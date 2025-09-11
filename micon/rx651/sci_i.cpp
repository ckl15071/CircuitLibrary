#include "sci_i.hpp"
#include "iodefine.h"
#include "port.hpp"

void Scii::setup(st_sci10* sci,
    st_port0* txPort, uint8_t txPin,
    st_port0* rxPort, uint8_t rxPin,
    uint32_t bitrate, uint32_t clock)
{
    m_sci = sci;
    m_txPort = txPort;
    m_rxPort = rxPort;
    m_txPin = txPin;
    m_rxPin = rxPin;

    //モジュールストップ解除
	SYSTEM.PRCR.WORD = 0xA502;
    if      (m_sci == &SCI10){MSTP(SCI10) = 0;}
    else if (m_sci == &SCI11){MSTP(SCI11) = 0;}
	SYSTEM.PRCR.WORD = 0xA500;

    //送受信禁止
    m_sci->SCR.BIT.TIE = 0;
    m_sci->SCR.BIT.TIE = 0;
    m_sci->SCR.BIT.RIE = 0;
    m_sci->SCR.BIT.TE = 0;
    m_sci->SCR.BIT.RE = 0;
    m_sci->SCR.BIT.TEIE = 0;

    //1.IO設定
    MPC.PWPR.BIT.B0WI = 0;      //PFSWEビットへの書き込み許可
    MPC.PWPR.BIT.PFSWE = 1;     //PFSレジスタへの書き込み許可
    if(m_sci == &SCI10)
    {
        if      (m_rxPort == (st_port0*)&PORT8 && m_rxPin == 1){MPC.P81PFS.BIT.PSEL = 0x0A;}
        else if (m_rxPort == (st_port0*)&PORT8 && m_rxPin == 6){MPC.P86PFS.BIT.PSEL = 0x0A;}
        else if (m_rxPort == (st_port0*)&PORTC && m_rxPin == 6){MPC.PC6PFS.BIT.PSEL = 0x24;}
        if      (m_txPort == (st_port0*)&PORT8 && m_txPin == 2){MPC.P82PFS.BIT.PSEL = 0x0A;}
        else if (m_txPort == (st_port0*)&PORT8 && m_txPin == 7){MPC.P87PFS.BIT.PSEL = 0x0A;}
        else if (m_txPort == (st_port0*)&PORTC && m_txPin == 7){MPC.PC7PFS.BIT.PSEL = 0x24;}
    }
    else if(m_sci == &SCI11)
    {
        if(m_txPort == (st_port0*)&PORT7 && m_txPin == 7){MPC.P77PFS.BIT.PSEL = 0x0A;}  //TXD11
        if(m_rxPort == (st_port0*)&PORT7 && m_rxPin == 6){MPC.P76PFS.BIT.PSEL = 0x0A;}  //RXD11
        if(m_txPort == (st_port0*)&PORTB && m_txPin == 7){MPC.PB7PFS.BIT.PSEL = 0x24;}  //TXD11
        if(m_rxPort == (st_port0*)&PORTB && m_rxPin == 6){MPC.PB6PFS.BIT.PSEL = 0x24;}  //RXD11
    }
    MPC.PWPR.BIT.PFSWE = 0;     //PFSレジスタへの書き込み禁止
    MPC.PWPR.BIT.B0WI = 1;      //PFSWEビットへの書き込み禁止 
    m_txPort->PMR.BYTE |= (0x01 << m_txPin);
    m_rxPort->PMR.BYTE |= (0x01 << m_rxPin);

    //2.
    m_sci->SCR.BIT.CKE = 0;   //SCK0端子はハイインピーダンス
    //3.
    //m_sci->SIMR1.BIT.IICM = 0;
    //m_sci->SPMR.BIT.CKPH = 0;
    //m_sci->SPMR.BIT.CKPOL = 0;

    //4.
    m_sci->SMR.BIT.CKS = 0;   //PCLK
    //m_sci->SMR.BIT.CKS = 1;   //PCLK(9600用)
    m_sci->SMR.BIT.MP = 0;    //マルチプロセッサ通信機能禁止
    m_sci->SMR.BIT.STOP = 0;  //1ストップビット
    //m_sci->SMR.BIT.PM = 0;    //偶数パリティ
    m_sci->SMR.BIT.PE = 0;    //パリティなし
    //m_sci->SMR.BIT.CHR = 0;    //データ長8ビット
    //m_sci->SCMR.BIT.CHR1 = 1;
    m_sci->SMR.BIT.CM = 0;    //調歩同期式or簡易i2cモード

    m_sci->SEMR.BIT.ABCS = 0;
    m_sci->SEMR.BIT.BGDM = 0;

    //5.
    //m_sci->BRR = 25;    //115200
    //m_sci->BRR = 77;    //9600用
    m_sci->BRR = clock * 1000000 / (32 * bitrate) - 1;

    //6.誤差補正値
    //m_sci->MDDR = 255;

    //7.
    //m_sci->SCR.BIT.TEIE = 1;  //TEI割り込み許可
    //m_sci->SCR.BIT.MPIE = 0;  //通常の受信動作

    //m_sci->SCR.BIT.RIE = 1;   //RXI、ERI割り込み要求許可
    //m_sci->SCR.BIT.TIE = 1;   //TXI割り込み要求許可
    //m_sci->SCR.BIT.RE = 1;    //シリアル受信動作許可
    //m_sci->SCR.BIT.TE = 1;    //シリアル送信動作許可
    m_sci->SCR.BYTE = 0xF0;

//    if(m_sci == &SCI10)
//    {
//        IPR(SCI10, TXI10) = 7;
//        IEN(SCI10, TXI10) = 0;
//        ICU.GENAL0.BIT.EN8 = 1;
//        ICU.GENAL0.BIT.EN9 = 1;
//    }
//    else if(m_sci == &SCI11)
//    {
//        IPR(SCI11, TXI11) = 7;
//        IEN(SCI11, TXI11) = 0;
//        ICU.GENAL0.BIT.EN12 = 1;
//        ICU.GENAL0.BIT.EN13 = 1;
//    }
//
//    //ICU.DTCER[112].BIT.DTCE = 0;    //CPUへの割り込み要因に設定
//    //ICU.IR[112].BIT.IR = 0;         //割り込み要求クリア
//    ICU.DTCER[IER_ICU_GROUPAL0].BIT.DTCE = 0;
//    ICU.IR[IER_ICU_GROUPAL0].BIT.IR = 0;
//    IPR(ICU, GROUPAL0) = 7;
//    IEN(ICU, GROUPAL0) = 1;

}

void Scii::putchar(char c)
{
    //while(SCI0.SSR.BIT.TDRE == 0);    //TDRレジスタに未送信のデータあり
    //while(SCI0.SSR.BIT.TEND == 0);    //キャラクタを送信中
    m_sci->TDR = c;
}

char Scii::getchar(void)
{
    return (char)m_sci->RDR;
}

//void Scii::setbitrate(E_bitrate bitrate)
//{
//    m_sci->BRR = bitrate;
//}

void startScii(void)
{
    //if(m_sci == &SCI10)
    //{
        IPR(SCI10, TXI10) = 7;
        IEN(SCI10, TXI10) = 0;
        ICU.GENAL0.BIT.EN8 = 1;
        ICU.GENAL0.BIT.EN9 = 1;

    //}
    //else if(m_sci == &SCI11)
    //{
        IPR(SCI11, TXI11) = 7;
        IEN(SCI11, TXI11) = 0;
        ICU.GENAL0.BIT.EN12 = 1;
        ICU.GENAL0.BIT.EN13 = 1;
    //}

    //受信割り込み
    IPR(SCI10, RXI10) = 7;
    IEN(SCI10, RXI10) = 1;  //受信割り込み有効
    IPR(SCI11, RXI11) = 7;
    IEN(SCI11, RXI11) = 1;  //受信割り込み有効

    ICU.DTCER[IER_ICU_GROUPAL0].BIT.DTCE = 0;   //CPUへの割り込み要因に設定
    ICU.IR[IER_ICU_GROUPAL0].BIT.IR = 0;        //割り込み要求クリア
    IPR(ICU, GROUPAL0) = 7;
    IEN(ICU, GROUPAL0) = 1;
}

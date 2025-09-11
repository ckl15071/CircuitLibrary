#include "sci_g.hpp"
#include "iodefine.h"
#include "port.hpp"

void Sci::setup(st_sci0* sci,
    st_port0* txPort, uint8_t txPin,
    st_port0* rxPort, uint8_t rxPin,
    uint32_t baudrate,
    uint32_t clock)
{
    m_sci = sci;
    m_txPort = txPort;
    m_rxPort = rxPort;
    m_txPin = txPin;
    m_rxPin = rxPin;

    //モジュールストップ解除
	SYSTEM.PRCR.WORD = 0xA502;
    if(m_sci == &SCI0){MSTP(SCI0) = 0;}
    if(m_sci == &SCI1){MSTP(SCI1) = 0;}
    if(m_sci == &SCI2){MSTP(SCI2) = 0;}
    if(m_sci == &SCI3){MSTP(SCI3) = 0;}
    if(m_sci == &SCI4){MSTP(SCI4) = 0;}
    if(m_sci == &SCI5){MSTP(SCI5) = 0;}
    if(m_sci == &SCI6){MSTP(SCI6) = 0;}
    if(m_sci == &SCI7){MSTP(SCI7) = 0;}
    if(m_sci == &SCI8){MSTP(SCI8) = 0;}
    if(m_sci == &SCI9){MSTP(SCI9) = 0;}
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
    if(m_sci == &SCI0)
    {
        if(m_txPort == (st_port0*)&PORT3 && m_txPin == 2){MPC.P32PFS.BIT.PSEL = 0x0B;}  //TXD0
        if(m_txPort == (st_port0*)&PORT2 && m_txPin == 0){MPC.P20PFS.BIT.PSEL = 0x0A;}  //TXD0
        if(m_rxPort == (st_port0*)&PORT2 && m_rxPin == 1){MPC.P21PFS.BIT.PSEL = 0x0A;}  //RXD0
    }
    else if(m_sci == &SCI1)
    {
        if(m_txPort == (st_port0*)&PORT1 && m_txPin == 6){MPC.P16PFS.BIT.PSEL = 0x0A;}  //TXD1
        if(m_rxPort == (st_port0*)&PORT1 && m_rxPin == 5){MPC.P15PFS.BIT.PSEL = 0x0A;}  //RXD1
        if(m_txPort == (st_port0*)&PORT2 && m_txPin == 6){MPC.P26PFS.BIT.PSEL = 0x0A;}  //TXD1
        if(m_rxPort == (st_port0*)&PORT3 && m_rxPin == 0){MPC.P30PFS.BIT.PSEL = 0x0A;}  //RXD1
    }
    else if(m_sci == &SCI2)
    {
        if(m_txPort == (st_port0*)&PORT1 && m_txPin == 3){MPC.P13PFS.BIT.PSEL = 0x0A;}  //TXD2
        if(m_rxPort == (st_port0*)&PORT1 && m_rxPin == 2){MPC.P12PFS.BIT.PSEL = 0x0A;}  //RXD2
        if(m_txPort == (st_port0*)&PORT5 && m_txPin == 0){MPC.P50PFS.BIT.PSEL = 0x0A;}  //TXD2
        if(m_rxPort == (st_port0*)&PORT5 && m_rxPin == 2){MPC.P52PFS.BIT.PSEL = 0x0A;}  //RXD2
    }
    else if(m_sci == &SCI3)
    {
        if(m_txPort == (st_port0*)&PORT2 && m_txPin == 3){MPC.P23PFS.BIT.PSEL = 0x0A;}  //TXD3
        if(m_rxPort == (st_port0*)&PORT2 && m_rxPin == 5){MPC.P25PFS.BIT.PSEL = 0x0A;}  //RXD3
        if(m_rxPort == (st_port0*)&PORT1 && m_rxPin == 6){MPC.P16PFS.BIT.PSEL = 0x0B;}  //RXD3
    }
    else if(m_sci == &SCI4)
    {
        ;
    }
    else if(m_sci == &SCI5)
    {
        if(m_txPort == (st_port0*)&PORTC && m_txPin == 3){MPC.PC3PFS.BIT.PSEL = 0x0A;}  //TXD5
        if(m_rxPort == (st_port0*)&PORTC && m_rxPin == 2){MPC.PC2PFS.BIT.PSEL = 0x0A;}  //RXD5
        if(m_txPort == (st_port0*)&PORTA && m_txPin == 4){MPC.PA4PFS.BIT.PSEL = 0x0A;}  //TXD5
        if(m_rxPort == (st_port0*)&PORTA && m_rxPin == 3){MPC.PA3PFS.BIT.PSEL = 0x0A;}  //RXD5
        if(m_rxPort == (st_port0*)&PORTA && m_rxPin == 2){MPC.PA2PFS.BIT.PSEL = 0x0A;}  //RXD5
    }
    else if(m_sci == &SCI6)
    {
        if(m_txPort == (st_port0*)&PORT3 && m_txPin == 2){MPC.P32PFS.BIT.PSEL = 0x0A;}  //TXD6
        if(m_rxPort == (st_port0*)&PORT3 && m_rxPin == 3){MPC.P33PFS.BIT.PSEL = 0x0A;}  //RXD6
        if(m_txPort == (st_port0*)&PORTB && m_txPin == 1){MPC.PB1PFS.BIT.PSEL = 0x0B;}  //TXD6
        if(m_rxPort == (st_port0*)&PORTB && m_rxPin == 0){MPC.PB0PFS.BIT.PSEL = 0x0B;}  //RXD6
    }
    else if(m_sci == &SCI7)
    {
        ;
    }
    else if(m_sci == &SCI8)
    {
        if(m_txPort == (st_port0*)&PORTC && m_txPin == 7){MPC.P32PFS.BIT.PSEL = 0x0A;}  //TXD8
        if(m_rxPort == (st_port0*)&PORTC && m_rxPin == 6){MPC.P33PFS.BIT.PSEL = 0x0A;}  //RXD8
    }
    else if(m_sci == &SCI9)
    {
        if(m_txPort == (st_port0*)&PORTB && m_txPin == 7){MPC.P32PFS.BIT.PSEL = 0x0A;}  //TXD9
        if(m_rxPort == (st_port0*)&PORTB && m_rxPin == 6){MPC.P33PFS.BIT.PSEL = 0x0A;}  //RXD9
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
    m_sci->SMR.BIT.MP = 0;    //マルチプロセッサ通信機能禁止
    m_sci->SMR.BIT.STOP = 0;  //1ストップビット
    //m_sci->SMR.BIT.PM = 0;    //偶数パリティ
    m_sci->SMR.BIT.PE = 0;    //パリティなし
    m_sci->SMR.BIT.CHR = 2;    //データ長8ビット
    m_sci->SMR.BIT.CM = 0;    //調歩同期式or簡易i2cモード

    m_sci->SEMR.BIT.ABCS = 0;
    m_sci->SEMR.BIT.BGDM = 0;

    //5.
    m_sci->BRR = 12;

    //6.誤差補正値
    m_sci->MDDR = 255;

    //7.
    m_sci->SCR.BIT.TEIE = 1;  //TEI割り込み許可
    //m_sci->SCR.BIT.MPIE = 0;  //通常の受信動作
    m_sci->SCR.BIT.RIE = 1;   //RXI、ERI割り込み要求許可
    m_sci->SCR.BIT.TIE = 1;   //TXI割り込み要求許可
    m_sci->SCR.BIT.RE = 1;    //シリアル受信動作許可
    m_sci->SCR.BIT.TE = 1;    //シリアル送信動作許可

    if(m_sci == &SCI0)
    {
        IPR(SCI0, TXI0) = 7;
        IEN(SCI0, TXI0) = 0;
        ICU.GENBL0.BIT.EN0 = 1;     //SCI0送信完了
        ICU.GENBL0.BIT.EN1 = 1;     //SCI0受信エラー
    }
    else if(m_sci == &SCI1)
    {
        IPR(SCI1, TXI1) = 7;
        IEN(SCI1, TXI1) = 0;
        ICU.GENBL0.BIT.EN2 = 1; //SCI1送信完了
        ICU.GENBL0.BIT.EN3 = 1; //SCI1受信エラー
    }
    else if(m_sci == &SCI2)
    {
        IPR(SCI2, TXI2) = 7;
        IEN(SCI2, TXI2) = 0;
        ICU.GENBL0.BIT.EN4 = 1; //SCI2送信完了
        ICU.GENBL0.BIT.EN5 = 1; //SCI1受信エラー
    }
    else if(m_sci == &SCI3)
    {
        IPR(SCI3, TXI3) = 7;
        IEN(SCI3, TXI3) = 0;
        ICU.GENBL0.BIT.EN6 = 1; //SCI3
        ICU.GENBL0.BIT.EN7 = 1;
    }
    else if(m_sci == &SCI4)
    {
        IPR(SCI4, TXI4) = 7;
        IEN(SCI4, TXI4) = 0;
        ICU.GENBL0.BIT.EN8 = 1; //SCI4
        ICU.GENBL0.BIT.EN9 = 1;
    }
    else if(m_sci == &SCI5)
    {
        IPR(SCI5, TXI5) = 7;
        IEN(SCI5, TXI5) = 0;
        ICU.GENBL0.BIT.EN10 = 1; //SCI5
        ICU.GENBL0.BIT.EN11 = 1;
    }
    else if(m_sci == &SCI6)
    {
        IPR(SCI6, TXI6) = 7;
        IEN(SCI6, TXI6) = 0;
        ICU.GENBL0.BIT.EN12 = 1; //SCI6
        ICU.GENBL0.BIT.EN13 = 1;
    }
    else if(m_sci == &SCI7)
    {
        IPR(SCI7, TXI7) = 7;
        IEN(SCI7, TXI7) = 0;
        ICU.GENBL0.BIT.EN14 = 1; //SCI7
        ICU.GENBL0.BIT.EN15 = 1;
    }
    else if(m_sci == &SCI8)
    {
        IPR(SCI8, TXI8) = 7;
        IEN(SCI8, TXI8) = 0;
        ICU.GENBL1.BIT.EN24 = 1; //SCI8
        ICU.GENBL1.BIT.EN25 = 1;
    }
    else if(m_sci == &SCI9)
    {
        IPR(SCI9, TXI9) = 7;
        IEN(SCI9, TXI9) = 0;
        ICU.GENBL1.BIT.EN26 = 1; //SCI9
        ICU.GENBL1.BIT.EN27 = 1;
    }

    if( m_sci == &SCI0 || m_sci == &SCI1 || m_sci == &SCI2 || m_sci == &SCI3 ||
        m_sci == &SCI4 || m_sci == &SCI5 || m_sci == &SCI6 || m_sci == &SCI7)
    {
        ICU.DTCER[110].BIT.DTCE = 0;    //CPUへの割り込み要因に設定
        ICU.IR[110].BIT.IR = 0;         //割り込み要求クリア
        IPR(ICU, GROUPBL0) = 7;
        IEN(ICU, GROUPBL0) = 1;
    }
    else if(m_sci == &SCI8 || m_sci == &SCI9)
    {
        ICU.DTCER[111].BIT.DTCE = 0;    //CPUへの割り込み要因に設定
        ICU.IR[111].BIT.IR = 0;         //割り込み要求クリア
        IPR(ICU, GROUPBL1) = 7;
        IEN(ICU, GROUPBL1) = 1;
    }
}

void Sci::putchar(char c)
{
    //while(SCI0.SSR.BIT.TDRE == 0);    //TDRレジスタに未送信のデータあり
    //while(SCI0.SSR.BIT.TEND == 0);    //キャラクタを送信中
    m_sci->TDR = c;
}

char Sci::getchar(void)
{
    return (char)m_sci->RDR;
}

void Sci::setBaudrate(E_BAUDRATE baudrate)
{
    m_sci->BRR = baudrate;
}

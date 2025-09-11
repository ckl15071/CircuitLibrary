#include "sci_simple_i2c.hpp"
#include "iodefine.h"
#include "port.hpp"

void SciSimpleI2c::setup(st_sci0* sci,
        st_port0* sclPort, uint8_t sclPin,
        st_port0* sdaPort, uint8_t sdaPin,
        uint32_t bitrate, uint32_t clock)
{
    m_sci = sci;
    m_sclPort = sclPort;
    m_sclPin = sclPin;
    m_sdaPort = sdaPort;
    m_sdaPin = sdaPin;

    //モジュールストップ解除
    this->resetModuleStop();

    m_sci->SCR.BIT.TIE = 0;
    m_sci->SCR.BIT.RIE = 0;
    m_sci->SCR.BIT.TE = 0;
    m_sci->SCR.BIT.RE = 0;
    m_sci->SCR.BIT.TEIE = 0;

    //[1]Nチャネルオープンドレイン出力、ハイインピーダンス
    this->setupIo();
    //m_sclPin->setup();
    //m_sdaPin->setup();
    //Port gpioScl(sclPort, sclPin, Port::OUTPUT_CMOS);
    //Port gpioSda(sdaPort, sdaPin, Port::OUTPUT_CMOS);

    //[2]
    m_sci->SIMR3.BIT.IICSDAS = 0x03;
    m_sci->SIMR3.BIT.IICSCLS = 0x03;

    //[3]
    m_sci->SMR.BYTE = 0x00;
    m_sci->SMR.BIT.CKS = 0;
    m_sci->SCMR.BIT.SDIR = 1;
    m_sci->SCMR.BIT.SINV = 0;
    m_sci->SCMR.BIT.SMIF = 0;

    //[4],[5]
    //48MHz、100kbps
    m_sci->SCR.BIT.CKE = 0;
    //m_sci->BRR = 14;
    m_sci->BRR = clock * 1000000 / (32 * bitrate) - 1;

    //48MHz、400kbps
    //m_sci->SCR.BIT.CKE = 0;
    //m_sci->BRR = 3;   //2.75
    //m_sci->MDDR = ;

    //[6]
    m_sci->SEMR.BIT.NFEN = 0;       //ノイズ除去
    m_sci->SEMR.BIT.BRME = 0;       //ビットレートモジュレーション
    m_sci->SNFR.BIT.NFCS = 1;       //ノイズフィルタクロックセレクト
    m_sci->SIMR1.BIT.IICM = 1;      //簡易I2Cモードセレクト
    m_sci->SIMR1.BIT.IICDL = 0x10;     //SSDA出力遅延セレクト
    m_sci->SIMR2.BIT.IICACKT = 1;
    m_sci->SIMR2.BIT.IICCSC = 1;
    m_sci->SIMR2.BIT.IICINTM = 0;   //I2C割り込みモードセレクト
    m_sci->SPMR.BYTE = 0x00;

    //[7]
    m_sci->SCR.BYTE = 0x30;
    //m_sci->SCR.BIT.TE = 1;
    //m_sci->SCR.BIT.RE = 1;
    //m_sci->SCR.BIT.TIE = 1;
    //m_sci->SCR.BIT.RIE = 1;
    //m_sci->SCR.BIT.TEIE = 1;
}

int SciSimpleI2c::beginTransmission(uint8_t address)
{
    //[2]
    m_sci->SIMR3.BIT.IICSTIF = 1;
    m_sci->SIMR3.BIT.IICSCLS = 1;
    m_sci->SIMR3.BIT.IICSDAS = 1;

    //条件生成完了待ち
    while(m_sci->SIMR3.BIT.IICSTIF == 0);

    //データ送信準備
    m_sci->SIMR3.BIT.IICSTIF = 0;
    m_sci->SIMR3.BIT.IICSCLS = 0;
    m_sci->SIMR3.BIT.IICSDAS = 0;

    //[3]TDRレジスタにスレーブアドレス、R/Wビットをライト
    //D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | W(=0)
    m_sci->TDR = (address << 1) & 0xFE | 0x00;

    //送信完了待ち
    while(m_sci->SSR.BIT.TEND == 0);

    //ACK確認
    return m_sci->SISR.BIT.IICACKR;
}

int SciSimpleI2c::beginTransmission(uint8_t address, uint8_t reg)
{
    m_sci->SIMR3.BIT.IICSTIF = 0;
    //[2]
    m_sci->SIMR3.BYTE = 0x51;
    //m_sci->SIMR3.BIT.IICSTAREQ = 1;
    //m_sci->SIMR3.BIT.IICSCLS = 1;
    //m_sci->SIMR3.BIT.IICSDAS = 1;

    //条件生成完了待ち
    while(m_sci->SIMR3.BIT.IICSTIF == 0);

    //データ送信準備
    m_sci->SIMR3.BIT.IICSTIF = 0;
    m_sci->SIMR3.BIT.IICSCLS = 0;
    m_sci->SIMR3.BIT.IICSDAS = 0;

    //[3]TDRレジスタにスレーブアドレス、R/Wビットをライト
    //D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | W(=0)
    uint8_t val = 0;
    val |= (address << 1);
    m_sci->TDR = val;

    //送信完了待ち
    while(m_sci->SSR.BIT.TEND == 0);
    //while(m_sci->SSR.BIT.TDRE == 0);

    //if(m_sci->SISR.BIT.IICACKR == 1){return m_sci->SISR.BIT.IICACKR;}

    m_sci->TDR = reg;
    while(m_sci->SSR.BIT.TEND == 0);
    //while(m_sci->SSR.BIT.TDRE == 0);

    //ACK確認
    return m_sci->SISR.BIT.IICACKR;
}

int SciSimpleI2c::endTransmission(void)
{
    m_sci->SIMR3.BIT.IICSTIF = 0;

    m_sci->SIMR3.BYTE = 0x54;
    //m_sci->SIMR3.BIT.IICSTPREQ = 1;
    //m_sci->SIMR3.BIT.IICSCLS = 1;
    //m_sci->SIMR3.BIT.IICSDAS = 1;

    //条件生成完了待ち
    while(m_sci->SIMR3.BIT.IICSTIF == 0);

    m_sci->SIMR3.BIT.IICSTIF = 0;
    m_sci->SIMR3.BIT.IICSCLS = 3;
    m_sci->SIMR3.BIT.IICSDAS = 3;

    return m_sci->SISR.BIT.IICACKR;
}

int SciSimpleI2c::write(uint8_t val)
{
    //[4]
    //TDRに送信データをライト
    m_sci->TDR = val;

    //送信完了待ち
    while(m_sci->SSR.BIT.TEND == 0);

    ////[6]
    //m_sci->SIMR3.BIT.IICSTPREQ = 1;
    //m_sci->SIMR3.BIT.IICSCLS = 1;
    //m_sci->SIMR3.BIT.IICSDAS = 1;

    ////条件生成完了待ち
    //while(m_sci->SIMR3.BIT.IICSTIF == 0);

    //m_sci->SIMR3.BIT.IICSTIF = 0;
    //m_sci->SIMR3.BIT.IICSCLS = 3;
    //m_sci->SIMR3.BIT.IICSDAS = 3;

    return m_sci->SISR.BIT.IICACKR;
}

int SciSimpleI2c::write(uint8_t* data, int length)
{
    for(int i = 0; i < length; i++)
    {
        m_sci->TDR = data[i];

        //送信完了待ち
        while(m_sci->SSR.BIT.TEND == 0);
    }

    return m_sci->SISR.BIT.IICACKR;
}

void SciSimpleI2c::resetModuleStop(void)
{
    SYSTEM.PRCR.WORD = 0xA502;
    if(m_sci == &SCI0){MSTP(SCI0) = 0;}
    else if(m_sci == &SCI1){MSTP(SCI1) = 0;}
    else if(m_sci == &SCI2){MSTP(SCI2) = 0;}
    else if(m_sci == &SCI3){MSTP(SCI3) = 0;}
    else if(m_sci == &SCI4){MSTP(SCI4) = 0;}
    else if(m_sci == &SCI5){MSTP(SCI5) = 0;}
    else if(m_sci == &SCI6){MSTP(SCI6) = 0;}
    else if(m_sci == &SCI7){MSTP(SCI7) = 0;}
    else if(m_sci == &SCI8){MSTP(SCI8) = 0;}
    else if(m_sci == &SCI9){MSTP(SCI9) = 0;}
    SYSTEM.PRCR.WORD = 0xA500;
}

void SciSimpleI2c::setupIo(void)
{
    MPC.PWPR.BIT.B0WI = 0;      //PFSWEビットへの書き込み許可
    MPC.PWPR.BIT.PFSWE = 1;     //PFSレジスタへの書き込み許可

    //100ピンに対応
    if(m_sci == &SCI0)
    {
        //if(m_sclPort == (st_port0*)&PORT3 && m_sclPin == 4){MPC.P34PFS.BIT.PSEL = 0x0B;}
        //if(m_sdaPort == (st_port0*)&PORT3 && m_sdaPin == 2){MPC.P32PFS.BIT.PSEL = 0x0B;}
    }
    if(m_sci == &SCI1)
    {
    }
    if(m_sci == &SCI2)
    {
        if(m_sclPort == (st_port0*)&PORT1 && m_sclPin == 2){MPC.P12PFS.BIT.PSEL = 0x0A;}
        if(m_sdaPort == (st_port0*)&PORT1 && m_sdaPin == 3){MPC.P13PFS.BIT.PSEL = 0x0A;}
    }
    if(m_sci == &SCI3)
    {
        if(m_sclPort == (st_port0*)&PORT2 && m_sclPin == 5){MPC.P25PFS.BIT.PSEL = 0x0A;}
        if(m_sdaPort == (st_port0*)&PORT2 && m_sdaPin == 3){MPC.P23PFS.BIT.PSEL = 0x0A;}
    }
    if(m_sci == &SCI4)
    {
    }
    if(m_sci == &SCI5)
    {
    }
    if(m_sci == &SCI6)
    {
    }
    if(m_sci == &SCI7)
    {
    }
    if(m_sci == &SCI8)
    {
    }
    if(m_sci == &SCI9)
    {
    }
    MPC.PWPR.BIT.PFSWE = 0;     //PFSレジスタへの書き込み禁止
    MPC.PWPR.BIT.B0WI = 1;      //PFSWEビットへの書き込み禁止 

    m_sclPort->PMR.BYTE |= (0x01 << m_sclPin);
    m_sdaPort->PMR.BYTE |= (0x01 << m_sdaPin);
}

void SciSimpleI2c::start(void)
{
    IPR(SCI2, TXI2) = 7;
    IEN(SCI2, TXI2) = 0;
}

//Hardware

//void isr(void)
//{
//
//}

//void SciSimpleI2c::writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t sendStop)
//{
//    uint8_t slarw = 0;  //Write
//    slarw |= address << 1;
//
//    if(inReqStart == true)
//    {
//        inReqStart = false;
//        //送信開始
//    }
//
//    //受信
//    //if(twi_error == 0xFF)
//    //{
//    //    return 0;   //Success
//    //}
//    //else if(twi_error == TW_MT_SLA_NACK)
//    //{
//    //    return 2;   //Error: address send, nack received
//    //}
//    //else if(twi_error == TW_MT_DATA_NACK)
//    //{
//    //    return 3;  //Error: data send, nack received
//    //}
//    //else
//    //{
//    //    return 4;   //Other twi error
//    //}
//    
//
//}
//
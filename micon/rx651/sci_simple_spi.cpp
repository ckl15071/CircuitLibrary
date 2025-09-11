#include "sci_simple_spi.hpp"

//SS端子（出力）は汎用ポートで制御
//マスタモードかスレーブモードかの設定
void SciSimpleSpi::setup(st_sci0* sci,
        st_port0* sckPort, uint8_t sckPin,
        st_port0* smosiPort, uint8_t smosiPin,
        st_port0* smisoPort, uint8_t smisoPin,
        uint32_t bitrate, uint32_t clock,
        uint8_t bitOrder, uint8_t dataMode
)
{
    m_sci = sci;
    m_sckPort = sckPort;
    m_sckPin = sckPin;
    m_smosiPort = smosiPort;
    m_smosiPin = smosiPin;
    m_smisoPort = smisoPort;
    m_smisoPin = smisoPin;

    //モジュールストップ解除
    resetModuleStop();

    //送受信禁止
    m_sci->SCR.BIT.TIE = 0;
    m_sci->SCR.BIT.RIE = 0;
    m_sci->SCR.BIT.TE = 0;
    m_sci->SCR.BIT.RE = 0;
    m_sci->SCR.BIT.TEIE = 0;

    //1.IO設定
    setupIo();

    //2.
    m_sci->SCR.BIT.CKE = 0;

    //3.
    m_sci->SIMR1.BIT.IICM = 0;
    this->setDataMode(dataMode);
    //SPIモードレジスタ
    m_sci->SPMR.BIT.SSE = 0;    //SSn#端子機能禁止
    m_sci->SPMR.BIT.CTSE = 0;   //CTS機能禁止
    m_sci->SPMR.BIT.MSS = 0;    //マスタモード

    //4
    //m_sci->SMR.BIT.CKS = 0;     //PCLK
    m_sci->SMR.BIT.CKS = 1;     //PCLK
    //m_sci->SMR.BIT.MP = 0;      //マルチプロセッサ通信機能禁止
    //m_sci->SMR.BIT.STOP = 0;    //1ストップビット
    //m_sci->SMR.BIT.PE = 0;      //パリティなし
    //m_sci->SMR.BIT.CHR = 2;     //データ長8ビット
    m_sci->SMR.BIT.CM = 1;      //クロック同期式モードor簡易SPIモード
    m_sci->SCMR.BIT.SMIF = 0;   //非SMIF（調歩同期式、クロック同期式、簡易SPI、簡易I2C）
    this->setBitOrder(bitOrder);

    //5.
    //m_sci->BRR = 2;
    //m_sci->BRR = 3;
    m_sci->BRR = clock * 1000000 / (8 * 2 * bitrate) - 1;
    //this->setClockDivider(bitrate, clock);

    //6.誤差補正値
    //m_sci->MDDR = 255;



    //7.
//    m_sci->SCR.BIT.TEIE = 1;  //TEI割り込み許可
//    //m_sci->SCR.BIT.MPIE = 0;  //通常の受信動作
    //m_sci->SCR.BIT.RIE = 1;   //RXI、ERI割り込み要求許可
//    m_sci->SCR.BIT.TIE = 1;   //TXI割り込み要求許可
    //m_sci->SCR.BIT.RE = 1;    //シリアル受信動作許可
    //m_sci->SCR.BIT.TE = 1;    //シリアル送信動作許可
    m_sci->SCR.BYTE |= 0x30;
}

void SciSimpleSpi::setBitOrder(uint8_t bitOrder)
{
    if(bitOrder == LSBFIRST)
    {
        m_sci->SCMR.BIT.SDIR = LSBFIRST;
    }
    else
    {
        m_sci->SCMR.BIT.SDIR = MSBFIRST;
    }
}

void SciSimpleSpi::setDataMode(uint8_t dataMode)
{
    switch(dataMode)
    {
    case SPI_MODE0:
    default:
        m_sci->SPMR.BIT.CKPOL = 0;
        m_sci->SPMR.BIT.CKPH = 0;
        break;
    case SPI_MODE1:
        m_sci->SPMR.BIT.CKPOL = 0;
        m_sci->SPMR.BIT.CKPH = 1;
        break;
    case SPI_MODE2:
        m_sci->SPMR.BIT.CKPOL = 1;
        m_sci->SPMR.BIT.CKPH = 0;
        break;
    case SPI_MODE3:
        m_sci->SPMR.BIT.CKPOL = 1;
        m_sci->SPMR.BIT.CKPH = 1;
        break;
    }
}

void SciSimpleSpi::setClockDivider(uint32_t bitrate, uint32_t clock)
{

}

uint8_t SciSimpleSpi::transfer(uint8_t data)
{
    uint8_t ret = 0;
    while(m_sci->SSR.BIT.TDRE == 0);
    m_sci->TDR = data;
    while(m_sci->SSR.BIT.TEND == 0);
    while(m_sci->SSR.BIT.RDRF == 0)
    {
        if(m_sci->SSR.BIT.ORER == 1)
        {
            m_sci->SSR.BIT.ORER = 0;
        }
    }
    return m_sci->RDR;
}

void SciSimpleSpi::resetModuleStop(void)
{
	SYSTEM.PRCR.WORD = 0xA502;
    if      (m_sci == &SCI0){MSTP(SCI0) = 0;}
    else if (m_sci == &SCI1){MSTP(SCI1) = 0;}
    else if (m_sci == &SCI2){MSTP(SCI2) = 0;}
    else if (m_sci == &SCI3){MSTP(SCI3) = 0;}
    else if (m_sci == &SCI4){MSTP(SCI4) = 0;}
    else if (m_sci == &SCI5){MSTP(SCI5) = 0;}
    else if (m_sci == &SCI6){MSTP(SCI6) = 0;}
    else if (m_sci == &SCI7){MSTP(SCI7) = 0;}
    else if (m_sci == &SCI8){MSTP(SCI8) = 0;}
    else if (m_sci == &SCI9){MSTP(SCI9) = 0;}
	SYSTEM.PRCR.WORD = 0xA500;
}

void SciSimpleSpi::setupIo(void)
{
    MPC.PWPR.BIT.B0WI = 0;      //PFSWEビットへの書き込み許可
    MPC.PWPR.BIT.PFSWE = 1;     //PFSレジスタへの書き込み許可

    //100ピンに対応
    if(m_sci == &SCI0)
    {
        if      (m_smisoPort    == (st_port0*)&PORT2 && m_smisoPin  == 1){MPC.P21PFS.BIT.PSEL = 0x0A;}
        else if (m_smisoPort    == (st_port0*)&PORT3 && m_smosiPin  == 3){MPC.P33PFS.BIT.PSEL = 0x0B;}
        if      (m_smosiPort    == (st_port0*)&PORT2 && m_smosiPin  == 0){MPC.P20PFS.BIT.PSEL = 0x0A;}
        else if (m_smosiPort    == (st_port0*)&PORT3 && m_smosiPin  == 2){MPC.P32PFS.BIT.PSEL = 0x0B;}
        if      (m_sckPort      == (st_port0*)&PORT2 && m_sckPin    == 2){MPC.P22PFS.BIT.PSEL = 0x0A;}
        else if (m_sckPort      == (st_port0*)&PORT3 && m_sckPin    == 4){MPC.P34PFS.BIT.PSEL = 0x0B;}
    }
    else if(m_sci == &SCI1)
    {
        if      (m_smisoPort    == (st_port0*)&PORT1 && m_smisoPin  == 5){MPC.P15PFS.BIT.PSEL = 0x0A;}
        else if (m_smisoPort    == (st_port0*)&PORT3 && m_smisoPin  == 0){MPC.P30PFS.BIT.PSEL = 0x0A;}
        //else if(m_smisoPort  == (st_port0*)&PORTF && m_smisoPin  == 2){MPC.PF2PFS.BIT.PSEL = 0x0A;}
        if      (m_smosiPort    == (st_port0*)&PORT1 && m_smosiPin  == 6){MPC.P16PFS.BIT.PSEL = 0x0A;}
        else if (m_smosiPort    == (st_port0*)&PORT2 && m_smosiPin  == 6){MPC.P26PFS.BIT.PSEL = 0x0A;}
        //else if(m_smosiPort  == (st_port0*)&PORTF && m_smosiPin  == 0){MPC.PF0PFS.BIT.PSEL = 0x0A;}
        if      (m_sckPort      == (st_port0*)&PORT1 && m_sckPin    == 7){MPC.P17PFS.BIT.PSEL = 0x0A;}
        else if (m_sckPort      == (st_port0*)&PORT2 && m_sckPin    == 7){MPC.P27PFS.BIT.PSEL = 0x0A;}
        //else if(m_sckPort    == (st_port0*)&PORTF && m_sckPin    == 1){MPC.PF1PFS.BIT.PSEL = 0x0A;}
    }
    else if(m_sci == &SCI2)
    {
        if      (m_smisoPort    == (st_port0*)&PORT1 && m_smisoPin  == 2){MPC.P12PFS.BIT.PSEL = 0x0A;}
        else if (m_smisoPort    == (st_port0*)&PORT5 && m_smisoPin  == 2){MPC.P52PFS.BIT.PSEL = 0x0A;}
        if      (m_smosiPort    == (st_port0*)&PORT1 && m_smosiPin  == 3){MPC.P13PFS.BIT.PSEL = 0x0A;}
        else if (m_smosiPort    == (st_port0*)&PORT5 && m_smosiPin  == 0){MPC.P50PFS.BIT.PSEL = 0x0A;}
        //if(m_sckPort    == (st_port0*)&PORT1 && m_sckPin    == 1){MPC.P11PFS.BIT.PSEL = 0x0A;}
        if      (m_sckPort      == (st_port0*)&PORT5 && m_sckPin    == 1){MPC.P51PFS.BIT.PSEL = 0x0A;}
    }
    else if(m_sci == &SCI3)
    {
        if      (m_smisoPort    == (st_port0*)&PORT1 && m_smisoPin  == 6){MPC.P16PFS.BIT.PSEL = 0x0B;}
        else if (m_smisoPort    == (st_port0*)&PORT2 && m_smisoPin  == 5){MPC.P25PFS.BIT.PSEL = 0x0A;}
        //if(m_smosiPort  == (st_port0*)&PORT1 && m_smosiPin  == 7){MPC.P17PFS.BIT.PSEL = 0x0A;}
        if      (m_smosiPort    == (st_port0*)&PORT2 && m_smosiPin  == 3){MPC.P23PFS.BIT.PSEL = 0x0A;}
        //if(m_sckPort    == (st_port0*)&PORT1 && m_sckPin    == 5){MPC.P15PFS.BIT.PSEL = 0x0A;}
        if      (m_sckPort      == (st_port0*)&PORT2 && m_sckPin    == 4){MPC.P24PFS.BIT.PSEL = 0x0A;}
    }
    else if(m_sci == &SCI4)
    {
        if(m_smisoPort          == (st_port0*)&PORTB && m_smisoPin  == 0){MPC.PB0PFS.BIT.PSEL = 0x0A;}
        if(m_smosiPort          == (st_port0*)&PORTB && m_smosiPin  == 1){MPC.PB1PFS.BIT.PSEL = 0x0A;}
        if(m_sckPort            == (st_port0*)&PORTB && m_sckPin    == 3){MPC.PB3PFS.BIT.PSEL = 0x0A;}
    }
    else if(m_sci == &SCI5)
    {
        if      (m_smisoPort    == (st_port0*)&PORTA && m_smisoPin  == 2){MPC.PA2PFS.BIT.PSEL = 0x0A;}
        else if (m_smisoPort    == (st_port0*)&PORTA && m_smisoPin  == 3){MPC.PA3PFS.BIT.PSEL = 0x0A;}
        else if (m_smisoPort    == (st_port0*)&PORTC && m_smisoPin  == 2){MPC.PC2PFS.BIT.PSEL = 0x0A;}
        if      (m_smosiPort    == (st_port0*)&PORTA && m_smosiPin  == 4){MPC.PA4PFS.BIT.PSEL = 0x0A;}
        else if (m_smosiPort    == (st_port0*)&PORTC && m_smosiPin  == 3){MPC.PC3PFS.BIT.PSEL = 0x0A;}
        if      (m_sckPort      == (st_port0*)&PORTA && m_sckPin    == 1){MPC.PA1PFS.BIT.PSEL = 0x0A;}
        else if (m_sckPort      == (st_port0*)&PORTC && m_sckPin    == 1){MPC.PC1PFS.BIT.PSEL = 0x0A;}
        else if (m_sckPort      == (st_port0*)&PORTC && m_sckPin    == 4){MPC.PC4PFS.BIT.PSEL = 0x0A;}
    }
    else if(m_sci == &SCI6)
    {
        if      (m_smisoPort    == (st_port0*)&PORT0 && m_smisoPin  == 1){MPC.P01PFS.BIT.PSEL = 0x0A;}
        else if (m_smisoPort    == (st_port0*)&PORT3 && m_smisoPin  == 3){MPC.P33PFS.BIT.PSEL = 0x0A;}
        else if (m_smisoPort    == (st_port0*)&PORTB && m_smisoPin  == 0){MPC.PB0PFS.BIT.PSEL = 0x0B;}
        if      (m_smosiPort    == (st_port0*)&PORT0 && m_smosiPin  == 0){MPC.P00PFS.BIT.PSEL = 0x0A;}
        else if (m_smosiPort    == (st_port0*)&PORT3 && m_smosiPin  == 2){MPC.P32PFS.BIT.PSEL = 0x0A;}
        else if (m_smosiPort    == (st_port0*)&PORTB && m_smosiPin  == 1){MPC.PB1PFS.BIT.PSEL = 0x0B;}
        if      (m_sckPort      == (st_port0*)&PORT0 && m_sckPin    == 2){MPC.P02PFS.BIT.PSEL = 0x0A;}
        else if (m_sckPort      == (st_port0*)&PORT3 && m_sckPin    == 4){MPC.P34PFS.BIT.PSEL = 0x0A;}
        else if (m_sckPort      == (st_port0*)&PORTB && m_sckPin    == 3){MPC.PB3PFS.BIT.PSEL = 0x0B;}
    }
    else if(m_sci == &SCI7)
    {
        if      (m_smisoPort    == (st_port0*)&PORT5 && m_smisoPin  == 7){MPC.P57PFS.BIT.PSEL = 0x0A;}
        else if (m_smisoPort    == (st_port0*)&PORT9 && m_smisoPin  == 2){MPC.P92PFS.BIT.PSEL = 0x0A;}
        if      (m_smosiPort    == (st_port0*)&PORT5 && m_smosiPin  == 5){MPC.P55PFS.BIT.PSEL = 0x0A;}
        else if (m_smosiPort    == (st_port0*)&PORT9 && m_smosiPin  == 0){MPC.P90PFS.BIT.PSEL = 0x0A;}
        if      (m_sckPort      == (st_port0*)&PORT5 && m_sckPin    == 6){MPC.P56PFS.BIT.PSEL = 0x0A;}
        else if (m_sckPort      == (st_port0*)&PORT9 && m_sckPin    == 1){MPC.P91PFS.BIT.PSEL = 0x0A;}
    }
    else if(m_sci == &SCI8)
    {
        if      (m_smisoPort    == (st_port0*)&PORTC && m_smisoPin  == 6){MPC.PC6PFS.BIT.PSEL = 0x0A;}
        else if (m_smisoPort    == (st_port0*)&PORTJ && m_smisoPin  == 1){MPC.PJ1PFS.BIT.PSEL = 0x0A;}
        if      (m_smosiPort    == (st_port0*)&PORTC && m_smosiPin  == 7){MPC.PC7PFS.BIT.PSEL = 0x0A;}
        else if (m_smosiPort    == (st_port0*)&PORTJ && m_smosiPin  == 2){MPC.PJ2PFS.BIT.PSEL = 0x0A;}
        if      (m_sckPort      == (st_port0*)&PORTC && m_sckPin    == 5){MPC.PC5PFS.BIT.PSEL = 0x0A;}
        else if (m_sckPort      == (st_port0*)&PORTJ && m_sckPin    == 0){MPC.PJ0PFS.BIT.PSEL = 0x0A;}
    }
    else if(m_sci == &SCI9)
    {
        if      (m_smisoPort    == (st_port0*)&PORTB && m_smisoPin  == 6){MPC.PB6PFS.BIT.PSEL = 0x0A;}
        if      (m_smosiPort    == (st_port0*)&PORTB && m_smosiPin  == 7){MPC.PB7PFS.BIT.PSEL = 0x0A;}
        if      (m_sckPort      == (st_port0*)&PORTB && m_sckPin    == 5){MPC.PB5PFS.BIT.PSEL = 0x0A;}
    }
    MPC.PWPR.BIT.PFSWE = 0;     //PFSレジスタへの書き込み禁止
    MPC.PWPR.BIT.B0WI = 1;      //PFSWEビットへの書き込み禁止 
    m_sckPort->PMR.BYTE     |= (0x01 << m_sckPin);
    m_smosiPort->PMR.BYTE   |= (0x01 << m_smosiPin);
    m_smisoPort->PMR.BYTE   |= (0x01 << m_smisoPin);
}

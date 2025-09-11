#include "RCC.hpp"
#include <math.h>

//PERIPH->REGにのビットをVALにする
#define writeBit(PERIPH, REG, SYM, VAL) (PERIPH->REG)=((PERIPH->REG)&(~PERIPH##_##REG##_##SYM##_Msk))|(VAL<<PERIPH##_##REG##_##SYM##_Pos)
#define writeReg(PERIPH, REG, VAL)      ()
#define readBit(PERIPH, REG, SYM)       (((PERIPH->REG)&PERIPH##_##REG##_##SYM##_Msk)>>PERIPH##_##REG##_##SYM##_Pos)
#define readReg(PERIPH, REG)            ()

namespace clock
{

int m_freqLSI = 32;
int m_freqHSI = 16;
float m_freqLSE;
int m_freqHSE;

int m_PLLQ = 0;
int m_PLLP = 0;
int m_PLLN = 0;
int m_PLLM = 0;
int m_AHBPrescaler = 0;
int m_APB1Prescaler = 0;
int m_APB2Prescaler = 0;

int m_freqHCLK;
int m_freqAPB1Peripheral = 0;   //PCLK1
int m_freqAPB1Timer = 0;
int m_freqAPB2Peripheral = 0;   //PCLK2
int m_freqAPB2Timer = 0;
int m_freqCortexSystem = 0;
int m_freqFCLK = 0;
int m_freqUSB = 0;
int m_freqVCO = 0;
int m_freqPLLIn;
int m_freqPLLOut;
int m_freqSYSCLK;

float m_powerVoltage = 0;

void setup_72MHz(void)
{

}

void setup_144MHz(void)
{

}

void setup_168MHz_HSE(void)
{
    //:**********************************************************************
    //!
    //! AHB
    //! FCLK    :MHz
    //! APB1 Peripheral clock    :MHz
    //! APB1 Timer clock    :MHz
    //! APB2 Peripheral clock(PCLK2) :MHz
    //! APB2 Timer clock    :MHz
    //! FLIT
    //!
    //:**********************************************************************
    //writeBit(RCC, CR, PLLON, 0);
    //while(readBit(RCC, CR, PLLRDY) == 1);   //PLL停止待ち

    //writeBit(RCC, CR, HSEON, 1);
    //while(readBit(RCC, CR, HSERDY) == 0);   //HSE動作待ち
    //writeBit(RCC, CFGR, PLLMULL, 0x4);      //PLLx6=72MHz
    ////writeBit(RCC, CFGR, PLLMULL, 0x7);      //PLLx9=72MHz
    //writeBit(RCC, CFGR, PLLSRC, 1);         //PLLソースにHSE
    //writeBit(RCC, CFGR, PPRE1, 0x4);        //2分周
    //writeBit(RCC, CFGR, SW, 0x2);           //システムクロックにPLL使用
    //writeBit(FLASH, ACR, LATENCY, 4);       //FLASH読み込みの遅延時間設定
    
    //writeBit(RCC, CR, PLLON, 1);
    //while(readBit(RCC, CR, PLLRDY) == 0);   //PLL安定化待ち

    RCC->CR &= ~RCC_CR_PLLON;
    while(RCC->CR & RCC_CR_PLLRDY);	//PLL停止待ち

    RCC->CR |= RCC_CR_HSEON;  //HSEON
    while((RCC->CR & RCC_CR_HSERDY) == 0);  //HSE動作待ち
    RCC->PLLCFGR = 0x04402A06;
    RCC->CFGR = 0x000C9402;
    //RCC->CFGR = 0xB00C9402; //mco2  分周

    FLASH->ACR &= ~FLASH_ACR_LATENCY;  //FLASH読み込みの遅延時間設定
    FLASH->ACR |= FLASH_ACR_LATENCY_5WS;  //FLASH読み込みの遅延時間設定

    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY));  //PLL安定化待ち
}

void setup_168MHz_HSI(void)
{
    RCC->CR &= ~RCC_CR_PLLON;
    while(RCC->CR & RCC_CR_PLLRDY);	//PLL停止待ち

    RCC->CR |= RCC_CR_HSION;  //HSEON
    while((RCC->CR & RCC_CR_HSIRDY) == 0);  //HSE動作待ち
    RCC->PLLCFGR = 0x04002A08;
    RCC->CFGR = 0x000C9402;
    //RCC->CFGR = 0xB00C9402; //mco2  分周

    FLASH->ACR &= ~FLASH_ACR_LATENCY;  //FLASH読み込みの遅延時間設定
    FLASH->ACR |= FLASH_ACR_LATENCY_5WS;  //FLASH読み込みの遅延時間設定

    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY));  //PLL安定化待ち
}
//RTC考慮なし
//Ether考慮なし
void setup_PLLCLK_HSE(void)
{
    m_freqPLLIn = m_freqHSE;
    m_freqVCO = m_freqPLLIn / m_PLLM * m_PLLN;
    m_freqPLLOut = m_freqVCO / m_PLLP;
    //m_PLLCLK = m_freqVCO / m_PLLP;
    m_freqSYSCLK = m_freqPLLOut;
    m_freqUSB = m_freqVCO / m_PLLQ;

    //m_freqEther = m_freqSYSCLK;
    m_freqHCLK = m_freqSYSCLK / m_AHBPrescaler;
    m_freqCortexSystem = m_freqHCLK / 1;
    m_freqFCLK = m_freqHCLK;
    m_freqAPB1Peripheral = m_freqHCLK / m_APB1Prescaler;
    m_freqAPB1Timer = m_freqAPB1Peripheral * 2;
    m_freqAPB2Peripheral = m_freqHCLK / m_APB2Prescaler;
    m_freqAPB2Timer = m_freqAPB2Peripheral * 2;

    if(m_freqHSE <= 0 || m_freqHSE > 26) return;
    //if(m_freqUSB <= 0 || m_freqUSB > 48) return -1;
    if(m_freqPLLOut <= 0 || m_freqPLLOut > 168) return;
    if(m_freqVCO < 100 || m_freqVCO > 432) return;
    if(m_freqHSE / m_PLLM < 1 || m_freqHSE / m_PLLM > 2) return;     //VCO入力周波数
    if(m_freqHCLK > 168) return;
    if(m_freqAPB1Peripheral > 42) return;
    if(m_freqAPB2Peripheral > 84) return;

    disablePll();
    enableHse();

    //設定反映
    RCC->PLLCFGR =
        ((m_PLLQ << RCC_PLLCFGR_PLLQ_Pos) & RCC_PLLCFGR_PLLQ_Msk) |
        ((2*(m_PLLP+1) << RCC_PLLCFGR_PLLP_Pos) & RCC_PLLCFGR_PLLP_Msk) |
        ((m_PLLN << RCC_PLLCFGR_PLLN_Pos) & RCC_PLLCFGR_PLLN_Msk) |
        ((m_PLLM << RCC_PLLCFGR_PLLM_Pos) & RCC_PLLCFGR_PLLM_Msk) |
        RCC_PLLCFGR_PLLSRC_HSE;

    uint8_t ppre1 = (uint8_t)(pow(2, m_APB1Prescaler+1))+4;
    uint8_t ppre2 = (uint8_t)(pow(2, m_APB2Prescaler+1))+4;
    uint8_t hpre;
    if(m_AHBPrescaler < 64) hpre = (uint8_t)(pow(2, m_AHBPrescaler+1))+8;
    else hpre = (uint8_t)(pow(2, m_AHBPrescaler+2))+8;
    RCC->CFGR =
        ((ppre2 << RCC_CFGR_PPRE2_Pos) & RCC_CFGR_PPRE2_Msk) |
        ((ppre1 << RCC_CFGR_PPRE1_Pos) & RCC_CFGR_PPRE1_Msk) |
        ((hpre << RCC_CFGR_HPRE_Pos) & RCC_CFGR_HPRE_Msk) |
        RCC_CFGR_SW;

    setupFlashLatency();

    enablePll();
}

void enableHse(void)
{
    RCC->CR |= RCC_CR_HSEON;
    while((RCC->CR & RCC_CR_HSERDY) == 0);  //HSE安定化待ち
}

void disableHse(void)
{

    RCC->CR &= ~RCC_CR_HSEON;
    while((RCC->CR & RCC_CR_HSERDY) == 1);  //HSE停止待ち
}

void enablePll(void)
{
    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY));  //PLL安定化待ち
}

void disablePll(void)
{
    RCC->CR &= ~RCC_CR_PLLON;
    while(RCC->CR & RCC_CR_PLLRDY);	//PLL停止待ち
}

void setupFlashLatency(void)
{
    if(m_powerVoltage < 1.8 || m_powerVoltage > 3.6) return;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;  //FLASH読み込みの遅延時間設定
    
    if(m_powerVoltage >= 2.7 && m_powerVoltage <= 3.6)
    {
        //電圧範囲2.7V - 3.6V
        if(m_freqHCLK >= 0 && m_freqHCLK <= 30) goto latency_0ws;
        else if(m_freqHCLK <= 60) goto latency_1ws;
        else if(m_freqHCLK <= 90) goto latency_2ws;
        else if(m_freqHCLK <= 120) goto latency_3ws;
        else if(m_freqHCLK <= 150) goto latency_4ws;
        else if(m_freqHCLK <= 168) goto latency_5ws;
    }
    else if(m_powerVoltage >= 2.4 && m_powerVoltage <= 2.7)
    {
        //電圧範囲2.4V - 2.7V
        if(m_freqHCLK >= 0 && m_freqHCLK <= 24) goto latency_0ws;
        else if(m_freqHCLK <= 48) goto latency_1ws;
        else if(m_freqHCLK <= 72) goto latency_2ws;
        else if(m_freqHCLK <= 96) goto latency_3ws;
        else if(m_freqHCLK <= 120) goto latency_4ws;
        else if(m_freqHCLK <= 144) goto latency_5ws;
        else if(m_freqHCLK <= 168) goto latency_6ws;
    }
    else if(m_powerVoltage >= 2.1 && m_powerVoltage <= 2.4)
    {
        //電圧範囲2.1V - 2.4V
        if(m_freqHCLK >= 0 && m_freqHCLK <= 22) goto latency_0ws;
        else if(m_freqHCLK <= 44) goto latency_1ws;
        else if(m_freqHCLK <= 66) goto latency_2ws;
        else if(m_freqHCLK <= 88) goto latency_3ws;
        else if(m_freqHCLK <= 110) goto latency_4ws;
        else if(m_freqHCLK <= 132) goto latency_5ws;
        else if(m_freqHCLK <= 154) goto latency_6ws;
        else if(m_freqHCLK <= 168) goto latency_7ws;
    }
    else if(m_powerVoltage >= 1.8 && m_powerVoltage <= 2.1)
    {
        //電圧範囲1.8V - 2.1V
        if(m_freqHCLK >= 0 && m_freqHCLK <= 20) goto latency_0ws;
        else if(m_freqHCLK <= 40) goto latency_1ws;
        else if(m_freqHCLK <= 60) goto latency_2ws;
        else if(m_freqHCLK <= 80) goto latency_3ws;
        else if(m_freqHCLK <= 100) goto latency_4ws;
        else if(m_freqHCLK <= 120) goto latency_5ws;
        else if(m_freqHCLK <= 140) goto latency_6ws;
        else if(m_freqHCLK <= 168) goto latency_7ws;
    }

latency_0ws:
    FLASH->ACR |= FLASH_ACR_LATENCY_0WS;
    return;
latency_1ws:
    FLASH->ACR |= FLASH_ACR_LATENCY_1WS;
    return;
latency_2ws:
    FLASH->ACR |= FLASH_ACR_LATENCY_2WS;
    return;
latency_3ws:
    FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
    return;
latency_4ws:
    FLASH->ACR |= FLASH_ACR_LATENCY_4WS;
    return;
latency_5ws:
    FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
    return;
latency_6ws:
    FLASH->ACR |= FLASH_ACR_LATENCY_6WS;
    return;
latency_7ws:
    FLASH->ACR |= FLASH_ACR_LATENCY_7WS;
    return;
}

void setHSE(int freqHSE)
{
    if(freqHSE < 4 || freqHSE > 26) return;
    m_freqHSE = freqHSE;
}
void setLSE(int freqLSE)
{
    if(freqLSE < 0 || freqLSE > 1000) return;
    m_freqLSE = freqLSE;
}

void setPLLQ(int PLLQ)
{
    m_PLLQ = PLLQ;
}

void setPLLP(int PLLP)
{
    m_PLLP = PLLP;
}


void setPLLN(int PLLN)
{
    m_PLLN = PLLN;
}

void setPLLM(int PLLM)
{
    m_PLLM = PLLM;
}

void setAHBPrescaler(int AHBPrescaler)
{
    m_AHBPrescaler = AHBPrescaler;
}

void setAPB1Prescaler(int APB1Prescaler)
{
    m_APB1Prescaler = APB1Prescaler;
}

void setAPB2Prescaler(int APB2Prescaler)
{
    m_APB2Prescaler = APB2Prescaler;
}

void setPowerVoltage(float powerVoltage)
{
    m_powerVoltage = powerVoltage;
}

int getHSE(void){return m_freqHSE;}

int getAPB1TimerClock(void){return m_freqAPB1Timer;}

int getAPB2TimerClock(void){return m_freqAPB2Timer;}

}//namespace

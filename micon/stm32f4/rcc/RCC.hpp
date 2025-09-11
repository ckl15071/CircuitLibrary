#pragma once
#include "stm32f405xx.h"

namespace clock
{

void setup_72MHz(void);
void setup_144MHz(void);
void setup_168MHz_HSE(void);
void setup_168MHz_HSI(void);

void setup_PLLCLK_HSE(void);
void setup_PLLCLK_HSI(void);
void setup_HSE(void);
void setup_HSI(void);
void setupFlashLatency(void);

void setLSE(int freqLSE);   //[kHz]
void setHSE(int freqHSE);   //[MHz]
void setPLLQ(int PLLQ);     //分周比
void setPLLP(int PLLP);     //分周
void setPLLN(int PLLN);     //逓倍
void setPLLM(int PLLM);     //分周
void setAHBPrescaler(int AHBPrescaler);    //分周比
void setAPB1Prescaler(int APB1Prescaler);    //分周比
void setAPB2Prescaler(int APB2Prescaler);    //分周比

void setPowerVoltage(float powerVoltage);    //電源電圧設定[V]

//getter
int getHSE(void);
int getAPB1TimerClock(void);
int getAPB2TimerClock(void);

//int m_freqLSI;       //[kHz]
//float m_freqLSE;     //[kHz]
//int m_freqHSI;   //[MHz]
//int m_freqHSE;   //[MHz]
//
//int m_freqVCO;
//int m_freqPLLIn;
//int m_freqPLLOut;
//int m_freqSYSCLK;
//
//int m_PLLQ;
//int m_PLLP;
//int m_PLLN;
//int m_PLLM;
//int m_AHBPrescaler;
//int m_APB1Prescaler;
//int m_APB2Prescaler;
//
//int m_freqHCLK;
//int m_freqAPB1Peripheral;   //PCLK1
//int m_freqAPB1Timer;
//int m_freqAPB2Peripheral;   //PCLK2
//int m_freqAPB2Timer;
//int m_freqCortexSystem;
//int m_freqFCLK;
//int m_freqUSB;
//
//float m_powerVoltage;

//安定化まで要時間
void enableHse(void);
void disableHse(void);
void enablePll(void);
void disablePll(void);
}

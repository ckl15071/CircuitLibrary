#include "TIM.hpp"

extern void interrupt_1ms(void);
extern void interrupt_10ms(void);

void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);
void TIM1_BRK_TIM9_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);

void TIM6_DAC_IRQHandler(void)
{
    //interrupt_1ms();
    TIM6->SR = 0;
}

void TIM7_IRQHandler(void)
{
    //interrupt_10ms();
    TIM7->SR = 0;
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    interrupt_1ms();
    TIM9->SR = 0;
}

void TIM1_UP_TIM10_IRQHandler(void)
{
    interrupt_10ms();
    TIM10->SR = 0;
}

void TIM::setup(TIM_TypeDef* TIMx, uint16_t prescaler, uint32_t interruptTime)
{
    setup(TIMx, TimMode::TIMER);

    //更新割り込みリクエスト許可
    m_TIMx->DIER = TIM_DIER_UIE;

    //m_TIMx->PSC = prescaler - 1;
    //m_TIMx->ARR = (m_sourceFreq * interruptTime) / (prescaler * 1000) - 1;

    //100ms
    //m_TIMx->PSC = 8400-1;
    //m_TIMx->ARR = 1000-1;
    if(m_TIMx == TIM9)  //1ms割り込み
    {
        m_TIMx->PSC = 1680-1;
        m_TIMx->ARR = 100-1;
    }
    else if(m_TIMx == TIM10)    //10ms割り込み
    {
        m_TIMx->PSC = 1680-1;
        m_TIMx->ARR = 1000-1;
    }
    
    resetCount();
    //enableCount();
}

void TIM::enableCount(void)
{
    m_TIMx->CR1 |= TIM_CR1_CEN;
}

void TIM::setCount(uint16_t count)
{
    m_TIMx->CNT = count;
}

void TIM::resetCount(void)
{
    setCount(0);
}

void TIM::setup(TIM_TypeDef* TIMx, TimMode timMode)
{
    m_TIMx = TIMx;
    m_timMode = timMode;

    if(TIMx == TIM1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
        NVIC_EnableIRQ(TIM1_CC_IRQn);
    }
    if(TIMx == TIM2)
    {

    }
    if(TIMx == TIM3)
    {

    }
    if(TIMx == TIM4)
    {

    }
    if(TIMx == TIM5)
    {

    }
    if(TIMx == TIM6)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
        NVIC_EnableIRQ(TIM6_DAC_IRQn);
    }
    if(TIMx == TIM7)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
        NVIC_EnableIRQ(TIM7_IRQn);
    }
    if(TIMx == TIM8)
    {}
    if(TIMx == TIM9)
    {
        RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
        NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
    }
    if(TIMx == TIM10)
    {
        RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
        NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
    }
    if(TIMx == TIM11)
    {}
    if(TIMx == TIM12)
    {}
    if(TIMx == TIM13)
    {}
    if(TIMx == TIM14)
    {
    }
}

void TIM::setSourceFreq(int freq)
{
    m_sourceFreq = freq;
}
#pragma once
#include "stm32f405xx.h"
#include "GPIO.hpp"

#ifdef __cplusplus
extern "C"{
#endif
//extern void TIM1_IRQHandler(void);
//extern void TIM2_IRQHandler(void);
//extern void TIM3_IRQHandler(void);
//extern void TIM4_IRQHandler(void);
extern void TIM6_DAC_IRQHandler(void);
extern void TIM7_IRQHandler(void);
extern void TIM1_BRK_TIM9_IRQHandler(void);
extern void TIM1_UP_TIM10_IRQHandler(void);
#ifdef __cplusplus
}
#endif

class TIM
{
public:
    typedef enum
    {
        TIMER, PWMOUT, COMP_PWMOUT, ENCODER
    }TimMode;

    TIM(){};
    ~TIM(){};

    void enableClock(void);
    void disableClock(void);
    bool isEnable(void);
    void enableCount(void);
    void disableCount(void);
    void setCount(uint16_t count);
    uint16_t getCount(void) const;
    void resetCount(void);
    bool isCountEnable(void);

    //エンコーダ
    //void setupEncoder();
    void setup(TIM_TypeDef* TIMx, GPIO_TypeDef* gpioA, uint8_t pinA, GPIO_TypeDef* gpioB, uint8_t pinB, uint16_t period);
    //PWM出力
    void setupPwmOut();
    //タイマ
    void setup(TIM_TypeDef* TIMx, uint16_t prescaler, uint32_t interruptTime);

    void setSourceFreq(int freq);

    class Channel
    {
    public:
        Channel(){};
        ~Channel(){};
        Channel(GPIO_TypeDef* GPIOx, uint8_t pin, GPIO::PinMode pinMode);

        //ピンにPWMを出力
        void pwm();

    private:
        GPIO* m_gpio;
    };
    Channel* ch1;
    Channel* ch1n;
    Channel* ch2;
    Channel* ch2n;
    Channel* ch3;
    Channel* ch3n;
    Channel* ch4;
private:
    TIM_TypeDef* m_TIMx;
    TimMode m_timMode;

    int m_sourceFreq = 0;

    void setup(TIM_TypeDef* TIMx, TimMode timMode);
};

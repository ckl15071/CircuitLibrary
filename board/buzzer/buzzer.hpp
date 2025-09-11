#pragma once
#include "../peripheral/gpio_base.hpp"

//class Buzzer
//{
//public:
//    Buzzer(GpioBase* gpio, int inverse = 0);
//    void setup(GpioBase* gpio, int inverse = 0);
//    void beepOn(void);
//    void beepOff(void);
//
//private:
//    GpioBase* m_gpio;
//    int m_inverse;
//
//};

class Buzzer
{
public:
    Buzzer(){};
    Buzzer(GpioBase* gpio, int inverse = 0);
    void setup(GpioBase* gpio, int inverse = 0);
    void beepOn(void);
    void beepOff(void);

    void setBeepTime(int beepTime);
    void control(void);

private:
    GpioBase* m_gpio;
    int m_inverse;

    int m_beepTime;

};

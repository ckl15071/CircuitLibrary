#pragma once
#include "../peripheral/gpio_base.hpp"

class Led
{
public:
    Led(){};
    Led(GpioBase* gpio, int inverse = 0);
    void setup(GpioBase* gpio, int inverse = 0);
    void write(int val);
    void turnOn(void);
    void turnOff(void);
    void toggle(void);

private:
    GpioBase* m_gpio;
    int m_inverse;
};

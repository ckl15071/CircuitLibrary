#pragma once
#include "../peripheral/gpio_base.hpp"

class SignalIn
{
public:
    SignalIn(){};
    SignalIn(GpioBase* gpio, int inverse = 0);
    void setup(GpioBase* gpio, int inverse = 0);
    int read(void);

private:
    GpioBase* m_gpio;
    int m_inverse;

};

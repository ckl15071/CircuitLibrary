#pragma once
#include "../peripheral/gpio_base.hpp"

class SignalOut
{
public:
    SignalOut(){};
    SignalOut(GpioBase* gpio, int inverse = 0);
    void setup(GpioBase* gpio, int inverse = 0);
    void on(void);
    void off(void);

private:
    GpioBase* m_gpio;
    int m_inverse;
};

#pragma once
#include "../peripheral/gpio_base.hpp"

class Relay
{
public:
    Relay(){};
    Relay(GpioBase* gpio, int inverse = 0);
    void setup(GpioBase* gpio, int inverse = 0);
    void on(void);
    void off(void);
    void toggle(void);

private:
    GpioBase* m_gpio;
    int m_inverse;
};

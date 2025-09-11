#pragma once
#include "../peripheral/gpio.hpp"

class Shift
{
public:
    void setup(GpioBase* gpio, int inverse = 0);
    void on(void);
    void off(void);
    void toggle(void);

private:
    GpioBase* m_gpio;
    int m_inverse;

};

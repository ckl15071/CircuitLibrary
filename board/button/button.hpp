#pragma once
#include "../peripheral/gpio_base.hpp"

class Button
{
public:
    Button(){};
    Button(GpioBase* gpio, int inverse = 0);
    void setup(GpioBase* gpio, int inverse = 0);
    int read(void);
    bool isPushed(void);
    bool isReleased(void);

private:
    GpioBase* m_gpio;
    int m_inverse;
};

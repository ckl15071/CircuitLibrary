#pragma once
#include "../peripheral/gpio_base.hpp"

class Switch
{
public:
    Switch();
    Switch(GpioBase* gpio, int inverse = 0);
    void setup(GpioBase* gpio, int inverse = 0);
    bool isPushed(void);
    uint8_t read(void);

private:
    GpioBase* m_gpio;
    int m_inverse;
};

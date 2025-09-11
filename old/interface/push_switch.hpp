#pragma once
#include "../peripheral/gpio_base.hpp"

class PushSwitch
{
public:
    PushSwitch(){};
    PushSwitch(GpioBase* gpio, int inverse = 0);
    void setup(GpioBase* gpio, int inverse = 0);
    bool isPushed(void);

private:
    GpioBase* m_gpio;
    int m_inverse;

    uint8_t read(void);
};

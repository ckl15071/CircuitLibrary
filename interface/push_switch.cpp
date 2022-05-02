#include "push_switch.hpp"

PushSwitch::PushSwitch(GpioBase* gpio, int inverse)
{
    this->setup(gpio, inverse);
}

void PushSwitch::setup(GpioBase* gpio, int inverse)
{
    m_gpio = gpio;
    m_inverse = inverse;
}

uint8_t PushSwitch::read(void)
{
    return (m_gpio->read() + m_inverse) % 2;
}

bool PushSwitch::isPushed(void)
{
    uint8_t val = this->read();
    if(val == 1){return true;}
    else{return false;}
}

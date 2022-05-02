#include "switch.hpp"

Switch::Switch()
{

}

Switch::Switch(GpioBase* gpio, int inverse)
{
    this->setup(gpio, inverse);
}

void Switch::setup(GpioBase* gpio, int inverse)
{
    m_gpio = gpio;
    m_inverse = inverse;
}

uint8_t Switch::read(void)
{
    return (m_gpio->read() + m_inverse) % 2;
}

bool Switch::isPushed(void)
{
    uint8_t val = m_gpio->read();
    return (val + m_inverse) % 2;
}

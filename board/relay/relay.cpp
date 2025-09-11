#include "relay.hpp"

Relay::Relay(GpioBase* gpio, int inverse)
{
    this->setup(gpio, inverse);
}

void Relay::setup(GpioBase* gpio, int inverse)
{
    m_gpio = gpio;
    m_inverse = inverse;
}

void Relay::on(void)
{
    uint8_t val = (1 + m_inverse) % 2;
    m_gpio->write(val);
}

void Relay::off(void)
{
    uint8_t val = (0 + m_inverse) % 2;
    m_gpio->write(val);
}

void Relay::toggle(void)
{
    m_gpio->toggle();
}

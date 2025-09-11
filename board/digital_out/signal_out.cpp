#include "signal_out.hpp"

SignalOut::SignalOut(GpioBase* gpio, int inverse)
{
    this->setup(gpio, inverse);
}

void SignalOut::setup(GpioBase* gpio, int inverse)
{
    m_gpio = gpio;
    m_inverse = inverse;
}

void SignalOut::on(void)
{
    uint8_t val = (1 + m_inverse) % 2;
    m_gpio->write(val);
}

void SignalOut::off(void)
{
    uint8_t val = (0 + m_inverse) % 2;
    m_gpio->write(val);
}

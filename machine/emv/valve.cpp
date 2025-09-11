#include "valve.hpp"

Valve::Valve(GPIO* gpio, int sign = 1)
{
    setup(gpio, sign);
}

void Valve::setup(GPIO* gpio, int sign)
{
    m_gpio = gpio;
    m_sign = sign;
}

void Valve::on()
{
    if(m_sign == 1) m_gpio->write(1);
    else m_gpio->write(0);
}

void Valve::off()
{
    if(m_sign == 1) m_gpio->write(0);
    else m_gpio->write(1);
}

#include "shift.hpp"

void Shift::setup(GpioBase* gpio, int inverse)
{
    m_gpio = gpio;
    m_inverse = inverse;

    this->off();
}

void Shift::on(void)
{
    m_gpio->write((uint8_t)(0x1 + m_inverse) % 2);
}

void Shift::off(void)
{
    m_gpio->write((uint8_t)(0x0 + m_inverse) % 2);
}
void Shift::toggle(void)
{
    m_gpio->toggle();
}

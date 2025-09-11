#include "led.hpp"

Led::Led(GpioBase* gpio, int inverse)
{
    this->setup(gpio, inverse);
}

void Led::setup(GpioBase* gpio, int inverse)
{
    m_gpio = gpio;
    m_inverse = inverse;
}

void Led::write(int state)
{
    uint8_t val = (state + m_inverse) % 2;
    m_gpio->write(val);
}

void Led::turnOn(void)
{
    uint8_t val = (1 + m_inverse) % 2;
    m_gpio->write(val);
}

void Led::turnOff(void)
{
    uint8_t val = (0 + m_inverse) % 2;
    m_gpio->write(val);
}

void Led::toggle(void)
{
    m_gpio->toggle();
}

#include "button.hpp"

Button::Button(GpioBase* gpio, int inverse)
{
    this->setup(gpio, inverse);
}

void Button::setup(GpioBase* gpio, int inverse)
{
    m_gpio = gpio;
    m_inverse = inverse;
}

int Button::read(void)
{
    int val =  m_gpio->read();
    if((val + m_inverse) % 2 == 1){return 1;}
    else{return 0;}
}

bool Button::isPushed(void)
{
    uint8_t val = m_gpio->read();
    if((val + m_inverse) % 2 == 1)
    {
        return true;
    }
    return false;
}

bool Button::isReleased(void)
{
    return !(this->isPushed());
}

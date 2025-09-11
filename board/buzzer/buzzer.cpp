#include "buzzer.hpp"

Buzzer::Buzzer(GpioBase* gpio, int inverse)
{
    this->setup(gpio, inverse);
}

void Buzzer::setup(GpioBase* gpio, int inverse)
{
    m_gpio = gpio;
    m_inverse = inverse;
}

void Buzzer::beepOn(void)
{
    uint8_t val = (1 + m_inverse) % 2;
    m_gpio->write(val);
}

void Buzzer::beepOff(void)
{
    uint8_t val = (0 + m_inverse) % 2;
    m_gpio->write(val);
}

void Buzzer::setBeepTime(int beepTime)
{
    m_beepTime = beepTime;
}

void Buzzer::control(void)
{
    if(m_beepTime > 0)
    {
        m_beepTime--;
        this->beepOn();
    }
    else
    {
        this->beepOff();
    }
}

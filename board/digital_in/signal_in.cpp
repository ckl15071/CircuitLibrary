#include "signal_in.hpp"

SignalIn::SignalIn(GpioBase* gpio, int inverse)
{
    this->setup(gpio, inverse);
}

void SignalIn::setup(GpioBase* gpio, int inverse)
{
    m_gpio = gpio;
    m_inverse = inverse;
}

int SignalIn::read(void)
{
    int val =  m_gpio->read();
    if((val + m_inverse) % 2 == 1){return 1;}
    else{return 0;}
}

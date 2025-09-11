#include "rotary_dipsw.hpp"

void RotaryDipSw::setup(GPIO* gpio0, GPIO* gpio1, GPIO* gpio2, GPIO* gpio3)
{
    m_gpio0 = gpio0;
    m_gpio1 = gpio1;
    m_gpio2 = gpio2;
    m_gpio3 = gpio3;
}

uint8_t RotaryDipSw::getVal(void)
{
    //return m_gpio0
}
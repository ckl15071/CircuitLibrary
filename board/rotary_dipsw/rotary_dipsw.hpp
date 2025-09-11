#pragma once
#include "peripheral/GPIO.hpp"

class RotaryDipSw
{
public:
    void setup(GPIO* gpio0, GPIO* gpio1, GPIO* gpio2, GPIO* gpio3);
    uint8_t getVal(void);

private:
    GPIO* m_gpio0;
    GPIO* m_gpio1;
    GPIO* m_gpio2;
    GPIO* m_gpio3;

};

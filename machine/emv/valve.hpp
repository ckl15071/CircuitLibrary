#pragma once
#include "peripheral/GPIO.hpp"

class Valve
{
public:
    Valve(){};
    Valve(GPIO* gpio, int sign = 1);
    Valve(){ m_gpio == NULL; };

    void setup(GPIO* gpio, int sign = 1);

    void on(void);
    void off(void);

private:
    GPIO* m_gpio;
    int m_sign;

};

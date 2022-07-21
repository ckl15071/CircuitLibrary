#include "gpio.hpp"
#include <Arduino.h>

void Gpio::setup(int pinNum, enum PinMode pin_mode)
{
    m_pinNum = pinNum;
    m_pinMode = pin_mode;

    //初期状態LOW
    this->write(0);

    if(pin_mode == MODE_INPUT)
    {
        pinMode(pinNum, INPUT);
    }
    else if(pin_mode == MODE_OUTPUT)
    {
        pinMode(pinNum, OUTPUT);
    }
}

uint8_t Gpio::read(void)
{
    return digitalRead(m_pinNum);
}

void Gpio::write(uint8_t value)
{
    digitalWrite(m_pinNum, value);
}

void Gpio::toggle(void)
{
    int val = digitalRead(m_pinNum);
    if(val == HIGH)
    {
        digitalWrite(m_pinNum, LOW);
    }
    else
    {
        digitalWrite(m_pinNum, HIGH);
    }
}

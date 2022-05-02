#pragma once
#include <stdint.h>
#include "gpio_base.hpp"

class Gpio : public GpioBase
{
public:
    enum PinMode{MODE_INPUT, MODE_OUTPUT};
    void setup(int pinNum, enum PinMode pinMode);

    uint8_t read(void);
    void write(uint8_t value);
    void toggle(void);

private:
    uint8_t m_pinNum;
    enum PinMode m_pinMode;
};

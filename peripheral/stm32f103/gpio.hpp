#pragma once
#include "../gpio_base.hpp"

class Gpio : public GpioBase
{
public:
    Gpio(){};
    //Gpio();
    void setup(void);

    uint8_t read(void);
    void write(uint8_t value);
    void toggle(void);

private:
};

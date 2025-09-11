#pragma once
#include <stdint.h>

class GpioBase
{
public:
    virtual uint8_t read(void){return 0;};
    virtual void write(uint8_t value){};
    virtual void toggle(void){};
};

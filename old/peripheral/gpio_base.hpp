#pragma once
#include <stdint.h>

class GpioBase
{
public:
    virtual uint8_t read(void);
    virtual void write(uint8_t value);
    virtual void toggle(void);
};

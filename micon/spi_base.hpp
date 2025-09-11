#pragma once
#include <stdint.h>

class SpiBase
{
public:
    virtual uint8_t transfer(uint8_t data){return 0;};
};

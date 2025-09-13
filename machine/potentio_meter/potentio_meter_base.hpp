#pragma once
#include <stdint.h>

class PotentioMeterBase
{
public:
    virtual void update(void) = 0;
    uint16_t getAngleRad(void);
    uint16_t getAngleDeg(void);

private:

};

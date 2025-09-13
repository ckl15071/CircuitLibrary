#pragma once
#include "../potentio_meter_base.hpp"

class CanPotentioMeter : public PotentioMeterBase
{
public:
    void update(void);

private:
    uint16_t m_angle;

};

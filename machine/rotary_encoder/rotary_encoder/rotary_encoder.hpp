#pragma once
#include "../encoder_base.hpp"
#include "../../../board/encoder/encoder.hpp"

class RotaryEncoder
{
public:
    RotaryEncoder(Encoder* encoder);

    void setup(Encoder* encoder);
    void update(void);

private:
    Encoder* m_encoder;
    uint16_t m_cntOld;

    uint16_t m_angle;
    uint16_t m_angVel;


};

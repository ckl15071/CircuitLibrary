#include "rotary_encoder.hpp"

RotaryEncoder::RotaryEncoder(Encoder* encoder)
{
    this->setup(encoder);
}

void RotaryEncoder::setup(Encoder* encoder)
{
    m_encoder = encoder;
}

void RotaryEncoder::update(void)
{
    uint16_t encNow = m_encoder->read();

    //角度計算
    m_angle = 0;

    //角速度計算
    m_angVel = 0;

}

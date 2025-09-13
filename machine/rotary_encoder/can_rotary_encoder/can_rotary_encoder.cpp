#include "can_rotary_encoder.hpp"
#include "../rotary_encoder_base.hpp"
#include <stdint.h>

CanRotaryEncoder::CanRotaryEncoder()
{

}

//通信時のLSBで受取→内部で変換
void CanRotaryEncoder::setVal(uint16_t raw_angle, uint16_t raw_angVel)
{
    //通信生値保存
    m_raw_angle = raw_angle;
    m_raw_angVel = raw_angVel;

    //解像度変換
    m_angle = m_param * raw_angle;
    m_angvel  = m_param * raw_angVel;
}


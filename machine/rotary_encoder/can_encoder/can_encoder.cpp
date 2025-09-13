#include "can_encoder.hpp"
#include "../encoder_base/encoder_base.hpp"
#include <stdint.h>

//通信時のLSBで受取→内部で変換
void CanEncoder::setVal(uint16_t raw_angle, uint16_t raw_angVel)
{
    //通信生値保存
    m_raw_angle = raw_angle;
    m_raw_angVel = raw_angVel;

    //解像度変換
    m_angle = m_param * raw_angle;
    m_angvel  = m_param * raw_angVel;
}


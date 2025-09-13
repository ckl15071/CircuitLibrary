#pragma once
#include <stdint.h>

#include "../encoder_base.hpp"

//CANから角度、角速度を取得
class CanEncoder : public EncoderBase
{
public:
    //角度取得[rad]
    uint16_t getAngle(void);

    //角速度取得[rps]
    uint16_t getAngVel(void);

    //受信した通信生値を保存
    void setVal(uint16_t raw_angle, uint16_t raw_angVel);

private:
    uint16_t m_raw_angle;
    uint16_t m_raw_angVel;
    uint16_t m_angle;
    uint16_t m_angvel;

    uint64_t m_param;

};

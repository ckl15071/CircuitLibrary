#include "encoder_base.hpp"
#include <stdint.h>

class EncoderBase
{
public:
    //角度取得
    uint16_t getActAngle();

    //角速度取得
    uint16_t getActAngVel();

private:

};

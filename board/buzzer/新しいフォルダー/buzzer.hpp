#pragma once
#include "peripheral/GPIO.hpp"
#include <stdint.h>

class Buzzer
{
public:
    void setup(GPIO* gpio);

    //時間指定
    void beep(uint16_t time);

    //時間、周波数指定
    void beep(uint16_t time, uint8_t hz);
    //void write(int val);

private:
    GPIO* m_gpio;   //器のみ。delete禁止
};

#pragma once
#include "controller.hpp"
#include "peripheral/USART.hpp"

class Sixaxis : public ControllerBase
{
public:
    struct State
    {
        uint8_t circle;
        uint8_t cross;
        uint8_t triangle;
        uint8_t square;
        uint8_t start;
        uint8_t select;
        uint8_t l1;
        uint8_t l2;
        uint8_t l3;
        uint8_t r1;
        uint8_t r2;
        uint8_t r3;
    };
    //設定
    void setup(USART* usart);

    //受信、m_stateの更新
    void calcPacket(void);

    //ボタンの読み取り
    uint8_t button(enum ButtonType button);



private:
    State m_state;

};

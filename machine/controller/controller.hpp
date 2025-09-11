#pragma once
#include <stdint.h>

class Controller
{
public:
    enum ButtonType
    {
        CIRCLE = 1,
        CROSS,
        SQUARE,
        TRIANGLE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        START,
        L1,
        L2,
        L3,
        R1,
        R2,
        R3,
    };
    uint8_t button(enum ButtonType button);
    void calcPacket(void);

private:

};


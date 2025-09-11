#pragma once
#include <stdint.h>
#include "../peripheral/usart_base.hpp"

class Serial
{
public:
    void setup(UsartBase* usart, uint32_t baudrate);

    int read(int size);
    int write(int size);
    int printf(const char format, ...);

private:
    UsartBase* m_usart;

};

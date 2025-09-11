#pragma once
#include <stdint.h>
#include "../peripheral/usart_base.hpp"
#include "byte_queue.hpp"

class SerialQueue
{
public:
    SerialQueue(UsartBase* usart);
    void setup(UsartBase* usart);

    int putchar(uint8_t c);
    int getchar(void);
    int write(const uint8_t* data, int size);
    int read(uint8_t* data, int size);
    int printf(const char* format, ...);

    void clear(void);
    void start(void);
    ByteQueue tx;
    ByteQueue rx;

private:
    UsartBase* m_usart;

};

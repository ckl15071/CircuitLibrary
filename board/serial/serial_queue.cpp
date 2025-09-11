#include "serial_queue.hpp"
#include <stdarg.h>
#include <stdio.h>

#include "iodefine.h"

SerialQueue::SerialQueue(UsartBase* usart)
{
    this->setup(usart);
}

void SerialQueue::setup(UsartBase* usart)
{
    m_usart = usart;

    this->clear();
}

int SerialQueue::putchar(uint8_t c)
{
    if(!(tx.enqueue(c))){return EOF;}
    return (int)c;
}

int SerialQueue::getchar(void)
{
    uint8_t c;
    if(!(rx.dequeue(&c))){return EOF;}
    return (int)c;
}

int SerialQueue::write(const uint8_t* data, int size)
{
    const uint8_t* p = data;
    int cnt = 0;

    if(p == NULL){return 0;}
    while(size > 0)
    {
        if(!(tx.enqueue(*(p++)))){break;}
        cnt++;
        size--;
    }
    return cnt;
}

int SerialQueue::read(uint8_t* data, int size)
{
    uint8_t* p = data;
    int cnt = 0;

    if(p == NULL){return 0;}
    while(size > 0)
    {
        if(!(rx.dequeue(p++))){break;}
        cnt++;
        size--;
    }
    return cnt;
}

int SerialQueue::printf(const char* format, ...)
{
    char buffer[128];
    va_list ap;
    int len;
    va_start(ap, format);
    len = vsprintf(buffer, format, ap);
    va_end(ap);
    return write((uint8_t*)buffer, len);
}

void SerialQueue::clear(void)
{
    tx.clear();
    rx.clear();
}

void SerialQueue::start(void)
{
    //割り込み許可
    //IEN(SCI0, RXI0) = 1;
    //IEN(SCI1, RXI1) = 1;
    //IEN(SCI2, RXI2) = 1;
    //IEN(SCI3, RXI3) = 1;
    //IEN(SCI4, RXI4) = 1;
    //IEN(SCI5, RXI5) = 1;
    //IEN(SCI6, RXI6) = 1;
}

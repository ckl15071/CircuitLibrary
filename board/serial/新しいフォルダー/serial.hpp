#pragma once

class Serial
{
public:
    int putchar(uint8_t c);
    int getchar(void);
    int write(const uint8_t* data, int size);
    int read(uint8_t* data, int size);
    int printf(const char* format, ...);

private:
    USART* m_usart;

    Queue m_txQueue;
    Queue m_rxQueue;

    void clear(void);
};

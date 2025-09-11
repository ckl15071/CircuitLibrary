#pragma once
#include <stdint.h>

class ByteQueue
{
public:
    ByteQueue();
    bool enqueue(uint8_t data);
    bool dequeue(uint8_t* data);
    int getStoredSize(void);
    bool isEmpty(void);
    bool isFull(void);
    void clear(void);
    bool peek(uint8_t* data);
    bool isInterruptUnlocked(void);
    void lockInterrupt(void);
    void unlockInterrupt(void);

private:
    static const int m_qSize = 9;
    static const int m_qPointerMask = (1 << m_qSize) - 1;
    uint8_t m_qData[1 << m_qSize];
    int m_tail;
    int m_head;
    int m_storedSize;
};

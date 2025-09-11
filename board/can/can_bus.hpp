#pragma once
#include <stdint.h>
#include "../peripheral/can_base.hpp"

typedef struct
{
    uint16_t id;
    uint8_t dlc;
    uint8_t data[8];
}CanData;

class CanQueue
{
public:
    CanQueue();
    bool enqueue(CanData data);
    bool dequeue(CanData* data);
    int getStoredSize(void);
    bool isEmpty(void);
    bool isFull(void);
    void clear(void);
    bool peek(CanData* data);
    bool isInterruptUnlocked(void);
    void lockInterrupt(void);
    void unlockInterrupt(void);

private:
    static const int m_qSize = 9;
    static const int m_qPointerMask = (1 << m_qSize) - 1;

    CanData m_qData[1 << m_qSize];
    int m_tail;
    int m_head;
    int m_storedSize;
};

class CanBus
{
public:
    CanBus();

    int write(const CanData* data, int size);
    int read(CanData* data, int size);

    void clear(void);
    void clearTx(void);
    void clearRx(void);

    CanQueue tx;
    CanQueue rx;

private:
};

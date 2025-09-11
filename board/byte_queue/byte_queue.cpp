#include "byte_queue.hpp"
#include <machine.h>

#define IS_INTERRUPT_UNLOCKED() (get_psw()&(1<<16) ? 1 : 0)    //割り込みが許可されていたら1を返す。キューの排他制御に使用。
#define LOCK_INTERRUPT() clrpsw_i()     //割り込み禁止
#define UNLOCK_INTERRUPT() setpsw_i()   //割り込み許可

ByteQueue::ByteQueue()
{
    this->clear();
}

bool ByteQueue::isInterruptUnlocked(void)
{
    if(IS_INTERRUPT_UNLOCKED()){return true;}
    return false;
}

inline void ByteQueue::lockInterrupt(void)
{
    LOCK_INTERRUPT();
}

inline void ByteQueue::unlockInterrupt(void)
{
    UNLOCK_INTERRUPT();
}

bool ByteQueue::enqueue(uint8_t data)
{
    bool intLock = this->isInterruptUnlocked();
    int pNext;

    if(intLock){this->lockInterrupt();}
    pNext = (m_tail+1)&m_qPointerMask;
    if(pNext == m_head)
    {
        //一杯
        if(intLock){this->unlockInterrupt();}
        return false;
    }
    m_qData[m_tail] = data;
    m_tail = pNext;
    m_storedSize++;
    if(intLock){this->unlockInterrupt();}
    return true;
}

bool ByteQueue::dequeue(uint8_t* data)
{
    bool intLock = this->isInterruptUnlocked();

    if(intLock){this->lockInterrupt();}
    if(m_head == m_tail)
    {
        //空
        if(intLock){this->unlockInterrupt();}
        return false;
    }
    *data = m_qData[m_head];
    m_head = (m_head+1)&m_qPointerMask;
    m_storedSize--;
    if(intLock){this->unlockInterrupt();}
    return true;
}

int ByteQueue::getStoredSize(void)
{
    return m_storedSize;
}

bool ByteQueue::isEmpty(void)
{
    if(m_storedSize == 0){return true;}
    return false;
}

bool ByteQueue::isFull(void)
{
    if(m_storedSize == m_qPointerMask){return true;}
    return false;
}

void ByteQueue::clear(void)
{
    bool intLock = this->isInterruptUnlocked();

    if(intLock){this->lockInterrupt();}
    m_tail = 0;
    m_head = 0;
    m_storedSize = 0;
    if(intLock){this->unlockInterrupt();}
}

bool ByteQueue::peek(uint8_t* data)
{
    if(m_storedSize != 0)
    {
        *data = m_qData[m_head];
        return true;
    }
    return false;
}

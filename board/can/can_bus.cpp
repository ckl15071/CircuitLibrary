#include "can_bus.hpp"
#include <stdio.h>
#include <machine.h>

#define IS_INTERRUPT_UNLOCKED() (get_psw()&(1<<16) ? 1 : 0)    //割り込みが許可されていたら1を返す。キューの排他制御に使用。
#define LOCK_INTERRUPT() clrpsw_i()     //割り込み禁止
#define UNLOCK_INTERRUPT() setpsw_i()   //割り込み許可

CanQueue::CanQueue()
{
    this->clear();
}

bool CanQueue::isInterruptUnlocked(void)
{
    if(IS_INTERRUPT_UNLOCKED()){return true;}
    return false;
}

void CanQueue::lockInterrupt(void)
{
    LOCK_INTERRUPT();
}

void CanQueue::unlockInterrupt(void)
{
    UNLOCK_INTERRUPT();
}

bool CanQueue::enqueue(CanData data)
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

bool CanQueue::dequeue(CanData* data)
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

int CanQueue::getStoredSize(void)
{
    return m_storedSize;
}

bool CanQueue::isEmpty(void)
{
    if(m_storedSize == 0){return true;}
    return false;
}

bool CanQueue::isFull(void)
{
    if(m_storedSize == m_qPointerMask){return true;}
    return false;
}

void CanQueue::clear(void)
{
    bool intLock = this->isInterruptUnlocked();

    if(intLock){this->lockInterrupt();}
    m_tail = 0;
    m_head = 0;
    m_storedSize = 0;
    if(intLock){this->unlockInterrupt();}
}

bool CanQueue::peek(CanData* data)
{
    if(m_storedSize != 0)
    {
        *data = m_qData[m_head];
        return true;
    }
    return false;
}

CanBus::CanBus()
{
    this->clear();
}

int CanBus::write(const CanData* data, int size)
{
    const CanData* p = data;
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

int CanBus::read(CanData* data, int size)
{
    CanData* p = data;
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

void CanBus::clear(void)
{
    this->clearTx();
    this->clearRx();
}

void CanBus::clearTx(void)
{
    tx.clear();
}

void CanBus::clearRx(void)
{
    rx.clear();
}

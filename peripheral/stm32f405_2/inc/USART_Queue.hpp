/*
 * USART_Queue.hpp
 *
 *  Created on: 2019/08/01
 *      Author: Shibata
 */

#ifndef USART_QUEUE_HPP_
#define USART_QUEUE_HPP_

#include <stdint.h>

class ByteQueue{
private:
    static const int qsize = 9;    //キューサイズ（2^qsize-1 bytes）
    static const int qpointer_mask = (1<<qsize) - 1;
    uint8_t qdata[1<<qsize];
    int tail;
    int front;
    int storedsize;
    inline bool isInterruptUnlocked(void);
    inline void LockInterrupt(void);
    inline void UnlockInterrupt(void);

public:
    ByteQueue();
    bool enqueue(uint8_t data);
    bool dequeue(uint8_t *data);
    int getStoredSize(void);
    bool isEmpty(void);
    bool isFull(void);
    void clear(void);
    bool peek(uint8_t *data);
};;

class SerialPort{
private:
public:
    ByteQueue tx;
    ByteQueue rx;
    void clear(void);
    int putchar(uint8_t c);
    int getchar(void);
    int write(const uint8_t *data, int size);
    int read(uint8_t *data, int size);
    int printf(const char *format, ...);
};

#endif /* USART_QUEUE_HPP_ */

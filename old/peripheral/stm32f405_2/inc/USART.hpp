/*
 * USART.hpp
 *
 *  Created on: 2019/05/01
 *      Author: Shibata
 */

#ifndef USART_HPP_
#define USART_HPP_

#include <stdint.h>
#include "stm32f446xx.h"
#include "GPIO.hpp"

class USART{
public:
    void setup(USART_TypeDef *usart, GPIO_TypeDef *usart_tx, uint8_t tx_pin, GPIO_TypeDef *usart_rx, uint8_t rx_pin, uint32_t baudrate);
    void clockEnable(void);
    void setAlternate(void);

    void enableRxInterrupt(void);
    void disableRxInterrupt(void);
    int isEnableRxInterrupt(void);

    //void clear(void);
    int putchar(uint8_t c);
    int getchar(void);
    int write(const uint8_t *data, int size);
    int read(uint8_t *data, int size);
    int printf(const char *format, ...);
private:
    USART_TypeDef *USARTx;
    GPIO *tx;
    GPIO *rx;
};

//USART3->BRR = 0x00000182; //180MHz
//USART3->BRR = 0x00000165; //168MHz
//USART3->BRR = 0x0000009C; //72MHz
//USART3->BRR = 0x00000139; //144MHz


#endif /* USART_HPP_ */

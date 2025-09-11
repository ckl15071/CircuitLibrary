/*
 * USART.cpp
 *
 *  Created on: 2019/05/02
 *      Author: Shibata
 */

#include "USART.hpp"
#include <stdio.h>
#include <stdarg.h>
#include "CatchRobo2019.hpp"

int USART::putchar(uint8_t c){
    while((USART1->SR & USART_SR_TC) == 0);
    USART1->DR = c;
    while((USART1->SR & USART_SR_TXE) == 0);

    return (int)c;
}

int USART::getchar(void){
    uint8_t c;
    c = USART1->DR;

	return (int)c;

}

int USART::write(const uint8_t *data, int size){
    const uint8_t *p = data;
    int cnt = 0;

    if(p == NULL) return 0;
    while(size>0){
        putchar(*(p++));
        size--;
        cnt++;
    }

    return cnt;
}

int USART::read(uint8_t *data, int size){
    int cnt=0;
    while(size > 0){
        getchar();
        size--;
        cnt++;
    }

    return cnt;
}
int USART::printf(const char *format, ...){
    char buffer[128];
    va_list ap;
    int len;
    va_start(ap, format);
    len = vsprintf(buffer, format, ap);
    va_end(ap);
    return write((uint8_t*)buffer, len);
}

void USART::clockEnable(void){

    if(USARTx == USART1) RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    if(USARTx == USART2) RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    //if(USARTx == USART3) RCC->APB2ENR |= RCC_APB2ENR_USART3EN;
    if(USARTx == UART4) RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
}

void USART::setAlternate(void){
    if(tx == NULL || rx == NULL) return;

    //USART1 TX
    if(USARTx == USART1 || USARTx == USART2 || USARTx == USART3){
        tx->setAlternate(AF7);
        rx->setAlternate(AF7);
    }

    if(USARTx == UART4 || USARTx == UART5){
        tx->setAlternate(AF8);
        rx->setAlternate(AF8);
    }
}

void USART::setup(USART_TypeDef *usart, GPIO_TypeDef *usart_tx, uint8_t tx_pin, GPIO_TypeDef *usart_rx, uint8_t rx_pin, uint32_t baudrate){
    this->USARTx = usart;
    tx = new GPIO(usart_tx, tx_pin, GPIO::ALTERNATE);
    rx = new GPIO(usart_rx, rx_pin, GPIO::ALTERNATE);

    clockEnable();
    setAlternate();

    if(baudrate == 115200){
        if(USARTx == USART1 || USARTx == USART6){
            USARTx->BRR = 0x00000271;   //115200bps
        }else{
            USARTx->BRR = 0x00000139;    //115200bps
        }
    }

    USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);
    USARTx->CR1 |= USART_CR1_UE;
}

void USART::enableRxInterrupt(void){
    if(USARTx == USART1) USART1->CR1 |= USART_CR1_RXNEIE;
    //if(USARTx == USART1) USART1->CR1 |= USART_CR1_RXNEIE;
    //if(USARTx == USART1) USART1->CR1 |= USART_CR1_RXNEIE;
    //if(USARTx == USART1) USART1->CR1 |= USART_CR1_RXNEIE;

    //switch(usart_num){
    //    case 1:
    //        USART1->CR1 |= USART_CR1_RXNEIE;
    //        break;
    //    case 2:
    //        USART2->CR1 |= USART_CR1_RXNEIE;
    //        break;
    //    case 3:
    //        USART3->CR1 |= USART_CR1_RXNEIE;
    //        break;
    //    case 4:
    //        UART4->CR1 |= USART_CR1_RXNEIE;
    //        break;
    //    default:
    //        //error
    //        break;
    //}
}
void USART::disableRxInterrupt(void){
    if(USARTx == USART1) USART1->CR1 &= ~(USART_CR1_RXNEIE);
    //if(USARTx == USART1) USART1->CR1 &= ~(USART_CR1_RXNEIE);
    //if(USARTx == USART1) USART1->CR1 &= ~(USART_CR1_RXNEIE);
    //if(USARTx == USART1) USART1->CR1 &= ~(USART_CR1_RXNEIE);

    //switch(usart_num){
    //    case 1:
    //        USART1->CR1 &= ~(USART_CR1_RXNEIE);
    //        break;
    //    case 2:
    //        USART2->CR1 &= ~(USART_CR1_RXNEIE);
    //        break;
    //    case 3:
    //        USART3->CR1 &= ~(USART_CR1_RXNEIE);
    //        break;
    //    case 4:
    //        UART4->CR1 &= ~(USART_CR1_RXNEIE);
    //        break;
    //    default:
    //        //error
    //        break;
    //}
}
//int USART::isEnableRxInterrupt(void){
//
//}

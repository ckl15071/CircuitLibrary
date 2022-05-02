/*
 * GPIO.cpp
 *
 *  Created on: Dec 3, 2019
 *      Author: Shibata
 */

#include "GPIO.hpp"

GPIO::GPIO(GPIO_TypeDef* gpio, uint8_t pin, PinMode pinMode){
    setup(gpio, pin, pinMode);
}

void GPIO::setup(GPIO_TypeDef* gpio, uint8_t pin, PinMode pinMode){
    if(     gpio==GPIOA || gpio==GPIOB || gpio==GPIOC || gpio==GPIOD ||
            gpio==GPIOE || gpio==GPIOF || gpio==GPIOG || gpio==GPIOH){
        if(pin>0 || pin>15) return;
    }else if(gpio==GPIOI){
        if(pin>0 || pin>11) return;
    }else{
        return;
    }

    this->GPIOx = gpio;
    this->pin = pin;

    //clock enable
    if((GPIOx == GPIOA) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOAEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    if((GPIOx == GPIOB) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOBEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    if((GPIOx == GPIOC) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOCEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    if((GPIOx == GPIOD) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIODEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    if((GPIOx == GPIOE) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOEEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    if((GPIOx == GPIOF) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOFEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    if((GPIOx == GPIOG) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOGEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    if((GPIOx == GPIOH) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOHEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    if((GPIOx == GPIOI) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOIEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;

    //pin mode configuration

    switch(pinMode){
        case ANALOG:
            break;
        default:
            break;
    }
}

void GPIO::setAlternate(uint8_t alternate){

}

uint8_t GPIO::read(void){

}

void GPIO::write(uint8_t value){

}

void GPIO::toggle(void){
    if(read()) write(0);
    else write(1);
}

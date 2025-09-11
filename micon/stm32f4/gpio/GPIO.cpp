#include "GPIO.hpp"

GPIO::GPIO(GPIO_TypeDef* GPIOx, uint8_t pin, PinMode pinMode)
{
    setup(GPIOx, pin, pinMode);
}

GPIO::GPIO(GPIO_TypeDef* GPIOx, uint8_t pin, PinMode pinMode, OutputSpeed outputSpeed)
{
    setup(GPIOx, pin, pinMode, outputSpeed);
}

void GPIO::setup(GPIO_TypeDef* GPIOx, uint8_t pin, PinMode pinMode)
{
    if(GPIOx==GPIOA || GPIOx==GPIOB || GPIOx==GPIOC || GPIOx==GPIOD ||
       GPIOx==GPIOE || GPIOx==GPIOF || GPIOx==GPIOG || GPIOx==GPIOH)
    {
        if(pin<0 || pin>15) return;
    }
    else if(GPIOx==GPIOI){
        if(pin<0 || pin>11) return;
    }
    else
    {
        return;
    }

    m_GPIOx = GPIOx;
    m_pin = pin;

    //clock enable
    if((m_GPIOx == GPIOA) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOAEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    if((m_GPIOx == GPIOB) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOBEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    if((m_GPIOx == GPIOC) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOCEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    if((m_GPIOx == GPIOD) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIODEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    if((m_GPIOx == GPIOE) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOEEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    if((m_GPIOx == GPIOF) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOFEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    if((m_GPIOx == GPIOG) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOGEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    if((m_GPIOx == GPIOH) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOHEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    if((m_GPIOx == GPIOI) && (!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOIEN))) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;

    //pin mode configuration
    m_GPIOx->MODER &= ~(3 << (m_pin*2));
    m_GPIOx->MODER |= ((pinMode >> 5) & 0x03) << (m_pin*2);
    m_GPIOx->OTYPER &= ~(1 << m_pin);
    m_GPIOx->OTYPER |= ((pinMode >> 4) & 0x01) << m_pin;
    m_GPIOx->PUPDR &= ~(3 << (m_pin*2));
    m_GPIOx->PUPDR |= (pinMode & 0x03) << (m_pin*2);
}

//出力
void GPIO::setup(GPIO_TypeDef* gpio, uint8_t pin, PinMode pinMode, OutputSpeed outputSpeed)
{
    setup(gpio, pin, pinMode);
    m_GPIOx->OSPEEDR &= ~(3 << (m_pin*2));
    m_GPIOx->OSPEEDR |= ((pinMode >> 2) & 0x03) << (m_pin*2);
}

void GPIO::setAlternate(uint8_t alternate)
{

}

uint8_t GPIO::read(void)
{
    return (uint8_t)((m_GPIOx->IDR >> m_pin) & 0x01);
}

void GPIO::write(uint8_t value)
{
    if(value)   m_GPIOx->ODR |=  (0x1 << m_pin);
    else        m_GPIOx->ODR &= ~(0x1 << m_pin);
}

void GPIO::toggle(void)
{
    if(read()) write(0);
    else write(1);
}

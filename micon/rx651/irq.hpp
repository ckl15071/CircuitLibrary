#pragma once
#include <stdint.h>
#include "port.hpp"

class Irq
{
public:
    Irq(uint8_t irq, st_port0* port, uint8_t pin, uint8_t irqcr, uint8_t priority);
    void setup(uint8_t irq, st_port0* port, uint8_t pin, uint8_t irqcr, uint8_t priority);

private:
    uint8_t m_irq;

    uint8_t getIer(uint8_t irq);
    uint8_t getIen(uint8_t irq);
};

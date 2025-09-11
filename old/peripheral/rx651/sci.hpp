#pragma once
#include "../usart_base.hpp"
#include "iodefine.h"
#include "port.hpp"

#define SCI000          ((st_sci0*)0x8A000)
#define SCI001          ((st_sci0*)0x8A020)
#define SCI002          ((st_sci0*)0x8A040)
#define SCI003          ((st_sci0*)0x8A060)
#define SCI004          ((st_sci0*)0x8A080)
#define SCI005          ((st_sci0*)0x8A0A0)
#define SCI006          ((st_sci0*)0x8A0C0)
#define SCI007          ((st_sci0*)0x8A0E0)
#define SCI008          ((st_sci0*)0x8A100)
#define SCI009          ((st_sci0*)0x8A120)

class Sci : public UsartBase
{
public:
    void setup(st_sci0* sci, st_port0* txPort, uint8_t txPin, st_port0* rxPort, uint8_t rxPin, uint32_t baudrate);
    void putchar(char c);
    char getchar(void);

private:
    st_sci0* m_sci;

    st_port0* m_txPort;
    st_port0* m_rxPort;
    uint8_t m_txPin;
    uint8_t m_rxPin;

    uint32_t m_baudrate;

};

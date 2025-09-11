//SCIg(SCI0~9)
#pragma once
#include "../usart_base.hpp"
#include "iodefine.h"
#include "port.hpp"

class Sci : public UsartBase
{
public:
    typedef enum
    {
        E_BAUDRATE_115200 = 12
    }E_BAUDRATE;

    void setup(st_sci0* sci,
        st_port0* txPort, uint8_t txPin,
        st_port0* rxPort, uint8_t rxPin,
        uint32_t clock,
        uint32_t baudrate);

    void putchar(char c);
    char getchar(void);

    void setBaudrate(E_BAUDRATE baudrate);

private:
    __evenaccess st_sci0* m_sci;

    __evenaccess st_port0* m_txPort;
    __evenaccess st_port0* m_rxPort;
    uint8_t m_txPin;
    uint8_t m_rxPin;

};

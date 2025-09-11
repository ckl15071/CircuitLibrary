//SCIi(SCI10, SCI11)
#pragma once
#include "../usart_base.hpp"
#include "iodefine.h"
#include "port.hpp"

//送信完了割り込み許可
void startScii(void);


class Scii : public UsartBase
{
public:
    //typedef enum
    //{
    //    E_bitrate_115200 = 12
    //}E_bitrate;

    void setup(st_sci10* sci,
        st_port0* txPort, uint8_t txPin,
        st_port0* rxPort, uint8_t rxPin,
        uint32_t clock,
        uint32_t bitrate);


    void putchar(char c);
    char getchar(void);

    //void setbitrate(E_bitrate bitrate);

private:
    __evenaccess st_sci10* m_sci;

    __evenaccess st_port0* m_txPort;
    __evenaccess st_port0* m_rxPort;
    uint8_t m_txPin;
    uint8_t m_rxPin;

};

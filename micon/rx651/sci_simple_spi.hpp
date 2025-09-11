#pragma once
#include "../spi_base.hpp"
#include "iodefine.h"
#include <stdint.h>
#include "Port.hpp"

#define LSBFIRST 0
#define MSBFIRST 1

#define SPI_MODE0   0
#define SPI_MODE1   1
#define SPI_MODE2   2
#define SPI_MODE3   3

class SciSimpleSpi : public SpiBase
{
public:
    //enum
    //{
    //    SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3
    //}SPI_MODE;
    //msb or lsb
    //master or slave
    void setup(st_sci0* sci,
        st_port0* sckPort, uint8_t sckPin,
        st_port0* smosiPort, uint8_t smosiPin,
        st_port0* smisoPort, uint8_t smisoPin,
        uint32_t bitrate, uint32_t clock,
        uint8_t bitOrder, uint8_t dataMode
    );
    void setClockDivider(uint32_t bitrate, uint32_t clock);
    void setBitOrder(uint8_t bitOrder);
    void setDataMode(uint8_t dataMode);

    //void transfer(uint8_t data);
    uint8_t transfer(uint8_t data);
    //void transfer(uint16_t data);
    //void transfer(uint8_t* buf, size_t count);

private:
    st_sci0* m_sci;

    st_port0* m_sckPort;
    uint8_t m_sckPin;
    st_port0* m_smosiPort;
    uint8_t m_smosiPin;
    st_port0* m_smisoPort;
    uint8_t m_smisoPin;

    void resetModuleStop(void);
    void setupIo(void);
};

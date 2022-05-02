#include "spi.hpp"
#include <SPI.h>

void SpiArduino::setup(void)
{
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    SPI.setDataMode(SPI_MODE0);
}

void SpiArduino::transfer(uint8_t data)
{
    SPI.transfer(data);
}

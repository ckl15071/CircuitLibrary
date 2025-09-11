#include "mcp3204.hpp"

Mcp3204::Mcp3204(SpiBase* spi, GpioBase* cs)
{
    this->setup(spi, cs);
}

void Mcp3204::setup(SpiBase* spi, GpioBase* cs)
{
    m_spi = spi;
    m_cs = cs;
    m_val[0] = m_val[1] = m_val[2] = m_val[3] = 0;
    m_cs->write(1);
}

void Mcp3204::analogReadSingle(int channel)
//int Mcp3204::analogReadSingle(int channel)
{
    if(channel >= D_CHANNEL_NUM){return;}
    uint8_t recv[2];

    m_cs->write(0);
    m_spi->transfer(0x06 | channel >> 2);
    recv[0] = m_spi->transfer(channel << 6);
    recv[1] = m_spi->transfer(0x00);
    m_cs->write(1);

    //return (recv[0] & 0x0F) << 8 + recv[1];
    m_val[channel] = ((recv[0] & 0x0F) << 8) + recv[1];
}

void Mcp3204::analogReadDiff(int channel)
//int Mcp3204::analogReadDiff(int channel)
{
    if(channel >= D_CHANNEL_NUM){return;}

    uint8_t recv[2];
    m_cs->write(0);
    m_spi->transfer(0x04 | channel >> 2);
    recv[0] = m_spi->transfer(channel << 6);
    recv[1] = m_spi->transfer(0x00);
    m_cs->write(1);

    //return (recv[0] & 0x0F) << 8 + recv[1];
    m_val[channel] = (int)((recv[0] & 0x0F) << 8 + recv[1]);
}

int Mcp3204::getVal(int channel)
{
    if(channel >= D_CHANNEL_NUM){return -1;}
    return m_val[channel];
}

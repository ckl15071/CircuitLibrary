#include "mcp4922.hpp"

//CCRX（C99）用
#include <stdio.h>
#define nullptr (NULL)

Mcp4922::Mcp4922(SpiBase* spi, GpioBase* ss)
{
    this->setup(spi, ss);
}

Mcp4922::Mcp4922(SpiBase* spi, GpioBase* ss, GpioBase* ldac)
{
    this->setup(spi, ss, ldac);
}

//SPIは共有
void Mcp4922::setup(SpiBase* spi, GpioBase* cs)
{
    this->setup(spi, cs, nullptr);
}

void Mcp4922::setup(SpiBase* spi, GpioBase* cs, GpioBase* ldac)
{
    m_spi = spi;
    m_cs = cs;
    m_ldac = ldac;

    if(m_ldac != nullptr)
    {
        m_ldac->write(1);
    }

    m_tgtVal[0] = 0;
    m_tgtVal[1] = 0;
}

void Mcp4922::setTgtVal(int val[2])
{
    m_tgtVal[0] = val[0];
    m_tgtVal[1] = val[1];
}

void Mcp4922::getTgtVal(int val[])
{
    val[0] = m_tgtVal[0];
    val[1] = m_tgtVal[1];
}

//送信処理
void Mcp4922::send(void)
{
    int spiCommand;

    //VOUTA
    spiCommand = 0x30;
    m_cs->write(0);
    m_spi->transfer((m_tgtVal[0] >> 8) | spiCommand);
    m_spi->transfer(m_tgtVal[0] & 0xFF);
    m_cs->write(1);

    //VOUTB
    spiCommand = 0xB0;
    m_cs->write(0);
    m_spi->transfer((m_tgtVal[1] >> 8) | spiCommand);
    m_spi->transfer(m_tgtVal[1] & 0xFF);
    m_cs->write(1);
}

void Mcp4922::load(void)
{
    if(m_ldac != nullptr)
    {
        //10usないぐらい
        m_ldac->write(0);
        m_ldac->write(1);
    }
}

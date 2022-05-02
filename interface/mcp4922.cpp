#include "mcp4922.hpp"

//SPIは共有
void Mcp4922::setup(SpiArduino* spi, GpioBase* ss)
{
    m_spi = spi;
    m_ss = ss;
}

void Mcp4922::setTgtVal(int val[2])
{
    m_tgtVal[0] = val[0];
    m_tgtVal[1] = val[1];
}

//送信処理
void Mcp4922::run(void)
{
    int spiCommand;

    //VOUTA
    spiCommand = 0x30;
    m_ss->write(0);
    m_spi->transfer((m_tgtVal[0] >> 8) | spiCommand);
    m_spi->transfer(m_tgtVal[0] & 0xFF);
    m_ss->write(1);

    //VOUTB
    spiCommand = 0xB0;
    m_ss->write(0);
    m_spi->transfer((m_tgtVal[1] >> 8) | spiCommand);
    m_spi->transfer(m_tgtVal[1] & 0xFF);
    m_ss->write(1);
}

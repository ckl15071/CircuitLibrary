#pragma once
#include "../peripheral/gpio_base.hpp"
#include "../peripheral/spi_base.hpp"

#define D_CHANNEL_NUM   4

//enum
//{
//    E_MODE_SINGLE   = 1,
//    E_MODE_DIFF     
//};

//TODO: DIFF対応
class Mcp3204
{
public:
    //Mcp3204(SpiBase* spi, GpioBase* cs, int sgldiff = 1);
    Mcp3204(){};
    Mcp3204(SpiBase* spi, GpioBase* cs);
    void setup(SpiBase* spi, GpioBase* cs);

    void analogReadSingle(int channel);
    void analogReadDiff(int channel);
    //int analogReadSingle(int channel);
    //int analogReadDiff(int channel);

    int getVal(int channel);

private:
    SpiBase* m_spi;
    GpioBase* m_cs;

    int m_val[D_CHANNEL_NUM];
};

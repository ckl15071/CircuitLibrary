#pragma once
#include "../peripheral/gpio_base.hpp"
#include "../peripheral/spi_base.hpp"

//12bitADC
class Mcp4922
{
public:
    Mcp4922(){};
    Mcp4922(SpiBase* spi, GpioBase* ss);
    Mcp4922(SpiBase* spi, GpioBase* ss, GpioBase* ldac);
    void setup(SpiBase* spi, GpioBase* cs);
    void setup(SpiBase* spi, GpioBase* cs, GpioBase* ldac);

    void setTgtVal(int val[2]);
    void getTgtVal(int val[]);

    void send(void);
    void load(void);

private:
    SpiBase* m_spi;
    GpioBase* m_cs;
    GpioBase* m_ldac;

    int m_tgtVal[2];    //12bit val
};

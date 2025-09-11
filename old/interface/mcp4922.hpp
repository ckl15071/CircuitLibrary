#pragma once
#include "../peripheral/gpio_base.hpp"
#include "../peripheral/spi.hpp"

//12bitADC
class Mcp4922
{
public:
    void setup(SpiArduino* spi, GpioBase* ss);

    void setTgtVal(int val[2]);

    void run(void);

private:
    SpiArduino* m_spi;
    GpioBase* m_ss;

    int m_tgtVal[2];    //12bit val
};

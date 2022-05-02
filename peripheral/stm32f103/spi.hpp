#pragma once
#include "../spi_base.hpp"

class Spi : public SpiBase
{
public:
    void setup(void);

    void transfer();

private:

};


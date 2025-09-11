#pragma once
#include <stdint.h>
#include "iodefine.h"

class Cmt
{
public:
    typedef enum
    {
        E_DIV_PCLK8 = 0x00,
        E_DIV_PCLK32 = 0x01,
        E_DIV_PCLK128 = 0x02,
        E_DIV_PCLK512 = 0x03
    }E_DIV;
    void setup(st_cmt0* cmt, uint16_t cmcor, E_DIV div);

    void setupInterrupt(void);

    void setCompareMatchCount(uint16_t count);
    void setCnt(uint16_t count);
    void resetCnt(void);
    void startCnt(void);
    void stopCnt(void);

private:
    __evenaccess st_cmt0* m_cmt;
};

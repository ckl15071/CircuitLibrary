#pragma once
#include <stdint.h>

class Cmt
{
public:
    void setup();


    void setupInterrupt();

    void setCompareMatchCount(uint16_t count);
    void setCnt(uint16_t count);
    void resetCnt(void);
    void startCnt(void);
    void stopCnt(void);

private:
    //st_cmt* m_cmt;
};

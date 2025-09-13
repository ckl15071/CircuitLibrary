#pragma once
#include <stdint.h>

class Encoder
{
public:
    Encoder();
    ~Encoder();

    void setup(void);
    uint16_t read(void);

private:
    uint16_t m_cnt;

};

#include "encoder.hpp"

Encoder::Encoder()
{
    this->setup();
}

Encoder::~Encoder()
{

}

void Encoder::setup(void)
{
    m_cnt = 0x00;
}
uint16_t Encoder::read(void)
{
    m_cnt = 0;
}

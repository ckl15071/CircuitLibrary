#include "analog_val.hpp"

void AnalogVal::setup(AdConverterBase* adc)
{
    m_adc = adc;
}

int AnalogVal::getVal(void)
{
    return m_adc->getVal();
}

float AnalogVal::getRatio(void)
{
    return m_adc->getRatio();
}

int AnalogVal::get8bitVal(void)
{
    return m_adc->get8bitVal();
}

int AnalogVal::get10bitVal(void)
{
    return m_adc->get10bitVal();
}

int AnalogVal::get12bitVal(void)
{
    return m_adc->get12bitVal();
}

int AnalogVal::get16bitVal(void)
{
    return m_adc->get16bitVal();
}

void AnalogVal::run(void)
{
    m_adc->run();
}

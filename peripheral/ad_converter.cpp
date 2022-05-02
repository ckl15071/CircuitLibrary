#include "ad_converter.hpp"
#include <Arduino.h>

void AdConverterArduino::setup(int pinNum)
{
    m_pinNum = pinNum;
}

float AdConverterArduino::getRatio(void)
{
    return (float)m_analogVal / 1023;
}

int AdConverterArduino::get8bitVal(void)
{
    return m_analogVal >> 2;
}

int AdConverterArduino::get10bitVal(void)
{
    return m_analogVal;
}

int AdConverterArduino::get12bitVal(void)
{
    return m_analogVal << 2;
}

int AdConverterArduino::get16bitVal(void)
{
    return m_analogVal << 4;
}

void AdConverterArduino::run(void)
{
    m_analogVal = analogRead(m_pinNum);
}

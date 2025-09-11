#pragma once
#include "../peripheral/ad_converter_base.hpp"

class AnalogVal
{
public:
    void setup(AdConverterBase* adc);

    int getVal(void);

    float getRatio(void);
    int get8bitVal(void);
    int get10bitVal(void);
    int get12bitVal(void);
    int get16bitVal(void);

    void run(void);

private:
    AdConverterBase* m_adc;

};

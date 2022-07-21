#pragma once
#include "ad_converter_base.hpp"

//ピンごと
//10bitADC
//Arduino用
class AdConverterArduino : public AdConverterBase
{
public:
    void setup(int pinNum);

    float getRatio(void);
    int get8bitVal(void);
    int get10bitVal(void);
    int get12bitVal(void);
    int get16bitVal(void);

    void run(void);

private:
    int m_pinNum;
};

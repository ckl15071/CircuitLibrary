#pragma once

class AdConverterBase
{
public:
    int getVal(void);
    virtual float getRatio(void);
    virtual int get8bitVal(void);
    virtual int get10bitVal(void);
    virtual int get12bitVal(void);
    virtual int get16bitVal(void);

    virtual void run(void);

protected:
    int m_analogVal;

private:
};


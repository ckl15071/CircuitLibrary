#pragma once
#include <stdint.h>

class UsartBase
{
public:
    virtual int read();
    virtual int write();

private:

};

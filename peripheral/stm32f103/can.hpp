#pragma once
#include "../can_base.hpp"

class BxCan : public CanBase
{
public:
    void setup();
    void setBitrate(int bitrate);

    void transfer();
    void send();
    void recv();

private:

};

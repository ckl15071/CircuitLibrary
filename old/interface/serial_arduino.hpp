#pragma once
#include <stdint.h>

class SerialArduino
{
public:
    void setup(int32_t bitrate);
    //int read(uint8_t* data, int size);
    int write(const uint8_t* data, int size);
    int printf(const char* format, ...);

private:

};

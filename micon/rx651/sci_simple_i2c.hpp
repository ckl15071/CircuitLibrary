#pragma once
//#include "../i2c_base.hpp"
#include "iodefine.h"
#include <stdint.h>

//class SciSimpleI2c : public I2cBase
class SciSimpleI2c
{
public:
    void setup(st_sci0* sci,
        st_port0* sclPort, uint8_t sclPin,
        st_port0* sdaPort, uint8_t sdaPin,
        uint32_t bitrate, uint32_t clock);
    
    //void setSlaveAddress(int address);
    int requestFrom(int address, int quantity, int stop);

    int beginTransmission(uint8_t address);
    int beginTransmission(uint8_t address, uint8_t reg);
    int endTransmission(void);
    
    uint8_t read(uint8_t* buffer, size_t len, bool stop);
    int write(uint8_t val);
    int write(uint8_t* data, int length);

    void start(void);

//    uint8_t write(const uint8_t* buffer, size_t len, bool stop,
//        const uint8_t* prefix_buffer, size_t prefix_len);

    
    //uint8_t write_then_read();

private:
    st_sci0* m_sci;

    st_port0* m_sclPort;
    uint8_t m_sclPin;
    st_port0* m_sdaPort;
    uint8_t m_sdaPin;

    void resetModuleStop(void);
    void setupIo(void);

    void init();
    void disable();
    void stop();
    void releaseBus();
    void setAddress(uint8_t address);
    void writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop);

};

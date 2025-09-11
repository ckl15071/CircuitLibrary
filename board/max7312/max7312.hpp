#pragma once
#include <stdint.h>
#include <stdio.h>
#include "../peripheral/gpio_base.hpp"
#include "../peripheral/rx651/sci_simple_i2c.hpp"

//COMMAND
#define D_COMMAND_INPUT_PORT1       0x00
#define D_COMMAND_INPUT_PORT2       0x01
#define D_COMMAND_OUTPUT_PORT1      0x02
#define D_COMMAND_OUTPUT_PORT2      0x03
#define D_COMMAND_PORT1_POL_INV     0x04
#define D_COMMAND_PORT2_POL_INV     0x05
#define D_COMMAND_PORT1_CONFIG      0x06
#define D_COMMAND_PORT2_CONFIG      0x07
#define D_COMMAND_TIMEOUT_REG       0x08
//#define D_COMMAND_FACTORY_RESERVED  0xFF

class Max7312
{
public:
    enum
    {
        INPUT = 1,
        OUTPUT = 0
    };

    Max7312(){};
    Max7312(SciSimpleI2c* i2c, GpioBase* intOut = NULL, uint8_t slaveAddr = 0x40);
    void setup(SciSimpleI2c* i2c, GpioBase* intOut = NULL, uint8_t slaveAddr = 0x40);

    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, uint8_t val);
    int digitalRead(uint8_t pin);

    void writeOutput(void);
    void writeConfig(void);

    //void write(uint8_t command, uint8_t val);
    //void read();

private:
    //I2cBase* m_i2c;
    SciSimpleI2c* m_i2c;
    GpioBase* m_int;
    uint8_t m_slaveAddr;

    uint8_t m_input[2];
    uint8_t m_output[2];
    uint8_t m_polar[2];
    uint8_t m_config[2];
    uint8_t m_timeout;
};

#include "max7312.hpp"

Max7312::Max7312(SciSimpleI2c* i2c, GpioBase* intOut, uint8_t slaveAddr)
{
    this->setup(i2c, intOut, slaveAddr);
}

void Max7312::setup(SciSimpleI2c* i2c, GpioBase* intOut, uint8_t slaveAddr)
{
    m_i2c = i2c;
    m_int = intOut;
    m_slaveAddr = slaveAddr;

    m_output[0] = 0xFF;
    m_output[1] = 0xFF;
    m_polar[0] = 0x00;
    m_polar[1] = 0x00;
    m_config[0] = 0xFF;
    m_config[1] = 0xFF;
    m_timeout = 0x01;
}

void Max7312::pinMode(uint8_t pin, uint8_t mode)
{
    if(pin < 0 || pin > 15)
    {
        return;
    }
    else if(pin < 8)
    {
        m_config[0] &= ~(0x01 << pin);
        m_config[0] |= mode << pin;
    }
    else
    {
        m_config[1] &= ~(0x01 << (pin - 8));
        m_config[1] |= mode << (pin - 8);
    }
}

int Max7312::digitalRead(uint8_t pin)
{
    if(pin < 0 || pin > 15)
    {
        return 0;
    }
    else if(pin < 8)
    {
        return (m_input[0] >> pin) & 0x01;
    }
    else
    {
        return (m_input[1] >> pin) & 0x01;
    }
}

void Max7312::digitalWrite(uint8_t pin, uint8_t val)
{
    if(pin < 0 || pin > 15)
    {
        return;
    }
    else if(pin < 8)
    {
        m_output[0] &= ~(0x01 << pin);
        m_output[0] |= val << pin;
    }
    else
    {
        m_output[1] &= ~(0x01 << (pin - 8));
        m_output[1] |= val << (pin - 8);
    }
}

void Max7312::writeConfig(void)
{
    m_i2c->beginTransmission(m_slaveAddr, D_COMMAND_PORT1_CONFIG);
    m_i2c->write(m_config[0]);
    m_i2c->write(m_config[1]);
    m_i2c->endTransmission();
}

void Max7312::writeOutput(void)
{
    m_i2c->beginTransmission(m_slaveAddr, D_COMMAND_OUTPUT_PORT1);
    m_i2c->write(m_output[0]);
    m_i2c->write(m_output[1]);
    //m_i2c->write(0xFF);
    //m_i2c->write(0xFF);
    m_i2c->endTransmission();
}

//void Max7312::write(uint8_t command, uint8_t val)
//{
//    m_i2c->beginTransmission(m_slaveAddr, command);
//    m_i2c->write(val);
//    m_i2c->endTransmission();
//
//    //アドレス+0
//    //ACK
//    //コマンド
//    //ACK
//    //データ送信
//    //ペアデータ送信
//}
//
//void Max7312::read()
//{
//    //アドレス+0
//    //ACK
//    //コマンド
//    //ACK
//    //リスタート
//    //アドレス+1
//    //ACK
//    //データ流れてくる
//    //マスターからACK返せば永遠に読める
//
//}

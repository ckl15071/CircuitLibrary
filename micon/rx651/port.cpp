#include "port.hpp"

Port::Port(st_port0* port, uint8_t pin, Mode mode)
{
    this->setup(port, pin, mode);
}

void Port::setup(st_port0* port, uint8_t pin, Mode mode)
{
    m_port = port;
    m_pin = pin;
    m_mode = mode;

    m_port->PMR.BYTE &= ~(0x01 << m_pin);
    switch(mode)
    {
    case INPUT:
        m_port->PMR.BYTE &= ~(0x01 << m_pin);
        m_port->PDR.BYTE &= ~(0x01 << m_pin);
        m_port->PCR.BYTE &= ~(0x01 << m_pin);
        break;
    case INPUT_PU:
        m_port->PMR.BYTE &= ~(0x01 << m_pin);
        m_port->PDR.BYTE &= ~(0x01 << m_pin);
        m_port->PCR.BYTE |= (0x01 << m_pin);
        break;

    case OUTPUT_CMOS:
        m_port->PMR.BYTE &= ~(0x01 << m_pin);
        m_port->PDR.BYTE |= (0x01 << m_pin);
        if(m_port == (st_port0*)&PORTE && m_pin == 1)
        {
            PORTE.ODR0.BIT.B2 = 0;
            PORTE.ODR0.BIT.B3 = 0;
        }
        else if(m_pin < 4)
        {
            m_port->ODR0.BYTE &= ~(0x03 << m_pin*2);
        }
        else
        {
            m_port->ODR1.BYTE &= ~(0x03 << (m_pin-4)*2);
        }
        break;
    case OUTPUT_OD_NCH:
        m_port->PMR.BYTE &= ~(0x01 << m_pin);
        m_port->PDR.BYTE |= (0x01 << m_pin);
        if(m_port == (st_port0*)&PORTE && m_pin == 1)
        {
            PORTE.ODR0.BIT.B2 = 1;
            PORTE.ODR0.BIT.B3 = 0;
        }
        else if(m_pin < 4)
        {
            m_port->ODR0.BYTE &= ~(0x03 << m_pin*2);
            m_port->ODR0.BYTE |= (0x01 << m_pin*2);
        }
        else
        {
            m_port->ODR1.BYTE &= ~(0x03 << (m_pin-4)*2);
            m_port->ODR1.BYTE |= (0x01 << (m_pin-4)*2);
        }
        break;
    case OUTPUT_OD_PCH:
        m_port->PMR.BYTE &= ~(0x01 << m_pin);
        m_port->PDR.BYTE |= (0x01 << m_pin);
        if(m_port == (st_port0*)&PORTE && m_pin == 1)
        {
            PORTE.ODR0.BIT.B2 = 0;
            PORTE.ODR0.BIT.B3 = 1;
        }
        else if(m_pin < 4)
        {
            m_port->ODR0.BYTE &= ~(0x03 << m_pin*2);
            m_port->ODR0.BYTE |= (0x02 << m_pin*2);
        }
        else
        {
            m_port->ODR1.BYTE &= ~(0x03 << (m_pin-4)*2);
            m_port->ODR1.BYTE |= (0x02 << (m_pin-4)*2);
        }
        break;
    case PERIPH:
        m_port->PMR.BYTE |= (0x01 << m_pin);
        break;
    };
}

uint8_t Port::read(void)
{
    return (uint8_t)((m_port->PIDR.BYTE >> m_pin) & 0x01);
}

void Port::write(uint8_t value)
{
    if(value)
    {
        m_port->PODR.BYTE |= (0x01 << m_pin);
    }
    else
    {
        m_port->PODR.BYTE &= ~(0x01 << m_pin);
    }
}

void Port::toggle(void)
{
    if(read()){write(0);}
    else{write(1);}
}

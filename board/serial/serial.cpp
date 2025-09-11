#include "serial.hpp"

void Serial::setup(UsartBase* usart, uint32_t baudrate)
{
    m_usart = usart;
    //m_usart->setBaudrate(baudrate);
}
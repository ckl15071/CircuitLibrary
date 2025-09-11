#pragma once
#include <stdint.h>
#include "iodefine.h"

class Can
{
public:
    typedef enum
    {
        E_IDE_STD = 0, E_IDE_EXT = 1
    }E_IDE;

    typedef enum
    {
        E_RTR_DATA_FRAME = 0, E_RTR_REMOTE_FRAME = 1
    }E_RTR;

    //標準フォーマット専用
    typedef struct
    {
        uint32_t StdId; //0 to 0x7FF
        uint32_t ExtId; //0 to 0x1FFFFFFF
        uint8_t IDE;
        uint8_t RTR;
        uint8_t DLC;
        uint8_t data[8];
    }CanMsg;

    typedef enum
    {
        E_DIR_TX = 0, E_DIR_RX = 1
    }E_DIR;

    void setup( st_can* can,
                st_port0* txPort, uint8_t txPin,
                st_port0* rxPort, uint8_t rxPin,
                uint32_t baudrate,
                uint32_t clock);
    
    void setMailBox(int mb, int dir, CanMsg msg);
    void setMailBox(int mb, int dir, uint32_t sid);
    void start(void);

    void send(CanMsg msg, int mb);
    void recv(CanMsg &msg);

private:
    __evenaccess st_can* m_can;
};

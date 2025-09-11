#pragma once
#include "../gpio_base.hpp"
#include "iodefine.h"
#include <stdint.h>

#define P00     (st_port0*)&PORT0, (uint8_t)0
#define P01     (st_port0*)&PORT0, (uint8_t)1
#define P02     (st_port0*)&PORT0, (uint8_t)2
#define P03     (st_port0*)&PORT0, (uint8_t)3
//#define P04     (st_port0*)&PORT0, (uint8_t)4
#define P05     (st_port0*)&PORT0, (uint8_t)5
//#define P06     (st_port0*)&PORT0, (uint8_t)6
#define P07     (st_port0*)&PORT0, (uint8_t)7
#define P10     (st_port0*)&PORT1, (uint8_t)0
#define P11     (st_port0*)&PORT1, (uint8_t)1
#define P12     (st_port0*)&PORT1, (uint8_t)2
#define P13     (st_port0*)&PORT1, (uint8_t)3
#define P14     (st_port0*)&PORT1, (uint8_t)4
#define P15     (st_port0*)&PORT1, (uint8_t)5
#define P16     (st_port0*)&PORT1, (uint8_t)6
#define P17     (st_port0*)&PORT1, (uint8_t)7
#define P20     (st_port0*)&PORT2, (uint8_t)0
#define P21     (st_port0*)&PORT2, (uint8_t)1
#define P22     (st_port0*)&PORT2, (uint8_t)2
#define P23     (st_port0*)&PORT2, (uint8_t)3
#define P24     (st_port0*)&PORT2, (uint8_t)4
#define P25     (st_port0*)&PORT2, (uint8_t)5
#define P26     (st_port0*)&PORT2, (uint8_t)6
#define P27     (st_port0*)&PORT2, (uint8_t)7
#define P30     (st_port0*)&PORT3, (uint8_t)0
#define P31     (st_port0*)&PORT3, (uint8_t)1
#define P32     (st_port0*)&PORT3, (uint8_t)2
#define P33     (st_port0*)&PORT3, (uint8_t)3
#define P34     (st_port0*)&PORT3, (uint8_t)4
#define P35     (st_port0*)&PORT3, (uint8_t)5
#define P36     (st_port0*)&PORT3, (uint8_t)6
#define P37     (st_port0*)&PORT3, (uint8_t)7
#define P40     (st_port0*)&PORT4, (uint8_t)0
#define P41     (st_port0*)&PORT4, (uint8_t)1
#define P42     (st_port0*)&PORT4, (uint8_t)2
#define P43     (st_port0*)&PORT4, (uint8_t)3
#define P44     (st_port0*)&PORT4, (uint8_t)4
#define P45     (st_port0*)&PORT4, (uint8_t)5
#define P46     (st_port0*)&PORT4, (uint8_t)6
#define P47     (st_port0*)&PORT4, (uint8_t)7
#define P50     (st_port0*)&PORT5, (uint8_t)0
#define P51     (st_port0*)&PORT5, (uint8_t)1
#define P52     (st_port0*)&PORT5, (uint8_t)2
#define P53     (st_port0*)&PORT5, (uint8_t)3
#define P54     (st_port0*)&PORT5, (uint8_t)4
#define P55     (st_port0*)&PORT5, (uint8_t)5
#define P56     (st_port0*)&PORT5, (uint8_t)6
#define P57     (st_port0*)&PORT5, (uint8_t)7
#define P60     (st_port0*)&PORT6, (uint8_t)0
#define P61     (st_port0*)&PORT6, (uint8_t)1
#define P62     (st_port0*)&PORT6, (uint8_t)2
#define P63     (st_port0*)&PORT6, (uint8_t)3
#define P64     (st_port0*)&PORT6, (uint8_t)4
#define P65     (st_port0*)&PORT6, (uint8_t)5
#define P66     (st_port0*)&PORT6, (uint8_t)6
#define P67     (st_port0*)&PORT6, (uint8_t)7
#define P70     (st_port0*)&PORT7, (uint8_t)0
#define P71     (st_port0*)&PORT7, (uint8_t)1
#define P72     (st_port0*)&PORT7, (uint8_t)2
#define P73     (st_port0*)&PORT7, (uint8_t)3
#define P74     (st_port0*)&PORT7, (uint8_t)4
#define P75     (st_port0*)&PORT7, (uint8_t)5
#define P76     (st_port0*)&PORT7, (uint8_t)6
#define P77     (st_port0*)&PORT7, (uint8_t)7
#define P80     (st_port0*)&PORT8, (uint8_t)0
#define P81     (st_port0*)&PORT8, (uint8_t)1
#define P82     (st_port0*)&PORT8, (uint8_t)2
#define P83     (st_port0*)&PORT8, (uint8_t)3
#define P84     (st_port0*)&PORT8, (uint8_t)4
#define P85     (st_port0*)&PORT8, (uint8_t)5
#define P86     (st_port0*)&PORT8, (uint8_t)6
#define P87     (st_port0*)&PORT8, (uint8_t)7
#define P90     (st_port0*)&PORT9, (uint8_t)0
#define P91     (st_port0*)&PORT9, (uint8_t)1
#define P92     (st_port0*)&PORT9, (uint8_t)2
#define P93     (st_port0*)&PORT9, (uint8_t)3
#define P94     (st_port0*)&PORT9, (uint8_t)4
#define P95     (st_port0*)&PORT9, (uint8_t)5
#define P96     (st_port0*)&PORT9, (uint8_t)6
#define P97     (st_port0*)&PORT9, (uint8_t)7
#define PA0     (st_port0*)&PORTA, (uint8_t)0
#define PA1     (st_port0*)&PORTA, (uint8_t)1
#define PA2     (st_port0*)&PORTA, (uint8_t)2
#define PA3     (st_port0*)&PORTA, (uint8_t)3
#define PA4     (st_port0*)&PORTA, (uint8_t)4
#define PA5     (st_port0*)&PORTA, (uint8_t)5
#define PA6     (st_port0*)&PORTA, (uint8_t)6
#define PA7     (st_port0*)&PORTA, (uint8_t)7
#define PB0     (st_port0*)&PORTB, (uint8_t)0
#define PB1     (st_port0*)&PORTB, (uint8_t)1
#define PB2     (st_port0*)&PORTB, (uint8_t)2
#define PB3     (st_port0*)&PORTB, (uint8_t)3
#define PB4     (st_port0*)&PORTB, (uint8_t)4
#define PB5     (st_port0*)&PORTB, (uint8_t)5
#define PB6     (st_port0*)&PORTB, (uint8_t)6
#define PB7     (st_port0*)&PORTB, (uint8_t)7
#define PC0     (st_port0*)&PORTC, (uint8_t)0
#define PC1     (st_port0*)&PORTC, (uint8_t)1
#define PC2     (st_port0*)&PORTC, (uint8_t)2
#define PC3     (st_port0*)&PORTC, (uint8_t)3
#define PC4     (st_port0*)&PORTC, (uint8_t)4
#define PC5     (st_port0*)&PORTC, (uint8_t)5
#define PC6     (st_port0*)&PORTC, (uint8_t)6
#define PC7     (st_port0*)&PORTC, (uint8_t)7
#define PD0     (st_port0*)&PORTD, (uint8_t)0
#define PD1     (st_port0*)&PORTD, (uint8_t)1
#define PD2     (st_port0*)&PORTD, (uint8_t)2
#define PD3     (st_port0*)&PORTD, (uint8_t)3
#define PD4     (st_port0*)&PORTD, (uint8_t)4
#define PD5     (st_port0*)&PORTD, (uint8_t)5
#define PD6     (st_port0*)&PORTD, (uint8_t)6
#define PD7     (st_port0*)&PORTD, (uint8_t)7
#define PE0     (st_port0*)&PORTE, (uint8_t)0
#define PE1     (st_port0*)&PORTE, (uint8_t)1
#define PE2     (st_port0*)&PORTE, (uint8_t)2
#define PE3     (st_port0*)&PORTE, (uint8_t)3
#define PE4     (st_port0*)&PORTE, (uint8_t)4
#define PE5     (st_port0*)&PORTE, (uint8_t)5
#define PE6     (st_port0*)&PORTE, (uint8_t)6
#define PE7     (st_port0*)&PORTE, (uint8_t)7
#define PF0     (st_port0*)&PORTF, (uint8_t)0
#define PF1     (st_port0*)&PORTF, (uint8_t)1
#define PF2     (st_port0*)&PORTF, (uint8_t)2
#define PF3     (st_port0*)&PORTF, (uint8_t)3
#define PF4     (st_port0*)&PORTF, (uint8_t)4
#define PF5     (st_port0*)&PORTF, (uint8_t)5
//#define PF6     (st_port0*)&PORTF, (uint8_t)6
//#define PF7     (st_port0*)&PORTF, (uint8_t)7
#define PG0     (st_port0*)&PORTG, (uint8_t)0
#define PG1     (st_port0*)&PORTG, (uint8_t)1
#define PG2     (st_port0*)&PORTG, (uint8_t)2
#define PG3     (st_port0*)&PORTG, (uint8_t)3
#define PG4     (st_port0*)&PORTG, (uint8_t)4
#define PG5     (st_port0*)&PORTG, (uint8_t)5
#define PG6     (st_port0*)&PORTG, (uint8_t)6
#define PG7     (st_port0*)&PORTG, (uint8_t)7
#define PJ0     (st_port0*)&PORTJ, (uint8_t)0
#define PJ1     (st_port0*)&PORTJ, (uint8_t)1
#define PJ2     (st_port0*)&PORTJ, (uint8_t)2
#define PJ3     (st_port0*)&PORTJ, (uint8_t)3
//#define PJ4     (st_port0*)&PORTJ, (uint8_t)4
#define PJ5     (st_port0*)&PORTJ, (uint8_t)5
//#define PJ6     (st_port0*)&PORTJ, (uint8_t)6
//#define PJ7     (st_port0*)&PORTJ, (uint8_t)7

class Port : public GpioBase
{
public:
    enum Mode
    {
        //汎用入出力ポートとして使用
        INPUT = 0x0000,
        INPUT_PU = 0x0010,
        OUTPUT_CMOS = 0x0100,
        OUTPUT_OD_NCH = 0x0101,
        OUTPUT_OD_PCH = 0x0110,

        //周辺モジュールとして使用
        PERIPH = 0x1000
    };

    Port(){};
    Port(st_port0* port, uint8_t pin, Mode mode);
    void setup(st_port0* port, uint8_t pin, Mode mode);

    uint8_t read(void);
    void write(uint8_t value);
    void toggle(void);

private:
    __evenaccess st_port0* m_port;
    uint8_t m_pin;
    Mode m_mode;
};

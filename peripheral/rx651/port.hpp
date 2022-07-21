#pragma once
#include "../gpio_base.hpp"
#include "iodefine.h"
#include <stdint.h>

#define GPIO0           ((st_port0*)0x8c000)
#define GPIO1           ((st_port0*)0x8c001)
#define GPIO2           ((st_port0*)0x8C002)
#define GPIO3           ((st_port0*)0x8C003)
#define GPIO4           ((st_port0*)0x8c004)
#define GPIO5           ((st_port0*)0x8c005)
#define GPIO6           ((st_port0*)0x8c006)
#define GPIO7           ((st_port0*)0x8c007)
#define GPIO8           ((st_port0*)0x8c008)
#define GPIO9           ((st_port0*)0x8c009)
#define GPIOA           ((st_port0*)0x8C00A)
#define GPIOB           ((st_port0*)0x8C00B)
#define GPIOC           ((st_port0*)0x8C00C)
#define GPIOD           ((st_port0*)0x8C00D)
#define GPIOE           ((st_port0*)0x8C00E)
#define GPIOF           ((st_port0*)0x8C00F)
#define GPIOG           ((st_port0*)0x8C010)
#define GPIOJ           ((st_port0*)0x8C012)

#define P00     GPIO0, (uint8_t)0
#define P01     GPIO0, (uint8_t)1
#define P02     GPIO0, (uint8_t)2
#define P03     GPIO0, (uint8_t)3
//#define P04     GPIO0, (uint8_t)4
#define P05     GPIO0, (uint8_t)5
//#define P06     GPIO0, (uint8_t)6
#define P07     GPIO0, (uint8_t)7
#define P10     GPIO1, (uint8_t)0
#define P11     GPIO1, (uint8_t)1
#define P12     GPIO1, (uint8_t)2
#define P13     GPIO1, (uint8_t)3
#define P14     GPIO1, (uint8_t)4
#define P15     GPIO1, (uint8_t)5
#define P16     GPIO1, (uint8_t)6
#define P17     GPIO1, (uint8_t)7
#define P20     GPIO2, (uint8_t)0
#define P21     GPIO2, (uint8_t)1
#define P22     GPIO2, (uint8_t)2
#define P23     GPIO2, (uint8_t)3
#define P24     GPIO2, (uint8_t)4
#define P25     GPIO2, (uint8_t)5
#define P26     GPIO2, (uint8_t)6
#define P27     GPIO2, (uint8_t)7
#define P30     GPIO3, (uint8_t)0
#define P31     GPIO3, (uint8_t)1
#define P32     GPIO3, (uint8_t)2
#define P33     GPIO3, (uint8_t)3
#define P34     GPIO3, (uint8_t)4
#define P35     GPIO3, (uint8_t)5
#define P36     GPIO3, (uint8_t)6
#define P37     GPIO3, (uint8_t)7
#define P40     GPIO4, (uint8_t)0
#define P41     GPIO4, (uint8_t)1
#define P42     GPIO4, (uint8_t)2
#define P43     GPIO4, (uint8_t)3
#define P44     GPIO4, (uint8_t)4
#define P45     GPIO4, (uint8_t)5
#define P46     GPIO4, (uint8_t)6
#define P47     GPIO4, (uint8_t)7
#define P50     GPIO5, (uint8_t)0
#define P51     GPIO5, (uint8_t)1
#define P52     GPIO5, (uint8_t)2
#define P53     GPIO5, (uint8_t)3
#define P54     GPIO5, (uint8_t)4
#define P55     GPIO5, (uint8_t)5
#define P56     GPIO5, (uint8_t)6
#define P57     GPIO5, (uint8_t)7
#define P60     GPIO6, (uint8_t)0
#define P61     GPIO6, (uint8_t)1
#define P62     GPIO6, (uint8_t)2
#define P63     GPIO6, (uint8_t)3
#define P64     GPIO6, (uint8_t)4
#define P65     GPIO6, (uint8_t)5
#define P66     GPIO6, (uint8_t)6
#define P67     GPIO6, (uint8_t)7
#define P70     GPIO7, (uint8_t)0
#define P71     GPIO7, (uint8_t)1
#define P72     GPIO7, (uint8_t)2
#define P73     GPIO7, (uint8_t)3
#define P74     GPIO7, (uint8_t)4
#define P75     GPIO7, (uint8_t)5
#define P76     GPIO7, (uint8_t)6
#define P77     GPIO7, (uint8_t)7
#define P80     GPIO8, (uint8_t)0
#define P81     GPIO8, (uint8_t)1
#define P82     GPIO8, (uint8_t)2
#define P83     GPIO8, (uint8_t)3
#define P84     GPIO8, (uint8_t)4
#define P85     GPIO8, (uint8_t)5
#define P86     GPIO8, (uint8_t)6
#define P87     GPIO8, (uint8_t)7
#define P90     GPIO9, (uint8_t)0
#define P91     GPIO9, (uint8_t)1
#define P92     GPIO9, (uint8_t)2
#define P93     GPIO9, (uint8_t)3
#define P94     GPIO9, (uint8_t)4
#define P95     GPIO9, (uint8_t)5
#define P96     GPIO9, (uint8_t)6
#define P97     GPIO9, (uint8_t)7
#define PA0     GPIOA, (uint8_t)0
#define PA1     GPIOA, (uint8_t)1
#define PA2     GPIOA, (uint8_t)2
#define PA3     GPIOA, (uint8_t)3
#define PA4     GPIOA, (uint8_t)4
#define PA5     GPIOA, (uint8_t)5
#define PA6     GPIOA, (uint8_t)6
#define PA7     GPIOA, (uint8_t)7
#define PB0     GPIOB, (uint8_t)0
#define PB1     GPIOB, (uint8_t)1
#define PB2     GPIOB, (uint8_t)2
#define PB3     GPIOB, (uint8_t)3
#define PB4     GPIOB, (uint8_t)4
#define PB5     GPIOB, (uint8_t)5
#define PB6     GPIOB, (uint8_t)6
#define PB7     GPIOB, (uint8_t)7
#define PC0     GPIOC, (uint8_t)0
#define PC1     GPIOC, (uint8_t)1
#define PC2     GPIOC, (uint8_t)2
#define PC3     GPIOC, (uint8_t)3
#define PC4     GPIOC, (uint8_t)4
#define PC5     GPIOC, (uint8_t)5
#define PC6     GPIOC, (uint8_t)6
#define PC7     GPIOC, (uint8_t)7
#define PD0     GPIOD, (uint8_t)0
#define PD1     GPIOD, (uint8_t)1
#define PD2     GPIOD, (uint8_t)2
#define PD3     GPIOD, (uint8_t)3
#define PD4     GPIOD, (uint8_t)4
#define PD5     GPIOD, (uint8_t)5
#define PD6     GPIOD, (uint8_t)6
#define PD7     GPIOD, (uint8_t)7
#define PE0     GPIOE, (uint8_t)0
#define PE1     GPIOE, (uint8_t)1
#define PE2     GPIOE, (uint8_t)2
#define PE3     GPIOE, (uint8_t)3
#define PE4     GPIOE, (uint8_t)4
#define PE5     GPIOE, (uint8_t)5
#define PE6     GPIOE, (uint8_t)6
#define PE7     GPIOE, (uint8_t)7
#define PF0     GPIOF, (uint8_t)0
#define PF1     GPIOF, (uint8_t)1
#define PF2     GPIOF, (uint8_t)2
#define PF3     GPIOF, (uint8_t)3
#define PF4     GPIOF, (uint8_t)4
#define PF5     GPIOF, (uint8_t)5
//#define PF6     GPIOF, (uint8_t)6
//#define PF7     GPIOF, (uint8_t)7
#define PG0     GPIOG, (uint8_t)0
#define PG1     GPIOG, (uint8_t)1
#define PG2     GPIOG, (uint8_t)2
#define PG3     GPIOG, (uint8_t)3
#define PG4     GPIOG, (uint8_t)4
#define PG5     GPIOG, (uint8_t)5
#define PG6     GPIOG, (uint8_t)6
#define PG7     GPIOG, (uint8_t)7
#define PJ0     GPIOJ, (uint8_t)0
#define PJ1     GPIOJ, (uint8_t)1
#define PJ2     GPIOJ, (uint8_t)2
#define PJ3     GPIOJ, (uint8_t)3
//#define PJ4     GPIOJ, (uint8_t)4
#define PJ5     GPIOJ, (uint8_t)5
//#define PJ6     GPIOJ, (uint8_t)6
//#define PJ7     GPIOJ, (uint8_t)7

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
    void setup(st_port0* port, uint8_t pin, Mode mode);

    uint8_t read(void);
    void write(uint8_t value);
    void toggle(void);

private:
    st_port0* m_port;
    uint8_t m_pin;
    Mode m_mode;
};

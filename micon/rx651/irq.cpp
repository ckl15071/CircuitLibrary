#include "irq.hpp"
#include "iodefine.h"

#define D_IRQ_VECTOR_NUM_BASE       64

Irq::Irq(uint8_t irq, st_port0* port, uint8_t pin, uint8_t irqcr, uint8_t priority)
{
    this->setup(irq, port, pin, irqcr, priority);
}

void Irq::setup(uint8_t irq, st_port0* port, uint8_t pin, uint8_t irqcr, uint8_t priority)
{
    m_irq = irq;

    //[1]割り込み要求禁止
    ICU.IER[getIer(irq)].BYTE &= ~(0x01 << (irq % 8));

    //デジタルフィルタ無効
    if(irq < 8){ICU.IRQFLTE0.BYTE &= ~(0x01 << irq);}
    else{ICU.IRQFLTE1.BYTE &= ~(0x01 << (irq - 8));}

    //デジタルフィルタのサンプリングクロック設定
    //IRQFLTC0.FCLKSELi = ;
    //IRQFLTC1.FCLKSELi = ;
    //int PCLKB_DIV_8 = 0x01;
    //int PCLKb_DIV_32 = 0x02;
    //int PCLKB_DIV_64 = 0x03;

    //一旦分周なし固定
    if(irq < 8){ICU.IRQFLTC0.WORD &= ~((0x03) << (irq * 2));}
    else{ICU.IRQFLTC1.WORD &= ~((0x03) << ((irq - 8) * 2));}
    //if(irq < 8){ICU.IRQFLTC0.BYTE |= (PCLKB_DIV_8 << (irq * 2));}
    //else{ICU.IRQRLTC1.BYTE |= (PCLKB_DIV_8 << (irq * 2));}

    //[4]I/Oポートの設定
    //Port p(port, pin, Port::INPUT);
    MPC.PWPR.BIT.B0WI = 0;      //PFSWEビットへの書き込み許可
    MPC.PWPR.BIT.PFSWE = 1;     //PFSレジスタへの書き込み許可
    switch(irq)
    {
    case 0:
        if(port == (st_port0*)&PORT1 && pin == 0){MPC.P10PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT3 && pin == 0){MPC.P30PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTD && pin == 0){MPC.PD0PFS.BIT.ISEL = 1;}
        break;
    case 1:
        if(port == (st_port0*)&PORT1 && pin == 1){MPC.P11PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT3 && pin == 1){MPC.P31PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTD && pin == 1){MPC.PD1PFS.BIT.ISEL = 1;}
        break;
    case 2:
        if(port == (st_port0*)&PORT1 && pin == 2){MPC.P12PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT3 && pin == 2){MPC.P32PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTD && pin == 2){MPC.PD2PFS.BIT.ISEL = 1;}
        break;
    case 3:
        if(port == (st_port0*)&PORT1 && pin == 3){MPC.P13PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT3 && pin == 3){MPC.P33PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTD && pin == 3){MPC.PD3PFS.BIT.ISEL = 1;}
        break;
    case 4:
        if(port == (st_port0*)&PORT1 && pin == 4){MPC.P14PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT3 && pin == 4){MPC.P34PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTB && pin == 1){MPC.PB1PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTD && pin == 4){MPC.PD4PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTF && pin == 5){MPC.PF5PFS.BIT.ISEL = 1;}
        break;
    case 5:
        if(port == (st_port0*)&PORT1 && pin == 5){MPC.P15PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTA && pin == 4){MPC.PA4PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTD && pin == 5){MPC.PD5PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTE && pin == 5){MPC.PE5PFS.BIT.ISEL = 1;}
        break;
    case 6:
        if(port == (st_port0*)&PORT1 && pin == 6){MPC.P16PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTA && pin == 3){MPC.PA3PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTD && pin == 6){MPC.PD6PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTE && pin == 6){MPC.PE6PFS.BIT.ISEL = 1;}
        break;
    case 7:
        if(port == (st_port0*)&PORT1 && pin == 7){MPC.P17PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTD && pin == 7){MPC.PD7PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTE && pin == 2){MPC.PE2PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTE && pin == 7){MPC.PE7PFS.BIT.ISEL = 1;}
        break;
    case 8:
        if(port == (st_port0*)&PORT0 && pin == 0){MPC.P00PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT2 && pin == 0){MPC.P20PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT4 && pin == 0){MPC.P40PFS.BIT.ISEL = 1;}
        break;
    case 9:
        if(port == (st_port0*)&PORT0 && pin == 1){MPC.P01PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT2 && pin == 1){MPC.P21PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT4 && pin == 1){MPC.P41PFS.BIT.ISEL = 1;}
        break;
    case 10:
        if(port == (st_port0*)&PORT0 && pin == 2){MPC.P02PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT4 && pin == 2){MPC.P42PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT5 && pin == 5){MPC.P55PFS.BIT.ISEL = 1;}
        break;
    case 11:
        if(port == (st_port0*)&PORT0 && pin == 3){MPC.P03PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT4 && pin == 3){MPC.P43PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTA && pin == 1){MPC.PA1PFS.BIT.ISEL = 1;}
        break;
    case 12:
        if(port == (st_port0*)&PORT4 && pin == 4){MPC.P44PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTB && pin == 0){MPC.PB0PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTC && pin == 1){MPC.PC1PFS.BIT.ISEL = 1;}
        break;
    case 13:
        if(port == (st_port0*)&PORT0 && pin == 5){MPC.P05PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT4 && pin == 5){MPC.P45PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTC && pin == 6){MPC.PC6PFS.BIT.ISEL = 1;}
        break;
    case 14:
        if(port == (st_port0*)&PORT4 && pin == 6){MPC.P46PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTC && pin == 0){MPC.PC0PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORTC && pin == 7){MPC.PC7PFS.BIT.ISEL = 1;}
        break;
    case 15:
        if(port == (st_port0*)&PORT0 && pin == 7){MPC.P07PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT4 && pin == 7){MPC.P47PFS.BIT.ISEL = 1;}
        if(port == (st_port0*)&PORT6 && pin == 7){MPC.P67PFS.BIT.ISEL = 1;}
        break;
    default:
        break;
    }
    MPC.PWPR.BIT.PFSWE = 0;     //PFSレジスタへの書き込み禁止
    MPC.PWPR.BIT.B0WI = 1;      //PFSWEビットへの書き込み禁止 

    //[5]検出方法選択
    //irqcr = 0:レベル、1:立ち下がり、2:立ち上がり、3:両エッジ
    ICU.IRQCR[irq].BIT.IRQMD = irqcr & 0x03;

    //[6]エッジ検出の場合フラグ0
    if(irqcr != 0)
    {
        ICU.IR[irq + D_IRQ_VECTOR_NUM_BASE].BIT.IR = 0;
    }

    //[7]デジタルフィルタ有効化
    if(irq < 8){ICU.IRQFLTE0.BYTE |= (0x01 << irq);}
    else{ICU.IRQFLTE1.BYTE |= (0x01 << (irq - 8));}

    //[8]割り込み要求先をDTCにする場合
    //ICU.DTCER[irq + D_IRQ_VECTOR_NUM_BASE].BIT.DTCE = 0;    //CPUへの割り込み要因に設定

    //優先度設定
    ICU.IPR[irq + D_IRQ_VECTOR_NUM_BASE].BIT.IPR = priority;

    //[9]割り込み要求許可
    ICU.IER[getIer(irq)].BYTE |= (0x01 << (irq % 8));
}

uint8_t Irq::getIer(uint8_t irq)
{
    return (irq < 8) ? 8 : 9;
}

//uint8_t Irq::getIen(uint8_t irq)
//{
//    return irq % 8;
//}

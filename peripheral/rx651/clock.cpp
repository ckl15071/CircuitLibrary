#include "clock.hpp"
#include "iodefine.h"

namespace clock
{
void setup96MHz(void)
{
    //プロテクト解除
    SYSTEM.PRCR.WORD = 0xA503;    //クロック発生回路、消費電力低減機能

    //HOCO停止
    //SYSTEM.HOCOPCR.BIT.HOCOPCNT = 1;    //HOCOの停止

    //動作電力制御モード設定
//    SYSTEM.OPCCR.BIT.OPCM = 0;    //高速動作モード
//    while(SYSTEM.OPCCR.BIT.OPCMTSF == 1);

    //サブクロックの発振停止
//    RTC.RCR4.BIT.RCKSEL = 0;    //カウントソースにサブクロックを選択
//    RTC.RCR3.BIT.RTCEN = 0;    //サブクロック発振器停止
//    //dummy read four times
//    //for(int i = 0; i < 4; i++)
//    //{
//    //    int dummy = RTC.RCR3.BIT.RTCEN;
//    //}
//    SYSTEM.SOSCCR.BIT.SOSTP = 1;    //サブクロック発振器停止
//    while(SYSTEM.SOSCCR.BYTE != 0x01);
//    while(SYSTEM.OSCOVFSR.BIT.SOOVF != 0);    //サブクロック発振停止待ち

    //1
    SYSTEM.MOFCR.BIT.MOFXIN = 0;    //強制発振なし
    SYSTEM.MOFCR.BIT.MODRV2 = 0;    //メインクロック発振器ドライブ能力2切り替え（0:20.1~24MHz）
    SYSTEM.MOFCR.BIT.MOSEL = 0;        //発振子

    //2
    SYSTEM.MOSCWTCR.BIT.MSTS = 0x53;    //約10ms待ち

    //3
    SYSTEM.MOSCCR.BIT.MOSTP = 0;    //メインクロック発振器動作
    //while(SYSTEM.MOSCCR.BIT.MOSTP != 0);
    while(SYSTEM.OSCOVFSR.BIT.MOOVF != 1);    //メインクロック発信安定待ち
    //while(SYSTEM.OSCOVFSR.BIT.MOOVF != 0);    //メインクロック発信安定待ち

    //4
    //SYSTEM.ROMWT.BIT.ROMWT = 2;        //ROMウェイトサイクル（フラッシュメモリのアクセスウェイト数）:2
    SYSTEM.ROMWT.BIT.ROMWT = 1;
    while(SYSTEM.ROMWT.BIT.ROMWT != 1);

    //5
    //PLLコントロールレジスタ
    SYSTEM.PLLCR.BIT.PLLSRCSEL = 0;    //PLLクロックソースはメインクロック発振器
    SYSTEM.PLLCR.BIT.PLIDIV = 1;    //PLLCRは2分周
    //SYSTEM.PLLCR.BIT.STC = 0x27;    //PLLCRは20逓倍
    SYSTEM.PLLCR.BIT.STC = 0x1F;    //PLLCRは16逓倍

    //6
    SYSTEM.PLLCR2.BIT.PLLEN = 0;    //PLL動作
    //7
    while(SYSTEM.OSCOVFSR.BIT.PLOVF != 1);    //PLLクロック発振安定待ち
    //while(SYSTEM.OSCOVFSR.BIT.PLOVF == 0);    //PLLクロック発振安定待ち
    //メインクロック発信コントロールレジスタMOSCWTCRの設定必要

    //分周
    SYSTEM.SCKCR.BIT.PCKD = 2;    //4分周    周辺モジュールクロックD（60MHz max）
    SYSTEM.SCKCR.BIT.PCKC = 2;    //4分周    周辺モジュールクロックC（60MHz max）
    SYSTEM.SCKCR.BIT.PCKB = 2;    //4分周    周辺モジュールクロックB（60MHz max）
    SYSTEM.SCKCR.BIT.PCKA = 1;    //2分周    周辺モジュールクロックA（120MHz max）
    SYSTEM.SCKCR.BIT.BCK = 1;    //2分周    外部バスクロック（120MHz max）
    SYSTEM.SCKCR.BIT.ICK = 1;    //2分周    システムクロック（120MHz max）
    SYSTEM.SCKCR.BIT.FCK = 2;    //4分周    FlashIFクロック（4~60MHz、60MHz max）
    //sdclk 60MHz(max)
    //uclk 48MHz(max)
    //canmclk 24MHz(max)
    //RTCSCLK：32.768kHz
    //RTCMCLK：8MHz～16MHz
    //IWDTCLK：120kHz
    //JTAGTCK：10MHz (max)

    //pclkd=48
    //PCLKC=48
    //PCLKB=48
    //PCLKA=96
    //ICLK=96

    //8
    //システムクロックコントロールレジスタ3（ここまでにPLL起こす）
    SYSTEM.SCKCR3.BIT.CKSEL = 4;    //PLL回路選択

    SYSTEM.PRCR.WORD = 0xA500;
}

}//namespace

#include "s12adf.hpp"
#include "iodefine.h"

void S12Ad::setup(int scanMode, int ch, int intNum)
{
    if(scanMode == 0x03){return;}

    //モジュールストップ解除
    SYSTEM.PRCR.WORD = 0xA502;
    MSTP(S12AD) = 0;
    SYSTEM.PRCR.WORD = 0xA500;

    //割り込み要求禁止
    S12AD.ADCSR.BIT.ADIE = 0;
    IEN(PERIB, INTB130) = 0;
    //IEN(S12ADI) = 0;

    //A/D変換禁止
    S12AD.ADCSR.BIT.ADST = 0;

    //スキャンモード選択
    S12AD.ADCSR.BIT.ADCS = scanMode;

    //チャネル選択
    S12AD.ADANSA0.WORD = ch;

    //A/D変換時間の設定
    //初期値11ステート、変更なし
    //S12AD.ADSSTR0 = 0xFF;   //0x30;

    S12AD.ADADS0.WORD = 0xFF;
    S12AD.ADADC.BYTE = 0x85;

    //I/Oポート機能設定
    if(ch & 0x01)
    {
        PORT4.PMR.BIT.B0 = 0;
        PORT4.PDR.BIT.B0 = 0;
        MPC.P40PFS.BYTE = 0x80;
    }
    if(ch & 0x02)
    {
        PORT4.PMR.BIT.B1 = 0;
        PORT4.PDR.BIT.B1 = 0;
        MPC.P41PFS.BYTE = 0x80;
    }
    if(ch & 0x04)
    {
        PORT4.PMR.BIT.B2 = 0;
        PORT4.PDR.BIT.B2 = 0;
        MPC.P42PFS.BYTE = 0x80;
    }
    if(ch & 0x08)
    {
        PORT4.PMR.BIT.B3 = 0;
        PORT4.PDR.BIT.B3 = 0;
        MPC.P43PFS.BYTE = 0x80;
    }
    if(ch & 0x10)
    {
        PORT4.PMR.BIT.B4 = 0;
        PORT4.PDR.BIT.B4 = 0;
        MPC.P44PFS.BYTE = 0x80;
    }
    if(ch & 0x20)
    {
        PORT4.PMR.BIT.B5 = 0;
        PORT4.PDR.BIT.B5 = 0;
        MPC.P45PFS.BYTE = 0x80;
    }
    if(ch & 0x40)
    {
        PORT4.PMR.BIT.B6 = 0;
        PORT4.PDR.BIT.B6 = 0;
        MPC.P46PFS.BYTE = 0x80;
    }
    if(ch & 0x80)
    {
        PORT4.PMR.BIT.B7 = 0;
        PORT4.PDR.BIT.B7 = 0;
        MPC.P47PFS.BYTE = 0x80;
    }

    //選択型割り込み設定
    ICU.SLIBXR130.BYTE = 64;        //選択型割り込み（144~207）に要因番号64（S12ADI）を割り当て
    ICU.SLIPRCR.BIT.WPRC = 1;   //選択型割り込み要因選択レジスタ書き込み禁止、一度1にするとソフトで0にできない
    while(ICU.SLIPRCR.BIT.WPRC != 1);

    //割り込み優先レベル設定（130）
    IPR(PERIB, INTB130) = 5;
    //IPR(S12ADI) = 0x01;

    ICU.DTCER[intNum].BIT.DTCE = 0;

    //割り込み要求クリア
    ICU.IR[intNum].BIT.IR = 0;
    //IR(S12ADI) = 0;

    //割り込み要求を許可
    S12AD.ADCSR.BIT.ADIE = 1;

    //IEN(S12ADI) = 1;

    //マスカブル割り込み許可
    //setpsw_i();

    //A/D変換開始
    //S12AD.ADCSR.BIT.ADST = 1;
}

void S12Ad::start(void)
{
    IEN(PERIB, INTB130) = 0;
    ICU.IR[IR_PERIB_INTB130].BIT.IR = 0;          //割り込み要求クリア
    IPR(PERIB, INTB130) = 7;
    IEN(PERIB, INTB130) = 1;

    S12AD.ADCSR.BIT.ADST = 1;
}

void S12Ad::stop(void)
{
    S12AD.ADCSR.BIT.ADST = 0;
}

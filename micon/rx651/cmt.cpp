#include "cmt.hpp"

#define D_ICU_VECT_NUM_CMT0   28
#define D_ICU_VECT_NUM_CMT1   29
#define D_ICU_VECT_NUM_CMT2   
#define D_ICU_VECT_NUM_CMT3   

void Cmt::setup(st_cmt0* cmt, uint16_t cmcor, E_DIV div)
{
    m_cmt = cmt;
    //書き込みプロテクトレジスタ
    SYSTEM.PRCR.WORD = 0xA502;    //書き込み許可
    if(m_cmt == &CMT0){MSTP(CMT0) = 0;}
    if(m_cmt == &CMT1){MSTP(CMT1) = 0;}
    if(m_cmt == &CMT2){MSTP(CMT2) = 0;}
    if(m_cmt == &CMT3){MSTP(CMT3) = 0;}
    SYSTEM.PRCR.WORD = 0xA500;    //書き込み禁止

    //基本設定
    //m_cmt->CMCR.BIT.CKS = 0;    //クロック:PCKL/8=48/8MHz=6MHz
    m_cmt->CMCR.BIT.CKS = div;
    m_cmt->CMCR.BIT.CMIE = 1;    //コンペアマッチ割り込み（CMIn）許可
    //m_cmt->CMCR.WORD = 0x0040;
    //m_cmt->CMCR.WORD &= ~(0x03);
    //m_cmt->CMCR.WORD |= (div & 0x03);

    this->setCompareMatchCount(cmcor);

    this->setupInterrupt();

    this->resetCnt();
}

void Cmt::setCompareMatchCount(uint16_t count)
{
    m_cmt->CMCOR = count - 1;
}

void Cmt::setupInterrupt(void)
{
    if(m_cmt == &CMT0)
    {
        //CMT0
        IPR(CMT0, CMI0) = 10;            //ICU.IPR[28].BIT.IPR = 7;    //割り込み優先レベル
        ICU.DTCER[D_ICU_VECT_NUM_CMT0].BIT.DTCE = 0;     //CPUへの割り込み要因に設定
        IEN(CMT0, CMI0) = 1;            //割り込み要求許可//ICU.IER[0x03].BIT.IEN4 = 1;    //割り込み要求許可
        ICU.IR[D_ICU_VECT_NUM_CMT0].BIT.IR = 0;          //割り込み要求クリア
    }
    if(m_cmt == &CMT1)
    {
        //CMT1
        IPR(CMT1, CMI1) = 6;            //割り込み優先レベル
        ICU.DTCER[D_ICU_VECT_NUM_CMT1].BIT.DTCE = 0;     //CPUへの割り込み要因に設定
        IEN(CMT1, CMI1) = 1;            //割り込み要求許可
        ICU.IR[D_ICU_VECT_NUM_CMT1].BIT.IR = 0;          //割り込み要求クリア
    }
    if(m_cmt == &CMT2)
    {
        ;
        //CMT002、CMT003は選択型割り込み
    }
    if(m_cmt == &CMT3)
    {
        ;
        //CMT002、CMT003は選択型割り込み
    }
}

void Cmt::setCnt(uint16_t count)
{
    m_cmt->CMCNT = 0;    //カウンタ
}

void Cmt::resetCnt(void)
{
    this->setCnt(0);
}

void Cmt::startCnt(void)
{
    if(m_cmt == &CMT0)
    {
        CMT.CMSTR0.BIT.STR0 = 1;    //CMT0.CMCNTカウンタのカウント動作開始
    }
    if(m_cmt == &CMT1)
    {
        CMT.CMSTR0.BIT.STR1 = 1;    //CMT1.CMCNTカウンタのカウント動作開始
    }
    if(m_cmt == &CMT2)
    {
        CMT.CMSTR1.BIT.STR2 = 1;    //CMT2.CMCNTカウンタのカウント動作開始
    }
    if(m_cmt == &CMT3)
    {
        CMT.CMSTR1.BIT.STR3 = 1;    //CMT3.CMCNTカウンタのカウント動作開始
    }
}

void Cmt::stopCnt(void)
{
    if(m_cmt == &CMT0)
    {
        CMT.CMSTR0.BIT.STR0 = 0;    //CMT0.CMCNTカウンタのカウント動作停止
    }
    if(m_cmt == &CMT1)
    {
        CMT.CMSTR0.BIT.STR1 = 0;    //CMT1.CMCNTカウンタのカウント動作停止
    }
    if(m_cmt == &CMT2)
    {
        CMT.CMSTR1.BIT.STR2 = 0;    //CMT2.CMCNTカウンタのカウント動作停止
    }
    if(m_cmt == &CMT3)
    {
        CMT.CMSTR1.BIT.STR3 = 0;    //CMT3.CMCNTカウンタのカウント動作停止
    }
}

#include "cmt.hpp"
#include "iodefine.h"

void Cmt::setup()
{
    SYSTEM.PRCR.WORD = 0xA502;    //書き込み許可
    //if(st_cmt == CMT0)
    //{
    //    MSTP(CMT0) = 0;
    //}
    //if(st_cmt == CMT1)
    //{
    //    MSTP(CMT1) = 0;
    //}
    //if(st_cmt == CMT2)
    //{
    //    MSTP(CMT2) = 0;
    //}
    //if(st_cmt == CMT3)
    //{
    //    MSTP(CMT3) = 0;
    //}
    SYSTEM.PRCR.WORD = 0xA500;    //書き込み禁止
}

//void Cmt::setCompareMatchCount(uint16_t count)
//{
//    m_cmt->CMCOR = count - 1;
//}

//void Cmt::setupInterrupt(uint8_t pr)
//{
//    if(m_cmt == CMT0)
//    {
//        IPR(CMT0, CMI0) = pr;
//        IEN(CMT0, CMI0) = 1;
//        ICU.DTCER[28].BIT.DTCE = 0;
//        ICU.IR[28].BIT.IR = 0;
//    }
//    //if(m_cmt == CMT1)
//    //{
//        //IPR(CMT1, CMI1) = ;
//        //IEN(CMT1, CMI1) = 1;
//        //ICU.DTCER[29].BIT.DTCE = 0;
//        //ICU.IR[29].BIT.IR = 0;
//    //}
//    //if(m_cmt == CMT2)
//    //{
//
//    //}
//    //if(m_cmt == CMT3)
//    //{
//
//    //}
//
//}

void Cmt::setCnt(uint16_t count)
{
    CMT0.CMCNT = 0;    //カウンタ
}

void Cmt::resetCnt(void)
{
    this->setCnt(0);
}

void Cmt::startCnt(void)
{
    CMT.CMSTR0.BIT.STR0 = 1;    //CMT0.CMCNTカウンタのカウント動作開始
}

void Cmt::stopCnt(void)
{
    CMT.CMSTR0.BIT.STR0 = 0;    //CMT0.CMCNTカウンタのカウント動作開始
}

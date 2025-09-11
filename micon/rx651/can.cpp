#include "can.hpp"
#include "port.hpp"
void _setupCanMb(void);

void Can::setup(st_can* can,
                st_port0* txPort, uint8_t txPin,
                st_port0* rxPort, uint8_t rxPin,
                uint32_t bitrate, uint32_t clock)
{
    m_can = can;

    //CANポート設定
    MPC.PWPR.BIT.B0WI = 0;                  //プロテクト解除
    MPC.PWPR.BIT.PFSWE = 1;
    if(m_can == &CAN0)
    {
        if(txPort == (st_port0*)&PORT3 && txPin == 2){MPC.P32PFS.BIT.PSEL = 0x10;}
        if(rxPort == (st_port0*)&PORT3 && rxPin == 3){MPC.P33PFS.BIT.PSEL = 0x10;}
        if(txPort == (st_port0*)&PORTD && txPin == 1){MPC.PD1PFS.BIT.PSEL = 0x10;}
        if(rxPort == (st_port0*)&PORTD && rxPin == 2){MPC.PD2PFS.BIT.PSEL = 0x10;}
    }
    if(m_can == &CAN1)
    {
        if(txPort == (st_port0*)&PORT1 && txPin == 4){MPC.P14PFS.BIT.PSEL = 0x10;}
        if(rxPort == (st_port0*)&PORT1 && rxPin == 5){MPC.P15PFS.BIT.PSEL = 0x10;}
        if(txPort == (st_port0*)&PORT5 && txPin == 4){MPC.P54PFS.BIT.PSEL = 0x10;}
        if(rxPort == (st_port0*)&PORT5 && rxPin == 5){MPC.P55PFS.BIT.PSEL = 0x10;}
    }
    MPC.PWPR.BIT.PFSWE = 0;                 //プロテクト
    MPC.PWPR.BIT.B0WI = 1;
    txPort->PMR.BYTE |= (0x01 << txPin);
    rxPort->PMR.BYTE |= (0x01 << rxPin);

    //モジュールストップ解除
    SYSTEM.PRCR.WORD = 0xA502;
    if      (m_can == &CAN0){MSTP(CAN0) = 0;}
    else if (m_can == &CAN1){MSTP(CAN1) = 0;}
    SYSTEM.PRCR.WORD = 0xA500;

    //:**********************************************************************
    //! リセットモード
    //:**********************************************************************

    //CANリセットモード移行（BCRレジスタを設定する）
    m_can->CTLR.BIT.CANM = 1;     //CANリセットモード（1か3）
    while(m_can->STR.BIT.RSTST != 1);
    m_can->CTLR.BIT.SLPM = 0;     //CANスリープモード解除
    while(m_can->STR.BIT.SLPST == 1);

    //:**********************************************************************
    //! リセットモード（CAN基本設定）
    //:**********************************************************************

    //CAN設定
    m_can->CTLR.BIT.MBM = 0;      ///通常MBモード
    m_can->CTLR.BIT.IDFM = 0;     ///標準IDモード
    //m_can->CTLR.BIT.MLM = 0;      ///オーバライドモード
    m_can->CTLR.BIT.MLM = 1;      ///オーバランモード
    m_can->CTLR.BIT.TPM = 0;      ///ID優先送信モード
    m_can->CTLR.BIT.TSPS = 0;     ///タイムスタンププリスケーラ1ビットタイム（なにこれ）
    //m_can->CTLR.BIT.SLPM = 0;     //CANスリープモードではない
    //m_can->CTLR.BIT.BOM = 0;      //ノーマルモード
    m_can->CTLR.BIT.RBOC = 0;     ///バスオフ強制復帰しない

    //通信速度（500kbps）
    m_can->BCR.BIT.CCLKS = 0; //CANクロックソースPCLKB
    m_can->BCR.BIT.TSEG2 = 2; //3Tq（タイムセグメント2）
    m_can->BCR.BIT.SJW = 0;   //1Tq（再同期ジャンプ幅）
    //m_can->BCR.BIT.BRP = 7;   //fCANCLKの周波数設定（P+1=8）
    //m_can->BCR.BIT.BRP = clock / (12 * bitrate) - 1;
    m_can->BCR.BIT.BRP = clock * 1000000 / (bitrate * 12) - 1;
    m_can->BCR.BIT.TSEG1 = 7; //8Tq（タイムセグメント1）

    //12Tq固定
    //m_can->BCR.LONG = 0x70000200;
    //m_can->BCR.LONG |= ((clock / (12 * bitrate) - 1) & 0x3FF) << 16;   //BRP
    
    //EIERはリセットモード時に設定
    //エラー割り込み許可
    //m_can->EIER.BYTE = 0xFF;      //エラー割り込み全許可
    m_can->EIER.BIT.ORIE = 1;     //受信オーバラン割り込み許可
    
    //送信割り込み、受信割り込み（選択型割り込み）
    IEN(PERIB, INTB128) = 0;
    ICU.SLIBXR128.BYTE = 52;     //選択型割り込み（144~207）に要因番号52（RXM0）を割り当て
    //! @todo   選択型割り込みまとめて記述
    //ICU.SLIPRCR.BIT.WPRC = 1;   //選択型割り込み要因選択レジスタ書き込み禁止、一度1にするとソフトで0にできない
    //while(ICU.SLIPRCR.BIT.WPRC != 1);
    ICU.DTCER[128].BIT.DTCE = 0;   //CPUへの割り込み要因に設定
    ICU.IR[128].BIT.IR = 0;     //割り込み要求クリア
    IPR(PERIB, INTB128) = 7;
    IEN(PERIB, INTB128) = 1;

    //エラー割り込み（グループ割り込みBE0）
    //IPR(CAN0, ERS0) = 7;
    //IEN(CAN0, ERS0) = 1;
    ICU.GENBE0.BIT.EN0 = 1;
    ICU.DTCER[106].BIT.DTCE = 0;    //CPUへの割り込み要因に設定
    ICU.IR[106].BIT.IR = 0;    //割り込み要求クリア
    IPR(ICU, GROUPBE0) = 7;
    IEN(ICU, GROUPBE0) = 1;

    //:**********************************************************************
    //! Haltモード移行
    //:**********************************************************************

    //CAN Haltモード移行（MB設定、テストモード設定）
    //CTLRレジスタ（CANM、SLPM以外）、EIERレジスタ変更禁止
    m_can->CTLR.BIT.CANM = 2; //CAN Haltモード
    while(m_can->STR.BIT.HLTST != 1);

    //:**********************************************************************
    //! Haltモード（メールボックス、テストモード設定）
    //:**********************************************************************

    m_can->TCR.BIT.TSTE = 0;
    //テスト制御
    //m_can->TCR.BIT.TSTE = 1;  //CANテストモード許可
    //m_can->TCR.BIT.TSTM = 1;  //リッスンオンモード
    //m_can->TCR.BIT.TSTM = 2;  //外部ループバック
    //m_can->TCR.BIT.TSTM = 3;  //内部ループバック

    //_setupCanMb();

    //割り込み設定
    //BE0   0   CAN0    ERS0    106（ベクタ番号）
    //BE0   1   CAN1    ERS1    106（ベクタ番号）

    //選択型割り込みB要因一覧
    //割り込み要因番号                          割り込みステータスフラグ
    //50    RXF0（受信FIFO割り込み）            PIBR6.PIR2
    //51    TXF0                                PIBR6.PIR3
    //52    RXM0（MB0~31メッセージ受信完了）    PIBR6.PIR4
    //53    TXM0                                PIBR6.PIR5
    //54    RXF1（受信FIFO割り込み）            PIBR6.PIR6
    //55    TXF1                                PIBR6.PIR7
    //56    RXM1（MB0~31メッセージ受信完了）    PIBR7.PIR0
    //57    TXM1                                PIBR6.PIR1

    //CANオペレーションモード移行
    m_can->CTLR.BIT.CANM = 0;     //CANオペレーションモード
    while(m_can->STR.BIT.RSTST != 0 || m_can->STR.BIT.HLTST != 0);
}

//標準フォーマットのみ対応（暫定）
void Can::send(CanMsg msg, int mb)
{
    if(mb < 0 || mb >= 32){return;}

    m_can->MCTL[mb].BIT.TX.TRMREQ = 0;
    m_can->MCTL[mb].BIT.TX.SENTDATA = 0;

    m_can->MB[mb].ID.BIT.IDE = msg.IDE;
    m_can->MB[mb].ID.BIT.RTR = msg.RTR;
    if(msg.IDE == E_IDE_STD)
    {
        //標準フォーマット
        //m_can->MB[mb].ID.BIT.SID = msg.StdId;
        if(m_can == &CAN0){CAN0.MB[mb].ID.BIT.SID = msg.StdId;}
        if(m_can == &CAN1){CAN0.MB[mb].ID.BIT.SID = msg.StdId;}
    }
    else
    {
        //拡張フォーマット
        //m_can->MB[mb].ID.BIT.SID = msg.StdId;
        //m_can->MB[mb].ID.BIT.EID = ;
    }
    for(int i = 0; i < msg.DLC; i++)
    {
        m_can->MB[mb].DATA[i] = msg.data[i];
    }

    m_can->MCTL[mb].BIT.TX.TRMREQ = 1;  //送信メールボックスに設定
}

void Can::setMailBox(int mb, int dir, CanMsg msg)
{
    if(mb < 0 || mb > 31){return;}

    //Haltモード遷移
    m_can->CTLR.BIT.CANM = 2; //CAN Haltモード
    while(m_can->STR.BIT.HLTST != 1);

    if(dir == E_DIR_TX)
    {
        //送信MBに設定
        m_can->MCTL[mb].BIT.RX.RECREQ = 0;
        //m_can->MCTL[mb].BIT.TX.TRMREQ = 1;
    }
    else
    {
        //CAN0.MIER.BIT.MB1 = 1;      //MB0割り込み許可
        //CAN0.MKIVLR.BIT.MB1 = 1;
        //CAN0.MB[1].ID.BIT.IDE = 0;
        //CAN0.MB[1].ID.BIT.RTR = 0;
        //CAN0.MB[1].ID.BIT.SID = 0x025;

        m_can->MIER.LONG |= (0x01 << mb);       //メールボックス割り込み許可
        m_can->MKIVLR.LONG |= (0x01 << mb);     //アクセプタンスマスクレジスタ無効化

        m_can->MB[mb].ID.BIT.IDE = msg.IDE;
        m_can->MB[mb].ID.BIT.RTR = msg.RTR;
        m_can->MB[mb].ID.BIT.SID = msg.StdId;

        //受信MBに設定
        m_can->MCTL[mb].BIT.RX.RECREQ = 1;
        m_can->MCTL[mb].BIT.TX.TRMREQ = 0;
    }
}

void Can::setMailBox(int mb, int dir, uint32_t sid)
{
    CanMsg msg;
    msg.StdId = (sid & 0x7FF);
    //msg.IDE = E_IDE::Std;
    msg.IDE = E_IDE_STD;
    //msg.RTR = E_RTR::DATA_FRAME;
    msg.RTR = E_RTR_DATA_FRAME;
    this->setMailBox(mb, dir, msg);
}

void Can::start(void)
{
    //CANオペレーションモード移行
    m_can->CTLR.BIT.CANM = 0;     //CANオペレーションモード
    while(m_can->STR.BIT.RSTST != 0 || m_can->STR.BIT.HLTST != 0);
}

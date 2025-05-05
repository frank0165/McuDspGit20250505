/* 
 * DSP MCU与外部交互 系统信息初始化功能
 * Copyright 2025-2025 Tauren Semiconductor.
 * Create data: 2025-3-28
 * auther: zhanglaipeng
 * email: laipeng.zhang@taurentech.net
 */

#ifndef _LANE_MODE_API_H_
#define _LANE_MODE_API_H_

#include "sre_basic_typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum LaneRateModeE {
    LANE_MODE_INVALID = 0,
    LANE_MODE_1P244 = 1,
    LANE_MODE_1P25,
    LANE_MODE_2P488,
    LANE_MODE_2P5,
    LANE_MODE_3P125,
    LANE_MODE_5P,
    LANE_MODE_9P95,
    LANE_MODE_10P3125,
    LANE_MODE_12P44,
    LANE_MODE_12P5,
    LANE_MODE_24P88_NRZ,
    LANE_MODE_24P88_PAM4,
    LANE_MODE_25P78125_NRZ,
    LANE_MODE_25P78125_PAM4,
    LANE_MODE_26P5625_NRZ,
    LANE_MODE_26P5625_PAM4,
    LANE_MODE_49P76_NRZ,
    LANE_MODE_49P76_PAM4,
    LANE_MODE_51P5625_NRZ,
    LANE_MODE_51P5625_PAM4,
    LANE_MODE_53P125_NRZ,
    LANE_MODE_53P125_PAM4,
    LANE_MODE_NUM
} LaneRateModeE;

typedef enum LaneDataBitWidthE {
    DATA_BIT_WIDTH_8 = 0,
    DATA_BIT_WIDTH_16,
    DATA_BIT_WIDTH_32,
    DATA_BIT_WIDTH_64,
    DATA_BIT_WIDTH_NUM
} LaneDataBitWidthE;
/*********** API_RUN_CTRL_CAT CHIP_RUN para struct ***************/
typedef struct SystemChipRunS {
    UINT32 rxRunMask;   // 0 host rx   1 line rx
    UINT32 txRunMask;   // 0 host tx   1 line tx
} SystemChipRunS;
/*********** API_RUN_CTRL_CAT CHIP_RUN para struct ***************/


/*********** API_PARA_INIT_CAT CHIP_MODE_INIT para struct ***************/
typedef union LaneRateMode {
    UINT8 val;
    struct {
        UINT8 rateMode: 6;
        UINT8 dataWidth: 2;
    } bits;
} LaneRateMode;
typedef union LaneModeCfg {
    UINT32 val;
    struct {
        LaneRateMode rxRate;
        LaneRateMode txRate[3];
    } hostBits;
    struct {
        LaneRateMode rxRate[3];
        LaneRateMode txRate;
    } lineBits;
} LaneModeCfg;

typedef struct SystemParaInitS {
    UINT32 isCfgFlag;
    UINT32 rxEnableMask;  // bit0 host rx, bit1 line rx   0:disable  1:enable
    UINT32 txEnableMask;  // bit0 host tx, bit1 line tx   0:disable  1:enable
    LaneModeCfg laneModeCfg[2];    // 0 host     1 line
} SystemParaInitS;
typedef struct SystemParaInitOutS {
    UINT32 rxEnableMask;  // bit0 host rx, bit1 line rx   0:disable  1:enable
    UINT32 txEnableMask;  // bit0 host tx, bit1 line tx   0:disable  1:enable
    LaneModeCfg laneModeCfg[2];
} SystemParaInitOutS;
/*********** API_PARA_INIT_CAT CHIP_MODE_INIT para struct ***************/

/*********** API_PARA_INIT_CAT DATAPATH_PARA_INIT para struct ***************/
typedef struct TxDatapathParaS {
    UINT8 txDEncodeAdd : 1;
    UINT8 txEncode1dEn : 1;
    UINT8 txDataInv : 1;
    UINT8 txGrayEn : 1;
    UINT8 txSwapEn : 1;
    UINT8 txLutSel : 1;    // 0:直通表  1:依lane rate mode配置
    UINT8 txLutGear : 2;   // 直通表档位，仅在txLutSel为0时有效，0-3,0幅度最低
} TxDatapathParaS;
typedef struct RxDatapathParaS {
    UINT8 rxSel1d : 1;
    UINT8 rxEn1d : 1;
    UINT8 rxDataInv : 1;
    UINT8 rxGrayEn : 1;
    UINT8 rxSwapEn : 1;
    UINT8 rxBurstEn : 1;  // 0: 连续模式， 1：burst模式     仅BCDR host及DSP line侧有效
    UINT8 rsv : 2;
} RxDatapathParaS;

typedef union LaneDatapathModeCfg{
    UINT32 val;
    struct {
        RxDatapathParaS hostRxDatapathCfg;
        TxDatapathParaS hostTxDatapathCfg;
        RxDatapathParaS lineRxDatapathCfg;
        TxDatapathParaS lineTxDatapathCfg;
    } bits;
} LaneDatapathModeCfg;
typedef struct SystemDatapathParaInitS {
    UINT32 isCfgFlag;
    UINT32 rxCfgMask;  // bit0 host rx, bit1 line rx   0:disable  1:enable
    UINT32 txCfgMask;  // bit0 host tx, bit1 line tx   0:disable  1:enable
    LaneDatapathModeCfg laneDatapathCfg;  // 每条lane一个byte，从低到高  host rx  host tx  line rx  line tx
} SystemDatapathParaInitS;
typedef struct SystemDatapathParaOutS {
    UINT32 rxCfgMask;  // bit0 host rx, bit1 line rx   0:disable  1:enable
    UINT32 txCfgMask;  // bit0 host tx, bit1 line tx   0:disable  1:enable
    LaneDatapathModeCfg laneDatapathCfg;  // 每条lane一个byte，从低到高  host rx  host tx  line rx  line tx
} SystemDatapathParaOutS;

typedef struct SystemCalibParaInitS {
    UINT32 isCfgFlag;
    UINT32 rxCfgMask;
    UINT32 txCfgMask;
} SystemCalibParaInitS;
typedef struct SystemCalibParaInitRspS {
    UINT32 rxCfgMask;
    UINT32 txCfgMask;
} SystemCalibParaInitRspS;

typedef struct SystemCalibParaAddrRspS {
    UINT32 baseAddr;
    UINT32 headLen;
    UINT32 oneLaneLen;
} SystemCalibParaAddrRspS;

/*********** API_PARA_INIT_CAT DATAPATH_PARA_INIT para struct ***************/

/*********** API_RESET_CTRL_CAT SIG_LANE_MODE_INIT para struct ***************/
typedef union SigLaneDatapathCfgS {
    UINT32 val;
    struct {
        RxDatapathParaS rxDatapathCfg;
        UINT8 rsv0;
        TxDatapathParaS txDatapathCfg;
        UINT8 rsv1;
    } bits;
} SigLaneDatapathCfgS;
typedef struct SystemSigLaneParaS {
    UINT32 laneType;            // 0:host  1:line;
    UINT32 enCfg;               // bit0:rx   bit1:tx
    LaneModeCfg laneModeCfg;
    SigLaneDatapathCfgS datapathCfg;
} SystemSigLaneParaS;
/*********** API_RESET_CTRL_CAT SIG_LANE_MODE_INIT para struct ***************/


/*********** API_RESET_CTRL_CAT LANE_SHUTDOWN para struct ***************/
typedef union LaneShutdownCfgS {
    UINT32 val;
    struct {
        UINT16 laneType;  // 0 host  1 line
        UINT8 rxDownFlag;
        UINT8 txDownFlag;
    } bits;
} LaneShutdownCfgS;
typedef struct SystemLaneShutdownS {
    UINT32 laneNum;  // max 2  host一个 line一个
    LaneShutdownCfgS cfg[2];
} SystemLaneShutdownS;
/*********** API_RESET_CTRL_CAT LANE_SHUTDOWN para struct ***************/

/*********** API_RESET_CTRL_CAT SIG_LANE_TX_PRBS_CFG para struct ***************/
typedef struct TrxPrbsParaS {
    UINT8 prbsEn : 1;     // 0 不使能，1 使能
    UINT8 prbsPatSel : 3;   // pattern选择 0:PRBS7 1:PRBS13 2:PRBS15 3: PRBS31  其他无效
    UINT8 prbsPatInv : 1;   // 0：不取反   1：取反
    UINT8 rsv : 3;
} TrxPrbsParaS;

typedef struct TxPrbsUserSetS {
    UINT32 valid : 1;       // 该用户是否有效 0:无效 1:有效
    UINT32 prbsBlen : 20;   // 该用户的prbs发送长度，单位cycle，  0~1048575 实际生效1~1048576
    UINT32 rateMode : 5;   // 该用户的tx工作速率模式（需要与该lane的工作模式匹配）
    UINT32 rsv : 6;
} TxPrbsUserSetS;

typedef union LaneTxPrbsBasicCfgS {
    UINT32 val;
    TrxPrbsParaS bits;
} LaneTxPrbsBasicCfgS;

typedef union LaneTxPrbsMultiUserCfgS {
    UINT32 val;
    TxPrbsUserSetS bits;
} LaneTxPrbsMultiUserCfgS;
typedef struct SystemLaneTxPrbsCfgS {
    UINT32 laneType;   // 0 host 1 line
    LaneTxPrbsBasicCfgS prbsPara;
    LaneTxPrbsMultiUserCfgS multiUserCfg[3]; // 仅host tx有效
} SystemLaneTxPrbsCfgS;
/*********** API_RESET_CTRL_CAT SIG_LANE_TX_PRBS_CFG para struct ***************/

/*********** API_DFX_CTRL_CAT RX_LANE_BER_GET para struct***************/
typedef union LaneRxBerCmdS {
    UINT32 val;
    TrxPrbsParaS bits;
} LaneRxBerCmdS;

typedef struct SystemLaneRxBerCmdS {
    UINT32 laneType;  // 0 host 1 line
    LaneRxBerCmdS prbsPara;
    UINT32 cycleHigh;
    UINT32 cycleLow;
} SystemLaneRxBerCmdS;

typedef struct SystemLaneRxBerOutS {
    UINT32 laneType;
    UINT32 berLowVal;
    UINT32 berHighVal;
    UINT32 cycleHigh;
    UINT32 cycleLow;
} SystemLaneRxBerOutS;
/*********** API_DFX_CTRL_CAT RX_LANE_BER_GET para struct***************/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


# 1 "../../src/thd_dsp_download_release_V0_0/do_cmd_struct.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 389 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "../../src/thd_dsp_download_release_V0_0/do_cmd_struct.c" 2








# 1 "../../src/thd_dsp_download_release_V0_0/do_api.h" 1
# 12 "../../src/thd_dsp_download_release_V0_0/do_api.h"
# 1 "../../src/thd_dsp_download_release_V0_0/lane_mode_api.h" 1
# 12 "../../src/thd_dsp_download_release_V0_0/lane_mode_api.h"
# 1 "../../src/thd_dsp_download_release_V0_0/sre_basic_typedef.h" 1
# 10 "../../src/thd_dsp_download_release_V0_0/sre_basic_typedef.h"
# 1 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 1 3
# 56 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 3
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int int64_t;


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;





typedef signed char int_least8_t;
typedef signed short int int_least16_t;
typedef signed int int_least32_t;
typedef signed long long int int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long int uint_least64_t;




typedef signed int int_fast8_t;
typedef signed int int_fast16_t;
typedef signed int int_fast32_t;
typedef signed long long int int_fast64_t;


typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long int uint_fast64_t;






typedef signed int intptr_t;
typedef unsigned int uintptr_t;



typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
# 11 "../../src/thd_dsp_download_release_V0_0/sre_basic_typedef.h" 2



typedef unsigned char UINT8;
typedef signed char INT8;
typedef unsigned short UINT16;
typedef char CHAR;
typedef short INT16;
typedef unsigned int UINT32;
typedef int INT32;
typedef long long INT64;
typedef unsigned long long UINT64;
typedef uintptr_t UINTPTR;
typedef void VOID;
typedef char SRE_BOOL;
typedef double DOUBLE;
typedef float FLOAT;
# 13 "../../src/thd_dsp_download_release_V0_0/lane_mode_api.h" 2





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

typedef struct SystemChipRunS {
    UINT32 rxRunMask;
    UINT32 txRunMask;
} SystemChipRunS;




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
    UINT32 rxEnableMask;
    UINT32 txEnableMask;
    LaneModeCfg laneModeCfg[2];
} SystemParaInitS;
typedef struct SystemParaInitOutS {
    UINT32 rxEnableMask;
    UINT32 txEnableMask;
    LaneModeCfg laneModeCfg[2];
} SystemParaInitOutS;



typedef struct TxDatapathParaS {
    UINT8 txDEncodeAdd : 1;
    UINT8 txEncode1dEn : 1;
    UINT8 txDataInv : 1;
    UINT8 txGrayEn : 1;
    UINT8 txSwapEn : 1;
    UINT8 txLutSel : 1;
    UINT8 txLutGear : 2;
} TxDatapathParaS;
typedef struct RxDatapathParaS {
    UINT8 rxSel1d : 1;
    UINT8 rxEn1d : 1;
    UINT8 rxDataInv : 1;
    UINT8 rxGrayEn : 1;
    UINT8 rxSwapEn : 1;
    UINT8 rxBurstEn : 1;
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
    UINT32 rxCfgMask;
    UINT32 txCfgMask;
    LaneDatapathModeCfg laneDatapathCfg;
} SystemDatapathParaInitS;
typedef struct SystemDatapathParaOutS {
    UINT32 rxCfgMask;
    UINT32 txCfgMask;
    LaneDatapathModeCfg laneDatapathCfg;
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
    UINT32 laneType;
    UINT32 enCfg;
    LaneModeCfg laneModeCfg;
    SigLaneDatapathCfgS datapathCfg;
} SystemSigLaneParaS;




typedef union LaneShutdownCfgS {
    UINT32 val;
    struct {
        UINT16 laneType;
        UINT8 rxDownFlag;
        UINT8 txDownFlag;
    } bits;
} LaneShutdownCfgS;
typedef struct SystemLaneShutdownS {
    UINT32 laneNum;
    LaneShutdownCfgS cfg[2];
} SystemLaneShutdownS;



typedef struct TrxPrbsParaS {
    UINT8 prbsEn : 1;
    UINT8 prbsPatSel : 3;
    UINT8 prbsPatInv : 1;
    UINT8 rsv : 3;
} TrxPrbsParaS;

typedef struct TxPrbsUserSetS {
    UINT32 valid : 1;
    UINT32 prbsBlen : 20;
    UINT32 rateMode : 5;
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
    UINT32 laneType;
    LaneTxPrbsBasicCfgS prbsPara;
    LaneTxPrbsMultiUserCfgS multiUserCfg[3];
} SystemLaneTxPrbsCfgS;



typedef union LaneRxBerCmdS {
    UINT32 val;
    TrxPrbsParaS bits;
} LaneRxBerCmdS;

typedef struct SystemLaneRxBerCmdS {
    UINT32 laneType;
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
# 13 "../../src/thd_dsp_download_release_V0_0/do_api.h" 2






typedef struct MailBoxCmd {
    volatile UINT32 funDef;
    volatile UINT32 inPara[62];
    volatile UINT32 cmdFlag;
} MailBoxCmd;

typedef struct MailBoxRe {
    volatile UINT32 funDef;
    volatile UINT32 ret;
    volatile UINT32 outPara[61];
    volatile UINT32 cmdFlag;
} MailBoxRe;
typedef union MailBoxManage {
    MailBoxCmd cmd;
    MailBoxRe re;
} MailBoxManage;
# 48 "../../src/thd_dsp_download_release_V0_0/do_api.h"
typedef enum FuncCataE {
    API_RUN_CTRL_CAT = 0,
    API_PARA_INIT_CAT,
    API_RESET_CTRL_CAT,
    API_ALRM_CTRL_CAT,
    API_LPC_CTRL_CAT,
    API_DFX_CTRL_CAT,
    API_WAVE_CTRL_CAT,
    API_FUNC_CATA_NUM,
} FuncCataE;


typedef enum RunCtrlFunE {
    CHIP_RUN = 0,
    CHIP_TX_RUN,
    CHIP_RX_RUN,
    RUN_CTRL_FUNC_NUM
} RunCtrlFunE;


typedef enum ParaInitFunE {
    CHIP_MODE_INIT = 0,
    DATAPATH_PARA_INIT = 1,
    CALIB_PARA_INIT,
    PARA_INIT_FUNC_NUM
} ParaInitFunE;


typedef enum ResetCtrlFuncE {
    SIG_LANE_MODE_INIT = 0,
    LANE_SHUTDOWN,
    SIG_LANE_TX_PRBS_CFG,
    RESET_CTRL_FUNC_NUM
} ResetCtrlFuncE;


typedef enum AlrmCtrlFuncE {
    ALRM_RPT_GET = 0,
    ALRM_FIX,
    ALRM_CTRL_NUM
} AlrmCtrlFuncE;


typedef enum LowPowerCtrlFuncE {
    LOWPOWER_SET = 0,
    LOWPOWER_CTRL_FUNC_NUM
} LowPowerCtrlFuncE;


typedef enum DfxCtrlFuncE {
    MCU_TICK_GET = 0,
    IDLE_ERR_SET,
    VERSION_GET,
    RX_LANE_BER_GET,
    UART_DEBUG_EN,
    DFX_CTRL_FUNC_NUM
} DfxCtrlFuncE;


typedef enum WaveCtrlFuncE {
    TX_LUT_SET = 0,
    WAVE_CTRL_FUNC_NUM
} WaveCtrlFuncE;
# 10 "../../src/thd_dsp_download_release_V0_0/do_cmd_struct.c" 2

# 1 "../../src/thd_dsp_download_release_V0_0/ip_op.h" 1
# 19 "../../src/thd_dsp_download_release_V0_0/ip_op.h"
typedef struct DoOpCmdS {
    UINT32 funcCat;
    UINT32 funNo;
    UINT16 inputParaNum;
    UINT16 outputParaNum;
    UINT32 timeOutMs;
} DoOpCmdS;

typedef struct FwSecS {
    UINT32 fwName[4];
    UINT32 secNum;
    UINT32 secInfo[20];
    UINT32 fwBuff[0x5c00];
} FwSecS;

extern UINTPTR g_sreFuncArr[API_FUNC_CATA_NUM];

VOID SRE_McuEnable(UINT8 en);
VOID SRE_DownloadFirmware(FwSecS *fwManage);
UINT32 SRE_CmdSend(UINT32 funcCata, UINT32 func, UINT32 *inputPara, UINT32 *outputPara, UINT8 needWait);
UINT32 SRE_GetCmdResult(UINT32 funcCata, UINT32 func, UINT32 *outputPara, UINT32 *finish);
UINT32 SRE_HpllSetup(UINT8 workMode);
UINT32 SRE_DspSetUp(UINT8 workMode, UINT32 fwAddr);
# 12 "../../src/thd_dsp_download_release_V0_0/do_cmd_struct.c" 2


DoOpCmdS g_funcCat0Para[RUN_CTRL_FUNC_NUM] = {

    {API_RUN_CTRL_CAT, CHIP_RUN, 2, 0, 60 * 1000},
    {API_RUN_CTRL_CAT, CHIP_TX_RUN, 0, 0, 60 * 1000},
    {API_RUN_CTRL_CAT, CHIP_RX_RUN, 0, 0, 60 * 1000},
};


DoOpCmdS g_funcCat1Para[PARA_INIT_FUNC_NUM] = {





    {API_PARA_INIT_CAT, CHIP_MODE_INIT, 5, 4, 1 * 100},
    {API_PARA_INIT_CAT, DATAPATH_PARA_INIT, 4, 3, 1 * 100},

    {API_PARA_INIT_CAT, CALIB_PARA_INIT, 3, 2, 1 * 100},
};


DoOpCmdS g_funcCat2Para[RESET_CTRL_FUNC_NUM] = {

    {API_RESET_CTRL_CAT, SIG_LANE_MODE_INIT, 3, 0, 5 * 1000},
    {API_RESET_CTRL_CAT, LANE_SHUTDOWN, 33, 0, 1 * 200},
};


DoOpCmdS g_funcCat3Para[ALRM_CTRL_NUM] = {

    {API_ALRM_CTRL_CAT, ALRM_RPT_GET, 0, 1, 1 * 100},
    {API_ALRM_CTRL_CAT, ALRM_FIX, 1, 0, 1 * 200},
};


DoOpCmdS g_funcCat4Para[LOWPOWER_CTRL_FUNC_NUM] = {

    {API_LPC_CTRL_CAT, LOWPOWER_SET, 2, 0, 1 * 100},
};


DoOpCmdS g_funcCat5Para[DFX_CTRL_FUNC_NUM] = {

    {API_DFX_CTRL_CAT, MCU_TICK_GET, 0, 1, 1 * 100},
    {API_DFX_CTRL_CAT, IDLE_ERR_SET, 1, 5, 1 * 100},
    {API_DFX_CTRL_CAT, VERSION_GET, 1, 9, 1 * 100},
    {API_DFX_CTRL_CAT, RX_LANE_BER_GET, 4, 5, 1 * 100},
    {API_DFX_CTRL_CAT, UART_DEBUG_EN, 2, 1, 1 * 100}
};


DoOpCmdS g_funcCat6Para[WAVE_CTRL_FUNC_NUM] = {

    {API_WAVE_CTRL_CAT, TX_LUT_SET, 0, 1, 1 * 100},
};


UINTPTR g_sreFuncArr[API_FUNC_CATA_NUM] = {
    (UINTPTR)g_funcCat0Para,
    (UINTPTR)g_funcCat1Para,
    (UINTPTR)g_funcCat2Para,
    (UINTPTR)g_funcCat3Para,
    (UINTPTR)g_funcCat4Para,
    (UINTPTR)g_funcCat5Para,
    (UINTPTR)g_funcCat6Para
};

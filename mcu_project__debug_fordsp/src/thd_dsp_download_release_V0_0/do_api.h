/* 
 * MCU与外部交互 系统信息初始化功能
 * Copyright 2022-2023 Tauren Semiconductor.
 * Create data: 2023-9-19
 * auther: zhanglaipeng
 * email: laipeng.zhang@taurentech.net
 */

#ifndef _DO_API_H_
#define _DO_API_H_

#include "lane_mode_api.h"
#ifdef __cplusplus
extern "C" {
#endif

#define MAILBOX_FUNC_PARA_NUM   62
#define MAILBOX_FUNC_OUT_NUM    61
typedef struct MailBoxCmd {
    volatile UINT32 funDef;
    volatile UINT32 inPara[MAILBOX_FUNC_PARA_NUM];
    volatile UINT32 cmdFlag;
} MailBoxCmd;

typedef struct MailBoxRe {
    volatile UINT32 funDef;
    volatile UINT32 ret;
    volatile UINT32 outPara[MAILBOX_FUNC_OUT_NUM];
    volatile UINT32 cmdFlag;
} MailBoxRe;
typedef union MailBoxManage {
    MailBoxCmd cmd;
    MailBoxRe re;
} MailBoxManage;

#define FUNC_CMD_MAGIC_WORD         0x00005A5A
#define FUNC_FININSH_MAGIC_WORD     0xA5A50000
#define FUNC_FININSH_MAGIC_MASK     0xFFFF0000
#define FUNC_CLEAR_INT_MAGIC_WORD   0x0


#define PARA_GET_FLAG   0x0
#define PARA_SET_FLAG   0x1

#define IDLE_ERR_GET_TYPE     0x0
#define IDLE_ERR_CLR_TYPE     0x1

typedef enum FuncCataE {
    API_RUN_CTRL_CAT = 0,          // func 0x0000_xxxx cata
    API_PARA_INIT_CAT,             // func 0x0001_xxxx cata
    API_RESET_CTRL_CAT,            // func 0x0002_xxxx cata
    API_ALRM_CTRL_CAT,             // func 0x0003_xxxx cata
    API_LPC_CTRL_CAT,              // func 0x0004_xxxx cata
    API_DFX_CTRL_CAT,              // func 0x0005_xxxx cata
    API_WAVE_CTRL_CAT,             // func 0x0006_xxxx cata
    API_FUNC_CATA_NUM,
} FuncCataE;

// API_RUN_CTRL_CAT        func 0x0000_xxxx cata
typedef enum RunCtrlFunE {
    CHIP_RUN = 0,
    CHIP_TX_RUN,
    CHIP_RX_RUN,
    RUN_CTRL_FUNC_NUM
} RunCtrlFunE;

// API_PARA_INIT_CAT        func 0x0001_xxxx cata
typedef enum ParaInitFunE {
    CHIP_MODE_INIT = 0,
    DATAPATH_PARA_INIT = 1,
    CALIB_PARA_INIT,
    PARA_INIT_FUNC_NUM
} ParaInitFunE;

// API_RESET_CTRL_CAT       func 0x0002_xxxx cata
typedef enum ResetCtrlFuncE {
    SIG_LANE_MODE_INIT = 0,
    LANE_SHUTDOWN,
    SIG_LANE_TX_PRBS_CFG,
    RESET_CTRL_FUNC_NUM
} ResetCtrlFuncE;

// API_ALRM_CTRL_CAT        func 0x0003_xxxx cata
typedef enum AlrmCtrlFuncE {
    ALRM_RPT_GET = 0,
    ALRM_FIX,
    ALRM_CTRL_NUM
} AlrmCtrlFuncE;

// API_LPC_CTRL_CAT         func 0x0004_xxxx cata
typedef enum LowPowerCtrlFuncE {
    LOWPOWER_SET = 0,
    LOWPOWER_CTRL_FUNC_NUM
} LowPowerCtrlFuncE;

// API_DFX_CTRL_CAT        func 0x0005_xxxx cata
typedef enum DfxCtrlFuncE {
    MCU_TICK_GET = 0,
    IDLE_ERR_SET,
    VERSION_GET,
    RX_LANE_BER_GET,
    UART_DEBUG_EN,
    DFX_CTRL_FUNC_NUM
} DfxCtrlFuncE;

// API_WAVE_CTRL_CAT        func 0x0006_xxxx cata
typedef enum WaveCtrlFuncE {
    TX_LUT_SET = 0,
    WAVE_CTRL_FUNC_NUM
} WaveCtrlFuncE;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

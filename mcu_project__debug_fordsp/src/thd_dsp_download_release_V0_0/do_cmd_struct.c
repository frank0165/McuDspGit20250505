/* 
 * MCU与外部交互 系统信息初始化功能
 * Copyright 2022-2023 Tauren Semiconductor.
 * Create data: 2023-9-19
 * auther: zhanglaipeng
 * email: laipeng.zhang@taurentech.net
 */

#include "do_api.h"
#include "sre_basic_typedef.h"
#include "ip_op.h"

// API_RUN_CTRL_CAT        func 0x0000_xxxx cata
DoOpCmdS g_funcCat0Para[RUN_CTRL_FUNC_NUM] = {
    // funcCat                  funNo                   inputParaNum    outputParaNum   timeOutMs
    {API_RUN_CTRL_CAT,          CHIP_RUN,               2,              0,              60 * 1000},
    {API_RUN_CTRL_CAT,          CHIP_TX_RUN,            0,              0,              60 * 1000},
    {API_RUN_CTRL_CAT,          CHIP_RX_RUN,            0,              0,              60 * 1000},
};

// API_PARA_INIT_CAT       func 0x0001_xxxx cata
DoOpCmdS g_funcCat1Para[PARA_INIT_FUNC_NUM] = {
    // funcCat                  funNo                   inputParaNum    outputParaNum   timeOutMs
    #if (CHIP_IS_BCDR == SRE_YES)
    {API_PARA_INIT_CAT,         CHIP_MODE_INIT,         35,             34,              1 * 100},
    {API_PARA_INIT_CAT,         DATAPATH_PARA_INIT,     19,             18,               1 * 100},
    #else
    {API_PARA_INIT_CAT,         CHIP_MODE_INIT,         5,              4,               1 * 100},
    {API_PARA_INIT_CAT,         DATAPATH_PARA_INIT,     4,              3,               1 * 100},
    #endif
    {API_PARA_INIT_CAT,         CALIB_PARA_INIT,        3,              2,               1 * 100},
};

// API_RESET_CTRL_CAT        func 0x0002_xxxx cata
DoOpCmdS g_funcCat2Para[RESET_CTRL_FUNC_NUM] = {
    // funcCat                  funNo                   inputParaNum    outputParaNum   timeOutMs
    {API_RESET_CTRL_CAT,        SIG_LANE_MODE_INIT,      3,              0,              5 * 1000},
    {API_RESET_CTRL_CAT,        LANE_SHUTDOWN,           33,              0,             1 * 200},
};

// API_ALRM_CTRL_CAT       func 0x0003_xxxx cata
DoOpCmdS g_funcCat3Para[ALRM_CTRL_NUM] = {
    // funcCat                  funNo                   inputParaNum    outputParaNum   timeOutMs
    {API_ALRM_CTRL_CAT,         ALRM_RPT_GET,           0,              1,              1 * 100},
    {API_ALRM_CTRL_CAT,         ALRM_FIX,               1,              0,              1 * 200},
};

// API_LPC_CTRL_CAT   func 0x0004_xxxx cata
DoOpCmdS g_funcCat4Para[LOWPOWER_CTRL_FUNC_NUM] = {
    // funcCat                  funNo                   inputParaNum    outputParaNum   timeOutMs
    {API_LPC_CTRL_CAT,          LOWPOWER_SET,           2,              0,              1 * 100},
};

// API_DFX_CTRL_CAT        func 0x0005_xxxx cata
DoOpCmdS g_funcCat5Para[DFX_CTRL_FUNC_NUM] = {
    // funcCat                  funNo                   inputParaNum    outputParaNum   timeOutMs
    {API_DFX_CTRL_CAT,          MCU_TICK_GET,           0,              1,              1 * 100},
    {API_DFX_CTRL_CAT,          IDLE_ERR_SET,           1,              5,              1 * 100},
    {API_DFX_CTRL_CAT,          VERSION_GET,            1,              9,              1 * 100},
    {API_DFX_CTRL_CAT,          RX_LANE_BER_GET,        4,              5,              1 * 100},
    {API_DFX_CTRL_CAT,          UART_DEBUG_EN,          2,              1,              1 * 100}
};

// API_DFX_CTRL_CAT        func 0x0006_xxxx cata
DoOpCmdS g_funcCat6Para[WAVE_CTRL_FUNC_NUM] = {
    // funcCat                  funNo                   inputParaNum    outputParaNum   timeOutMs
    {API_WAVE_CTRL_CAT,          TX_LUT_SET,           0,              1,              1 * 100},
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

/* 
 * 寄存器操作功能函数
 * Copyright 2022-2023 Tauren Semiconductor.
 * Create data: 2023-9-22
 * auther: zhanglaipeng
 * email: laipeng.zhang@taurentch.net
 */

#include "reg_op.h"
#include "sre_basic_typedef.h"
#include "sre_errcode.h"

#ifdef EXT_CTRL_MCU
UINT32 g_regMaxOpNum = 40;          // 与一次能传输多少内容有关
void fh_delay_us(uint32_t us);
VOID MCU_DelayUs(UINT32 us)
{
    fh_delay_us(us);
}

#if 0
const uint8_t g_dspFwBuff[] __attribute__((section(".ARM.__at_""0x08064C00"))) = {
#include "sre_fw.gd"
};
#endif

#endif

#ifdef _GCC_TOOLS_
UINT32 g_regMaxOpNum;
VOID I2C_RegisterWrite(UINT32 addr, UINT32 val) {}
VOID I2C_RegisterRead(UINT32 addr, UINT32 *val) {}
VOID I2C_RegisterWriteContinue(UINT32 addr, UINT32 *buff, UINT32 len) {}
VOID I2C_RegisterReadContinue(UINT32 addr, UINT32 *buff, UINT32 len) {}
VOID MCU_DelayUs(UINT32 us) {}
#endif


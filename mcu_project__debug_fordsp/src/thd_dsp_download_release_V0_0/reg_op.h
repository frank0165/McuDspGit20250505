/* 
 * 寄存器等功能
 * Copyright 2022-2023 Tauren Semiconductor.
 * Create data: 2023-9-22
 * auther: zhanglaipeng
 * email: laipeng.zhang@taurentch.net
 */

#ifndef _REG_OP_H_
#define _REG_OP_H_


#include "sre_basic_typedef.h"
#include "mailbox_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef EXT_CTRL_MCU
VOID MCU_DelayUs(UINT32 us);
extern UINT32 g_regMaxOpNum;
VOID dsp_fsl_reg_write(UINT32 reg, UINT32 val);
VOID dsp_fsl_reg_read(UINT32 reg, UINT32 *val);
VOID dsp_fsl_continue_write(UINT32 reg, UINT8 *buff, UINT32 buffLen);
VOID dsp_fsl_continue_read(UINT32 addr, UINT8 *Buff, UINT32 buffLen);
#define RegisterRead(val, reg) dsp_fsl_reg_read((UINT32)((UINTPTR)(&reg)), &(val))
#define RegisterWrite(reg, val) dsp_fsl_reg_write((UINT32)((UINTPTR)(&reg)), val)
#define RegisterWriteContinue(reg, buff, len) dsp_fsl_continue_write((UINT32)((UINTPTR)(reg)), (UINT8 *)buff, ((len) << 2))
#define RegisterReadContinue(reg, buff, len) dsp_fsl_continue_read((UINT32)((UINTPTR)(reg)), (UINT8 *)buff, ((len) << 2))
#else
    #ifdef _GCC_TOOLS_
        extern UINT32 g_regMaxOpNum;
        VOID I2C_RegisterWrite(UINT32 addr, UINT32 val);
        VOID I2C_RegisterRead(UINT32 addr, UINT32 *val);
        VOID I2C_RegisterWriteContinue(UINT32 addr, UINT32 *buff, UINT32 len);
        VOID I2C_RegisterReadContinue(UINT32 addr, UINT32 *buff, UINT32 len);
        #define RegisterRead(val, reg) I2C_RegisterRead((UINT32)((UINTPTR)(&reg) >> 2), &(val))
        #define RegisterWrite(reg, val) I2C_RegisterWrite((UINT32)((UINTPTR)(&reg) >> 2), val)
        #define RegisterWriteContinue(reg, buff, len) I2C_RegisterWriteContinue((UINT32)((UINTPTR)(reg) >> 2), buff, len)
        #define RegisterReadContinue(reg, buff, len) I2C_RegisterReadContinue((UINT32)((UINTPTR)(reg) >> 2), buff, len)
    #else
        #define RegisterRead(val, reg) (val) = (reg)
        #define RegisterWrite(reg, val) (reg) = (val)
        static inline VOID RegisterWriteContinue(volatile UINT32 *reg, UINT32 *buff, UINT32 len)
        {
            UINT32 wtCnt;
            for (wtCnt = 0; wtCnt < len; wtCnt++) {
                *reg = buff[wtCnt];
            }
        }
        static inline VOID RegisterReadContinue(volatile UINT32 *reg, UINT32 *buff, UINT32 len)
        {
            UINT32 rdCnt;
            for (rdCnt = 0; rdCnt < len; rdCnt++) {
                buff[rdCnt] = *reg;
            }
        }
    #endif
#endif
#define BYQIYUN_IP_BASE_ADDR     0x0

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

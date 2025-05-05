/* 
 * dsp操作功能声明
 * Copyright 2022-2023 Tauren Semiconductor.
 * Create data: 2023-9-22
 * auther: zhanglaipeng
 * email: laipeng.zhang@taurentch.net
 */

#ifndef _PUTU_OP_H_
#define _PUTU_OP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "sre_basic_typedef.h"
#include "do_api.h"

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
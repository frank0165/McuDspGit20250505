/* 
 * demo main 功能
 * Copyright 2024-2025 Tauren Semiconductor.
 * Create data: 2025-3-20
 * auther: zhanglaipeng
 */

#include "do_api.h"
#include "ip_op.h"
#include "sre_basic_typedef.h"

// 编译版本时需要添加编译选项定义 CHIP_TYPE数值
// 对应数值如下
// #define CHIP_IS_BCDRV100     0
// #define CHIP_IS_DSPV100      1
// #define CHIP_IS_BCDR201V100  2
// #define CHIP_IS_BCDRHS       3
// 如 定义CHIP_TYPE=0,表示为bcdr模式   定义CHIP_TYPE=1为qiyun芯片模式


extern UINT32 g_fwData[0x5c00];
#if (CHIP_IS_BCDR == SRE_YES)
VOID LaneRateParaSet(SystemParaInitS *lanePara)
{
    UINT32 i;
    lanePara->isCfgFlag = PARA_SET_FLAG;
    lanePara->rxEnableMask = 0x00ff00ff;        // lane0- 15 低速lane  lane16-31 高速lane
    lanePara->txEnableMask = 0x00ff00ff;        // lane0- 15 低速lane  lane16-31 高速lane
    for (i = 0; i < 2; i++) {
        lanePara->laneModeCfg[i].bits.rxRate[0].bits.dataWidth = DATA_BIT_WIDTH_8;
        lanePara->laneModeCfg[i].bits.rxRate[0].bits.rateMode = LANE_MODE_1P244;
        lanePara->laneModeCfg[i].bits.rxRate[1].bits.dataWidth = DATA_BIT_WIDTH_8;
        lanePara->laneModeCfg[i].bits.rxRate[1].bits.rateMode = LANE_MODE_2P488;
        lanePara->laneModeCfg[i].bits.rxRate[2].bits.dataWidth = 0;
        lanePara->laneModeCfg[i].bits.rxRate[2].bits.rateMode = LANE_MODE_INVALID;    // 该速率无效
        lanePara->laneModeCfg[i].bits.txRate.bits.dataWidth = DATA_BIT_WIDTH_8;
        lanePara->laneModeCfg[i].bits.txRate.bits.rateMode = LANE_MODE_2P488;
    }
}
#endif
#if (CHIP_IS_DSP == SRE_YES)
VOID LaneRateParaSet(SystemParaInitS *lanePara)
{
    lanePara->isCfgFlag = PARA_SET_FLAG;
    lanePara->rxEnableMask = 0x00000003;        // bit0 host rx bit1 line rx
    lanePara->txEnableMask = 0x00000003;        // bit0 host tx bit1 line tx
    // host cfg
    lanePara->laneModeCfg[0].hostBits.rxRate.bits.dataWidth = DATA_BIT_WIDTH_32;
    lanePara->laneModeCfg[0].hostBits.rxRate.bits.rateMode = LANE_MODE_24P88_NRZ;
    lanePara->laneModeCfg[0].hostBits.txRate[0].bits.dataWidth = DATA_BIT_WIDTH_32;
    lanePara->laneModeCfg[0].hostBits.txRate[0].bits.rateMode = LANE_MODE_24P88_NRZ;
    lanePara->laneModeCfg[0].hostBits.txRate[1].bits.dataWidth = DATA_BIT_WIDTH_64;
    lanePara->laneModeCfg[0].hostBits.txRate[1].bits.rateMode = LANE_MODE_49P76_NRZ;
    lanePara->laneModeCfg[0].hostBits.txRate[2].bits.dataWidth = 0;
    lanePara->laneModeCfg[0].hostBits.txRate[2].bits.rateMode = LANE_MODE_INVALID;    // 该速率无效
    // line cfg
    lanePara->laneModeCfg[1].lineBits.rxRate[0].bits.dataWidth = DATA_BIT_WIDTH_32;
    lanePara->laneModeCfg[1].lineBits.rxRate[0].bits.rateMode = LANE_MODE_24P88_NRZ;
    lanePara->laneModeCfg[1].lineBits.rxRate[1].bits.dataWidth = DATA_BIT_WIDTH_64;
    lanePara->laneModeCfg[1].lineBits.rxRate[1].bits.rateMode = LANE_MODE_49P76_NRZ;
    lanePara->laneModeCfg[1].lineBits.rxRate[2].bits.dataWidth = 0;
    lanePara->laneModeCfg[1].lineBits.rxRate[2].bits.rateMode = LANE_MODE_INVALID;    // 该速率无效
    lanePara->laneModeCfg[1].lineBits.txRate.bits.dataWidth = DATA_BIT_WIDTH_32;
    lanePara->laneModeCfg[1].lineBits.txRate.bits.rateMode = LANE_MODE_24P88_NRZ;
}
#endif
int main(void)
{
    UINT32 ret;
    FwSecS *fwManage = (FwSecS *)g_fwData;
    UINT32 inputPara[35];
    UINT32 outputPara[5];
    SystemParaInitS *lanePara = (SystemParaInitS *)inputPara;
    UINT32 finish;
    SRE_DownloadFirmware(fwManage);
    // 每条lane模式初始化
    LaneRateParaSet(lanePara);
    // 下发每条lane的工作模式，阻塞式等待指令完成，ret为错误码信息，若为0则表示成功
    ret = SRE_CmdSend(API_PARA_INIT_CAT, CHIP_MODE_INIT, inputPara, outputPara, 1);
    if (ret != SRE_SUCCESS) {
        return ret;
    }
    // 下发开始运行指令，无需阻塞式等待，该执行在dsp芯片内运行时间较长，若阻塞式等待会影响片外mcu运行效率
    ret = SRE_CmdSend(API_RUN_CTRL_CAT, CHIP_RUN, inputPara, outputPara, 0);
    if (ret != SRE_SUCCESS) {
        return ret;
    }
    // 间断式读取之前下发的指令是否完成，finish为1表示之前指令执行完成，ret为返回的错误码，0表示无错误，若finish为0，则表示，未完成相应指令，返回值为0
    do {
        ret = SRE_GetCmdResult(API_RUN_CTRL_CAT, CHIP_RUN, outputPara, &finish);
        if (ret != SRE_SUCCESS) {
            return ret;
        }
    } while (finish == 0);

    return 0;
}
 
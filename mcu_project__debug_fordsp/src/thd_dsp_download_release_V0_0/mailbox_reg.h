/*
 * DSP_MAILBOX reg struct define
 * CopyRight 2024-2024 Tauren Semiconductor
 * Auther: zhanglaipeng
 * email : laipeng.zhang@taurentech.net
 * Create data: 2024-8-9
 */

#ifndef _MAILBOX_REG_H_
#define _MAILBOX_REG_H_

#include "sre_basic_typedef.h"
// #include "reg_basic_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********reg bit fild def*****************************************************************/
/***********regBlock DSP_MAILBOX member: rptMcuSta def offset: 0x48**************************/
typedef union RptMcuStaS {
    UINT32 val;
    struct {
        RO UINT32 rptHaltFromTile0: 1;                // 0:0    0x0
        RO UINT32 rptWfiFromTile0: 1;                 // 1:1    0x0
        RO UINT32 rptCeaseFromTile0: 1;               // 2:2    0x0
        RO UINT32 rptDebugFromTile0: 1;               // 3:3    0x0
        RO UINT32 rsv0: 28;                           // 31:4   0x0
    } bits;
} RptMcuStaS;

/***********regBlock DSP_MAILBOX member: cfgMcuBusMem def offset: 0x4a***********************/
typedef union CfgMcuBusMemS {
    UINT32 val;
    struct {
        RW UINT32 cfgMemDslplv: 1;                    // 0:0    0x1        sram参数配置，BCDR_MCU侧MEM共用同一套配置
        RW UINT32 cfgMemRtsel: 2;                     // 2:1    0x2        sram参数配置，BCDR_MCU侧MEM共用同一套配置
        RW UINT32 cfgMemWtsel: 2;                     // 4:3    0x1        sram参数配置，BCDR_MCU侧MEM共用同一套配置
        RW UINT32 cfgMemWasen: 1;                     // 5:5    0x1        sram参数配置，BCDR_MCU侧MEM共用同一套配置
        RW UINT32 cfgMemWassel: 2;                    // 7:6    0x1        sram参数配置，BCDR_MCU侧MEM共用同一套配置
        RO UINT32 rsv0: 24;                           // 31:8   0x0
    } bits;
} CfgMcuBusMemS;

/***********regBlock DSP_MAILBOX member: cfgRiscvMem def offset: 0x4b************************/
typedef union CfgRiscvMemS {
    UINT32 val;
    struct {
        RW UINT32 cfgBusMemShutDown: 1;               // 0:0    0x0        sram低功耗配置，bus_mem使用
        RW UINT32 cfgBusMemDeepSleep: 1;              // 1:1    0x0        sram低功耗配置，bus_mem使用
        RW UINT32 cfgRiscvMem0ShutDown: 1;            // 2:2    0x0        sram低功耗配置，riscv_mem0使用
        RW UINT32 cfgRiscvMem0DeepSleep: 1;           // 3:3    0x0        sram低功耗配置，riscv_mem0使用
        RW UINT32 cfgRiscvMem1ShutDown: 1;            // 4:4    0x0        sram低功耗配置，riscv_mem1使用
        RW UINT32 cfgRiscvMem1DeepSleep: 1;           // 5:5    0x0        sram低功耗配置，riscv_mem1使用
        RO UINT32 rsv0: 26;                           // 31:6   0x0
    } bits;
} CfgRiscvMemS;

#define MAILBOX_NUM                   0x40
/***********reg def**************************************************************************/
typedef struct MailboxRegTbl {
    RW volatile UINT32 mailbox[MAILBOX_NUM];                     // 0x0    0x00       与外部主控消息交互接口
    RW volatile UINT32 mcuBootSta;                               // 0x40   0x00       mcu运行状态寄存器
    RW volatile UINT32 sramRemapAddr;                            // 0x41   0x00       SRAM指向的地址
    RW volatile UINT32 sramRemapData;                            // 0x42   0x00       sram读写的数据
    RW volatile UINT32 downloafdFwEn;                            // 0x43   0x00       mcu下载fw模式使能1'd0:mcu正常运行fw模式1'd1:使能下载fw模式
    RW volatile UINT32 mcuEnable;                                // 0x44   0x00       mcu使能控制1'd0:mcu处于复位状态1'd1:使能
    RW volatile UINT32 mcuRtcDiv;                                // 0x45   0x20       mcu RTC分频
    RW volatile UINT32 extInterruptsEnMask;                      // 0x46   0x00       中断信号是否输入使能
    RO volatile UINT32 extInterrupts;                            // 0x47   0x00       外部中断源输入
    RO volatile UINT32 rptMcuSta;                                // 0x48   0x00       
    RW volatile UINT32 apbBypassArbEn;                           // 0x49   0x00       1'b1:不经过仲裁总线使能控制    1'b0:经过仲裁总线
    RW volatile UINT32 cfgMcuBusMem;                             // 0x4a   0x6d       
    RW volatile UINT32 cfgRiscvMem;                              // 0x4b   0x00       
} MailboxRegTbl;

#ifdef __cplusplus
}
#endif
#endif

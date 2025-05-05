/* 
 * 操作运行错误码列表
 * Copyright 2022-2022 Tauren Semiconductor.
 * Create data: 2022-8-3
 * auther:
 */
#ifndef _SRE_ERRCODE_H_
#define _SRE_ERRCODE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MODULE_SHIFT 24
#define ERR_CODE(module, num) ((module << MODULE_SHIFT) | (num))

#define ERROR_CODE_MCU 0x11
#define ERR_CODE_MCU_MODULE(num)                ERR_CODE(ERROR_CODE_MCU, num)

#define RES_CALI_INT_TIMEOUT                    ERR_CODE_MCU_MODULE(0)             // 0x11000000 电阻校准超时
#define TASK_LIST_IS_FULL                       ERR_CODE_MCU_MODULE(1)             // 0x11000001 任务队列 已满
#define TASK_FUNC_IS_NULL                       ERR_CODE_MCU_MODULE(2)             // 0x11000002 任务函数为空
#define TIM_FUNC_IS_NULL                        ERR_CODE_MCU_MODULE(3)             // 0x11000003 注册的函数指针为空
#define TIM_INTER_ERR                           ERR_CODE_MCU_MODULE(4)             // 0x11000004 注册的时间间隔不为基本时间间隔整数倍
#define TIM_FUNC_IS_FULL                        ERR_CODE_MCU_MODULE(5)             // 0x11000005 中断处理函数队列已满
#define FIND_FUNC_NUM_ERR                       ERR_CODE_MCU_MODULE(6)             // 0x11000006 函数编号错误，函数编号越界
#define FIND_FUNC_CATALOG_ERR                   ERR_CODE_MCU_MODULE(7)             // 0x11000007 函数分类失败，未找到对应编号分类
#define PLL_WAIT_LOCK_OVERTIME_ERR              ERR_CODE_MCU_MODULE(8)             // 0x11000008 等待PLL lock超时
#define PLL_WAIT_CDR_LOCK_OVERTIME_ERR          ERR_CODE_MCU_MODULE(9)             // 0x11000009 等待PLL CDR lock超时
#define PLL_FRE_NOT_MATCH_ERR                   ERR_CODE_MCU_MODULE(0xA)           // 0x1100000a pll 频率不匹配
#define CLKPATH_CFG_ERROR                       ERR_CODE_MCU_MODULE(0xB)           // 0x1100000B RX clkpath 配置异常
#define LANE_MODE_CFG_OVER_ERROR                ERR_CODE_MCU_MODULE(0xC)           // 0x1100000C MODE 配置异常
#define LANE_MODE_SPD_ERROR                     ERR_CODE_MCU_MODULE(0xD)           // 0x1100000d MODE 速率配置异常
#define LANE_MODE_VITWIDTH_ERROR                ERR_CODE_MCU_MODULE(0xE)           // 0x1100000E LANE BIT WIDTH 配置异常
#define LANE_MODE_LOWSPD_ERROR                  ERR_CODE_MCU_MODULE(0xF)           // 0x1100000F 低速lane配置成高速异常
#define LANE_IDX_ERROR                          ERR_CODE_MCU_MODULE(0x10)          // 0x11000010 lane idx错误
#define LANE_RESETERROR                         ERR_CODE_MCU_MODULE(0x11)          // 0x11000011 lane reset错误,当前lane处于运行态
#define ENDFUNC_APPLY_ERROR                     ERR_CODE_MCU_MODULE(0x12)          // 0x11000012 idle任务查找失败
#define SHUTDOWN_LANENUM_ERROR                  ERR_CODE_MCU_MODULE(0x13)          // 0x11000013 lane num配置错误
#define RX_INTF_CALIB_WAIT_TIMEOUT              ERR_CODE_MCU_MODULE(0x14)          // 0x11000014 lane slicer校准等待超时
#define RX_INTF_CALIB_NOT_CONV                  ERR_CODE_MCU_MODULE(0x15)          // 0x11000015 lane slicer校准不收敛
#define RX_VGA_CALIB_WAIT_TIMEOUT               ERR_CODE_MCU_MODULE(0x16)          // 0x11000016 lane VGA校准等待超时
#define RX_PRBS_CHECK_FIND_SEED_TIMEOUT         ERR_CODE_MCU_MODULE(0x17)          // 0x11000017 rx lane prbs查找seed超时告警
#define RX_EQ_ADAPT_TIMEOUT                     ERR_CODE_MCU_MODULE(0x18)          // 0x11000018 rx eq 自适应收敛超时
#define RX_EQ_ADAPT_OVERFLOW_ALM                ERR_CODE_MCU_MODULE(0x19)          // 0x11000019 rx eq 自适应溢出告警
#define BCDR_USE_ERR_GPLL                       ERR_CODE_MCU_MODULE(0x1A)          // 0x1100001A GPLL全低功耗异常
#define REG_OP_FUNC_IS_NULL                     ERR_CODE_MCU_MODULE(0x1B)          // 0x1100001B 寄存器操作函数为空
#define ERR_WAITFOR_RSP_TIMEOUT                 ERR_CODE_MCU_MODULE(0x1C)          // 0x1100001C 指令等待超时
#define ERR_OUTPARA_IS_NULL                     ERR_CODE_MCU_MODULE(0x1D)          // 0x1100001D 出参指针为空
#define ERR_INPARA_IS_NULL                      ERR_CODE_MCU_MODULE(0x1e)          // 0x1100001e 入参指针为空
#define LANE_CFG_DISABLE_ERROR                  ERR_CODE_MCU_MODULE(0x1f)          // 0x1100001f 配置了未使能的lane的参数
#define ERR_NEXTFUNC_IS_NULL                    ERR_CODE_MCU_MODULE(0x20)          // 0x11000020 任务衔接函数为空
#define RX_PRBS_CHECKER_TIMEROUT                ERR_CODE_MCU_MODULE(0x21)          // 0x11000021 prbs checker done 超时
#define PRBS_PATTERN_ERROR                      ERR_CODE_MCU_MODULE(0x22)          // 0x11000022 prbs pattern 配置非法
#define PRBS_USER_RATE_MODE_ERROR               ERR_CODE_MCU_MODULE(0x23)          // 0x11000023 prbs user ratemode 非本lane的工作模式
#define RATE_PARA_FLUSH_FAILED                  ERR_CODE_MCU_MODULE(0x24)          // 0x11000024 从数字打rate参数失败
#define HPLL_LOCK_ERR                           ERR_CODE_MCU_MODULE(0x25)          // 0x11000025 hpll 失锁
#define CALIB_AFCDR_WHEN_CDR_UNLOCK             ERR_CODE_MCU_MODULE(0x26)          // 0x11000026 当cdr未锁时，进行after cdr calib
#define TX_PRBS_NOT_WORKING                     ERR_CODE_MCU_MODULE(0x27)          // 0x11000027 TX prbs未正常工作
#define SET_FLAG_ERR                            ERR_CODE_MCU_MODULE(0x28)          // 0x11000028 set 入参错误
#define LANETYPE_ERR                            ERR_CODE_MCU_MODULE(0x29)          // 0x11000029 lanetype错误
#define RATEMODE_ERR                            ERR_CODE_MCU_MODULE(0x2A)          // 0x1100002A ratemode错误


#define SOC_PLL_WAIT_LOCK_TIMEOUT               ERR_CODE_MCU_MODULE(0xF000)        // 0x1100F000 SOC pll 等待超时

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

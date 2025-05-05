
/******************************************************************************
*****

 * 文 件 名   : timer_common.h
 * 负 责 人   : fz
 * 创建日期   : 2023年4月12日
 * 文件描述   : timer通过接口
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

*******************************************************************************
****/


#ifndef _TIMER_COMMON_H_
#define _TIMER_COMMON_H_

#include "gd32e501.h"


/* delete by fz, 20250310, 原因:此处定时器只用调用，正式版本中不用到 */
#if 0
/*一般定时器，供计数、定时采样、更新等使用*/
#define COMMON_TIMER						TIMER13
#define RCU_COMMON_TIMER					RCU_TIMER13
#define COMMON_TIMER_IRQn					TIMER13_IRQn
#define COMMON_TIMER_IRQHandler			TIMER13_IRQHandler
#endif

/* delete end by fz, 20250310 */

/*****************************************************************************
 * 函 数 名  : timer_process_init
 * 负 责 人  : fz
 * 创建日期  : 2023年7月20日
 * 函数功能  : 定时器处理过程初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void timer_process_init(void);

//void timer_trigger_config_init(void);

//void timer_counter_config_init(void);

#endif
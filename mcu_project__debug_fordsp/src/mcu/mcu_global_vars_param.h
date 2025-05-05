#ifndef _MCU_GLOBAL_VARS_PARAM_
#define _MCU_GLOBAL_VARS_PARAM_

#include "gd32e501.h"

typedef struct _GLOBAL_VARS_PARAM_
{
	/* add by fz, 20250225, 原因:升级标识 */
	uint8_t g_update_process_flag;
	uint8_t g_50g_ddm_sw_auto_process_flag;
	
	uint8_t g_10g_ddm_sw_auto_process_flag;
	
	uint8_t g_1g_ddm_sw_auto_process_flag;
	
	uint8_t g_ddm_sw_auto_process_flag;

    /*trigger触发次数*/
    uint32_t g_trigger_count;


	uint32_t g_sys_tick_period;

/* add by fz, 20250220, 原因:执行pid算法时的时间间隔 */
	uint32_t g_tec_pid_calc_ms_task;

/* add by fz, 20250212, 原因:用于ddm轮询任务 */
	uint32_t g_ddm_process_ms_task;

/* add by fz, 20250212, 原因:用于打印检查任务 */
	uint32_t g_check_print_ms_task;

    uint32_t g_dsp_fw_ticks_ret;
    uint32_t g_dsp_fw_version_ret;  
    uint32_t g_i2c_exception_irq_status_counter;
	
}GLOBAL_VARS_PARAM __attribute__((aligned(4)));


extern volatile GLOBAL_VARS_PARAM g_mcu_vars_param;



/*定时器ms(毫秒计数)*/
//#define MCU_TIMER_MS_PERIOD				g_mcu_vars_param.g_timer_iterrupt_period


/*定时器sec(秒计数)*/
//#define MCU_TIMER_SECS_PERIOD				(MCU_TIMER_MS_PERIOD / 1000)

/*系统定时器计数*/
/*系统ms 毫秒*/
#define MCU_SYSTEM_MS_PERIOD					g_mcu_vars_param.g_sys_tick_period

/*系统secs 秒*/
#define MCU_SYSTEM_SECS_PERIOD					(MCU_SYSTEM_MS_PERIOD / 1000)


#define TEC_PID_CALC_MS_TASK					g_mcu_vars_param.g_tec_pid_calc_ms_task


#define DDM_PROCESS_MS_TASK			g_mcu_vars_param.g_ddm_process_ms_task


#define PRINT_CHECK_MS_TASK			g_mcu_vars_param.g_check_print_ms_task


/*****************************************************************************
 * 函 数 名  : global_vars_param_init
 * 负 责 人  : fz
 * 创建日期  : 2025年2月21日
 * 函数功能  : 初始化全局变量
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
void global_vars_param_init();



#endif
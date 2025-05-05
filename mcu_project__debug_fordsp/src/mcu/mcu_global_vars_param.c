
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcu_global_vars_param.h"

/*************************************************************************
* 变量功能：mcu中定义全局变量封装成结构体
* 取值范围：mcu中定义的全局变量
* 注意事项：无
*************************************************************************/
volatile  GLOBAL_VARS_PARAM g_mcu_vars_param;


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
void global_vars_param_init()
{	
	/* add by fz, 20250225, 原因:默认是不升极 */
	
	g_mcu_vars_param.g_update_process_flag = RESET;
	g_mcu_vars_param.g_50g_ddm_sw_auto_process_flag = RESET;
	g_mcu_vars_param.g_10g_ddm_sw_auto_process_flag = RESET;
	g_mcu_vars_param.g_1g_ddm_sw_auto_process_flag = RESET;
	g_mcu_vars_param.g_ddm_sw_auto_process_flag = SET;


	g_mcu_vars_param.g_sys_tick_period = 0;

	/* add by fz, 20250220, 原因:执行pid算法时的时间间隔 */
	g_mcu_vars_param.g_tec_pid_calc_ms_task = 0;

	/* add by fz, 20250212, 原因:用于ddm轮询任务 */
	g_mcu_vars_param.g_ddm_process_ms_task = 0;

	/* add by fz, 20250212, 原因:用于打印检查任务 */
	g_mcu_vars_param.g_check_print_ms_task = 0;  

    g_mcu_vars_param.g_i2c_exception_irq_status_counter = 0;
	return;
	
}

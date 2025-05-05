/***********************************************************************************

 * 文 件 名   : tec_data_type.h
 * 负 责 人   : fangzhe
 * 创建日期   : 2025年3月23日
 * 文件描述   : 定义tec的数据结构
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#ifndef _TEC_DATA_TYPE_H_
#define _TEC_DATA_TYPE_H_

#include "gd32e501.h"
#include "user_config.h"

typedef struct _TEC_GLOBAL_VARS_PARAM_
{
	/*************************************************************************
	* 变量功能：tec的ctl的初始值工作电压
	* 取值范围：初始值为1.25v;依据SGM1296芯片手册，1.25v时,tec几乎不工作
	* 注意事项：无
	*************************************************************************/
	float g_ctl_voltage_set;


	/*************************************************************************
	* 变量功能：tec 的自动处理开关 :读取热敏电阻电压、温度等
	* 取值范围：SET or RESET
	* 注意事项：对应虚拟寄存器:TEC_AUTO_REG,现在没有用到
	*************************************************************************/
	//uint8_t g_tec_auto_ctrl_flag;

	/*************************************************************************
	* 变量功能：tec process在main中处理开关
	* 取值范围：SET代表处理中；RESET代表关闭处理
	* 注意事项：无
	*************************************************************************/
	uint8_t g_tec_proc_flag;

	/*************************************************************************
	* 变量功能：tec的pid自动控制开关
	* 取值范围：SET or RESET
	* 注意事项：对应虚拟寄存器:TEC_CALC_CTRL_AUTO_REG
	*************************************************************************/
	uint8_t g_tec_calc_argum_auto_flag;



	/*************************************************************************
	* 变量功能：tec的ctl的需要锁定的目标温度 * 100
	* 取值范围：目标温度 * 100，为整型
	* 注意事项：无
	*************************************************************************/
	uint16_t g_tec_ctrl_temperautre_obj;

}TEC_GLOBAL_VARS_PARAM;

extern volatile TEC_GLOBAL_VARS_PARAM g_tec_vars_param;



#if defined(FH_IC_SGM41296_HARDWARE) && (FH_IC_SGM41296_HARDWARE == CFG_YES)

#include "sgm41296_tec.h"
#define TEC_CTL_DISABLE_VALUE		(SGM41296_CTL_ZERO_VOLTAGE)

#else

#error "not define TEC_CTL_DISABLE_VALUE"

#endif


/*ctl输出最大电压2*/
#define TEC_CTL_VOLTAGE_OUT_MAX			2

/*最小输出电压*/
#define TEC_CTL_VOLTAGE_OUT_MIN			0.45

/*变化的差值，float型*/
#define TEC_CTL_MAX_FLOAT_OFFSET			0.1

/*变化的差值 ,int型，TEC_CTL_MAX_FLOAT_OFFSET * 100*/
#define TEC_CTL_MAX_INT_OFFSET				10

/*目标温度50度，乘100*/
#define TEC_TEMP_OBJ				g_tec_vars_param.g_tec_ctrl_temperautre_obj//5000 

#endif


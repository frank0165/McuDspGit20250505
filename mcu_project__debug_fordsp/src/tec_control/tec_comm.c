/***********************************************************************************

 * 文 件 名   : tec_comm.c
 * 负 责 人   : fz
 * 创建日期   : 2023年5月18日
 * 文件描述   : tec控制
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/
#include <stdio.h>
#include <string.h>



#include "mcu_data_type.h"
#include "mcu_pin_type.h"
#include "mcu_system_comm.h"
#include "mcu_global_vars_param.h"
#include "tec_comm.h"
#include "i2c_comm.h"
#include "sff_8472.h"

#include "dac_comm.h"
#include "thermistor_rth.h"
#include "tec_driver.h"




/*************************************************************************
* 变量功能：tec的所用到的全局变量进行封装成结构体
* 取值范围：tec的所用到的全局变量
* 注意事项：无
*************************************************************************/
volatile TEC_GLOBAL_VARS_PARAM g_tec_vars_param;



/*****************************************************************************
 * 函 数 名  : tec_global_vars_init
 * 负 责 人  : fz
 * 创建日期  : 2025年2月21日
 * 函数功能  : 初始化tec中的全局变量
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 

*****************************************************************************/
void tec_global_vars_init()
{	

	/*************************************************************************
	* 变量功能：tec process在main中处理开关
	* 取值范围：SET代表处理中；RESET代表关闭处理
	* 注意事项：无
	*************************************************************************/
	g_tec_vars_param.g_tec_proc_flag = RESET;


	/*************************************************************************
	* 变量功能：tec的ctl的初始值工作电压
	* 取值范围：初始值为1.25v;依据SGM1296芯片手册，1.25v时,tec几乎不工作
	* 注意事项：无
	*************************************************************************/
	g_tec_vars_param.g_ctl_voltage_set = TEC_CTL_DISABLE_VALUE;




	/*************************************************************************
	* 变量功能：tec的pid自动控制开关
	* 取值范围：SET or RESET
	* 
	注意事项：对应虚拟寄存器:TEC_CALC_CTRL_AUTO_REG;在main函数中初始化时默认开启，
	最后初始化完了在tec_start_auto_adjust()启动
	*************************************************************************/
	g_tec_vars_param.g_tec_calc_argum_auto_flag = SET;//为保险还是默认开启



	/*************************************************************************
	* 变量功能：tec的ctl的需要锁定的目标温度 * 100
	* 取值范围：目标温度 * 100，为整型
	* 注意事项：无
	*************************************************************************/
	g_tec_vars_param.g_tec_ctrl_temperautre_obj = 5000;

}


/*****************************************************************************
 * 函 数 名  : tec_config_init
 * 负 责 人  : fz
 * 创建日期  : 2023年5月18日
 * 函数功能  : tec初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无。tec初始时，关闭en,sd,power

*****************************************************************************/
void tec_config_init(void)
{
	tec_global_vars_init();
	
	tec_device_init();
	
	return;
}







/*
tec_calc_auto_rth_temp:奇怪现象
uint16_t rth_temp_value改为uint32_t,则温度锁定就不准确
TEC_TEMP_OBJ换成uin32_t g_tec_ctrl_temperautre_obj,则温度锁定就不准确
*/

/*****************************************************************************
 * 函 数 名  : tec_calc_auto_rth_temp
 * 负 责 人  : fz
 * 创建日期  : 2023年7月19日
 * 函数功能  : tec自动温度调节
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void tec_calc_auto_rth_temp(void)
{
	float rth_temp = 0.0; //实际温度[-40,125]，稍后会通过rth_temp_value映射到[0,165]
	float tmp = 0.0; // 当前温度与目标温度之间的差值
	uint16_t rth_temp_value = 0; /*温度的整数,保留两位小数，温度*100 */
	uint32_t int_tmp = 0;
	
	get_tec_therm_temperature(&rth_temp);

	/*[-40,125] => [0,165],+40且保留两位小数,避免负数计算*/
	rth_temp_value = (rth_temp + TEC_RTH_TEMP_ZERO)* CALC_FLOAT_PARAM;

	/*当前温度高于目标温度1℃时*/
	if(rth_temp_value > (TEC_TEMP_OBJ + 100 + TEC_RTH_TEMP_ZERO * CALC_FLOAT_PARAM))
	{
		//当前温度与目标温度之间的差值
		tmp = (rth_temp_value - TEC_TEMP_OBJ - TEC_RTH_TEMP_ZERO * CALC_FLOAT_PARAM);
		
		//原g_ctl_voltage_set -= tmp / CALC_FLOAT_PARAM * 0.01; /*1℃对应0.01 v*/
		//改成如下:g_ctl_voltage_set调节的幅度不能一次过大，否则tec芯片会锁住
		int_tmp = (tmp * 100/ CALC_FLOAT_PARAM * 0.01); //差值的实际值，没有×100的值，如1，而非100
		if(int_tmp > TEC_CTL_MAX_INT_OFFSET)
		{
			g_tec_vars_param.g_ctl_voltage_set -= TEC_CTL_MAX_FLOAT_OFFSET;
		}
		else
		{
			g_tec_vars_param.g_ctl_voltage_set -= tmp / CALC_FLOAT_PARAM * 0.01;
		}
	}
	else if(rth_temp_value < (TEC_TEMP_OBJ + 100 + TEC_RTH_TEMP_ZERO * CALC_FLOAT_PARAM))
	{
		/*当前温度低于目标温度1℃时*/
		tmp = (TEC_TEMP_OBJ - rth_temp_value + TEC_RTH_TEMP_ZERO * CALC_FLOAT_PARAM);
		
		//g_ctl_voltage_set += tmp / CALC_FLOAT_PARAM * 0.01;
		int_tmp = (tmp * 100/ CALC_FLOAT_PARAM * 0.01);
		if(int_tmp > TEC_CTL_MAX_INT_OFFSET)
		{
			g_tec_vars_param.g_ctl_voltage_set += TEC_CTL_MAX_FLOAT_OFFSET;
		}
		else
		{
			g_tec_vars_param.g_ctl_voltage_set += tmp / CALC_FLOAT_PARAM * 0.01;
		}
		
	}

	if(g_tec_vars_param.g_ctl_voltage_set > TEC_CTL_VOLTAGE_OUT_MAX)
	{
		g_tec_vars_param.g_ctl_voltage_set = TEC_CTL_VOLTAGE_OUT_MAX;
	}
	else if(g_tec_vars_param.g_ctl_voltage_set < TEC_CTL_VOLTAGE_OUT_MIN)
	{
		g_tec_vars_param.g_ctl_voltage_set = TEC_CTL_VOLTAGE_OUT_MIN;
	}
	
	tec_set_ctl_voltage(g_tec_vars_param.g_ctl_voltage_set);	
	
}


/*****************************************************************************
 * 函 数 名  : tec_save_ctl_temperature_value
 * 负 责 人  : fz
 * 创建日期  : 2024年2月21日
 * 函数功能  : 保存温度到default_config_value
 * 输入参数  : uint16_t temp
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 
 * 其    它  : 温度值temp实际上是保留了两位小数，实际用时要除以100才是真实温度

*****************************************************************************/
void tec_save_ctl_temperature_value(uint16_t temp)
{
	if(temp < 4000)
	{
		temp = 4000;
	}

	if(temp > 5500)
	{
		temp = 5500;
	}

	//TEC TARGET保存实际值
	uint8_t value[2];
	set_u16(value, temp);
	default_config_value[RX_TEC_TARGET_VALUE_HIGH] = value[0];
	default_config_value[RX_TEC_TARGET_VALUE_LOW] = value[1];
	
	return;

}


/*****************************************************************************
 * 函 数 名  : tec_process
 * 负 责 人  : fz
 * 创建日期  : 2023年5月18日
 * 函数功能  : 
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void tec_process()
{
#if 0
	float vctl= 0.0;
	//static uint32_t tec_pid_ticks = 0;

	/* add by fz, 20250310, 原因:通上位机配置vctl，主要是调试时使用 ；
		此处调试时可以加printf,不用时删掉
	*/


	if(SET == g_tec_vars_param.g_tec_proc_flag)
	{

		vctl = g_tec_vars_param.g_ctl_voltage_set;			
		tec_set_ctl_voltage(vctl);
				
		g_tec_vars_param.g_tec_proc_flag = RESET;	
	
	}
#endif

	if(SET == g_tec_vars_param.g_tec_calc_argum_auto_flag)
	{
		/*1秒钟锁定明显些*/		
		if(TEC_PID_CALC_MS_TASK > 1000)		{
			
			TEC_PID_CALC_MS_TASK = 0;
			tec_pid_calc_auto();
			
		}			
		
	}
	
}



/*****************************************************************************
 * 函 数 名  : tec_pid_calc_auto
 * 负 责 人  : fz
 * 创建日期  : 2023年6月6日
 * 函数功能  : pid算法
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void tec_pid_calc_auto()
{
	tec_calc_auto_rth_temp();
	tec_release_limit_refresh();
	return;
}

/*****************************************************************************
 * 函 数 名  : tec_start_auto_adjust
 * 负 责 人  : fz
 * 创建日期  : 2023年12月22日
 * 函数功能  : tec开始自动调节
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void tec_start_auto_adjust()
{
	g_tec_vars_param.g_tec_calc_argum_auto_flag = SET;
}



/*****************************************************************************
 * 函 数 名  : tec_set_default_mini_status
 * 负 责 人  : fz
 * 创建日期  : 2025年3月7日
 * 函数功能  : 设置功能最小默认状态
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 现在是做升级时设置tec为最小功能，停止tec的自动算法，

*****************************************************************************/
void tec_set_default_mini_status()
{	
	g_tec_vars_param.g_tec_calc_argum_auto_flag = 1;
	g_tec_vars_param.g_tec_proc_flag = SET;
    sgm41296_vtec_dac_ctl_set(SGM41296_CTL_ZERO_VOLTAGE);
}

/*****************************************************************************
 * 函 数 名  : tec_set_ctrl_temperature_obj
 * 负 责 人  : fz
 * 创建日期  : 2024年2月21日
 * 函数功能  : 设置目标渡
 * 输入参数  : float temp 实际温度值
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void tec_set_ctrl_temperature_obj(float temp)
{
	uint16_t value = temp * CALC_100TIMES;
	g_tec_vars_param.g_tec_ctrl_temperautre_obj = value;
	return;
}


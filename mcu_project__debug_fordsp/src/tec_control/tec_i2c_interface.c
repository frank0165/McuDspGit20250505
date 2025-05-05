/***********************************************************************************

 * 文 件 名   : tec_i2c_interface.c
 * 负 责 人   : fz
 * 创建日期   : 2025年1月16日
 * 文件描述   : tec的i2c接口实现
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#include <stdio.h>
#include <string.h>
#include "mcu_data_type.h"
#include "mcu_system_comm.h"
#include "thermistor_rth.h"
#include "tec_comm.h"
#include "tec_driver.h"
#include "tec_i2c_interface.h"
#include "mcu_global_vars_param.h"




/*****************************************************************************
 * 函 数 名  : tec_i2c_vtec_ctl_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2023年5月18日
 * 函数功能  : 上位机由i2c写ctl值给mcu
 * 输入参数  : uint8_t *pbuff,  写入的buff
 				uint32_t bufflen 写入的长度,
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 对应寄存器命令TEC_VTEC_CTL_REG

*****************************************************************************/
void tec_i2c_vtec_ctl_reg_write(uint8_t *pbuff,uint32_t bufflen)
{	
	
	uint16_t tmp_volt = 0;
	/*参数检查*/
	if(NULL == pbuff || bufflen < 3)
	{
		return;
	}

	/*检查对应的寄存器*/
	if(pbuff[0] != TEC_VTEC_CTL_REG)
	{
		return;
	}

	
	/*写入的ctl值*/
	tmp_volt = get_u16((pbuff + 1));

	g_tec_vars_param.g_ctl_voltage_set = tmp_volt;
	g_tec_vars_param.g_ctl_voltage_set /= CALC_FLOAT_PARAM;

	tec_set_ctl_voltage(g_tec_vars_param.g_ctl_voltage_set);
  
	/*启动处理,调用试时可以加打印*/
	//g_tec_vars_param.g_tec_proc_flag = SET;

	
}


/*****************************************************************************
 * 函 数 名  : tec_i2c_vtec_ctl_reg_read
 * 负 责 人  : fz
 * 创建日期  : 2023年12月4日
 * 函数功能  : 主从方式回读ctl的控制电压
 * 输入参数  : uint8_t regaddr   寄存器
 				uint32_t bufflen  要读取的长度
 * 输出参数  : uint8_t *pbuff     回读的内容
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void tec_i2c_vtec_ctl_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{	
	uint32_t value = 0;
	if(TEC_VTEC_CTL_REG != regaddr)
	{
		return;
	}
	
	if(NULL == pbuff || bufflen < 4)
	{
		return;
	}
	
	value = g_tec_vars_param.g_ctl_voltage_set * CALC_100TIMES;
	set_u32(pbuff, value);	

	return;
}



/*****************************************************************************
 * 函 数 名  : tec_i2_ctl_temperature_reg_read
 * 负 责 人  : fz
 * 创建日期  : 2023年6月6日
 * 函数功能  : 上位读取热敏电阻的温度电压(读取的采样电压，传给上位机，
 				上位机计算温度
 * 输入参数  :	uint8_t regaddr  工作寄存器
 				uint32_t bufflen 读取的长度
 * 输出参数  : uint8_t *pbuff		读取的数据
 * 返 回 值  : 无
 * 调用关系  : 
 * 其    它  : 寄存器TEC_CTL_TEMP

*****************************************************************************/
void tec_i2_ctl_temperature_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
	/*参数初始化*/
	uint32_t value = 0;
	float temp_vol = 0.0;
	uint32_t tmp_len = 0;
	
	/* add by fz, 20230625, 原因:参数合法值检查 */
	if(TEC_CTL_TEMP != regaddr)
	{
		return;
	}

	if(NULL == pbuff)
	{
		return;
	}

	if(bufflen < sizeof(uint32_t))
	{
		return;
	}	

	/* add by fz, 20250116, 原因:得到的实际温度应该+40,以正数传递 */
	get_tec_therm_temperature(&temp_vol);
	value = (temp_vol + TEC_RTH_TEMP_ZERO) * CALC_100TIMES;

	/*给pbuff赋值*/
	set_u32(pbuff,value);	
	
	
}





/*****************************************************************************
 * 函 数 名  : tec_i2c_calc_ctl_auto_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2023年5月23日
 * 函数功能  : i2c tec温度自动调控
 * 输入参数  : uint8_t *pbuff,
 				      uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : TEC_CALC_CTRL_AUTO_REG

*****************************************************************************/
void tec_i2c_calc_ctl_auto_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t reg = 0;

	/*参数检查*/
	if(NULL == pbuff || bufflen < 2)
	{
		return;
	}

	reg |= pbuff[0];

	if(reg != TEC_CALC_CTRL_AUTO_REG)
	{
		return;
	}

	g_tec_vars_param.g_tec_calc_argum_auto_flag = pbuff[1];	

	/*当不自动演算时，就设置为1.25 v*/
	if(RESET == g_tec_vars_param.g_tec_calc_argum_auto_flag)
	{
		g_tec_vars_param.g_ctl_voltage_set = TEC_CTL_DISABLE_VALUE;
		
		tec_set_ctl_voltage(g_tec_vars_param.g_ctl_voltage_set);
	}
		
}


/*****************************************************************************
 * 函 数 名  : tec_i2c_temperature_obj_write
 * 负 责 人  : fz
 * 创建日期  : 2023年5月23日
 * 函数功能  : 上位机i2c写目标温度给mcu
 * 输入参数  : uint8_t *pbuff,  buff数据
 				uint32_t bufflen  对应长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void tec_i2c_temperature_obj_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t reg = 0;

	/*参数检查*/
	if(NULL == pbuff || bufflen < 3)
	{
		return;
	}

	reg |= pbuff[0];
	if(reg != TEC_TEMP_OBJ_CFG_REG)
	{
		return;
	}

	g_tec_vars_param.g_tec_ctrl_temperautre_obj &= 0;
	g_tec_vars_param.g_tec_ctrl_temperautre_obj |= get_u16(&pbuff[1]);
	
	tec_save_ctl_temperature_value(g_tec_vars_param.g_tec_ctrl_temperautre_obj);

	return;
}


/*****************************************************************************
 * 函 数 名  : tec_xtec_value_reg_read
 * 负 责 人  : fz
 * 创建日期  : 2023年9月21日
 * 函数功能  : 
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void tec_xtec_value_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
	/*参数初始化*/
	uint8_t tmp[4] = {0,0,0,0};
	float voltage = 0.0;
	uint32_t value = 0;	
	
	/* add by fz, 20230625, 原因:参数合法值检查 */
	if(TEC_XTEC_VALUE_REG != regaddr)
	{
		return;
	}

	if(NULL == pbuff)
	{
		return;
	}

	if(bufflen < 4)
	{
		return;
	}	
	
	tec_get_xtec_voltage(&voltage);
	value = voltage * CALC_100TIMES;
	set_u32(pbuff, value);

	return;
	
}



void test_tec_i2c_rest_gpio_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t reg = 0;

	/*参数检查*/
	if(NULL == pbuff || bufflen < 3)
	{
		return;
	}

	reg |= pbuff[0];
	if(reg != TEST_TEC_RESET_REG)
	{
		return;
	}

	sgm1296_tec_init();
	return;
}


/***********************************************************************************

 * �� �� ��   : tec_comm.c
 * �� �� ��   : fz
 * ��������   : 2023��5��18��
 * �ļ�����   : tec����
 * ��Ȩ˵��   : Copyright (C) 2000-2023   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

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
* �������ܣ�tec�����õ���ȫ�ֱ������з�װ�ɽṹ��
* ȡֵ��Χ��tec�����õ���ȫ�ֱ���
* ע�������
*************************************************************************/
volatile TEC_GLOBAL_VARS_PARAM g_tec_vars_param;



/*****************************************************************************
 * �� �� ��  : tec_global_vars_init
 * �� �� ��  : fz
 * ��������  : 2025��2��21��
 * ��������  : ��ʼ��tec�е�ȫ�ֱ���
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : 

*****************************************************************************/
void tec_global_vars_init()
{	

	/*************************************************************************
	* �������ܣ�tec process��main�д�����
	* ȡֵ��Χ��SET�������У�RESET����رմ���
	* ע�������
	*************************************************************************/
	g_tec_vars_param.g_tec_proc_flag = RESET;


	/*************************************************************************
	* �������ܣ�tec��ctl�ĳ�ʼֵ������ѹ
	* ȡֵ��Χ����ʼֵΪ1.25v;����SGM1296оƬ�ֲᣬ1.25vʱ,tec����������
	* ע�������
	*************************************************************************/
	g_tec_vars_param.g_ctl_voltage_set = TEC_CTL_DISABLE_VALUE;




	/*************************************************************************
	* �������ܣ�tec��pid�Զ����ƿ���
	* ȡֵ��Χ��SET or RESET
	* 
	ע�������Ӧ����Ĵ���:TEC_CALC_CTRL_AUTO_REG;��main�����г�ʼ��ʱĬ�Ͽ�����
	����ʼ��������tec_start_auto_adjust()����
	*************************************************************************/
	g_tec_vars_param.g_tec_calc_argum_auto_flag = SET;//Ϊ���ջ���Ĭ�Ͽ���



	/*************************************************************************
	* �������ܣ�tec��ctl����Ҫ������Ŀ���¶� * 100
	* ȡֵ��Χ��Ŀ���¶� * 100��Ϊ����
	* ע�������
	*************************************************************************/
	g_tec_vars_param.g_tec_ctrl_temperautre_obj = 5000;

}


/*****************************************************************************
 * �� �� ��  : tec_config_init
 * �� �� ��  : fz
 * ��������  : 2023��5��18��
 * ��������  : tec��ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : �ޡ�tec��ʼʱ���ر�en,sd,power

*****************************************************************************/
void tec_config_init(void)
{
	tec_global_vars_init();
	
	tec_device_init();
	
	return;
}







/*
tec_calc_auto_rth_temp:�������
uint16_t rth_temp_value��Ϊuint32_t,���¶������Ͳ�׼ȷ
TEC_TEMP_OBJ����uin32_t g_tec_ctrl_temperautre_obj,���¶������Ͳ�׼ȷ
*/

/*****************************************************************************
 * �� �� ��  : tec_calc_auto_rth_temp
 * �� �� ��  : fz
 * ��������  : 2023��7��19��
 * ��������  : tec�Զ��¶ȵ���
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void tec_calc_auto_rth_temp(void)
{
	float rth_temp = 0.0; //ʵ���¶�[-40,125]���Ժ��ͨ��rth_temp_valueӳ�䵽[0,165]
	float tmp = 0.0; // ��ǰ�¶���Ŀ���¶�֮��Ĳ�ֵ
	uint16_t rth_temp_value = 0; /*�¶ȵ�����,������λС�����¶�*100 */
	uint32_t int_tmp = 0;
	
	get_tec_therm_temperature(&rth_temp);

	/*[-40,125] => [0,165],+40�ұ�����λС��,���⸺������*/
	rth_temp_value = (rth_temp + TEC_RTH_TEMP_ZERO)* CALC_FLOAT_PARAM;

	/*��ǰ�¶ȸ���Ŀ���¶�1��ʱ*/
	if(rth_temp_value > (TEC_TEMP_OBJ + 100 + TEC_RTH_TEMP_ZERO * CALC_FLOAT_PARAM))
	{
		//��ǰ�¶���Ŀ���¶�֮��Ĳ�ֵ
		tmp = (rth_temp_value - TEC_TEMP_OBJ - TEC_RTH_TEMP_ZERO * CALC_FLOAT_PARAM);
		
		//ԭg_ctl_voltage_set -= tmp / CALC_FLOAT_PARAM * 0.01; /*1���Ӧ0.01 v*/
		//�ĳ�����:g_ctl_voltage_set���ڵķ��Ȳ���һ�ι��󣬷���tecоƬ����ס
		int_tmp = (tmp * 100/ CALC_FLOAT_PARAM * 0.01); //��ֵ��ʵ��ֵ��û�С�100��ֵ����1������100
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
		/*��ǰ�¶ȵ���Ŀ���¶�1��ʱ*/
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
 * �� �� ��  : tec_save_ctl_temperature_value
 * �� �� ��  : fz
 * ��������  : 2024��2��21��
 * ��������  : �����¶ȵ�default_config_value
 * �������  : uint16_t temp
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : 
 * ��    ��  : �¶�ֵtempʵ�����Ǳ�������λС����ʵ����ʱҪ����100������ʵ�¶�

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

	//TEC TARGET����ʵ��ֵ
	uint8_t value[2];
	set_u16(value, temp);
	default_config_value[RX_TEC_TARGET_VALUE_HIGH] = value[0];
	default_config_value[RX_TEC_TARGET_VALUE_LOW] = value[1];
	
	return;

}


/*****************************************************************************
 * �� �� ��  : tec_process
 * �� �� ��  : fz
 * ��������  : 2023��5��18��
 * ��������  : 
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void tec_process()
{
#if 0
	float vctl= 0.0;
	//static uint32_t tec_pid_ticks = 0;

	/* add by fz, 20250310, ԭ��:ͨ��λ������vctl����Ҫ�ǵ���ʱʹ�� ��
		�˴�����ʱ���Լ�printf,����ʱɾ��
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
		/*1������������Щ*/		
		if(TEC_PID_CALC_MS_TASK > 1000)		{
			
			TEC_PID_CALC_MS_TASK = 0;
			tec_pid_calc_auto();
			
		}			
		
	}
	
}



/*****************************************************************************
 * �� �� ��  : tec_pid_calc_auto
 * �� �� ��  : fz
 * ��������  : 2023��6��6��
 * ��������  : pid�㷨
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void tec_pid_calc_auto()
{
	tec_calc_auto_rth_temp();
	tec_release_limit_refresh();
	return;
}

/*****************************************************************************
 * �� �� ��  : tec_start_auto_adjust
 * �� �� ��  : fz
 * ��������  : 2023��12��22��
 * ��������  : tec��ʼ�Զ�����
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void tec_start_auto_adjust()
{
	g_tec_vars_param.g_tec_calc_argum_auto_flag = SET;
}



/*****************************************************************************
 * �� �� ��  : tec_set_default_mini_status
 * �� �� ��  : fz
 * ��������  : 2025��3��7��
 * ��������  : ���ù�����СĬ��״̬
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ������������ʱ����tecΪ��С���ܣ�ֹͣtec���Զ��㷨��

*****************************************************************************/
void tec_set_default_mini_status()
{	
	g_tec_vars_param.g_tec_calc_argum_auto_flag = 1;
	g_tec_vars_param.g_tec_proc_flag = SET;
    sgm41296_vtec_dac_ctl_set(SGM41296_CTL_ZERO_VOLTAGE);
}

/*****************************************************************************
 * �� �� ��  : tec_set_ctrl_temperature_obj
 * �� �� ��  : fz
 * ��������  : 2024��2��21��
 * ��������  : ����Ŀ���
 * �������  : float temp ʵ���¶�ֵ
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void tec_set_ctrl_temperature_obj(float temp)
{
	uint16_t value = temp * CALC_100TIMES;
	g_tec_vars_param.g_tec_ctrl_temperautre_obj = value;
	return;
}


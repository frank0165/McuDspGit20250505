/***********************************************************************************

 * �� �� ��   : tec_i2c_interface.c
 * �� �� ��   : fz
 * ��������   : 2025��1��16��
 * �ļ�����   : tec��i2c�ӿ�ʵ��
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

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
 * �� �� ��  : tec_i2c_vtec_ctl_reg_write
 * �� �� ��  : fz
 * ��������  : 2023��5��18��
 * ��������  : ��λ����i2cдctlֵ��mcu
 * �������  : uint8_t *pbuff,  д���buff
 				uint32_t bufflen д��ĳ���,
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��Ӧ�Ĵ�������TEC_VTEC_CTL_REG

*****************************************************************************/
void tec_i2c_vtec_ctl_reg_write(uint8_t *pbuff,uint32_t bufflen)
{	
	
	uint16_t tmp_volt = 0;
	/*�������*/
	if(NULL == pbuff || bufflen < 3)
	{
		return;
	}

	/*����Ӧ�ļĴ���*/
	if(pbuff[0] != TEC_VTEC_CTL_REG)
	{
		return;
	}

	
	/*д���ctlֵ*/
	tmp_volt = get_u16((pbuff + 1));

	g_tec_vars_param.g_ctl_voltage_set = tmp_volt;
	g_tec_vars_param.g_ctl_voltage_set /= CALC_FLOAT_PARAM;

	tec_set_ctl_voltage(g_tec_vars_param.g_ctl_voltage_set);
  
	/*��������,������ʱ���ԼӴ�ӡ*/
	//g_tec_vars_param.g_tec_proc_flag = SET;

	
}


/*****************************************************************************
 * �� �� ��  : tec_i2c_vtec_ctl_reg_read
 * �� �� ��  : fz
 * ��������  : 2023��12��4��
 * ��������  : ���ӷ�ʽ�ض�ctl�Ŀ��Ƶ�ѹ
 * �������  : uint8_t regaddr   �Ĵ���
 				uint32_t bufflen  Ҫ��ȡ�ĳ���
 * �������  : uint8_t *pbuff     �ض�������
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

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
 * �� �� ��  : tec_i2_ctl_temperature_reg_read
 * �� �� ��  : fz
 * ��������  : 2023��6��6��
 * ��������  : ��λ��ȡ����������¶ȵ�ѹ(��ȡ�Ĳ�����ѹ��������λ����
 				��λ�������¶�
 * �������  :	uint8_t regaddr  �����Ĵ���
 				uint32_t bufflen ��ȡ�ĳ���
 * �������  : uint8_t *pbuff		��ȡ������
 * �� �� ֵ  : ��
 * ���ù�ϵ  : 
 * ��    ��  : �Ĵ���TEC_CTL_TEMP

*****************************************************************************/
void tec_i2_ctl_temperature_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
	/*������ʼ��*/
	uint32_t value = 0;
	float temp_vol = 0.0;
	uint32_t tmp_len = 0;
	
	/* add by fz, 20230625, ԭ��:�����Ϸ�ֵ��� */
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

	/* add by fz, 20250116, ԭ��:�õ���ʵ���¶�Ӧ��+40,���������� */
	get_tec_therm_temperature(&temp_vol);
	value = (temp_vol + TEC_RTH_TEMP_ZERO) * CALC_100TIMES;

	/*��pbuff��ֵ*/
	set_u32(pbuff,value);	
	
	
}





/*****************************************************************************
 * �� �� ��  : tec_i2c_calc_ctl_auto_reg_write
 * �� �� ��  : fz
 * ��������  : 2023��5��23��
 * ��������  : i2c tec�¶��Զ�����
 * �������  : uint8_t *pbuff,
 				      uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : TEC_CALC_CTRL_AUTO_REG

*****************************************************************************/
void tec_i2c_calc_ctl_auto_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t reg = 0;

	/*�������*/
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

	/*�����Զ�����ʱ��������Ϊ1.25 v*/
	if(RESET == g_tec_vars_param.g_tec_calc_argum_auto_flag)
	{
		g_tec_vars_param.g_ctl_voltage_set = TEC_CTL_DISABLE_VALUE;
		
		tec_set_ctl_voltage(g_tec_vars_param.g_ctl_voltage_set);
	}
		
}


/*****************************************************************************
 * �� �� ��  : tec_i2c_temperature_obj_write
 * �� �� ��  : fz
 * ��������  : 2023��5��23��
 * ��������  : ��λ��i2cдĿ���¶ȸ�mcu
 * �������  : uint8_t *pbuff,  buff����
 				uint32_t bufflen  ��Ӧ����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void tec_i2c_temperature_obj_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t reg = 0;

	/*�������*/
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
 * �� �� ��  : tec_xtec_value_reg_read
 * �� �� ��  : fz
 * ��������  : 2023��9��21��
 * ��������  : 
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void tec_xtec_value_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
	/*������ʼ��*/
	uint8_t tmp[4] = {0,0,0,0};
	float voltage = 0.0;
	uint32_t value = 0;	
	
	/* add by fz, 20230625, ԭ��:�����Ϸ�ֵ��� */
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

	/*�������*/
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


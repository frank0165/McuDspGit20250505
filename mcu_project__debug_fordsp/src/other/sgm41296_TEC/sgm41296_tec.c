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
#include "sgm41296_tec.h"
#include "mcu_pin_type.h"
#include "adc_sample_interface.h"
#include "dac_comm.h"
#include "i2c_comm.h"
#include "mcu_data_type.h"

#if defined(FH_IC_SGM41296_HARDWARE) && (FH_IC_SGM41296_HARDWARE == CFG_YES)




/*****************************************************************************
 * �� �� ��  : sgm41296_tec_config_init
 * �� �� ��  : fz
 * ��������  : 2023��5��18��
 * ��������  : sgm41296_tec��ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void sgm41296_tec_gpio_init()
{
	/*TEC SD���ƽ�Ĭ��Ϊ��*/
	gpio_mode_set(GPIO_TEC_SD_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_TEC_SD_PIN);
    gpio_output_options_set(GPIO_TEC_SD_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_TEC_SD_PIN);
	gpio_bit_set(GPIO_TEC_SD_PORT,GPIO_TEC_SD_PIN);	
	
	/*TEC EN���ƽ�Ĭ��Ϊ��*/
	gpio_mode_set(GPIO_TEC_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_TEC_EN_PIN);
    gpio_output_options_set(GPIO_TEC_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_TEC_EN_PIN);
	gpio_bit_set(GPIO_TEC_EN_PORT,GPIO_TEC_EN_PIN);

	return;
}

/*****************************************************************************
 * �� �� ��  : sgm41296_tec_get_xtec_voltage
 * �� �� ��  : fz
 * ��������  : 2025��1��13��
 * ��������  : ��ȡxtec�ĵ�ѹ
 * �������  : ��
 * �������  : float *voltage оƬ��xtec������ѹ
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : 

*****************************************************************************/
void sgm41296_tec_get_xtec_voltage(float *voltage)
{
	uint16_t data = 0;
	/* add by fz, 20230625, ԭ��:������� */
	if(NULL == voltage)
	{
		return;
	}

	/*������ѹ*/
	data = adc_dma_channel_sample_average(XTEC_ADC_IN);
	*voltage = MCU_REF_VOLTAGE / MCU_12BIT_RANGE * data;
	
	return;	
}

/*****************************************************************************
 * �� �� ��  : sgm41296_tec_get_therm_adc
 * �� �� ��  : fz
 * ��������  : 2023��7��19��
 * ��������  : ��ȡ����������¶ȵ�ADCֵ
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : �����¶ȵ�ADCֵ
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
uint32_t sgm41296_tec_get_therm_adc()
{	
	return adc_dma_channel_sample_average(TEC_THERM_ADC_IN);
		
}


/*****************************************************************************
 * �� �� ��  : sgm41296_tec_release_limit_refresh
 * �� �� ��  : fz
 * ��������  : 2023��12��4��
 * ��������  : sgm41296оƬ����������
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void sgm41296_tec_release_limit_refresh()
{
	uint32_t slave_address = I2C_TEC_DEV_ADDR;
	uint8_t reg = 0;
	uint8_t data = 0;
	uint8_t pbuffer[2] = {0,0};

	reg = 0x9;/*״̬�Ĵ���*/
	master_reg_1byte_size_read(slave_address, reg,&data, 1);

    if(1 == ((data >> 5) & 0x1) //VLIMΪ1���ѹ��������
		|| 1 == ((data >> 4) & 0x1) //ILIMΪ1�������������
		|| 0 == ((data >> 3) & 0x1)) //PWORΪ0����disable
	{

		/*���limt֮ǰ�ȶ��Ĵ�������*/
		memset(pbuffer,0,sizeof(pbuffer));
		reg = 0x0;//device control�Ĵ���
		data &= 0;

		/*�Ȼض�*/
		master_reg_1byte_size_read(slave_address, reg,&data, 1);

		data |= 0x03; /*Ҫ release��0011*/
		pbuffer[0] = reg;
		pbuffer[1] |= data;
		master_reg_byte_write(slave_address, pbuffer, 2);
	}
	
}


/*****************************************************************************
 * �� �� ��  : sgm1296_tec_init
 * �� �� ��  : fz
 * ��������  : 2023��5��18��
 * ��������  : sgm41296_tec��ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void sgm1296_tec_init(void)
{
	sgm41296_vtec_dac_ctl_set(SGM41296_CTL_ZERO_VOLTAGE);
	sgm41296_tec_gpio_init();
}


/*****************************************************************************
 * �� �� ��  : sgm41296_vtec_dac_ctl_set
 * �� �� ��  : fz
 * ��������  : 2023��5��18��
 * ��������  : 
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 
 #define TEC_VCTL_DAC_PERIPH		DAC0
#define TEC_VCTL_DAC_OUT			DAC_OUT_0

*****************************************************************************/
void sgm41296_vtec_dac_ctl_set(float voltage)
{
	uint16_t data = 0;
	data = voltage * MCU_12BIT_RANGE / MCU_REF_VOLTAGE;
	dac_data_set(TEC_VCTL_DAC_PERIPH, TEC_VCTL_DAC_OUT,DAC_ALIGN_12B_R,data);
	
}

#endif

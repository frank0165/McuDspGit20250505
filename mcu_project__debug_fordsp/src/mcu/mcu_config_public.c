#include <stdio.h>
#include <string.h>
#include "gd32e501_i2c.h"
#include "mcu_data_type.h"
#include "mcu_config_public.h"
#include "mcu_system_comm.h"

#if 0
extern void calibration_tx_i_50g_reg_write(uint8_t *pbuff,uint32_t bufflen);
extern void calibration_tx_pwr_50g_reg_write(uint8_t *pbuff,uint32_t bufflen);
extern void calibration_rx_pwr_50g_reg_write(uint8_t * pbuff, uint32_t bufflen);
extern void calibration_tx_i_10g_reg_write(uint8_t *pbuff,uint32_t bufflen);
extern void calibration_tx_pwr_10g_reg_write(uint8_t *pbuff,uint32_t bufflen);
extern void calibration_rx_pwr_10g_reg_write(uint8_t * pbuff, uint32_t bufflen);
extern void calibration_tx_i_1g_reg_write(uint8_t *pbuff,uint32_t bufflen);
extern void calibration_tx_pwr_1g_reg_write(uint8_t *pbuff,uint32_t bufflen);
extern void calibration_rx_pwr_1g_reg_write(uint8_t * pbuff, uint32_t bufflen);

#endif

/*****************************************************************************
 * �� �� ��  : rcu_config_init
 * �� �� ��  : fz
 * ��������  : 2023��4��24��
 * ��������  : rcu��ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  :  

*****************************************************************************/
void rcu_config_init(void)
{
   /* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_GPIOF);
   
    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);

    /* enable slave i2c clock */
    rcu_periph_clock_enable(RCU_I2C2);
    rcu_periph_clock_enable(RCU_I2C1);
    rcu_periph_clock_enable(RCU_I2C0);
	
	/* enable DAC clock */
	rcu_periph_clock_enable(RCU_DAC0);
	rcu_periph_clock_enable(RCU_DAC1);
	rcu_periph_clock_enable(RCU_DAC2);

	/*����DAC��ѹʱ*/
	rcu_periph_clock_enable(RCU_CFGCMP);

	/*
		��GD32E501��Ʒ��ADCʱ����APB2ʱ�Ӿ�2��4��6��8��Ƶ����AHBʱ�Ӿ�3��5��7��9��Ƶ
		��IRC28M��IRC28M/2ʱ�ӻ�ã�������ͨ���������üĴ���2(RCU_CFG2)��ADCSELλ��
		ѡ��ADCʱ��Դ�ġ�
	*/
	rcu_periph_clock_enable(RCU_ADC);

	 /* enable DMA clock */
    rcu_periph_clock_enable(RCU_DMA);

	/*����ADCʱ��*/
	rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);

	rcu_periph_clock_enable(RCU_CRC);
	
}


/*****************************************************************************
 * �� �� ��  : syscfg_config
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��23��
 * ��������  : mcu��ϵͳ��ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : 

*****************************************************************************/
void syscfg_config(void)
{
    syscfg_deinit();
    syscfg_vref_enable();
}






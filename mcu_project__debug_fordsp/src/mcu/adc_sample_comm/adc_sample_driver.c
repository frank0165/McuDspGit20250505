/***********************************************************************************

 * �� �� ��   : adc_sample_driver.c
 * �� �� ��   : fangzhe
 * ��������   : 2025��3��23��
 * �ļ�����   : adc sample��driver�ӿ�
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/
#include "adc_sample_driver.h"
#include "mcu_pin_type.h"


/*****************************************************************************
 * �� �� ��  : adc_gpio_init
 * �� �� ��  : fz
 * ��������  : 2023��5��19��
 * ��������  : 
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void adc_sample_gpio_init()
{
     /*�����������mcu_pin_type.h�Ѿ�ʹ�ú�����ˣ������ټӺ�����Ե�����
      ���ڿ�����ʲô���õİ취
    */

	/*******************mcu��tec�Ŀ���**********************************/
	/* add begin by fz, 20230518, ԭ��:Ӧ���������������
		
	*/
	/* add by fz, 20250113, ԭ��:sgm41296 ����*/
	gpio_mode_set(GPIO_THERM_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_THERM_AD_PIN);
	gpio_mode_set(GPIO_ITEC_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_ITEC_AD_PIN);

	/* add by fz, 20231011, ԭ��:�����¶� */
	gpio_mode_set(GPIO_CASE_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_CASE_AD_PIN);

	/*********************** ��ģ����ն�RSSI AD���� *******************/
	/* add by gqhuan, 20240902, ԭ��:��ģ����ն�RSSI AD���� */
	/* 50GPON */
	/* configure GPIO PC2 as ADC  */
  	gpio_mode_set(GPIO_RSSI_PORT_50G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_RSSI_AD_PIN_50G);

	/* 10GPON */
	/* configure GPIO PB3 as ADC  */
  	gpio_mode_set(GPIO_RSSI_PORT_10G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_RSSI_AD_PIN_10G);

	/* 1GPON */
	/* configure GPIO PA0 as ADC  */
  	gpio_mode_set(GPIO_RSSI_PORT_1G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_RSSI_AD_PIN_1G);

	/* add by fz, 20250304, ԭ��:50Gʹ��PB1����SGM41295��MON */	
	//dspû��sgm41295
//	gpio_mode_set(GPIO_LD_MON_PORT_50G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE,GPIO_LD_MON_PIN_50G);

}


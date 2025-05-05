/***********************************************************************************

 * �� �� ��   : adc_sample_comm.h
 * �� �� ��   : fz
 * ��������   : 2023��5��18��
 * �ļ�����   : adc config init
 * ��Ȩ˵��   : Copyright (C) 2000-2023   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#ifndef _ADC_SAMPLE_COMM_H_
#define _ADC_SAMPLE_COMM_H_

#include "gd32e501.h"


/*adc  ����ʱ��������ŷ���*/
/*����б仯ʱ��DMA�г�ʼ����numberҲҪ�б仯*/
typedef enum {
	TEC_RTH_TEMP_ADC_RANK_ID = 0,/*���������¶�adc*/
	XTEC_OUT_ADC_RANK_ID = 1,    /*VTEC����AD*/
	CASE_TEMP_ADC_RANK_ID = 2,	 /*�����¶�AD*/	
	//LD_50G_MON_ADC_RANK_ID = 3, /*sgm41295����MON*/
	ADC_REGULAR_RANK_SIZE = 3
}ADC_SAMPLE_REGULAR_RANK_IDX;


/* add by fz, 20250304, ԭ��:DMA����ʱֻʹ�� 
TEC_RTH_TEMP_ADC_RANK_ID,
XTEC_OUT_ADC_RANK_ID
CASE_TEMP_ADC_RANK_ID
����DMA��������ĳ���Ϊ3
*/
/* add by fz, 20250307, ԭ��:�������й�����һ��ʹ��dma��ʽ��ȡadc */
#define DMA_ADC_RANK_SIZE			ADC_REGULAR_RANK_SIZE

/* add by fz, 20250219, ԭ��:ע���������� */
typedef enum{
	RXPW_RSSI_ADC_50G_RANK_INSERT_ID = 0,	/*50G RSSI����*/
	RXPW_RSSI_ADC_10G_RANK_INSERT_ID = 1,	/*10G RSSI����*/
	RXPW_RSSI_ADC_1G_RANK_INSERT_ID = 2,	/*1G RSSI����*/
	ADC_INSERT_RANK_SIZE = 3
}ADC_SAMPLE_INSERT_RANK_IDX;

/* add by fz, 20250304, ԭ��:����ע���鳤��Ϊ3 */
#define ADC_SAMPLE_INSERT_RANK_SIZE			ADC_INSERT_RANK_SIZE


/*****************************************************************************
 * �� �� ��  : adc_sample_dma_regular_data_channel
 * �� �� ��  : fz
 * ��������  : 2023��10��18��
 * ��������  : DMA��ʽ����ͨ����ȡadc����
 * �������  : uint8_t ch  adc channel
 * �������  : ��
 * �� �� ֵ  : adc
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
uint16_t adc_sample_dma_regular_data_channel(uint8_t ch);

/*****************************************************************************
 * �� �� ��  : adc_regular_channel_sample
 * �� �� ��  : fz
 * ��������  : 2025��3��4��
 * ��������  : �����鷽ʽ��ȡ����ֵ
 * �������  : uint8_t rank,
 				uint8_t channel
 * �������  : ��
 * �� �� ֵ  : ����ֵ
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
uint16_t adc_regular_channel_sample(uint8_t rank,uint8_t channel);




/*****************************************************************************
 * �� �� ��  : get_adc_inserted_channel_sample
 * �� �� ��  : fz
 * ��������  : 2023��12��1��
 * ��������  : ��ȡע�����һ�β���
 * �������  : uint8_t rank ע����:[0,3]
 				uint8_t channel ADC����ͨ��
 * �������  : ��
 * �� �� ֵ  : AD����ֵ
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
uint16_t get_adc_inserted_channel_sample(uint8_t rank,uint8_t channel);


/*****************************************************************************
 * �� �� ��  : adc_dma_config_init
 * �� �� ��  : fz
 * ��������  : 2023��10��18��
 * ��������  : ʹ��adcʱ,dma������
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : 

*****************************************************************************/
void adc_dma_config_init();

/*****************************************************************************
 * �� �� ��  : adc_sample_function_init
 * �� �� ��  : fz
 * ��������  : 2023��10��18��
 * ��������  : adc�������ܳ�ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void adc_sample_function_init();




#endif

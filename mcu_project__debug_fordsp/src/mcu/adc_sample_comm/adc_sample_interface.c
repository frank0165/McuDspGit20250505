/***********************************************************************************

 * �� �� ��   : adc_sample_interface.c
 * �� �� ��   : fangzhe
 * ��������   : 2025��3��23��
 * �ļ�����   : adc����ӿ�
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#include "adc_sample_interface.h"
#include "adc_sample_comm.h"
#include "adc_sample_driver.h"

/*****************************************************************************
 * �� �� ��  : adc_sample_init
 * �� �� ��  : fz
 * ��������  : 2023��5��19��
 * ��������  : ADC sample�ĳ�ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void adc_sample_init()
{	
	/* add begin by fz, 20230518, ԭ��:�������������ADC���� */
	adc_sample_gpio_init();
	adc_dma_config_init();
	adc_sample_function_init();

}



/*****************************************************************************
 * �� �� ��  : adc_inserted_channel_sample_average
 * �� �� ��  : fz
 * ��������  : 2023��12��1��
 * ��������  : ��ȡע�����ƽ��AD����
 * �������  :  uint8_t rank  ע��������:0-3
 				uint8_t channel ADC����ͨ��,����AD��PIN����
 * �������  : ��
 * �� �� ֵ  : ƽ������ֵ
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
uint16_t adc_inserted_channel_sample_average(uint8_t rank,uint8_t channel)
{
	uint32_t adc_raw = 0;
	uint32_t adc_avg = 0;
	uint8_t count = 12;  
	uint32_t ad_max = 0;
	uint32_t ad_min = 4096;
	uint32_t ad_temp = 0;	

	for(int i = 0;i < count;i++)
	{
		ad_temp = get_adc_inserted_channel_sample(rank,channel);
		
		if(ad_temp > ad_max)
		{
			ad_max = ad_temp;
		}
		if(ad_temp < ad_min)
		{
			ad_min = ad_temp;
		}
		adc_raw += ad_temp;
	}

	adc_avg = (adc_raw - ad_max - ad_min)/ (count - 2);
	return adc_avg;

}




/*****************************************************************************
 * �� �� ��  : adc_dma_channel_sample_average
 * �� �� ��  : fz
 * ��������  : 2023��12��1��
 * ��������  : ����DMA��ʽ��ȡ������Ĳ���ƽ��ֵ
 * �������  :uint8_t channel ����ΪADCͨ��:ADC_CHANNEL_x  x = 0...15
 * �������  : ��
 * �� �� ֵ  : ����ƽ��ֵ
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
uint16_t adc_dma_channel_sample_average(uint8_t channel)
{
    uint32_t adc_raw = 0;
    uint8_t degree = 3;  //���Ĵ������� 2^3
    for(int i = 0;i < (1 << degree);i++)
    {
        //��ȡADC����
        adc_raw += adc_sample_dma_regular_data_channel(channel);
        //fh_delay_us(100);
    }
    
    //����ѭ��8�ζ�ȡ,��� >>3λ���ǳ���8
    adc_raw >>= degree;
    return adc_raw;

}
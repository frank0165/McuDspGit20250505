/***********************************************************************************

 * 文 件 名   : adc_sample_interface.c
 * 负 责 人   : fangzhe
 * 创建日期   : 2025年3月23日
 * 文件描述   : adc对外接口
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#include "adc_sample_interface.h"
#include "adc_sample_comm.h"
#include "adc_sample_driver.h"

/*****************************************************************************
 * 函 数 名  : adc_sample_init
 * 负 责 人  : fz
 * 创建日期  : 2023年5月19日
 * 函数功能  : ADC sample的初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void adc_sample_init()
{	
	/* add begin by fz, 20230518, 原因:配置热敏电阻的ADC采样 */
	adc_sample_gpio_init();
	adc_dma_config_init();
	adc_sample_function_init();

}



/*****************************************************************************
 * 函 数 名  : adc_inserted_channel_sample_average
 * 负 责 人  : fz
 * 创建日期  : 2023年12月1日
 * 函数功能  : 获取注入组的平均AD采样
 * 输入参数  :  uint8_t rank  注入组的序号:0-3
 				uint8_t channel ADC采样通道,就是AD的PIN引脚
 * 输出参数  : 无
 * 返 回 值  : 平均采样值
 * 调用关系  : 外部接口
 * 其    它  : 无

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
 * 函 数 名  : adc_dma_channel_sample_average
 * 负 责 人  : fz
 * 创建日期  : 2023年12月1日
 * 函数功能  : 依据DMA方式获取规则组的采样平均值
 * 输入参数  :uint8_t channel 参数为ADC通道:ADC_CHANNEL_x  x = 0...15
 * 输出参数  : 无
 * 返 回 值  : 采样平均值
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
uint16_t adc_dma_channel_sample_average(uint8_t channel)
{
    uint32_t adc_raw = 0;
    uint8_t degree = 3;  //读的次数的幂 2^3
    for(int i = 0;i < (1 << degree);i++)
    {
        //读取ADC次数
        adc_raw += adc_sample_dma_regular_data_channel(channel);
        //fh_delay_us(100);
    }
    
    //这里循环8次读取,因此 >>3位就是除以8
    adc_raw >>= degree;
    return adc_raw;

}
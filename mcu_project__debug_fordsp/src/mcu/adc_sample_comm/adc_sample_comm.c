/***********************************************************************************

 * 文 件 名   : adc_sample_comm.c
 * 负 责 人   : fz
 * 创建日期   : 2023年5月18日
 * 文件描述   : adc config init
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <systick.h>
#include "adc_sample_comm.h"
#include "adc_sample_driver.h"
#include "mcu_data_type.h"
#include "mcu_pin_type.h"

#include "mcu_system_comm.h"



/*************************************************************************
* 变量功能：dma的AD采样值
* 取值范围：AD采样值
* 注意事项：无
*************************************************************************/
volatile uint16_t adc_dma_sample_value[DMA_ADC_RANK_SIZE];



/*****************************************************************************
 * 函 数 名  : adc_sample_dma_regular_data_channel
 * 负 责 人  : fz
 * 创建日期  : 2023年10月18日
 * 函数功能  : DMA方式依据通道获取adc数据
 * 输入参数  : uint8_t ch  adc channel
 * 输出参数  : 无
 * 返 回 值  : adc
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
uint16_t adc_sample_dma_regular_data_channel(uint8_t ch)
{
	ADC_SAMPLE_REGULAR_RANK_IDX rank_idx;
	
	switch(ch)
	{
		case TEC_THERM_ADC_IN:
		{
			rank_idx = TEC_RTH_TEMP_ADC_RANK_ID;
			break;
		}
		case XTEC_ADC_IN:
		{
			rank_idx = XTEC_OUT_ADC_RANK_ID;
			break;
		}
		case CASE_ADC_IN:
		{
			rank_idx = CASE_TEMP_ADC_RANK_ID;
			break;
		}
 #if 0
		case LD_50G_MON_ADC_IN:
		{
			rank_idx = LD_50G_MON_ADC_RANK_ID;
			break;
		}
#endif
		default:
		{
			return 0;
		}
	}

	return adc_dma_sample_value[rank_idx];
	
}


/*****************************************************************************
 * 函 数 名  : adc_regular_channel_sample
 * 负 责 人  : fz
 * 创建日期  : 2025年3月4日
 * 函数功能  : 规则组方式获取采样值
 * 输入参数  : uint8_t rank,
 				uint8_t channel
 * 输出参数  : 无
 * 返 回 值  : 采样值
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
uint16_t adc_regular_channel_sample(uint8_t rank,uint8_t channel)
{
	uint32_t run_us = 0;
	uint8_t cyl = 0;
	
    /* ADC regular channel config */
    adc_regular_channel_config(rank, channel, ADC_SAMPLETIME_55POINT5);
    /* ADC software trigger enable */
    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);

    /* wait the end of conversion flag */
  //  while(!adc_flag_get(ADC_FLAG_EOC));
  	run_us = CYCLE_DELAY_TIME_US;
	cyl = 0;		
	while_fun(!adc_flag_get(ADC_FLAG_EOIC),run_us,cyl);
	
    /* clear the end of conversion flag */
    adc_flag_clear(ADC_FLAG_EOC);
	
    /* return regular channel sample value */
    return (adc_regular_data_read());
}




/*****************************************************************************
 * 函 数 名  : adc_dma_config_init
 * 负 责 人  : fz
 * 创建日期  : 2023年10月18日
 * 函数功能  : 使用adc时,dma的配置
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 

*****************************************************************************/
void adc_dma_config_init()
{
	 /* ADC_DMA_channel configuration */
    dma_parameter_struct dma_data_parameter;	
	 
	for(uint32_t i = 0; i < DMA_ADC_RANK_SIZE;i++)
	{
		adc_dma_sample_value[i] &= 0; 
	}

/* add begin by fz, 20231129, 原因:规则通道AD采样 */
    /* ADC DMA_channel configuration ,
    注意!!!!:1)一定要依据芯片手册核对DMA与引脚是否对应上;
    2)规则组的个数与DMA的 dma_data_parameter.number要核对上
    adc_channel_length_config中的长度length要与dma_data_parameter.number
    匹配
    */
    dma_deinit(DMA_SAMPLE_REGULAR_CHANNEL);/*DMA有7个通道*/	
    
    /* initialize DMA single data mode */
    dma_data_parameter.periph_addr  = (uint32_t)(&ADC_RDATA);
    dma_data_parameter.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
    dma_data_parameter.memory_addr  = (uint32_t)(&adc_dma_sample_value);
    dma_data_parameter.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
    dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;
    dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_16BIT;  
    dma_data_parameter.direction    = DMA_PERIPHERAL_TO_MEMORY;

	//容易出错处，number的值与adc_dma_sample_value数组大小，规则组rank个数要仔细核对
    dma_data_parameter.number       = DMA_ADC_RANK_SIZE; 
    dma_data_parameter.priority     = DMA_PRIORITY_HIGH;
    dma_init(DMA_SAMPLE_REGULAR_CHANNEL, &dma_data_parameter);

    dma_circulation_enable(DMA_SAMPLE_REGULAR_CHANNEL);
  
    /* enable DMA channel */
    dma_channel_enable(DMA_SAMPLE_REGULAR_CHANNEL);

/* add end by fz, 20231129 */

	
}



/*****************************************************************************
 * 函 数 名  : adc_sample_function_init
 * 负 责 人  : fz
 * 创建日期  : 2023年10月18日
 * 函数功能  : adc采样功能初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/

#if 0
void adc_sample_function_init()
{
	/* add begin by fz, 20231129, 原因:规则通道 */
	adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);
	
	/* ADC scan function enable */
	adc_special_function_config(ADC_SCAN_MODE, ENABLE);
	adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, 
		ADC_EXTTRIG_REGULAR_NONE); 
	adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);

	/* ADC data alignment config */
	adc_data_alignment_config(ADC_DATAALIGN_RIGHT);

	/* ADC channel length config ,3个规则组*/
	adc_channel_length_config(ADC_REGULAR_CHANNEL, 3U);	
	
	/* ADC regular channel config */
	adc_regular_channel_config(TEC_RTH_TEMP_ADC_RANK_ID, TEC_THERM_ADC_IN, ADC_SAMPLETIME_55POINT5);
	adc_regular_channel_config(XTEC_OUT_ADC_RANK_ID, XTEC_ADC_IN, ADC_SAMPLETIME_55POINT5);
	adc_regular_channel_config(CASE_TEMP_ADC_RANK_ID, CASE_ADC_IN, ADC_SAMPLETIME_55POINT5);
	//adc_regular_channel_config(RXPW_RSSI_ADC_50G_RANK_ID, RSSI_ADC_IN_50G, ADC_SAMPLETIME_55POINT5);
	//adc_regular_channel_config(RXPW_RSSI_ADC_10G_RANK_ID, RSSI_ADC_IN_10G, ADC_SAMPLETIME_55POINT5);
	//adc_regular_channel_config(RXPW_RSSI_ADC_1G_RANK_ID, RSSI_ADC_IN_1G, ADC_SAMPLETIME_55POINT5);

	/*注入组*/
	//adc_inserted_channel_config(0,
	//	RSSI_ADC_IN,ADC_SAMPLETIME_55POINT5);	

	adc_channel_length_config(ADC_INSERTED_CHANNEL, 1U);
	/* ADC trigger config */
	adc_external_trigger_source_config(ADC_INSERTED_CHANNEL, 
		ADC_EXTTRIG_INSERTED_NONE); 
	adc_external_trigger_config(ADC_INSERTED_CHANNEL, ENABLE);
	
	
	/* enable ADC interface */
	adc_enable();
	system_delay_ms(1);

	/* ADC calibration and reset calibration */
	adc_calibration_enable();

	/* ADC DMA function enable */
	adc_dma_mode_enable();
	
	/* ADC software trigger enable */
	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
	//adc_software_trigger_enable(ADC_INSERTED_CHANNEL);

	/* add end by fz, 20231129 */	
	
}

#endif

void adc_sample_function_init()
{
	/* add begin by fz, 20231129, 原因:规则通道 */
	adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);
	
	/* ADC scan function enable */
	adc_special_function_config(ADC_SCAN_MODE, ENABLE);

	/* add by fz, 20250219, 原因:规则 组 ，软件触发*/
	adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, 
		ADC_EXTTRIG_REGULAR_NONE); 
	adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);

		/*注入组，软件触发*/
	adc_external_trigger_source_config(ADC_INSERTED_CHANNEL,
	ADC_EXTTRIG_INSERTED_NONE);	
	adc_external_trigger_config(ADC_INSERTED_CHANNEL, ENABLE);	

	/* ADC data alignment config */
	adc_data_alignment_config(ADC_DATAALIGN_RIGHT);

	/* ADC channel length config ,3个规则组ADC_REGULAR_RANK_SIZE,
	与adc_dma_sample_value[DMA_ADC_RANK_SIZE]对应，	
	adc_dma_config_init()中，dma_data_parameter.number = DMA_ADC_RANK_SIZE; 
	*/
	adc_channel_length_config(ADC_REGULAR_CHANNEL, ADC_REGULAR_RANK_SIZE);		
	adc_regular_channel_config(TEC_RTH_TEMP_ADC_RANK_ID, TEC_THERM_ADC_IN, ADC_SAMPLETIME_55POINT5);
	adc_regular_channel_config(XTEC_OUT_ADC_RANK_ID, XTEC_ADC_IN, ADC_SAMPLETIME_55POINT5);
	adc_regular_channel_config(CASE_TEMP_ADC_RANK_ID, CASE_ADC_IN, ADC_SAMPLETIME_55POINT5);
//	adc_regular_channel_config(LD_50G_MON_ADC_RANK_ID,LD_50G_MON_ADC_IN,ADC_SAMPLETIME_55POINT5);
	

	/* ADC channel length config ,3个注入组,ADC_INSERT_RANK_SIZE*/
	adc_channel_length_config(ADC_INSERTED_CHANNEL, ADC_INSERT_RANK_SIZE);	
	adc_inserted_channel_config(RXPW_RSSI_ADC_50G_RANK_INSERT_ID, RSSI_ADC_IN_50G, ADC_SAMPLETIME_55POINT5);
	adc_inserted_channel_config(RXPW_RSSI_ADC_10G_RANK_INSERT_ID, RSSI_ADC_IN_10G, ADC_SAMPLETIME_55POINT5);
	adc_inserted_channel_config(RXPW_RSSI_ADC_1G_RANK_INSERT_ID, RSSI_ADC_IN_1G, ADC_SAMPLETIME_55POINT5);
	
	
	
	/* enable ADC interface */
	adc_enable();
	system_delay_ms(1);

	/* ADC calibration and reset calibration */
	adc_calibration_enable();

	/* ADC DMA function enable */
	adc_dma_mode_enable();
	
	/* ADC software trigger enable */
	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
	adc_software_trigger_enable(ADC_INSERTED_CHANNEL);

	/* add end by fz, 20231129 */	
	
}



/*****************************************************************************
 * 函 数 名  : get_adc_inserted_channel_sample
 * 负 责 人  : fz
 * 创建日期  : 2023年12月1日
 * 函数功能  : 获取注入组的一次采样
 * 输入参数  : uint8_t rank 注入组:[0,3]
 				uint8_t channel ADC采样通道
 * 输出参数  : 无
 * 返 回 值  : AD采样值
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
uint16_t get_adc_inserted_channel_sample(uint8_t rank,uint8_t channel)
{
	uint32_t run_us = 0;
	uint8_t cyl = 0;
	
    /* ADC regular channel config */
    adc_inserted_channel_config(rank, channel, ADC_SAMPLETIME_55POINT5);

    /* ADC software trigger enable */
    adc_software_trigger_enable(ADC_INSERTED_CHANNEL);

    /* wait the end of conversion flag */
   // while(!adc_flag_get(ADC_FLAG_EOC));

	run_us = CYCLE_DELAY_TIME_US;
	cyl = 0;		
	while_fun(!adc_flag_get(ADC_FLAG_EOIC),run_us,cyl);
	
    /* clear the end of conversion flag */
    adc_flag_clear(ADC_FLAG_EOIC);
	
    /* return regular channel sample value */
    return (adc_inserted_data_read(rank));
	
}

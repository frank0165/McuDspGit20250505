/***********************************************************************************

 * 文 件 名   : adc_sample_comm.h
 * 负 责 人   : fz
 * 创建日期   : 2023年5月18日
 * 文件描述   : adc config init
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#ifndef _ADC_SAMPLE_COMM_H_
#define _ADC_SAMPLE_COMM_H_

#include "gd32e501.h"


/*adc  采样时规则组序号分配*/
/*这个有变化时，DMA中初始化的number也要有变化*/
typedef enum {
	TEC_RTH_TEMP_ADC_RANK_ID = 0,/*热敏电阻温度adc*/
	XTEC_OUT_ADC_RANK_ID = 1,    /*VTEC反馈AD*/
	CASE_TEMP_ADC_RANK_ID = 2,	 /*壳体温度AD*/	
	//LD_50G_MON_ADC_RANK_ID = 3, /*sgm41295采样MON*/
	ADC_REGULAR_RANK_SIZE = 3
}ADC_SAMPLE_REGULAR_RANK_IDX;


/* add by fz, 20250304, 原因:DMA采样时只使用 
TEC_RTH_TEMP_ADC_RANK_ID,
XTEC_OUT_ADC_RANK_ID
CASE_TEMP_ADC_RANK_ID
定义DMA采样数组的长度为3
*/
/* add by fz, 20250307, 原因:本方案中规则组一律使用dma方式读取adc */
#define DMA_ADC_RANK_SIZE			ADC_REGULAR_RANK_SIZE

/* add by fz, 20250219, 原因:注入组分配序号 */
typedef enum{
	RXPW_RSSI_ADC_50G_RANK_INSERT_ID = 0,	/*50G RSSI采样*/
	RXPW_RSSI_ADC_10G_RANK_INSERT_ID = 1,	/*10G RSSI采样*/
	RXPW_RSSI_ADC_1G_RANK_INSERT_ID = 2,	/*1G RSSI采样*/
	ADC_INSERT_RANK_SIZE = 3
}ADC_SAMPLE_INSERT_RANK_IDX;

/* add by fz, 20250304, 原因:定义注入组长度为3 */
#define ADC_SAMPLE_INSERT_RANK_SIZE			ADC_INSERT_RANK_SIZE


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
uint16_t adc_sample_dma_regular_data_channel(uint8_t ch);

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
uint16_t adc_regular_channel_sample(uint8_t rank,uint8_t channel);




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
uint16_t get_adc_inserted_channel_sample(uint8_t rank,uint8_t channel);


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
void adc_dma_config_init();

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
void adc_sample_function_init();




#endif

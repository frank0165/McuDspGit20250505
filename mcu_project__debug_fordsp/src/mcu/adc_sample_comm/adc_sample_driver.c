/***********************************************************************************

 * 文 件 名   : adc_sample_driver.c
 * 负 责 人   : fangzhe
 * 创建日期   : 2025年3月23日
 * 文件描述   : adc sample的driver接口
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/
#include "adc_sample_driver.h"
#include "mcu_pin_type.h"


/*****************************************************************************
 * 函 数 名  : adc_gpio_init
 * 负 责 人  : fz
 * 创建日期  : 2023年5月19日
 * 函数功能  : 
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void adc_sample_gpio_init()
{
     /*这里的引脚在mcu_pin_type.h已经使用宏控制了，这里再加宏控制显得杂乱
      正在考虑有什么更好的办法
    */

	/*******************mcu对tec的控制**********************************/
	/* add begin by fz, 20230518, 原因:应用于热敏电阻采样
		
	*/
	/* add by fz, 20250113, 原因:sgm41296 引脚*/
	gpio_mode_set(GPIO_THERM_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_THERM_AD_PIN);
	gpio_mode_set(GPIO_ITEC_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_ITEC_AD_PIN);

	/* add by fz, 20231011, 原因:壳体温度 */
	gpio_mode_set(GPIO_CASE_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_CASE_AD_PIN);

	/*********************** 三模光接收端RSSI AD采样 *******************/
	/* add by gqhuan, 20240902, 原因:三模光接收端RSSI AD采样 */
	/* 50GPON */
	/* configure GPIO PC2 as ADC  */
  	gpio_mode_set(GPIO_RSSI_PORT_50G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_RSSI_AD_PIN_50G);

	/* 10GPON */
	/* configure GPIO PB3 as ADC  */
  	gpio_mode_set(GPIO_RSSI_PORT_10G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_RSSI_AD_PIN_10G);

	/* 1GPON */
	/* configure GPIO PA0 as ADC  */
  	gpio_mode_set(GPIO_RSSI_PORT_1G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_RSSI_AD_PIN_1G);

	/* add by fz, 20250304, 原因:50G使用PB1采样SGM41295的MON */	
	//dsp没有sgm41295
//	gpio_mode_set(GPIO_LD_MON_PORT_50G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE,GPIO_LD_MON_PIN_50G);

}


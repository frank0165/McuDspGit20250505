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
 * 函 数 名  : rcu_config_init
 * 负 责 人  : fz
 * 创建日期  : 2023年4月24日
 * 函数功能  : rcu初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  :  

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

	/*配置DAC电压时*/
	rcu_periph_clock_enable(RCU_CFGCMP);

	/*
		在GD32E501产品中ADC时钟由APB2时钟经2、4、6、8分频或由AHB时钟经3、5、7、9分频
		或IRC28M或IRC28M/2时钟获得，它们是通过设置配置寄存器2(RCU_CFG2)的ADCSEL位来
		选择ADC时钟源的。
	*/
	rcu_periph_clock_enable(RCU_ADC);

	 /* enable DMA clock */
    rcu_periph_clock_enable(RCU_DMA);

	/*配置ADC时钟*/
	rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);

	rcu_periph_clock_enable(RCU_CRC);
	
}


/*****************************************************************************
 * 函 数 名  : syscfg_config
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月23日
 * 函数功能  : mcu的系统初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
void syscfg_config(void)
{
    syscfg_deinit();
    syscfg_vref_enable();
}






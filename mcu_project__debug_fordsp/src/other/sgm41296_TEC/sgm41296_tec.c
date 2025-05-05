/***********************************************************************************

 * 文 件 名   : tec_comm.c
 * 负 责 人   : fz
 * 创建日期   : 2023年5月18日
 * 文件描述   : tec控制
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

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
 * 函 数 名  : sgm41296_tec_config_init
 * 负 责 人  : fz
 * 创建日期  : 2023年5月18日
 * 函数功能  : sgm41296_tec初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void sgm41296_tec_gpio_init()
{
	/*TEC SD控制脚默认为高*/
	gpio_mode_set(GPIO_TEC_SD_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_TEC_SD_PIN);
    gpio_output_options_set(GPIO_TEC_SD_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_TEC_SD_PIN);
	gpio_bit_set(GPIO_TEC_SD_PORT,GPIO_TEC_SD_PIN);	
	
	/*TEC EN控制脚默认为高*/
	gpio_mode_set(GPIO_TEC_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_TEC_EN_PIN);
    gpio_output_options_set(GPIO_TEC_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_TEC_EN_PIN);
	gpio_bit_set(GPIO_TEC_EN_PORT,GPIO_TEC_EN_PIN);

	return;
}

/*****************************************************************************
 * 函 数 名  : sgm41296_tec_get_xtec_voltage
 * 负 责 人  : fz
 * 创建日期  : 2025年1月13日
 * 函数功能  : 读取xtec的电压
 * 输入参数  : 无
 * 输出参数  : float *voltage 芯片的xtec反馈电压
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
void sgm41296_tec_get_xtec_voltage(float *voltage)
{
	uint16_t data = 0;
	/* add by fz, 20230625, 原因:参数检查 */
	if(NULL == voltage)
	{
		return;
	}

	/*采样电压*/
	data = adc_dma_channel_sample_average(XTEC_ADC_IN);
	*voltage = MCU_REF_VOLTAGE / MCU_12BIT_RANGE * data;
	
	return;	
}

/*****************************************************************************
 * 函 数 名  : sgm41296_tec_get_therm_adc
 * 负 责 人  : fz
 * 创建日期  : 2023年7月19日
 * 函数功能  : 获取热敏电阻的温度的ADC值
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 采样温度的ADC值
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
uint32_t sgm41296_tec_get_therm_adc()
{	
	return adc_dma_channel_sample_average(TEC_THERM_ADC_IN);
		
}


/*****************************************************************************
 * 函 数 名  : sgm41296_tec_release_limit_refresh
 * 负 责 人  : fz
 * 创建日期  : 2023年12月4日
 * 函数功能  : sgm41296芯片的门限清零
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void sgm41296_tec_release_limit_refresh()
{
	uint32_t slave_address = I2C_TEC_DEV_ADDR;
	uint8_t reg = 0;
	uint8_t data = 0;
	uint8_t pbuffer[2] = {0,0};

	reg = 0x9;/*状态寄存器*/
	master_reg_1byte_size_read(slave_address, reg,&data, 1);

    if(1 == ((data >> 5) & 0x1) //VLIM为1则电压到达门限
		|| 1 == ((data >> 4) & 0x1) //ILIM为1则电流到达门限
		|| 0 == ((data >> 3) & 0x1)) //PWOR为0就是disable
	{

		/*清除limt之前先读寄存器配置*/
		memset(pbuffer,0,sizeof(pbuffer));
		reg = 0x0;//device control寄存器
		data &= 0;

		/*先回读*/
		master_reg_1byte_size_read(slave_address, reg,&data, 1);

		data |= 0x03; /*要 release，0011*/
		pbuffer[0] = reg;
		pbuffer[1] |= data;
		master_reg_byte_write(slave_address, pbuffer, 2);
	}
	
}


/*****************************************************************************
 * 函 数 名  : sgm1296_tec_init
 * 负 责 人  : fz
 * 创建日期  : 2023年5月18日
 * 函数功能  : sgm41296_tec初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void sgm1296_tec_init(void)
{
	sgm41296_vtec_dac_ctl_set(SGM41296_CTL_ZERO_VOLTAGE);
	sgm41296_tec_gpio_init();
}


/*****************************************************************************
 * 函 数 名  : sgm41296_vtec_dac_ctl_set
 * 负 责 人  : fz
 * 创建日期  : 2023年5月18日
 * 函数功能  : 
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 
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

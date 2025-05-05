/***********************************************************************
	* 文 件 名： gn7153.c
	* 负 责 人： gqhuan
	* 创建日期： 2024-06
	* 文件描述： GN7153 10G BOSA Driver功能函数
	* 版权说明： Copyright (c) 1999-2024    烽火通信科技股份有限公司
	* 其    他： 
	* 修改日志： 
************************************************************************/

#include "user_config.h"
#include "mcu_pin_type.h"
#include "mcu_data_type.h"
#include "gn7153.h"
#include "dev_reg_address.h"

#include "i2c_comm.h"
#include "sff_8472.h"

#if defined( FH_IC_GN7153_HARDWARE) && (FH_IC_GN7153_HARDWARE == CFG_YES)



/***********************************************************************
	** 函 数 名： gn7153_init
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153初始化
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_init()
{

		/* GPIO初始化 */
		gn7153_gpio_init();
 
		/* 芯片reset */
		gn7153_reset();
	
		/* 软件使能txdsbl,1-shut down */
		gn7153_soft_txdsbl_ctrl(1);
	
		/* 初始化寄存器配置 */
		gn7153_normal_setting();
		
		/* 软件使能txdsbl,1-shut down */
		gn7153_soft_txdsbl_ctrl(0);

		/* 使能ADC功能 */
		gn7153_adc();
 
}

/***********************************************************************
	** 函 数 名： gn7153_gpio_init
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153引脚初始化
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_gpio_init()
{
	/* configure GPIO PA3 as RESET */ 
	//gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_3);    
	//gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
	gpio_mode_set(GPIO_10G_RST_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_10G_RST_PIN);    
	gpio_output_options_set(GPIO_10G_RST_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_10G_RST_PIN);

    gpio_mode_set(GPIO_10G_RXSD_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_10G_RXSD_PIN);    
	gpio_output_options_set(GPIO_10G_RXSD_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_10G_RXSD_PIN);


#if 0

 /* configure GPIO pins of slave */
    gpio_mode_set(GPIO_I2C_SLAVE_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_I2C_SLAVE_SCL);
    gpio_output_options_set(GPIO_I2C_SLAVE_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, 
	GPIO_I2C_SLAVE_SCL);
#endif
    gpio_mode_set(GPIO_MODNR_10G_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_MODNR_10G_PIN);    
	gpio_output_options_set(GPIO_MODNR_10G_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_MODNR_10G_PIN);
    
}

/***********************************************************************
	** 函 数 名： gn7153_reset
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153复位
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_reset()
{
	/* RST高电平 */
	gpio_bit_reset(GPIO_10G_RST_PORT, GPIO_10G_RST_PIN);
	system_delay_ms(10);
	gpio_bit_set(GPIO_10G_RST_PORT, GPIO_10G_RST_PIN);
    
}

/***********************************************************************
	** 函 数 名： gn7153_soft_txdsbl_ctrl
	** 输    入： uint8_t ctrl_switch 0-enable 1-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153 软件使能/去使能TXDSBL
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_soft_txdsbl_ctrl(uint8_t ctrl_switch)
{
	if(ctrl_switch == 1){
		uint8_t tx_ld_soft_txdsbl_reg[2];//0x96-TXSDO_REG25
		tx_ld_soft_txdsbl_reg[0] = 0x60;
		tx_ld_soft_txdsbl_reg[1] = 0x34;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, tx_ld_soft_txdsbl_reg, 2);
	}
	else{
		uint8_t tx_ld_soft_txdsbl_reg[2];//0x96-TXSDO_REG25
		tx_ld_soft_txdsbl_reg[0] = 0x60;
		tx_ld_soft_txdsbl_reg[1] = 0x30;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, tx_ld_soft_txdsbl_reg, 2);
	}
	
}

/***********************************************************************
	** 函 数 名： gn7153_normal_setting
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153初始化配置
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_normal_setting()
{
	/* 设置功率控制模式 */
	uint8_t adjust_type = 1;//0:闭环模式 1:开环模式
	
	/* 设置驱动芯片为源端 */
	gn7153_source_sink_select(1);

	/* 使能APC功能 */
	gn7153_apc_ctrl(1);

	/* 设置IPHOTO监测范围 */
	uint8_t mpd_iphoto_range[2];
	mpd_iphoto_range[0] = 0x57;//0x57-TXSDO_REG5
	mpd_iphoto_range[1] = 0x02;
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, mpd_iphoto_range, 2);
	
	if(adjust_type == 0){
		/* 去使能override模式 */
		gn7153_override_ctrl(0);
		
		/* 设置APC锁定目标值 */
		uint8_t apc_target_value[2];
		apc_target_value[0] = 0x0F;//0x0F-APC_REG6
		apc_target_value[1] = 0x5F;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, apc_target_value, 2);
		
		/* soft txdsbl恢复后保存上次电流值 */
		uint8_t ld_bias_txdsbl_mask[2];
		ld_bias_txdsbl_mask[0] = 0x06;//0x06-TOP_REG5
		ld_bias_txdsbl_mask[1] = 0x0F;//bit[4:4]=1  restores LD bias current
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, ld_bias_txdsbl_mask, 2);
	}
	else{
		/* 使能override模式 */
		gn7153_override_ctrl(1);
		
		/* 手动写入LD偏置电流 */
		uint8_t lower_value[2];
		uint8_t upper_value[2];
		lower_value[0] = 0x0D;//0x0D-APC_REG4
		upper_value[0] = 0x0E;//0x0E-APC_REG5
		lower_value[1] = 0x00;//bit[7:0]=4F
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, lower_value, 2);
		upper_value[1] = 0x04;//bit[1:0]=05
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, upper_value, 2);
		
		/* soft txdsbl恢复后保存上次电流值 */
		uint8_t ld_bias_txdsbl_mask[2];
		ld_bias_txdsbl_mask[0] = 0x06;//0x06-TOP_REG5
		ld_bias_txdsbl_mask[1] = 0x1F;//bit[4:4]=1  restores LD bias current
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, ld_bias_txdsbl_mask, 2);
		
	}
	/* 设置调制电压 */
	float mod_vcc;
	mod_vcc = 0.0;//单位mV
	gn7153_set_ld_imod(mod_vcc);

	#if 1
	/* 清除告警 */
	uint8_t txflt_reg[2] = {0x62, 0x40};//0x62-TXFLT_REG1
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, txflt_reg, 2);
	#endif

	#if 1
	/* 极性反转 */
	uint8_t rxtop_reg1[2] = {0x73, 0x4C};//0x73-TXTOP_REG1
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, rxtop_reg1, 2);
	#endif

	#if 1
	/* RESET模式设置 */
	uint8_t pulse_gen_reg1[2] = {0x7B, 0x04};//0x7B-PULSE_GEN_REG1
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, pulse_gen_reg1, 2);
	#endif
	
}

/***********************************************************************
	** 函 数 名： gn7153_adc
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153的ADC转换
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_adc()
{
    uint8_t value[2];
		/*ADC上电*/
		value[0] = 0x34;//0x34-PWRDN_REG2 PD_ADC = 0
		value[1] = 0x03;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);
		/*ADC重置、设置ADC手动/自动模式*/
		value[0] = 0x14;//0x14-ADC_REG0 ADC_RESET = 0 ADC_AUTO_CONV_EN = 0
		value[1] = 0x0C;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);
		/*设置ADC分辨率10bit和转换速率4*/
		value[0] = 0x16;//0x16-ADC_REG2 ADC_RESOLUTION = 3d ADC_CLK_RATE = 3d
		value[1] = 0x1B;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);
		/*选择ADC转换的源端*/
		value[0] = 0x15;//0x15-ADC_REG1 ADC_SRC_SEL = 1d
		value[1] = 0x02;//01 LD BIAS 02 IPHOTO VOLTAGE 03 LD MODULATION 04/05 Temperature Sensor 06 3.3v supply sensor 07 1.8v supply sensor
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);
		/*启动ADC转换*/
		value[0] = 0x17;//0x17-ADC_REG3 ADC_START_CONV = 1
		value[1] = 0x01;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);
}

/***********************************************************************
	** 函 数 名： gn7153_source_sink_select
	** 输    入： uint8_t ctrl_switch 1-enable source 0-enable sink
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153选择源宿端
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_source_sink_select(uint8_t ctrl_switch)
{	
		uint8_t value[2];
		value[0] = 0x61;//0x61-TXSDO_REG26
    if(ctrl_switch == 1){
			value[1] = 0x09;
		}
		else{
			value[1] = 0x11;
		}
		master_reg_byte_write(GN7153_SLAVE_ADDRESS,value, 2);
}

/***********************************************************************
	** 函 数 名： gn7153_apc_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153使能/去使能APC功能
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_apc_ctrl(uint8_t ctrl_switch)
{
	uint8_t value[2];
	value[0] = 0x0B;//0x0B-APC_REG1
	if(ctrl_switch == 1){
			value[1] = 0x01;
	}
	else{
			value[1] = 0x00;
	}
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,value, 2);
    
}

/***********************************************************************
	** 函 数 名： gn7153_override_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153 使能/去使能上帝模式
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_override_ctrl(uint8_t ctrl_switch)
{
	uint8_t value[2];
	value[0] = 0x0E;//0x0E-APC_REG5
	if(ctrl_switch == 1){
		value[1] = 0x04;
	}
	else{
		value[1] = 0x00;
	}
  master_reg_byte_write(GN7153_SLAVE_ADDRESS,value, 2);
}

/***********************************************************************
	** 函 数 名： gn7153_temperature_monitor_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable 2-second source
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153使能/去使能温度监控
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_temperature_monitor_ctrl(uint8_t ctrl_switch)
{
	uint8_t value[2];
	value[0] = 0x15;////0x15-ADC_REG1 ADC_SRC_SEL = 04/05d
	if(ctrl_switch == 1){
			value[1] = 0x04;
		}
	else if(ctrl_switch == 2){
		value[1] = 0x05;
	}
	else{
			value[1] = 0x06;
	}
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,value, 2);
    
}
/***********************************************************************
	** 函 数 名： gn7153_get_temperature
	** 输    入： float* temperature
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153获取温度值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_get_temperature(float* temperature)
{
	uint8_t adc_out_lo[1];
	uint8_t adc_out_hi[1];
	uint8_t value[2];
	
	uint16_t adc_out_1 = 0;
	gn7153_temperature_monitor_ctrl(1);
	
	/*启动ADC转换*/
	value[0] = 0x17;//0x17-ADC_REG3 ADC_START_CONV = 1
	value[1] = 0x01;
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);
	fh_delay_us(1000);
	//system_delay_ms(1);
	
	uint8_t adc_done_conv[1];
	master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x18, adc_done_conv, 1);//0x18-ADC_REG4 ADC_DONE_CONV
	if (adc_done_conv[0] == 1){			
		master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x19, adc_out_lo, 1);//0x19-ADC_REG5 ADC_OUT_LO
		master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x1A, adc_out_hi, 1);//0x1A-ADC_REG6 ADC_OUT_HI
		adc_out_1 = adc_out_hi[0] * 256 + adc_out_lo[0];
	}
	
	uint16_t adc_out_2 = 0;
	gn7153_temperature_monitor_ctrl(2);
	
	/*启动ADC转换*/
	value[0] = 0x17;//0x17-ADC_REG3 ADC_START_CONV = 1
	value[1] = 0x01;
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);
	fh_delay_us(1000);
	//system_delay_ms(1);
	
	master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x18, adc_done_conv, 1);//0x18-ADC_REG4 ADC_DONE_CONV
	if (adc_done_conv[0] == 1){		
		master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x19, adc_out_lo, 1);//0x19-ADC_REG5 ADC_OUT_LO
		master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x1A, adc_out_hi, 1);//0x1A-ADC_REG6 ADC_OUT_HI
		adc_out_2 = adc_out_hi[0] * 256 + adc_out_lo[0];
	} 
	*temperature = 3.50 * (adc_out_1 - adc_out_2) - 301.98;

}
/***********************************************************************
	** 函 数 名： gn7153_voltage_monitor_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153使能/去使能电压监控
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_voltage_monitor_ctrl(uint8_t ctrl_switch)
{
	uint8_t value[2];
	value[0] = 0x15;////0x15-ADC_REG1 ADC_SRC_SEL = 06d
	if(ctrl_switch == 1){
		value[1] = 0x06;
	}
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,value, 2);
    
}
/***********************************************************************
	** 函 数 名： gn7153_get_voltage
	** 输    入： float* voltage
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153获取电压值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_get_voltage(float* vcc)
{
	uint8_t adc_out_lo[1];
	uint8_t adc_out_hi[1];
	uint8_t value[2];
	uint16_t adc_out = 0;
	gn7153_voltage_monitor_ctrl(1);
	
	/*启动ADC转换*/
	value[0] = 0x17;//0x17-ADC_REG3 ADC_START_CONV = 1
	value[1] = 0x01;
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);
	fh_delay_us(1000);
	//system_delay_ms(1);
	
	uint8_t adc_done_conv[1];
	master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x18, adc_done_conv, 1);//0x18-ADC_REG4 ADC_DONE_CONV
	if (adc_done_conv[0] == 1){			
		master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x19, adc_out_lo, 1);//0x19-ADC_REG5 ADC_OUT_LO
		master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x1A, adc_out_hi, 1);//0x1A-ADC_REG6 ADC_OUT_HI
		adc_out = adc_out_hi[0] * 256 + adc_out_lo[0];
	}

	if(0 == adc_out)
	{
		*vcc= 0.0;
	}
	else
	{
		*vcc = 0.005586 * adc_out - 0.02313;
	}
	
	ddm_adc_out_val.voltage_adc_out_1 = adc_out;

}
/***********************************************************************
	** 函 数 名： gn7153_ld_ibias_monitor_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153使能/去使能激光器驱动电流监控
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_ld_ibias_monitor_ctrl(uint8_t ctrl_switch)
{
	uint8_t value[2];
	uint8_t bias_mon[2];
	value[0] = 0x15;//0x15-ADC_REG1 ADC_SRC_SEL = 01d
	bias_mon[0] = 0x58;//0x58-TXSDO_REG8 bit[2] CSR_TXSDO_BIAS_MON_EN
	if(ctrl_switch == 1){
		value[1] = 0x01;
		bias_mon[1] = 0x05;
	}
	else
	{
		value[1] = 0x06;
		bias_mon[1] = 0x01;
	}
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,value, 2);
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,bias_mon, 2);
	  
}
/***********************************************************************
	** 函 数 名： gn7153_get_ld_ibias
	** 输    入： float* vcc
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153获取激光器驱动电流值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_get_ld_ibias(float* ibias)
{
	uint8_t adc_out_lo[1];
	uint8_t adc_out_hi[1];
	uint8_t value[2];
	uint16_t adc_out = 0;
	
	gn7153_ld_ibias_monitor_ctrl(1);
	
	/*启动ADC转换*/
	value[0] = 0x17;//0x17-ADC_REG3 ADC_START_CONV = 1
	value[1] = 0x01;
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);
	fh_delay_us(1000);
	//system_delay_ms(1);
	
	uint8_t adc_done_conv[1];
	master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x18, adc_done_conv, 1);//0x18-ADC_REG4 ADC_DONE_CONV
	if (adc_done_conv[0] == 1){			
		master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x19, adc_out_lo, 1);//0x19-ADC_REG5 ADC_OUT_LO
		master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x1A, adc_out_hi, 1);//0x1A-ADC_REG6 ADC_OUT_HI
		adc_out = adc_out_hi[0] * 256 + adc_out_lo[0];
	}
	
	*ibias = om_default_config.tx_i_slope_1 * adc_out + om_default_config.tx_i_offset_1;
	ddm_adc_out_val.ibias_adc_out_1 = adc_out;

}
/***********************************************************************
	** 函 数 名： gn7153_set_ld_ibias
	** 输    入： uint16_t ibias
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153设置激光器驱动电流值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_set_ld_ibias(uint16_t ibias){
	uint8_t ibias_set_val[2];
	set_u16(ibias_set_val, ibias);
	
	/* 手动写入LD偏置电流 */
	uint8_t lower_value[2];
	uint8_t upper_value[2];
	lower_value[0] = 0x0D;//0x0D-APC_REG4
	upper_value[0] = 0x0E;//0x0E-APC_REG5
	lower_value[1] = ibias_set_val[1];//bit[7:0]=7F 9F
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, lower_value, 2);
	upper_value[1] = 0x04 | ibias_set_val[0];//bit[1:0]=0 04
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, upper_value, 2);
	
}
/***********************************************************************
	** 函 数 名： gn7153_mpd_ibias_monitor_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153使能/去使能背光电流监控
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_mpd_ibias_monitor_ctrl(uint8_t ctrl_switch)
{
	uint8_t value[2];
	value[0] = 0x15;////0x15-ADC_REG1 ADC_SRC_SEL = 02d
	if(ctrl_switch == 1){
		value[1] = 0x02;
	}
	else
	{
		value[1] = 0x06;
	}
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,value, 2);
    
}
/***********************************************************************
	** 函 数 名： gn7153_get_mpd_ibias
	** 输    入： float* ibias
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153获取激光器背光电流值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_get_mpd_ibias(float* ibias)
{
	uint8_t adc_out_lo[1];
	uint8_t adc_out_hi[1];
	uint8_t value[2];
	uint16_t adc_out = 0;
	
	gn7153_mpd_ibias_monitor_ctrl(1);
	
	/*启动ADC转换*/
	value[0] = 0x17;//0x17-ADC_REG3 ADC_START_CONV = 1
	value[1] = 0x01;
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);
	fh_delay_us(1000);
	//system_delay_ms(1);
	
	uint8_t adc_done_conv[1];
	master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x18, adc_done_conv, 1);//0x18-ADC_REG4 ADC_DONE_CONV
	if (adc_done_conv[0] == 1){			
		master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x19, adc_out_lo, 1);//0x19-ADC_REG5 ADC_OUT_LO
		master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS, 0x1A, adc_out_hi, 1);//0x1A-ADC_REG6 ADC_OUT_HI
		adc_out = adc_out_hi[0] * 256 + adc_out_lo[0];
	}
	*ibias = 0.000348 * adc_out + 0.00108;
	ddm_adc_out_val.tx_power_adc_out_1 = adc_out;

}
/***********************************************************************
	** 函 数 名： gn7153_set_ld_imod
	** 输    入： uint16_t mod_vcc 调制电压
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153设置LD调制电流值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_set_ld_imod(uint16_t mod_vcc)
{
	uint8_t txsdo_imod_lo[2];
	uint8_t txsdo_imod_hi[2];
	
	txsdo_imod_lo[0] = 0x59;//0x59-TXSDO_REG10
	txsdo_imod_hi[0] = 0x5A;//0x5A-TXSDO_REG11
	
	uint16_t code = mod_vcc / (0.154*25);
	txsdo_imod_lo[1] = (uint8_t)(code);
	txsdo_imod_hi[1] = (uint8_t)(code >> 8);
	
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,txsdo_imod_lo, 2);
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,txsdo_imod_hi, 2);
}
/***********************************************************************
	** 函 数 名： gn7153_set_txsdo_crosspoint_adjust
	** 输    入： uint8_t value：交叉点调节值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153设置发端交叉点调节值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_set_tx_ld_cpa(uint8_t value)
{
	uint8_t txsdo_cpa_en[2];
	uint8_t txsdo_cpa_val[2];
	
	txsdo_cpa_en[0] = 0x33;//0x33-PWRDN_REG1
	txsdo_cpa_val[0] = 0x5B;//0x5B-TXSDO_REG12
	
	txsdo_cpa_en[1] = 0x0;
	txsdo_cpa_val[1] = value;
	
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,txsdo_cpa_en, 2);
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,txsdo_cpa_val, 2);
	
}

/***********************************************************************
	** 函 数 名： gn7153_set_tx_eq_boost
	** 输    入： uint8_t value：EQ调节值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153设置发端EQ调节值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_set_tx_eq_boost(uint8_t value)
{
	uint8_t tx_eq_boost[2];
	
	tx_eq_boost[0] = 0x48;//0x48-TX_REG3 bit[1:0]
	
	tx_eq_boost[1] = value;//0/2/4/6 dB
	
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,tx_eq_boost, 2);

}

/***********************************************************************
	** 函 数 名： gn7153_set_rx_eq_boost
	** 输    入： uint16_t value：EQ调节值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153设置收端EQ调节值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_set_rx_eq_boost(uint16_t value)
{
	uint8_t rx_eq_boost_la_reg[2];
	rx_eq_boost_la_reg[0] = 0x80;//0x80-RXLA_REG1
	rx_eq_boost_la_reg[1] = value; 
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, rx_eq_boost_la_reg, 2);

}

/***********************************************************************
	** 函 数 名： gn7153_set_rx_swing
	** 输    入： uint16_t value：swing调节值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153设置收端驱动摆幅
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_set_rx_swing(uint16_t value)
{
	uint8_t rx_swing_val_reg[2];
	rx_swing_val_reg[0] = 0x77; //0x77-RXSDO_REG1
	rx_swing_val_reg[1] = value; 
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, rx_swing_val_reg, 2);
}

/***********************************************************************
	** 函 数 名： gn7153_set_tx_ld_preemph
	** 输    入： uint8_t value：预加重值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153设置发端预加重值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_set_tx_ld_preemph(uint8_t value)
{
	uint8_t txsdo_preemph_en[2];
	uint8_t txsdo_preemph_val[2];
	
	txsdo_preemph_en[0] = 0x33;//0x33-PWRDN_REG1
	txsdo_preemph_val[0] = 0x5D;//0x5B-TXSDO_REG14
	
	txsdo_preemph_en[1] = 0x0;
	txsdo_preemph_val[1] = value;
	
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,txsdo_preemph_en, 2);
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,txsdo_preemph_val, 2);
	
}

/***********************************************************************
	** 函 数 名： gn7153_set_rx_drv_preemph
	** 输    入： uint16_t value：预加重调节值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153设置收端预加重值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_set_rx_drv_preemph(uint16_t value)
{
	uint8_t rx_drv_preemph_en[2];
	uint8_t rx_drv_preemph_val[2];
	rx_drv_preemph_en[0] = 0x79; //0x79-RX_PD_RXSDO_EMPHASIS
	rx_drv_preemph_en[1] = 0x00;
	rx_drv_preemph_val[0] = 0x78; //0x78-RXSDO_REG2
	rx_drv_preemph_val[1] = value; 

	master_reg_byte_write(GN7153_SLAVE_ADDRESS, rx_drv_preemph_en, 2);
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, rx_drv_preemph_val, 2);
}

/***********************************************************************
	** 函 数 名： gn7153_set_rx_los_threshold
	** 输    入： uint8_t los_th 信号丢失阈值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153设置收端信号丢失阈值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_set_rx_los_threshold(uint8_t los_th){
	
	uint8_t rx_los_threshold[2];
	rx_los_threshold[0] = 0x91;//0x91-LOS_CTRL_REG1
	rx_los_threshold[1] = los_th;
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,rx_los_threshold, 2);
	
}

/***********************************************************************
	** 函 数 名： gn7153_set_rx_los_hyst
	** 输    入： uint8_t los_hyst 信号丢失磁滞值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153设置收端信号丢失磁滞
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_set_rx_los_hyst(uint8_t los_hyst){
	
	uint8_t rx_los_hyst[2];
	rx_los_hyst[0] = 0x92;//0x92-LOS_CTRL_REG2 RXLOS_HYST_SELECT[4:0]
	rx_los_hyst[1] = los_hyst;
	master_reg_byte_write(GN7153_SLAVE_ADDRESS,rx_los_hyst, 2);
	
}

/***********************************************************************
	** 函 数 名： gn7153_temperaturel_Sample_Average
	** 输    入： float* temperature：多次采样温度的平均值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7153温度采样上报的平均值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7153_temperaturel_Sample_Average(float* temperature)
{
    float temp = 0.0;
		float temp_sum = 0.0;
    uint8_t degree = 3;  //读的次数的幂 2^3
    for(int i = 0;i < (1 << degree);i++)
    {
        //读取ADC次数
		gn7153_get_temperature(&temp);
        temp_sum += temp;  
		system_delay_ms(1);
    }
    
    //这里循环8次读取,因此 >>3位就是除以8
    * temperature = temp_sum / 8;

}


/*****************************************************************************
 * 函 数 名  : gn7153_apc_auto_enable_ctrl
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : apc自动控制使用
 * 输入参数  : uint8_t ctrl_switch  1--使能；
                                    0--去使能
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void gn7153_apc_auto_enable_ctrl(uint8_t ctrl_switch)
{
	uint8_t value[10];
	uint8_t temp_data = 0;
	uint8_t reg = 0xB; /*APC_REG1*/
	uint8_t apc_reg0xb_value = 0;
	uint8_t apc_mask = 0;
	uint8_t apc_ovr = 0;

	memset(value,0,sizeof(value));	
	
	master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS,reg,&apc_reg0xb_value,1);

	reg = 0x6;/*LD_BIAS_TXDSBL_MASK,[4:4]*/
	master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS,reg,&apc_mask,1);

	reg = 0xe;/*APC_OVR REG5*/
	master_reg_1byte_size_read(GN7153_SLAVE_ADDRESS,reg,&apc_ovr,1);

	//gn7153_soft_txdsbl_ctrl(1);
	
	if(1 == ctrl_switch)
	{
		/*读取mask*/
		memset(value,0,sizeof(value));
		reg = 0x6;/*LD_BIAS_TXDSBL_MASK,[4:4]*/
		apc_mask &= ~(1 << 4); /*使能apc时，要把mask disable*/
		temp_data = apc_mask;
		value[0] = reg;
		value[1] = temp_data;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);		

		/*设置APC_OVR*/
		memset(value,0,sizeof(value));
		reg = 0xe;/*APC_REG5*/		
		temp_data = (apc_ovr & ~(0x1 << 2)); /*[2:2] APC_OVR,set low*/
		value[0] = reg;
		value[1] = temp_data;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);	

		apc_reg0xb_value |= 0x1;/*enable*/		
		reg = 0xB;
		memset(value,0,sizeof(value));
		value[0] = reg;
		value[1] = apc_reg0xb_value;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);
		
		
	}
	else
	{
		/*设置APC_OVR*/
		memset(value,0,sizeof(value));
		reg = 0xe;/*APC_REG5,*/		
		temp_data = (apc_ovr |(0x1 << 2)); /*[2:2] APC_OVR,set high*/
		value[0] = reg;
		value[1] = temp_data;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);	

		/*enableLD_BIAS_TXDSBL_MASK*/
		memset(value,0,sizeof(value));
		reg = 0x6;/*LD_BIAS_TXDSBL_MASK,[4:4]*/		
		apc_mask |= (0x1 << 4); /*去使能apc时，要把mask enable*/
		temp_data = apc_mask;	
		value[0] = reg;
		value[1] = temp_data;
		master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);	
		
	}

	//gn7153_soft_txdsbl_ctrl(0);	
	/* 清除告警 */
	uint8_t txflt_reg[2] = {0x62, 0x40};//0x62-TXFLT_REG1
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, txflt_reg, 2);

	return;
}

/*****************************************************************************
 * 函 数 名  : gn7153_apc_target_voltage
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : 设置apc目标电压
 * 输入参数  : float voltage_target :APC目标电压值
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void gn7153_apc_target_voltage(float voltage_target)
{
	uint8_t value[10];
	uint8_t reg = 0xF;
	uint8_t tmp_data = 0;
	float tmp_float = 0.0;
	
	tmp_float= (voltage_target > 1000.0) ? 1000.0 : voltage_target;

	tmp_data = tmp_float / 4;
	
	memset(value,0,sizeof(value));
	value[0] = reg;
	value[1] = tmp_data;
	master_reg_byte_write(GN7153_SLAVE_ADDRESS, value, 2);

	return;
}

#endif


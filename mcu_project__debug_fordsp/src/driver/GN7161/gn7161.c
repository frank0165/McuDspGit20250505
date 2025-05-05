/***********************************************************************
	* 文 件 名： gn7161.c
	* 负 责 人： gqhuan
	* 创建日期： 2023-09
	* 文件描述： GN7161 50G BOSA Driver功能函数
	* 版权说明： Copyright (c) 1999-2023    烽火通信科技股份有限公司
	* 其    他： 
	* 修改日志： 
************************************************************************/


//#include "gn7161.h"
#include "mcu_data_type.h"
#include "i2c_comm.h"
#include "sff_8472.h"
#include "dev_reg_address.h"

#if defined(FH_IC_GN7161_HARDWARE) && (FH_IC_GN7161_HARDWARE == CFG_YES)

//extern volatile DDM_ADC_OUT_VAL ddm_adc_out_val;//外部ddm监控变量ADC值
//extern volatile OM_DEFAULT_CONFIG om_default_config; //外部光模块默认参数



/***********************************************************************
	** 函 数 名： gn7161_init
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161初始化
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_init()
{
	/* GPIO初始化 */
	gn7161_gpio_init();

	
	/* 芯片reset */
	gn7161_reset();
	
	
	/* 使能txdsbl */
//	gn7161_txdsbl_ctrl(1);

	
	/* 载入FW */
	gn7161_download_firmware();
	
	/* 延时1s */
	fh_delay_ms(500);
	
	
	/* 软件使能txdsbl,1-shut down */
	gn7161_soft_txdsbl_ctrl(1);
	
	/* 初始化寄存器配置 */
	gn7161_normal_setting();
	
	/* 软件去使能txdsbl,0-start,开启 */
	gn7161_soft_txdsbl_ctrl(0);

	/* 发端lane通道极性反转 */
	gn7161_tx_lane_polarity_inversion(1);
	
	/* 打开lane通道 */
	gn7161_tx_lane_ctrl(1);

	/* 使能ADC功能 */
	gn7161_adc();

		
}

/***********************************************************************
	** 函 数 名： gn7161_gpio_init
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161引脚初始化
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_gpio_init()
{
	/* configure GPIO PA12 as RESET */ 
	gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_12);    
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
	/* configure GPIO PA1 as 50G_TXDSBL */ 
	gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_1);    
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
}

/***********************************************************************
	** 函 数 名： gn7161_reset
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161复位
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_reset()
{
	/* RST高电平 */
	gpio_bit_reset(GPIOA, GPIO_PIN_12);
	system_delay_ms(10);
	gpio_bit_set(GPIOA, GPIO_PIN_12);
	
}

/***********************************************************************
	** 函 数 名： gn7161_txdsbl_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161 使能/去使能TXDSBL
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_txdsbl_ctrl(uint8_t ctrl_switch)
{
	if(ctrl_switch == 1){
		/* TXDSBL高电平 */
		gpio_bit_set(GPIOB, GPIO_PIN_3);
	}
	else{
		/* TXDSBL低电平 */
		gpio_bit_reset(GPIOB, GPIO_PIN_3);
	}
	
}

/***********************************************************************
	** 函 数 名： gn7161_soft_txdsbl_ctrl
	** 输    入： uint8_t ctrl_switch 0-enable 1-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161 软件使能/去使能TXDSBL
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_soft_txdsbl_ctrl(uint8_t ctrl_switch)
{
	if(ctrl_switch == 1){
		uint8_t tx_ld_soft_txdsbl_reg[3];//0x85E-TX_LD_SOFT_TXDSBL_REG
		set_u16(tx_ld_soft_txdsbl_reg, 0x085E);
		tx_ld_soft_txdsbl_reg[2] = 0x01;
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_soft_txdsbl_reg, 3);
	}
	else{
		uint8_t tx_ld_soft_txdsbl_reg[3];//0x85E-TX_LD_SOFT_TXDSBL_REG
		set_u16(tx_ld_soft_txdsbl_reg, 0x085E);
		tx_ld_soft_txdsbl_reg[2] = 0x00;
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_soft_txdsbl_reg, 3);
	}
	
}

/***********************************************************************
	** 函 数 名： gn7161_normal_setting
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161初始化配置
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_normal_setting()
{
	uint8_t tx_losl_status_reg_0[2];//0x75-TX_LOSL_STATUS_REG_0
	tx_losl_status_reg_0[0] = 0x75;  
	tx_losl_status_reg_0[1] = 0;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_losl_status_reg_0, 2);
	
	uint8_t tx_txdsbl_input_reg[3];//0x818-TX_TXDSBL_INPUT_REG
	set_u16(tx_txdsbl_input_reg, 0x0818);
	tx_txdsbl_input_reg[2] = 0; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_txdsbl_input_reg, 3);

	uint8_t tx_apc_ovr_reg[3];//0x827-TX_APC_OVR_REG
	set_u16(tx_apc_ovr_reg, 0x0827);
	tx_apc_ovr_reg[2] = 0x01; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_apc_ovr_reg, 3);
	
	uint8_t csr_apc_dac_ovr_val_lo[3];//0x825-CSR_APC_DAC_OVR_VAL_LO
	set_u16(csr_apc_dac_ovr_val_lo, 0x0825);
	csr_apc_dac_ovr_val_lo[2] = 0x00;// 0x98
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, csr_apc_dac_ovr_val_lo, 3);
	
	uint8_t csr_apc_dac_ovr_val_hi[3];//0x826-CSR_APC_DAC_OVR_VAL_HI 
	set_u16(csr_apc_dac_ovr_val_hi, 0x0826);
	csr_apc_dac_ovr_val_hi[2] = 0x00; // 0x01
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, csr_apc_dac_ovr_val_hi, 3);
	
	uint8_t tx_apc_vph_range_sel_reg[3];//0x86E-TX_APC_VPH_RANGE_SEL_REG
	set_u16(tx_apc_vph_range_sel_reg, 0x086E);
	tx_apc_vph_range_sel_reg[2] = 0x04;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS,tx_apc_vph_range_sel_reg, 3);

	uint8_t tx_apc_clk_rates_div_reg[3];//0x824-TX_APC_CLK_RATES_DIV_REG
	set_u16(tx_apc_clk_rates_div_reg, 0x0824);
	tx_apc_clk_rates_div_reg[2] = 0x00;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS,tx_apc_clk_rates_div_reg, 3);
	
//	uint8_t tx_ld_soft_txdsbl_reg[3];//0x85E-TX_LD_SOFT_TXDSBL_REG
//	set_u16(tx_ld_soft_txdsbl_reg, 0x085E);
//	tx_ld_soft_txdsbl_reg[2] = 0x00;
//	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_soft_txdsbl_reg, 3);
	
	uint8_t tx_ld_cpa_ctrl_reg[3];//0x880-TX_LD_CPA_CTRL_REG
	set_u16(tx_ld_cpa_ctrl_reg, 0x0880);
	tx_ld_cpa_ctrl_reg[2] = 0x16;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_cpa_ctrl_reg, 3);
	
	uint8_t tx_ld_vcasc_sel_reg[3];//0x883-TX_LD_VCASC_SEL_REG
	set_u16(tx_ld_vcasc_sel_reg, 0x0883);
	tx_ld_vcasc_sel_reg[2] = 0x04; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_vcasc_sel_reg, 3);
	
	uint8_t tx_ld_imod_ctrl_main_7_0_reg[3];//0x893-TX_LD_IMOD_CTRL_MAIN_7_0_REG
	set_u16(tx_ld_imod_ctrl_main_7_0_reg, 0x0893);
	tx_ld_imod_ctrl_main_7_0_reg[2] = 0x44;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_imod_ctrl_main_7_0_reg, 3);
	
	uint8_t tx_ld_mute_reg[3];//0x8B3-TX_LD_MUTE_REG
	set_u16(tx_ld_mute_reg, 0x08B3);
	tx_ld_mute_reg[2] = 0; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_mute_reg, 3);

	uint8_t rx_prbs5gen_latch_reset_reg[3];//0x1815-rx_prbs5gen_latch_reset_reg
	set_u16(rx_prbs5gen_latch_reset_reg, 0x1815);
	rx_prbs5gen_latch_reset_reg[2] = 0;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_prbs5gen_latch_reset_reg, 3);

	uint8_t rx_los_threshold_reg[3];//0x1847-RX_LOS_THRESHOLD_REG
	set_u16(rx_los_threshold_reg, 0x1847);
	rx_los_threshold_reg[2] = 0x14;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_los_threshold_reg, 3);
	
	uint8_t rx_los_hyst_select_reg[3];//0x1848-RX_LOS_HYST_SELECT_REG
	set_u16(rx_los_hyst_select_reg, 0x1848);
	rx_los_hyst_select_reg[2] = 0x03;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_los_hyst_select_reg, 3);
	
	uint8_t rx_eq_boost_25g_reg[3];//0x184B-RX_EQ_BOOST_25G_REG
	set_u16(rx_eq_boost_25g_reg, 0x184B);
	rx_eq_boost_25g_reg[2] = 0x28;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_eq_boost_25g_reg, 3);
	
	uint8_t rx_sel_man_reset_source_reg[3];//0x186E-RX_LOS_SEL_MAN_RESET_SOURCE_REG
	set_u16(rx_sel_man_reset_source_reg, 0x186E);
	rx_sel_man_reset_source_reg[2] = 0x02;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_sel_man_reset_source_reg, 3);
	
	uint8_t rx_decoder_rateselpolinv_reg[3];//0x1878-RX_DECODER_RATESELPOLINV_REG
	set_u16(rx_decoder_rateselpolinv_reg, 0x1878);
	rx_decoder_rateselpolinv_reg[2] = 0x01;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_decoder_rateselpolinv_reg, 3);
	
	uint8_t rx_man_reset_en_reg[3];//0x187C-RX_MAN_RESET_EN_REG
	set_u16(rx_man_reset_en_reg, 0x187C);
	rx_man_reset_en_reg[2] = 0x01;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_man_reset_en_reg, 3);
	
	uint8_t rx_retime_byp_mux_cdr_lock_mask_en_reg[3];//0x1881-RX_RETIME_BYP_MUX_CDR_LOCK_MASK_EN_REG
	set_u16(rx_retime_byp_mux_cdr_lock_mask_en_reg, 0x1881);
	rx_retime_byp_mux_cdr_lock_mask_en_reg[2] = 0x01;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_retime_byp_mux_cdr_lock_mask_en_reg, 3);
	
	uint8_t rx_drv_auto_mute_en_reg[3];//0x1886-RX_DRV_AUTO_MUTE_EN_REG
	set_u16(rx_drv_auto_mute_en_reg, 0x1886);
	rx_drv_auto_mute_en_reg[2] = 0x01;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_drv_auto_mute_en_reg, 3);
	
	uint8_t csr_rx_pulsewidth_reg_7_0[3];//0x20AB-CSR_RX_PULSEWIDTH_REG_7_0
	set_u16(csr_rx_pulsewidth_reg_7_0, 0x20AB);
	csr_rx_pulsewidth_reg_7_0[2] = 0x07;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, csr_rx_pulsewidth_reg_7_0, 3);
	
	uint8_t tx_ld_bias_mon_en_reg[3];//0x862-TX_LD_BIAS_MON_EN_REG 偏置电流监控上电
	set_u16(tx_ld_bias_mon_en_reg, 0x0862);
	tx_ld_bias_mon_en_reg[2] = 0x01;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_bias_mon_en_reg, 3);
	
	uint8_t tx_pd_supply_sensor_reg[3];//0x863-TX_PD_SUPPLY_SENSOR_REG 工作电压监控上电
	set_u16(tx_pd_supply_sensor_reg, 0x0863);
	tx_pd_supply_sensor_reg[2] = 0x00;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_pd_supply_sensor_reg, 3);
	
	uint8_t tx_en_temp_sensor_reg[3];//0x864-TX_EN_TEMP_SENSOR_REG 温度监控上电
	set_u16(tx_en_temp_sensor_reg, 0x0864);
	tx_en_temp_sensor_reg[2] = 0x00;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_en_temp_sensor_reg, 3);

	//0x0865-TX_ADC_SRC_TO_VPHOTO_REG 背光电流监控使能
	uint8_t tx_adc_src_to_vphoto_reg[3];	
	set_u16(tx_adc_src_to_vphoto_reg, 0x0865);
	tx_adc_src_to_vphoto_reg[2] = 0x01;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_src_to_vphoto_reg, 3);
	
	gn7161_set_rx_swing(0x0064);
	gn7161_set_rx_eq_boost(0x0028);

	/* 清除告警 */
	uint8_t tx_fault_clear_status_reg[3];//0x84B-TX_FAULT_CLEAR_STATUS_REG
	set_u16(tx_fault_clear_status_reg, 0x084B);
	tx_fault_clear_status_reg[2] = 0x01;//0x01 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_fault_clear_status_reg, 3);

}

/***********************************************************************
	** 函 数 名： gn7161_adc
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161的ADC转换
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_adc()
{
		/*ADC上电*/
		uint8_t tx_pd_adc_reg[3];//0x867-TX_PD_ADC_REG
		set_u16(tx_pd_adc_reg, 0x0867);
		tx_pd_adc_reg[2] = 0; 
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_pd_adc_reg, 3);
	
		/*ADC重置、设置ADC手动/自动模式*/
		uint8_t tx_adc_reset_reg[3];//0x82C-TX_ADC_RESET_REG
		set_u16(tx_adc_reset_reg, 0x082C);
		tx_adc_reset_reg[2] = 0; 
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_reset_reg, 3);
	
		uint8_t tx_adc_auto_conv_en_reg[3];//0x82D-TX_ADC_AUTO_CONV_EN_REG
		set_u16(tx_adc_auto_conv_en_reg, 0x082D);
		tx_adc_auto_conv_en_reg[2] = 0; 
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_auto_conv_en_reg, 3);
	
		/*设置ADC分辨率10bit和转换速率3MHz*/
		uint8_t tx_adc_resolution_reg[3];//0x831-TX_ADC_RESOLUTION_REG
		set_u16(tx_adc_resolution_reg, 0x0831);
		tx_adc_resolution_reg[2] = 0x03; 
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_resolution_reg, 3);
		
		uint8_t tx_adc_clk_rate_reg[3];//0x868-TX_ADC_CLK_RETE_REG
		set_u16(tx_adc_clk_rate_reg, 0x0868);
		tx_adc_clk_rate_reg[2] = 0x03; 
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_clk_rate_reg, 3);
		
		/*选择ADC转换的源端*/
		uint8_t tx_adc_src_sel_reg[3];//0x830-TX_ADC_SRC_SEL_REG
		set_u16(tx_adc_src_sel_reg, 0x0830);
		tx_adc_src_sel_reg[2] = 0x02;//00 reference voltage; 01 LD BIAS; 02 IPHOTO VOLTAGE; 04 Temperature Sensor; 06 3.3v supply sensor; 07 1.6v supply sensor 
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_src_sel_reg, 3);
		
		/*启动ADC转换*/
		uint8_t tx_adc_start_conv_reg[3];//0x832-TX_ADC_START_CONV_REG
		set_u16(tx_adc_start_conv_reg, 0x0832);
		tx_adc_start_conv_reg[2] = 0x01; 
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_start_conv_reg, 3);
}

/***********************************************************************
	** 函 数 名： gn7161_source_sink_select
	** 输    入： uint8_t ctrl_switch 1-enable source 0-enable sink
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161选择源宿端
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_source_sink_select(uint8_t ctrl_switch)
{	
		uint8_t tx_ld_bias_source_en_reg[3];//0x85F-TX_LD_BIAS_SOURCE_EN_REG
		set_u16(tx_ld_bias_source_en_reg, 0x85F);
	
		uint8_t tx_ld_bias_sink_en_reg[3];//0x860-TX_LD_BIAS_SINK_EN_REG
		set_u16(tx_ld_bias_sink_en_reg, 0x860);
	
    if(ctrl_switch == 1){
			tx_ld_bias_source_en_reg[2] = 0x01;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_bias_source_en_reg, 3);
			tx_ld_bias_sink_en_reg[2] = 0x00;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_bias_sink_en_reg, 3);
		}
		else{
			tx_ld_bias_source_en_reg[2] = 0x00;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_bias_source_en_reg, 3);
			tx_ld_bias_sink_en_reg[2] = 0x01;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_bias_sink_en_reg, 3);
		}
}

/***********************************************************************
	** 函 数 名： gn7161_apc_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161使能/去使能APC功能
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_apc_ctrl(uint8_t ctrl_switch)
{
	uint8_t tx_apc_en_reg[3];//0x81D-TX_APC_EN_REG
	set_u16(tx_apc_en_reg, 0x81D);
	if(ctrl_switch == 1){
			tx_apc_en_reg[2] = 0x01;
		}
		else{
			tx_apc_en_reg[2] = 0x00;
		}
		master_reg_byte_write(GN7161_SLAVE_ADDRESS,tx_apc_en_reg, 3);
    
}

/***********************************************************************
	** 函 数 名： gn7161_override_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161 使能/去使能上帝模式
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_override_ctrl(uint8_t ctrl_switch)
{
	uint8_t tx_apc_ovr_reg[3];//0x827-TX_APC_OVR_REG
	set_u16(tx_apc_ovr_reg, 0x827);
	if(ctrl_switch == 1){
			tx_apc_ovr_reg[2] = 0x01;
		}
		else{
			tx_apc_ovr_reg[2] = 0x00;
		}
    master_reg_byte_write(GN7161_SLAVE_ADDRESS,tx_apc_ovr_reg, 3);
}
/***********************************************************************
	** 函 数 名： gn7161_temperature_monitor_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable 2-second source
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161使能/去使能温度监控
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_temperature_monitor_ctrl(uint8_t ctrl_switch)
{
	uint8_t tx_adc_src_sel_reg[3];//0x830-TX_ADC_SRC_SEL_REG
	set_u16(tx_adc_src_sel_reg, 0x0830);
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_src_sel_reg, 3);
	if(ctrl_switch == 1){
			tx_adc_src_sel_reg[2] = 0x04;//04 Temperature Sensor;
		}
	else{
			tx_adc_src_sel_reg[2] = 0x02;//02 IPHOTO VOLTAGE;
	}
	master_reg_byte_write(GN7161_SLAVE_ADDRESS,tx_adc_src_sel_reg, 3);
    
}
/***********************************************************************
	** 函 数 名： gn7161_get_temperature
	** 输    入： float* temperature
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161获取温度值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_get_temperature(float* temperature)
{
	uint8_t tx_adc_out_lo_reg[1];
	uint8_t tx_adc_out_hi_reg[1];
	
	uint16_t adc_out = 0;
	gn7161_temperature_monitor_ctrl(1);
	
	/*启动ADC转换*/
	uint8_t tx_adc_start_conv_reg[3];//0x832-TX_ADC_START_CONV_REG
	set_u16(tx_adc_start_conv_reg, 0x0832);
	tx_adc_start_conv_reg[2] = 0x01; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_start_conv_reg, 3);
	//fh_delay_us(1000);
	system_delay_ms(1);
	
	uint8_t tx_adc_done_conv_reg[1];
	master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0833, tx_adc_done_conv_reg, 1);//0x833-TX_ADC_DONE_CONV_REG
	if(tx_adc_done_conv_reg[0] == 1){			
		master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0834, tx_adc_out_lo_reg, 1);//0x834-TX_ADC_OUT_LO_REG 
		master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0835, tx_adc_out_hi_reg, 1);//0x835-TX_ADC_OUT_HI_REG 
		adc_out = tx_adc_out_hi_reg[0] * 256 + tx_adc_out_lo_reg[0];
	}
	*temperature = 0.6038 * adc_out - 299.72;

	//不是在这里取温度值，是在获取壳体温度时赋值的
	//ddm_adc_out_val.temperature_adc_out = adc_out;
}
/***********************************************************************
	** 函 数 名： gn7161_voltage_monitor_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161使能/去使能电压监控
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_voltage_monitor_ctrl(uint8_t ctrl_switch)
{
	uint8_t tx_adc_src_sel_reg[3];//0x830-TX_ADC_SRC_SEL_REG
	set_u16(tx_adc_src_sel_reg, 0x0830);
	if(ctrl_switch == 1){
			tx_adc_src_sel_reg[2] = 0x06;//06 3.3v supply sensor;
	}
	else{
			tx_adc_src_sel_reg[2] = 0x02;//02 IPHOTO VOLTAGE;
	}
	master_reg_byte_write(GN7161_SLAVE_ADDRESS,tx_adc_src_sel_reg, 3);
    
}

/***********************************************************************
	** 函 数 名： gn7161_get_voltage
	** 输    入： float* voltage
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161获取电压值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_get_voltage(float* vcc)
{
	uint8_t tx_adc_out_lo_reg[1];
	uint8_t tx_adc_out_hi_reg[1];
	uint8_t value[2];
	uint16_t adc_out = 0;
	gn7161_voltage_monitor_ctrl(1);
	
	/*启动ADC转换*/
	uint8_t tx_adc_start_conv_reg[3];//0x832-TX_ADC_START_CONV_REG
	set_u16(tx_adc_start_conv_reg, 0x0832);
	tx_adc_start_conv_reg[2] = 0x01; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_start_conv_reg, 3);
	//fh_delay_us(1000);
	system_delay_ms(1);
	
	uint8_t tx_adc_done_conv_reg[1];
	master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0833, tx_adc_done_conv_reg, 1);//0x833-TX_ADC_DONE_CONV_REG
	if(tx_adc_done_conv_reg[0] == 0){			
		master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0834, tx_adc_out_lo_reg, 1);//0x834-TX_ADC_OUT_LO_REG 
		master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0835, tx_adc_out_hi_reg, 1);//0x835-TX_ADC_OUT_HI_REG
		adc_out = tx_adc_out_hi_reg[0] * 256 + tx_adc_out_lo_reg[0];
	}
	*vcc = 0.005586 * adc_out - 0.02313;
	ddm_adc_out_val.voltage_adc_out_0 = adc_out;
}
/***********************************************************************
	** 函 数 名： gn7161_ld_ibias_monitor_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161使能/去使能激光器驱动电流监控
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_ld_ibias_monitor_ctrl(uint8_t ctrl_switch)
{
	uint8_t tx_adc_src_sel_reg[3];//0x830-TX_ADC_SRC_SEL_REG
	set_u16(tx_adc_src_sel_reg, 0x0830);
	if(ctrl_switch == 1){
			tx_adc_src_sel_reg[2] = 0x01;//01 LD BIAS;
	}
	else{
			tx_adc_src_sel_reg[2] = 0x02;//02 IPHOTO VOLTAGE;
	}
	master_reg_byte_write(GN7161_SLAVE_ADDRESS,tx_adc_src_sel_reg, 3);
	  
}
/***********************************************************************
	** 函 数 名： gn7161_get_ld_ibias
	** 输    入： float* vcc
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161获取激光器驱动电流值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_get_ld_ibias(float* ibias)
{
	uint8_t tx_adc_out_lo_reg[1];
	uint8_t tx_adc_out_hi_reg[1];
	uint16_t adc_out = 0;
	
	gn7161_ld_ibias_monitor_ctrl(1);
	
	/*启动ADC转换*/
	uint8_t tx_adc_start_conv_reg[3];//0x832-TX_ADC_START_CONV_REG
	set_u16(tx_adc_start_conv_reg, 0x0832);
	tx_adc_start_conv_reg[2] = 0x01; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_start_conv_reg, 3);
	//fh_delay_us(1000);
	system_delay_ms(1);
	
	uint8_t tx_adc_done_conv_reg[1];
	master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0833, tx_adc_done_conv_reg, 1);//0x833-TX_ADC_DONE_CONV_REG
	if(tx_adc_done_conv_reg[0] == 0){			
		master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0834, tx_adc_out_lo_reg, 1);//0x834-TX_ADC_OUT_LO_REG 
		master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0835, tx_adc_out_hi_reg, 1);//0x835-TX_ADC_OUT_HI_REG
		adc_out = tx_adc_out_hi_reg[0] * 256 + tx_adc_out_lo_reg[0];
	}
	*ibias = om_default_config.tx_i_slope_0 * adc_out + om_default_config.tx_i_offset_0;//mA
	ddm_adc_out_val.ibias_adc_out_0 = adc_out;
}
/***********************************************************************
	** 函 数 名： gn7161_set_ld_ibias
	** 输    入： float* vcc
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161设置激光器驱动电流值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_set_ld_ibias(uint16_t ibias){
	uint8_t ibias_set_val[2];
	set_u16(ibias_set_val, ibias);
	
	uint8_t csr_apc_dac_ovr_val_lo[3];//0x825-CSR_APC_DAC_OVR_VAL_LO
	set_u16(csr_apc_dac_ovr_val_lo, 0x0825);
	csr_apc_dac_ovr_val_lo[2] = ibias_set_val[1];
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, csr_apc_dac_ovr_val_lo, 3);
	
	uint8_t csr_apc_dac_ovr_val_hi[3];//0x826-CSR_APC_DAC_OVR_VAL_HI 
	set_u16(csr_apc_dac_ovr_val_hi, 0x0826);
	csr_apc_dac_ovr_val_hi[2] = ibias_set_val[0]; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, csr_apc_dac_ovr_val_hi, 3);
}
/***********************************************************************
	** 函 数 名： gn7161_mpd_ibias_monitor_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161使能/去使能背光电流监控
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_mpd_ibias_monitor_ctrl(uint8_t ctrl_switch)
{
	
	uint8_t tx_adc_src_sel_reg[3];//0x830-TX_ADC_SRC_SEL_REG
	set_u16(tx_adc_src_sel_reg, 0x0830);

	if(ctrl_switch == 1){
			tx_adc_src_sel_reg[2] = 0x02;//02 IPHOTO VOLTAGE;default
	}

	master_reg_byte_write(GN7161_SLAVE_ADDRESS,tx_adc_src_sel_reg, 3);
    
}
/***********************************************************************
	** 函 数 名： gn7161_get_mpd_ibias
	** 输    入： float* ibias
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161获取激光器背光电流值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_get_mpd_ibias(float* ibias)
{
	uint8_t tx_adc_out_lo_reg[1];
	uint8_t tx_adc_out_hi_reg[1];
	uint16_t adc_out = 0;
	
	gn7161_mpd_ibias_monitor_ctrl(1);
	
	/*启动ADC转换*/
	uint8_t tx_adc_start_conv_reg[3];//0x832-TX_ADC_START_CONV_REG
	set_u16(tx_adc_start_conv_reg, 0x0832);
	tx_adc_start_conv_reg[2] = 0x01; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_adc_start_conv_reg, 3);
	//fh_delay_us(1000);
	system_delay_ms(1);
	
	uint8_t tx_adc_done_conv_reg[1];
	master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0833, tx_adc_done_conv_reg, 1);//0x833-TX_ADC_DONE_CONV_REG
	if(tx_adc_done_conv_reg[0] == 0){			
		master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0834, tx_adc_out_lo_reg, 1);//0x834-TX_ADC_OUT_LO_REG 
		master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS, 0x0835, tx_adc_out_hi_reg, 1);//0x835-TX_ADC_OUT_HI_REG
		adc_out = tx_adc_out_hi_reg[0] * 256 + tx_adc_out_lo_reg[0];
		//adc_out= 793;
	}
	*ibias = 0.000339 * adc_out + 0.000167;//gqhuan 修改
	ddm_adc_out_val.tx_power_adc_out_0 = adc_out;
}

/***********************************************************************
	** 函 数 名： gn7161_set_tx_ld_cpa
	** 输    入： uint8_t value：交叉点调节值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161设置发端交叉点调节值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_set_tx_ld_cpa(uint8_t value)
{
	uint8_t tx_ld_cpa_ctrl_reg[3];//0x880-TX_LD_CPA_CTRL_REG
	set_u16(tx_ld_cpa_ctrl_reg, 0x0880);
	tx_ld_cpa_ctrl_reg[2] = value; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_cpa_ctrl_reg, 3);
	
}

/***********************************************************************
	** 函 数 名： gn7161_set_rx_eq_boost
	** 输    入： uint16_t value：EQ调节值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161设置收端EQ调节值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_set_rx_eq_boost(uint16_t value)
{
	uint8_t rx_eq_boost_25g_reg[3];//0x184B-RX_EQ_BOOST_25G_REG
	set_u16(rx_eq_boost_25g_reg, 0x184B);
	rx_eq_boost_25g_reg[2] = (uint8_t)value; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_eq_boost_25g_reg, 3);

}

/***********************************************************************
	** 函 数 名： gn7161_set_rx_swing
	** 输    入： uint16_t value：swing调节值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161设置收端驱动摆幅
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_set_rx_swing(uint16_t value)
{
	uint8_t rx_swing_val_reg[3];//0x1882-RX_DRV_MAIN_SWING_REG
	set_u16(rx_swing_val_reg, 0x1882);
	rx_swing_val_reg[2] = value; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_swing_val_reg, 3);
}
	
/***********************************************************************
	** 函 数 名： gn7161_set_ld_imod
	** 输    入： float* vcc
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161设置激光器调制电压
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_set_ld_imod(uint16_t imod){
	uint8_t imod_set_val[2];
	set_u16(imod_set_val, imod);
	
	uint8_t tx_ld_imod_ctrl_main_9_8_reg[3];//0x892-TX_LD_IMOD_CTRL_MAIN_9_8_REG 
	set_u16(tx_ld_imod_ctrl_main_9_8_reg, 0x0892);
	tx_ld_imod_ctrl_main_9_8_reg[2] = imod_set_val[0]; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_imod_ctrl_main_9_8_reg, 3);
	
	uint8_t tx_ld_imod_ctrl_main_7_0_reg[3];//0x893-TX_LD_IMOD_CTRL_MAIN_7_0_REG
	set_u16(tx_ld_imod_ctrl_main_7_0_reg, 0x0893);
	tx_ld_imod_ctrl_main_7_0_reg[2] = imod_set_val[1];
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_imod_ctrl_main_7_0_reg, 3);
	
}

/***********************************************************************
	** 函 数 名： gn7161_set_tx_ld_deemph
	** 输    入： uint16_t imod_de 去预加重值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161设置发端去预加重值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_set_tx_ld_deemph(uint16_t imod_de){
	
	uint8_t ld_deemph_powerdown[3];//0x8A2-LD_DEEMPH_POWERDOWN
	set_u16(ld_deemph_powerdown, 0x08A2);
	ld_deemph_powerdown[2] = 0x00;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS,ld_deemph_powerdown, 3);
	
	uint8_t imod_de_set_val[2];
	set_u16(imod_de_set_val, imod_de);
	
	uint8_t tx_ld_imod_ctrl_main_de_9_8_reg[3];//0x896-TX_LD_IMOD_CTRL_MAIN_DE_9_8_REG 
	set_u16(tx_ld_imod_ctrl_main_de_9_8_reg, 0x0896);
	tx_ld_imod_ctrl_main_de_9_8_reg[2] = imod_de_set_val[0]; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_imod_ctrl_main_de_9_8_reg, 3);
	
	uint8_t tx_ld_imod_ctrl_main_de_7_0_reg[3];//0x897-TX_LD_IMOD_CTRL_MAIN_DE_7_0_REG
	set_u16(tx_ld_imod_ctrl_main_de_7_0_reg, 0x0897);
	tx_ld_imod_ctrl_main_de_7_0_reg[2] = imod_de_set_val[1];
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_ld_imod_ctrl_main_de_7_0_reg, 3);
	
}

/***********************************************************************
	** 函 数 名： gn7161_set_rx_drv_deemph
	** 输    入： uint8_t level_de 去预加重值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161设置收端去预加重值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_set_rx_drv_deemph(uint8_t level_de){
	
	uint8_t drv_deemph_powerdown[3];//0x187F-DRIVER_DEEMPH_POWERDOWN
	set_u16(drv_deemph_powerdown, 0x187F);
	drv_deemph_powerdown[2] = 0x00;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS,drv_deemph_powerdown, 3);
	
	uint8_t rx_drv_deemph_level_reg[3];//0x1883-RX_DRV_DEEMPH_LEVEL_REG 
	set_u16(rx_drv_deemph_level_reg, 0x1883);
	rx_drv_deemph_level_reg[2] = level_de; 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, rx_drv_deemph_level_reg, 3);
	
}
/***********************************************************************
	** 函 数 名： gn7161_set_rx_los_threshold
	** 输    入： uint8_t los_th 信号丢失阈值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161设置收端信号丢失阈值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_set_rx_los_threshold(uint8_t los_th){
	
	uint8_t rx_los_threshold[3];//0x1847-RX_LOS_THRESHOLD_REG
	set_u16(rx_los_threshold, 0x1847);
	rx_los_threshold[2] = los_th;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS,rx_los_threshold, 3);
	
}
/***********************************************************************
	** 函 数 名： gn7161_set_rx_los_hyst
	** 输    入： uint8_t los_hyst 信号丢失迟滞值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161设置收端信号丢失迟滞
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_set_rx_los_hyst(uint8_t los_hyst){
	
	uint8_t rx_los_hyst[3];//0x1848-RX_LOS_HYST_SELECT_REG
	set_u16(rx_los_hyst, 0x1848);
	rx_los_hyst[2] = los_hyst;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS,rx_los_hyst, 3);
	
}
/***********************************************************************
	** 函 数 名： gn7161_temperature_sample_average
	** 输    入： float* temperature：多次采样温度的平均值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161温度采样上报的平均值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_temperature_sample_average(float* temperature)
{
    float temp = 0.0;
		float temp_sum = 0.0;
    uint8_t degree = 3;  //读的次数的幂 2^3
    for(int i = 0;i < (1 << degree);i++)
    {
        //读取ADC次数
		gn7161_get_temperature(&temp);
        temp_sum += temp;
       system_delay_ms(1);
    }
    
    //这里循环8次读取,因此 >>3位就是除以8
    * temperature = temp_sum / 8;

}

/***********************************************************************
	** 函 数 名： gn7161_download_firmware
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161载入FW文件
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
#if (FH_IC_GN7161_FIRMWARE_08v21_1_2_8 == CFG_YES)

/*2023 08批次GN7161芯片FW导入程序*/
void gn7161_download_firmware()
{
	/*开始载入FW文件*/
	uint8_t uc_ctl_reg[3];
	uint8_t page_len = 200;
	set_u16(uc_ctl_reg, 0x2068);//0x2068-UC_CTL_REG  
	uc_ctl_reg[2] = 1;//0x0001 step1
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, uc_ctl_reg, 3);
	
	uint8_t booting_completed[3];
	set_u16(booting_completed, 0x205E);//0x205E-BOOTING_COMPLETED  
	booting_completed[2] = 0;//0x0000 step2
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, booting_completed, 3);

	/*设置gn7161 i2c高速*/
	uint8_t i2c_fast_reg[3];
	set_u16(i2c_fast_reg, 0x206a);
	i2c_fast_reg[2] = 5;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, i2c_fast_reg, 3);

	uint8_t fw_byte[220];
	uint16_t i = 0;
	uint16_t k = 0;
	uint16_t idx = 0;
	uint32_t fw_start_addr = FWADDRESS;
	uint16_t fw_image_start = 0x4000;
	
	uint16_t fw_page = FW_LENGTH / page_len;
	uint16_t fw_mod =  FW_LENGTH % page_len;
	
	for(i = 0; i < fw_page;i++)
	{
		idx = 0;
		k = 0;
		memset(fw_byte,0,sizeof(fw_byte));
		set_u16(fw_byte, fw_image_start);
		idx += 2;

		while(k < page_len)
		{
			*(uint64_t*)&fw_byte[idx] = REG64(fw_start_addr + k);
			idx += 8;
			k += 8;			
		}		
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, fw_byte, idx);
		fw_start_addr = fw_start_addr + page_len;
		fw_image_start = fw_image_start + page_len;
	}

	if(fw_mod != 0)
	{
		idx = 0;
		k = 0;
		memset(fw_byte,0,sizeof(fw_byte));
		set_u16(fw_byte, fw_image_start);
		idx += 2;

		for(k = 0; k < fw_mod;k++)
		{
			fw_byte[idx++] = REG8(fw_start_addr++);
		}
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, fw_byte, idx);
	}
	
	uc_ctl_reg[2] = 3;//0x2068-UC_CTL_REG  0x0003 step4
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, uc_ctl_reg, 3);
	
	uc_ctl_reg[2] = 2;//0x2068-UC_CTL_REG  0x0002 step5
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, uc_ctl_reg, 3);
	
}

#elif (FH_IC_GN7161_FIRMWARE_0Bv21_1_2_10 == CFG_YES)

/*2023 0B 批次GN7161芯片FW导入程序*/
void gn7161_download_firmware()
{
	/*开始载入FW文件*/
	uint8_t uc_ctl_reg[3];
	uint8_t page_len = 200;
	set_u16(uc_ctl_reg, 0x2068);//0x2068-UC_CTL_REG  
	uint8_t booting_completed[3];
	set_u16(booting_completed, 0x205E);//0x205E-BOOTING_COMPLETED  
	booting_completed[2] = 0;//0x0000 step1
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, booting_completed, 3);

	/*设置gn7161 i2c高速*/
	uint8_t i2c_fast_reg[3];
	set_u16(i2c_fast_reg, 0x206a);
	i2c_fast_reg[2] = 5;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, i2c_fast_reg, 3);

	uint8_t fw_byte[220];
	uint16_t i = 0;
	uint16_t k = 0;
	uint16_t idx = 0;
	uint32_t fw_start_addr = FWADDRESS;
	uint16_t fw_image_start = 0x4000;
	
	uint16_t fw_page = FW_LENGTH / page_len;
	uint16_t fw_mod =  FW_LENGTH % page_len;
	
	for(i = 0; i < fw_page;i++)
	{
		idx = 0;
		k = 0;
		memset(fw_byte,0,sizeof(fw_byte));
		set_u16(fw_byte, fw_image_start);
		idx += 2;

		while(k < page_len)
		{
			*(uint64_t*)&fw_byte[idx] = REG64(fw_start_addr + k);
			idx += 8;
			k += 8;			
		}		
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, fw_byte, idx);
		fw_start_addr = fw_start_addr + page_len;
		fw_image_start = fw_image_start + page_len;
	}

	if(fw_mod != 0)
	{
		idx = 0;
		k = 0;
		memset(fw_byte,0,sizeof(fw_byte));
		set_u16(fw_byte, fw_image_start);
		idx += 2;

		for(k = 0; k < fw_mod;k++)
		{
			fw_byte[idx++] = REG8(fw_start_addr++);
		}
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, fw_byte, idx);
	}
	
	uc_ctl_reg[2] = 2;//0x2068-UC_CTL_REG  0x0002 step3
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, uc_ctl_reg, 3);
	
	uc_ctl_reg[2] = 3;//0x2068-UC_CTL_REG  0x0003 step4
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, uc_ctl_reg, 3);
	
}

#else

#error "no define gn7161 firmware"

#endif

/***********************************************************************
	** 函 数 名： gn7161_tx_lane_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable 
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161开闭发端lane
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_tx_lane_ctrl(uint8_t ctrl_switch)
{	
	uint8_t lane_reg[3];//0xE301
	set_u16(lane_reg, 0xE301);
	uint8_t cmd_code_reg[3];//0xE302
	set_u16(cmd_code_reg, 0xE302);
	uint8_t input_data_reg[3];//0xE303 
	set_u16(input_data_reg, 0xE303);
	uint8_t cmd_ctrl_and_status_reg[3];//0xE300
	set_u16(cmd_ctrl_and_status_reg, 0xE300);
	
	if(ctrl_switch == 1){
			lane_reg[2] = 0x00;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,lane_reg, 3);
			
			cmd_code_reg[2] = 0x10;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_code_reg, 3);
			
			input_data_reg[2] = 0x01;//enable
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,input_data_reg, 3);
			
			cmd_ctrl_and_status_reg[2] = 0x01;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_ctrl_and_status_reg, 3);
	}
	else{
			lane_reg[2] = 0x00;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,lane_reg, 3);
			
			cmd_code_reg[2] = 0x10;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_code_reg, 3);
			
			input_data_reg[2] = 0x00;//disable
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,input_data_reg, 3);
			
			cmd_ctrl_and_status_reg[2] = 0x01;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_ctrl_and_status_reg, 3);
	}
		
}

/*****************************************************************************
 * 函 数 名  : gn7161_apc_auto_enable_ctrl
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : apc自动控制使用
 * 输入参数  : uint8_t ctrl_switch  1--使能；
                                    0--去使能
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void gn7161_apc_auto_enable_ctrl(uint8_t ctrl_switch)
{
	uint8_t value[10];
	uint8_t temp_data = 0;
	uint8_t mask = 0;
	uint8_t apc_ovr = 0;
	uint16_t reg = 0x081D; /*APC_Loop*/
	uint8_t apc_reg0x81d_value = 0;
	uint8_t apc_reg0x86e_value = 0;

	memset(value,0,sizeof(value));	
	
	master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS,reg,&apc_reg0x81d_value,1);
	
	reg = 0x0821;/*LD_BIAS_TXDSBL_MASK,[0:0]*/
	master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS,reg,&mask,1);

	reg = 0x0827;/*TX_APC_OVR,REG[0]*/
	master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS,reg,&apc_ovr,1);

	
	reg = 0x086e;/*TX_APC_VPH_RANGE_SEL_REG[2:0]*/
	master_reg_2byte_size_read(GN7161_SLAVE_ADDRESS,reg,&apc_reg0x86e_value,1);


//	gn7161_soft_txdsbl_ctrl(1);
	
	if(1 == ctrl_switch)
	{
		/*使能apc时，要把mask disable*/
		reg = 0x0821;		
		temp_data = (mask & ~0x1);	
		memset(value,0,sizeof(value));
		set_u16(value, reg);
		value[2] = temp_data;
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, value, 3);		

		/*设置APC_OVR*/
		reg = 0x0827;
		temp_data = (apc_ovr & ~0x1); /*reg[0] APC_OVR,set low*/
		memset(value,0,sizeof(value));
		set_u16(value,reg);
		value[2] = temp_data;
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, value, 3);	

#if 0
		/*设置iphto*/
		reg = 0x086e;
		temp_data = apc_reg0x86e_value >> 3;
		temp_data = (temp_data << 3) + 0x2;
		memset(value,0,sizeof(value));
		set_u16(value,reg);
		value[2] = temp_data;
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, value, 3);	
#endif
		if(0 == (apc_reg0x81d_value & 0x1))
		{
			/*APC_Loop*/
			apc_reg0x81d_value |= 0x1;/*enable*/		
			reg = 0x081D;
			memset(value,0,sizeof(value));
			set_u16(value,reg);
			value[2] = apc_reg0x81d_value;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS, value, 3);

			reg = 0x0820;
			memset(value,0,sizeof(value));
			set_u16(value,reg);
			value[2] |= (1 << 3);
			master_reg_byte_write(GN7161_SLAVE_ADDRESS, value, 3);
		}
		
		
	}
	else
	{
		/*设置APC_OVR*/
		memset(value,0,sizeof(value));
		reg = 0x0827;/*TX_APC_OVR,REG[0]*/	
		temp_data = (apc_ovr | 0x1);/*reg[0] APC_OVR,set high*/	
		set_u16(value,reg);
		value[2] = temp_data;
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, value, 3);	

		/*读取mask*/
		memset(value,0,sizeof(value));
		reg = 0x0821;/*LD_BIAS_TXDSBL_MASK,[0:0]*/
		temp_data= (mask | 1);/*使能apc时，要把mask enable*/		
		set_u16(value, reg);
		value[2] = temp_data;
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, value, 3);		

#if 0
		/*APC_Loop*/
		apc_reg0x81d_value &= ~0x1;/*disable*/		
		reg = 0x081D;
		memset(value,0,sizeof(value));
		set_u16(value,reg);
		value[2] = apc_reg0x81d_value;
		master_reg_byte_write(GN7161_SLAVE_ADDRESS, value, 3);
#endif		
	}

	//gn7161_soft_txdsbl_ctrl(0);	
	/* 清除告警 */
	uint8_t tx_fault_clear_status_reg[3];//0x84B-TX_FAULT_CLEAR_STATUS_REG
	set_u16(tx_fault_clear_status_reg, 0x084B);
	tx_fault_clear_status_reg[2] = 0x01;//0x01 
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, tx_fault_clear_status_reg, 3);

	return;
}

/*****************************************************************************
 * 函 数 名  : gn7161_apc_target_voltage
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : 设置apc目标电压
 * 输入参数  : uint8_t voltage_target :APC target电压,单位毫伏
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : Set APC final target reference threshold (0V to 1V range in
               steps of 4mV

*****************************************************************************/
void gn7161_apc_target_voltage(float voltage_target)
{

	uint8_t value[10];
	uint16_t reg = 0x0869;
	uint8_t tmp_data = 0;
	float tmp_float = 0.0;

	tmp_float = (voltage_target > 1000.0) ? 1000.0 : voltage_target;	

	tmp_data = tmp_float / 4;

	memset(value,0,sizeof(value));
	set_u16(value,reg);
	value[2] = tmp_data;
	master_reg_byte_write(GN7161_SLAVE_ADDRESS, value, 3);

	return;
}

/***********************************************************************
	** 函 数 名： gn7161_tx_lane_polarity_inversion
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable 
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： GN7161发端lane极性反转
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void gn7161_tx_lane_polarity_inversion(uint8_t ctrl_switch)
{	
	uint8_t lane_reg[3];//0xE301
	set_u16(lane_reg, 0xE301);
	uint8_t cmd_code_reg[3];//0xE302
	set_u16(cmd_code_reg, 0xE302);
	uint8_t input_data_reg[3];//0xE303 
	set_u16(input_data_reg, 0xE303);
	uint8_t cmd_ctrl_and_status_reg[3];//0xE300
	set_u16(cmd_ctrl_and_status_reg, 0xE300);
	
	if(ctrl_switch == 1){
			#if 0
			/*关闭lane数据通道*/
			lane_reg[2] = 0x00;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,lane_reg, 3);
			
			cmd_code_reg[2] = 0x10;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_code_reg, 3);
			
			input_data_reg[2] = 0x00;//disable
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,input_data_reg, 3);
			
			cmd_ctrl_and_status_reg[2] = 0x01;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_ctrl_and_status_reg, 3);

			system_delay_ms(10);
			#endif

			/*发端lane极性反转使能*/
			lane_reg[2] = 0x00;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,lane_reg, 3);
			
			cmd_code_reg[2] = 0x13;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_code_reg, 3);
			
			input_data_reg[2] = 0x01;//enable
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,input_data_reg, 3);
			
			cmd_ctrl_and_status_reg[2] = 0x01;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_ctrl_and_status_reg, 3);

			system_delay_ms(10);

			#if 0
			/*打开lane数据通道*/
			lane_reg[2] = 0x00;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,lane_reg, 3);
			
			cmd_code_reg[2] = 0x10;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_code_reg, 3);
			
			input_data_reg[2] = 0x01;//enable
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,input_data_reg, 3);
			
			cmd_ctrl_and_status_reg[2] = 0x01;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_ctrl_and_status_reg, 3);

			system_delay_ms(10);
			#endif
	}
	else{
			#if 0
			/*关闭lane数据通道*/
			lane_reg[2] = 0x00;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,lane_reg, 3);
			
			cmd_code_reg[2] = 0x10;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_code_reg, 3);
			
			input_data_reg[2] = 0x00;//disable
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,input_data_reg, 3);
			
			cmd_ctrl_and_status_reg[2] = 0x01;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_ctrl_and_status_reg, 3);

			system_delay_ms(10);
			#endif

			/*发端lane极性反转去使能*/
			lane_reg[2] = 0x00;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,lane_reg, 3);
			
			cmd_code_reg[2] = 0x13;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_code_reg, 3);
			
			input_data_reg[2] = 0x00;//disable
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,input_data_reg, 3);
			
			cmd_ctrl_and_status_reg[2] = 0x01;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_ctrl_and_status_reg, 3);

			system_delay_ms(10);

			#if 0
			/*打开lane数据通道*/
			lane_reg[2] = 0x00;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,lane_reg, 3);
			
			cmd_code_reg[2] = 0x10;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_code_reg, 3);
			
			input_data_reg[2] = 0x01;//enable
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,input_data_reg, 3);
			
			cmd_ctrl_and_status_reg[2] = 0x01;
			master_reg_byte_write(GN7161_SLAVE_ADDRESS,cmd_ctrl_and_status_reg, 3);

			system_delay_ms(10);
			#endif
	}
		
}

#endif
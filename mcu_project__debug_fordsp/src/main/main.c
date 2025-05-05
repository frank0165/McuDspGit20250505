/*!
    \file    main.c
    \brief   mcu control code
    \version 2024-01-01, V1.0.0, firmware for GD32E501
*/

/*
    Copyright (c) 2024, Fiberhome Inc.

*/
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "prj_header_directory.h"

#if 0
#include "gd32e501_it.h"
#include "systick.h"
#include "user_config.h"
#include "mcu_pin_type.h"
#include "mcu_data_type.h"
#include "mcu_global_vars_param.h"
#include "mcu_system_comm.h"
#include "mcu_config_public.h"
#include "com_usart_comm.h"
#include "adc_sample_interface.h"
#include "i2c_comm.h"
#include "dac_comm.h"
#include "tec_comm.h"
#include "tec_i2c_interface.h"
#include "timer_comm.h"
#include "update_comm.h"
#include "update_i2c_interface.h"
#include "sff_8472.h"
#include "ddm_i2c_interface.h"
#include "ddm_sff_i2c_interface.h"
#include "ddm_50g_config_interface.h"
#include "ddm_10g_config_interface.h"
#include "ddm_1g_config_interface.h"
#include "trigger_interrupt_mode.h"
#include "mailbox_i2c_interface.h"

#endif



/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/





//extern uint8_t g_ddm_sw_auto_process_flag;


/*****************************************************************************
 * 函 数 名  : i2c_cmd_register_init
 * 负 责 人  : fz
 * 创建日期  : 2023年11月21日
 * 函数功能  : 主从i2c命令注册功能
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 

*****************************************************************************/
static void i2c_cmd_register_init()
{
    /*与OLT交互*/
	i2c_slave_func_register_write_callback(I2C_MCU_SPEC_ADDR,mcu_addr0xspec_reg_byte_write);
	i2c_slave_func_register_read_callback(I2C_MCU_SPEC_ADDR,mcu_addr0xspec_reg_byte_read);


	/*A0 flash读写*/
	i2c_slave_func_register_write_callback(I2C_8472_A0_ADDR,om_flash_write_reg_byte);
	i2c_slave_func_register_read_callback(I2C_8472_A0_ADDR,om_v2_flash_read_reg_byte);
	
	/*A2 flash读写*/
	i2c_slave_func_register_write_callback(I2C_8472_A2_ADDR,om_flash_write_reg_byte);
	i2c_slave_func_register_read_callback(I2C_8472_A2_ADDR,om_v2_flash_read_reg_byte);
	
	/*B0 flash读写*/
	i2c_slave_func_register_write_callback(I2C_8472_B0_ADDR,om_flash_write_reg_byte);
	i2c_slave_func_register_read_callback(I2C_8472_B0_ADDR,om_v2_flash_read_reg_byte);
	
	/*B2 flash读写*/
	i2c_slave_func_register_write_callback(I2C_8472_B2_ADDR,om_flash_write_reg_byte);	
	i2c_slave_func_register_read_callback(I2C_8472_B2_ADDR,om_v2_flash_read_reg_byte);

	/*C0 flash读写*/
	i2c_slave_func_register_write_callback(I2C_8472_C0_ADDR,om_flash_write_reg_byte);
	i2c_slave_func_register_read_callback(I2C_8472_C0_ADDR,om_v2_flash_read_reg_byte);
	
	/*C2 flash读写*/
	i2c_slave_func_register_write_callback(I2C_8472_C2_ADDR,om_flash_write_reg_byte);	
	i2c_slave_func_register_read_callback(I2C_8472_C2_ADDR,om_v2_flash_read_reg_byte);

	/*a2 温度/电压/偏置电流/发送功率/接收功率上报，调试使用，与上位机轮询界面要交互*/
	i2c_slave_func_register_read_callback(I2C_8472_MEM_A2_ADDR,om_v2_memory_read_reg_byte);

	/*b2 温度/电压/偏置电流/发送功率/接收功率上报*/
	i2c_slave_func_register_read_callback(I2C_8472_MEM_B2_ADDR,om_v2_memory_read_reg_byte);

	/*c2 温度/电压/偏置电流/发送功率/接收功率上报*/
	i2c_slave_func_register_read_callback(I2C_8472_MEM_C2_ADDR,om_v2_memory_read_reg_byte);

	i2c_slave_func_register_read_callback(I2C_FLASH_A8_ADDR,cfg_v2_flash_read_reg_byte);
	
	
    /*mcu升级app*/
	mcu_register_reg_addr_write_callback(UPGRADE_APP_SOFTWARE_REG,update_app_write_reg_byte);

    /*mcu升级firmware*/
	mcu_register_reg_addr_write_callback(UPGRADE_FIRMWARE_REG,update_firmware_write_reg_byte);

    /*回读版本信息*/
	mcu_register_reg_addr_read_callback(UPGRADE_DEV_VERSION_INFO_REG,upgrade_dev_version_reg_read);


	/*温度/电压/偏置电流/发送功率/接收功率AD上报*/
	mcu_register_reg_addr_read_callback(CMD_MODULE_DDM_INFO_REG,om_cmd_ddm_read_reg_byte);

    /*上位机写密码*/
	mcu_register_reg_addr_write_callback(CMD_OPTICAL_PASSWORD_LIMIT_REG,user_check_password_write_reg);

    /*上位机控制ddm轮询标识*/
	mcu_register_reg_addr_write_callback(CMD_DDM_SWITCH_ATUO_PROCESS_REG,ddm_i2c_switch_auto_process_reg_write);

	/*VAPD设置*/
	mcu_register_reg_addr_write_callback(APD_SET_VOLTAGE_REG,apd_i2c_vcc_reg_write);
	/*SOA电流设置*/
	mcu_register_reg_addr_write_callback(CMD_SOA_ELECTRIC_REG,soa_i2c_ild_reg_write);
	/*EA负压设置*/
	mcu_register_reg_addr_write_callback(CMD_NEG_VOLTAGE_REG,vea_i2c_vcc_reg_write);
	/*IBIAS电流设置*/
	mcu_register_reg_addr_write_callback(CMD_IBIAS_DRV_LD_REG,ibias_i2c_reg_write);
	/*IMOD调制电流设置*/
	mcu_register_reg_addr_write_callback(CMD_IMOD_DRV_LD_REG,imod_i2c_reg_write);
	/*RX_SWING收端摆幅设置*/
	mcu_register_reg_addr_write_callback(CMD_RX_SWING_DRV_LD_REG,swing_i2c_reg_write);
	/*RX_EQ收端均衡设置*/
	mcu_register_reg_addr_write_callback(CMD_RX_EQ_DRV_LD_REG,rx_eq_i2c_reg_write);
	/*TxCross交叉点设置*/
	mcu_register_reg_addr_write_callback(CMD_TX_LD_CROSS_POINT_ADJUSt_REG,cpa_i2c_reg_write);
	/*Tx_DeEmph发端去预加重设置*/
	mcu_register_reg_addr_write_callback(CMD_TX_LD_DE_EMPH_REG,tx_deemph_i2c_reg_write);
	/*Rx_DeEmph收端去预加重设置*/
	mcu_register_reg_addr_write_callback(CMD_RX_LD_DE_EMPH_REG,rx_deemph_i2c_reg_write);
	/*SDA设置 RX Loss Hyst*/
	mcu_register_reg_addr_write_callback(CMD_SIGNAL_DETECT_ASSERT_REG,rx_los_threshold_i2c_reg_write);
	/*SDD设置 RX Loss Threshold*/
	mcu_register_reg_addr_write_callback(CMD_SIGNAL_DETECT_DE_ASSERT_REG,rx_los_hyst_i2c_reg_write);

	//导入已经调试成功的配置数据
	mcu_register_reg_addr_write_callback(CMD_OPTICAL_MODULE_CFG_FLASH,import_binary_file_data_to_mcu_flash);

    /*读取当前tec控制的温度*/
	mcu_register_reg_addr_read_callback(TEC_CTL_TEMP,tec_i2_ctl_temperature_reg_read);

    /*上位机配置tec vctl*/
	mcu_register_reg_addr_write_callback(TEC_VTEC_CTL_REG,tec_i2c_vtec_ctl_reg_write);

    /*上位获取当前tec vctl*/
	mcu_register_reg_addr_read_callback(TEC_VTEC_CTL_REG,tec_i2c_vtec_ctl_reg_read);

    /*上位机使能tec 自动演算*/
	mcu_register_reg_addr_write_callback(TEC_CALC_CTRL_AUTO_REG,tec_i2c_calc_ctl_auto_reg_write);

    /*上位机读取tec的状态寄存器*/
	mcu_register_reg_addr_read_callback(TEC_XTEC_VALUE_REG,tec_xtec_value_reg_read);

    /*上位机配置tec的目标温度*/
	mcu_register_reg_addr_write_callback(TEC_TEMP_OBJ_CFG_REG,tec_i2c_temperature_obj_write);

	/*保存默认寄存器配置到flash内存*/
	mcu_register_reg_addr_write_callback(CMD_COMMAND_MAP_REG,cmd_command_map_reg_write);

    /*上位机读取配置的长度*/
	mcu_register_reg_addr_read_callback(CMD_COMMON_READ_REG,cmd_common_reg_read);

    /*上位机读取50g monitor的采样值*/
	mcu_register_reg_addr_read_callback(CMD_DDM_50G_MONITOR_REG,ddm_i2c_50g_monitor_reg_read);

    mcu_register_reg_addr_read_callback(CMD_MONITOR_I2C_STATUS_REG,monitor_i2c_status_reg_read);

   // mcu_register_reg_addr_read_callback(CMD_DSP_TICKS_REG,mailbox_i2c_dsp_ticks_reg_read);
   //  mcu_register_reg_addr_read_callback(CMD_DSP_FW_VERSION_REG,mailbox_i2c_dsp_fw_reg_read);
	
	/*A2/B2/C2 状态位和控制位写入*/
	i2c_slave_func_register_write_callback(I2C_8472_MEM_A2_ADDR,om_memory_state_ctrl_write_reg_byte);
	i2c_slave_func_register_write_callback(I2C_8472_MEM_B2_ADDR,om_memory_state_ctrl_write_reg_byte);
	i2c_slave_func_register_write_callback(I2C_8472_MEM_C2_ADDR,om_memory_state_ctrl_write_reg_byte);

#if (MCU_TEST_FUNS_CFG == MCU_CFG_YES)
	//mcu_register_reg_addr_write_callback(TEST_TEC_EN_SD_REG,test_tec_en_sd_write);	
	//mcu_register_reg_addr_read_callback(TEST_TEC_EN_SD_REG,test_tec_en_sd_read);
	mcu_register_reg_addr_write_callback(TEST_I2C_RESTART_REG,test_i2c_restart_reg_write);
	mcu_register_reg_addr_write_callback(TEST_TEC_RESET_REG,test_tec_i2c_rest_gpio_write);
	mcu_register_reg_addr_write_callback(TEST_DSP_FSL_RSTPIN_REG,dsp_fsl_i2c_rst_pin_reg_write);
	mcu_register_reg_addr_write_callback(TEST_DSP_FSL_INFO_REG,dsp_fsl_i2c_data_path_reg_write);
	mcu_register_reg_addr_read_callback(TEST_DSP_FSL_INFO_REG,dsp_fsl_i2c_info_reg_read);
	mcu_register_reg_addr_write_callback(TEST_DSP_FSL_DOWNLOAD_REG,dsp_fsl_i2c_start_download_reg_write);
	
	mcu_register_reg_addr_write_callback(TEST_DAC_PIN_REG,test_dac_value_write_reg);
	mcu_register_reg_addr_write_callback(TEST_GPIO_PIN_REG,test_gpio_value_write_reg);
	mcu_register_reg_addr_write_callback(TEST_GPIO_INFO_REG,test_gpio_info_write_reg);
	mcu_register_reg_addr_read_callback(TEST_GPIO_INFO_REG,test_gpio_info_read_reg);
//	mcu_register_reg_addr_read_callback(TEST_READ_PRINT_BUFF_REG,
		//					debug_read_printf_buff_read_reg);
#endif


}
 //uint32_t g_dd[] = {0x39316239, 0x3932355f, 0x62795f56, 0x305f3000,
   // 0x00000007};

//extern int dsp_fw_download(uint32_t fw_addr);
extern void dsp_fsl_init();
 extern uint32_t dsp_fsl_ic_download();
 extern void ddm_50g_set_rx_vapd(float apd_vcc);
 extern void dsp_fsl_run_hpll();
int main(void)
{      
	/*如果没有这个设置，启动后程序将不会跳转*/
	nvic_vector_table_set(NVIC_VECTTAB_FLASH,AAPPLICATIONADDRESS);	

	printf("start Ab_Sf\r\n");
	
	
	rcu_config_init();		
	systick_config();	
    syscfg_config();
    
    global_vars_param_init();
    
    /*usart串口，调试时使用*/
	com_usart_init();		
	i2c_config_init();
	
	dac_config_init();
	adc_sample_init();

    /* delete by fangzhe, 20250321, 原因:只用系统时钟 */
	//timer_process_init();

    /*i2c注册接口***/
	i2c_cmd_register_init();

    /*flash配置初始化*/
	flash_config_init();

    /*tec初始化*/
	tec_config_init();

    system_delay_ms(100);
    /*ddm各初始化*/
	ddm_50g_dev_init();
	ddm_10g_dev_init();
	ddm_1g_dev_init();

    /*trigger脚初始化*/
	mcu_trigger_mode_init();

    /*启动tec自动调节*/
	tec_start_auto_adjust();
	

    /*默认配置初始化*/
	om_default_config_flash_init();
    dsp_fsl_ic_download();
    
    
    /* add by fangzhe, 20250327, 原因:调试状态时tec不调节且配置为0状态 */
	tec_set_default_mini_status();
     
	   
    
	while(1)
	{	
		i2c_slave_read_write_handle();
		//fh_delay_us(1);
		
	#if 1
		/* add by fz, 20250307, 原因:启动后显示打印点 ，主要是看系统是否正常运行*/
		if(PRINT_CHECK_MS_TASK > 1000) 			
		{
			PRINT_CHECK_MS_TASK = 0;
			PRINTOUT(".");
            //float temp_vol = 0.0;
           // get_tec_therm_temperature(&temp_vol);
          //  PRINTOUT("rth(%.2f)\r\n",temp_vol);
          // dsp_fsl_run_hpll();
			
		}
	#endif		

    #if 1
		if(SET == g_mcu_vars_param.g_ddm_sw_auto_process_flag)		
		{
			tec_process();	
			ddm_process();
		}
	#endif	
		
		
	}
	
	
}


/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t) ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}

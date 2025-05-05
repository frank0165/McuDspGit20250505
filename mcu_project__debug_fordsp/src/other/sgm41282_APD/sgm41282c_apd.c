/***********************************************************************
	* 文 件 名： sgm41282c.c
	* 负 责 人： gqhuan
	* 创建日期： 2023-02
	* 文件描述： SGM41282C升压采保芯片功能函数
	* 版权说明： Copyright (c) 1999-2023    烽火通信科技股份有限公司
	* 其    他： 
	* 修改日志： 
************************************************************************/
#include "sgm41282c_apd.h"
#include "dac_comm.h"

#if defined(FH_IC_SGM41282C_HARDWARE) && (FH_IC_SGM41282C_HARDWARE == CFG_YES)

//extern volatile DDM_ADC_OUT_VAL ddm_adc_out_val;//外部ddm监控变量ADC值

/***********************************************************************
	** 函 数 名： sgm41282c_init
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41282c初始化
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm41282c_init()
{		


	/*********************** 50GPON ************************/
	sgm41282c_gpio_50g_init();

	/* DAC-VS引脚输出电压增量 */
	float apd_vcc = 0;
	sgm41282c_set_apd(apd_vcc,0);


	/*********************** 10GPON ************************/
	
    sgm41282c_gpio_10g_init();
	/* DAC-VS引脚输出电压增量 */
	float apd_vcc_10g = 0;
	sgm41282c_set_apd(apd_vcc_10g,1);

	/*********************** 1GPON ************************/
	
    sgm41282c_gpio_1g_init();
	/* DAC-VS引脚输出电压增量 */
	float apd_vcc_1g = 0;
	sgm41282c_set_apd(apd_vcc_1g,2);
	

}



/*****************************************************************************
 * 函 数 名  : sgm41282c_gpio_50g_init
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月26日
 * 函数功能  : 50g sgm41282引脚初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void sgm41282c_gpio_50g_init()
{
    /* configure GPIO PC9 as EN */
	gpio_mode_set(GPIO_EN_PORT_50G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_EN_PIN_50G);
	gpio_output_options_set(GPIO_EN_PORT_50G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_EN_PIN_50G);

	/* configure GPIO PC11 as GAIN */
	gpio_mode_set(GPIO_GAIN_PORT_50G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_GAIN_PIN_50G);
	gpio_output_options_set(GPIO_GAIN_PORT_50G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_GAIN_PIN_50G);

	/* configure GPIO PC10 as THXOR */
	gpio_mode_set(GPIO_THXOR_PORT_50G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_THXOR_PIN_50G);
	gpio_output_options_set(GPIO_THXOR_PORT_50G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_THXOR_PIN_50G);

   /* GPIO PC9-EN引脚使能电压芯片 */
	//gpio_bit_set(GPIOC, GPIO_PIN_9);
	gpio_bit_set(GPIO_EN_PORT_50G,GPIO_EN_PIN_50G);

	/* GPIO PC11-GAIN低位设置1倍增益 高位8倍增益*/
	//gpio_bit_reset(GPIOC, GPIO_PIN_11);
	gpio_bit_reset(GPIO_GAIN_PORT_50G,GPIO_GAIN_PIN_50G);

	/* GPIO PC10-THXOR低位*/
	//gpio_bit_reset(GPIOC, GPIO_PIN_10);
	gpio_bit_reset(GPIO_THXOR_PORT_50G,GPIO_THXOR_PIN_50G);
    
}


/*****************************************************************************
 * 函 数 名  : sgm41282c_gpio_10g_init
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月26日
 * 函数功能  : 10g sgm41282压引脚初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void sgm41282c_gpio_10g_init()
{
    
	/* configure GPIO PC3 as EN */
	gpio_mode_set(GPIO_EN_PORT_10G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_EN_PIN_10G);
	gpio_output_options_set(GPIO_EN_PORT_10G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_EN_PIN_10G);

	/* configure GPIO PB15 as GAIN */
	gpio_mode_set(GPIO_GAIN_PORT_10G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_GAIN_PIN_10G);
	gpio_output_options_set(GPIO_GAIN_PORT_10G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_GAIN_PIN_10G);

	/* configure GPIO PB12 as THXOR */
	gpio_mode_set(GPIO_THXOR_PORT_10G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_THXOR_PIN_10G);
	gpio_output_options_set(GPIO_THXOR_PORT_10G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_THXOR_PIN_10G);

    /* GPIO PC3-EN引脚使能电压芯片 */
	//gpio_bit_set(GPIOC, GPIO_PIN_3);
	gpio_bit_set(GPIO_EN_PORT_10G,GPIO_EN_PIN_10G);

	/* GPIO PB15-GAIN低位设置1倍增益 高位8倍增益*/
	//gpio_bit_reset(GPIOB, GPIO_PIN_15);
	gpio_bit_set(GPIO_GAIN_PORT_10G,GPIO_GAIN_PIN_10G);

	/* GPIO PB12-THXOR低位*/
	//gpio_bit_reset(GPIOB, GPIO_PIN_12);
	gpio_bit_set(GPIO_THXOR_PORT_10G,GPIO_THXOR_PIN_10G);

}

/*****************************************************************************
 * 函 数 名  : sgm41282c_gpio_1g_init
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月26日
 * 函数功能  : 1g sgm41282引脚初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void sgm41282c_gpio_1g_init()
{
    /* configure GPIO PC15 as EN */
	gpio_mode_set(GPIO_EN_PORT_1G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_EN_PIN_1G);
	gpio_output_options_set(GPIO_EN_PORT_1G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_EN_PIN_1G);

	/* configure GPIO PF1 as GAIN */
	gpio_mode_set(GPIO_GAIN_PORT_1G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_GAIN_PIN_1G);
	gpio_output_options_set(GPIO_GAIN_PORT_1G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_GAIN_PIN_1G);

	/* configure GPIO PF0 as THXOR */
	gpio_mode_set(GPIO_THXOR_PORT_1G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_THXOR_PIN_1G);
	gpio_output_options_set(GPIO_THXOR_PORT_1G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_THXOR_PIN_1G);

    /* GPIO PC15-EN引脚使能电压芯片 */
	//gpio_bit_set(GPIOC, GPIO_PIN_15);
	gpio_bit_set(GPIO_EN_PORT_1G,GPIO_EN_PIN_1G);

	/* GPIO PF1-GAIN低位设置1倍增益 高位8倍增益*/
	//gpio_bit_reset(GPIOF, GPIO_PIN_1);
	gpio_bit_set(GPIO_GAIN_PORT_1G,GPIO_GAIN_PIN_1G);

	/* GPIO PF0-THXOR低位*/
	//gpio_bit_reset(GPIOF, GPIO_PIN_0);
	gpio_bit_set(GPIO_THXOR_PORT_1G,GPIO_THXOR_PIN_1G);
}






/***********************************************************************
	** 函 数 名： sgm41282c_reset
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41282c复位
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm41282c_reset()
{
	/* 设置软复位 */
	
}


/***********************************************************************
	** 函 数 名： sgm41282c_get_rssi_value
	** 输    入： uint16_t* rssi 采保值
							 uint8_t pon_rate 速率
	** 输    出： 无
	** 返 回 值： 无
	** 功能描述： SGM41282c获取RSSI采样保持值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm41282c_get_rssi_value(uint16_t* rssi, uint8_t pon_rate)
{
	return;	
}


void sgm41282c_set_rssi_value(uint16_t rssi, uint8_t pon_rate)
{
	return;
}


/***********************************************************************
	** 函 数 名： sgm41282c_set_apd_vcc
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41282c设置apd升压值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm41282c_set_apd_vcc(uint16_t dac_val, uint8_t pon_rate)
{
	if(pon_rate == 0){
		
		/* 设置DAC-VS电压输出 */
		dac_data_set(VS_DAC_PERIPH_50G, VS_DAC_OUT_50G, DAC_ALIGN_12B_R, dac_val);
      
	}
	else if(pon_rate == 1){

		#if ((MODULE_50G_10G_OPTICAL == CFG_YES) || (MODULE_50G_10G_1G_OPTICAL == \
				CFG_YES))
		/* 设置DAC-VS电压输出 */
		dac_data_set(VS_DAC_PERIPH_10G, VS_DAC_OUT_10G, DAC_ALIGN_12B_R, dac_val);
        
		#endif
	}

	else if(pon_rate == 2){

		#if (MODULE_50G_10G_1G_OPTICAL == CFG_YES)
		
		/* 设置DAC-VS电压输出 */
		dac_data_set(VS_DAC_PERIPH_1G, VS_DAC_OUT_1G, DAC_ALIGN_12B_R, dac_val);
        
		#endif

	}
	
	return;	
}

/***********************************************************************
	** 函 数 名： sgm41282c_set_apd
	** 输    入： float apd_vcc：升压电压值
								uint8_t pon_rate：0代表50G 1代表10G 2代表1G
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： sgm41282c设置APD电压值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm41282c_set_apd(float apd_vcc, uint8_t pon_rate)
{
	uint16_t dac_value;
	dac_value = (uint16_t)((apd_vcc*0.0341+0.1041) / 2.5 * 4096);
	sgm41282c_set_apd_vcc(dac_value,pon_rate);
	return;
}

#endif

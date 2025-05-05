/***********************************************************************************

 * 文 件 名   : dac_driver.c
 * 负 责 人   : fangzhe
 * 创建日期   : 2025年3月23日
 * 文件描述   : dac的driver接口
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#include "gd32e501.h"
#include "mcu_data_type.h"
#include "mcu_pin_type.h"

/*****************************************************************************
 * 函 数 名  : dac_gpion_init
 * 负 责 人  : fz
 * 创建日期  : 2023年5月18日
 * 函数功能  : dac的gpio初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
void dac_gpion_init()
{
    /*这里的引脚在mcu_pin_type.h已经使用宏控制了，这里再加宏控制显得杂乱
      正在考虑有什么更好的办法

    */
	 
	/* add by fz, 20230518, 原因:应用于vtec的ctl pin */
	/*PA4---DAC0_OUT0;应用于tec ctl引脚*/
	gpio_mode_set(GPIO_TEC_VCTL_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_PULLDOWN, 
		GPIO_TEC_VCTL_PIN);

    	/* configure GPIO PA4 as DAC ,dac0 */
	gpio_mode_set(GPIO_VS_PORT_50G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, 
			GPIO_VS_DA_PIN_50G);

	/* configure GPIO PC4 as DAC  */
	gpio_mode_set(GPIO_VS_PORT_10G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, 
			GPIO_VS_DA_PIN_10G);

	/* configure GPIO PA5 as DAC  */
	gpio_mode_set(GPIO_VS_PORT_1G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, 
			GPIO_VS_DA_PIN_1G);

    
    /* configure GPIO PC5 as DAC  */
	gpio_mode_set(GPIO_50G_EA_CTL_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_50G_EA_CTL_PIN);

    	/* configure GPIO PA7 as DAC  */
	gpio_mode_set(GPIO_EA_CTL_PORT_10G, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_EA_CTL_PIN_10G);

}



/*****************************************************************************
 * 函 数 名  : dac_periph_config
 * 负 责 人  : fz
 * 创建日期  : 2023年5月18日
 * 函数功能  : 
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void dac_periph_config(void)
{	

	/* add begin by fz, 20230518, 原因:配置DAC通道，映射GPIO_TEC_VCTL_PIN ,
		应用于tec vtec输入电压 */
		
	dac_deinit(DAC1);
	
#if defined(FH_IC_SGM41296_HARDWARE) && (FH_IC_SGM41296_HARDWARE == CFG_YES)
	dac_trigger_source_config(TEC_VCTL_DAC_PERIPH,TEC_VCTL_DAC_OUT,DAC_TRIGGER_SOFTWARE);

	/* configure the DAC0_OUT0 */
	dac_trigger_disable(TEC_VCTL_DAC_PERIPH, TEC_VCTL_DAC_OUT);
	//dac_wave_mode_config(TEC_VCTL_DAC_PERIPH, TEC_VCTL_DAC_OUT, DAC_WAVE_DISABLE);
	dac_output_buffer_enable(TEC_VCTL_DAC_PERIPH, TEC_VCTL_DAC_OUT);	
	dac_enable(TEC_VCTL_DAC_PERIPH,TEC_VCTL_DAC_OUT);

	
#endif

	/* add end by fz, 20230518 */

	/* add begin by gqhuan, 20240902, 原因:配置DAC通道，映射GPIO_VS_DA_PIN_50G/GPIO_VS_DA_PIN_10G/GPIO_VS_DA_PIN_1G ,
		应用于三模采保芯片VS输入电压 */
	dac_deinit(DAC0);

/* add by fz, 20250115, 原因:设置50g,1g vapd引脚 */
#if defined(FH_IC_SGM41282C_HARDWARE) && (FH_IC_SGM41282C_HARDWARE == CFG_YES)
	/* configure the DAC0_OUT0 */
	dac_trigger_source_config(VS_DAC_PERIPH_50G, VS_DAC_OUT_50G, DAC_TRIGGER_SOFTWARE);
	dac_output_buffer_disable(VS_DAC_PERIPH_50G, VS_DAC_OUT_50G);
	dac_enable(VS_DAC_PERIPH_50G, VS_DAC_OUT_50G);
	dac_software_trigger_enable(VS_DAC_PERIPH_50G, VS_DAC_OUT_50G);
	
	/* configure the DAC0_OUT1 */
	dac_trigger_source_config(VS_DAC_PERIPH_1G, VS_DAC_OUT_1G, DAC_TRIGGER_SOFTWARE);
	dac_output_buffer_disable(VS_DAC_PERIPH_1G, VS_DAC_OUT_1G);
	dac_enable(VS_DAC_PERIPH_1G, VS_DAC_OUT_1G);
	dac_software_trigger_enable(VS_DAC_PERIPH_1G, VS_DAC_OUT_1G);
#endif
	
//	dac_deinit(DAC1);// TEC配置已定义
	/* configure the DAC1_OUT1 */

   

#if defined(FH_IC_SGM2508_HARDWARE) && (FH_IC_SGM2508_HARDWARE == CFG_YES)
/* add by fz, 20250115, 原因:设置10g的负压引脚 ,DAC1*/
	dac_trigger_source_config(EA_CTL_DAC_PERIPH_10G, EA_CTL_DAC_OUT_10G, DAC_TRIGGER_SOFTWARE);
	dac_output_buffer_disable(EA_CTL_DAC_PERIPH_10G, EA_CTL_DAC_OUT_10G);
	dac_enable(EA_CTL_DAC_PERIPH_10G, EA_CTL_DAC_OUT_10G);
	dac_software_trigger_enable(EA_CTL_DAC_PERIPH_10G, EA_CTL_DAC_OUT_10G);

 
#endif

    dac_deinit(DAC2);
	   /* add by fangzhe, 20250326, 原因:50G负压 ，DAC2*/
    dac_trigger_source_config(EA_50G_CTL_PERIPH, EA_50G_CTL_DAC_OUT, DAC_TRIGGER_SOFTWARE);
	dac_output_buffer_disable(EA_50G_CTL_PERIPH, EA_50G_CTL_DAC_OUT);
	dac_enable(EA_50G_CTL_PERIPH, EA_50G_CTL_DAC_OUT);
	dac_software_trigger_enable(EA_50G_CTL_PERIPH, EA_50G_CTL_DAC_OUT);

/* add by fz, 20250115, 原因:设置10g vapd引脚 */
#if defined(FH_IC_SGM41282C_HARDWARE) && (FH_IC_SGM41282C_HARDWARE == CFG_YES)\
	&& ((MODULE_50G_10G_OPTICAL == CFG_YES) || (MODULE_50G_10G_1G_OPTICAL == \
	CFG_YES))
	/* configure the DAC2_OUT0 */
	dac_trigger_source_config(VS_DAC_PERIPH_10G, VS_DAC_OUT_10G, DAC_TRIGGER_SOFTWARE);
	dac_output_buffer_disable(VS_DAC_PERIPH_10G, VS_DAC_OUT_10G);
	dac_enable(VS_DAC_PERIPH_10G, VS_DAC_OUT_10G);
	dac_software_trigger_enable(VS_DAC_PERIPH_10G, VS_DAC_OUT_10G);
#endif

	 
}



/***********************************************************************
	* 文 件 名： sgm2508.c
	* 负 责 人： gqhuan
	* 创建日期： 2023-02
	* 文件描述： SGM2508负压芯片功能函数
	* 版权说明： Copyright (c) 1999-2023    烽火通信科技股份有限公司
	* 其    他： 
	* 修改日志： 
************************************************************************/


#include "sgm2508_ea.h"

#if defined(FH_IC_SGM2508_HARDWARE) && (FH_IC_SGM2508_HARDWARE == CFG_YES)

/***********************************************************************
	** 函 数 名： sgm2508_init
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM2508初始化
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm2508_init()
{		
	/* GPIO引脚初始化 */
	sgm2508_gpio_init();
	
	/* 设置VEA负压值 */
	float vea_vcc = 0;
	sgm2508_set_vea_10g(vea_vcc);

    sgm2508_set_vea_50g(vea_vcc);	
	
}

/***********************************************************************
	** 函 数 名： sgm2508_gpio_init
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM2508引脚初始化
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm2508_gpio_init()
{
#if 0
#define GPIO_EA_50G_VBIAS_EN_PORT          GPIOC
#define GPIO_EA_50G_VBIAS_EN_PIN          GPIO_PIN_8

//oo
#define GPIO_50G_EA_CTL_PORT        GPIOC
#define GPIO_50G_EA_CTL_PIN         GPIO_PIN_5
#define EA_50G_CTL_PERIPH           DAC2
#define EA_50G_CTL_DAC_OUT          DAC_OUT_1
#endif

    /* 设置高电平EA_EN */    
	gpio_mode_set(GPIO_EA_50G_VBIAS_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_EA_50G_VBIAS_EN_PIN);
	gpio_output_options_set(GPIO_EA_50G_VBIAS_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_EA_50G_VBIAS_EN_PIN);

    
    /* add by fangzhe, 20250326, 原因:10G配置 */
	/* 设置高电平EA_EN */
	gpio_mode_set(GPIO_EA_EN_PORT_10G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_EA_EN_PIN_10G);
	gpio_output_options_set(GPIO_EA_EN_PORT_10G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_EA_EN_PIN_10G);


    /* GPIO PB14 EA-EN引脚使能电流芯片 */
	//gpio_bit_set(GPIOB, GPIO_PIN_14);
	gpio_bit_set(GPIO_EA_EN_PORT_10G, GPIO_EA_EN_PIN_10G);

    gpio_bit_set(GPIO_EA_50G_VBIAS_EN_PORT, GPIO_EA_50G_VBIAS_EN_PIN);
}

/***********************************************************************
	** 函 数 名： sgm2508_set_vea_10g
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM2508设置10G负压值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm2508_set_vea_10g(float vea_vcc)
{
	/* 设置负压值 */
	uint16_t dac_value;
	dac_value = (uint16_t)(vea_vcc / 2.5 * 4096);
	/* 设置DAC-VS电压输出 */
	dac_data_set(EA_CTL_DAC_PERIPH_10G,EA_CTL_DAC_OUT_10G, DAC_ALIGN_12B_R, dac_value);
}


/***********************************************************************
	** 函 数 名： sgm2508_set_vea_50g
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM2508设置50G负压值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm2508_set_vea_50g(float vea_vcc)
{
	/* 设置负压值 */
	uint16_t dac_value;
	dac_value = (uint16_t)(vea_vcc / 2.5 * 4096);
	/* 设置DAC-VS电压输出 */
	dac_data_set(EA_50G_CTL_PERIPH,EA_50G_CTL_DAC_OUT,DAC_ALIGN_12B_R, dac_value);
}

#endif


/***********************************************************************************

 * �� �� ��   : dac_driver.c
 * �� �� ��   : fangzhe
 * ��������   : 2025��3��23��
 * �ļ�����   : dac��driver�ӿ�
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#include "gd32e501.h"
#include "mcu_data_type.h"
#include "mcu_pin_type.h"

/*****************************************************************************
 * �� �� ��  : dac_gpion_init
 * �� �� ��  : fz
 * ��������  : 2023��5��18��
 * ��������  : dac��gpio��ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : 

*****************************************************************************/
void dac_gpion_init()
{
    /*�����������mcu_pin_type.h�Ѿ�ʹ�ú�����ˣ������ټӺ�����Ե�����
      ���ڿ�����ʲô���õİ취

    */
	 
	/* add by fz, 20230518, ԭ��:Ӧ����vtec��ctl pin */
	/*PA4---DAC0_OUT0;Ӧ����tec ctl����*/
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
 * �� �� ��  : dac_periph_config
 * �� �� ��  : fz
 * ��������  : 2023��5��18��
 * ��������  : 
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void dac_periph_config(void)
{	

	/* add begin by fz, 20230518, ԭ��:����DACͨ����ӳ��GPIO_TEC_VCTL_PIN ,
		Ӧ����tec vtec�����ѹ */
		
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

	/* add begin by gqhuan, 20240902, ԭ��:����DACͨ����ӳ��GPIO_VS_DA_PIN_50G/GPIO_VS_DA_PIN_10G/GPIO_VS_DA_PIN_1G ,
		Ӧ������ģ�ɱ�оƬVS�����ѹ */
	dac_deinit(DAC0);

/* add by fz, 20250115, ԭ��:����50g,1g vapd���� */
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
	
//	dac_deinit(DAC1);// TEC�����Ѷ���
	/* configure the DAC1_OUT1 */

   

#if defined(FH_IC_SGM2508_HARDWARE) && (FH_IC_SGM2508_HARDWARE == CFG_YES)
/* add by fz, 20250115, ԭ��:����10g�ĸ�ѹ���� ,DAC1*/
	dac_trigger_source_config(EA_CTL_DAC_PERIPH_10G, EA_CTL_DAC_OUT_10G, DAC_TRIGGER_SOFTWARE);
	dac_output_buffer_disable(EA_CTL_DAC_PERIPH_10G, EA_CTL_DAC_OUT_10G);
	dac_enable(EA_CTL_DAC_PERIPH_10G, EA_CTL_DAC_OUT_10G);
	dac_software_trigger_enable(EA_CTL_DAC_PERIPH_10G, EA_CTL_DAC_OUT_10G);

 
#endif

    dac_deinit(DAC2);
	   /* add by fangzhe, 20250326, ԭ��:50G��ѹ ��DAC2*/
    dac_trigger_source_config(EA_50G_CTL_PERIPH, EA_50G_CTL_DAC_OUT, DAC_TRIGGER_SOFTWARE);
	dac_output_buffer_disable(EA_50G_CTL_PERIPH, EA_50G_CTL_DAC_OUT);
	dac_enable(EA_50G_CTL_PERIPH, EA_50G_CTL_DAC_OUT);
	dac_software_trigger_enable(EA_50G_CTL_PERIPH, EA_50G_CTL_DAC_OUT);

/* add by fz, 20250115, ԭ��:����10g vapd���� */
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



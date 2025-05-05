/***********************************************************************
	* �� �� ���� sgm2508.c
	* �� �� �ˣ� gqhuan
	* �������ڣ� 2023-02
	* �ļ������� SGM2508��ѹоƬ���ܺ���
	* ��Ȩ˵���� Copyright (c) 1999-2023    ���ͨ�ſƼ��ɷ����޹�˾
	* ��    ���� 
	* �޸���־�� 
************************************************************************/


#include "sgm2508_ea.h"

#if defined(FH_IC_SGM2508_HARDWARE) && (FH_IC_SGM2508_HARDWARE == CFG_YES)

/***********************************************************************
	** �� �� ���� sgm2508_init
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM2508��ʼ��
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm2508_init()
{		
	/* GPIO���ų�ʼ�� */
	sgm2508_gpio_init();
	
	/* ����VEA��ѹֵ */
	float vea_vcc = 0;
	sgm2508_set_vea_10g(vea_vcc);

    sgm2508_set_vea_50g(vea_vcc);	
	
}

/***********************************************************************
	** �� �� ���� sgm2508_gpio_init
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM2508���ų�ʼ��
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
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

    /* ���øߵ�ƽEA_EN */    
	gpio_mode_set(GPIO_EA_50G_VBIAS_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_EA_50G_VBIAS_EN_PIN);
	gpio_output_options_set(GPIO_EA_50G_VBIAS_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_EA_50G_VBIAS_EN_PIN);

    
    /* add by fangzhe, 20250326, ԭ��:10G���� */
	/* ���øߵ�ƽEA_EN */
	gpio_mode_set(GPIO_EA_EN_PORT_10G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_EA_EN_PIN_10G);
	gpio_output_options_set(GPIO_EA_EN_PORT_10G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_EA_EN_PIN_10G);


    /* GPIO PB14 EA-EN����ʹ�ܵ���оƬ */
	//gpio_bit_set(GPIOB, GPIO_PIN_14);
	gpio_bit_set(GPIO_EA_EN_PORT_10G, GPIO_EA_EN_PIN_10G);

    gpio_bit_set(GPIO_EA_50G_VBIAS_EN_PORT, GPIO_EA_50G_VBIAS_EN_PIN);
}

/***********************************************************************
	** �� �� ���� sgm2508_set_vea_10g
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM2508����10G��ѹֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm2508_set_vea_10g(float vea_vcc)
{
	/* ���ø�ѹֵ */
	uint16_t dac_value;
	dac_value = (uint16_t)(vea_vcc / 2.5 * 4096);
	/* ����DAC-VS��ѹ��� */
	dac_data_set(EA_CTL_DAC_PERIPH_10G,EA_CTL_DAC_OUT_10G, DAC_ALIGN_12B_R, dac_value);
}


/***********************************************************************
	** �� �� ���� sgm2508_set_vea_50g
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM2508����50G��ѹֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm2508_set_vea_50g(float vea_vcc)
{
	/* ���ø�ѹֵ */
	uint16_t dac_value;
	dac_value = (uint16_t)(vea_vcc / 2.5 * 4096);
	/* ����DAC-VS��ѹ��� */
	dac_data_set(EA_50G_CTL_PERIPH,EA_50G_CTL_DAC_OUT,DAC_ALIGN_12B_R, dac_value);
}

#endif


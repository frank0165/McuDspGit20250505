/***********************************************************************
	* �� �� ���� sgm41282c.c
	* �� �� �ˣ� gqhuan
	* �������ڣ� 2023-02
	* �ļ������� SGM41282C��ѹ�ɱ�оƬ���ܺ���
	* ��Ȩ˵���� Copyright (c) 1999-2023    ���ͨ�ſƼ��ɷ����޹�˾
	* ��    ���� 
	* �޸���־�� 
************************************************************************/
#include "sgm41282c_apd.h"
#include "dac_comm.h"

#if defined(FH_IC_SGM41282C_HARDWARE) && (FH_IC_SGM41282C_HARDWARE == CFG_YES)

//extern volatile DDM_ADC_OUT_VAL ddm_adc_out_val;//�ⲿddm��ر���ADCֵ

/***********************************************************************
	** �� �� ���� sgm41282c_init
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41282c��ʼ��
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41282c_init()
{		


	/*********************** 50GPON ************************/
	sgm41282c_gpio_50g_init();

	/* DAC-VS���������ѹ���� */
	float apd_vcc = 0;
	sgm41282c_set_apd(apd_vcc,0);


	/*********************** 10GPON ************************/
	
    sgm41282c_gpio_10g_init();
	/* DAC-VS���������ѹ���� */
	float apd_vcc_10g = 0;
	sgm41282c_set_apd(apd_vcc_10g,1);

	/*********************** 1GPON ************************/
	
    sgm41282c_gpio_1g_init();
	/* DAC-VS���������ѹ���� */
	float apd_vcc_1g = 0;
	sgm41282c_set_apd(apd_vcc_1g,2);
	

}



/*****************************************************************************
 * �� �� ��  : sgm41282c_gpio_50g_init
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��26��
 * ��������  : 50g sgm41282���ų�ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : 
 * ��    ��  : 

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

   /* GPIO PC9-EN����ʹ�ܵ�ѹоƬ */
	//gpio_bit_set(GPIOC, GPIO_PIN_9);
	gpio_bit_set(GPIO_EN_PORT_50G,GPIO_EN_PIN_50G);

	/* GPIO PC11-GAIN��λ����1������ ��λ8������*/
	//gpio_bit_reset(GPIOC, GPIO_PIN_11);
	gpio_bit_reset(GPIO_GAIN_PORT_50G,GPIO_GAIN_PIN_50G);

	/* GPIO PC10-THXOR��λ*/
	//gpio_bit_reset(GPIOC, GPIO_PIN_10);
	gpio_bit_reset(GPIO_THXOR_PORT_50G,GPIO_THXOR_PIN_50G);
    
}


/*****************************************************************************
 * �� �� ��  : sgm41282c_gpio_10g_init
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��26��
 * ��������  : 10g sgm41282ѹ���ų�ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : 
 * ��    ��  : 

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

    /* GPIO PC3-EN����ʹ�ܵ�ѹоƬ */
	//gpio_bit_set(GPIOC, GPIO_PIN_3);
	gpio_bit_set(GPIO_EN_PORT_10G,GPIO_EN_PIN_10G);

	/* GPIO PB15-GAIN��λ����1������ ��λ8������*/
	//gpio_bit_reset(GPIOB, GPIO_PIN_15);
	gpio_bit_set(GPIO_GAIN_PORT_10G,GPIO_GAIN_PIN_10G);

	/* GPIO PB12-THXOR��λ*/
	//gpio_bit_reset(GPIOB, GPIO_PIN_12);
	gpio_bit_set(GPIO_THXOR_PORT_10G,GPIO_THXOR_PIN_10G);

}

/*****************************************************************************
 * �� �� ��  : sgm41282c_gpio_1g_init
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��26��
 * ��������  : 1g sgm41282���ų�ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : 
 * ��    ��  : 

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

    /* GPIO PC15-EN����ʹ�ܵ�ѹоƬ */
	//gpio_bit_set(GPIOC, GPIO_PIN_15);
	gpio_bit_set(GPIO_EN_PORT_1G,GPIO_EN_PIN_1G);

	/* GPIO PF1-GAIN��λ����1������ ��λ8������*/
	//gpio_bit_reset(GPIOF, GPIO_PIN_1);
	gpio_bit_set(GPIO_GAIN_PORT_1G,GPIO_GAIN_PIN_1G);

	/* GPIO PF0-THXOR��λ*/
	//gpio_bit_reset(GPIOF, GPIO_PIN_0);
	gpio_bit_set(GPIO_THXOR_PORT_1G,GPIO_THXOR_PIN_1G);
}






/***********************************************************************
	** �� �� ���� sgm41282c_reset
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41282c��λ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41282c_reset()
{
	/* ������λ */
	
}


/***********************************************************************
	** �� �� ���� sgm41282c_get_rssi_value
	** ��    �룺 uint16_t* rssi �ɱ�ֵ
							 uint8_t pon_rate ����
	** ��    ���� ��
	** �� �� ֵ�� ��
	** ���������� SGM41282c��ȡRSSI��������ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
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
	** �� �� ���� sgm41282c_set_apd_vcc
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41282c����apd��ѹֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41282c_set_apd_vcc(uint16_t dac_val, uint8_t pon_rate)
{
	if(pon_rate == 0){
		
		/* ����DAC-VS��ѹ��� */
		dac_data_set(VS_DAC_PERIPH_50G, VS_DAC_OUT_50G, DAC_ALIGN_12B_R, dac_val);
      
	}
	else if(pon_rate == 1){

		#if ((MODULE_50G_10G_OPTICAL == CFG_YES) || (MODULE_50G_10G_1G_OPTICAL == \
				CFG_YES))
		/* ����DAC-VS��ѹ��� */
		dac_data_set(VS_DAC_PERIPH_10G, VS_DAC_OUT_10G, DAC_ALIGN_12B_R, dac_val);
        
		#endif
	}

	else if(pon_rate == 2){

		#if (MODULE_50G_10G_1G_OPTICAL == CFG_YES)
		
		/* ����DAC-VS��ѹ��� */
		dac_data_set(VS_DAC_PERIPH_1G, VS_DAC_OUT_1G, DAC_ALIGN_12B_R, dac_val);
        
		#endif

	}
	
	return;	
}

/***********************************************************************
	** �� �� ���� sgm41282c_set_apd
	** ��    �룺 float apd_vcc����ѹ��ѹֵ
								uint8_t pon_rate��0����50G 1����10G 2����1G
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� sgm41282c����APD��ѹֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41282c_set_apd(float apd_vcc, uint8_t pon_rate)
{
	uint16_t dac_value;
	dac_value = (uint16_t)((apd_vcc*0.0341+0.1041) / 2.5 * 4096);
	sgm41282c_set_apd_vcc(dac_value,pon_rate);
	return;
}

#endif

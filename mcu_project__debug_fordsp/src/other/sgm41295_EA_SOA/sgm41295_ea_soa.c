/***********************************************************************
	* �� �� ���� sgm41295.c
	* �� �� �ˣ� gqhuan
	* �������ڣ� 2023-02
	* �ļ������� SGM41295��ѹоƬ���ܺ���
	* ��Ȩ˵���� Copyright (c) 1999-2023    ���ͨ�ſƼ��ɷ����޹�˾
	* ��    ���� 
	* �޸���־�� 
************************************************************************/

#include "sgm41295_ea_soa.h"

#if defined(FH_IC_SGM41295_HARDWARE) && (FH_IC_SGM41295_HARDWARE == CFG_YES)

/***********************************************************************
	** �� �� ���� sgm41295_init
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41295��ʼ��
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41295_init()
{		
	/* GPIO���ų�ʼ�� */
	sgm41295_gpio_init();
  
	/* ����SOA LD����ֵ */
	float ild = 0.0;//mA
	sgm41295_set_ld(ild);
	sgm41295_ld_ctrl(1);
	
	/* ����VEA��ѹֵ */
	float vea_vcc = 0;
	sgm41295_set_vea(vea_vcc);
	sgm41295_vea_ctrl(1);
	
	/* GPIO PA10 LD-EN����ʹ�ܵ���оƬ */
	gpio_bit_set(GPIO_LD_EN_PORT_50G, GPIO_LD_EN_PIN_50G);
 
}

/***********************************************************************
	** �� �� ���� sgm41295_gpio_init
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41295���ų�ʼ��
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41295_gpio_init()
{
	/* ���øߵ�ƽLD_EN */
	gpio_mode_set(GPIO_LD_EN_PORT_50G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_LD_EN_PIN_50G);
  	gpio_output_options_set(GPIO_LD_EN_PORT_50G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LD_EN_PIN_50G);
}

/***********************************************************************
	** �� �� ���� sgm41295_reset
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41295��λ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41295_reset()
{
	/* ������λ */
	uint8_t soft_reset[2];
	soft_reset[0] = 0x00;//0x00-Soft Reset
	soft_reset[1] = 0x04;//bit[2] 1: Generate Reset.
	master_reg_byte_write(SGM41295_SLAVE_ADDRESS, soft_reset, 2);
}

/***********************************************************************
	** �� �� ���� sgm41295_set_vea
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41295���ø�ѹֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41295_set_vea(float vea_vcc)
{
	/* ���ø�ѹֵ */
	uint8_t code;//VEA = 3.2 �� (Code/256)
	code = (uint8_t)(vea_vcc/3.2*256);
	sgm41295_set_vea_reg(code);
}

/***********************************************************************
	** �� �� ���� sgm41295_set_vea_reg
** ��    �룺 uint8_t code����ѹ����ʽ�����Ӧ�ļĴ���ֵ
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41295���ø�ѹֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41295_set_vea_reg(uint8_t code)
{
	/* ����VEA�Ĵ���ֵ */
	uint8_t eam_bias[2];
	eam_bias[0] = 0x21;//0x21-VEA
	eam_bias[1] = code;//VEA = 3.2 �� (Code/256)
	master_reg_byte_write(SGM41295_SLAVE_ADDRESS, eam_bias, 2);
}

/***********************************************************************
	** �� �� ���� sgm41295_set_ld
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41295����LD����ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
***********************************************************************/
void sgm41295_set_ld(float ild)
{
	/* ����LD����ֵ */
	uint8_t code;//ILD = k*(offset + 128 *(code/256)) k=1 offset=16mA
	code = (uint8_t)((ild)*2);
	
	sgm41295_set_ld_reg(code);
}

/***********************************************************************
	** �� �� ���� sgm41295_set_ld_reg
** ��    �룺 uint8_t code��LD��������ʽ�����Ӧ�ļĴ���ֵ
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41295����LD����ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41295_set_ld_reg(uint8_t code)
{
	/* ����LD�����Ĵ���ֵ */
	/* ����k/offset����ֵ */
	uint8_t k_offset[2];
	k_offset[0] = 0x05;//0x05-k and offset address
	k_offset[1] = 0x00;//k=1 offset=00mA
	master_reg_byte_write(SGM41295_SLAVE_ADDRESS, k_offset, 2);
	/* ����LD����ֵ */
	uint8_t laser_bias[2];
	laser_bias[0] = 0x20;//0x20-ILD
	laser_bias[1] = code;//ILD = k*(offset + 128 *(code/256)) *52mA
	master_reg_byte_write(SGM41295_SLAVE_ADDRESS, laser_bias, 2);
}

/***********************************************************************
	** �� �� ���� sgm41295_vea_ctrl
	** ��    �룺 uint8_t ctrl_switch 1-enable 0-disable
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41295ʹ��/ȥʹ�ܸ�ѹ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41295_vea_ctrl(uint8_t ctrl_switch)
{
	uint8_t vea_en[2];
	vea_en[0] = 0x03;//0x03-VEA_EN
	uint8_t reg_en[1];
	master_reg_1byte_size_read(SGM41295_SLAVE_ADDRESS, 0x03, reg_en, 1);
	
	if(ctrl_switch == 1){
			vea_en[1] = reg_en[0] | 0x02;
	}
	else{
			vea_en[1] = reg_en[0] & 0x01;
	}
	master_reg_byte_write(SGM41295_SLAVE_ADDRESS, vea_en, 2);
    
}

/***********************************************************************
	** �� �� ���� sgm41295_ld_ctrl
	** ��    �룺 uint8_t ctrl_switch 1-enable 0-disable
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� SGM41295ʹ��/ȥʹ�ܵ���
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void sgm41295_ld_ctrl(uint8_t ctrl_switch)
{
	uint8_t ld_en[2];
	ld_en[0] = 0x03;//0x03-VEA_EN
	uint8_t reg_en[1];
	master_reg_1byte_size_read(SGM41295_SLAVE_ADDRESS, 0x03, reg_en, 1);
	
	if(ctrl_switch == 1){
			ld_en[1] = reg_en[0] | 0x01;
	}
	else{
			ld_en[1] = reg_en[0] & 0x02;
	}
	master_reg_byte_write(SGM41295_SLAVE_ADDRESS, ld_en, 2);
    
}

#endif

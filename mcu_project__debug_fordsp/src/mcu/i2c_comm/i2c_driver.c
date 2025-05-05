/***********************************************************************************

 * �� �� ��   : i2c_driver.c
 * �� �� ��   : fangzhe
 * ��������   : 2025��3��23��
 * �ļ�����   : i2c driver�Ľӿ�
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#include "i2c_driver.h"
#include "mcu_pin_type.h"


/*****************************************************************************
 * �� �� ��  : gpio_slave_i2c_config_init
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : slave_i2c gpio��ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void gpio_slave_i2c_config_init(void)
{
	/****************slave ��gpio�ţ���Ϊslaveģʽ  ********************************/       
   /* connect PB10 to I2C1_SCL */
    gpio_af_set(GPIO_I2C_SLAVE_PORT, GPIO_I2C_SLAVE_AF, GPIO_I2C_SLAVE_SCL);
   
    /* connect PB11 to slave_SDA */
    gpio_af_set(GPIO_I2C_SLAVE_PORT , GPIO_I2C_SLAVE_AF, GPIO_I2C_SLAVE_SDA);
	
    /* configure GPIO pins of slave */
    gpio_mode_set(GPIO_I2C_SLAVE_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_I2C_SLAVE_SCL);
    gpio_output_options_set(GPIO_I2C_SLAVE_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, 
	GPIO_I2C_SLAVE_SCL);
	
    gpio_mode_set(GPIO_I2C_SLAVE_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_I2C_SLAVE_SDA);
    gpio_output_options_set(GPIO_I2C_SLAVE_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, 
		GPIO_I2C_SLAVE_SDA);
/************************** end **********************************************/
}




/*****************************************************************************
 * �� �� ��  : gpio_master_i2c_config_init
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : master_i2c gpio��ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void gpio_master_i2c_config_init(void)
{

/*******************master i2c ��gpio�ţ���Ϊmasterģʽ ***************************/
	
	/* connect PB10 to master_SDA */
    gpio_af_set(GPIO_I2C_MASTER_A_PORT, GPIO_I2C_MASTER_A_AF, GPIO_I2C_MASTER_A_SCL);

    /* connect PB11 to master_SDA */
    gpio_af_set(GPIO_I2C_MASTER_A_PORT, GPIO_I2C_MASTER_A_AF, GPIO_I2C_MASTER_A_SDA);
	
    /* configure GPIO pins of master */
    gpio_mode_set(GPIO_I2C_MASTER_A_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_I2C_MASTER_A_SCL);
    gpio_output_options_set(GPIO_I2C_MASTER_A_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, 
		GPIO_I2C_MASTER_A_SCL);
	
    gpio_mode_set(GPIO_I2C_MASTER_A_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_I2C_MASTER_A_SDA);
    gpio_output_options_set(GPIO_I2C_MASTER_A_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, 
		GPIO_I2C_MASTER_A_SDA);	

/********************** end *********************************************/

/*******************master B i2c ��gpio�ţ���Ϊmasterģʽ ***************************/

	/* connect PB8 to master_SCL */
   	gpio_af_set(GPIO_I2C_MASTER_B_PORT, GPIO_I2C_MASTER_B_AF, GPIO_I2C_MASTER_B_SCL);

    /* connect PB9 to master_SDA */
    gpio_af_set(GPIO_I2C_MASTER_B_PORT, GPIO_I2C_MASTER_B_AF, GPIO_I2C_MASTER_B_SDA);
	
    gpio_mode_set(GPIO_I2C_MASTER_B_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, 
    	GPIO_I2C_MASTER_B_SCL);
    gpio_output_options_set(GPIO_I2C_MASTER_B_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, 
		GPIO_I2C_MASTER_B_SCL);
	
    gpio_mode_set(GPIO_I2C_MASTER_B_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, 
    	GPIO_I2C_MASTER_B_SDA);
    gpio_output_options_set(GPIO_I2C_MASTER_B_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, 
		GPIO_I2C_MASTER_B_SDA);	
/********************** end *********************************************/
}



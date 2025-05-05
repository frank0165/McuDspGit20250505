/***********************************************************************************

 * 文 件 名   : i2c_driver.c
 * 负 责 人   : fangzhe
 * 创建日期   : 2025年3月23日
 * 文件描述   : i2c driver的接口
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#include "i2c_driver.h"
#include "mcu_pin_type.h"


/*****************************************************************************
 * 函 数 名  : gpio_slave_i2c_config_init
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : slave_i2c gpio初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void gpio_slave_i2c_config_init(void)
{
	/****************slave 的gpio脚，作为slave模式  ********************************/       
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
 * 函 数 名  : gpio_master_i2c_config_init
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : master_i2c gpio初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void gpio_master_i2c_config_init(void)
{

/*******************master i2c 的gpio脚，作为master模式 ***************************/
	
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

/*******************master B i2c 的gpio脚，作为master模式 ***************************/

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



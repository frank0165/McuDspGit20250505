/***********************************************************************
	* 文 件 名： sgm41295.c
	* 负 责 人： gqhuan
	* 创建日期： 2023-02
	* 文件描述： SGM41295负压芯片功能函数
	* 版权说明： Copyright (c) 1999-2023    烽火通信科技股份有限公司
	* 其    他： 
	* 修改日志： 
************************************************************************/

#include "sgm41295_ea_soa.h"

#if defined(FH_IC_SGM41295_HARDWARE) && (FH_IC_SGM41295_HARDWARE == CFG_YES)

/***********************************************************************
	** 函 数 名： sgm41295_init
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41295初始化
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm41295_init()
{		
	/* GPIO引脚初始化 */
	sgm41295_gpio_init();
  
	/* 设置SOA LD电流值 */
	float ild = 0.0;//mA
	sgm41295_set_ld(ild);
	sgm41295_ld_ctrl(1);
	
	/* 设置VEA负压值 */
	float vea_vcc = 0;
	sgm41295_set_vea(vea_vcc);
	sgm41295_vea_ctrl(1);
	
	/* GPIO PA10 LD-EN引脚使能电流芯片 */
	gpio_bit_set(GPIO_LD_EN_PORT_50G, GPIO_LD_EN_PIN_50G);
 
}

/***********************************************************************
	** 函 数 名： sgm41295_gpio_init
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41295引脚初始化
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm41295_gpio_init()
{
	/* 设置高电平LD_EN */
	gpio_mode_set(GPIO_LD_EN_PORT_50G, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_LD_EN_PIN_50G);
  	gpio_output_options_set(GPIO_LD_EN_PORT_50G, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LD_EN_PIN_50G);
}

/***********************************************************************
	** 函 数 名： sgm41295_reset
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41295复位
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm41295_reset()
{
	/* 设置软复位 */
	uint8_t soft_reset[2];
	soft_reset[0] = 0x00;//0x00-Soft Reset
	soft_reset[1] = 0x04;//bit[2] 1: Generate Reset.
	master_reg_byte_write(SGM41295_SLAVE_ADDRESS, soft_reset, 2);
}

/***********************************************************************
	** 函 数 名： sgm41295_set_vea
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41295设置负压值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm41295_set_vea(float vea_vcc)
{
	/* 设置负压值 */
	uint8_t code;//VEA = 3.2 × (Code/256)
	code = (uint8_t)(vea_vcc/3.2*256);
	sgm41295_set_vea_reg(code);
}

/***********************************************************************
	** 函 数 名： sgm41295_set_vea_reg
** 输    入： uint8_t code：负压按公式计算对应的寄存器值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41295设置负压值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm41295_set_vea_reg(uint8_t code)
{
	/* 设置VEA寄存器值 */
	uint8_t eam_bias[2];
	eam_bias[0] = 0x21;//0x21-VEA
	eam_bias[1] = code;//VEA = 3.2 × (Code/256)
	master_reg_byte_write(SGM41295_SLAVE_ADDRESS, eam_bias, 2);
}

/***********************************************************************
	** 函 数 名： sgm41295_set_ld
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41295设置LD电流值
	** 作    者： gqhuan
	** 日    期： 
***********************************************************************/
void sgm41295_set_ld(float ild)
{
	/* 设置LD电流值 */
	uint8_t code;//ILD = k*(offset + 128 *(code/256)) k=1 offset=16mA
	code = (uint8_t)((ild)*2);
	
	sgm41295_set_ld_reg(code);
}

/***********************************************************************
	** 函 数 名： sgm41295_set_ld_reg
** 输    入： uint8_t code：LD电流按公式计算对应的寄存器值
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41295设置LD电流值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void sgm41295_set_ld_reg(uint8_t code)
{
	/* 设置LD电流寄存器值 */
	/* 设置k/offset电流值 */
	uint8_t k_offset[2];
	k_offset[0] = 0x05;//0x05-k and offset address
	k_offset[1] = 0x00;//k=1 offset=00mA
	master_reg_byte_write(SGM41295_SLAVE_ADDRESS, k_offset, 2);
	/* 设置LD电流值 */
	uint8_t laser_bias[2];
	laser_bias[0] = 0x20;//0x20-ILD
	laser_bias[1] = code;//ILD = k*(offset + 128 *(code/256)) *52mA
	master_reg_byte_write(SGM41295_SLAVE_ADDRESS, laser_bias, 2);
}

/***********************************************************************
	** 函 数 名： sgm41295_vea_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41295使能/去使能负压
	** 作    者： gqhuan
	** 日    期： 
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
	** 函 数 名： sgm41295_ld_ctrl
	** 输    入： uint8_t ctrl_switch 1-enable 0-disable
	** 输    出： 无
	** 返 回 值： void
	** 功能描述： SGM41295使能/去使能电流
	** 作    者： gqhuan
	** 日    期： 
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

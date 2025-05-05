/***********************************************************************************

 * 文 件 名   : ddm_sff_i2c_interface.h
 * 负 责 人   : fz
 * 创建日期   : 2025年1月15日
 * 文件描述   : sff_8472的i2c接口
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#ifndef _DDM_SFF_I2C_INTERFACE_H_
#define _DDM_SFF_I2C_INTERFACE_H_
#include "gd32e501_it.h"
#include "mcu_data_type.h"


/*****************************************************************************
 * 函 数 名  : om_flash_write_reg_byte
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月21日
 * 函数功能  : 写表到flash
 * 输入参数  : uint32_t slave_addr, 设置地址,A0,B0,C0;A2,B2,C2
             uint8_t *p_buff, 要写的内容,第一个字节是寄存器
                uint32_t buff_len p_buff的长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
void om_flash_write_reg_byte(uint32_t slave_addr,uint8_t *p_buff,uint32_t buff_len);

/*****************************************************************************
 * 函 数 名  : om_memory_state_ctrl_write_reg_byte
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月21日
 * 函数功能  : 写状态表到临时内存
 * 输入参数  :  uint32_t slave_addr, 设置地址,A0,B0,C0;A2,B2,C2
             uint8_t *p_buff, 要写的内容,第一个字节是寄存器
                uint32_t buff_len p_buff的长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 上位机测试使用

*****************************************************************************/
void om_memory_state_ctrl_write_reg_byte(uint32_t slave_addr,uint8_t *p_buff,uint32_t buff_len);

/*****************************************************************************
 * 函 数 名  : om_v2_flash_read_reg_byte
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月21日
 * 函数功能  : 从flash区中读取flash--以表形式保存
 * 输入参数  : I2C_ALL_ADDRESS_INFO *p_address_info  地址及寄存信息
                uint32_t buff_len p_buff的长度:I2C_SLAVE_WRITE_READ_MAX
 * 输出参数  : p_buff 实际表的数据
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void om_v2_flash_read_reg_byte(I2C_ALL_ADDRESS_INFO *p_address_info,uint8_t *p_buff,uint32_t 
							buff_len);


/***********************************************************************
	** 函 数 名： om_memory_read_reg_byte
	** 输    入：I2C_ALL_ADDRESS_INFO *p_address_info 地址信息
				uint32_t buff_len p_buff的长度							
								
	** 输    出： uint8_t *p_buff 从内存中读取a0,b0,c0,a2,b2,c2
	** 返 回 值： 无
	** 功能描述： 虚拟寄存器数值读取
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void om_v2_memory_read_reg_byte(I2C_ALL_ADDRESS_INFO *p_address_info,
													uint8_t *p_buff,
													uint32_t buff_len);

/***********************************************************************
	** 函 数 名： om_cmd_ddm_read_reg_byte
	** 输    入： uint8_t regaddr 寄存器首地址
				  uint8_t *p_buff 缓冲地址
				  uint32_t buff_len 偏移量 
	** 输    出： 无
	** 返 回 值： 无
	** 功能描述： ddm物理量虚拟寄存器数值读取
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void om_cmd_ddm_read_reg_byte(uint8_t regaddr, uint8_t *pbuff, uint32_t 
											bufflen);

/***********************************************************************
	** 函 数 名： om_save_data_config_flash_write
	** 输    入： uint8_t *pbuff 寄存器缓存
								uint32_t bufflen 字节长度
	** 输    出： 无
	** 返 回 值： 无
	** 功能描述： 设置收端deemph值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void om_save_data_config_flash_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : om_erase_data_config_flash_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : 清除flash数据
 * 输入参数  : uint8_t *pbuff 寄存器缓存
			uint32_t bufflen 字节长度
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void om_erase_data_config_flash_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : cfg_v2_flash_read_reg_byte
 * 负 责 人  : fz
 * 创建日期  : 2025年1月3日
 * 函数功能  : mcu的slave的特殊地址:0xA8的读功能，用于读取保存的配置
 * 输入参数  : uint32_t slave_addr  slave地址.
 				uint8_t regaddress  寄存器值 				
 				uint32_t buffer_len 数据的长度
 * 输出参数  : uint8_t* p_buffer	读取的数据
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 本函数只处理设备地址 0xA8，其它的设备地址不处理。

*****************************************************************************/
void cfg_v2_flash_read_reg_byte(I2C_ALL_ADDRESS_INFO *p_address_info,
		uint8_t *p_buff,uint32_t buff_len);

/*****************************************************************************
 * 函 数 名  : cmd_common_reg_read
 * 负 责 人  : fz
 * 创建日期  : 2024年10月12日
 * 函数功能  : 通用读功能
 * 输入参数  : uint8_t regaddr 寄存器
 				uint32_t bufflen pbuff的长度
 * 输出参数  : uint8_t *pbuff 实际的flash的配置长度
 * 返 回 值  : 无
 * 调用关系  : 
 * 其    它  : CMD_COMMON_READ_REG = 0x27,

*****************************************************************************/
void cmd_common_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen);


#endif


/***********************************************************************************

 * 文 件 名   : update_i2c_interface.h
 * 负 责 人   : fz
 * 创建日期   : 2025年1月16日
 * 文件描述   : 升级功能的i2接口
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#ifndef __UPDATE_I2C_INTERFACE_H_
#define __UPDATE_I2C_INTERFACE_H_

#include "gd32e501.h"


/*****************************************************************************
 * 函 数 名  : update_app_write_reg_byte
 * 负 责 人  : fz
 * 创建日期  : 2023年8月24日
 * 函数功能  : mcu应用程序升级
 * 输入参数  : uint8_t *p_buff,传入的数据。
                       p_buff[0]:UPGRADE_APP_SOFTWARE_REG
                       p_buff[1]:UPGRADE_APP_DOING,正在传输文件
                       			UPGRADE_APP_END，传输文件结束
                       			UPGRADE_CRC_END，传办CRC
 				uint32_t buff_len
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void update_app_write_reg_byte(uint8_t *p_buff,uint32_t 
			buff_len);

/*****************************************************************************
 * 函 数 名  : update_firmware_write_reg_byte
 * 负 责 人  : fz
 * 创建日期  : 2023年11月6日
 * 函数功能  : 光模块的firmware升级
 * 输入参数  : uint8_t *p_buff,传入的数据。
			   uint32_t buff_len 长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void update_firmware_write_reg_byte(uint8_t *p_buff,uint32_t buff_len);


/*****************************************************************************
 * 函 数 名  : update_user_boot_write_reg_byte
 * 负 责 人  : fz
 * 创建日期  : 2023年11月6日
 * 函数功能  : 光模块的firmware升级
 * 输入参数  : uint8_t *p_buff,传入的数据。
			   uint32_t buff_len 长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 目前没用

*****************************************************************************/
void update_user_boot_write_reg_byte(uint8_t *p_buff,uint32_t buff_len);

void upgrade_dev_version_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t 
		bufflen);

#endif
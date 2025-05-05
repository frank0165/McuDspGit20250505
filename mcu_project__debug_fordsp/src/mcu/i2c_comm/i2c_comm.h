#ifndef _I2C_COMM_H_
#define _I2C_COMM_H_

#include "gd32e501.h"

#include "i2c_opt_ie_interface.h"

/*回调的数组长度*/
#define MCU_REGADDR_CALLBACK_ITEMS	(44)

/* add by fz, 20230515, 原因:i2c写的回调接口 ，p_buff包括寄存器*/

/*****************************************************************************
 * 函 数 名  : 回调函数--寄存器地址写接口
 * 负 责 人  : fz
 * 创建日期  : 2023年7月17日
 * 函数功能  : 当设备地址不变时，针对不同寄存器对应的回调函数
 * 输入参数  : uint8_t *p_buff     写入的内容；首字节p_buff[0]是寄存器
 			   uint32_t buff_len	p_buff的长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
typedef void (*MCU_REGADDR_WRITE_CALLBACK)(uint8_t *p_buff,uint32_t buff_len);

/* add by fz, 20230515, 原因:i2c写的回调接口 ，p_buff不包括寄存器*/


/*****************************************************************************
 * 函 数 名  : 回调函数--寄存器地址读接口
 * 负 责 人  : fz
 * 创建日期  : 2023年7月17日
 * 函数功能  :  当设备地址不变时，针对不同寄存器对应的回调函数
 * 输入参数  :  uint8_t regaddress  寄存器
 * 输出参数  : uint8_t *p_buff,   读到的内容
 				uint32_t buff_len   p_buff的长度
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
typedef void (*MCU_REGADDR_READ_CALLBACK)(uint8_t regaddress,uint8_t *p_buff,uint32_t buff_len);


/* add by fz, 20230515, 原因:针对mcu设备地址的i2c的写的回调数据结构 */
typedef struct _MCU_REGADDR_WRITE_CALLBACK_HANDLE_
{
	uint8_t reg_addr;
	MCU_REGADDR_WRITE_CALLBACK callback;
}MCU_REGADDR_WRITE_CALLBACK_HANDLE;


/* add by fz, 20230515, 原因:针对mcu设备地址的i2c的读的回调数据结构 */
typedef struct _MCU_REGADDR_READ_CALLBACK_HANDLE_
{
	uint8_t reg_addr;
	MCU_REGADDR_READ_CALLBACK callback;
}MCU_REGADDR_READ_CALLBACK_HANDLE;


/*****************************************************************************
 * 函 数 名  : mcu_register_reg_addr_write_callback
 * 负 责 人  : fz
 * 创建日期  : 2023年5月18日
 * 函数功能  :i2c slave下的 寄存器地址的写回调函数
 * 输入参数  : uint8_t reg_addr  寄存器地址
 				MCU_REGADDR_WRITE_CALLBACK write_callback  对应写接口函数
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void mcu_register_reg_addr_write_callback(uint8_t reg_addr,
	MCU_REGADDR_WRITE_CALLBACK write_callback);



/*****************************************************************************
 * 函 数 名  : mcu_register_reg_addr_read_callback
 * 负 责 人  : fz
 * 创建日期  : 2023年5月18日
 * 函数功能  : i2c slave下的 寄存器地址的读回调函数
 * 输入参数  : uint8_t reg_addr  寄存器地址
 				MCU_REGADDR_READ_CALLBACK read_callback  对应读接口函数
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void mcu_register_reg_addr_read_callback(uint8_t reg_addr,	
			MCU_REGADDR_READ_CALLBACK read_callback);



/*****************************************************************************
 * 函 数 名  : mcu_addr0xc0_reg_byte_write
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : mcu的slave的特殊地址写功能
 * 输入参数  : uint32_t slave_addr  slave地址
 				uint8_t* p_buffer	要写入的数据
 				uint32_t buffer_len 数据的长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void mcu_addr0xspec_reg_byte_write(uint32_t slave_addr,
									uint8_t* p_buffer, 
									uint32_t buffer_len);

/*****************************************************************************
 * 函 数 名  : mcu_addr0xspec_reg_byte_read
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : mcu的slave的特殊地址:0xce的读功能
 * 输入参数  : uint32_t slave_addr  slave地址.
 				uint8_t regaddress  寄存器值 				
 				uint32_t buffer_len 数据的长度
 * 输出参数  : uint8_t* p_buffer	读取的数据
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 本函数只处理设备地址 0xce，其它的设备地址不处理。

*****************************************************************************/
void mcu_addr0xspec_reg_byte_read(I2C_ALL_ADDRESS_INFO *p_address_info,
		uint8_t *p_buff,
		uint32_t buff_len);



/*****************************************************************************
 * 函 数 名  : mcu_addr0xspec_1byte_reg_byte_read
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : mcu的slave的特殊地址:0xce的读功能
 * 输入参数  : uint32_t slave_addr  slave地址.
 				uint8_t regaddress  1个字节寄存器值 				
 				uint32_t buffer_len 数据的长度
 * 输出参数  : uint8_t* p_buffer	读取的数据
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 本函数只处理设备地址 0xce，其它的设备地址不处理。

*****************************************************************************/
void mcu_addr0xspec_1byte_reg_byte_read(uint32_t slave_address,uint8_t 
				regaddress,uint8_t *p_buff,uint32_t buff_len);


/*****************************************************************************
 * 函 数 名  : i2c_config_init
 * 负 责 人  : fz
 * 创建日期  : 2023年7月19日
 * 函数功能  : i2c初始化配置
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
void i2c_config_init();

#endif


#include <string.h>

#include "i2c_comm.h"
#include "i2c_driver.h"

#include "mcu_data_type.h"
#include "mcu_pin_type.h"
#include "mcu_system_comm.h"


/*************************************************************************
* 变量功能：针对mcu设备地址的写功能
* 取值范围：数量MCU_REGADDR_CALLBACK_ITEMS
* 注意事项：无
*************************************************************************/
MCU_REGADDR_WRITE_CALLBACK_HANDLE 
g_mcu_addr0xspec_reg_write_callback_array[MCU_REGADDR_CALLBACK_ITEMS];

/*************************************************************************
* 变量功能：g_mcu_addr0xspec_reg_write_callback_array数组下标
* 取值范围：数量MCU_REGADDR_CALLBACK_ITEMS
* 注意事项：无
*************************************************************************/
uint32_t g_mcu_addr0xspec_reg_write_idx = 0;

/*************************************************************************
* 变量功能：针对mcu设备地址的读功能
* 取值范围：数量MCU_REGADDR_CALLBACK_ITEMS
* 注意事项：无
*************************************************************************/
MCU_REGADDR_READ_CALLBACK_HANDLE 
g_mcu_addr0xspec_reg_read_callback_array[MCU_REGADDR_CALLBACK_ITEMS];

/*************************************************************************
* 变量功能：g_mcu_addr0xspec_reg_read_callback_array数组下标
* 取值范围：数量MCU_REGADDR_CALLBACK_ITEMS
* 注意事项：无
*************************************************************************/
uint32_t g_mcu_addr0xspec_reg_read_idx = 0;






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
void i2c_config_init()
{
    i2c_global_param_init();
    memset(g_mcu_addr0xspec_reg_write_callback_array,0,
		sizeof(g_mcu_addr0xspec_reg_write_callback_array));
    
	gpio_slave_i2c_config_init();
	gpio_master_i2c_config_init();

	user_optical_pwd_limit_init();
	slave_i2c_config_init();
	master_i2c_config_init();	

	
	
}



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
				MCU_REGADDR_WRITE_CALLBACK write_callback)
{
	uint32_t i = 0;
	for(i = 0; i < g_mcu_addr0xspec_reg_write_idx;i++)
	{
		if(reg_addr == g_mcu_addr0xspec_reg_write_callback_array[i].reg_addr)
		{
			return;
		}
	}

   
	if(g_mcu_addr0xspec_reg_write_idx < MCU_REGADDR_CALLBACK_ITEMS)
	{
		g_mcu_addr0xspec_reg_write_callback_array[g_mcu_addr0xspec_reg_write_idx].callback = write_callback;
		g_mcu_addr0xspec_reg_write_callback_array[g_mcu_addr0xspec_reg_write_idx].reg_addr = 
				reg_addr;
		g_mcu_addr0xspec_reg_write_idx++;
	}

	return;
	
}


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
			MCU_REGADDR_READ_CALLBACK read_callback)
{
	uint32_t i = 0;
	for(i = 0; i < g_mcu_addr0xspec_reg_read_idx;i++)
	{
		if(reg_addr == g_mcu_addr0xspec_reg_read_callback_array[i].reg_addr)
		{
			return;
		}
	}

	if(g_mcu_addr0xspec_reg_read_idx < MCU_REGADDR_CALLBACK_ITEMS)
	{
		g_mcu_addr0xspec_reg_read_callback_array[g_mcu_addr0xspec_reg_read_idx].callback = 
		read_callback;
		g_mcu_addr0xspec_reg_read_callback_array[g_mcu_addr0xspec_reg_read_idx].reg_addr = 
				reg_addr;
		g_mcu_addr0xspec_reg_read_idx++;
	}

	return;
	
}





/*****************************************************************************
 * 函 数 名  : mcu_addr0xc0_reg_byte_write
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : mcu的slave的特殊地址:0xce的写功能
 * 输入参数  : uint32_t slave_addr  slave地址.
 				uint8_t* p_buffer	要写入的数据
 				uint32_t buffer_len 数据的长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 本函数只处理设备地址 0xce，其它的设备地址不处理。

*****************************************************************************/
void mcu_addr0xspec_reg_byte_write(uint32_t slave_addr,
									uint8_t* p_buffer, 
									uint32_t buffer_len	)
{
	uint8_t reg = 0;
	uint32_t i = 0;
	if(I2C_MCU_SPEC_ADDR != slave_addr)
	{
		return;
	}
	if(NULL == p_buffer || buffer_len < 2)
	{
		return;
	}

	reg |= *p_buffer;

	for(i = 0; i < g_mcu_addr0xspec_reg_write_idx;i++)
	{
		if(reg == g_mcu_addr0xspec_reg_write_callback_array[i].reg_addr)
		{
			break;
		}
	}

	if(i < g_mcu_addr0xspec_reg_write_idx)
	{
		g_mcu_addr0xspec_reg_write_callback_array[i].callback(p_buffer,buffer_len);
	}

	return;
	
}


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
				regaddress,uint8_t *p_buff,uint32_t buff_len)
{
	
	uint32_t i = 0;
	if(I2C_MCU_SPEC_ADDR != slave_address)
	{
		return;
	}
	if(NULL == p_buff)
	{
		return;
	}

	for(i = 0; i < g_mcu_addr0xspec_reg_read_idx;i++)
	{
		if(regaddress == g_mcu_addr0xspec_reg_read_callback_array[i].reg_addr)
		{
			break;
		}
	}

	if(i < g_mcu_addr0xspec_reg_read_idx)
	{
		g_mcu_addr0xspec_reg_read_callback_array[i].callback(regaddress,p_buff,buff_len);
	}

	
}


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
		uint32_t buff_len)
{
	if(NULL == p_address_info)
	{
		return;
	}

	if(1 == p_address_info->reg_size)
	{
		mcu_addr0xspec_1byte_reg_byte_read(p_address_info->slave_address,p_address_info->regaddress[0],
		p_buff,buff_len);
	}
	return;
}
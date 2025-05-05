/***********************************************************************************

 * 文 件 名   : i2c_opt_ie.c
 * 负 责 人   : fz
 * 创建日期   : 2023年5月15日
 * 文件描述   : i2c处理master、slave
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/


/*!
    \file    I2C1_IE.c
    \brief   I2C1 slave receiver interrupt program
    
    \version 2020-03-02, V1.0.0, firmware for GD32E501
    \version 2020-04-10, V1.0.1, firmware for GD32E501
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/
#include "gd32e501.h"
#include "gd32e501_i2c.h"
#include <string.h>
#include "mcu_system_comm.h"
#include "stdio.h"
#include "i2c_opt_ie.h"
#include <stdlib.h>


#include "gd32e501_eval.h"
#include "mcu_data_type.h"
#include "mcu_pin_type.h"
#include "dev_reg_address.h"
#include "systick.h"

#include "mcu_global_vars_param.h"
/*************************************************************************
* 变量功能：i2c slave callback function of write
* 取值范围：数量I2C_CALL_BACK_ITEMS
* 注意事项：回调数据一直保存，不要清空
*************************************************************************/
volatile I2C_WRITE_CFG_CALLBACK_HANDLE 
g_slave_write_cfg_callback_array[I2C_CALL_BACK_ITEMS];

/*************************************************************************
* 变量功能：g_slave_write_cfg_callback_array数组下标
* 取值范围：数量I2C_CALL_BACK_ITEMS
* 注意事项：回调数据一直保存，不要清空
*************************************************************************/
volatile uint32_t g_slave_write_cfg_idx = 0;


/*************************************************************************
* 变量功能：i2c slave callback function of read
* 取值范围：数量I2C_CALL_BACK_ITEMS
* 注意事项：回调数据一直保存，不要清空
*************************************************************************/
volatile I2C_READ_CFG_CALLBACK_HANDLE 
g_slave_read_cfg_callback_array[I2C_CALL_BACK_ITEMS];

/*************************************************************************
* 变量功能：g_slave_read_cfg_callback_array数组下标
* 取值范围：数量I2C_CALL_BACK_ITEMS
* 注意事项：回调数据一直保存，不要清空
*************************************************************************/
volatile uint32_t g_slave_read_cfg_idx = 0;




/* delete by fangzhe, 20250320, 原因:slave_i2c不用 ，因为这种用法无效*/
/*slave i2c i2c 状机是否空闲，SET空闲,RESET不空闲*/
//volatile uint32_t g_slave_i2c_irq_status_pre = I2C_INT_NON_STATUS;

/*************************************************************************
* 变量功能：i2c slave buffer数据
* 取值范围：无
* 注意事项：无
*************************************************************************/
I2C_SLAVE_BUFF_CFG g_i2c_slave_info_cfg;

/*************************************************************************
* 变量功能：i2c master buffer数据
* 取值范围：无
* 注意事项：无
*************************************************************************/
I2C_MASTER_BUFF_CFG g_ai2c_master_info_cfg;

/*************************************************************************
* 变量功能：i2c master buffer数据
* 取值范围：无
* 注意事项：无
*************************************************************************/
I2C_MASTER_BUFF_CFG g_bi2c_master_info_cfg;

/* add by fz, 20231106, 原因:光模块默认密码 */
uint8_t g_optical_limit_pwd[OPT_MOD_LIMIT_PASSWORD_LENGTH];

/* add by fz, 20231106, 原因:默认可以访问的寄存器写功能 */
volatile uint8_t g_user_authority_access_array_write_reg[] = {CMD_OPTICAL_PASSWORD_LIMIT_REG};


/*************************************************************************
* 变量功能：i2c 全局变量数据
* 取值范围：无
* 注意事项：无
*************************************************************************/
volatile I2C_GLOBAL_VARS_PARAM g_i2c_global_vars;



void slave_i2c_receive_handle();

void slave_i2c_address_match_handle();


/*****************************************************************************
 * 函 数 名  : reset_master_i2c
 * 负 责 人  : fz
 * 创建日期  : 2025年3月10日
 * 函数功能  : 复位master模式的i2c
 * 输入参数  : uint32_t i2c_periph i2c总线
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 

*****************************************************************************/
void reset_master_i2c(uint32_t i2c_periph)
{
	I2C_MASTER_BUFF_CFG *p_master_cfg = NULL;

	if(CHECK_DEV_ERR_I2C(i2c_periph))
	{
		return;
	}
	g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;
	
	p_master_cfg = GET_MASTER_CFG_OF_I2C(i2c_periph);
	i2c_master_info_buffer_clear(p_master_cfg);
	
	i2c_disable(i2c_periph);
	i2c_enable(i2c_periph);
	
}

/*****************************************************************************
 * 函 数 名  : i2c_slave_func_register_read_callback
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月21日
 * 函数功能  : slave i2c读注册
 * 输入参数  : uint32_t slave_address, 设备地址
            I2C_READ_CFG_CALLBACK read_callback  回调接口
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
void i2c_slave_func_register_read_callback(uint32_t 
	slave_address,I2C_READ_CFG_CALLBACK read_callback)
{
	uint32_t i = 0;

    /*已注册过就直接返回*/
	for(i = 0; i < g_slave_read_cfg_idx;i++)
	{
		if(slave_address == g_slave_read_cfg_callback_array[i].slave_address)
		{
			return;
		}
	}

    /*找个空间注册*/
	if(g_slave_read_cfg_idx < I2C_CALL_BACK_ITEMS)
	{
		g_slave_read_cfg_callback_array[g_slave_read_cfg_idx].callback = read_callback;
		g_slave_read_cfg_callback_array[g_slave_read_cfg_idx].slave_address = slave_address;
		g_slave_read_cfg_idx++;
	}

	return;
	
}

/*****************************************************************************
 * 函 数 名  : i2c_slave_func_register_write_callback
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月21日
 * 函数功能  : slave i2c写注册
 * 输入参数  : uint32_t slave_address, 设备地址
            I2C_READ_CFG_CALLBACK read_callback  回调接口
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
void i2c_slave_func_register_write_callback(uint32_t 
			slave_address,I2C_WRITE_CFG_CALLBACK write_callback)
{
	uint32_t i = 0;

     /*已注册过就直接返回*/
	for(i = 0; i < g_slave_write_cfg_idx;i++)
	{
		if(slave_address == g_slave_write_cfg_callback_array[i].slave_address)
		{
			return;
		}
	}

   

     /*找个空间注册*/
	if(g_slave_write_cfg_idx < I2C_CALL_BACK_ITEMS)
	{
		g_slave_write_cfg_callback_array[g_slave_write_cfg_idx].callback = write_callback;
		g_slave_write_cfg_callback_array[g_slave_write_cfg_idx].slave_address = slave_address;
		g_slave_write_cfg_idx++;
	}
}


/*****************************************************************************
 * 函 数 名  : i2c_slave_buffer_info_clear
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 清零g_i2c_slave_info_cfg
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void i2c_slave_buffer_info_clear()
{	
	memset(&g_i2c_slave_info_cfg,0,sizeof(g_i2c_slave_info_cfg));
	
}


/*****************************************************************************
 * 函 数 名  : i2c_slave_info_slave_address_add
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 给g_i2c_slave_info_cfg设置地址
 * 输入参数  : uint32_t slave_address  slave address
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void i2c_slave_info_slave_address_add(uint32_t slave_address)
{
	g_i2c_slave_info_cfg.address_info.slave_address = slave_address;
}

/*****************************************************************************
 * 函 数 名  : i2c_slave_buffer_info_data_add
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 给g_i2c_slave_info_cfg设置数据
 * 输入参数  : uint32_t data  数据
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void i2c_slave_buffer_info_data_add(uint32_t data)
{
	uint32_t idx = g_i2c_slave_info_cfg.buffer_idx;

	if(idx < I2C_SLAVE_BUFFER_MAX)
	{
		g_i2c_slave_info_cfg.slave_buffer[idx] = data;		
		g_i2c_slave_info_cfg.buffer_idx++;	
		
	}

	return;		
}


/*****************************************************************************
 * 函 数 名  : i2c_slave_buffer_mng_regaddress_info
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 从g_i2c_slave_info_cfg的buffer中得到reg_address
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : i2c  slave模式时，会接收到寄存器地址，
 				由这函数把reg_address从buffer中移到regaddress
*****************************************************************************/
void i2c_slave_buffer_mng_regaddress_info()
{
	uint32_t idx = g_i2c_slave_info_cfg.buffer_idx;

	if(idx <= MCU_I2C_REGADDRESS_SIZE)
	{
		//注意不能把address_info.slave_address也清零
		memset(&g_i2c_slave_info_cfg.address_info.regaddress,
			0,
			sizeof(g_i2c_slave_info_cfg.address_info.regaddress));

		memcpy(g_i2c_slave_info_cfg.address_info.regaddress,
			g_i2c_slave_info_cfg.slave_buffer,
			idx);
		g_i2c_slave_info_cfg.address_info.reg_size = idx;
		
		memset(g_i2c_slave_info_cfg.slave_buffer,0,
			sizeof(g_i2c_slave_info_cfg.slave_buffer));
		g_i2c_slave_info_cfg.buffer_idx = 0;		
		
	}

	return;
	
}


/*****************************************************************************
 * 函 数 名  : i2c_slave_info_get_buff_info
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 获取g_i2c_slave_info_cfg的指针
 * 输入参数  : 无
 * 输出参数  : I2C_SLAVE_BUFF_CFG **p_buff_info 指针
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无
 
*****************************************************************************/
void i2c_slave_info_get_buff_info(I2C_SLAVE_BUFF_CFG **p_buff_info)
{
	*p_buff_info = &g_i2c_slave_info_cfg;
	return;
}



/*****************************************************************************
 * 函 数 名  : i2c_slave_info_popup_data_from_buffer
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 获取g_i2c_slave_info_cfg中的buffer数据
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无
 
*****************************************************************************/
uint8_t i2c_slave_info_popup_data_from_buffer()
{
	uint32_t idx = g_i2c_slave_info_cfg.buffer_idx;
	uint8_t data = 0;
	if(g_i2c_slave_info_cfg.buffer_idx < I2C_SLAVE_WRITE_READ_MAX)
	{
		data = g_i2c_slave_info_cfg.slave_buffer[idx];
		g_i2c_slave_info_cfg.buffer_idx++;
		return data;
		
	}

	return 0;	
}

/*****************************************************************************
 * 函 数 名  : i2c_slave_info_state_is_read
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 获取i2c slave的状态
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无
 
*****************************************************************************/
uint8_t i2c_slave_info_state_is_read()
{
	return g_i2c_slave_info_cfg.read_flag;
}


/*****************************************************************************
 * 函 数 名  : i2c_slave_info_set_state_read_flag
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 设置i2c slave的read flag
 * 输入参数  : uint8_t flag :0-表示初始状态,
                             1-表示读标识；
                             其它未定，目前没用到
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无
 
*****************************************************************************/
void i2c_slave_info_set_state_read_flag(uint8_t flag)
{
	g_i2c_slave_info_cfg.read_flag = flag;
}


/*****************************************************************************
 * 函 数 名  : i2c_master_buffer_info_data_add
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : g_i2c_master_info_cfg的buffer中增加数据
 * 输入参数  : uint32_t data 要添加的数据
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无
 
*****************************************************************************/
void i2c_master_buffer_info_data_add(uint32_t dev_i2c,uint32_t data)
{
	I2C_MASTER_BUFF_CFG *ptr_master = NULL;
	
	if(CHECK_DEV_ERR_I2C(dev_i2c))
	{
		return;
	}
	ptr_master = GET_MASTER_CFG_OF_I2C(dev_i2c);
	
	uint32_t idx = ptr_master->buffer_idx;

	if(idx < I2C_SLAVE_BUFFER_MAX)
	{
		ptr_master->master_buffer[idx++] = data;
		ptr_master->buffer_idx = idx;
		
	}

	return;		
}

/*****************************************************************************
 * 函 数 名  : i2c_master_info_popup_data_from_buffer
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 从g_i2c_master_info_cfg的buffer中移位得到数据，每调用一次数组下标就
               增加1
 * 输入参数  : uint32_t dev_i2c master的i2c总线
 * 输出参数  : 无
 * 返 回 值  : 返回数据
 * 调用关系  : 内部调用
 * 其    它  : 无
 
*****************************************************************************/
uint8_t i2c_master_info_popup_data_from_buffer(uint32_t dev_i2c)
{
	I2C_MASTER_BUFF_CFG *ptr_master_i2c = NULL;
	ptr_master_i2c = GET_MASTER_CFG_OF_I2C(dev_i2c);
	uint32_t idx = ptr_master_i2c->buffer_idx;
	uint8_t data = 0;
	if(ptr_master_i2c->buffer_idx < I2C_SLAVE_WRITE_READ_MAX)
	{
		data = ptr_master_i2c->master_buffer[idx];
		ptr_master_i2c->buffer_idx++;
		return data;
		
	}

	return 0;	
}

/*****************************************************************************
 * 函 数 名  : i2c_master_info_buffer_clear
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 清零g_i2c_master_info_cfg
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无 
 
*****************************************************************************/
void i2c_master_info_buffer_clear(I2C_MASTER_BUFF_CFG *ptr_buff)
{
	if(NULL == ptr_buff)
	{
		return;
	}
	memset(ptr_buff,0,sizeof(I2C_MASTER_BUFF_CFG));
}


/*****************************************************************************
 * 函 数 名  : i2c_write_lock
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : i2c 中断模式中，write lock
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无 
 
*****************************************************************************/
void i2c_write_lock()
{
	g_i2c_global_vars.g_write_doing_flag = I2C_LOCK_BUSY;
}

/*****************************************************************************
 * 函 数 名  : i2c_write_unlock
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : i2c 中断模式中，write unlock
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无 
 
*****************************************************************************/
void i2c_write_unlock()
{
	g_i2c_global_vars.g_write_doing_flag = I2C_LOCK_IDLE;
}

/*****************************************************************************
 * 函 数 名  : i2c_get_write_lock
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 获取write lock
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无 
 
*****************************************************************************/
I2C_LOCK_SEM i2c_get_write_lock()
{
	return g_i2c_global_vars.g_write_doing_flag;
}

/*****************************************************************************
 * 函 数 名  : i2c_read_lock
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : i2c 中断模式中，read lock
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无
 
*****************************************************************************/
void i2c_read_lock()
{
	g_i2c_global_vars.g_read_doing_flag = I2C_LOCK_BUSY;
}

/*****************************************************************************
 * 函 数 名  : i2c_slave_info_popup_data_from_buffer
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : i2c 中断模式中，read unlock
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无
 
*****************************************************************************/
void i2c_read_unlock()
{
	g_i2c_global_vars.g_read_doing_flag = I2C_LOCK_IDLE;
}

/*****************************************************************************
 * 函 数 名  : i2c_slave_info_popup_data_from_buffer
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : 获取read lock
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无
 
*****************************************************************************/
I2C_LOCK_SEM i2c_get_read_lock()
{
	return g_i2c_global_vars.g_read_doing_flag;
}



/*****************************************************************************
 * 函 数 名  : reset_slave_i2c
 * 负 责 人  : fz
 * 创建日期  : 2025年3月10日
 * 函数功能  : 仅用于slave i2c复位
 * 输入参数  : uint32_t dev_i2c  i2c总线,slave只能是SLAVE_I2C
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void reset_slave_i2c(uint32_t dev_i2c)
{
	i2c_disable(dev_i2c);
	i2c_enable(dev_i2c);
	i2c_slave_buffer_info_clear();

	//g_slave_i2c_irq_status_pre = I2C_INT_NON_STATUS;
	g_i2c_global_vars.g_slave_read_handle_flag = RESET;
	g_i2c_global_vars.g_slave_write_handle_flag = RESET;
	g_i2c_global_vars.g_slave_receive_handle_flag = RESET;
	g_i2c_global_vars.g_slave_address_handle_flag = RESET;

	i2c_write_unlock();	
	i2c_read_unlock();
}


/*****************************************************************************
 * 函 数 名  : slave_i2c_write_special_handleing
 * 负 责 人  : fz
 * 创建日期  : 2025年3月3日
 * 函数功能  : 在进行升级，写flash时，停止轮询ddm
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 内部调用
 * 其    它  : 

*****************************************************************************/
void slave_i2c_write_special_handleing()
{
	I2C_SLAVE_BUFF_CFG *p_slave_info = NULL;
	
	i2c_slave_info_get_buff_info(&p_slave_info);
	if(NULL == p_slave_info)
	{
		return;
	}

	if(UPGRADE_APP_SOFTWARE_REG == p_slave_info->slave_buffer[0]
		|| UPGRADE_FIRMWARE_REG == p_slave_info->slave_buffer[0]
		|| CMD_OPTICAL_MODULE_CFG_FLASH == p_slave_info->slave_buffer[0])
	{
		g_mcu_vars_param.g_update_process_flag = SET;
	}
}



/*****************************************************************************
 * 函 数 名  : slave_event_irq_handler
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c1的slave中断事件处理功能
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c1的slave中断事件产生
 * 其    它  : 无
 断点调试与正常运行时的事件不一样;设置断点单调调试，
 会造成时序及中断事件与手册不一样
******************************************************************************/
void slave_event_irq_handler(uint32_t dev_i2c)
{	
	uint8_t data = 0;
	uint32_t tmp = 0;
	uint32_t run_us = 0;
	uint8_t cyl = 0;

    /* add by fangzhe, 20250422, 原因:如有任何的中断响应则计数清零 */
    g_mcu_vars_param.g_i2c_exception_irq_status_counter = 0;
	
  if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_ADDSEND))
	{

    /* delete by fangzhe, 20250320, 原因:因为有判断写i2c_get_write_lock,所以不需要状态
    g_slave_i2c_irq_status_pre;
    另外:1)因为如果是read模式，会有两次进入ADDSEND中断，原while_fun判断方式无意义,
         2) 如果是write模式，ADDSEND后，后又进入写操作，在完成之前不会变为I2C_INT_NON_STATUS，
            会一直是I2C_INT_ADDSEND_STATUS标只，所以while_fun判断无效，这也是为什么while_fun判断失效
            而在写操作没完成前进又进入了ADDSEND中断；
            原代码中整个slave中断g_slave_i2c_irq_status_pre只设置了两个状态I2C_INT_ADDSEND_STATUS
            和I2C_INT_NON_STATUS,这也是原代码有误的造成的。
         3) while_fun也不能只依据I2C_INT_NON_STATUS,因为2)所述会有两次进入ADDSEND；*/
#if 0
		/*依据i2c传输，会有两次进入地址中断*/
		/*防止i2c一个末处理完时，另一个时钟周期到来了*/
		run_us = CYCLE_DELAY_TIME_US;
		cyl = 0;		
		while_fun(!(I2C_INT_NON_STATUS == g_slave_i2c_irq_status_pre 
			|| I2C_INT_ADDSEND_STATUS == g_slave_i2c_irq_status_pre),run_us,cyl);
		if(1 == cyl)
		{			
			g_slave_i2c_irq_status_pre = I2C_INT_ADDSEND_STATUS;
			SLAVE_RECEIVE_ADDR() &= 0;	
			reset_slave_i2c(dev_i2c);
			return;
			
		}
		
		g_slave_i2c_irq_status_pre = I2C_INT_ADDSEND_STATUS;	
#endif
		
		/* add by fz, 20250310, 原因:当前没有写操作时就进入地址匹配处理 */
		if(I2C_LOCK_IDLE == i2c_get_write_lock())	
		{
			slave_i2c_address_match_handle();
		}
		else
		{
			/* add by fz, 20250307, 原因:因为当前有写操作，
				屏蔽addM中断响应 ，准备交给中断外处理*/
			i2c_interrupt_disable(dev_i2c,I2C_INT_ADDM);
			g_i2c_global_vars.g_slave_address_handle_flag = SET;
		}		
		
    }
	else if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_RBNE))
	{
		i2c_interrupt_disable(dev_i2c,I2C_INT_STPDET | I2C_INT_RBNE | I2C_INT_TI);		
		
		i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_RBNE | I2C_INT_FLAG_TI);		
		
		g_i2c_global_vars.g_slave_receive_handle_flag = SET;

        /* add by fangzhe, 20250321, 原因:接收数据只与mcu的内存交互，速度快 
            可以在中断中处理*/
		slave_i2c_receive_handle();
		
    }
	else if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_TI))
	{	
		
		/*必须得disable I2C_INT_TI | I2C_INT_STPDET,才能保证事件顺序*/
		i2c_interrupt_disable(dev_i2c,I2C_INT_TI | I2C_INT_STPDET);
		
		//i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_STPDET);
		i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_TI);

        /* add by fangzhe, 20250321, 原因:中断外处理标识 
        while(1)体中处理*/
		g_i2c_global_vars.g_slave_read_handle_flag = SET;			
		
	}
	else if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_STPDET))
	{     
			
		/*依据协议:I2C主机发送STOP条件后，不需要等待从机的应答。停止信号是单向的，由主机发出
		标志着通信的结束。从机在检测到停止信号后，应释放总线，不再进行数据传输。
		也就是说在stop时，如果writing因时间过长而还未完成，主机有可能会重新发start消息。
		这里即使disable I2C_INT_STPDET也不行，因为主机不必等应答
		*/
		i2c_interrupt_disable(dev_i2c,I2C_INT_STPDET | I2C_INT_TI | I2C_INT_RBNE);	

		/*清除标识很重要*/
		i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_STPDET);
	
		/*开始写保护*/
		i2c_write_lock();
		
		/*当为写时，至少两个字节，一个寄存器，一个值*/
		if(1 != i2c_slave_info_state_is_read()) 
		{
			/*写标识置位，while(1)体中处理slave_i2c_write_handle,写完后清空*/
			g_i2c_global_vars.g_slave_write_handle_flag = SET;
 			slave_i2c_write_special_handleing();			
			
		}
		else  
		{
			//结束后，指针还原到初始位		

			/*buffer中的第一位保留寄存的值.非断点调试时，RBNE完后直接STPDET，没有进入下一个
				RBNE
			*/			
				
			i2c_slave_buffer_info_clear();
			SLAVE_RECEIVE_ADDR() &= 0;
			//g_slave_i2c_irq_status_pre = I2C_INT_NON_STATUS;
			
			i2c_write_unlock();
		}		
			
    }
	
}



/*****************************************************************************
 * 函 数 名  : slave_i2c_receive_handle
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : i2c slave模式下,receive处理
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void slave_i2c_receive_handle()
{
	
	uint8_t data = 0;
	I2C_SLAVE_BUFF_CFG *p_slave_cfg = NULL;

	/*写保护未释放，说明当前还有未写完的数据，返回原来的中断继续写，
      而receive准备在中断处while(1)中处理
    */
	if(I2C_LOCK_BUSY == i2c_get_write_lock())
	{
		g_i2c_global_vars.g_slave_write_handle_flag = SET; 
		return;
	}
	
	g_i2c_global_vars.g_slave_receive_handle_flag = RESET;


    /* delete by fangzhe, 20250321, 原因:代码冗余，改为后面的代码 */
#if 0
	i2c_slave_info_get_buff_info(&p_slave_cfg);
	if(NULL != p_slave_cfg)
	{
	    /* add by fangzhe, 20250321, 原因:防止接收越界 */
		if(PRE_LESS_LATER(p_slave_cfg->buffer_idx,I2C_SLAVE_BUFFER_MAX))
		{
			data = i2c_data_receive(SLAVE_I2C);
			i2c_slave_buffer_info_data_add(data);		
			
		}
		else
		{
			/*主要是为了产生中断，拉高scl*/
			i2c_data_receive(SLAVE_I2C);
		}
	}
	else
	{
		i2c_data_receive(SLAVE_I2C);
	}

#endif	
    /* delete end by fangzhe, 20250321 */

    data = i2c_data_receive(SLAVE_I2C);
    i2c_slave_info_get_buff_info(&p_slave_cfg);
	if(NULL != p_slave_cfg)
    {
         /* add by fangzhe, 20250321, 原因:防止接收越界 */
		if(PRE_LESS_LATER(p_slave_cfg->buffer_idx,I2C_SLAVE_BUFFER_MAX))
	    {
	        i2c_slave_buffer_info_data_add(data);	
	    }
    }    

	i2c_interrupt_enable(SLAVE_I2C, I2C_INT_STPDET | I2C_INT_RBNE | I2C_INT_TI);
}

/*****************************************************************************
 * 函 数 名  : slave_i2c_address_match_handle
 * 负 责 人  : fz
 * 创建日期  : 2025年3月7日
 * 函数功能  : 地址匹配处理
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 

*****************************************************************************/
void slave_i2c_address_match_handle()
{
	/* add by fz, 20250310, 原因:当前有写操作时，就返回不回复ack */
	if(I2C_LOCK_BUSY == i2c_get_write_lock())	
	{
		return;
	}

#if 1
/*作为发送端，SET;这里必须要这么写，否则中断事件会乱*/
	if(SET == i2c_flag_get(SLAVE_I2C, I2C_STAT_TR))
	{
		/* clear I2C_TDATA register */
    	I2C_STAT(SLAVE_I2C) |= I2C_STAT_TBE;
	}
#endif
	
	/* clear the ADDSEND bit */
	i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_ADDSEND);

	/* add by fz, 20250310, 原因:因为在进入中断之外处理时,先disable 
	ADDM，处理完后要enable */
	if(SET == g_i2c_global_vars.g_slave_address_handle_flag)
	{
		i2c_interrupt_enable(SLAVE_I2C,I2C_INT_ADDM | I2C_INT_STPDET | I2C_INT_TI | I2C_INT_RBNE);
	}
	else
	{
		/* add by fz, 20250310, 原因:是在中断内部处理，就不需要 enable 
		ADDM;因为enable后会反映响应ADDM中断*/
		i2c_interrupt_enable(SLAVE_I2C,I2C_INT_STPDET | I2C_INT_TI | I2C_INT_RBNE);

	}

	//SLAVE_RECEIVE_ADDR() = (i2c_recevied_address_get(SLAVE_I2C) << 1);

	/* add by fz, 20250310, 原因:断点调试时可以查看 ,所以代替了上述的宏*/
	g_i2c_global_vars.g_receive_address = (i2c_recevied_address_get(SLAVE_I2C) << 1);

	//如果为read，会有两次进入address，这里不能有clear
	//i2c_slave_buffer_info_clear();
	i2c_slave_info_slave_address_add(g_i2c_global_vars.g_receive_address);
	g_i2c_global_vars.g_slave_address_handle_flag = RESET;
	
	
}

/*****************************************************************************
 * 函 数 名  : slave_i2c_read_handle
 * 负 责 人  : fz
 * 创建日期  : 2023年12月6日
 * 函数功能  : i2c slave模式下,read处理
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void slave_i2c_read_handle()
{
	uint8_t data = 0;	
	
	/*直接用变量，没有使用函数，是为了避免发生中断*/
	g_i2c_global_vars.g_slave_read_handle_flag = RESET;
	I2C_SLAVE_BUFF_CFG *ptr_buff_info = NULL;
	
	
	/*读一个寄存器，一个字节*/
	/*上位机读时，有时候会连续读两次，这里++就显得错误
		场景 :mcu实始启动，先写mcu；然后第一次读上位机，就会发现slave连续两次 TI;
		第二次读上位机，就会发现只有 slave一个TI。
		
*/	

		/*当前还未进入读状态，也就是首次要进入读状态*/
		if(0 == i2c_slave_info_state_is_read())
		{
			/*会把buff清理*/
			i2c_slave_buffer_mng_regaddress_info();

			/* add by fz, 20250312, 原因:已发生了read ，设置标识符*/
			i2c_slave_info_set_state_read_flag(1);

			i2c_slave_info_get_buff_info(&ptr_buff_info);
			if(NULL == ptr_buff_info) /*目前这里不可能为NULL*/
			{
				return;
			}

            /* add by fangzhe, 20250321, 原因:不论上位机要求多个字节，这里统一读取最大字节数 
               
            */
			slave_v2_reg_byte_read(&(ptr_buff_info->address_info),
				ptr_buff_info->slave_buffer,I2C_SLAVE_WRITE_READ_MAX);
			
		}

		data = i2c_slave_info_popup_data_from_buffer();
	

	/*如果这放在i2c_write_unlock前，则执行完后会立即产生中断*/
	i2c_data_transmit(SLAVE_I2C, data); 
	i2c_interrupt_enable(SLAVE_I2C, I2C_INT_STPDET | I2C_INT_TI);	

}


/*****************************************************************************
 * 函 数 名  : slave_i2c_write_handle
 * 负 责 人  : fz
 * 创建日期  : 2023年7月19日
 * 函数功能  : 在main中处理i2c slave write 
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 

*****************************************************************************/
void slave_i2c_write_handle(void)
{	
	I2C_SLAVE_BUFF_CFG *p_slave_info = NULL;
	

	/*i2c中断时，没有获取的i2c写保护，就不能在while中执行写操作*/
	if(I2C_LOCK_IDLE == i2c_get_write_lock())
	{
		return;
	}

	i2c_slave_info_get_buff_info(&p_slave_info);
	if(NULL == p_slave_info)
	{
		return;
	}

/*	slave_reg_byte_write(g_receive_address, 
		p_slave_info->slave_buffer,
		p_slave_info->buffer_idx);	*/
	slave_reg_byte_write(p_slave_info->address_info.slave_address, 
		p_slave_info->slave_buffer,
		p_slave_info->buffer_idx);

	/* add by fz, 20250312, 原因:必需要清空 ，read_flag要清空*/
	i2c_slave_buffer_info_clear();
	
	//g_slave_i2c_irq_status_pre = I2C_INT_NON_STATUS;

	i2c_write_unlock();

	g_i2c_global_vars.g_slave_write_handle_flag = RESET;

	/*这里注释掉memset,是因为执行memset时，又中断跳转了*/
	/*buffer中的第一位保留寄存的值.非断点调试时，RBNE完后直接STPDET*/		
	//memset(&g_slave_buffer[1],0,I2C_BUFFER_ARRAY_MAX - 1);	 
	
}


/*****************************************************************************
 * 函 数 名  : slave_i2c_lock_reset
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年4月22日
 * 函数功能  : slave i2c死锁恢复
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void slave_i2c_lock_reset()
{
    FlagStatus pin_scl_status = RESET;
    FlagStatus pin_sda_status = RESET;
    static uint32_t pre_ticks = 0;  

    pin_scl_status = gpio_input_bit_get(GPIO_I2C_SLAVE_PORT, GPIO_I2C_SLAVE_SCL);
	pin_sda_status = gpio_input_bit_get(GPIO_I2C_SLAVE_PORT, GPIO_I2C_SLAVE_SDA);

    /* add by fangzhe, 20250422, 原因:异常i2c状态 */
    if(1 == pin_scl_status && 0 == pin_sda_status)
    {		
        /* add by fangzhe, 20250422, 原因:异常计数 。计数器也一个计时开关*/
        g_mcu_vars_param.g_i2c_exception_irq_status_counter++;

        /* add by fangzhe, 20250422, 原因:异常状态开始计时。例如:i2c恢复正常，
        计数就会清零；计时pre_ticks不用清零，因为重新开始计数时，计时pre_ticks会重新赋值。
        
        */
        if(1 == g_mcu_vars_param.g_i2c_exception_irq_status_counter)
        {			//g_slave_i2c_reset_flag = SET;
            pre_ticks = MCU_SYSTEM_SECS_PERIOD;			
        }
      
        if( g_mcu_vars_param.g_i2c_exception_irq_status_counter > 3)
        {
            /*都为无符号整数,等待4秒钟*/
            if(MCU_SYSTEM_SECS_PERIOD  >= (10 + pre_ticks)) 
            {                
                reset_slave_i2c(SLAVE_I2C);
                g_mcu_vars_param.g_i2c_exception_irq_status_counter = 0;
               // pre_ticks = MCU_SYSTEM_SECS_PERIOD;

            }
        }	

    }   

}

/*****************************************************************************
 * 函 数 名  : slave_i2c_middle_handle
 * 负 责 人  : fz
 * 创建日期  : 2023年7月19日
 * 函数功能  : 在main的while循环中处理write和read
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void slave_i2c_middle_handle(void)
{
    FlagStatus pin_scl_status = RESET;
	FlagStatus pin_sda_status = RESET;
   
    pin_scl_status = gpio_input_bit_get(GPIO_I2C_SLAVE_PORT, GPIO_I2C_SLAVE_SCL);
	pin_sda_status = gpio_input_bit_get(GPIO_I2C_SLAVE_PORT, GPIO_I2C_SLAVE_SDA);

    /* add by fangzhe, 20250422, 原因:非异常状态时计数清零 */
	if(!(1 == pin_scl_status && 0 == pin_sda_status))
	{
		 g_mcu_vars_param.g_i2c_exception_irq_status_counter = 0;		
			
	}
    
	if(SET == g_i2c_global_vars.g_slave_read_handle_flag)
	{
		slave_i2c_read_handle();
		
	}

    /* add by fangzhe, 20250321, 原因:因为 地址匹配中断对writing状态做了
        处理，这里调用是不会发生的；但是为了程序的完整性还是保留
    */
	if(SET == g_i2c_global_vars.g_slave_receive_handle_flag)
	{		
		slave_i2c_receive_handle();
	}
	
	if(SET == g_i2c_global_vars.g_slave_write_handle_flag)
	{
		slave_i2c_write_handle();		
		
	}

	if(SET == g_i2c_global_vars.g_slave_address_handle_flag)
	{
		slave_i2c_address_match_handle();
	}

    slave_i2c_lock_reset();
	
}


/*****************************************************************************
 * 函 数 名  : i2c_slave_read_write_handle
 * 负 责 人  : fz
 * 创建日期  : 2023年5月27日
 * 函数功能  : 在main 的while循环中处理write 和 read
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void i2c_slave_read_write_handle(void)
{
	slave_i2c_middle_handle();
}


/*****************************************************************************
 * 函 数 名  : slave_error_irq_handler
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c1的slave错误中断事件处理功能
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c1的slave错误中断事件产生
 * 其    它  : 无

*****************************************************************************/
void slave_error_irq_handler(void)
{
    /* bus error 它用于指示在 I2C 通信过程中发生了?总线错误*/
	/*验证:通信时拔掉i2c的线就进入这个中断；reset_slave_i2c后可以恢复*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_BERR))
	{
		i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_BERR);		
		reset_slave_i2c(SLAVE_I2C);
    }

    /* arbitration lost 通信里用于表示仲裁丢失（Arbitration Lost
）的中断标志。本方案没有i2c仲裁，可以不处理*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_LOSTARB))
	{
        i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_LOSTARB);
        reset_slave_i2c(SLAVE_I2C);
    }

    /* over-run or under-run when SCL stretch is disabled I
    2C_INT_FLAG_OUERR 代表上溢 / 下溢错误（Overrun/Underrun Error）中断标志。在 
I2C 通信过程中，当数据传输的速率与设备处理数据的速率不匹配时，就可能会出现上溢或下溢的情况，
从而触发该中断。
    验证:升级时，不作disable ADDM，就会反复响应ADDM中断，这时会产生I2C_INT_FLAG_OUERR

*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_OUERR)){
        i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_OUERR);
		reset_slave_i2c(SLAVE_I2C);
    }

    /* PEC error I2C 数据包错误校验（PEC）错误中断标志*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_PECERR))
	{
       i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_PECERR);
    }

    /* timeout error 它用于指示 I2C 通信过程中发生了 超时错误。*/
     /* 还没造出TIMEOUT中断*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_TIMEOUT))
	{
        i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_TIMEOUT);

		/* add by fz, 20250310, 原因:超时就恢复i2c */		
		reset_slave_i2c(SLAVE_I2C);
    }

    /* SMBus alert  SMBus 告警（SMBus Alert）中断标志。它用于指示在 SMBus（System Management Bus
） 通信中，从设备触发了 SMBus 告警*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_SMBALT))
	{
        i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_SMBALT);
		
		/* add by fz, 20250310, 原因:就恢复i2c */		
		reset_slave_i2c(SLAVE_I2C);
    }

	//它用于指示在 I2C 通信过程中，从设备（Slave）未发送应答信号（NACK）
	if (i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_NACK)) 
     {
	  	
		// 停止当前通信
        i2c_stop_on_bus(SLAVE_I2C);
		
        // 清除NACK中断标志
        i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_NACK);		
        
    }	
 
	
}

/*****************************************************************************
 * 函 数 名  : master_event_irq_handler
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master中断事件
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c0的中断事件产生
 * 其    它  : 

*****************************************************************************/
void master_i2c_event_irq_handler(uint32_t dev_i2c)
{
	uint8_t data = 0;
	I2C_MASTER_BUFF_CFG *p_master_cfg;

	if(CHECK_DEV_ERR_I2C(dev_i2c))
	{
		return;
	}
		
	if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_RBNE))
	{
		
		i2c_interrupt_enable(dev_i2c, I2C_INT_STPDET | I2C_INT_TC);
	
		
		/*主机接收*/	
		data = i2c_data_receive(dev_i2c);		

	//	i2c_master_info_get_buff_info(&p_master_cfg);
		p_master_cfg = GET_MASTER_CFG_OF_I2C(dev_i2c);
		if(NULL != p_master_cfg)
		{
			/*首次进入接收中断*/
			if(0 == p_master_cfg->read_flag)
			{
				p_master_cfg->read_flag = 1;
				memset(p_master_cfg->master_buffer,0,sizeof(p_master_cfg->master_buffer));
				p_master_cfg->buffer_idx = 0;
			}
		}

		i2c_master_buffer_info_data_add(dev_i2c,data);
		
		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_RBNE_STATUS;
        
		
	}
	else if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_TI))
	{		
			
			data = i2c_master_info_popup_data_from_buffer(dev_i2c);	
			i2c_data_transmit(dev_i2c, data);		
				
			g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_TI_STATUS;
             
    }
	else if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_TC))
	{
		/*主机发送最后一个字节或者接收最后一个字节*/  		
		//i2c_master_info_get_buff_info(&p_master_cfg);		
		p_master_cfg= GET_MASTER_CFG_OF_I2C(dev_i2c);

		//处理I2C_INT_FLAG_RBNE
		if(g_i2c_global_vars.g_master_i2c_irq_status_pre == I2C_INT_RBNE_STATUS) 
        {
        	i2c_stop_on_bus(dev_i2c);
		}	
			
		//处理两个以上I2C_INT_FLAG_TI;
		//当MASTER为读的时，先写一个寄存器值，然后会TC；所以这里会data > 1
		//当master为写的时，因为引用的是外部缓冲区，这就可能无效
		/* modify by fz, 20230828, 原因:改成由g_master_buffer 缓冲区发送数据*/
		if(g_i2c_global_vars.g_master_i2c_irq_status_pre == I2C_INT_TI_STATUS && 
		 2 == p_master_cfg->read_flag) //当前是write，master write
		{
			i2c_stop_on_bus(dev_i2c);
		}

		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_TC_STATUS;
		i2c_interrupt_disable(dev_i2c,I2C_INT_TC);
        
	
    }
	else if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_STPDET))
	{
        /* clear STPDET interrupt flag */

		i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_STPDET);		
      
		/*i2c 状态中止,释放资源*/		
		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;		       
		
    }
	
}

/*****************************************************************************
 * 函 数 名  : Master_ErrorIRQ_Handler
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master的出错中断事件
 * 输入参数  : uint32_t dev_i2c i2c总线，MASTER_A_I2C，MASTER_B_I2C
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c0的出错中断事件产生
 * 其    它  : 无

*****************************************************************************/
void master_i2c_error_irq_handler(uint32_t dev_i2c)
{
	    /* bus error */			
    if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_BERR))
	{
        i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_BERR);
		reset_master_i2c(dev_i2c);
    }

    /* arbitration lost */
    if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_LOSTARB))
	{
        i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_LOSTARB);
        reset_master_i2c(dev_i2c);
    }

    /* over-run or under-run when SCL stretch is disabled */
    if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_OUERR))
	{
        i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_OUERR);
		reset_master_i2c(dev_i2c);
    }

    /* PEC error */
    if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_PECERR))
	{
       i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_PECERR);
    }

    /* timeout error ，还没造出TIMEOUT中断*/
    if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_TIMEOUT))
	{
        i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_TIMEOUT);
		reset_master_i2c(dev_i2c);

    }

    /* SMBus alert */
    if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_SMBALT))
	{
        i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_SMBALT);
		reset_master_i2c(dev_i2c);
    }

	//它用于指示在 I2C 通信过程中，从设备（Slave）未发送应答信号（NACK）
	if (i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_NACK)) 
     {
	  	
		// 停止当前通信
        i2c_stop_on_bus(dev_i2c);
		
        // 清除NACK中断标志
        i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_NACK);		
        
    }

    /* disable the I2C0 interrupt */
   // i2c_interrupt_disable(dev_i2c, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_TI | 
		//I2C_INT_TC | I2C_INT_RBNE);	


}

/*****************************************************************************
 * 函 数 名  : slave_i2c_dev_config
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : slave i2c的总线初始化
 * 输入参数  : uint32_t dev_i2c,  i2c总线
 				uint32_t adress,   址
			uint8_t nvic_event_irq, 中断事件向量
			uint8_t nvic_error_irq  错误事向量
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void slave_i2c_dev_config(uint32_t dev_i2c,uint32_t adress,
			uint8_t nvic_event_irq,uint8_t nvic_error_irq)
{
	/*初始化slave buffer缓冲空间*/
	i2c_slave_buffer_info_clear();
	
	//rcu_i2c_clock_config(SLAVE_I2C,RCU_I2CSRC_IRC8M);
	rcu_i2c_clock_config(dev_i2c,RCU_I2CSRC_CKSYS);

	 /* configure I2C timing */
    i2c_timing_config(dev_i2c, 0, 0x9, 0);

	 /* add by fz, 20250303, 原因:i2c速率调到400K */
    i2c_master_clock_config(dev_i2c, 0x39, 0xBB);

     //i2c速率调到400K
   // i2c_master_clock_config(dev_i2c, 0x50, 0x73);
	
    /* configure I2C address */
	i2c_second_address_config(dev_i2c, adress,ADDRESS2_MASK_ALL);
	
    /* enable I2C1 */
    i2c_enable(dev_i2c);


	//优先级调到最高
	nvic_irq_enable(nvic_event_irq,NIVC_IRQ_GROUP,I2C_SLAVE_IRQ_EVENT_PRI);

	//使能错误中断
	nvic_irq_enable(nvic_error_irq, NIVC_IRQ_GROUP, I2C_SLAVE_IRQ_ERR_PRI);

	/* enable the I2C1 interrupt */
	i2c_interrupt_enable(dev_i2c, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_ADDM | 
		I2C_INT_TI | I2C_INT_RBNE);
	

}


/*****************************************************************************
 * 函 数 名  : slave_i2c_config_init
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的slave配置初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void slave_i2c_config_init()
{
   
	slave_i2c_dev_config(SLAVE_I2C,MCU_SECOND_ADDRESS7,SLAVE_EV_IRQn,SLAVE_ER_IRQn);
}
/*****************************************************************************
 * 函 数 名  : get_master_i2c_by_dev_address
 * 负 责 人  : fz
 * 创建日期  : 2024年4月9日
 * 函数功能  : 依据设备地址得到i2c总线
 * 输入参数  : uint32_t dev_address 设备地址
 * 输出参数  : uint32_t *ptr_i2c i2c总线，MASTER_A_I2C 或MASTER_B_I2C
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void get_master_i2c_by_dev_address(uint32_t dev_address,uint32_t *ptr_i2c)
{
	
	//uint8_t masterBi2c_mapAddress[2] = {0x48,0xc6};//10G 设备地址，固定值
	uint8_t masterBi2c_mapAddress[2] = {GN7153_SLAVE_ADDRESS,
	                UX3326_SLAVE_ADDRESS};//10G 设备地址，固定值
	uint32_t i = 0;
	if(NULL != ptr_i2c)
	{
		for(i = 0; i < sizeof(masterBi2c_mapAddress);i++)
		{
			if(dev_address == masterBi2c_mapAddress[i])
			{
				*ptr_i2c = MASTER_B_I2C;//10G，1G
				return;
			}
		}

		*ptr_i2c = MASTER_A_I2C;	//50G	
	}
	return;
    
}


/*****************************************************************************
 * 函 数 名  : master_i2c_set_irq_status_info
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年5月3日
 * 函数功能  : 保存master的i2c状态
 * 输入参数  : uint32_t dev_i2c,  MASTER_A_I2C或MASTER_B_I2C
                uint32_t irq_status 见MCU_I2C_INT_STATUS
                uint8_t work : 0-为masterWrite,1-masterRead;
 * 输出参数  : 无
 * 返 回 值  : 0-成功;其它失败
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
uint32_t master_i2c_set_irq_status_info(uint32_t dev_i2c,
                uint32_t irq_status,
                uint32_t regAddr,
                uint8_t work)
{
    if(MASTER_A_I2C == dev_i2c)
    {
        g_i2c_global_vars.g_master_i2c_status.I2cOp.bits.MasterA_Irq = irq_status;
        g_i2c_global_vars.g_master_i2c_status.I2cOp.bits.MasterAWork = work; /*0为write,1为read*/
        g_i2c_global_vars.g_master_i2c_status.I2cA_RegAddr = regAddr;
         
    }
    else if(MASTER_B_I2C == dev_i2c)
    {
       g_i2c_global_vars.g_master_i2c_status.I2cOp.bits.MasterB_Irq = irq_status; 
       g_i2c_global_vars.g_master_i2c_status.I2cOp.bits.MasterBWork = work; 
       g_i2c_global_vars.g_master_i2c_status.I2cB_RegAddr = regAddr;
    }
    else
    {
        return 1;
    }

    return 0;
}

/*****************************************************************************
 * 函 数 名  : master_reg_byte_write
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master写功能
 * 输入参数  : uint32_t slave_addr  slave地址
 				uint8_t* p_buffer	要写入的数据，p_buffer[0]是寄存器
 				uint32_t buffer_len 数据的长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void master_reg_byte_write(uint32_t slave_addr,
									uint8_t* p_buffer, 
									uint32_t buffer_len	)
{	
	uint32_t run_us = 0;
	uint8_t cyl = 0;
	I2C_MASTER_BUFF_CFG *p_master_cfg = NULL;
	uint32_t master_i2c = MASTER_A_I2C; //50G

    /*跟踪i2c状态才用到,主要调试dsp和tec共用i2c*/
    uint32_t testRegAddr = 0;

     /*参数判断，长度至少为2字节，最大长度不超过buff空间*/
	if(NULL == p_buffer || buffer_len < 2 || buffer_len >= I2C_MASTER_BUFFER_MAX)
	{
		return;
	}	

    if(DSP_FSL_SLAVE_ADDRESS == slave_addr)
    {
        testRegAddr = get_u32(p_buffer);
    }
    else
    {
        testRegAddr = p_buffer[0];
    }

	get_master_i2c_by_dev_address(slave_addr,&master_i2c);
	
	run_us = CYCLE_DELAY_TIME_US;
	cyl = 0;
	while_fun((g_i2c_global_vars.g_master_i2c_irq_status_pre != 
	I2C_INT_STPDET_STATUS),run_us,cyl);
	if(1 == cyl)
	{
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
            testRegAddr,
            0);
        return;
	}

	g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_NON_STATUS;

	/* clear I2C_TDATA register */
	I2C_STAT(master_i2c) |= I2C_STAT_TBE;

	/* send slave address to I2C bus*/
	i2c_master_addressing(master_i2c, slave_addr, I2C_MASTER_TRANSMIT);

	/* configure number of bytes to be transferred */
	i2c_transfer_byte_number_config(master_i2c, buffer_len);

	i2c_interrupt_enable(master_i2c, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_TI | 
	I2C_INT_TC | I2C_INT_RBNE);

    /*用有限循环代替无限循环*/
	// while(i2c_flag_get(MASTER_A_I2C, I2C_FLAG_I2CBSY));
	run_us = CYCLE_DELAY_TIME_US;
	cyl = 0;
	while_fun(i2c_flag_get(master_i2c, I2C_FLAG_I2CBSY),run_us,cyl);
	if(1 == cyl)
	{
		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;
		i2c_disable(master_i2c);
		i2c_enable(master_i2c);

         /* add by fangzhe, 20250503, 原因:增加监控状态 */
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
            testRegAddr,
            0);
		
		return;
	}	


	/*改成由g_master_buffer缓冲区发送数据*/
	p_master_cfg = GET_MASTER_CFG_OF_I2C(master_i2c);

    /* add by fangzhe, 20250321, 原因:清空缓存 */
	i2c_master_info_buffer_clear(p_master_cfg);

	p_master_cfg->read_flag = 0x2; //写模式
	memcpy(p_master_cfg->master_buffer,p_buffer,buffer_len);

	/* the master sends a start condition to I2C bus */
	i2c_start_on_bus(master_i2c);

    /* add by fangzhe, 20250321, 原因:有限等待代替无限等待 ，
    g_master_i2c_irq_status_pre会在中断中置为I2C_INT_STPDET_STATUS
        */
	run_us = CYCLE_DELAY_TIME_US;
	cyl = 0;
	while_fun(((g_i2c_global_vars.g_master_i2c_irq_status_pre != I2C_INT_STPDET_STATUS)),run_us,cyl);
	if(1 == cyl)
	{
		i2c_interrupt_disable(master_i2c, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_TI | 
			I2C_INT_TC | I2C_INT_RBNE);
		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;

		i2c_disable(master_i2c);
		i2c_enable(master_i2c);	

           /* add by fangzhe, 20250503, 原因:增加监控状态 */
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
            testRegAddr,
            0);
	}	

   /* add by fangzhe, 20250503, 原因:增加监控状态 */
    master_i2c_set_irq_status_info(master_i2c,
        g_i2c_global_vars.g_master_i2c_irq_status_pre,
        testRegAddr,
        0);


}

/*****************************************************************************
 * 函 数 名  : master_dsp_fsl_reg_4byte_write
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master写功能,只针对dsp特殊地址及寄存器
 * 输入参数  : uint32_t slave_addr  slave地址
 				uint8_t* p_buffer	要写入的数据，p_buffer[0]是寄存器
 				uint32_t buffer_len 数据的长度
 				
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : dsp的寄存器宽度是20bit,写入的实质是3个字节的寄存器。
 例程代码 
 #define RegisterWrite(reg, val) I2C_RegisterWrite((UINT32)((UINTPTR)(&reg) >> 2), val)
 4字节左移两位后
 txBuff[0] = (uint8_t)((addr >> 16) & 0xff);
    txBuff[1] = (uint8_t)((addr >> 8) & 0xff);
    txBuff[2] = (uint8_t)((addr >> 0) & 0xff);

*****************************************************************************/
void master_dsp_fsl_reg_4byte_write(uint32_t slave_addr,
									uint8_t* p_buffer, 
									uint32_t buffer_len	)
{
    uint32_t reg_address = 0;
    uint32_t dsp_reg = 0;
    uint8_t* dsp_buff_ptr = NULL;
    uint32_t dsp_buff_len = 0;

    //四字节寄存器+uin32_t字节数
   // if(DSP_FSL_SLAVE_ADDRESS != slave_addr || buffer_len < 8)
   if(buffer_len < 8)
    {
        return;
    }

    //获取地址,并且转换dsp寄存器格式
    //例程给的先要右移两位
    reg_address = (get_u32(p_buffer));
    dsp_reg = (reg_address >> 2);

    dsp_buff_ptr = &p_buffer[1];
    dsp_buff_len = (buffer_len - 1);
    dsp_buff_ptr[0] = (uint8_t)((dsp_reg >> 16) & 0xff);
    dsp_buff_ptr[1] = (uint8_t)((dsp_reg >> 8) & 0xff);
    dsp_buff_ptr[2] = (uint8_t)((dsp_reg >> 0) & 0xff);
    
    master_reg_byte_write(slave_addr,dsp_buff_ptr,dsp_buff_len);

    return;
    
    
}

/*****************************************************************************
 * 函 数 名  : master_reg_1byte_size_read
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master的单字节寄存器读功能
 * 输入参数  : uint32_t slave_addr  slave地址
 				uint8_t	reg	是寄存器 				
 				uint32_t buffer_len 数据的长度
 * 输出参数  : uint8_t *p_buffer  要读的的buffer
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void master_reg_1byte_size_read(uint32_t slave_address,uint8_t reg,uint8_t *p_buffer,
	uint32_t buffer_len)
{
	I2C_ALL_ADDRESS_INFO address_info;
	memset(&address_info,0,sizeof(I2C_ALL_ADDRESS_INFO));
	address_info.slave_address = slave_address;
	address_info.reg_size = 1;
	address_info.regaddress[0] = reg;
	master_reg_byte_read(&address_info,slave_address,p_buffer,buffer_len);
	return;
}

/*****************************************************************************
 * 函 数 名  : master_reg_2byte_size_read
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master的两字节寄存器读功能
 * 输入参数  : uint32_t slave_addr  slave地址
 				uint16_t	reg	是寄存器 				
 				uint32_t buffer_len 数据的长度
 * 输出参数  : uint8_t *p_buffer  要读的的buffer
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void master_reg_2byte_size_read(uint32_t slave_address,uint16_t reg,uint8_t *p_buffer,
	uint32_t buffer_len)
{
	I2C_ALL_ADDRESS_INFO address_info;
	memset(&address_info,0,sizeof(I2C_ALL_ADDRESS_INFO));
	address_info.slave_address = slave_address;
	address_info.reg_size = 2;
	set_u16(address_info.regaddress, reg);
	master_reg_byte_read(&address_info,slave_address,p_buffer,buffer_len);
	return;
}

/*****************************************************************************
 * 函 数 名  : master_dsp_fsl_reg_4byte_size_read
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master的四字节寄存器读功能
 * 输入参数  : uint32_t slave_addr  slave地址
 				uint32_t	reg	是寄存器 				
 				uint32_t buffer_len 数据的长度
 * 输出参数  : uint8_t *p_buffer  要读的的buffer
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无,见master_dsp_fsl_reg_4byte_write。参数是4字节寄存器，实质发出去的是3字节

*****************************************************************************/
void master_dsp_fsl_reg_4byte_size_read(uint32_t slave_address,uint32_t reg,uint8_t *p_buffer,
	uint32_t buffer_len)
{
    I2C_ALL_ADDRESS_INFO address_info;
    uint32_t read_address = 0;
    uint32_t dsp_reg = 0;
	memset(&address_info,0,sizeof(I2C_ALL_ADDRESS_INFO));
       
    if(NULL == p_buffer)
    {
        return;
    }

    read_address = ((((slave_address >> 3) << 2) +2) << 1);

    //dsp的要求，先右移两位
    dsp_reg = reg >> 2;
    
    address_info.slave_address = slave_address;
    address_info.reg_size = 3;
    address_info.regaddress[0] = (uint8_t)((dsp_reg >> 16) & 0xff);
    address_info.regaddress[1] = (uint8_t)((dsp_reg >> 8) & 0xff);
    address_info.regaddress[2] = (uint8_t)((dsp_reg >> 0) & 0xff);  
	master_reg_byte_read(&address_info,read_address,p_buffer,buffer_len);
    return;
    
}

/*****************************************************************************
 * 函 数 名  : master_reg_byte_read
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master读功能
 * 输入参数  : uint32_t slave_addr  	slave地址
 				uint8_t reg_address,  	寄存器地址 				
 				uint32_t buffer_len 	要读出的数据的长度
 * 输出参数  : uint8_t* p_buffer		读出数据时的buffer
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void master_reg_byte_read(I2C_ALL_ADDRESS_INFO *p_address_info,uint32_t read_addr,
							uint8_t* p_buffer, 
							uint32_t buffer_len	)
{
	uint32_t i = 0;
	uint32_t run_us = 0;
	uint8_t cyl = 0;
	I2C_MASTER_BUFF_CFG *p_master_cfg = NULL;
	uint32_t master_i2c = MASTER_A_I2C;

	if(0u == p_buffer || buffer_len < 1
		|| buffer_len > I2C_MASTER_BUFFER_MAX)
	{
		return;
	}

	if(NULL == p_address_info)
	{
		return;
	}


	get_master_i2c_by_dev_address(p_address_info->slave_address,
		&master_i2c);

	run_us = CYCLE_DELAY_TIME_US;
	cyl = 0;
	while_fun(g_i2c_global_vars.g_master_i2c_irq_status_pre != I2C_INT_STPDET_STATUS,run_us,cyl);
	if(1 == cyl)
	{
	    /* add by fangzhe, 20250503, 原因:增加监控状态 */
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
            read_addr,
            1);
		return;
	}

	g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_NON_STATUS;

	p_master_cfg = GET_MASTER_CFG_OF_I2C(master_i2c);
	i2c_master_info_buffer_clear(p_master_cfg);
	
	i2c_interrupt_enable(master_i2c, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_TI | 
		I2C_INT_TC | I2C_INT_ADDM | I2C_INT_RBNE);
	
	//i2c_interrupt_disable(MASTER_A_I2C,I2C_INT_STPDET);

	I2C_STAT(master_i2c) |= I2C_STAT_TBE;
	
	/* send slave address to I2C bus*/
    i2c_master_addressing(master_i2c, p_address_info->slave_address, I2C_MASTER_TRANSMIT);
	i2c_transfer_byte_number_config(master_i2c, p_address_info->reg_size);
	
	//while(i2c_flag_get(MASTER_A_I2C, I2C_FLAG_I2CBSY));	
	run_us = CYCLE_DELAY_TIME_US;
	cyl = 0;
	while_fun(i2c_flag_get(master_i2c, I2C_FLAG_I2CBSY),run_us,cyl);
	if(1 == cyl)
	{
		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;
		i2c_disable(master_i2c);
		i2c_enable(master_i2c);		

        /* add by fangzhe, 20250503, 原因:增加监控状态 */
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
            read_addr,
            1);
		return;
	}

	/*寄存器放入缓存区，在master_event_irq_handler中发送*/
	/*g_master_buffer[0] = reg_address; 
	g_master_buff_ptr = g_master_buffer;*/
	memcpy(&(p_master_cfg->address_info),p_address_info,
			sizeof(I2C_ALL_ADDRESS_INFO));

	memcpy(p_master_cfg->master_buffer,p_master_cfg->address_info.regaddress,
		p_master_cfg->address_info.reg_size);
	
	
    i2c_start_on_bus(master_i2c); 
    
	/*以上是发送reg_address*/

	 /* wait until TC bit is set ，发送完成了*/
	run_us = CYCLE_DELAY_TIME_US;
	cyl = 0;
	while_fun(!i2c_flag_get(master_i2c, I2C_FLAG_TC),run_us,cyl);
	if(1 == cyl)
	{
		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;
		i2c_disable(master_i2c);
		i2c_enable(master_i2c);		

            /* add by fangzhe, 20250503, 原因:增加监控状态 */
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
             read_addr,
            1);
		return;
	}	
	
		
    /* send slave address to I2C bus ,master开始读，也就是接收read_addr*/
  //  i2c_master_addressing(master_i2c, p_address_info->slave_address, I2C_MASTER_RECEIVE);
    i2c_master_addressing(master_i2c, read_addr, I2C_MASTER_RECEIVE);
	i2c_transfer_byte_number_config(master_i2c, buffer_len);
	
    i2c_start_on_bus(master_i2c); 

	run_us = CYCLE_DELAY_TIME_US; /*之前为３，时间太短了*/
	cyl = 0;
	while_fun(g_i2c_global_vars.g_master_i2c_irq_status_pre != I2C_INT_STPDET_STATUS,
		run_us,cyl);
	if(1 == cyl)
	{
		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;
		i2c_disable(master_i2c);
		i2c_enable(master_i2c);	

        /* add by fangzhe, 20250503, 原因:增加监控状态 */
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
            read_addr,
            1);
		return;
	}

    /* add by fangzhe, 20250503, 原因:增加监控状态 */
    master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
             read_addr,
            1);

	//???p_buffer[0] = g_master_buffer[0];
	//i = g_master_buffer[0];调试才用
	memcpy(p_buffer,p_master_cfg->master_buffer,buffer_len);

}


/*****************************************************************************
 * 函 数 名  : master_i2c_config_init
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master配置初始化
 * 输入参数  : uint32_t dev_i2c i2c总线
                uint32_t adress 设备地址
		        uint8_t nvic_event_irq 中断事件优先级
		        uint8_t nvic_err_irq  异常中断优先级
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void master_i2c_dev_config(uint32_t dev_i2c,uint32_t adress,
		uint8_t nvic_event_irq,uint8_t nvic_err_irq)
{
	/*清零master 数据缓冲区*/
	I2C_MASTER_BUFF_CFG * p_master_cfg = NULL;

	if(CHECK_DEV_ERR_I2C(dev_i2c))
	{
		return;
	}

	p_master_cfg = GET_MASTER_CFG_OF_I2C(dev_i2c);
	i2c_master_info_buffer_clear(p_master_cfg);

	rcu_i2c_clock_config(dev_i2c,RCU_I2CSRC_CKSYS);

	/* configure I2C timing */
	i2c_timing_config(dev_i2c, 0, 0x9, 0);

	/* add by fz, 20250303, 原因:i2c速率调到400K */
	//i2c_master_clock_config(dev_i2c, 0x73, 0x73);////对应400K

    i2c_master_clock_config(dev_i2c, 0x39, 0xBB);

	/* clear I2C_TDATA register */
	I2C_STAT(dev_i2c) |= I2C_STAT_TBE;    


	/* configure I2C address */
	i2c_address_config(dev_i2c, adress, I2C_ADDFORMAT_7BITS);

	i2c_automatic_end_disable(dev_i2c);	


	/* enable MASTER_A_I2C */
	i2c_enable(dev_i2c);	

	nvic_irq_enable(nvic_event_irq,NIVC_IRQ_GROUP,I2C_MASTER_IRQ_EVENT_PRI);

	/* add by fz, 20250310, 原因:有两条master i2c线 ，不处理错误中断
		在master模式下出错容易恢复
	*/
	nvic_irq_enable(nvic_err_irq,NIVC_IRQ_GROUP,I2C_MASTER_IRQ_ERR_PRI);

	 /* enable the MASTER_A_I2C interrupt */
    i2c_interrupt_enable(dev_i2c, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_TI | 
		I2C_INT_TC | I2C_INT_ADDM | I2C_INT_RBNE);
 
}



/*****************************************************************************
 * 函 数 名  : master_i2c_config_init
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master配置初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void master_i2c_config_init()
{
	master_i2c_dev_config(MASTER_B_I2C,MCU_I2C_ADDRESS7,MASTER_B_EV_IRQn,MASTER_B_ER_IRQn);
	master_i2c_dev_config(MASTER_A_I2C,MCU_I2C_ADDRESS7,MASTER_A_EV_IRQn,MASTER_A_ER_IRQn);
	
}


/*****************************************************************************
 * 函 数 名  : slave_reg_byte_read
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的slave读功能
 * 输入参数  : uint32_t slave_addr  	slave地址
 				uint8_t reg_address,  	寄存器地址 				
 				uint32_t buffer_len 	要读出的数据的长度
 * 输出参数  : uint8_t* p_buffer		读出数据时的buffer
 * 返 回 值  : 无
 * 调用关系  : 无
 * 其    它  : 这里的buffer_len是给出的g_slave_buff空间的最大缓存长度 :I2C_SLAVE_WRITE_READ_MAX
               如果是mcu的地址，则实际读取的长度由各接口确定;
               如果是外置芯片的地址，则只读取一个字节

*****************************************************************************/
void slave_v2_reg_byte_read(I2C_ALL_ADDRESS_INFO *p_slave_info,
							uint8_t* p_buffer, 
							uint32_t buffer_len	)
{
	uint32_t i = 0;
	
	if(buffer_len > I2C_SLAVE_WRITE_READ_MAX)
	{
		buffer_len = I2C_SLAVE_WRITE_READ_MAX;
	}

	if(NULL == p_slave_info)
	{
		return;
	}	
	
	for(i = 0; i < g_slave_read_cfg_idx;i++)
	{
		if(p_slave_info->slave_address == g_slave_read_cfg_callback_array[i].slave_address)
		{
			break;
		}
	}

	if(i < g_slave_read_cfg_idx)
	{
		
		g_slave_read_cfg_callback_array[i].callback(p_slave_info,
			p_buffer,buffer_len);
	}
	else
	{

		/*外置芯片读取数据长度为1字节；
			因为若统一按照max长度(255字节)读取，则外置芯片因为没有这么长度，就会
			异常。
		*/
	    if(DSP_FSL_SLAVE_ADDRESS == p_slave_info->slave_address)
        {
            uint32_t dsp_reg = 0;            
            dsp_reg = get_u32(p_slave_info->regaddress);
            master_dsp_fsl_reg_4byte_size_read(p_slave_info->slave_address,
                dsp_reg,
                p_buffer,200);              
        }
		else
        {
            master_reg_byte_read(p_slave_info,p_slave_info->slave_address,
    			p_buffer,1);

    		/*调试代码时查看值*/
    		i = p_buffer[0];
		}
      
	}

	return;
}


/*****************************************************************************
 * 函 数 名  : slave_reg_byte_write
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的slave写功能
 * 输入参数  : uint32_t slave_addr  slave地址
 				uint8_t* p_buffer	要写入的数据
 				uint32_t buffer_len 数据的长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void slave_reg_byte_write(uint32_t slave_addr,
									uint8_t* p_buffer, 
									uint32_t buffer_len	)
{	
	uint32_t i = 0;

	if(buffer_len > I2C_SLAVE_WRITE_READ_MAX)
	{
		buffer_len = I2C_SLAVE_WRITE_READ_MAX;
	}

    /*写的长度至少为2,寄存器+数据*/
	if(NULL == p_buffer || buffer_len < 2)
	{
		return;
	}

    /* delete by fangzhe, 20250321, 原因:目前无密码限制 */
#if 0
	if(USER_ACCESS_NO == user_check_write_reg_flag(MSC_REG_1BYTE(p_buffer)))
	{
		return;
	}
#endif
	
	for(i = 0; i < g_slave_write_cfg_idx;i++)
	{
		if(slave_addr == g_slave_write_cfg_callback_array[i].slave_address)
		{
			break;
		}
	}


	if(i < g_slave_write_cfg_idx)
	{			
		g_slave_write_cfg_callback_array[i].callback(slave_addr,p_buffer,buffer_len);		
				
	}
	else
	{	
	    if(DSP_FSL_SLAVE_ADDRESS == slave_addr)
        {           
           master_dsp_fsl_reg_4byte_write(slave_addr,p_buffer,buffer_len);
           
        }
		else
        {
           master_reg_byte_write(slave_addr,p_buffer,buffer_len);
		}
    
	}

	/*清空slave的buffer,??放在这儿或是外面更合理?*/
	i2c_slave_buffer_info_clear();

	return;
}


/*****************************************************************************
 * 函 数 名  : i2c全局变量初始化
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月23日
 * 函数功能  : i2c_global_param_init
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void i2c_global_param_init()
{  
    /*slave接收的地址*/
    g_i2c_global_vars.g_receive_address = 0;

    /*************************************************************************
    * 变量功能：i2c slave中断模式中，read handle标识
    * 取值范围：RESET-read未发生；SET-read发生；
    * 注意事项：无
    *************************************************************************/
    g_i2c_global_vars.g_slave_read_handle_flag = RESET;

    /*************************************************************************
    * 变量功能：i2c slave中断模式中，write handle标识
    * 取值范围：RESET-write未发生；SET-write发生；
    * 注意事项：无
    *************************************************************************/
    g_i2c_global_vars.g_slave_write_handle_flag = RESET;

    /*************************************************************************
    * 变量功能：i2c slave中断模式中，receive handle标识
    * 取值范围：RESET-receive未发生；SET-receive发生；
    * 注意事项：无
    *************************************************************************/
    g_i2c_global_vars.g_slave_receive_handle_flag = RESET;

    /*************************************************************************
    * 变量功能：i2c slave中断模式中, 地址匹配时设置处理标识位
    * 取值范围：RESET-当前中断中处理；SET-中断外处理地址匹配；
    * 注意事项：无
    *************************************************************************/
    g_i2c_global_vars.g_slave_address_handle_flag = RESET;

    /*************************************************************************
    * 变量功能：i2c中断模式中，write doing 
    * 取值范围：I2C_LOCK_IDLE-空闲;I2C_LOCK_BUSY-busy
    * 注意事项：无
    *************************************************************************/
    g_i2c_global_vars.g_write_doing_flag = I2C_LOCK_IDLE;

    /*************************************************************************
    * 变量功能：i2c中断模式中，read doing 
    * 取值范围：I2C_LOCK_IDLE-空闲;I2C_LOCK_BUSY-busy
    * 注意事项：无
    *************************************************************************/
    g_i2c_global_vars.g_read_doing_flag = I2C_LOCK_IDLE;

    /*master i2c 状机是否空闲，SET空闲,RESET不空闲*/
    /*************************************************************************
    * 变量功能：master i2c中断模式中当前的中断状态
    * 取值范围：中断状态。初始为停止状态
    * 注意事项：无
    *************************************************************************/
    g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;

    /* add by fz, 20231106, 原因:光模块访问标识 */
    g_i2c_global_vars.g_user_access_flag = USER_ACCESS_NO;  


    g_i2c_global_vars.g_master_i2c_status.I2cA_RegAddr = 0;
    g_i2c_global_vars.g_master_i2c_status.I2cB_RegAddr = 0;
    g_i2c_global_vars.g_master_i2c_status.I2cOp.I2cStatus = 0;



    memset((void*)g_slave_write_cfg_callback_array,0,
        sizeof(g_slave_write_cfg_callback_array));

    memset((void*)g_slave_read_cfg_callback_array,0,
        sizeof(g_slave_read_cfg_callback_array));

    return;

}


/*****************************************************************************
 * 函 数 名  : monitor_i2c_status_reg_read
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年5月3日
 * 函数功能  : 读取i2c的工作状态
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void monitor_i2c_status_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
    if(CMD_MONITOR_I2C_STATUS_REG != regaddr)
    {
        return;
    }

    pbuff[0] = (g_i2c_global_vars.g_master_i2c_status.I2cOp.I2cStatus & 0xFF);
    pbuff[1] = (g_i2c_global_vars.g_master_i2c_status.I2cOp.I2cStatus >> 8) & 0xFF;
    pbuff[2] = (g_i2c_global_vars.g_master_i2c_status.I2cOp.I2cStatus >> 16) & 0xFF;
    pbuff[3] = (g_i2c_global_vars.g_master_i2c_status.I2cOp.I2cStatus >> 24) & 0xFF;
   
    pbuff[4] = (g_i2c_global_vars.g_master_i2c_status.I2cA_RegAddr & 0xFF);
    pbuff[5] = (g_i2c_global_vars.g_master_i2c_status.I2cA_RegAddr >> 8) & 0xFF;
    pbuff[6] = (g_i2c_global_vars.g_master_i2c_status.I2cA_RegAddr >> 16) & 0xFF;
    pbuff[7] = (g_i2c_global_vars.g_master_i2c_status.I2cA_RegAddr >> 24) & 0xFF;

    pbuff[8] = (g_i2c_global_vars.g_master_i2c_status.I2cB_RegAddr & 0xFF);
    pbuff[9] = (g_i2c_global_vars.g_master_i2c_status.I2cB_RegAddr >> 8) & 0xFF;
    pbuff[10] = (g_i2c_global_vars.g_master_i2c_status.I2cB_RegAddr >> 16) & 0xFF;
    pbuff[11] = (g_i2c_global_vars.g_master_i2c_status.I2cB_RegAddr >> 24) & 0xFF;

   

    return;
}


 void test_i2c_restart_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
    uint8_t flag_i2c = 0;
    uint32_t i2c_dev = 0;
    if(TEST_I2C_RESTART_REG != pbuff[0])
    {
        return;
    }

    flag_i2c = pbuff[1];

    if('a' == flag_i2c || 'A' == flag_i2c)
    {
        i2c_dev = MASTER_A_I2C;
    }
    else  if('b' == flag_i2c || 'B' == flag_i2c)
    {
        i2c_dev = MASTER_B_I2C;
    }
    else
    {
        return;
    }

    i2c_disable(i2c_dev);
	i2c_enable(i2c_dev);

    return;
    
}

/* delete by fangzhe, 20250321, 原因:密码功能目前还不成熟 */

#if 1
/*****************************************************************************
 * 函 数 名  : user_check_password_write_reg
 * 负 责 人  : fz
 * 创建日期  : 2023年8月24日
 * 函数功能  : mcu检查密码
 * 输入参数  : uint8_t *p_buff,p_buff[0],SYSTEM_PASSWORD_REG
 				uint32_t buff_len   密码长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void user_check_password_write_reg(uint8_t *p_buff,uint32_t buff_len)
{
	uint32_t pwd_len = 0;
	uint8_t str_pwd[OPT_MOD_LIMIT_PASSWORD_LENGTH + 1];

	/*参数判断*/
	if(NULL == p_buff || buff_len < (OPT_MOD_LIMIT_PASSWORD_LENGTH + 1))
	{
		return;
	}

	/*寄存器核定*/
	if(CMD_OPTICAL_PASSWORD_LIMIT_REG != MSC_REG_1BYTE(p_buff))
	{
		return;
	}

	memset(str_pwd,0,sizeof(str_pwd));
	memcpy(str_pwd,&p_buff[1],OPT_MOD_LIMIT_PASSWORD_LENGTH);
	pwd_len = strlen((char*)str_pwd);
	

	if(pwd_len != strlen((char*)g_optical_limit_pwd))
	{
		g_i2c_global_vars.g_user_access_flag = USER_ACCESS_NO;
		return;
	}

	if(0 == memcmp(g_optical_limit_pwd,str_pwd,pwd_len))
	{
		g_i2c_global_vars.g_user_access_flag = USER_ACCESS_YES;
	}
	else if(0 == memcmp(str_pwd,"666666",sizeof("666666")))
	{
		g_i2c_global_vars.g_user_access_flag = USER_ACCESS_YES;
	}
	else
	{
		g_i2c_global_vars.g_user_access_flag = USER_ACCESS_NO;
		return;
	}
	
	
}


/*****************************************************************************
 * 函 数 名  : user_optical_pwd_limit_init
 * 负 责 人  : fz
 * 创建日期  : 2023年11月6日
 * 函数功能  : 光模块密码限定初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void user_optical_pwd_limit_init()
{
	memcpy(g_optical_limit_pwd,"fiberhome",sizeof("fiberhome"));
}


/*****************************************************************************
 * 函 数 名  : user_check_write_reg_flag
 * 负 责 人  : fz
 * 创建日期  : 2023年8月24日
 * 函数功能  : 检查i2c的write权限
 * 输入参数  : uint8_t reg 寄存器
 * 输出参数  : 无
 * 返 回 值  : USER_ACCESS_YES,有权访问；否则无权访问
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
uint8_t user_check_write_reg_flag(uint8_t reg)
{
	uint32_t i = 0;
	for(i = 0; i < sizeof(g_user_authority_access_array_write_reg);i++)
	{
		if(reg == g_user_authority_access_array_write_reg[i])
		{
			return USER_ACCESS_YES;
		}
			
	}

	return g_i2c_global_vars.g_user_access_flag;
}

#endif




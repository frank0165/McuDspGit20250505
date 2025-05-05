/***********************************************************************************

 * 文 件 名   : i2c_opt_IE.h
 * 负 责 人   : fz
 * 创建日期   : 2023年5月15日
 * 文件描述   : i2c处理master、slave
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/


/*!
    \file    I2C1_IE.c
    \brief   The header file of I2C0 and I2C1 interrupt
    
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

#ifndef _I2C_OPT_IE_H_
#define _I2C_OPT_IE_H_


#include "gd32e501.h"
#include "mcu_data_type.h"
#include "i2c_opt_ie_data_type.h"


/* function declarations */
/* handle I2C0 event interrupt request */


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
void master_i2c_event_irq_handler(uint32_t dev_i2c);

/*****************************************************************************
 * 函 数 名  : master_i2c_error_irq_handler
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master的出错中断事件
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c0的出错中断事件产生
 * 其    它  : 无

*****************************************************************************/
void master_i2c_error_irq_handler(uint32_t dev_i2c);



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

*****************************************************************************/
//void Slave_EventIRQ_Handler(void);
void slave_event_irq_handler(uint32_t dev_i2c);

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
void slave_error_irq_handler(void);


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
void i2c_slave_read_write_handle();

/*****************************************************************************
 * 函 数 名  : master_reg_byte_write
 * 负 责 人  : fz
 * 创建日期  : 2023年5月15日
 * 函数功能  : i2c的master写功能
 * 输入参数  : uint32_t slave_addr  slave地址
 				uint8_t* p_buffer	要写入的数据
 				uint32_t buffer_len 数据的长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void master_reg_byte_write(uint32_t slave_addr,
									uint8_t* p_buffer, 
									uint32_t buffer_len	);

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
									uint32_t buffer_len	);

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
							uint32_t buffer_len	);

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
	uint32_t buffer_len);

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
	uint32_t buffer_len);


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
	uint32_t buffer_len);


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
 * 其    它  : 这里的buffer_len是给出的g_slave_buff空间的最大缓存长度
               如果是mcu的地址，则实际读取的长度由各接口确定;
               如果是外置芯片的地址，则只读取一个字节

*****************************************************************************/
void slave_v2_reg_byte_read(I2C_ALL_ADDRESS_INFO *p_slave_info,
							uint8_t* p_buffer, 
							uint32_t buffer_len);
							


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
									uint32_t buffer_len	);

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
void master_i2c_config_init();


/*****************************************************************************
 * 函 数 名  : slave_i2c_middle_handle
 * 负 责 人  : fz
 * 创建日期  : 2023年7月19日
 * 函数功能  : 在main的while循环中处理write和read
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 

*****************************************************************************/
void slave_i2c_middle_handle(void);


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
void slave_i2c_config_init();


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
void user_check_password_write_reg(uint8_t *p_buff,uint32_t buff_len);

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
void user_optical_pwd_limit_init();

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
uint8_t user_check_write_reg_flag(uint8_t reg);


/*****************************************************************************
 * 负 责 人  : fz
 * 创建日期  : 2024年4月9日
 * 函数功能  : 依据设备地址得到i2c总线
 * 输入参数  : uint32_t dev_address 设备地址
 * 输出参数  : uint32_t *ptr_i2c i2c总线，MASTER_A_I2C 或MASTER_B_I2C
 * 返 回 值  : 无
 * 调用关系  : i2c协议栈内部调用
 * 其    它  : 无

*****************************************************************************/
void get_master_i2c_by_dev_address(uint32_t dev_address,uint32_t *ptr_i2c);



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
void i2c_slave_buffer_info_clear();


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
void i2c_master_info_buffer_clear(I2C_MASTER_BUFF_CFG *ptr_buff);

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
	slave_address,I2C_READ_CFG_CALLBACK read_callback);

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
			slave_address,I2C_WRITE_CFG_CALLBACK write_callback);


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
//void i2c_global_param_init();

/*****************************************************************************
 * 函 数 名  : master_i2c_set_irq_status_info
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年5月3日
 * 函数功能  : 保存master的i2c状态
 * 输入参数  : uint32_t dev_i2c,  MASTER_A_I2C或MASTER_B_I2C
                uint32_t irq_status 见MCU_I2C_INT_STATUS
 * 输出参数  : 无
 * 返 回 值  : 0-成功;其它失败
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
uint32_t master_i2c_set_irq_status_info(uint32_t dev_i2c,
        uint32_t irq_status,
        uint32_t regAddr,
        uint8_t work);


 void test_i2c_restart_reg_write(uint8_t *pbuff,uint32_t bufflen);

#endif /* I2C_IE_H */

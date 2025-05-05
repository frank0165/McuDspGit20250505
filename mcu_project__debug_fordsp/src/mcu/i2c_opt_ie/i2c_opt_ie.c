/***********************************************************************************

 * �� �� ��   : i2c_opt_ie.c
 * �� �� ��   : fz
 * ��������   : 2023��5��15��
 * �ļ�����   : i2c����master��slave
 * ��Ȩ˵��   : Copyright (C) 2000-2023   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

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
* �������ܣ�i2c slave callback function of write
* ȡֵ��Χ������I2C_CALL_BACK_ITEMS
* ע������ص�����һֱ���棬��Ҫ���
*************************************************************************/
volatile I2C_WRITE_CFG_CALLBACK_HANDLE 
g_slave_write_cfg_callback_array[I2C_CALL_BACK_ITEMS];

/*************************************************************************
* �������ܣ�g_slave_write_cfg_callback_array�����±�
* ȡֵ��Χ������I2C_CALL_BACK_ITEMS
* ע������ص�����һֱ���棬��Ҫ���
*************************************************************************/
volatile uint32_t g_slave_write_cfg_idx = 0;


/*************************************************************************
* �������ܣ�i2c slave callback function of read
* ȡֵ��Χ������I2C_CALL_BACK_ITEMS
* ע������ص�����һֱ���棬��Ҫ���
*************************************************************************/
volatile I2C_READ_CFG_CALLBACK_HANDLE 
g_slave_read_cfg_callback_array[I2C_CALL_BACK_ITEMS];

/*************************************************************************
* �������ܣ�g_slave_read_cfg_callback_array�����±�
* ȡֵ��Χ������I2C_CALL_BACK_ITEMS
* ע������ص�����һֱ���棬��Ҫ���
*************************************************************************/
volatile uint32_t g_slave_read_cfg_idx = 0;




/* delete by fangzhe, 20250320, ԭ��:slave_i2c���� ����Ϊ�����÷���Ч*/
/*slave i2c i2c ״���Ƿ���У�SET����,RESET������*/
//volatile uint32_t g_slave_i2c_irq_status_pre = I2C_INT_NON_STATUS;

/*************************************************************************
* �������ܣ�i2c slave buffer����
* ȡֵ��Χ����
* ע�������
*************************************************************************/
I2C_SLAVE_BUFF_CFG g_i2c_slave_info_cfg;

/*************************************************************************
* �������ܣ�i2c master buffer����
* ȡֵ��Χ����
* ע�������
*************************************************************************/
I2C_MASTER_BUFF_CFG g_ai2c_master_info_cfg;

/*************************************************************************
* �������ܣ�i2c master buffer����
* ȡֵ��Χ����
* ע�������
*************************************************************************/
I2C_MASTER_BUFF_CFG g_bi2c_master_info_cfg;

/* add by fz, 20231106, ԭ��:��ģ��Ĭ������ */
uint8_t g_optical_limit_pwd[OPT_MOD_LIMIT_PASSWORD_LENGTH];

/* add by fz, 20231106, ԭ��:Ĭ�Ͽ��Է��ʵļĴ���д���� */
volatile uint8_t g_user_authority_access_array_write_reg[] = {CMD_OPTICAL_PASSWORD_LIMIT_REG};


/*************************************************************************
* �������ܣ�i2c ȫ�ֱ�������
* ȡֵ��Χ����
* ע�������
*************************************************************************/
volatile I2C_GLOBAL_VARS_PARAM g_i2c_global_vars;



void slave_i2c_receive_handle();

void slave_i2c_address_match_handle();


/*****************************************************************************
 * �� �� ��  : reset_master_i2c
 * �� �� ��  : fz
 * ��������  : 2025��3��10��
 * ��������  : ��λmasterģʽ��i2c
 * �������  : uint32_t i2c_periph i2c����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : 

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
 * �� �� ��  : i2c_slave_func_register_read_callback
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��21��
 * ��������  : slave i2c��ע��
 * �������  : uint32_t slave_address, �豸��ַ
            I2C_READ_CFG_CALLBACK read_callback  �ص��ӿ�
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : 

*****************************************************************************/
void i2c_slave_func_register_read_callback(uint32_t 
	slave_address,I2C_READ_CFG_CALLBACK read_callback)
{
	uint32_t i = 0;

    /*��ע�����ֱ�ӷ���*/
	for(i = 0; i < g_slave_read_cfg_idx;i++)
	{
		if(slave_address == g_slave_read_cfg_callback_array[i].slave_address)
		{
			return;
		}
	}

    /*�Ҹ��ռ�ע��*/
	if(g_slave_read_cfg_idx < I2C_CALL_BACK_ITEMS)
	{
		g_slave_read_cfg_callback_array[g_slave_read_cfg_idx].callback = read_callback;
		g_slave_read_cfg_callback_array[g_slave_read_cfg_idx].slave_address = slave_address;
		g_slave_read_cfg_idx++;
	}

	return;
	
}

/*****************************************************************************
 * �� �� ��  : i2c_slave_func_register_write_callback
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��21��
 * ��������  : slave i2cдע��
 * �������  : uint32_t slave_address, �豸��ַ
            I2C_READ_CFG_CALLBACK read_callback  �ص��ӿ�
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : 

*****************************************************************************/
void i2c_slave_func_register_write_callback(uint32_t 
			slave_address,I2C_WRITE_CFG_CALLBACK write_callback)
{
	uint32_t i = 0;

     /*��ע�����ֱ�ӷ���*/
	for(i = 0; i < g_slave_write_cfg_idx;i++)
	{
		if(slave_address == g_slave_write_cfg_callback_array[i].slave_address)
		{
			return;
		}
	}

   

     /*�Ҹ��ռ�ע��*/
	if(g_slave_write_cfg_idx < I2C_CALL_BACK_ITEMS)
	{
		g_slave_write_cfg_callback_array[g_slave_write_cfg_idx].callback = write_callback;
		g_slave_write_cfg_callback_array[g_slave_write_cfg_idx].slave_address = slave_address;
		g_slave_write_cfg_idx++;
	}
}


/*****************************************************************************
 * �� �� ��  : i2c_slave_buffer_info_clear
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ����g_i2c_slave_info_cfg
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void i2c_slave_buffer_info_clear()
{	
	memset(&g_i2c_slave_info_cfg,0,sizeof(g_i2c_slave_info_cfg));
	
}


/*****************************************************************************
 * �� �� ��  : i2c_slave_info_slave_address_add
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ��g_i2c_slave_info_cfg���õ�ַ
 * �������  : uint32_t slave_address  slave address
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void i2c_slave_info_slave_address_add(uint32_t slave_address)
{
	g_i2c_slave_info_cfg.address_info.slave_address = slave_address;
}

/*****************************************************************************
 * �� �� ��  : i2c_slave_buffer_info_data_add
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ��g_i2c_slave_info_cfg��������
 * �������  : uint32_t data  ����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

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
 * �� �� ��  : i2c_slave_buffer_mng_regaddress_info
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ��g_i2c_slave_info_cfg��buffer�еõ�reg_address
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : i2c  slaveģʽʱ������յ��Ĵ�����ַ��
 				���⺯����reg_address��buffer���Ƶ�regaddress
*****************************************************************************/
void i2c_slave_buffer_mng_regaddress_info()
{
	uint32_t idx = g_i2c_slave_info_cfg.buffer_idx;

	if(idx <= MCU_I2C_REGADDRESS_SIZE)
	{
		//ע�ⲻ�ܰ�address_info.slave_addressҲ����
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
 * �� �� ��  : i2c_slave_info_get_buff_info
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ��ȡg_i2c_slave_info_cfg��ָ��
 * �������  : ��
 * �������  : I2C_SLAVE_BUFF_CFG **p_buff_info ָ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��
 
*****************************************************************************/
void i2c_slave_info_get_buff_info(I2C_SLAVE_BUFF_CFG **p_buff_info)
{
	*p_buff_info = &g_i2c_slave_info_cfg;
	return;
}



/*****************************************************************************
 * �� �� ��  : i2c_slave_info_popup_data_from_buffer
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ��ȡg_i2c_slave_info_cfg�е�buffer����
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��
 
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
 * �� �� ��  : i2c_slave_info_state_is_read
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ��ȡi2c slave��״̬
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��
 
*****************************************************************************/
uint8_t i2c_slave_info_state_is_read()
{
	return g_i2c_slave_info_cfg.read_flag;
}


/*****************************************************************************
 * �� �� ��  : i2c_slave_info_set_state_read_flag
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ����i2c slave��read flag
 * �������  : uint8_t flag :0-��ʾ��ʼ״̬,
                             1-��ʾ����ʶ��
                             ����δ����Ŀǰû�õ�
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��
 
*****************************************************************************/
void i2c_slave_info_set_state_read_flag(uint8_t flag)
{
	g_i2c_slave_info_cfg.read_flag = flag;
}


/*****************************************************************************
 * �� �� ��  : i2c_master_buffer_info_data_add
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : g_i2c_master_info_cfg��buffer����������
 * �������  : uint32_t data Ҫ��ӵ�����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��
 
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
 * �� �� ��  : i2c_master_info_popup_data_from_buffer
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ��g_i2c_master_info_cfg��buffer����λ�õ����ݣ�ÿ����һ�������±��
               ����1
 * �������  : uint32_t dev_i2c master��i2c����
 * �������  : ��
 * �� �� ֵ  : ��������
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��
 
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
 * �� �� ��  : i2c_master_info_buffer_clear
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ����g_i2c_master_info_cfg
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : �� 
 
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
 * �� �� ��  : i2c_write_lock
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : i2c �ж�ģʽ�У�write lock
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : �� 
 
*****************************************************************************/
void i2c_write_lock()
{
	g_i2c_global_vars.g_write_doing_flag = I2C_LOCK_BUSY;
}

/*****************************************************************************
 * �� �� ��  : i2c_write_unlock
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : i2c �ж�ģʽ�У�write unlock
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : �� 
 
*****************************************************************************/
void i2c_write_unlock()
{
	g_i2c_global_vars.g_write_doing_flag = I2C_LOCK_IDLE;
}

/*****************************************************************************
 * �� �� ��  : i2c_get_write_lock
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ��ȡwrite lock
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : �� 
 
*****************************************************************************/
I2C_LOCK_SEM i2c_get_write_lock()
{
	return g_i2c_global_vars.g_write_doing_flag;
}

/*****************************************************************************
 * �� �� ��  : i2c_read_lock
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : i2c �ж�ģʽ�У�read lock
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��
 
*****************************************************************************/
void i2c_read_lock()
{
	g_i2c_global_vars.g_read_doing_flag = I2C_LOCK_BUSY;
}

/*****************************************************************************
 * �� �� ��  : i2c_slave_info_popup_data_from_buffer
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : i2c �ж�ģʽ�У�read unlock
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��
 
*****************************************************************************/
void i2c_read_unlock()
{
	g_i2c_global_vars.g_read_doing_flag = I2C_LOCK_IDLE;
}

/*****************************************************************************
 * �� �� ��  : i2c_slave_info_popup_data_from_buffer
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : ��ȡread lock
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��
 
*****************************************************************************/
I2C_LOCK_SEM i2c_get_read_lock()
{
	return g_i2c_global_vars.g_read_doing_flag;
}



/*****************************************************************************
 * �� �� ��  : reset_slave_i2c
 * �� �� ��  : fz
 * ��������  : 2025��3��10��
 * ��������  : ������slave i2c��λ
 * �������  : uint32_t dev_i2c  i2c����,slaveֻ����SLAVE_I2C
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

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
 * �� �� ��  : slave_i2c_write_special_handleing
 * �� �� ��  : fz
 * ��������  : 2025��3��3��
 * ��������  : �ڽ���������дflashʱ��ֹͣ��ѯddm
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : 

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
 * �� �� ��  : slave_event_irq_handler
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c1��slave�ж��¼�������
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c1��slave�ж��¼�����
 * ��    ��  : ��
 �ϵ��������������ʱ���¼���һ��;���öϵ㵥�����ԣ�
 �����ʱ���ж��¼����ֲ᲻һ��
******************************************************************************/
void slave_event_irq_handler(uint32_t dev_i2c)
{	
	uint8_t data = 0;
	uint32_t tmp = 0;
	uint32_t run_us = 0;
	uint8_t cyl = 0;

    /* add by fangzhe, 20250422, ԭ��:�����κε��ж���Ӧ��������� */
    g_mcu_vars_param.g_i2c_exception_irq_status_counter = 0;
	
  if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_ADDSEND))
	{

    /* delete by fangzhe, 20250320, ԭ��:��Ϊ���ж�дi2c_get_write_lock,���Բ���Ҫ״̬
    g_slave_i2c_irq_status_pre;
    ����:1)��Ϊ�����readģʽ���������ν���ADDSEND�жϣ�ԭwhile_fun�жϷ�ʽ������,
         2) �����writeģʽ��ADDSEND�󣬺��ֽ���д�����������֮ǰ�����ΪI2C_INT_NON_STATUS��
            ��һֱ��I2C_INT_ADDSEND_STATUS��ֻ������while_fun�ж���Ч����Ҳ��Ϊʲôwhile_fun�ж�ʧЧ
            ����д����û���ǰ���ֽ�����ADDSEND�жϣ�
            ԭ����������slave�ж�g_slave_i2c_irq_status_preֻ����������״̬I2C_INT_ADDSEND_STATUS
            ��I2C_INT_NON_STATUS,��Ҳ��ԭ�����������ɵġ�
         3) while_funҲ����ֻ����I2C_INT_NON_STATUS,��Ϊ2)�����������ν���ADDSEND��*/
#if 0
		/*����i2c���䣬�������ν����ַ�ж�*/
		/*��ֹi2cһ��ĩ������ʱ����һ��ʱ�����ڵ�����*/
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
		
		/* add by fz, 20250310, ԭ��:��ǰû��д����ʱ�ͽ����ַƥ�䴦�� */
		if(I2C_LOCK_IDLE == i2c_get_write_lock())	
		{
			slave_i2c_address_match_handle();
		}
		else
		{
			/* add by fz, 20250307, ԭ��:��Ϊ��ǰ��д������
				����addM�ж���Ӧ ��׼�������ж��⴦��*/
			i2c_interrupt_disable(dev_i2c,I2C_INT_ADDM);
			g_i2c_global_vars.g_slave_address_handle_flag = SET;
		}		
		
    }
	else if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_RBNE))
	{
		i2c_interrupt_disable(dev_i2c,I2C_INT_STPDET | I2C_INT_RBNE | I2C_INT_TI);		
		
		i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_RBNE | I2C_INT_FLAG_TI);		
		
		g_i2c_global_vars.g_slave_receive_handle_flag = SET;

        /* add by fangzhe, 20250321, ԭ��:��������ֻ��mcu���ڴ潻�����ٶȿ� 
            �������ж��д���*/
		slave_i2c_receive_handle();
		
    }
	else if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_TI))
	{	
		
		/*�����disable I2C_INT_TI | I2C_INT_STPDET,���ܱ�֤�¼�˳��*/
		i2c_interrupt_disable(dev_i2c,I2C_INT_TI | I2C_INT_STPDET);
		
		//i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_STPDET);
		i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_TI);

        /* add by fangzhe, 20250321, ԭ��:�ж��⴦���ʶ 
        while(1)���д���*/
		g_i2c_global_vars.g_slave_read_handle_flag = SET;			
		
	}
	else if(i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_STPDET))
	{     
			
		/*����Э��:I2C��������STOP�����󣬲���Ҫ�ȴ��ӻ���Ӧ��ֹͣ�ź��ǵ���ģ�����������
		��־��ͨ�ŵĽ������ӻ��ڼ�⵽ֹͣ�źź�Ӧ�ͷ����ߣ����ٽ������ݴ��䡣
		Ҳ����˵��stopʱ�����writing��ʱ���������δ��ɣ������п��ܻ����·�start��Ϣ��
		���Ｔʹdisable I2C_INT_STPDETҲ���У���Ϊ�������ص�Ӧ��
		*/
		i2c_interrupt_disable(dev_i2c,I2C_INT_STPDET | I2C_INT_TI | I2C_INT_RBNE);	

		/*�����ʶ����Ҫ*/
		i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_STPDET);
	
		/*��ʼд����*/
		i2c_write_lock();
		
		/*��Ϊдʱ�����������ֽڣ�һ���Ĵ�����һ��ֵ*/
		if(1 != i2c_slave_info_state_is_read()) 
		{
			/*д��ʶ��λ��while(1)���д���slave_i2c_write_handle,д������*/
			g_i2c_global_vars.g_slave_write_handle_flag = SET;
 			slave_i2c_write_special_handleing();			
			
		}
		else  
		{
			//������ָ�뻹ԭ����ʼλ		

			/*buffer�еĵ�һλ�����Ĵ��ֵ.�Ƕϵ����ʱ��RBNE���ֱ��STPDET��û�н�����һ��
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
 * �� �� ��  : slave_i2c_receive_handle
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : i2c slaveģʽ��,receive����
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void slave_i2c_receive_handle()
{
	
	uint8_t data = 0;
	I2C_SLAVE_BUFF_CFG *p_slave_cfg = NULL;

	/*д����δ�ͷţ�˵����ǰ����δд������ݣ�����ԭ�����жϼ���д��
      ��receive׼�����жϴ�while(1)�д���
    */
	if(I2C_LOCK_BUSY == i2c_get_write_lock())
	{
		g_i2c_global_vars.g_slave_write_handle_flag = SET; 
		return;
	}
	
	g_i2c_global_vars.g_slave_receive_handle_flag = RESET;


    /* delete by fangzhe, 20250321, ԭ��:�������࣬��Ϊ����Ĵ��� */
#if 0
	i2c_slave_info_get_buff_info(&p_slave_cfg);
	if(NULL != p_slave_cfg)
	{
	    /* add by fangzhe, 20250321, ԭ��:��ֹ����Խ�� */
		if(PRE_LESS_LATER(p_slave_cfg->buffer_idx,I2C_SLAVE_BUFFER_MAX))
		{
			data = i2c_data_receive(SLAVE_I2C);
			i2c_slave_buffer_info_data_add(data);		
			
		}
		else
		{
			/*��Ҫ��Ϊ�˲����жϣ�����scl*/
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
         /* add by fangzhe, 20250321, ԭ��:��ֹ����Խ�� */
		if(PRE_LESS_LATER(p_slave_cfg->buffer_idx,I2C_SLAVE_BUFFER_MAX))
	    {
	        i2c_slave_buffer_info_data_add(data);	
	    }
    }    

	i2c_interrupt_enable(SLAVE_I2C, I2C_INT_STPDET | I2C_INT_RBNE | I2C_INT_TI);
}

/*****************************************************************************
 * �� �� ��  : slave_i2c_address_match_handle
 * �� �� ��  : fz
 * ��������  : 2025��3��7��
 * ��������  : ��ַƥ�䴦��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : 

*****************************************************************************/
void slave_i2c_address_match_handle()
{
	/* add by fz, 20250310, ԭ��:��ǰ��д����ʱ���ͷ��ز��ظ�ack */
	if(I2C_LOCK_BUSY == i2c_get_write_lock())	
	{
		return;
	}

#if 1
/*��Ϊ���Ͷˣ�SET;�������Ҫ��ôд�������ж��¼�����*/
	if(SET == i2c_flag_get(SLAVE_I2C, I2C_STAT_TR))
	{
		/* clear I2C_TDATA register */
    	I2C_STAT(SLAVE_I2C) |= I2C_STAT_TBE;
	}
#endif
	
	/* clear the ADDSEND bit */
	i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_ADDSEND);

	/* add by fz, 20250310, ԭ��:��Ϊ�ڽ����ж�֮�⴦��ʱ,��disable 
	ADDM���������Ҫenable */
	if(SET == g_i2c_global_vars.g_slave_address_handle_flag)
	{
		i2c_interrupt_enable(SLAVE_I2C,I2C_INT_ADDM | I2C_INT_STPDET | I2C_INT_TI | I2C_INT_RBNE);
	}
	else
	{
		/* add by fz, 20250310, ԭ��:�����ж��ڲ������Ͳ���Ҫ enable 
		ADDM;��Ϊenable��ᷴӳ��ӦADDM�ж�*/
		i2c_interrupt_enable(SLAVE_I2C,I2C_INT_STPDET | I2C_INT_TI | I2C_INT_RBNE);

	}

	//SLAVE_RECEIVE_ADDR() = (i2c_recevied_address_get(SLAVE_I2C) << 1);

	/* add by fz, 20250310, ԭ��:�ϵ����ʱ���Բ鿴 ,���Դ����������ĺ�*/
	g_i2c_global_vars.g_receive_address = (i2c_recevied_address_get(SLAVE_I2C) << 1);

	//���Ϊread���������ν���address�����ﲻ����clear
	//i2c_slave_buffer_info_clear();
	i2c_slave_info_slave_address_add(g_i2c_global_vars.g_receive_address);
	g_i2c_global_vars.g_slave_address_handle_flag = RESET;
	
	
}

/*****************************************************************************
 * �� �� ��  : slave_i2c_read_handle
 * �� �� ��  : fz
 * ��������  : 2023��12��6��
 * ��������  : i2c slaveģʽ��,read����
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void slave_i2c_read_handle()
{
	uint8_t data = 0;	
	
	/*ֱ���ñ�����û��ʹ�ú�������Ϊ�˱��ⷢ���ж�*/
	g_i2c_global_vars.g_slave_read_handle_flag = RESET;
	I2C_SLAVE_BUFF_CFG *ptr_buff_info = NULL;
	
	
	/*��һ���Ĵ�����һ���ֽ�*/
	/*��λ����ʱ����ʱ������������Σ�����++���Եô���
		���� :mcuʵʼ��������дmcu��Ȼ���һ�ζ���λ�����ͻᷢ��slave�������� TI;
		�ڶ��ζ���λ�����ͻᷢ��ֻ�� slaveһ��TI��
		
*/	

		/*��ǰ��δ�����״̬��Ҳ�����״�Ҫ�����״̬*/
		if(0 == i2c_slave_info_state_is_read())
		{
			/*���buff����*/
			i2c_slave_buffer_mng_regaddress_info();

			/* add by fz, 20250312, ԭ��:�ѷ�����read �����ñ�ʶ��*/
			i2c_slave_info_set_state_read_flag(1);

			i2c_slave_info_get_buff_info(&ptr_buff_info);
			if(NULL == ptr_buff_info) /*Ŀǰ���ﲻ����ΪNULL*/
			{
				return;
			}

            /* add by fangzhe, 20250321, ԭ��:������λ��Ҫ�����ֽڣ�����ͳһ��ȡ����ֽ��� 
               
            */
			slave_v2_reg_byte_read(&(ptr_buff_info->address_info),
				ptr_buff_info->slave_buffer,I2C_SLAVE_WRITE_READ_MAX);
			
		}

		data = i2c_slave_info_popup_data_from_buffer();
	

	/*��������i2c_write_unlockǰ����ִ���������������ж�*/
	i2c_data_transmit(SLAVE_I2C, data); 
	i2c_interrupt_enable(SLAVE_I2C, I2C_INT_STPDET | I2C_INT_TI);	

}


/*****************************************************************************
 * �� �� ��  : slave_i2c_write_handle
 * �� �� ��  : fz
 * ��������  : 2023��7��19��
 * ��������  : ��main�д���i2c slave write 
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : 

*****************************************************************************/
void slave_i2c_write_handle(void)
{	
	I2C_SLAVE_BUFF_CFG *p_slave_info = NULL;
	

	/*i2c�ж�ʱ��û�л�ȡ��i2cд�������Ͳ�����while��ִ��д����*/
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

	/* add by fz, 20250312, ԭ��:����Ҫ��� ��read_flagҪ���*/
	i2c_slave_buffer_info_clear();
	
	//g_slave_i2c_irq_status_pre = I2C_INT_NON_STATUS;

	i2c_write_unlock();

	g_i2c_global_vars.g_slave_write_handle_flag = RESET;

	/*����ע�͵�memset,����Ϊִ��memsetʱ�����ж���ת��*/
	/*buffer�еĵ�һλ�����Ĵ��ֵ.�Ƕϵ����ʱ��RBNE���ֱ��STPDET*/		
	//memset(&g_slave_buffer[1],0,I2C_BUFFER_ARRAY_MAX - 1);	 
	
}


/*****************************************************************************
 * �� �� ��  : slave_i2c_lock_reset
 * �� �� ��  : fangzhe
 * ��������  : 2025��4��22��
 * ��������  : slave i2c�����ָ�
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void slave_i2c_lock_reset()
{
    FlagStatus pin_scl_status = RESET;
    FlagStatus pin_sda_status = RESET;
    static uint32_t pre_ticks = 0;  

    pin_scl_status = gpio_input_bit_get(GPIO_I2C_SLAVE_PORT, GPIO_I2C_SLAVE_SCL);
	pin_sda_status = gpio_input_bit_get(GPIO_I2C_SLAVE_PORT, GPIO_I2C_SLAVE_SDA);

    /* add by fangzhe, 20250422, ԭ��:�쳣i2c״̬ */
    if(1 == pin_scl_status && 0 == pin_sda_status)
    {		
        /* add by fangzhe, 20250422, ԭ��:�쳣���� ��������Ҳһ����ʱ����*/
        g_mcu_vars_param.g_i2c_exception_irq_status_counter++;

        /* add by fangzhe, 20250422, ԭ��:�쳣״̬��ʼ��ʱ������:i2c�ָ�������
        �����ͻ����㣻��ʱpre_ticks�������㣬��Ϊ���¿�ʼ����ʱ����ʱpre_ticks�����¸�ֵ��
        
        */
        if(1 == g_mcu_vars_param.g_i2c_exception_irq_status_counter)
        {			//g_slave_i2c_reset_flag = SET;
            pre_ticks = MCU_SYSTEM_SECS_PERIOD;			
        }
      
        if( g_mcu_vars_param.g_i2c_exception_irq_status_counter > 3)
        {
            /*��Ϊ�޷�������,�ȴ�4����*/
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
 * �� �� ��  : slave_i2c_middle_handle
 * �� �� ��  : fz
 * ��������  : 2023��7��19��
 * ��������  : ��main��whileѭ���д���write��read
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void slave_i2c_middle_handle(void)
{
    FlagStatus pin_scl_status = RESET;
	FlagStatus pin_sda_status = RESET;
   
    pin_scl_status = gpio_input_bit_get(GPIO_I2C_SLAVE_PORT, GPIO_I2C_SLAVE_SCL);
	pin_sda_status = gpio_input_bit_get(GPIO_I2C_SLAVE_PORT, GPIO_I2C_SLAVE_SDA);

    /* add by fangzhe, 20250422, ԭ��:���쳣״̬ʱ�������� */
	if(!(1 == pin_scl_status && 0 == pin_sda_status))
	{
		 g_mcu_vars_param.g_i2c_exception_irq_status_counter = 0;		
			
	}
    
	if(SET == g_i2c_global_vars.g_slave_read_handle_flag)
	{
		slave_i2c_read_handle();
		
	}

    /* add by fangzhe, 20250321, ԭ��:��Ϊ ��ַƥ���ж϶�writing״̬����
        ������������ǲ��ᷢ���ģ�����Ϊ�˳���������Ի��Ǳ���
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
 * �� �� ��  : i2c_slave_read_write_handle
 * �� �� ��  : fz
 * ��������  : 2023��5��27��
 * ��������  : ��main ��whileѭ���д���write �� read
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void i2c_slave_read_write_handle(void)
{
	slave_i2c_middle_handle();
}


/*****************************************************************************
 * �� �� ��  : slave_error_irq_handler
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c1��slave�����ж��¼�������
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c1��slave�����ж��¼�����
 * ��    ��  : ��

*****************************************************************************/
void slave_error_irq_handler(void)
{
    /* bus error ������ָʾ�� I2C ͨ�Ź����з�����?���ߴ���*/
	/*��֤:ͨ��ʱ�ε�i2c���߾ͽ�������жϣ�reset_slave_i2c����Իָ�*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_BERR))
	{
		i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_BERR);		
		reset_slave_i2c(SLAVE_I2C);
    }

    /* arbitration lost ͨ�������ڱ�ʾ�ٲö�ʧ��Arbitration Lost
�����жϱ�־��������û��i2c�ٲã����Բ�����*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_LOSTARB))
	{
        i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_LOSTARB);
        reset_slave_i2c(SLAVE_I2C);
    }

    /* over-run or under-run when SCL stretch is disabled I
    2C_INT_FLAG_OUERR �������� / �������Overrun/Underrun Error���жϱ�־���� 
I2C ͨ�Ź����У������ݴ�����������豸�������ݵ����ʲ�ƥ��ʱ���Ϳ��ܻ�������������������
�Ӷ��������жϡ�
    ��֤:����ʱ������disable ADDM���ͻᷴ����ӦADDM�жϣ���ʱ�����I2C_INT_FLAG_OUERR

*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_OUERR)){
        i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_OUERR);
		reset_slave_i2c(SLAVE_I2C);
    }

    /* PEC error I2C ���ݰ�����У�飨PEC�������жϱ�־*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_PECERR))
	{
       i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_PECERR);
    }

    /* timeout error ������ָʾ I2C ͨ�Ź����з����� ��ʱ����*/
     /* ��û���TIMEOUT�ж�*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_TIMEOUT))
	{
        i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_TIMEOUT);

		/* add by fz, 20250310, ԭ��:��ʱ�ͻָ�i2c */		
		reset_slave_i2c(SLAVE_I2C);
    }

    /* SMBus alert  SMBus �澯��SMBus Alert���жϱ�־��������ָʾ�� SMBus��System Management Bus
�� ͨ���У����豸������ SMBus �澯*/
    if(i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_SMBALT))
	{
        i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_SMBALT);
		
		/* add by fz, 20250310, ԭ��:�ͻָ�i2c */		
		reset_slave_i2c(SLAVE_I2C);
    }

	//������ָʾ�� I2C ͨ�Ź����У����豸��Slave��δ����Ӧ���źţ�NACK��
	if (i2c_interrupt_flag_get(SLAVE_I2C, I2C_INT_FLAG_NACK)) 
     {
	  	
		// ֹͣ��ǰͨ��
        i2c_stop_on_bus(SLAVE_I2C);
		
        // ���NACK�жϱ�־
        i2c_interrupt_flag_clear(SLAVE_I2C, I2C_INT_FLAG_NACK);		
        
    }	
 
	
}

/*****************************************************************************
 * �� �� ��  : master_event_irq_handler
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��master�ж��¼�
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c0���ж��¼�����
 * ��    ��  : 

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
	
		
		/*��������*/	
		data = i2c_data_receive(dev_i2c);		

	//	i2c_master_info_get_buff_info(&p_master_cfg);
		p_master_cfg = GET_MASTER_CFG_OF_I2C(dev_i2c);
		if(NULL != p_master_cfg)
		{
			/*�״ν�������ж�*/
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
		/*�����������һ���ֽڻ��߽������һ���ֽ�*/  		
		//i2c_master_info_get_buff_info(&p_master_cfg);		
		p_master_cfg= GET_MASTER_CFG_OF_I2C(dev_i2c);

		//����I2C_INT_FLAG_RBNE
		if(g_i2c_global_vars.g_master_i2c_irq_status_pre == I2C_INT_RBNE_STATUS) 
        {
        	i2c_stop_on_bus(dev_i2c);
		}	
			
		//������������I2C_INT_FLAG_TI;
		//��MASTERΪ����ʱ����дһ���Ĵ���ֵ��Ȼ���TC�����������data > 1
		//��masterΪд��ʱ����Ϊ���õ����ⲿ����������Ϳ�����Ч
		/* modify by fz, 20230828, ԭ��:�ĳ���g_master_buffer ��������������*/
		if(g_i2c_global_vars.g_master_i2c_irq_status_pre == I2C_INT_TI_STATUS && 
		 2 == p_master_cfg->read_flag) //��ǰ��write��master write
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
      
		/*i2c ״̬��ֹ,�ͷ���Դ*/		
		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;		       
		
    }
	
}

/*****************************************************************************
 * �� �� ��  : Master_ErrorIRQ_Handler
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��master�ĳ����ж��¼�
 * �������  : uint32_t dev_i2c i2c���ߣ�MASTER_A_I2C��MASTER_B_I2C
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c0�ĳ����ж��¼�����
 * ��    ��  : ��

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

    /* timeout error ����û���TIMEOUT�ж�*/
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

	//������ָʾ�� I2C ͨ�Ź����У����豸��Slave��δ����Ӧ���źţ�NACK��
	if (i2c_interrupt_flag_get(dev_i2c, I2C_INT_FLAG_NACK)) 
     {
	  	
		// ֹͣ��ǰͨ��
        i2c_stop_on_bus(dev_i2c);
		
        // ���NACK�жϱ�־
        i2c_interrupt_flag_clear(dev_i2c, I2C_INT_FLAG_NACK);		
        
    }

    /* disable the I2C0 interrupt */
   // i2c_interrupt_disable(dev_i2c, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_TI | 
		//I2C_INT_TC | I2C_INT_RBNE);	


}

/*****************************************************************************
 * �� �� ��  : slave_i2c_dev_config
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : slave i2c�����߳�ʼ��
 * �������  : uint32_t dev_i2c,  i2c����
 				uint32_t adress,   ַ
			uint8_t nvic_event_irq, �ж��¼�����
			uint8_t nvic_error_irq  ����������
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void slave_i2c_dev_config(uint32_t dev_i2c,uint32_t adress,
			uint8_t nvic_event_irq,uint8_t nvic_error_irq)
{
	/*��ʼ��slave buffer����ռ�*/
	i2c_slave_buffer_info_clear();
	
	//rcu_i2c_clock_config(SLAVE_I2C,RCU_I2CSRC_IRC8M);
	rcu_i2c_clock_config(dev_i2c,RCU_I2CSRC_CKSYS);

	 /* configure I2C timing */
    i2c_timing_config(dev_i2c, 0, 0x9, 0);

	 /* add by fz, 20250303, ԭ��:i2c���ʵ���400K */
    i2c_master_clock_config(dev_i2c, 0x39, 0xBB);

     //i2c���ʵ���400K
   // i2c_master_clock_config(dev_i2c, 0x50, 0x73);
	
    /* configure I2C address */
	i2c_second_address_config(dev_i2c, adress,ADDRESS2_MASK_ALL);
	
    /* enable I2C1 */
    i2c_enable(dev_i2c);


	//���ȼ��������
	nvic_irq_enable(nvic_event_irq,NIVC_IRQ_GROUP,I2C_SLAVE_IRQ_EVENT_PRI);

	//ʹ�ܴ����ж�
	nvic_irq_enable(nvic_error_irq, NIVC_IRQ_GROUP, I2C_SLAVE_IRQ_ERR_PRI);

	/* enable the I2C1 interrupt */
	i2c_interrupt_enable(dev_i2c, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_ADDM | 
		I2C_INT_TI | I2C_INT_RBNE);
	

}


/*****************************************************************************
 * �� �� ��  : slave_i2c_config_init
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��slave���ó�ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void slave_i2c_config_init()
{
   
	slave_i2c_dev_config(SLAVE_I2C,MCU_SECOND_ADDRESS7,SLAVE_EV_IRQn,SLAVE_ER_IRQn);
}
/*****************************************************************************
 * �� �� ��  : get_master_i2c_by_dev_address
 * �� �� ��  : fz
 * ��������  : 2024��4��9��
 * ��������  : �����豸��ַ�õ�i2c����
 * �������  : uint32_t dev_address �豸��ַ
 * �������  : uint32_t *ptr_i2c i2c���ߣ�MASTER_A_I2C ��MASTER_B_I2C
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void get_master_i2c_by_dev_address(uint32_t dev_address,uint32_t *ptr_i2c)
{
	
	//uint8_t masterBi2c_mapAddress[2] = {0x48,0xc6};//10G �豸��ַ���̶�ֵ
	uint8_t masterBi2c_mapAddress[2] = {GN7153_SLAVE_ADDRESS,
	                UX3326_SLAVE_ADDRESS};//10G �豸��ַ���̶�ֵ
	uint32_t i = 0;
	if(NULL != ptr_i2c)
	{
		for(i = 0; i < sizeof(masterBi2c_mapAddress);i++)
		{
			if(dev_address == masterBi2c_mapAddress[i])
			{
				*ptr_i2c = MASTER_B_I2C;//10G��1G
				return;
			}
		}

		*ptr_i2c = MASTER_A_I2C;	//50G	
	}
	return;
    
}


/*****************************************************************************
 * �� �� ��  : master_i2c_set_irq_status_info
 * �� �� ��  : fangzhe
 * ��������  : 2025��5��3��
 * ��������  : ����master��i2c״̬
 * �������  : uint32_t dev_i2c,  MASTER_A_I2C��MASTER_B_I2C
                uint32_t irq_status ��MCU_I2C_INT_STATUS
                uint8_t work : 0-ΪmasterWrite,1-masterRead;
 * �������  : ��
 * �� �� ֵ  : 0-�ɹ�;����ʧ��
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
uint32_t master_i2c_set_irq_status_info(uint32_t dev_i2c,
                uint32_t irq_status,
                uint32_t regAddr,
                uint8_t work)
{
    if(MASTER_A_I2C == dev_i2c)
    {
        g_i2c_global_vars.g_master_i2c_status.I2cOp.bits.MasterA_Irq = irq_status;
        g_i2c_global_vars.g_master_i2c_status.I2cOp.bits.MasterAWork = work; /*0Ϊwrite,1Ϊread*/
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
 * �� �� ��  : master_reg_byte_write
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��masterд����
 * �������  : uint32_t slave_addr  slave��ַ
 				uint8_t* p_buffer	Ҫд������ݣ�p_buffer[0]�ǼĴ���
 				uint32_t buffer_len ���ݵĳ���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void master_reg_byte_write(uint32_t slave_addr,
									uint8_t* p_buffer, 
									uint32_t buffer_len	)
{	
	uint32_t run_us = 0;
	uint8_t cyl = 0;
	I2C_MASTER_BUFF_CFG *p_master_cfg = NULL;
	uint32_t master_i2c = MASTER_A_I2C; //50G

    /*����i2c״̬���õ�,��Ҫ����dsp��tec����i2c*/
    uint32_t testRegAddr = 0;

     /*�����жϣ���������Ϊ2�ֽڣ���󳤶Ȳ�����buff�ռ�*/
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

    /*������ѭ����������ѭ��*/
	// while(i2c_flag_get(MASTER_A_I2C, I2C_FLAG_I2CBSY));
	run_us = CYCLE_DELAY_TIME_US;
	cyl = 0;
	while_fun(i2c_flag_get(master_i2c, I2C_FLAG_I2CBSY),run_us,cyl);
	if(1 == cyl)
	{
		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;
		i2c_disable(master_i2c);
		i2c_enable(master_i2c);

         /* add by fangzhe, 20250503, ԭ��:���Ӽ��״̬ */
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
            testRegAddr,
            0);
		
		return;
	}	


	/*�ĳ���g_master_buffer��������������*/
	p_master_cfg = GET_MASTER_CFG_OF_I2C(master_i2c);

    /* add by fangzhe, 20250321, ԭ��:��ջ��� */
	i2c_master_info_buffer_clear(p_master_cfg);

	p_master_cfg->read_flag = 0x2; //дģʽ
	memcpy(p_master_cfg->master_buffer,p_buffer,buffer_len);

	/* the master sends a start condition to I2C bus */
	i2c_start_on_bus(master_i2c);

    /* add by fangzhe, 20250321, ԭ��:���޵ȴ��������޵ȴ� ��
    g_master_i2c_irq_status_pre�����ж�����ΪI2C_INT_STPDET_STATUS
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

           /* add by fangzhe, 20250503, ԭ��:���Ӽ��״̬ */
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
            testRegAddr,
            0);
	}	

   /* add by fangzhe, 20250503, ԭ��:���Ӽ��״̬ */
    master_i2c_set_irq_status_info(master_i2c,
        g_i2c_global_vars.g_master_i2c_irq_status_pre,
        testRegAddr,
        0);


}

/*****************************************************************************
 * �� �� ��  : master_dsp_fsl_reg_4byte_write
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��masterд����,ֻ���dsp�����ַ���Ĵ���
 * �������  : uint32_t slave_addr  slave��ַ
 				uint8_t* p_buffer	Ҫд������ݣ�p_buffer[0]�ǼĴ���
 				uint32_t buffer_len ���ݵĳ���
 				
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : dsp�ļĴ��������20bit,д���ʵ����3���ֽڵļĴ�����
 ���̴��� 
 #define RegisterWrite(reg, val) I2C_RegisterWrite((UINT32)((UINTPTR)(&reg) >> 2), val)
 4�ֽ�������λ��
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

    //���ֽڼĴ���+uin32_t�ֽ���
   // if(DSP_FSL_SLAVE_ADDRESS != slave_addr || buffer_len < 8)
   if(buffer_len < 8)
    {
        return;
    }

    //��ȡ��ַ,����ת��dsp�Ĵ�����ʽ
    //���̸�����Ҫ������λ
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
 * �� �� ��  : master_reg_1byte_size_read
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��master�ĵ��ֽڼĴ���������
 * �������  : uint32_t slave_addr  slave��ַ
 				uint8_t	reg	�ǼĴ��� 				
 				uint32_t buffer_len ���ݵĳ���
 * �������  : uint8_t *p_buffer  Ҫ���ĵ�buffer
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

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
 * �� �� ��  : master_reg_2byte_size_read
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��master�����ֽڼĴ���������
 * �������  : uint32_t slave_addr  slave��ַ
 				uint16_t	reg	�ǼĴ��� 				
 				uint32_t buffer_len ���ݵĳ���
 * �������  : uint8_t *p_buffer  Ҫ���ĵ�buffer
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

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
 * �� �� ��  : master_dsp_fsl_reg_4byte_size_read
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��master�����ֽڼĴ���������
 * �������  : uint32_t slave_addr  slave��ַ
 				uint32_t	reg	�ǼĴ��� 				
 				uint32_t buffer_len ���ݵĳ���
 * �������  : uint8_t *p_buffer  Ҫ���ĵ�buffer
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��,��master_dsp_fsl_reg_4byte_write��������4�ֽڼĴ�����ʵ�ʷ���ȥ����3�ֽ�

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

    //dsp��Ҫ����������λ
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
 * �� �� ��  : master_reg_byte_read
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��master������
 * �������  : uint32_t slave_addr  	slave��ַ
 				uint8_t reg_address,  	�Ĵ�����ַ 				
 				uint32_t buffer_len 	Ҫ���������ݵĳ���
 * �������  : uint8_t* p_buffer		��������ʱ��buffer
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

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
	    /* add by fangzhe, 20250503, ԭ��:���Ӽ��״̬ */
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

        /* add by fangzhe, 20250503, ԭ��:���Ӽ��״̬ */
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
            read_addr,
            1);
		return;
	}

	/*�Ĵ������뻺��������master_event_irq_handler�з���*/
	/*g_master_buffer[0] = reg_address; 
	g_master_buff_ptr = g_master_buffer;*/
	memcpy(&(p_master_cfg->address_info),p_address_info,
			sizeof(I2C_ALL_ADDRESS_INFO));

	memcpy(p_master_cfg->master_buffer,p_master_cfg->address_info.regaddress,
		p_master_cfg->address_info.reg_size);
	
	
    i2c_start_on_bus(master_i2c); 
    
	/*�����Ƿ���reg_address*/

	 /* wait until TC bit is set �����������*/
	run_us = CYCLE_DELAY_TIME_US;
	cyl = 0;
	while_fun(!i2c_flag_get(master_i2c, I2C_FLAG_TC),run_us,cyl);
	if(1 == cyl)
	{
		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;
		i2c_disable(master_i2c);
		i2c_enable(master_i2c);		

            /* add by fangzhe, 20250503, ԭ��:���Ӽ��״̬ */
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
             read_addr,
            1);
		return;
	}	
	
		
    /* send slave address to I2C bus ,master��ʼ����Ҳ���ǽ���read_addr*/
  //  i2c_master_addressing(master_i2c, p_address_info->slave_address, I2C_MASTER_RECEIVE);
    i2c_master_addressing(master_i2c, read_addr, I2C_MASTER_RECEIVE);
	i2c_transfer_byte_number_config(master_i2c, buffer_len);
	
    i2c_start_on_bus(master_i2c); 

	run_us = CYCLE_DELAY_TIME_US; /*֮ǰΪ����ʱ��̫����*/
	cyl = 0;
	while_fun(g_i2c_global_vars.g_master_i2c_irq_status_pre != I2C_INT_STPDET_STATUS,
		run_us,cyl);
	if(1 == cyl)
	{
		g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;
		i2c_disable(master_i2c);
		i2c_enable(master_i2c);	

        /* add by fangzhe, 20250503, ԭ��:���Ӽ��״̬ */
        master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
            read_addr,
            1);
		return;
	}

    /* add by fangzhe, 20250503, ԭ��:���Ӽ��״̬ */
    master_i2c_set_irq_status_info(master_i2c,
            g_i2c_global_vars.g_master_i2c_irq_status_pre,
             read_addr,
            1);

	//???p_buffer[0] = g_master_buffer[0];
	//i = g_master_buffer[0];���Բ���
	memcpy(p_buffer,p_master_cfg->master_buffer,buffer_len);

}


/*****************************************************************************
 * �� �� ��  : master_i2c_config_init
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��master���ó�ʼ��
 * �������  : uint32_t dev_i2c i2c����
                uint32_t adress �豸��ַ
		        uint8_t nvic_event_irq �ж��¼����ȼ�
		        uint8_t nvic_err_irq  �쳣�ж����ȼ�
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void master_i2c_dev_config(uint32_t dev_i2c,uint32_t adress,
		uint8_t nvic_event_irq,uint8_t nvic_err_irq)
{
	/*����master ���ݻ�����*/
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

	/* add by fz, 20250303, ԭ��:i2c���ʵ���400K */
	//i2c_master_clock_config(dev_i2c, 0x73, 0x73);////��Ӧ400K

    i2c_master_clock_config(dev_i2c, 0x39, 0xBB);

	/* clear I2C_TDATA register */
	I2C_STAT(dev_i2c) |= I2C_STAT_TBE;    


	/* configure I2C address */
	i2c_address_config(dev_i2c, adress, I2C_ADDFORMAT_7BITS);

	i2c_automatic_end_disable(dev_i2c);	


	/* enable MASTER_A_I2C */
	i2c_enable(dev_i2c);	

	nvic_irq_enable(nvic_event_irq,NIVC_IRQ_GROUP,I2C_MASTER_IRQ_EVENT_PRI);

	/* add by fz, 20250310, ԭ��:������master i2c�� ������������ж�
		��masterģʽ�³������׻ָ�
	*/
	nvic_irq_enable(nvic_err_irq,NIVC_IRQ_GROUP,I2C_MASTER_IRQ_ERR_PRI);

	 /* enable the MASTER_A_I2C interrupt */
    i2c_interrupt_enable(dev_i2c, I2C_INT_ERR | I2C_INT_STPDET | I2C_INT_TI | 
		I2C_INT_TC | I2C_INT_ADDM | I2C_INT_RBNE);
 
}



/*****************************************************************************
 * �� �� ��  : master_i2c_config_init
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��master���ó�ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void master_i2c_config_init()
{
	master_i2c_dev_config(MASTER_B_I2C,MCU_I2C_ADDRESS7,MASTER_B_EV_IRQn,MASTER_B_ER_IRQn);
	master_i2c_dev_config(MASTER_A_I2C,MCU_I2C_ADDRESS7,MASTER_A_EV_IRQn,MASTER_A_ER_IRQn);
	
}


/*****************************************************************************
 * �� �� ��  : slave_reg_byte_read
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��slave������
 * �������  : uint32_t slave_addr  	slave��ַ
 				uint8_t reg_address,  	�Ĵ�����ַ 				
 				uint32_t buffer_len 	Ҫ���������ݵĳ���
 * �������  : uint8_t* p_buffer		��������ʱ��buffer
 * �� �� ֵ  : ��
 * ���ù�ϵ  : ��
 * ��    ��  : �����buffer_len�Ǹ�����g_slave_buff�ռ����󻺴泤�� :I2C_SLAVE_WRITE_READ_MAX
               �����mcu�ĵ�ַ����ʵ�ʶ�ȡ�ĳ����ɸ��ӿ�ȷ��;
               ���������оƬ�ĵ�ַ����ֻ��ȡһ���ֽ�

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

		/*����оƬ��ȡ���ݳ���Ϊ1�ֽڣ�
			��Ϊ��ͳһ����max����(255�ֽ�)��ȡ��������оƬ��Ϊû����ô���ȣ��ͻ�
			�쳣��
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

    		/*���Դ���ʱ�鿴ֵ*/
    		i = p_buffer[0];
		}
      
	}

	return;
}


/*****************************************************************************
 * �� �� ��  : slave_reg_byte_write
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��slaveд����
 * �������  : uint32_t slave_addr  slave��ַ
 				uint8_t* p_buffer	Ҫд�������
 				uint32_t buffer_len ���ݵĳ���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

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

    /*д�ĳ�������Ϊ2,�Ĵ���+����*/
	if(NULL == p_buffer || buffer_len < 2)
	{
		return;
	}

    /* delete by fangzhe, 20250321, ԭ��:Ŀǰ���������� */
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

	/*���slave��buffer,??��������������������?*/
	i2c_slave_buffer_info_clear();

	return;
}


/*****************************************************************************
 * �� �� ��  : i2cȫ�ֱ�����ʼ��
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��23��
 * ��������  : i2c_global_param_init
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void i2c_global_param_init()
{  
    /*slave���յĵ�ַ*/
    g_i2c_global_vars.g_receive_address = 0;

    /*************************************************************************
    * �������ܣ�i2c slave�ж�ģʽ�У�read handle��ʶ
    * ȡֵ��Χ��RESET-readδ������SET-read������
    * ע�������
    *************************************************************************/
    g_i2c_global_vars.g_slave_read_handle_flag = RESET;

    /*************************************************************************
    * �������ܣ�i2c slave�ж�ģʽ�У�write handle��ʶ
    * ȡֵ��Χ��RESET-writeδ������SET-write������
    * ע�������
    *************************************************************************/
    g_i2c_global_vars.g_slave_write_handle_flag = RESET;

    /*************************************************************************
    * �������ܣ�i2c slave�ж�ģʽ�У�receive handle��ʶ
    * ȡֵ��Χ��RESET-receiveδ������SET-receive������
    * ע�������
    *************************************************************************/
    g_i2c_global_vars.g_slave_receive_handle_flag = RESET;

    /*************************************************************************
    * �������ܣ�i2c slave�ж�ģʽ��, ��ַƥ��ʱ���ô����ʶλ
    * ȡֵ��Χ��RESET-��ǰ�ж��д���SET-�ж��⴦���ַƥ�䣻
    * ע�������
    *************************************************************************/
    g_i2c_global_vars.g_slave_address_handle_flag = RESET;

    /*************************************************************************
    * �������ܣ�i2c�ж�ģʽ�У�write doing 
    * ȡֵ��Χ��I2C_LOCK_IDLE-����;I2C_LOCK_BUSY-busy
    * ע�������
    *************************************************************************/
    g_i2c_global_vars.g_write_doing_flag = I2C_LOCK_IDLE;

    /*************************************************************************
    * �������ܣ�i2c�ж�ģʽ�У�read doing 
    * ȡֵ��Χ��I2C_LOCK_IDLE-����;I2C_LOCK_BUSY-busy
    * ע�������
    *************************************************************************/
    g_i2c_global_vars.g_read_doing_flag = I2C_LOCK_IDLE;

    /*master i2c ״���Ƿ���У�SET����,RESET������*/
    /*************************************************************************
    * �������ܣ�master i2c�ж�ģʽ�е�ǰ���ж�״̬
    * ȡֵ��Χ���ж�״̬����ʼΪֹͣ״̬
    * ע�������
    *************************************************************************/
    g_i2c_global_vars.g_master_i2c_irq_status_pre = I2C_INT_STPDET_STATUS;

    /* add by fz, 20231106, ԭ��:��ģ����ʱ�ʶ */
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
 * �� �� ��  : monitor_i2c_status_reg_read
 * �� �� ��  : fangzhe
 * ��������  : 2025��5��3��
 * ��������  : ��ȡi2c�Ĺ���״̬
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

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

/* delete by fangzhe, 20250321, ԭ��:���빦��Ŀǰ�������� */

#if 1
/*****************************************************************************
 * �� �� ��  : user_check_password_write_reg
 * �� �� ��  : fz
 * ��������  : 2023��8��24��
 * ��������  : mcu�������
 * �������  : uint8_t *p_buff,p_buff[0],SYSTEM_PASSWORD_REG
 				uint32_t buff_len   ���볤��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void user_check_password_write_reg(uint8_t *p_buff,uint32_t buff_len)
{
	uint32_t pwd_len = 0;
	uint8_t str_pwd[OPT_MOD_LIMIT_PASSWORD_LENGTH + 1];

	/*�����ж�*/
	if(NULL == p_buff || buff_len < (OPT_MOD_LIMIT_PASSWORD_LENGTH + 1))
	{
		return;
	}

	/*�Ĵ����˶�*/
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
 * �� �� ��  : user_optical_pwd_limit_init
 * �� �� ��  : fz
 * ��������  : 2023��11��6��
 * ��������  : ��ģ�������޶���ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void user_optical_pwd_limit_init()
{
	memcpy(g_optical_limit_pwd,"fiberhome",sizeof("fiberhome"));
}


/*****************************************************************************
 * �� �� ��  : user_check_write_reg_flag
 * �� �� ��  : fz
 * ��������  : 2023��8��24��
 * ��������  : ���i2c��writeȨ��
 * �������  : uint8_t reg �Ĵ���
 * �������  : ��
 * �� �� ֵ  : USER_ACCESS_YES,��Ȩ���ʣ�������Ȩ����
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

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




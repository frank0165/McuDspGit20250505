/***********************************************************************************

 * �� �� ��   : i2c_opt_IE.h
 * �� �� ��   : fz
 * ��������   : 2023��5��15��
 * �ļ�����   : i2c����master��slave
 * ��Ȩ˵��   : Copyright (C) 2000-2023   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

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
void master_i2c_event_irq_handler(uint32_t dev_i2c);

/*****************************************************************************
 * �� �� ��  : master_i2c_error_irq_handler
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��master�ĳ����ж��¼�
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c0�ĳ����ж��¼�����
 * ��    ��  : ��

*****************************************************************************/
void master_i2c_error_irq_handler(uint32_t dev_i2c);



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

*****************************************************************************/
//void Slave_EventIRQ_Handler(void);
void slave_event_irq_handler(uint32_t dev_i2c);

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
void slave_error_irq_handler(void);


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
void i2c_slave_read_write_handle();

/*****************************************************************************
 * �� �� ��  : master_reg_byte_write
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : i2c��masterд����
 * �������  : uint32_t slave_addr  slave��ַ
 				uint8_t* p_buffer	Ҫд�������
 				uint32_t buffer_len ���ݵĳ���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void master_reg_byte_write(uint32_t slave_addr,
									uint8_t* p_buffer, 
									uint32_t buffer_len	);

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
									uint32_t buffer_len	);

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
							uint32_t buffer_len	);

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
	uint32_t buffer_len);

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
	uint32_t buffer_len);


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
	uint32_t buffer_len);


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
 * ��    ��  : �����buffer_len�Ǹ�����g_slave_buff�ռ����󻺴泤��
               �����mcu�ĵ�ַ����ʵ�ʶ�ȡ�ĳ����ɸ��ӿ�ȷ��;
               ���������оƬ�ĵ�ַ����ֻ��ȡһ���ֽ�

*****************************************************************************/
void slave_v2_reg_byte_read(I2C_ALL_ADDRESS_INFO *p_slave_info,
							uint8_t* p_buffer, 
							uint32_t buffer_len);
							


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
									uint32_t buffer_len	);

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
void master_i2c_config_init();


/*****************************************************************************
 * �� �� ��  : slave_i2c_middle_handle
 * �� �� ��  : fz
 * ��������  : 2023��7��19��
 * ��������  : ��main��whileѭ���д���write��read
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : 

*****************************************************************************/
void slave_i2c_middle_handle(void);


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
void slave_i2c_config_init();


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
void user_check_password_write_reg(uint8_t *p_buff,uint32_t buff_len);

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
void user_optical_pwd_limit_init();

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
uint8_t user_check_write_reg_flag(uint8_t reg);


/*****************************************************************************
 * �� �� ��  : fz
 * ��������  : 2024��4��9��
 * ��������  : �����豸��ַ�õ�i2c����
 * �������  : uint32_t dev_address �豸��ַ
 * �������  : uint32_t *ptr_i2c i2c���ߣ�MASTER_A_I2C ��MASTER_B_I2C
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2cЭ��ջ�ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void get_master_i2c_by_dev_address(uint32_t dev_address,uint32_t *ptr_i2c);



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
void i2c_slave_buffer_info_clear();


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
void i2c_master_info_buffer_clear(I2C_MASTER_BUFF_CFG *ptr_buff);

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
	slave_address,I2C_READ_CFG_CALLBACK read_callback);

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
			slave_address,I2C_WRITE_CFG_CALLBACK write_callback);


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
//void i2c_global_param_init();

/*****************************************************************************
 * �� �� ��  : master_i2c_set_irq_status_info
 * �� �� ��  : fangzhe
 * ��������  : 2025��5��3��
 * ��������  : ����master��i2c״̬
 * �������  : uint32_t dev_i2c,  MASTER_A_I2C��MASTER_B_I2C
                uint32_t irq_status ��MCU_I2C_INT_STATUS
 * �������  : ��
 * �� �� ֵ  : 0-�ɹ�;����ʧ��
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
uint32_t master_i2c_set_irq_status_info(uint32_t dev_i2c,
        uint32_t irq_status,
        uint32_t regAddr,
        uint8_t work);


 void test_i2c_restart_reg_write(uint8_t *pbuff,uint32_t bufflen);

#endif /* I2C_IE_H */

/***********************************************************************************

 * �� �� ��   : ddm_sff_i2c_interface.h
 * �� �� ��   : fz
 * ��������   : 2025��1��15��
 * �ļ�����   : sff_8472��i2c�ӿ�
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#ifndef _DDM_SFF_I2C_INTERFACE_H_
#define _DDM_SFF_I2C_INTERFACE_H_
#include "gd32e501_it.h"
#include "mcu_data_type.h"


/*****************************************************************************
 * �� �� ��  : om_flash_write_reg_byte
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��21��
 * ��������  : д��flash
 * �������  : uint32_t slave_addr, ���õ�ַ,A0,B0,C0;A2,B2,C2
             uint8_t *p_buff, Ҫд������,��һ���ֽ��ǼĴ���
                uint32_t buff_len p_buff�ĳ���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : 

*****************************************************************************/
void om_flash_write_reg_byte(uint32_t slave_addr,uint8_t *p_buff,uint32_t buff_len);

/*****************************************************************************
 * �� �� ��  : om_memory_state_ctrl_write_reg_byte
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��21��
 * ��������  : д״̬����ʱ�ڴ�
 * �������  :  uint32_t slave_addr, ���õ�ַ,A0,B0,C0;A2,B2,C2
             uint8_t *p_buff, Ҫд������,��һ���ֽ��ǼĴ���
                uint32_t buff_len p_buff�ĳ���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��λ������ʹ��

*****************************************************************************/
void om_memory_state_ctrl_write_reg_byte(uint32_t slave_addr,uint8_t *p_buff,uint32_t buff_len);

/*****************************************************************************
 * �� �� ��  : om_v2_flash_read_reg_byte
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��21��
 * ��������  : ��flash���ж�ȡflash--�Ա���ʽ����
 * �������  : I2C_ALL_ADDRESS_INFO *p_address_info  ��ַ���Ĵ���Ϣ
                uint32_t buff_len p_buff�ĳ���:I2C_SLAVE_WRITE_READ_MAX
 * �������  : p_buff ʵ�ʱ������
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void om_v2_flash_read_reg_byte(I2C_ALL_ADDRESS_INFO *p_address_info,uint8_t *p_buff,uint32_t 
							buff_len);


/***********************************************************************
	** �� �� ���� om_memory_read_reg_byte
	** ��    �룺I2C_ALL_ADDRESS_INFO *p_address_info ��ַ��Ϣ
				uint32_t buff_len p_buff�ĳ���							
								
	** ��    ���� uint8_t *p_buff ���ڴ��ж�ȡa0,b0,c0,a2,b2,c2
	** �� �� ֵ�� ��
	** ���������� ����Ĵ�����ֵ��ȡ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void om_v2_memory_read_reg_byte(I2C_ALL_ADDRESS_INFO *p_address_info,
													uint8_t *p_buff,
													uint32_t buff_len);

/***********************************************************************
	** �� �� ���� om_cmd_ddm_read_reg_byte
	** ��    �룺 uint8_t regaddr �Ĵ����׵�ַ
				  uint8_t *p_buff �����ַ
				  uint32_t buff_len ƫ���� 
	** ��    ���� ��
	** �� �� ֵ�� ��
	** ���������� ddm����������Ĵ�����ֵ��ȡ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void om_cmd_ddm_read_reg_byte(uint8_t regaddr, uint8_t *pbuff, uint32_t 
											bufflen);

/***********************************************************************
	** �� �� ���� om_save_data_config_flash_write
	** ��    �룺 uint8_t *pbuff �Ĵ�������
								uint32_t bufflen �ֽڳ���
	** ��    ���� ��
	** �� �� ֵ�� ��
	** ���������� �����ն�deemphֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void om_save_data_config_flash_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * �� �� ��  : om_erase_data_config_flash_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : ���flash����
 * �������  : uint8_t *pbuff �Ĵ�������
			uint32_t bufflen �ֽڳ���
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void om_erase_data_config_flash_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * �� �� ��  : cfg_v2_flash_read_reg_byte
 * �� �� ��  : fz
 * ��������  : 2025��1��3��
 * ��������  : mcu��slave�������ַ:0xA8�Ķ����ܣ����ڶ�ȡ���������
 * �������  : uint32_t slave_addr  slave��ַ.
 				uint8_t regaddress  �Ĵ���ֵ 				
 				uint32_t buffer_len ���ݵĳ���
 * �������  : uint8_t* p_buffer	��ȡ������
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ������ֻ�����豸��ַ 0xA8���������豸��ַ������

*****************************************************************************/
void cfg_v2_flash_read_reg_byte(I2C_ALL_ADDRESS_INFO *p_address_info,
		uint8_t *p_buff,uint32_t buff_len);

/*****************************************************************************
 * �� �� ��  : cmd_common_reg_read
 * �� �� ��  : fz
 * ��������  : 2024��10��12��
 * ��������  : ͨ�ö�����
 * �������  : uint8_t regaddr �Ĵ���
 				uint32_t bufflen pbuff�ĳ���
 * �������  : uint8_t *pbuff ʵ�ʵ�flash�����ó���
 * �� �� ֵ  : ��
 * ���ù�ϵ  : 
 * ��    ��  : CMD_COMMON_READ_REG = 0x27,

*****************************************************************************/
void cmd_common_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen);


#endif


/***********************************************************************************

 * �� �� ��   : update_comm.h
 * �� �� ��   : fz
 * ��������   : 2023��8��16��
 * �ļ�����   : ��������
 * ��Ȩ˵��   : Copyright (C) 2000-2023   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : ����mcu����������
 * �޸���־   : 

***********************************************************************************/


#ifndef _UPDATE_COMM_H_
#define _UPDATE_COMM_H_

#include "gd32e501.h"
#include <stdio.h>
#include <stdlib.h>

/* add by fz, 20230828, ԭ��:mcuдflashʱҪ8�ı��� */
#define DIV_MOD_VALUE			8
#define DOUBLE_WORLD_LEN		8

extern uint32_t g_page_idx;
extern uint32_t g_pkt_count_to_flash;
extern uint32_t g_pkt_rx;
extern uint8_t update_flag;
extern uint8_t *g_update_mem_ptr;
extern uint32_t g_update_mem_idx;

/*****************************************************************************
 * �� �� ��  : update_mem_malloc
 * �� �� ��  : fz
 * ��������  : 2023��8��28��
 * ��������  : ����ʱ����һ���ѿռ�
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
ErrStatus update_mem_malloc();

/*****************************************************************************
 * �� �� ��  : upate_mem_is_alloc
 * �� �� ��  : fz
 * ��������  : 2023��8��28��
 * ��������  : �Ƿ����ѿռ�ɹ�
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ERROR=0;����SUCCESS
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : 

*****************************************************************************/
ErrStatus upate_mem_is_alloc();

/*****************************************************************************
 * �� �� ��  : update_mem_all_memset
 * �� �� ��  : fz
 * ��������  : 2023��8��28��
 * ��������  : �ѿռ�����
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : 

*****************************************************************************/
void update_mem_all_memset();

/*****************************************************************************
 * �� �� ��  : read_update_flag
 * �� �� ��  : gqhuan
 * ��������  : 2023��8��30��
 * ��������  : ���������־λ��ȡ
 * �������  : 
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void read_update_flag();

/*****************************************************************************
 * �� �� ��  : write_update_flag
 * �� �� ��  : gqhuan
 * ��������  : 2023��8��30��
 * ��������  : ���������־λд��
 * �������  : 
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void write_update_flag(uint64_t newflag);

/*****************************************************************************
 * �� �� ��  : update_write_mem_one_page_to_flash
 * �� �� ��  : fz
 * ��������  : 2023��8��28��
 * ��������  : �ѿռ仺��һҳ���ݺ�д��flash;�������һҳ�Ͳ�д
 * �������  : uint8_t *pbuffer, Ҫ���������
 				uint32_t buffer_len   ���ݳ���
 * �������  : ��
 * �� �� ֵ  : ERROR=0������SUCCESS
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
ErrStatus comm_update_write_mem_one_page_to_flash(uint32_t upate_addr,
		uint8_t *pbuffer,uint32_t buffer_len);

/*****************************************************************************
 * �� �� ��  : update_write_to_flash
 * �� �� ��  : fz
 * ��������  : 2023��8��28��
 * ��������  : �ѻ������д�ŵ�����д��flash
 * �������  : uint32_t upate_addr ������ַ
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : 

*****************************************************************************/
void comm_update_write_to_flash(uint32_t upate_addr);






uint32_t test_get_gpio_pin(uint32_t flag);
uint32_t test_get_gpio_periph(uint32_t flg);

void test_dac_value_write_reg(uint8_t *p_buff,uint32_t buff_len);
void test_gpio_value_write_reg(uint8_t *p_buff,uint32_t buff_len);
void test_gpio_info_write_reg(uint8_t *p_buff,uint32_t buff_len);
void test_gpio_info_read_reg(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen);

//void test_adc_info_write_reg(uint8_t *p_buff,uint32_t buff_len);
//void test_adc_info_read_reg(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen);


#if 0
void test_two_reg_info_write_reg(uint32_t slave_addr,uint8_t *p_buff,uint32_t 
		buff_len);

void test_two_reg_info_read_byte(I2C_ALL_ADDRESS_INFO *p_address_info,uint8_t *p_buff,uint32_t 
	buff_len);

#endif

#endif

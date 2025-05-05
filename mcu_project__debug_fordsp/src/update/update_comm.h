/***********************************************************************************

 * 文 件 名   : update_comm.h
 * 负 责 人   : fz
 * 创建日期   : 2023年8月16日
 * 文件描述   : 升级功能
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 用于mcu的升级功能
 * 修改日志   : 

***********************************************************************************/


#ifndef _UPDATE_COMM_H_
#define _UPDATE_COMM_H_

#include "gd32e501.h"
#include <stdio.h>
#include <stdlib.h>

/* add by fz, 20230828, 原因:mcu写flash时要8的倍数 */
#define DIV_MOD_VALUE			8
#define DOUBLE_WORLD_LEN		8

extern uint32_t g_page_idx;
extern uint32_t g_pkt_count_to_flash;
extern uint32_t g_pkt_rx;
extern uint8_t update_flag;
extern uint8_t *g_update_mem_ptr;
extern uint32_t g_update_mem_idx;

/*****************************************************************************
 * 函 数 名  : update_mem_malloc
 * 负 责 人  : fz
 * 创建日期  : 2023年8月28日
 * 函数功能  : 升级时分配一个堆空间
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
ErrStatus update_mem_malloc();

/*****************************************************************************
 * 函 数 名  : upate_mem_is_alloc
 * 负 责 人  : fz
 * 创建日期  : 2023年8月28日
 * 函数功能  : 是否分配堆空间成功
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : ERROR=0;其它SUCCESS
 * 调用关系  : 内部调用
 * 其    它  : 

*****************************************************************************/
ErrStatus upate_mem_is_alloc();

/*****************************************************************************
 * 函 数 名  : update_mem_all_memset
 * 负 责 人  : fz
 * 创建日期  : 2023年8月28日
 * 函数功能  : 堆空间清零
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 

*****************************************************************************/
void update_mem_all_memset();

/*****************************************************************************
 * 函 数 名  : read_update_flag
 * 负 责 人  : gqhuan
 * 创建日期  : 2023年8月30日
 * 函数功能  : 升级区域标志位读取
 * 输入参数  : 
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void read_update_flag();

/*****************************************************************************
 * 函 数 名  : write_update_flag
 * 负 责 人  : gqhuan
 * 创建日期  : 2023年8月30日
 * 函数功能  : 升级区域标志位写入
 * 输入参数  : 
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void write_update_flag(uint64_t newflag);

/*****************************************************************************
 * 函 数 名  : update_write_mem_one_page_to_flash
 * 负 责 人  : fz
 * 创建日期  : 2023年8月28日
 * 函数功能  : 堆空间缓存一页数据后写入flash;如果不到一页就不写
 * 输入参数  : uint8_t *pbuffer, 要与入的数据
 				uint32_t buffer_len   数据长度
 * 输出参数  : 无
 * 返 回 值  : ERROR=0；其它SUCCESS
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
ErrStatus comm_update_write_mem_one_page_to_flash(uint32_t upate_addr,
		uint8_t *pbuffer,uint32_t buffer_len);

/*****************************************************************************
 * 函 数 名  : update_write_to_flash
 * 负 责 人  : fz
 * 创建日期  : 2023年8月28日
 * 函数功能  : 把缓冲区中存放的数据写到flash
 * 输入参数  : uint32_t upate_addr 升级地址
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 内部调用
 * 其    它  : 

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

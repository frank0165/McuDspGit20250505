/***********************************************************************************

 * 文 件 名   : mcu_system_comm.h
 * 负 责 人   : fz
 * 创建日期   : 2023年5月3日
 * 文件描述   : mcu system function
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/
#ifndef _MCU_SYSTEM_COMM_H_
#define _MCU_SYSTEM_COMM_H_
#include "gd32e501.h"

#define MCU_REF_VOLTAGE				2.5
#define MCU_12BIT_RANGE				4096

#define MCU_CFG_YES				1
#define MCU_CFG_NO				0


#define MCU_TEST_FUNS_CFG		MCU_CFG_YES

#define MCU_DEBUG_FUNS_CFG		MCU_CFG_NO

/*一般float乘上100，用整数表示*/
#define CALC_FLOAT_PARAM		100
#define CALC_100TIMES			100

#include "stdio.h"

#define PRINTOUT				printf

/*****************************************************************************
 * 函 数 名  : fh_delay_ms
 * 负 责 人  : fz
 * 创建日期  : 2023年8月29日
 * 函数功能  : 延时毫秒
 * 输入参数  : uint32_t ms  毫秒
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
void fh_delay_ms(uint32_t ms);

/*****************************************************************************
 * 函 数 名  : fh_delay_us
 * 负 责 人  : fz
 * 创建日期  : 2023年8月29日
 * 函数功能  : 延时微秒
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
void fh_delay_us(uint32_t us);




/*****************************************************************************
 * 函 数 名  : system_delay_ms
 * 负 责 人  : fz
 * 创建日期  : 2023年8月30日
 * 函数功能  : 由系统时钟产生的延时
 * 输入参数  : uint32_t ms  毫秒
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 一定要在systick_config启动后使用

*****************************************************************************/
void system_delay_ms(uint32_t ms);


/*****************************************************************************
 * 函 数 名  : system_get_current_ticks
 * 负 责 人  : fz
 * 创建日期  : 2023年9月21日
 * 函数功能  : 得到当前tick计数
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 返回当前tick计数
 * 调用关系  : 外部接口
 * 其    它  : 这里1个tick代表1 ms

*****************************************************************************/
uint32_t system_get_current_ticks();

/* read flash value from addr_start*/
void flash_read(uint8_t *outputdata,uint32_t addr_start,uint16_t data_len);

/* write flash value from addr_start*/
int32_t flash_write(uint8_t *inputdata,uint32_t addr_start,uint16_t data_len);

/*!
    \brief      erase fmc single page from start_addr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_erase_single_page(uint32_t start_addr);

/*****************************************************************************
 * 函 数 名  : search_bisection_temp_by_adc
 * 负 责 人  : fz
 * 创建日期  : 2023年5月27日
 * 函数功能  : 查找温度
 * 输入参数  : uint16_t adc_value,  要查找的adc
				uint16_t* tec_table,   数据表
				uint16_t tec_count		数据表中的元素个数
				uint8_t scale,			刻度
 * 输出参数  : uint32_t* temp   输出找到的数据 (温度)，因为保留两小数，因此数据是*100
 * 返 回 值  : ERROR-失败;SUCCESS成功
 * 调用关系  : 内部调用
 * 其    它  : 二叉法查找法

*****************************************************************************/
uint8_t search_bisection_temp_by_adc(uint16_t adc_value, 
			uint16_t* tec_table, 
			uint16_t tec_count,
			uint8_t scale,
			uint32_t* temp);


/*****************************************************************************
 * 函 数 名  : set_u16
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月23日
 * 函数功能  : 设置2字节的大头端
 * 输入参数  : uint8_t *buf,  buffer
                uint16_t val  uint16_t型数据
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void set_u16( uint8_t *buf, uint16_t val);


/*****************************************************************************
 * 函 数 名  : get_u16
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月23日
 * 函数功能  : 获取uint16型数据
 * 输入参数  : uint8_t * pVal 传入的数组
 * 输出参数  : 无
 * 返 回 值  : uint16型数据
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
uint16_t get_u16(uint8_t * pVal);

/*****************************************************************************
 * 函 数 名  : set_u32
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月23日
 * 函数功能  : 设置2字节的大头端
 * 输入参数  : uint8_t *buf,  buffer
                uint16_t val  uint32_t型数据
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void set_u32(uint8_t *buf, uint32_t val);

/*****************************************************************************
 * 函 数 名  : get_u32
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月23日
 * 函数功能  : 获取uint16型数据
 * 输入参数  : uint8_t * pVal 传入的数组
 * 输出参数  : 无
 * 返 回 值  : uint32型数据
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
uint32_t get_u32(uint8_t *pVal);


#if (MCU_DEBUG_FUNS_CFG == MCU_CFG_YES)
void debug_read_printf_buff_read_reg(uint8_t regaddr,
											uint8_t *pbuff,
											uint32_t buffer_len);

void debug_printf_buffer_hex_save(uint8_t *p_buffer,uint32_t buffer_len);

#endif


#define CYCLE_DELAY_TIME_US	500//2000
#define while_fun(x,us,cycle) 	\
	(us) *= 72;							\
	while((us) > 1)							\
	{									\
		if(!(x))						\
		{								\
			cycle = 0;					\
			break;						\
		}								\
		us--;							\
	}									\
										\
	if(1 == us)							\
	{									\
		cycle = 1;						\
	}									\
	


#endif

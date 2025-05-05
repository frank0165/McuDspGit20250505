/***********************************************************************************

 * 文 件 名   : mcu_system_comm.c
 * 负 责 人   : fz
 * 创建日期   : 2023年5月3日
 * 文件描述   : mcu system function
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/
#include "mcu_system_comm.h"
#include "mcu_data_type.h"
#include "mcu_global_vars_param.h"
#include "gd32e501_eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (MCU_DEBUG_FUNS_CFG == MCU_CFG_YES)
PRINT_BUFFER_CONFIG g_print_buffer_cfg;

#endif

/*****************************************************************************
 * 函 数 名  : fh_delay_ms
 * 负 责 人  : fz
 * 创建日期  : 2023年8月29日
 * 函数功能  : 延时毫秒
 * 输入参数  : uint32_t ms  毫秒
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : cpu空转延时

*****************************************************************************/
void fh_delay_ms(uint32_t ms)
{
	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t us = 110 * ms;
    for(i = 0; i < us; i++)
    {
	    for(j = 0; j < 72; j++);
    }
}

/*****************************************************************************
 * 函 数 名  : fh_delay_us
 * 负 责 人  : fz
 * 创建日期  : 2023年8月29日
 * 函数功能  : 延时微秒
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : cpu空转延时

*****************************************************************************/
void fh_delay_us(uint32_t us)
{
	uint32_t i = 0;
	uint32_t j = 0;
    for(i = 0; i < us; i++)
    {
	    for(j = 0; j < 7; j++);
    }
}




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
void system_delay_ms(uint32_t ms)
{
	
	uint32_t tiks = MCU_SYSTEM_MS_PERIOD + ms;
	uint32_t covert_value = ~0;

	/*防止整数反转*/
	if(tiks == covert_value || 0 == tiks)
	{
		return;
	}

	while(MCU_SYSTEM_MS_PERIOD < tiks)
	{
		
	}

	return;
}

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
uint32_t system_get_current_ticks()
{
	return MCU_SYSTEM_MS_PERIOD;
}


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
void set_u16( uint8_t *buf, uint16_t val)
{
    /* ê?è?2?êy?D?? */
    if (NULL == buf)
    {
        return;
    }

    *buf = (val >> 8) & 0xFF;
    *(buf + 1) = val & 0xFF;
    return;
}


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
uint16_t get_u16(uint8_t * pVal)
{
	uint16_t  val = 0;
	uint8_t   highByteValue = 0;
	uint8_t   lowByteValue = 0;

    /* ê?è?2?êy?D?? */
    if (NULL == pVal)
    {
        return 0;
    }

    highByteValue = *pVal;
    lowByteValue = *(pVal + 1);
    val = ( ( (unsigned short)highByteValue ) << 8 ) |( (unsigned short)
			lowByteValue );
    return val;
}

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
void set_u32(uint8_t *buf, uint32_t val)
{
    /* ê?è?2?êy?D?? */
    if (NULL == buf)
    {
        return;
    }

    *buf = ( val >> 24 ) & 0xFF;
    *(buf + 1) = (val >> 16) & 0xFF;
    *(buf + 2) = (val >> 8) & 0xFF;
    *(buf + 3) = val & 0xFF;
    return;
}


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
uint32_t get_u32(uint8_t *pVal)
{
    uint32_t    val = 0;
    uint8_t   firstByteValue = 0;     /* μúò???êy?μ′óD? */
    uint8_t   secondByteValue = 0;    /* μú?t??êy?μ′óD?*/
    uint8_t   thirdByteValue = 0;     /* μúèy??êy?μ′óD? */
    uint8_t   fourthByteValue = 0;    /* μú????êy?μ′óD?*/

    /* ê?è?2?êy?D?? */
    if (NULL == pVal)
    {
        return 0;
    }

    firstByteValue = *(pVal);           /* ??è?μúò?×??úêy?μ */
    secondByteValue = *(pVal + 1);      /* ??è?μú?t×??úêy?μ */
    thirdByteValue = *(pVal + 2);       /* ??è?μúèy×??úêy?μ */
    fourthByteValue = *(pVal + 3);      /* ??è?μú??×??úêy?μ */

    /* ????×üêy?μ′óD? */
    val = (((unsigned int)firstByteValue) << 24 ) | (((unsigned int)
				secondByteValue) << 16) |
        (((unsigned int)thirdByteValue) << 8) |((unsigned int)fourthByteValue);
	
    return val;
}


#if (MCU_DEBUG_FUNS_CFG == MCU_CFG_YES)

void debug_read_printf_buff_read_reg(uint8_t regaddr,
													uint8_t *pbuff,
													uint32_t buffer_len)
{	
	if(TEST_READ_PRINT_BUFF_REG != regaddr)
	{
		return;
	}

	if(NULL == pbuff)
	{
		return;
	}

	if(buffer_len > PRINT_BUFFER_MAX)
	{
		buffer_len = PRINT_BUFFER_MAX;
	}

	memcpy(pbuff,g_print_buffer_cfg.buffer,buffer_len);

	return;
	
}

void debug_printf_buffer_hex_save(uint8_t *p_buffer,uint32_t buffer_len)
{
	memset(&g_print_buffer_cfg,0,sizeof(g_print_buffer_cfg));

	if(buffer_len > PRINT_BUFFER_MAX)
	{
		buffer_len = PRINT_BUFFER_MAX;
	}
	memcpy(g_print_buffer_cfg.buffer,p_buffer,buffer_len);
	
	return;
}

#endif

/*****************************************************************************
 * 函 数 名  : adc_calc_temp_value
 * 负 责 人  : fz
 * 创建日期  : 2023年5月24日
 * 函数功能  : 利用插值法计算温度
 * 输入参数  : uint16_t* tec_table, 数组表
			uint16_t tec_count, 数组中的元素
			uint16_t leftn,		数组中左位
			uint16_t rightn,    数组中右位
			uint16_t adc_value  需要计算的adc
			uint8_t  scale		精度
 * 输出参数  : uint32_t* temp   温度的整数，原数据*100，保留两位小数
 * 返 回 值  : 无
 * 调用关系  : 内部调用 (find_adc_temp)
 * 其    它  : 因为tec 热敏电阻是[-40,120],刻度是1,所以数组下标+40表示温度
 [0,160]=>[-40,120]，这里scale = 1;
               case热敏电阻[-40,125],该度是5,这里scale = 5

*****************************************************************************/
void adc_calc_temp_value(uint16_t* tec_table,
	uint16_t tec_count,
	uint16_t leftn,
	uint16_t rightn,
	uint16_t adc_value,
	uint8_t scale,
	uint32_t* temp)
{
	
	/* add by fz, 20230625, 原因:参数合法性检查 */
	if (NULL == tec_table || tec_count < 1 || NULL == temp
		|| 0 == scale)
	{
		return;
	}

	/* add by fz, 20230625, 原因:参数合法性检查 */
	if (leftn > rightn || rightn >= tec_count)
	{
		return;
	}

	/* add by fz, 20230625, 原因:插值计算 */
	if (leftn == rightn)
	{
		*temp = (leftn * scale) * CALC_FLOAT_PARAM;
		
	}
	else
	{
		*temp = (leftn * scale) * CALC_FLOAT_PARAM +
			(*(tec_table + leftn) - adc_value) * CALC_FLOAT_PARAM * scale / (*(tec_table + 
			leftn) - *(tec_table + rightn));
	}

	return;
}

#if 1
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
			uint32_t* temp)
{
	/*参数初始化*/
	uint16_t left_n = 0;
	uint16_t right_n = 0;
	uint16_t mid = 0;	

	
	/*参数合法性检查*/
	if (NULL == tec_table || tec_count < 1 || NULL == temp)
	{
		return ERROR;
	}
	right_n = tec_count - 1;

	if (adc_value < *(tec_table + right_n))
	{
		adc_value = *(tec_table + right_n);
		
	}
	else if(adc_value > *tec_table)
	{
		adc_value = *tec_table;
	}

	/* add by fz, 20230625, 原因:二叉法查找及计算 */
	while (left_n <= right_n)
	{
		mid = (left_n + right_n) / 2;
	
		if (*(tec_table + mid) == adc_value)
		{			
			adc_calc_temp_value(tec_table, 
				tec_count, 
				mid,
				mid, 
				adc_value,
				scale,
				temp);
			return SUCCESS;
		}
		else if (adc_value < *(tec_table + mid))
		{			
			left_n = mid + 1;
			if (left_n > right_n)
			{
				adc_calc_temp_value(tec_table, 
					tec_count, 
					right_n - 1, 
					right_n, 
					adc_value, 
					scale,
					temp);
				return SUCCESS;
			}

		}
		else
		{			
			right_n = mid - 1;
			if (right_n < left_n)
			{
				adc_calc_temp_value(tec_table,
					tec_count, 
					left_n - 1,
					left_n, 
					adc_value, 
					scale,
					temp);
				return SUCCESS;
			}			
		}

	}

	return ERROR;

}

/*!
    \brief      read flash vlaue from addr_start
    \param[in]  none
    \param[out] none
    \retval     none
*/
void flash_read(uint8_t *outputdata,uint32_t addr_start,uint16_t data_len)
{
	uint32_t addr = 0;
	uint16_t i = 0;
	
	addr = addr_start;
	
	for(i=0;i<data_len;i++) 
	{
		outputdata[i] = *(uint8_t*) addr;
		addr = addr + sizeof(uint8_t);
		
	}
}

/*!
    \brief      write flash vlaue from addr_start
    \param[in]  none
    \param[out] none
    \retval     none
*/
int32_t flash_write(uint8_t *inputdata,uint32_t addr_start,uint16_t data_len)
{
	uint16_t i,index;
	uint32_t new_addr;
	uint64_t data=0; 
	new_addr = addr_start;
	fmc_bank0_flag_clear(FMC_BANK0_FLAG_END | FMC_BANK0_FLAG_WPERR | FMC_BANK0_FLAG_PGERR);
    fmc_unlock();
	for(i=0;i<data_len;i++)
	{
		if((i+1) % 8 == 0){
			for(int8_t j=7;j>=0;j--){
				data <<= 8;
				index = j+((i+1)/8-1)*8;				
				data |= inputdata[index];
				
			}
			fmc_doubleword_program(new_addr,data);
			fmc_bank0_flag_clear(FMC_BANK0_FLAG_END | FMC_BANK0_FLAG_WPERR | FMC_BANK0_FLAG_PGERR);
			new_addr = new_addr+sizeof(uint64_t);
			data = 0;
		}	
	}
	fmc_lock();	
	return 0;
}

/*!
    \brief      erase fmc single page from start_addr
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_erase_single_page(uint32_t start_addr)
{
    /* unlock the flash program/erase controller */
    fmc_unlock();
  // fmc_bank0_unlock();

    /* clear all pending flags */
    fmc_bank0_flag_clear(FMC_BANK0_FLAG_END | FMC_BANK0_FLAG_WPERR | 
    FMC_BANK0_FLAG_PGERR);
    
    /* erase the flash pages */
	
    fmc_page_erase(start_addr);
	
    fmc_bank0_flag_clear(FMC_BANK0_FLAG_END | FMC_BANK0_FLAG_WPERR | FMC_BANK0_FLAG_PGERR);

    /* lock the main FMC after the erase operation */
    fmc_lock();
   // fmc_bank0_lock();
}


#endif


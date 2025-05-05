/***********************************************************************************

 * 文 件 名   : update_comm.c
 * 负 责 人   : fz
 * 创建日期   : 2023年8月16日
 * 文件描述   : 升级功双腿
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcu_data_type.h"
#include "mcu_pin_type.h"
#include "mcu_system_comm.h"
#include "mcu_global_vars_param.h"
#include "update_comm.h"



uint8_t *g_update_mem_ptr = 0U;
uint32_t g_update_mem_idx = 0;
uint32_t g_page_idx = 0;
uint32_t g_pkt_count_to_flash = 0;
uint32_t g_pkt_rx = 0;
uint8_t update_flag = SECTION_A_FLAG;

extern ErrStatus comm_update_flash_finish_one_page(uint32_t upate_addr);


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
ErrStatus update_mem_malloc()
{
	if(0U == g_update_mem_ptr)
	{
		g_update_mem_ptr = (uint8_t *)malloc(FLASH_PAGE_SIZE + 200);
		if(g_update_mem_ptr == NULL)
		{
		    /* add by fangzhe, 20250321, 原因:出错打印 ，
                malloc已经失败了，会产生异常，这里加打印提示
            */
			PRINTOUT("error_malloc \r\n");
		}		
		
	}

	if(g_update_mem_ptr != NULL)
	{
		memset(g_update_mem_ptr,0,FLASH_PAGE_SIZE);
	}
	else
	{
		return ERROR;
	}

	return SUCCESS;
}


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
ErrStatus upate_mem_is_alloc()
{
	ErrStatus ret = ERROR;
	ret = (0U == g_update_mem_ptr) ? ERROR : SUCCESS;
	return ret;
}

/*****************************************************************************
 * 函 数 名  : update_mem_free
 * 负 责 人  : fz
 * 创建日期  : 2023年8月28日
 * 函数功能  : 释放堆空间
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 

*****************************************************************************/
void update_mem_free()
{
	if(g_update_mem_ptr != 0U)
	{
		free(g_update_mem_ptr);
		g_update_mem_ptr = 0U;
	}
}

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
void update_mem_all_memset()
{
	if(g_update_mem_ptr != 0U)
	{
		memset(g_update_mem_ptr,0,FLASH_PAGE_SIZE);
		g_update_mem_idx = 0;
		g_page_idx = 0;
	}
}



/*****************************************************************************
 * 函 数 名  : read_update_flag
 * 负 责 人  : gqhuan
 * 创建日期  : 2023年8月30日
 * 函数功能  : 升级区域标志位读取
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void read_update_flag()
{
	uint32_t addr_start = UPDATE_FLAG + 7 * sizeof(uint8_t);
	flash_read(&update_flag,addr_start,1);
  
}

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
void write_update_flag(uint64_t newflag)
{
	uint8_t inputdata[8];
	
	for(int i =0;i<7;i++){
		inputdata[i] = 0;
	}
	inputdata[7] = newflag & 0xFF;

	fmc_erase_single_page(UPDATE_FLAG);
	flash_write(inputdata,UPDATE_FLAG,8);
	
}

/*****************************************************************************
 * 函 数 名  : update_flash_finish_one_page
 * 负 责 人  : fz
 * 创建日期  : 2023年8月28日
 * 函数功能  : 强制写一页数据到flash
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
ErrStatus comm_update_flash_finish_one_page(uint32_t upate_addr)
{
	/*写的地址*/
	
	fmc_erase_single_page(upate_addr + g_page_idx * FLASH_PAGE_SIZE);	
	flash_write(g_update_mem_ptr,
		upate_addr + g_page_idx * FLASH_PAGE_SIZE,
		FLASH_PAGE_SIZE);	
	
	g_page_idx++;
	g_pkt_count_to_flash += FLASH_PAGE_SIZE;
	//printf("(0x%x)/",upate_addr + g_page_idx * FLASH_PAGE_SIZE);	
	return SUCCESS;
}

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
void comm_update_write_to_flash(uint32_t upate_addr)
{
	uint32_t i = 0;	
	uint32_t div_mod = 0;	
	
	if(0 == g_update_mem_idx)
	{
		return;
	}

	if(ERROR == upate_mem_is_alloc())
	{
		return;
	}

	/*8的余数*/
	div_mod = g_update_mem_idx % DIV_MOD_VALUE;

	if(0 != div_mod)
	{
		/*总计大于1024，就返回*/
		if((g_update_mem_idx + (DIV_MOD_VALUE - div_mod)) > FLASH_PAGE_SIZE)
		{
			return;
		}

		/*补0，凑成8的倍数*/
		for(i = 0; i < (DIV_MOD_VALUE - div_mod);i++)
		{
			g_update_mem_ptr[g_update_mem_idx++] = 0U;
		}
	}

	if(0 != g_update_mem_idx)
	{
		fmc_erase_single_page(upate_addr + g_page_idx * FLASH_PAGE_SIZE);	
		flash_write(g_update_mem_ptr,
			upate_addr + g_page_idx * FLASH_PAGE_SIZE,
			g_update_mem_idx);	
	}

	//printf("flash_end_address(0x%x),mod=0x%x\r\n",
		//upate_addr + g_page_idx * FLASH_PAGE_SIZE + g_update_mem_idx,
		//g_update_mem_idx);
	//printf("#");	
	g_pkt_count_to_flash += g_update_mem_idx;

	if(FLASH_PAGE_SIZE == g_update_mem_idx)
	{
		g_page_idx++;
		g_update_mem_idx = 0;
	}
	
	return;
	
}

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
		uint8_t *pbuffer,uint32_t buffer_len)
{
	
	uint32_t cur_idx = 0;
	uint32_t tmplen = 0;
	uint32_t i = 0;
	if(0U == pbuffer || 0U == buffer_len)
	{
		return ERROR;
	}	

	/*当前堆中数据+buffer数据不到一页时*/
	if((g_update_mem_idx + buffer_len) <= FLASH_PAGE_SIZE)
	{
		memcpy(&g_update_mem_ptr[g_update_mem_idx],
			pbuffer,buffer_len);		
		
		g_update_mem_idx += buffer_len;
		if(FLASH_PAGE_SIZE == g_update_mem_idx)
		{
			comm_update_flash_finish_one_page(upate_addr);
			memset(g_update_mem_ptr,0,FLASH_PAGE_SIZE);			
			g_update_mem_idx = 0;
		}
		
	}
	else
	{
		/*当前堆中数据+buffer数据大于一页时*/
		memcpy(&g_update_mem_ptr[g_update_mem_idx],
			pbuffer,FLASH_PAGE_SIZE - g_update_mem_idx);
		
		cur_idx = FLASH_PAGE_SIZE - g_update_mem_idx;		

		/*先写一页数据到flash*/
		comm_update_flash_finish_one_page(upate_addr);

		/*剩下的数据放在堆中*/
		memset(g_update_mem_ptr,0,FLASH_PAGE_SIZE);
		g_update_mem_idx = 0;
		tmplen = buffer_len - cur_idx;					
		memcpy(&g_update_mem_ptr[g_update_mem_idx],
			&pbuffer[cur_idx],tmplen);
			g_update_mem_idx += tmplen;
		
	}

	return SUCCESS;
	
}

#if 0
void update_show_version_info()
{
	printf("%s_%s_%d_%d\r\n",__DATE__,__TIME__,sizeof(__DATE__),sizeof(__TIME__));
	
}

#endif


/* add by fangzhe, 20250321, 原因:调试代码 ，正式版本不要*/
#if (MCU_TEST_FUNS_CFG == MCU_CFG_YES)	

void test_dac_value_write_reg(uint8_t *p_buff,uint32_t buff_len)
{
	uint8_t k = 0;
	uint8_t tmp1 = 0;
	uint8_t tmp2 = 0;
	uint32_t dac_perith = DAC0;
	uint32_t dac_out = DAC_OUT_0;
	uint16_t dac_value = 0;
	if(NULL == p_buff || buff_len < 2)
	{
		return;
	}

	if(TEST_DAC_PIN_REG != p_buff[0])
	{
		return;
	}

	k = 1;
	tmp1 = p_buff[k];
	switch(p_buff[k])
	{
		case MCU_DAC_0:
		{
			dac_perith = DAC0;
			break;
		}
		
		case MCU_DAC_1:
		{
			dac_perith = DAC1;
			break;
		}
		default:
		{
			return;
			break;
		}

	}
	
	k++;

	tmp2 = p_buff[k];
	switch(p_buff[k])
	{
		case MCU_DAC_OUT_0:
		{
			dac_out = DAC_OUT_0;
			break;
		}
		
		case MCU_DAC_OUT_1:
		{
			dac_out = DAC_OUT_1;
			break;
		}
		default:
		{
			return;
			
		}

	}
	k++;
	dac_value = get_u16(&p_buff[k]);
	dac_data_set(dac_perith, dac_out,DAC_ALIGN_12B_R,dac_value);	
	printf("dac(%u),out(%u),dac_value(%u)\r\n",tmp1,tmp2,dac_value);

	return;
	
}


uint32_t test_get_gpio_periph(uint32_t flg)
{
	uint32_t gpio_periph = 0;
	switch(flg)
	{
		case MCU_GPIO_A:
		{
			gpio_periph = GPIOA;
			break;
		}
		case MCU_GPIO_B:
		{
			gpio_periph = GPIOB;
			break;
		}
		case MCU_GPIO_C:
		{
			gpio_periph = GPIOC;
			break;
		}
		case MCU_GPIO_D:
		{
			gpio_periph = GPIOD;
			break;
		}
		case MCU_GPIO_F:
		{
			gpio_periph = GPIOF;
			break;
		}
		default:
		{
			gpio_periph = 0xf;
			break;
		}
	}

	return gpio_periph;
}

uint32_t test_get_gpio_pin(uint32_t flag)
{
	uint32_t pin = 0;
	if(flag < 15)
	{
		pin = BIT(flag);
	}
	return pin;
}


//void gpio_bit_reset(uint32_t gpio_periph, uint32_t pin)

void test_gpio_value_write_reg(uint8_t *p_buff,uint32_t buff_len)
{
	uint32_t gpio_periph = 0;
	uint32_t pin = 0;
	uint8_t n = 0;
	uint8_t bit = 0;
	if(NULL == p_buff || buff_len < 2)
	{
		return;
	}

	if(TEST_GPIO_PIN_REG != p_buff[0])
	{
		return;
	}
	n = 1;
	
	gpio_periph = test_get_gpio_periph(p_buff[n++]);
	
	pin = test_get_gpio_pin(p_buff[n++]); 	

	//gpio_mode_set(gpio_periph, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_3);  

#if 0
    /*无用代码*/
	if(GPIOB == gpio_periph && GPIO_PIN_3 == pin)
	{
		gpio_mode_set(gpio_periph, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_3);
	}
#endif
	bit = p_buff[n];
	if(0 == bit)
	{
		gpio_bit_reset(gpio_periph, pin);
	}
	else
	{
		gpio_bit_set(gpio_periph, pin);
	}
	return;
	
}

//TEST_GPIO_INFO_REG
uint8_t test_gpio_flg = 0;
uint8_t test_gpio_in_out_flg = 0;
uint8_t test_gpio_pin_flg = 0;
void test_gpio_info_write_reg(uint8_t *p_buff,uint32_t buff_len)
{
	uint8_t n = 0;
	if(NULL == p_buff || buff_len < 2)
	{
		return;
	}

	if(TEST_GPIO_INFO_REG != p_buff[0])
	{
		return;
	}

	n = 1;
	test_gpio_flg = p_buff[n++];
	test_gpio_pin_flg = p_buff[n++];
	test_gpio_in_out_flg = p_buff[n];
	printf("gpio(%u),pin(%u),in_out(%u)\r\n",
		test_gpio_flg,
		test_gpio_pin_flg,
		test_gpio_in_out_flg);
	return;
}


void test_gpio_info_read_reg(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
	uint32_t gpio_periph = 0;
	uint32_t gpio_pin = 0;
	
	if(TEST_GPIO_INFO_REG != regaddr)
	{
		return;
	}

	if(NULL == pbuff)
	{
		return;
	}

	if(bufflen <1)
	{
		return;
	}	

	gpio_periph = test_get_gpio_periph(test_gpio_flg);
	gpio_pin = test_get_gpio_pin(test_gpio_pin_flg);
	

	if(0 == test_gpio_in_out_flg)
	{
		pbuff[0] = gpio_output_bit_get(gpio_periph,gpio_pin);
	}
	else
	{
		pbuff[0] = gpio_input_bit_get(gpio_periph,gpio_pin);
	}
	printf("gpio_bit(%u)\r\n",pbuff[0]);
	return;
}

#endif
//CMD_OPTICAL_PASSWORD_LIMIT



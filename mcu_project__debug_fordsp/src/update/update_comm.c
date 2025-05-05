/***********************************************************************************

 * �� �� ��   : update_comm.c
 * �� �� ��   : fz
 * ��������   : 2023��8��16��
 * �ļ�����   : ������˫��
 * ��Ȩ˵��   : Copyright (C) 2000-2023   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

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
ErrStatus update_mem_malloc()
{
	if(0U == g_update_mem_ptr)
	{
		g_update_mem_ptr = (uint8_t *)malloc(FLASH_PAGE_SIZE + 200);
		if(g_update_mem_ptr == NULL)
		{
		    /* add by fangzhe, 20250321, ԭ��:�����ӡ ��
                malloc�Ѿ�ʧ���ˣ�������쳣������Ӵ�ӡ��ʾ
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
ErrStatus upate_mem_is_alloc()
{
	ErrStatus ret = ERROR;
	ret = (0U == g_update_mem_ptr) ? ERROR : SUCCESS;
	return ret;
}

/*****************************************************************************
 * �� �� ��  : update_mem_free
 * �� �� ��  : fz
 * ��������  : 2023��8��28��
 * ��������  : �ͷŶѿռ�
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : 

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
 * �� �� ��  : read_update_flag
 * �� �� ��  : gqhuan
 * ��������  : 2023��8��30��
 * ��������  : ���������־λ��ȡ
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void read_update_flag()
{
	uint32_t addr_start = UPDATE_FLAG + 7 * sizeof(uint8_t);
	flash_read(&update_flag,addr_start,1);
  
}

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
 * �� �� ��  : update_flash_finish_one_page
 * �� �� ��  : fz
 * ��������  : 2023��8��28��
 * ��������  : ǿ��дһҳ���ݵ�flash
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
ErrStatus comm_update_flash_finish_one_page(uint32_t upate_addr)
{
	/*д�ĵ�ַ*/
	
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

	/*8������*/
	div_mod = g_update_mem_idx % DIV_MOD_VALUE;

	if(0 != div_mod)
	{
		/*�ܼƴ���1024���ͷ���*/
		if((g_update_mem_idx + (DIV_MOD_VALUE - div_mod)) > FLASH_PAGE_SIZE)
		{
			return;
		}

		/*��0���ճ�8�ı���*/
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
		uint8_t *pbuffer,uint32_t buffer_len)
{
	
	uint32_t cur_idx = 0;
	uint32_t tmplen = 0;
	uint32_t i = 0;
	if(0U == pbuffer || 0U == buffer_len)
	{
		return ERROR;
	}	

	/*��ǰ��������+buffer���ݲ���һҳʱ*/
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
		/*��ǰ��������+buffer���ݴ���һҳʱ*/
		memcpy(&g_update_mem_ptr[g_update_mem_idx],
			pbuffer,FLASH_PAGE_SIZE - g_update_mem_idx);
		
		cur_idx = FLASH_PAGE_SIZE - g_update_mem_idx;		

		/*��дһҳ���ݵ�flash*/
		comm_update_flash_finish_one_page(upate_addr);

		/*ʣ�µ����ݷ��ڶ���*/
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


/* add by fangzhe, 20250321, ԭ��:���Դ��� ����ʽ�汾��Ҫ*/
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
    /*���ô���*/
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



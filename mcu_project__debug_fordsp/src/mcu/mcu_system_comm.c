/***********************************************************************************

 * �� �� ��   : mcu_system_comm.c
 * �� �� ��   : fz
 * ��������   : 2023��5��3��
 * �ļ�����   : mcu system function
 * ��Ȩ˵��   : Copyright (C) 2000-2023   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

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
 * �� �� ��  : fh_delay_ms
 * �� �� ��  : fz
 * ��������  : 2023��8��29��
 * ��������  : ��ʱ����
 * �������  : uint32_t ms  ����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : cpu��ת��ʱ

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
 * �� �� ��  : fh_delay_us
 * �� �� ��  : fz
 * ��������  : 2023��8��29��
 * ��������  : ��ʱ΢��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : cpu��ת��ʱ

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
 * �� �� ��  : system_delay_ms
 * �� �� ��  : fz
 * ��������  : 2023��8��30��
 * ��������  : ��ϵͳʱ�Ӳ�������ʱ
 * �������  : uint32_t ms  ����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : һ��Ҫ��systick_config������ʹ��

*****************************************************************************/
void system_delay_ms(uint32_t ms)
{
	
	uint32_t tiks = MCU_SYSTEM_MS_PERIOD + ms;
	uint32_t covert_value = ~0;

	/*��ֹ������ת*/
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
 * �� �� ��  : system_get_current_ticks
 * �� �� ��  : fz
 * ��������  : 2023��9��21��
 * ��������  : �õ���ǰtick����
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ���ص�ǰtick����
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ����1��tick����1 ms

*****************************************************************************/
uint32_t system_get_current_ticks()
{
	return MCU_SYSTEM_MS_PERIOD;
}


/*****************************************************************************
 * �� �� ��  : set_u16
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��23��
 * ��������  : ����2�ֽڵĴ�ͷ��
 * �������  : uint8_t *buf,  buffer
                uint16_t val  uint16_t������
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void set_u16( uint8_t *buf, uint16_t val)
{
    /* ��?��?2?��y?D?? */
    if (NULL == buf)
    {
        return;
    }

    *buf = (val >> 8) & 0xFF;
    *(buf + 1) = val & 0xFF;
    return;
}


/*****************************************************************************
 * �� �� ��  : get_u16
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��23��
 * ��������  : ��ȡuint16������
 * �������  : uint8_t * pVal ���������
 * �������  : ��
 * �� �� ֵ  : uint16������
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : 

*****************************************************************************/
uint16_t get_u16(uint8_t * pVal)
{
	uint16_t  val = 0;
	uint8_t   highByteValue = 0;
	uint8_t   lowByteValue = 0;

    /* ��?��?2?��y?D?? */
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
 * �� �� ��  : set_u32
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��23��
 * ��������  : ����2�ֽڵĴ�ͷ��
 * �������  : uint8_t *buf,  buffer
                uint16_t val  uint32_t������
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void set_u32(uint8_t *buf, uint32_t val)
{
    /* ��?��?2?��y?D?? */
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
 * �� �� ��  : get_u32
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��23��
 * ��������  : ��ȡuint16������
 * �������  : uint8_t * pVal ���������
 * �������  : ��
 * �� �� ֵ  : uint32������
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : 

*****************************************************************************/
uint32_t get_u32(uint8_t *pVal)
{
    uint32_t    val = 0;
    uint8_t   firstByteValue = 0;     /* �̨���???��y?�̡䨮D? */
    uint8_t   secondByteValue = 0;    /* �̨�?t??��y?�̡䨮D?*/
    uint8_t   thirdByteValue = 0;     /* �̨���y??��y?�̡䨮D? */
    uint8_t   fourthByteValue = 0;    /* �̨�????��y?�̡䨮D?*/

    /* ��?��?2?��y?D?? */
    if (NULL == pVal)
    {
        return 0;
    }

    firstByteValue = *(pVal);           /* ??��?�̨���?��??����y?�� */
    secondByteValue = *(pVal + 1);      /* ??��?�̨�?t��??����y?�� */
    thirdByteValue = *(pVal + 2);       /* ??��?�̨���y��??����y?�� */
    fourthByteValue = *(pVal + 3);      /* ??��?�̨�??��??����y?�� */

    /* ????������y?�̡䨮D? */
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
 * �� �� ��  : adc_calc_temp_value
 * �� �� ��  : fz
 * ��������  : 2023��5��24��
 * ��������  : ���ò�ֵ�������¶�
 * �������  : uint16_t* tec_table, �����
			uint16_t tec_count, �����е�Ԫ��
			uint16_t leftn,		��������λ
			uint16_t rightn,    ��������λ
			uint16_t adc_value  ��Ҫ�����adc
			uint8_t  scale		����
 * �������  : uint32_t* temp   �¶ȵ�������ԭ����*100��������λС��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ����� (find_adc_temp)
 * ��    ��  : ��Ϊtec ����������[-40,120],�̶���1,���������±�+40��ʾ�¶�
 [0,160]=>[-40,120]������scale = 1;
               case��������[-40,125],�ö���5,����scale = 5

*****************************************************************************/
void adc_calc_temp_value(uint16_t* tec_table,
	uint16_t tec_count,
	uint16_t leftn,
	uint16_t rightn,
	uint16_t adc_value,
	uint8_t scale,
	uint32_t* temp)
{
	
	/* add by fz, 20230625, ԭ��:�����Ϸ��Լ�� */
	if (NULL == tec_table || tec_count < 1 || NULL == temp
		|| 0 == scale)
	{
		return;
	}

	/* add by fz, 20230625, ԭ��:�����Ϸ��Լ�� */
	if (leftn > rightn || rightn >= tec_count)
	{
		return;
	}

	/* add by fz, 20230625, ԭ��:��ֵ���� */
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
 * �� �� ��  : search_bisection_temp_by_adc
 * �� �� ��  : fz
 * ��������  : 2023��5��27��
 * ��������  : �����¶�
 * �������  : uint16_t adc_value,  Ҫ���ҵ�adc
				uint16_t* tec_table,   ���ݱ�
				uint16_t tec_count		���ݱ��е�Ԫ�ظ���
				uint8_t scale,			�̶�
 * �������  : uint32_t* temp   ����ҵ������� (�¶�)����Ϊ������С�������������*100
 * �� �� ֵ  : ERROR-ʧ��;SUCCESS�ɹ�
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ���淨���ҷ�

*****************************************************************************/
uint8_t search_bisection_temp_by_adc(uint16_t adc_value, 
			uint16_t* tec_table, 
			uint16_t tec_count,
			uint8_t scale,
			uint32_t* temp)
{
	/*������ʼ��*/
	uint16_t left_n = 0;
	uint16_t right_n = 0;
	uint16_t mid = 0;	

	
	/*�����Ϸ��Լ��*/
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

	/* add by fz, 20230625, ԭ��:���淨���Ҽ����� */
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


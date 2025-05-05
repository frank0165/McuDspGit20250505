/***********************************************************************************

 * �� �� ��   : update_i2c_interface.c
 * �� �� ��   : fz
 * ��������   : 2025��1��16��
 * �ļ�����   : �������ܵ�i2c�ӿ�ʵ��
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#include <stdio.h>
#include <string.h>
#include "mcu_data_type.h"
#include "mcu_global_vars_param.h"
#include "update_i2c_interface.h"
#include "sff_8472.h"
#include "update_comm.h"
#include "tec_comm.h"

unsigned char data_str[] = __DATE__;
unsigned char time_str[] = __TIME__;

/*0,no doing;1=ok,2=error*/
uint8_t g_crc_is_ok = CRC_NO_DOING;

/*****************************************************************************
 * �� �� ��  : update_app_write_reg_byte
 * �� �� ��  : fz
 * ��������  : 2023��8��24��
 * ��������  : mcuӦ�ó�������
 * �������  : uint8_t *p_buff,��������ݡ�
                       p_buff[0]:UPGRADE_APP_SOFTWARE_REG
                       p_buff[1]:UPGRADE_APP_DOING,���ڴ����ļ�
                       			UPGRADE_APP_END�������ļ�����
                       			UPGRADE_CRC_END������CRC
 				uint32_t buff_len
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void update_app_write_reg_byte(uint8_t *p_buff,uint32_t buff_len)
{
	uint32_t idx = 0;
	uint32_t write_len = 0;
	ErrStatus ret = ERROR;
	uint8_t pcrc[CRC32_RESULT_SIZE];
	uint32_t crc_receive_result = 0;
	uint32_t crc_flash_result = 0;
	uint32_t address = 0;
	
	if(NULL == p_buff || buff_len < 2)
	{
		return;
	}

	if(UPGRADE_APP_SOFTWARE_REG != p_buff[idx++])
	{
		return;
	}

/* add by fz, 20250116, ԭ��:�ر���ѯ���� */
	tec_set_default_mini_status();

	g_mcu_vars_param.g_ddm_sw_auto_process_flag = RESET;	
	g_mcu_vars_param.g_50g_ddm_sw_auto_process_flag = RESET;
	g_mcu_vars_param.g_10g_ddm_sw_auto_process_flag = RESET;
	g_mcu_vars_param.g_1g_ddm_sw_auto_process_flag = RESET;
	
	if(UPGRADE_APP_START == p_buff[1])
	{
		/* add by fz, 20250303, ԭ��:���������������Ϊset,ֹͣddm��ѯ */
		g_mcu_vars_param.g_update_process_flag = SET; 
		
		ret = upate_mem_is_alloc();
		if(ERROR == ret)
		{
			ret = update_mem_malloc();
			if(ERROR == ret)
			{
				//printf("update_mem_malloc error\r\n");
			}
			else
			{
				update_mem_all_memset();		
				g_pkt_rx = 0;
				g_pkt_count_to_flash = 0;
				g_page_idx = 0;
				
			}
		}
		else
		{
			update_mem_all_memset();		
			g_pkt_rx = 0;
			g_pkt_count_to_flash = 0;
			g_page_idx = 0;
			
		}

		read_update_flag();		
		//printf("XXstart update_flag(%u)\r\n",update_flag);
	}
	
	idx++;
	write_len = buff_len - idx; /*��Ч����*/
	g_pkt_rx += write_len;	/*���ڷ��գ�����·�ΪCRCʱҲ�����ӳ���*/	

	ret = upate_mem_is_alloc();
	if(ERROR == ret)
	{
	
		g_crc_is_ok = CRC_MALLOC_FAIL;
		return;
	}

	/* modify by fz, 20230829, ԭ��:�����жϣ�ֻ�����·��ļ�ʱ�Ż��浽���� */
	if(UPGRADE_APP_END == p_buff[1] || UPGRADE_APP_DOING == p_buff[1])
	{
		/*���ڷ��գ�����·�ΪCRCʱҲ�Ỻ�浽�ѿռ�*/	
		ret = comm_update_write_mem_one_page_to_flash(BAPPLICATIONADDRESS,
			&p_buff[idx],write_len);
	}
	
	if(UPGRADE_APP_END == p_buff[1])
	{
		comm_update_write_to_flash(BAPPLICATIONADDRESS);
		
	}

	/* add by fz, 20230829, ԭ��:�·�crcʱ���û��浽���� */
	if(UPGRADE_CRC_END == p_buff[1] && buff_len >= 6)
	{
		memset(pcrc,0,sizeof(pcrc));
		memcpy(&pcrc,&p_buff[2], sizeof(pcrc));
		crc_receive_result = get_u32(pcrc);
		
		PRINTOUT("crc:%02x %02x %02x %02x\r\n",pcrc[0],pcrc[1],pcrc[2],pcrc[3]);
		PRINTOUT("crc_receive_result:0x%x\r\n",crc_receive_result);
		
		om_crc32_reset();

		read_update_flag();		

		PRINTOUT("write to address:0x%x, pkt_len:%u\r\n",BAPPLICATIONADDRESS,g_pkt_count_to_flash);
		crc_flash_result = om_flash_block_data_calculate_crc32(BAPPLICATIONADDRESS,g_pkt_count_to_flash);
		PRINTOUT("crc_flash_result:0x%x\r\n",crc_flash_result);	

		if(crc_receive_result != crc_flash_result)
		{
			PRINTOUT("crc error !\r\n");
			g_crc_is_ok = CRC_CHECK_ERROR;
		}
		else
		{
		//	uint64_t newflag = SECTION_B_FLAG;			
			write_update_flag(SECTION_B_FLAG);	
			g_crc_is_ok = CRC_CHECK_OK;
		}
		
		update_mem_all_memset();		
		g_pkt_rx = 0;
		g_pkt_count_to_flash = 0;
		g_page_idx = 0;
	   
	}
	else
	{
		g_crc_is_ok = CRC_NO_END_RESULT;
	}
	
	return;
	
}



/*****************************************************************************
 * �� �� ��  : update_firmware_write_reg_byte
 * �� �� ��  : fz
 * ��������  : 2023��11��6��
 * ��������  : ��ģ���firmware����
 * �������  : uint8_t *p_buff,��������ݡ�
			   uint32_t buff_len ����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void update_firmware_write_reg_byte(uint8_t *p_buff,uint32_t buff_len)
{
	
	uint32_t write_len = 0;
	ErrStatus ret = ERROR;
	uint8_t pcrc[CRC32_RESULT_SIZE];
	uint32_t crc_receive_result = 0;
	uint32_t crc_flash_result = 0;
	uint32_t address = 0;
	
	if(NULL == p_buff || buff_len < 2)
	{
		return;
	}

	if(UPGRADE_FIRMWARE_REG != p_buff[0])
	{
		return;
	}

	tec_set_default_mini_status();
	g_mcu_vars_param.g_ddm_sw_auto_process_flag = RESET;
	
	if(UPGRADE_APP_START == p_buff[1])
	{
		/* add by fz, 20250303, ԭ��:���������������Ϊset,ֹͣddm��ѯ */
		g_mcu_vars_param.g_update_process_flag = SET; 
		
		ret = upate_mem_is_alloc();
		if(ERROR == ret)
		{
			ret = update_mem_malloc();
			if(ERROR == ret)
			{
			    /*mallocʧ�ܣ���ӡ��ʾ*/
				PRINTOUT("update_mem_malloc error\r\n");
			}
			else
			{
				update_mem_all_memset();		
				g_pkt_rx = 0;
				g_pkt_count_to_flash = 0;
				g_page_idx = 0;
				
			}
		}
		else
		{
			update_mem_all_memset();		
			g_pkt_rx = 0;
			g_pkt_count_to_flash = 0;
			g_page_idx = 0;
			
		}

		read_update_flag();		
		//printf("XXstart update_flag(%u)\r\n",update_flag);
	}
	
	
	write_len = buff_len - 2; /*��Ч����*/
	g_pkt_rx += write_len;	/*���ڷ��գ�����·�ΪCRCʱҲ�����ӳ���*/	

	ret = upate_mem_is_alloc();
	if(ERROR == ret)
	{
	    g_crc_is_ok = CRC_MALLOC_FAIL;
		return;
	}

	/* modify by fz, 20230829, ԭ��:�����жϣ�ֻ�����·��ļ�ʱ�Ż��浽���� */
	if(UPGRADE_APP_END == p_buff[1] || UPGRADE_APP_DOING == p_buff[1])
	{
		/*���ڷ��գ�����·�ΪCRCʱҲ�Ỻ�浽�ѿռ�*/	
		ret = comm_update_write_mem_one_page_to_flash(FWADDRESS,
			&p_buff[2],write_len);
	}
	
	if(UPGRADE_APP_END == p_buff[1])
	{
		comm_update_write_to_flash(FWADDRESS);

		#if 0
		printf("receive pkts(%u),pkt_to_flash(%u),page(%u)\r\n",
			g_pkt_rx,
			g_pkt_count_to_flash,
			g_page_idx);	
	   #endif
		
	}

	/* add by fz, 20230829, ԭ��:�·�crcʱ���û��浽���� */
	if(UPGRADE_CRC_END == p_buff[1] && buff_len >= 6)
	{
		memset(pcrc,0,sizeof(pcrc));
		memcpy(&pcrc,&p_buff[2], sizeof(pcrc));
		crc_receive_result = get_u32(pcrc);
		
		printf("crc_receive_result:0x%x\r\n",crc_receive_result);
		
		om_crc32_reset();

		read_update_flag();		

		printf("write to address:0x%x, pkt_len:%u\r\n",FWADDRESS,g_pkt_count_to_flash);
		crc_flash_result = om_flash_block_data_calculate_crc32(FWADDRESS,g_pkt_count_to_flash);
		printf("crc_flash_result:0x%x\r\n",crc_flash_result);	

		if(crc_receive_result != crc_flash_result)
		{
			printf("crc error !\r\n");
			g_crc_is_ok = CRC_CHECK_ERROR;
		}
		else
		{
			g_crc_is_ok = CRC_CHECK_OK;
		}
		
		update_mem_all_memset();		
		g_pkt_rx = 0;
		g_pkt_count_to_flash = 0;
		g_page_idx = 0;
	   
	}
    else
    {
        g_crc_is_ok = CRC_NO_END_RESULT;
    }
	
	return;
	
}

//extern uint32_t g_trigger_count;


/*****************************************************************************
 * �� �� ��  : upgrade_dev_version_reg_read
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��21��
 * ��������  : ��ȡ���������豸��Ϣ
 * �������  : uint8_t regaddr �Ĵ���
              uint32_t  bufflen pbuff�ĳ��ȣ�I2C_SLAVE_WRITE_READ_MAX
 * �������  : uint8_t *pbuff ʵ�ʷ��ص�ֵ
 * �� �� ֵ  : ��
 * ���ù�ϵ  : ��λ��i2c����
 * ��    ��  : ����ֵ���ܳ��Ȳ��ܳ���I2C_SLAVE_WRITE_READ_MAX

*****************************************************************************/
void upgrade_dev_version_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
	/*������ʼ��*/
	uint8_t tmp[80];
	uint32_t offset = 0;

	/*��App���ĵ�63ҳ��ȡboot������Ϣ*/
	//uint32_t dst_addr = AAPPLICATIONADDRESS + 63 * FLASH_PAGE_SIZE;
	
	/* add by fz, 20230625, ԭ��:�����Ϸ�ֵ��� */
	if(UPGRADE_DEV_VERSION_INFO_REG != regaddr)
	{
		return;
	}

	if(NULL == pbuff)
	{
		return;
	}

	memset(tmp,0,sizeof(tmp));	
	
	
	//date:12�ֽ�
	memcpy(&tmp[offset],__DATE__,12);
	offset += 12;

	//time: 9�ֽ�
	memcpy(&tmp[offset],__TIME__,9);
	offset += 9;
	
	//������1�ֽ�
	read_update_flag();
	tmp[offset] = update_flag;
	offset += 1;

	/*��ȡCRCУ����*/
	tmp[offset] = g_crc_is_ok;
	offset += 1;

    /*trigger��������������ʹ��*/
	set_u32(&tmp[offset],g_mcu_vars_param.g_trigger_count);
	offset += 4; //���Ϲ�27���ֽ�	С��I2C_SLAVE_WRITE_READ_MAX
	
	memcpy(pbuff,tmp,sizeof(tmp));	

	
}


/*****************************************************************************
 * �� �� ��  : update_user_boot_write_reg_byte
 * �� �� ��  : fz
 * ��������  : 2023��11��6��
 * ��������  : ��ģ���firmware����
 * �������  : uint8_t *p_buff,��������ݡ�
			   uint32_t buff_len ����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : Ŀǰû��

*****************************************************************************/
void update_user_boot_write_reg_byte(uint8_t *p_buff,uint32_t buff_len)
{
	#if 0
	uint32_t write_len = 0;
	ErrStatus ret = ERROR;
	uint8_t pcrc[CRC32_RESULT_SIZE];
	uint32_t crc_receive_result = 0;
	uint32_t crc_flash_result = 0;
	uint32_t address = 0;
	
	if(NULL == p_buff || buff_len < 2)
	{
		return;
	}

	if(CMD_UPGRADE_BOOT_SOFTWARE_REG != p_buff[0])
	{
		return;
	}

	if(UPGRADE_APP_START == p_buff[1])
	{
		ret = upate_mem_is_alloc();
		if(ERROR == ret)
		{
			ret = update_mem_malloc();
			if(ERROR == ret)
			{
				printf("update_mem_malloc error\r\n");
			}
			else
			{
				update_mem_all_memset();		
				g_pkt_rx = 0;
				g_pkt_count_to_flash = 0;
				g_page_idx = 0;
				
			}
		}
		else
		{
			update_mem_all_memset();		
			g_pkt_rx = 0;
			g_pkt_count_to_flash = 0;
			g_page_idx = 0;
			
		}

	//	read_update_flag();		
		//printf("XXstart update_flag(%u)\r\n",update_flag);
	}
	
	
	write_len = buff_len - 2; /*��Ч����*/
	g_pkt_rx += write_len;	/*���ڷ��գ�����·�ΪCRCʱҲ�����ӳ���*/	

	ret = upate_mem_is_alloc();
	if(ERROR == ret)
	{
		return;
	}

	/* modify by fz, 20230829, ԭ��:�����жϣ�ֻ�����·��ļ�ʱ�Ż��浽���� */
	if(UPGRADE_APP_END == p_buff[1] || UPGRADE_APP_DOING == p_buff[1])
	{
		/*���ڷ��գ�����·�ΪCRCʱҲ�Ỻ�浽�ѿռ�*/	
		ret = comm_update_write_mem_one_page_to_flash(USERBOOTADDRESS,
			&p_buff[2],write_len);
	}
	
	if(UPGRADE_APP_END == p_buff[1])
	{
		comm_update_write_to_flash(USERBOOTADDRESS);
		printf("receive pkts(%u),pkt_to_flash(%u),page(%u)\r\n",
			g_pkt_rx,
			g_pkt_count_to_flash,
			g_page_idx);		
		
	}

	/* add by fz, 20230829, ԭ��:�·�crcʱ���û��浽���� */
	if(UPGRADE_CRC_END == p_buff[1] && buff_len >= 6)
	{
		memset(pcrc,0,sizeof(pcrc));
		memcpy(&pcrc,&p_buff[2], sizeof(pcrc));
		crc_receive_result = get_u32(pcrc);
		
		printf("crc_receive_result:0x%x\r\n",crc_receive_result);
		
		om_crc32_reset();

		//read_update_flag();		

		printf("write to address:0x%x, pkt_len:%u\r\n",USERBOOTADDRESS,g_pkt_count_to_flash);
		crc_flash_result = om_flash_block_data_calculate_crc32(USERBOOTADDRESS,g_pkt_count_to_flash);
		printf("crc_flash_result:0x%x\r\n",crc_flash_result);	

		if(crc_receive_result != crc_flash_result)
		{
			printf("crc error !\r\n");
		}
		
		update_mem_all_memset();		
		g_pkt_rx = 0;
		g_pkt_count_to_flash = 0;
		g_page_idx = 0;
	   
	}
	
	return;
#endif	
}




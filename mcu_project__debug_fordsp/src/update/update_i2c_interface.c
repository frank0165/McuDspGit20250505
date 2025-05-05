/***********************************************************************************

 * 文 件 名   : update_i2c_interface.c
 * 负 责 人   : fz
 * 创建日期   : 2025年1月16日
 * 文件描述   : 升级功能的i2c接口实现
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

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
 * 函 数 名  : update_app_write_reg_byte
 * 负 责 人  : fz
 * 创建日期  : 2023年8月24日
 * 函数功能  : mcu应用程序升级
 * 输入参数  : uint8_t *p_buff,传入的数据。
                       p_buff[0]:UPGRADE_APP_SOFTWARE_REG
                       p_buff[1]:UPGRADE_APP_DOING,正在传输文件
                       			UPGRADE_APP_END，传输文件结束
                       			UPGRADE_CRC_END，传办CRC
 				uint32_t buff_len
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

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

/* add by fz, 20250116, 原因:关闭轮询开关 */
	tec_set_default_mini_status();

	g_mcu_vars_param.g_ddm_sw_auto_process_flag = RESET;	
	g_mcu_vars_param.g_50g_ddm_sw_auto_process_flag = RESET;
	g_mcu_vars_param.g_10g_ddm_sw_auto_process_flag = RESET;
	g_mcu_vars_param.g_1g_ddm_sw_auto_process_flag = RESET;
	
	if(UPGRADE_APP_START == p_buff[1])
	{
		/* add by fz, 20250303, 原因:接收升级命令就置为set,停止ddm轮询 */
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
	write_len = buff_len - idx; /*有效长度*/
	g_pkt_rx += write_len;	/*存在风险，如果下发为CRC时也会增加长度*/	

	ret = upate_mem_is_alloc();
	if(ERROR == ret)
	{
	
		g_crc_is_ok = CRC_MALLOC_FAIL;
		return;
	}

	/* modify by fz, 20230829, 原因:增加判断，只有在下发文件时才缓存到堆区 */
	if(UPGRADE_APP_END == p_buff[1] || UPGRADE_APP_DOING == p_buff[1])
	{
		/*存在风险，如果下发为CRC时也会缓存到堆空间*/	
		ret = comm_update_write_mem_one_page_to_flash(BAPPLICATIONADDRESS,
			&p_buff[idx],write_len);
	}
	
	if(UPGRADE_APP_END == p_buff[1])
	{
		comm_update_write_to_flash(BAPPLICATIONADDRESS);
		
	}

	/* add by fz, 20230829, 原因:下发crc时不用缓存到堆区 */
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
 * 函 数 名  : update_firmware_write_reg_byte
 * 负 责 人  : fz
 * 创建日期  : 2023年11月6日
 * 函数功能  : 光模块的firmware升级
 * 输入参数  : uint8_t *p_buff,传入的数据。
			   uint32_t buff_len 长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

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
		/* add by fz, 20250303, 原因:接收升级命令就置为set,停止ddm轮询 */
		g_mcu_vars_param.g_update_process_flag = SET; 
		
		ret = upate_mem_is_alloc();
		if(ERROR == ret)
		{
			ret = update_mem_malloc();
			if(ERROR == ret)
			{
			    /*malloc失败，打印提示*/
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
	
	
	write_len = buff_len - 2; /*有效长度*/
	g_pkt_rx += write_len;	/*存在风险，如果下发为CRC时也会增加长度*/	

	ret = upate_mem_is_alloc();
	if(ERROR == ret)
	{
	    g_crc_is_ok = CRC_MALLOC_FAIL;
		return;
	}

	/* modify by fz, 20230829, 原因:增加判断，只有在下发文件时才缓存到堆区 */
	if(UPGRADE_APP_END == p_buff[1] || UPGRADE_APP_DOING == p_buff[1])
	{
		/*存在风险，如果下发为CRC时也会缓存到堆空间*/	
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

	/* add by fz, 20230829, 原因:下发crc时不用缓存到堆区 */
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
 * 函 数 名  : upgrade_dev_version_reg_read
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月21日
 * 函数功能  : 读取升级完后的设备信息
 * 输入参数  : uint8_t regaddr 寄存器
              uint32_t  bufflen pbuff的长度，I2C_SLAVE_WRITE_READ_MAX
 * 输出参数  : uint8_t *pbuff 实际返回的值
 * 返 回 值  : 无
 * 调用关系  : 上位机i2c调用
 * 其    它  : 返回值的总长度不能超过I2C_SLAVE_WRITE_READ_MAX

*****************************************************************************/
void upgrade_dev_version_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
	/*参数初始化*/
	uint8_t tmp[80];
	uint32_t offset = 0;

	/*从App区的第63页读取boot编译信息*/
	//uint32_t dst_addr = AAPPLICATIONADDRESS + 63 * FLASH_PAGE_SIZE;
	
	/* add by fz, 20230625, 原因:参数合法值检查 */
	if(UPGRADE_DEV_VERSION_INFO_REG != regaddr)
	{
		return;
	}

	if(NULL == pbuff)
	{
		return;
	}

	memset(tmp,0,sizeof(tmp));	
	
	
	//date:12字节
	memcpy(&tmp[offset],__DATE__,12);
	offset += 12;

	//time: 9字节
	memcpy(&tmp[offset],__TIME__,9);
	offset += 9;
	
	//工作区1字节
	read_update_flag();
	tmp[offset] = update_flag;
	offset += 1;

	/*读取CRC校验结果*/
	tmp[offset] = g_crc_is_ok;
	offset += 1;

    /*trigger产生次数，调试使用*/
	set_u32(&tmp[offset],g_mcu_vars_param.g_trigger_count);
	offset += 4; //综上共27个字节	小于I2C_SLAVE_WRITE_READ_MAX
	
	memcpy(pbuff,tmp,sizeof(tmp));	

	
}


/*****************************************************************************
 * 函 数 名  : update_user_boot_write_reg_byte
 * 负 责 人  : fz
 * 创建日期  : 2023年11月6日
 * 函数功能  : 光模块的firmware升级
 * 输入参数  : uint8_t *p_buff,传入的数据。
			   uint32_t buff_len 长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 目前没用

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
	
	
	write_len = buff_len - 2; /*有效长度*/
	g_pkt_rx += write_len;	/*存在风险，如果下发为CRC时也会增加长度*/	

	ret = upate_mem_is_alloc();
	if(ERROR == ret)
	{
		return;
	}

	/* modify by fz, 20230829, 原因:增加判断，只有在下发文件时才缓存到堆区 */
	if(UPGRADE_APP_END == p_buff[1] || UPGRADE_APP_DOING == p_buff[1])
	{
		/*存在风险，如果下发为CRC时也会缓存到堆空间*/	
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

	/* add by fz, 20230829, 原因:下发crc时不用缓存到堆区 */
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




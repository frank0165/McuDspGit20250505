/***********************************************************************************

 * 文 件 名   : ddm_sff_i2c_interface.c
 * 负 责 人   : fz
 * 创建日期   : 2025年1月15日
 * 文件描述   : sff 8472的i2c接口
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#include "ddm_sff_i2c_interface.h"
#include "sff_8472.h"
#include "mcu_system_comm.h"
#include "ddm_50g_config_interface.h"
#include "ddm_10g_config_interface.h"
#include "ddm_1g_config_interface.h"
#include "mcu_global_vars_param.h"


/*****************************************************************************
 * 函 数 名  : om_flash_write_reg_byte
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月21日
 * 函数功能  : 写表到flash
 * 输入参数  : uint32_t slave_addr, 设置地址,A0,B0,C0;A2,B2,C2
             uint8_t *p_buff, 要写的内容,第一个字节是寄存器
                uint32_t buff_len p_buff的长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 

*****************************************************************************/
void om_flash_write_reg_byte(uint32_t slave_addr,uint8_t *p_buff,uint32_t buff_len)
{
	uint16_t i;
	uint32_t new_addr;
	uint8_t offset = *p_buff;

	if(slave_addr == 0xa0){
		fmc_erase_single_page(A0_REG_ADDRESS);
		new_addr = A0_REG_ADDRESS;
		for(i= 0; i < buff_len-1;i++)
		{	
			
			a0[i+offset] = *(p_buff + i + 1);
		}

		flash_write((uint8_t*)a0,new_addr,OM_TABLE_SFF_8472_DATA_LEN);
	}
	else if(slave_addr == 0xa2){
		//判断上位机或线卡是否把A2表寄存器0x6e的bit6位置修改为1
		if(offset == 0x6e){
			uint8_t state_flag = *(p_buff + 1);
			if(state_flag & 0x40){ //协议中高位为关闭
				//gn7161_soft_txdsbl_ctrl(1);
				//sgm41295_ld_ctrl(0);
				/*这个函数0为关闭*/
				ddm_50g_soft_txdsbl_ctrl(0);
			}
			else{
				//gn7161_soft_txdsbl_ctrl(0);
				//sgm41295_ld_ctrl(1);
				ddm_50g_soft_txdsbl_ctrl(1);
			}

		}
		else{
			fmc_erase_single_page(A2_REG_ADDRESS);
			new_addr = A2_REG_ADDRESS;
			for(i= 0; i < buff_len-1;i++)
			{	
				a2[i+offset] = *(p_buff + i + 1);
			}
			flash_write((uint8_t*)a2,new_addr,OM_TABLE_SFF_8472_DATA_LEN);
		}
		
	}
	else if(slave_addr == 0xb0){
		fmc_erase_single_page(B0_REG_ADDRESS);
		new_addr = B0_REG_ADDRESS;
		for(i= 0; i < buff_len-1;i++)
		{	
			b0[i+offset] = *(p_buff + i + 1);
		}
		flash_write((uint8_t*)b0,new_addr,OM_TABLE_SFF_8472_DATA_LEN);
	}
	else if(slave_addr == 0xb2){
		//判断上位机或线卡是否把B2表寄存器0x6e的bit6位置修改为1
		if(offset == 0x6e){
			uint8_t state_flag = *(p_buff + 1);
			if(state_flag & 0x40){
				//gn7153_soft_txdsbl_ctrl(1);
				ddm_10g_soft_txdsbl_ctrl(0);
			}
			else{
				//gn7153_soft_txdsbl_ctrl(0);
				ddm_10g_soft_txdsbl_ctrl(1);
			}

		}
		else{
			fmc_erase_single_page(B2_REG_ADDRESS);
			new_addr = B2_REG_ADDRESS;
			for(i= 0; i < buff_len-1;i++)
			{	
				b2[i+offset] = *(p_buff + i + 1);
			}
			flash_write((uint8_t*)b2,new_addr,OM_TABLE_SFF_8472_DATA_LEN);
		}
	}
	else if(slave_addr == 0xc0){
		fmc_erase_single_page(C0_REG_ADDRESS);
		new_addr = C0_REG_ADDRESS;
		for(i= 0; i < buff_len-1;i++)
		{	
			c0[i+offset] = *(p_buff + i + 1);
		}
		flash_write((uint8_t*)c0,new_addr,OM_TABLE_SFF_8472_DATA_LEN);
	}
	else if(slave_addr == 0xc2){
		//判断上位机或线卡是否把C2表寄存器0x6e的bit6位置修改为1
		if(offset == 0x6e){
			uint8_t state_flag = *(p_buff + 1);
			if(state_flag & 0x40){
				//ux3326_soft_txdsbl_ctrl(1);
				ddm_1g_soft_txdsbl_ctrl(0);
			}
			else{
				ddm_1g_soft_txdsbl_ctrl(1);
			}

		}
		else{
			fmc_erase_single_page(C2_REG_ADDRESS);
			new_addr = C2_REG_ADDRESS;
			for(i= 0; i < buff_len-1;i++)
			{	
				c2[i+offset] = *(p_buff + i + 1);
			}
			flash_write((uint8_t*)c2,new_addr,OM_TABLE_SFF_8472_DATA_LEN);
		}
	}
	return;
}


/*****************************************************************************
 * 函 数 名  : om_memory_state_ctrl_write_reg_byte
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月21日
 * 函数功能  : 写状态表到临时内存
 * 输入参数  :  uint32_t slave_addr, 设置地址,A0,B0,C0;A2,B2,C2
             uint8_t *p_buff, 要写的内容,第一个字节是寄存器
                uint32_t buff_len p_buff的长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 上位机测试使用

*****************************************************************************/
void om_memory_state_ctrl_write_reg_byte(uint32_t slave_addr,uint8_t *p_buff,uint32_t buff_len)
{
	uint16_t i;
	uint8_t offset = *p_buff;

	if(slave_addr == I2C_8472_MEM_A2_ADDR){
		for(i= 0; i < buff_len-1;i++)
		{	
			a2[i+offset] = *(p_buff + i + 1);
		}

	}
	else if(slave_addr == I2C_8472_MEM_B2_ADDR){
		for(i= 0; i < buff_len-1;i++)
		{	
			b2[i+offset] = *(p_buff + i + 1);
		}

	}
	else if(slave_addr == I2C_8472_MEM_C2_ADDR){
		for(i= 0; i < buff_len-1;i++)
		{	
			c2[i+offset] = *(p_buff + i + 1);
		}

	}
	
	//state_flag: 0-使能，1-去使能
	//判断上位机或线卡是否把A2表寄存器0x6e的bit6位置修改为1
	if((slave_addr == I2C_8472_MEM_A2_ADDR) && ((*p_buff) == 0x6e)){
		uint8_t state_flag = *(p_buff + 1);
		if(state_flag & 0x40){
			//gn7161_soft_txdsbl_ctrl(1);
			//sgm41295_ld_ctrl(0);
			ddm_50g_soft_txdsbl_ctrl(0);
		}
		else{
			//gn7161_soft_txdsbl_ctrl(0);
			//sgm41295_ld_ctrl(1);
			ddm_50g_soft_txdsbl_ctrl(1);
		}
	}
	//判断上位机或线卡是否把B2表寄存器0x6e的bit6位置修改为1
	if((slave_addr == I2C_8472_MEM_B2_ADDR) && ((*p_buff) == 0x6e)){
		uint8_t state_flag = *(p_buff + 1);
		if(state_flag & 0x40){
			//gn7153_soft_txdsbl_ctrl(1);
			ddm_10g_soft_txdsbl_ctrl(0);
		}
		else{
			//gn7153_soft_txdsbl_ctrl(0);
			ddm_10g_soft_txdsbl_ctrl(1);
		}
	}
	//判断上位机或线卡是否把C2表寄存器0x6e的bit6位置修改为1
	if((slave_addr == I2C_8472_MEM_C2_ADDR) && ((*p_buff) == 0x6e)){
		uint8_t state_flag = *(p_buff + 1);
		if(state_flag & 0x40){
			//ux3326_soft_txdsbl_ctrl(1);
			//ux3326软件使能反接
			ddm_1g_soft_txdsbl_ctrl(0); 
		}
		else{
			//ux3326_soft_txdsbl_ctrl(0);
			ddm_1g_soft_txdsbl_ctrl(1);
		}
	}
	
	return;
}



/*****************************************************************************
 * 函 数 名  : om_v2_flash_read_reg_byte
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月21日
 * 函数功能  : 从flash区中读取flash--以表形式保存
 * 输入参数  : I2C_ALL_ADDRESS_INFO *p_address_info  地址及寄存信息
                uint32_t buff_len p_buff的长度:I2C_SLAVE_WRITE_READ_MAX
 * 输出参数  : p_buff 实际表的数据
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void om_v2_flash_read_reg_byte(I2C_ALL_ADDRESS_INFO *p_address_info,uint8_t *p_buff,uint32_t buff_len)
{
	uint32_t addr_start;
	uint16_t i;
	uint32_t slave_addr = 0;
	uint8_t reg_address = 0;
	uint32_t len = 0;
	if(NULL == p_address_info || NULL == p_buff)
	{
		return;
	}

	if(1 != p_address_info->reg_size)
	{
		return;
	}
	slave_addr = p_address_info->slave_address;
	reg_address = p_address_info->regaddress[0];
	len = OM_TABLE_SFF_8472_DATA_LEN - reg_address;
	if(len > OM_TABLE_SFF_8472_DATA_LEN)
	{
		len = OM_TABLE_SFF_8472_DATA_LEN;
	}
	
	if(slave_addr == 0xa0){
		addr_start = A0_REG_ADDRESS + (uint32_t)reg_address;
		flash_read(p_buff,addr_start,len);
	}
	else if(slave_addr == 0xa2){
		addr_start = A2_REG_ADDRESS + (uint32_t)reg_address;
		flash_read(p_buff,addr_start,len);//从flash读取
		/*更新DDM物理量实时值，从内存中读取*/
		if((reg_address >= OM_A2_ADDR_TEMPERATURE)&&(reg_address <=OM_A2_ADDR_RXPOWER+1)){
			*p_buff = a2[reg_address];
		}
	}
	else if(slave_addr == 0xb0){
		addr_start = B0_REG_ADDRESS + (uint32_t)reg_address;
		flash_read(p_buff,addr_start,len);
	}
	else if(slave_addr == 0xb2){
		addr_start = B2_REG_ADDRESS + (uint32_t)reg_address;
		flash_read(p_buff,addr_start,len);
		/*更新DDM物理量实时值*/
		if((reg_address >= OM_A2_ADDR_TEMPERATURE)&&(reg_address <=OM_A2_ADDR_RXPOWER+1)){
			*p_buff = b2[reg_address];
		}
	}
	else if(slave_addr == 0xc0){
		addr_start = C0_REG_ADDRESS + (uint32_t)reg_address;
		flash_read(p_buff,addr_start,len);
	}
	else if(slave_addr == 0xc2){
		addr_start = C2_REG_ADDRESS + (uint32_t)reg_address;
		flash_read(p_buff,addr_start,len);
		/*更新DDM物理量实时值*/
		if((reg_address >= OM_A2_ADDR_TEMPERATURE)&&(reg_address <=OM_A2_ADDR_RXPOWER+1)){
			*p_buff = c2[reg_address];
		}
	}
	return;
}


/***********************************************************************
	** 函 数 名： om_cmd_ddm_read_reg_byte
	** 输    入： uint8_t regaddr 寄存器首地址
				  uint8_t *p_buff 缓冲地址
				  uint32_t buff_len 偏移量 
	** 输    出： 无
	** 返 回 值： 无
	** 功能描述： ddm物理量虚拟寄存器数值读取
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void om_cmd_ddm_read_reg_byte(uint8_t regaddr, uint8_t *pbuff, uint32_t bufflen)
{
	if(CMD_MODULE_DDM_INFO_REG != regaddr)
	{
		return;
	}
	
	if(NULL == pbuff || bufflen < 15)
	{
		return;
	}
	uint16_t i;
	uint8_t adc_val[2];
	set_u16(adc_val, ddm_adc_out_val.temperature_adc_out);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}
	
	set_u16(adc_val, ddm_adc_out_val.voltage_adc_out_0);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}
	
	set_u16(adc_val, ddm_adc_out_val.ibias_adc_out_0);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}
	
	set_u16(adc_val, ddm_adc_out_val.tx_power_adc_out_0);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}
	
	set_u16(adc_val, ddm_adc_out_val.rx_power_adc_out_0);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}

	set_u16(adc_val, ddm_adc_out_val.temperature_adc_out);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}

	set_u16(adc_val, ddm_adc_out_val.voltage_adc_out_1);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}
	
	set_u16(adc_val, ddm_adc_out_val.ibias_adc_out_1);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}
	
	set_u16(adc_val, ddm_adc_out_val.tx_power_adc_out_1);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}
	
	set_u16(adc_val, ddm_adc_out_val.rx_power_adc_out_1);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}

	set_u16(adc_val, ddm_adc_out_val.temperature_adc_out);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}
	set_u16(adc_val, ddm_adc_out_val.voltage_adc_out_2);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}
	
	set_u16(adc_val, ddm_adc_out_val.ibias_adc_out_2);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}
	
	set_u16(adc_val, ddm_adc_out_val.tx_power_adc_out_2);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}
	
	set_u16(adc_val, ddm_adc_out_val.rx_power_adc_out_2);
	for(i = 0U; i < 2; i++){
		*pbuff = adc_val[i];
		pbuff++;
	}

}

/***********************************************************************
	** 函 数 名： om_memory_read_reg_byte
	** 输    入：I2C_ALL_ADDRESS_INFO *p_address_info 地址信息
				uint32_t buff_len p_buff的长度							
								
	** 输    出： uint8_t *p_buff 从内存中读取a0,b0,c0,a2,b2,c2
	** 返 回 值： 无
	** 功能描述： 虚拟寄存器数值读取
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void om_v2_memory_read_reg_byte(I2C_ALL_ADDRESS_INFO *p_address_info,uint8_t *p_buff,uint32_t buff_len)
{
	uint32_t addr_start;
	uint16_t i;
	uint32_t slave_addr = 0;
	uint8_t reg_address = 0;
	uint32_t len = 0;
	if(NULL == p_address_info || NULL == p_buff)
	{
		return;
	}

	if(1 != p_address_info->reg_size)
	{
		return;
	}
	slave_addr = p_address_info->slave_address;
	reg_address = p_address_info->regaddress[0];
	len = 255 - reg_address;
	
	if(slave_addr == I2C_8472_MEM_A0_ADDR){
		addr_start = reg_address;
		for(i = 0U; i < len; i++){
			*p_buff = a0[addr_start+i];
			p_buff++;
		}
	}
	else if(slave_addr == I2C_8472_MEM_A2_ADDR){
		addr_start = reg_address;
		for(i = 0U; i < len; i++){
			*p_buff = a2[addr_start+i];
			p_buff++;
		}
	}
	else if(slave_addr == I2C_8472_MEM_B0_ADDR){
		addr_start = reg_address;
		for(i = 0U; i < len; i++){
			*p_buff = b0[addr_start+i];
			p_buff++;
		}
	}
	else if(slave_addr == I2C_8472_MEM_B2_ADDR){
		addr_start = reg_address;
		for(i = 0U; i < len; i++){
			*p_buff = b2[addr_start+i];
			p_buff++;
		}
	}
	else if(slave_addr == I2C_8472_MEM_C0_ADDR){
		addr_start = reg_address;
		for(i = 0U; i < len; i++){
			*p_buff = c0[addr_start+i];
			p_buff++;
		}
	}
	else if(slave_addr == I2C_8472_MEM_C2_ADDR){
		addr_start = reg_address;
		for(i = 0U; i < len; i++){
			*p_buff = c2[addr_start+i];
			p_buff++;
		}
	}
	return;
}


/***********************************************************************
	** 函 数 名： om_save_data_config_flash_write
	** 输    入： uint8_t *pbuff 寄存器缓存
								uint32_t bufflen 字节长度
	** 输    出： 无
	** 返 回 值： 无
	** 功能描述： 设置收端deemph值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void om_save_data_config_flash_write(uint8_t *pbuff,uint32_t bufflen)
{

	if(NULL == pbuff || bufflen < 2)
	{
		return;
	}

	if(CFG_SAVE_FLASH_EX != pbuff[1] || CMD_COMMAND_MAP_REG != pbuff[0])
	{
		return;
	}
	
	fmc_erase_single_page(CONFIGADDRESS);
	flash_write((uint8_t*)default_config_value,CONFIGADDRESS,sizeof(default_config_value));

	return;	
}

/*****************************************************************************
 * 函 数 名  : om_erase_data_config_flash_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : 清除flash数据
 * 输入参数  : uint8_t *pbuff 寄存器缓存
			uint32_t bufflen 字节长度
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void om_erase_data_config_flash_write(uint8_t *pbuff,uint32_t bufflen)
{

	if(NULL == pbuff || bufflen < 2)
	{
		return;
	}

	if(CFG_CLEAR_FLASH_EX != pbuff[1] || CMD_COMMAND_MAP_REG != pbuff[0])
	{
		return;
	}
	
	fmc_erase_single_page(CONFIGADDRESS);
	return;	
	
}

/*****************************************************************************
 * 函 数 名  : cfg_v2_flash_read_reg_byte
 * 负 责 人  : fz
 * 创建日期  : 2025年1月3日
 * 函数功能  : mcu的slave的特殊地址:0xA8的读功能，用于读取保存的配置
 * 输入参数  : uint32_t slave_addr  slave地址.
 				uint8_t regaddress  寄存器值 				
 				uint32_t buffer_len 数据的长度
 * 输出参数  : uint8_t* p_buffer	读取的数据
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 本函数只处理设备地址 0xA8，其它的设备地址不处理。

*****************************************************************************/
void cfg_v2_flash_read_reg_byte(I2C_ALL_ADDRESS_INFO *p_address_info,
		uint8_t *p_buff,uint32_t buff_len)
{
	uint32_t addr_start = 0;
	uint16_t i = 0;	
	uint32_t slave_addr = 0;
	uint8_t reg_address = 0;
	uint32_t len = 0;
	if(NULL == p_address_info || NULL == p_buff)
	{
		return;
	}

	if(1 != p_address_info->reg_size)
	{
		return;
	}
	slave_addr = p_address_info->slave_address;
	reg_address = p_address_info->regaddress[0];
	len = HMI_CFG_FLASH_LEN - reg_address;
	if(len > HMI_CFG_FLASH_LEN)
	{
		len = HMI_CFG_FLASH_LEN;
	}
	
	if(slave_addr == I2C_FLASH_A8_ADDR){
		addr_start = CONFIGADDRESS + (uint32_t)reg_address;
		flash_read(p_buff,addr_start,len);
	}

	return;	
}


/*****************************************************************************
 * 函 数 名  : cmd_common_reg_read
 * 负 责 人  : fz
 * 创建日期  : 2024年10月12日
 * 函数功能  : 通用读功能
 * 输入参数  : uint8_t regaddr 寄存器
 				uint32_t bufflen pbuff的长度
 * 输出参数  : uint8_t *pbuff 实际的flash的配置长度
 * 返 回 值  : 无
 * 调用关系  : 
 * 其    它  : CMD_COMMON_READ_REG = 0x27,

*****************************************************************************/
void cmd_common_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
	
	/* add by fz, 20230625, 原因:参数合法值检查 */
	if(CMD_COMMON_READ_REG != regaddr)
	{
		return;
	}

	if(NULL == pbuff)
	{
		return;
	}

	pbuff[0] = FLASH_CONFIG_LENGTH;

	return;
	
}





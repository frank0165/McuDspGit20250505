/***********************************************************************************

 * �� �� ��   : ddm_sff_i2c_interface.c
 * �� �� ��   : fz
 * ��������   : 2025��1��15��
 * �ļ�����   : sff 8472��i2c�ӿ�
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#include "ddm_sff_i2c_interface.h"
#include "sff_8472.h"
#include "mcu_system_comm.h"
#include "ddm_50g_config_interface.h"
#include "ddm_10g_config_interface.h"
#include "ddm_1g_config_interface.h"
#include "mcu_global_vars_param.h"


/*****************************************************************************
 * �� �� ��  : om_flash_write_reg_byte
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��21��
 * ��������  : д��flash
 * �������  : uint32_t slave_addr, ���õ�ַ,A0,B0,C0;A2,B2,C2
             uint8_t *p_buff, Ҫд������,��һ���ֽ��ǼĴ���
                uint32_t buff_len p_buff�ĳ���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : 

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
		//�ж���λ�����߿��Ƿ��A2��Ĵ���0x6e��bit6λ���޸�Ϊ1
		if(offset == 0x6e){
			uint8_t state_flag = *(p_buff + 1);
			if(state_flag & 0x40){ //Э���и�λΪ�ر�
				//gn7161_soft_txdsbl_ctrl(1);
				//sgm41295_ld_ctrl(0);
				/*�������0Ϊ�ر�*/
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
		//�ж���λ�����߿��Ƿ��B2��Ĵ���0x6e��bit6λ���޸�Ϊ1
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
		//�ж���λ�����߿��Ƿ��C2��Ĵ���0x6e��bit6λ���޸�Ϊ1
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
 * �� �� ��  : om_memory_state_ctrl_write_reg_byte
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��21��
 * ��������  : д״̬����ʱ�ڴ�
 * �������  :  uint32_t slave_addr, ���õ�ַ,A0,B0,C0;A2,B2,C2
             uint8_t *p_buff, Ҫд������,��һ���ֽ��ǼĴ���
                uint32_t buff_len p_buff�ĳ���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��λ������ʹ��

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
	
	//state_flag: 0-ʹ�ܣ�1-ȥʹ��
	//�ж���λ�����߿��Ƿ��A2��Ĵ���0x6e��bit6λ���޸�Ϊ1
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
	//�ж���λ�����߿��Ƿ��B2��Ĵ���0x6e��bit6λ���޸�Ϊ1
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
	//�ж���λ�����߿��Ƿ��C2��Ĵ���0x6e��bit6λ���޸�Ϊ1
	if((slave_addr == I2C_8472_MEM_C2_ADDR) && ((*p_buff) == 0x6e)){
		uint8_t state_flag = *(p_buff + 1);
		if(state_flag & 0x40){
			//ux3326_soft_txdsbl_ctrl(1);
			//ux3326���ʹ�ܷ���
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
 * �� �� ��  : om_v2_flash_read_reg_byte
 * �� �� ��  : fangzhe
 * ��������  : 2025��3��21��
 * ��������  : ��flash���ж�ȡflash--�Ա���ʽ����
 * �������  : I2C_ALL_ADDRESS_INFO *p_address_info  ��ַ���Ĵ���Ϣ
                uint32_t buff_len p_buff�ĳ���:I2C_SLAVE_WRITE_READ_MAX
 * �������  : p_buff ʵ�ʱ������
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

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
		flash_read(p_buff,addr_start,len);//��flash��ȡ
		/*����DDM������ʵʱֵ�����ڴ��ж�ȡ*/
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
		/*����DDM������ʵʱֵ*/
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
		/*����DDM������ʵʱֵ*/
		if((reg_address >= OM_A2_ADDR_TEMPERATURE)&&(reg_address <=OM_A2_ADDR_RXPOWER+1)){
			*p_buff = c2[reg_address];
		}
	}
	return;
}


/***********************************************************************
	** �� �� ���� om_cmd_ddm_read_reg_byte
	** ��    �룺 uint8_t regaddr �Ĵ����׵�ַ
				  uint8_t *p_buff �����ַ
				  uint32_t buff_len ƫ���� 
	** ��    ���� ��
	** �� �� ֵ�� ��
	** ���������� ddm����������Ĵ�����ֵ��ȡ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
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
	** �� �� ���� om_memory_read_reg_byte
	** ��    �룺I2C_ALL_ADDRESS_INFO *p_address_info ��ַ��Ϣ
				uint32_t buff_len p_buff�ĳ���							
								
	** ��    ���� uint8_t *p_buff ���ڴ��ж�ȡa0,b0,c0,a2,b2,c2
	** �� �� ֵ�� ��
	** ���������� ����Ĵ�����ֵ��ȡ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
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
	** �� �� ���� om_save_data_config_flash_write
	** ��    �룺 uint8_t *pbuff �Ĵ�������
								uint32_t bufflen �ֽڳ���
	** ��    ���� ��
	** �� �� ֵ�� ��
	** ���������� �����ն�deemphֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
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
 * �� �� ��  : om_erase_data_config_flash_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : ���flash����
 * �������  : uint8_t *pbuff �Ĵ�������
			uint32_t bufflen �ֽڳ���
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

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
 * �� �� ��  : cfg_v2_flash_read_reg_byte
 * �� �� ��  : fz
 * ��������  : 2025��1��3��
 * ��������  : mcu��slave�������ַ:0xA8�Ķ����ܣ����ڶ�ȡ���������
 * �������  : uint32_t slave_addr  slave��ַ.
 				uint8_t regaddress  �Ĵ���ֵ 				
 				uint32_t buffer_len ���ݵĳ���
 * �������  : uint8_t* p_buffer	��ȡ������
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ������ֻ�����豸��ַ 0xA8���������豸��ַ������

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
 * �� �� ��  : cmd_common_reg_read
 * �� �� ��  : fz
 * ��������  : 2024��10��12��
 * ��������  : ͨ�ö�����
 * �������  : uint8_t regaddr �Ĵ���
 				uint32_t bufflen pbuff�ĳ���
 * �������  : uint8_t *pbuff ʵ�ʵ�flash�����ó���
 * �� �� ֵ  : ��
 * ���ù�ϵ  : 
 * ��    ��  : CMD_COMMON_READ_REG = 0x27,

*****************************************************************************/
void cmd_common_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
	
	/* add by fz, 20230625, ԭ��:�����Ϸ�ֵ��� */
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





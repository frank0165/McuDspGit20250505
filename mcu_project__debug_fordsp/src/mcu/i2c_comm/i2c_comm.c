
#include <string.h>

#include "i2c_comm.h"
#include "i2c_driver.h"

#include "mcu_data_type.h"
#include "mcu_pin_type.h"
#include "mcu_system_comm.h"


/*************************************************************************
* �������ܣ����mcu�豸��ַ��д����
* ȡֵ��Χ������MCU_REGADDR_CALLBACK_ITEMS
* ע�������
*************************************************************************/
MCU_REGADDR_WRITE_CALLBACK_HANDLE 
g_mcu_addr0xspec_reg_write_callback_array[MCU_REGADDR_CALLBACK_ITEMS];

/*************************************************************************
* �������ܣ�g_mcu_addr0xspec_reg_write_callback_array�����±�
* ȡֵ��Χ������MCU_REGADDR_CALLBACK_ITEMS
* ע�������
*************************************************************************/
uint32_t g_mcu_addr0xspec_reg_write_idx = 0;

/*************************************************************************
* �������ܣ����mcu�豸��ַ�Ķ�����
* ȡֵ��Χ������MCU_REGADDR_CALLBACK_ITEMS
* ע�������
*************************************************************************/
MCU_REGADDR_READ_CALLBACK_HANDLE 
g_mcu_addr0xspec_reg_read_callback_array[MCU_REGADDR_CALLBACK_ITEMS];

/*************************************************************************
* �������ܣ�g_mcu_addr0xspec_reg_read_callback_array�����±�
* ȡֵ��Χ������MCU_REGADDR_CALLBACK_ITEMS
* ע�������
*************************************************************************/
uint32_t g_mcu_addr0xspec_reg_read_idx = 0;






/*****************************************************************************
 * �� �� ��  : i2c_config_init
 * �� �� ��  : fz
 * ��������  : 2023��7��19��
 * ��������  : i2c��ʼ������
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : 

*****************************************************************************/
void i2c_config_init()
{
    i2c_global_param_init();
    memset(g_mcu_addr0xspec_reg_write_callback_array,0,
		sizeof(g_mcu_addr0xspec_reg_write_callback_array));
    
	gpio_slave_i2c_config_init();
	gpio_master_i2c_config_init();

	user_optical_pwd_limit_init();
	slave_i2c_config_init();
	master_i2c_config_init();	

	
	
}



/*****************************************************************************
 * �� �� ��  : mcu_register_reg_addr_write_callback
 * �� �� ��  : fz
 * ��������  : 2023��5��18��
 * ��������  :i2c slave�µ� �Ĵ�����ַ��д�ص�����
 * �������  : uint8_t reg_addr  �Ĵ�����ַ
 				MCU_REGADDR_WRITE_CALLBACK write_callback  ��Ӧд�ӿں���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void mcu_register_reg_addr_write_callback(uint8_t reg_addr,	
				MCU_REGADDR_WRITE_CALLBACK write_callback)
{
	uint32_t i = 0;
	for(i = 0; i < g_mcu_addr0xspec_reg_write_idx;i++)
	{
		if(reg_addr == g_mcu_addr0xspec_reg_write_callback_array[i].reg_addr)
		{
			return;
		}
	}

   
	if(g_mcu_addr0xspec_reg_write_idx < MCU_REGADDR_CALLBACK_ITEMS)
	{
		g_mcu_addr0xspec_reg_write_callback_array[g_mcu_addr0xspec_reg_write_idx].callback = write_callback;
		g_mcu_addr0xspec_reg_write_callback_array[g_mcu_addr0xspec_reg_write_idx].reg_addr = 
				reg_addr;
		g_mcu_addr0xspec_reg_write_idx++;
	}

	return;
	
}


/*****************************************************************************
 * �� �� ��  : mcu_register_reg_addr_read_callback
 * �� �� ��  : fz
 * ��������  : 2023��5��18��
 * ��������  : i2c slave�µ� �Ĵ�����ַ�Ķ��ص�����
 * �������  : uint8_t reg_addr  �Ĵ�����ַ
 				MCU_REGADDR_READ_CALLBACK read_callback  ��Ӧ���ӿں���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void mcu_register_reg_addr_read_callback(uint8_t reg_addr,	
			MCU_REGADDR_READ_CALLBACK read_callback)
{
	uint32_t i = 0;
	for(i = 0; i < g_mcu_addr0xspec_reg_read_idx;i++)
	{
		if(reg_addr == g_mcu_addr0xspec_reg_read_callback_array[i].reg_addr)
		{
			return;
		}
	}

	if(g_mcu_addr0xspec_reg_read_idx < MCU_REGADDR_CALLBACK_ITEMS)
	{
		g_mcu_addr0xspec_reg_read_callback_array[g_mcu_addr0xspec_reg_read_idx].callback = 
		read_callback;
		g_mcu_addr0xspec_reg_read_callback_array[g_mcu_addr0xspec_reg_read_idx].reg_addr = 
				reg_addr;
		g_mcu_addr0xspec_reg_read_idx++;
	}

	return;
	
}





/*****************************************************************************
 * �� �� ��  : mcu_addr0xc0_reg_byte_write
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : mcu��slave�������ַ:0xce��д����
 * �������  : uint32_t slave_addr  slave��ַ.
 				uint8_t* p_buffer	Ҫд�������
 				uint32_t buffer_len ���ݵĳ���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ������ֻ�����豸��ַ 0xce���������豸��ַ������

*****************************************************************************/
void mcu_addr0xspec_reg_byte_write(uint32_t slave_addr,
									uint8_t* p_buffer, 
									uint32_t buffer_len	)
{
	uint8_t reg = 0;
	uint32_t i = 0;
	if(I2C_MCU_SPEC_ADDR != slave_addr)
	{
		return;
	}
	if(NULL == p_buffer || buffer_len < 2)
	{
		return;
	}

	reg |= *p_buffer;

	for(i = 0; i < g_mcu_addr0xspec_reg_write_idx;i++)
	{
		if(reg == g_mcu_addr0xspec_reg_write_callback_array[i].reg_addr)
		{
			break;
		}
	}

	if(i < g_mcu_addr0xspec_reg_write_idx)
	{
		g_mcu_addr0xspec_reg_write_callback_array[i].callback(p_buffer,buffer_len);
	}

	return;
	
}


/*****************************************************************************
 * �� �� ��  : mcu_addr0xspec_1byte_reg_byte_read
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : mcu��slave�������ַ:0xce�Ķ�����
 * �������  : uint32_t slave_addr  slave��ַ.
 				uint8_t regaddress  1���ֽڼĴ���ֵ 				
 				uint32_t buffer_len ���ݵĳ���
 * �������  : uint8_t* p_buffer	��ȡ������
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ������ֻ�����豸��ַ 0xce���������豸��ַ������

*****************************************************************************/
void mcu_addr0xspec_1byte_reg_byte_read(uint32_t slave_address,uint8_t 
				regaddress,uint8_t *p_buff,uint32_t buff_len)
{
	
	uint32_t i = 0;
	if(I2C_MCU_SPEC_ADDR != slave_address)
	{
		return;
	}
	if(NULL == p_buff)
	{
		return;
	}

	for(i = 0; i < g_mcu_addr0xspec_reg_read_idx;i++)
	{
		if(regaddress == g_mcu_addr0xspec_reg_read_callback_array[i].reg_addr)
		{
			break;
		}
	}

	if(i < g_mcu_addr0xspec_reg_read_idx)
	{
		g_mcu_addr0xspec_reg_read_callback_array[i].callback(regaddress,p_buff,buff_len);
	}

	
}


/*****************************************************************************
 * �� �� ��  : mcu_addr0xspec_reg_byte_read
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : mcu��slave�������ַ:0xce�Ķ�����
 * �������  : uint32_t slave_addr  slave��ַ.
 				uint8_t regaddress  �Ĵ���ֵ 				
 				uint32_t buffer_len ���ݵĳ���
 * �������  : uint8_t* p_buffer	��ȡ������
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ������ֻ�����豸��ַ 0xce���������豸��ַ������

*****************************************************************************/
void mcu_addr0xspec_reg_byte_read(I2C_ALL_ADDRESS_INFO *p_address_info,
		uint8_t *p_buff,
		uint32_t buff_len)
{
	if(NULL == p_address_info)
	{
		return;
	}

	if(1 == p_address_info->reg_size)
	{
		mcu_addr0xspec_1byte_reg_byte_read(p_address_info->slave_address,p_address_info->regaddress[0],
		p_buff,buff_len);
	}
	return;
}
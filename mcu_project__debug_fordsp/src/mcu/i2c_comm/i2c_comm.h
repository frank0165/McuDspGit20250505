#ifndef _I2C_COMM_H_
#define _I2C_COMM_H_

#include "gd32e501.h"

#include "i2c_opt_ie_interface.h"

/*�ص������鳤��*/
#define MCU_REGADDR_CALLBACK_ITEMS	(44)

/* add by fz, 20230515, ԭ��:i2cд�Ļص��ӿ� ��p_buff�����Ĵ���*/

/*****************************************************************************
 * �� �� ��  : �ص�����--�Ĵ�����ַд�ӿ�
 * �� �� ��  : fz
 * ��������  : 2023��7��17��
 * ��������  : ���豸��ַ����ʱ����Բ�ͬ�Ĵ�����Ӧ�Ļص�����
 * �������  : uint8_t *p_buff     д������ݣ����ֽ�p_buff[0]�ǼĴ���
 			   uint32_t buff_len	p_buff�ĳ���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
typedef void (*MCU_REGADDR_WRITE_CALLBACK)(uint8_t *p_buff,uint32_t buff_len);

/* add by fz, 20230515, ԭ��:i2cд�Ļص��ӿ� ��p_buff�������Ĵ���*/


/*****************************************************************************
 * �� �� ��  : �ص�����--�Ĵ�����ַ���ӿ�
 * �� �� ��  : fz
 * ��������  : 2023��7��17��
 * ��������  :  ���豸��ַ����ʱ����Բ�ͬ�Ĵ�����Ӧ�Ļص�����
 * �������  :  uint8_t regaddress  �Ĵ���
 * �������  : uint8_t *p_buff,   ����������
 				uint32_t buff_len   p_buff�ĳ���
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
typedef void (*MCU_REGADDR_READ_CALLBACK)(uint8_t regaddress,uint8_t *p_buff,uint32_t buff_len);


/* add by fz, 20230515, ԭ��:���mcu�豸��ַ��i2c��д�Ļص����ݽṹ */
typedef struct _MCU_REGADDR_WRITE_CALLBACK_HANDLE_
{
	uint8_t reg_addr;
	MCU_REGADDR_WRITE_CALLBACK callback;
}MCU_REGADDR_WRITE_CALLBACK_HANDLE;


/* add by fz, 20230515, ԭ��:���mcu�豸��ַ��i2c�Ķ��Ļص����ݽṹ */
typedef struct _MCU_REGADDR_READ_CALLBACK_HANDLE_
{
	uint8_t reg_addr;
	MCU_REGADDR_READ_CALLBACK callback;
}MCU_REGADDR_READ_CALLBACK_HANDLE;


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
	MCU_REGADDR_WRITE_CALLBACK write_callback);



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
			MCU_REGADDR_READ_CALLBACK read_callback);



/*****************************************************************************
 * �� �� ��  : mcu_addr0xc0_reg_byte_write
 * �� �� ��  : fz
 * ��������  : 2023��5��15��
 * ��������  : mcu��slave�������ַд����
 * �������  : uint32_t slave_addr  slave��ַ
 				uint8_t* p_buffer	Ҫд�������
 				uint32_t buffer_len ���ݵĳ���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ�ӿ�
 * ��    ��  : ��

*****************************************************************************/
void mcu_addr0xspec_reg_byte_write(uint32_t slave_addr,
									uint8_t* p_buffer, 
									uint32_t buffer_len);

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
		uint32_t buff_len);



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
				regaddress,uint8_t *p_buff,uint32_t buff_len);


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
void i2c_config_init();

#endif

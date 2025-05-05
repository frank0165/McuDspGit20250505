/***********************************************************************************

 * �� �� ��   : i2c_opt_ie_data_type.h
 * �� �� ��   : fangzhe
 * ��������   : 2025��3��23��
 * �ļ�����   : i2cЭ��ջ��������
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#ifndef _I2C_OPT_IE_DATA_TYPE_H_
#define _I2C_OPT_IE_DATA_TYPE_H_

#include "gd32e501.h"
#include "mcu_data_type.h"


#define PRE_LESS_LATER(len1,len2)  ((len1) <= (len2))

#define SLAVE_I2C 							I2C2
#define	SLAVE_EV_IRQn						I2C2_EV_IRQn
#define SLAVE_ER_IRQn						I2C2_ER_IRQn
#define SLAVE_EV_IRQHandler				I2C2_EV_IRQHandler
#define SLAVE_ER_IRQHandler				I2C2_ER_IRQHandler
							

//50G
#define MASTER_A_I2C						I2C1
#define	MASTER_A_EV_IRQn					I2C1_EV_IRQn
#define MASTER_A_ER_IRQn					I2C1_ER_IRQn
#define MASTER_A_EV_IRQHandler				I2C1_EV_IRQHandler
#define MASTER_A_ER_IRQHandler				I2C1_ER_IRQHandler

//10G
#define MASTER_B_I2C						I2C0
#define	MASTER_B_EV_IRQn					I2C0_EV_IRQn
#define MASTER_B_ER_IRQn					I2C0_ER_IRQn
#define MASTER_B_EV_IRQHandler				I2C0_EV_IRQHandler
#define MASTER_B_ER_IRQHandler				I2C0_ER_IRQHandler


#define CHECK_DEV_ERR_I2C(dev_i2c)		(MASTER_A_I2C != dev_i2c && MASTER_B_I2C != dev_i2c)




#define SLAVE_RECEIVE_ADDR()				g_i2c_global_vars.g_receive_address

/* add by fz, 20230515, ԭ��:i2c�ص��ӿ���Ŀ */
#define I2C_CALL_BACK_ITEMS	20

/* add by fz, 20231206, ԭ��:i2c��slave������Ϣ */
typedef struct _I2C_SLAVE_BUFF_CFG_
{
	uint8_t read_flag;	/*i2c��״̬��0-��ʾ��ʼ;1-��ʾ����ʶ;����δ����Ŀǰû�õ�*/
	uint32_t buffer_idx; /*slave_buffer�±�*/
	
	I2C_ALL_ADDRESS_INFO address_info;	/*��ַ������Ϣ*/

	/*����i2c������*/
	uint8_t slave_buffer[I2C_SLAVE_BUFFER_MAX];
	
}I2C_SLAVE_BUFF_CFG;


/*i2c�ض���callback*/
typedef void (*I2C_READ_CFG_CALLBACK)(I2C_ALL_ADDRESS_INFO *p_slave_info,
	uint8_t *p_buff,
	uint32_t buff_len);

/*i2c�ض������ݽṹ*/
typedef struct _I2C_READ_CFG_CALLBACK_HANDLE_
{
	uint32_t slave_address;
	I2C_READ_CFG_CALLBACK callback;
}I2C_READ_CFG_CALLBACK_HANDLE;



				
/*****************************************************************************
 * �� �� ��  : �ص�������I2Cд�ӿ�
 * �� �� ��  : fz
 * ��������  : 2023��7��17��
 * ��������  : i2c��д����
 * �������  : uint32_t slave_address    �豸��ַ
 				uint8_t *p_buff          д������ݣ����ֽ�p_buff[0]�ǼĴ���
 			   uint32_t buff_len		p_buff�ĳ���
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
typedef void (*I2C_WRITE_CFG_CALLBACK)(uint32_t slave_address,uint8_t *p_buff,uint32_t buff_len);



/* add by fz, 20230515, ԭ��:i2c��д�Ļص����ݽṹ */
typedef struct _I2C_WRITE_CFG_CALLBACK_HANDLE_
{
	uint32_t slave_address;
	I2C_WRITE_CFG_CALLBACK callback;
}I2C_WRITE_CFG_CALLBACK_HANDLE;


/* add by fz, 20231206, ԭ��:i2c��master������Ϣ */
typedef struct _I2C_MASTER_BUFF_CFG_
{
	uint8_t read_flag;	/*i2c��״̬��ʶ��0-��ʼ״̬;1-read״̬;2-write״̬*/
	uint32_t buffer_idx; /*master_buffer�±�*/
	
	I2C_ALL_ADDRESS_INFO address_info;	
	uint8_t master_buffer[I2C_MASTER_BUFFER_MAX];
	
}I2C_MASTER_BUFF_CFG;



#define GET_MASTER_CFG_OF_I2C(dev_i2c)		(MASTER_A_I2C == dev_i2c) ? \
									&g_ai2c_master_info_cfg : &g_bi2c_master_info_cfg	

/* add begin by fz, 20230515, ԭ��:�Զ���i2c�ж��е�״̬�¼� */
typedef enum _MCU_I2C_INT_STATUS_
{
	I2C_INT_RBNE_STATUS = 0,
	I2C_INT_TC_STATUS,
	I2C_INT_ADDSEND_STATUS,
	I2C_INT_STPDET_STATUS,
	I2C_INT_TI_STATUS,
	I2C_INT_NACK_STATUS,
	I2C_INT_NON_STATUS,
	I2C_INT_STAT_TR_STATUS
	
}MCU_I2C_INT_STATUS;

/* add by fz, 20231206, ԭ��:i2c��lock */
typedef enum _I2C_LOCK_SEM_
{
	I2C_LOCK_IDLE = RESET,
	I2C_LOCK_BUSY = SET
	
}I2C_LOCK_SEM;

 
/*�趨mcu�ĵ�ַ*/
#define MCU_I2C_ADDRESS7 0x82

/*�趨i2c��slave second��ַ�����Ĵ����ֲ�*/
#define MCU_SECOND_ADDRESS7	0x83




typedef struct _MasterI2cStatus_
{
    uint32_t I2cA_RegAddr;
    uint32_t I2cB_RegAddr;
    union 
    {
        uint32_t I2cStatus;
        struct {
         uint32_t MasterAWork: 1; /*0Ϊwrite,1Ϊread*/
         uint32_t MasterA_Scl: 1;
         uint32_t MasterA_Sda: 1;
         uint32_t MasterA_Irq: 4;
         uint32_t MasterBWork: 1; /*0Ϊwrite,1Ϊread*/
         uint32_t MasterB_Scl: 1;
         uint32_t MasterB_Sda: 1;
         uint32_t MasterB_Irq: 4;     
            }bits;   
    }I2cOp;
}MasterI2cStatus;

#if 0

/*slave���յĵ�ַ*/
volatile uint32_t g_receive_address = 0;

/*************************************************************************
* �������ܣ�i2c slave�ж�ģʽ�У�read handle��ʶ
* ȡֵ��Χ��RESET-readδ������SET-read������
* ע�������
*************************************************************************/
volatile uint8_t g_slave_read_handle_flag = RESET;

/*************************************************************************
* �������ܣ�i2c slave�ж�ģʽ�У�write handle��ʶ
* ȡֵ��Χ��RESET-writeδ������SET-write������
* ע�������
*************************************************************************/
volatile uint8_t g_slave_write_handle_flag = RESET;

/*************************************************************************
* �������ܣ�i2c slave�ж�ģʽ�У�receive handle��ʶ
* ȡֵ��Χ��RESET-receiveδ������SET-receive������
* ע�������
*************************************************************************/
volatile uint8_t g_slave_receive_handle_flag = RESET;

/*************************************************************************
* �������ܣ�i2c slave�ж�ģʽ��, ��ַƥ��ʱ���ô����ʶλ
* ȡֵ��Χ��RESET-��ǰ�ж��д���SET-�ж��⴦���ַƥ�䣻
* ע�������
*************************************************************************/
volatile uint8_t g_slave_address_handle_flag = RESET;

/*************************************************************************
* �������ܣ�i2c�ж�ģʽ�У�write doing 
* ȡֵ��Χ��I2C_LOCK_IDLE-����;I2C_LOCK_BUSY-busy
* ע�������
*************************************************************************/
volatile uint8_t g_write_doing_flag = I2C_LOCK_IDLE;

/*************************************************************************
* �������ܣ�i2c�ж�ģʽ�У�read doing 
* ȡֵ��Χ��I2C_LOCK_IDLE-����;I2C_LOCK_BUSY-busy
* ע�������
*************************************************************************/
volatile uint8_t g_read_doing_flag = I2C_LOCK_IDLE;
#endif

typedef struct _I2C_GLOBAL_VARS_PARAM_
{

    /*slave���յĵ�ַ*/
    uint32_t g_receive_address;
    MasterI2cStatus g_master_i2c_status;
    
    /*master i2c ״���Ƿ���У�SET����,RESET������*/
    uint8_t g_master_i2c_irq_status_pre;// I2C_INT_STPDET_STATUS;//I2C_INT_NON_STATUS;

/*************************************************************************
* �������ܣ�i2c slave�ж�ģʽ�У�read handle��ʶ
* ȡֵ��Χ��RESET-readδ������SET-read������
* ע�������
*************************************************************************/
    uint8_t g_slave_read_handle_flag;

/*************************************************************************
* �������ܣ�i2c slave�ж�ģʽ�У�write handle��ʶ
* ȡֵ��Χ��RESET-writeδ������SET-write������
* ע�������
*************************************************************************/
    uint8_t g_slave_write_handle_flag;

/*************************************************************************
* �������ܣ�i2c slave�ж�ģʽ�У�receive handle��ʶ
* ȡֵ��Χ��RESET-receiveδ������SET-receive������
* ע�������
*************************************************************************/
    uint8_t g_slave_receive_handle_flag;

/*************************************************************************
* �������ܣ�i2c slave�ж�ģʽ��, ��ַƥ��ʱ���ô����ʶλ
* ȡֵ��Χ��RESET-��ǰ�ж��д���SET-�ж��⴦���ַƥ�䣻
* ע�������
*************************************************************************/
    uint8_t g_slave_address_handle_flag;

/*************************************************************************
* �������ܣ�i2c�ж�ģʽ�У�write doing 
* ȡֵ��Χ��I2C_LOCK_IDLE-����;I2C_LOCK_BUSY-busy
* ע�������
*************************************************************************/
    uint8_t g_write_doing_flag;

/*************************************************************************
* �������ܣ�i2c�ж�ģʽ�У�read doing 
* ȡֵ��Χ��I2C_LOCK_IDLE-����;I2C_LOCK_BUSY-busy
* ע�������
*************************************************************************/
    uint8_t g_read_doing_flag;

    /* add by fz, 20231106, ԭ��:��ģ����ʱ�ʶ */
    uint8_t g_user_access_flag;

}I2C_GLOBAL_VARS_PARAM;

#endif
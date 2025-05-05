#include "gd32e501_eval.h"
#include "mcu_data_type.h"
#include "mcu_system_comm.h"
#include <stdint.h>
#include <math.h>
#include "gd32e501_crc.h"

/*DDM���������ADC���ֵ*/
extern volatile DDM_ADC_OUT_VAL ddm_adc_out_val;

/*��ģ��Ĭ�ϲ���*/
extern volatile OM_DEFAULT_CONFIG om_default_config;

/*��ģ������ģʽ*/
extern volatile SFF_MODULE_TYPE sff_module_type;

/*��ģ��Ĭ�ϲ��� */
extern volatile uint8_t default_config_value[FLASH_CONFIG_LENGTH];

/*************************************************************************
* �������ܣ�DDM�Զ���ѯ����
* ȡֵ��Χ��SET or RESET
* ע�������Ӧ����Ĵ���:CMD_DDM_SWITCH_ATUO_PROCESS_REG
*************************************************************************/
/*extern uint8_t g_50g_ddm_sw_auto_process_flag;
extern uint8_t g_10g_ddm_sw_auto_process_flag;
extern uint8_t g_1g_ddm_sw_auto_process_flag;
extern uint8_t g_ddm_sw_auto_process_flag;*/


/* SFF-8472 A0*/
extern volatile uint8_t a0[OM_TABLE_SFF_8472_DATA_LEN];
extern volatile uint8_t a2[OM_TABLE_SFF_8472_DATA_LEN];
extern volatile uint8_t b0[OM_TABLE_SFF_8472_DATA_LEN];
extern volatile uint8_t b2[OM_TABLE_SFF_8472_DATA_LEN];
extern volatile uint8_t c0[OM_TABLE_SFF_8472_DATA_LEN];
extern volatile uint8_t c2[OM_TABLE_SFF_8472_DATA_LEN];


#define FMC_PAGE_SIZE           ((uint16_t)0x400U)
#define FMC_WRITE_START_ADDR    ((uint32_t)0x0807F000U)
#define FMC_WRITE_END_ADDR      ((uint32_t)0x0807FFFFU)

#define OM_A2_TEMP_HIGH_ALARM  0x00
#define OM_A2_TEMP_LOW_ALARM  0x02


#define OM_A2_TEMP_HIGH_WARNING  0x04
#define OM_A2_TEMP_LOW_WARNING  0x06


#define OM_A2_VOLTAGE_HIGH_ALARM  0x08
#define OM_A2_VOLTAGE_LOW_ALARM  0x0A

#define OM_A2_VOLTAGE_HIGH_WARNING  0x0C
#define OM_A2_VOLTAGE_LOW_WARNING  0x0E


#define OM_A2_BIAS_HIGH_ALARM  0x10
#define OM_A2_BIAS_LOW_ALARM  0x12

#define OM_A2_BIAS_HIGH_WARNING  0x14
#define OM_A2_BIAS_LOW_WARNING  0x16

#define OM_A2_TXPOWER_HIGH_ALARM  0x18
#define OM_A2_TXPOWER_LOW_ALARM  0x1A

#define OM_A2_TXPOWER_HIGH_WARNING  0x1C
#define OM_A2_TXPOWER_LOW_WARNING  0x1E

#define OM_A2_RXPOWER_HIGH_ALARM  0x20
#define OM_A2_RXPOWER_LOW_ALARM  0x22

#define OM_A2_RXPOWER_HIGH_WARNING  0x24
#define OM_A2_RXPOWER_LOW_WARNING  0x26

#define OM_A2_ADDR_TEMPERATURE  0x60
#define OM_A2_ADDR_VOLTAGE  0x62
#define OM_A2_ADDR_BIAS  0x64
#define OM_A2_ADDR_TXPOWER  0x66
#define OM_A2_ADDR_RXPOWER  0x68

#define OM_A2_TX_STATE  0x6E

#define OM_A2_DDM_ALARM  0x70
#define OM_A2_DDM_WARNING  0x74



#define TEMPERATURE_ACCURACY_FACTOR	256
#define VOLTAGE_ACCURACY_FACTOR	        10000
#define BIAS_ACCURACY_FACTOR	        125
#define TXPOWER_ACCURACY_FACTOR	        1250
#define RXPOWER_ACCURACY_FACTOR     	10000
#define CALIBRATION_ACCURACY_FACTOR_1000     	1000
#define CALIBRATION_ACCURACY_FACTOR_100    100

#define RX_PWR_MIN_MW 0.0001






/* ���¿����¶ȣ��棩*/
void update_om_temperature();



/* ���¹�����ѹ��V��*/
void update_om_voltage();


/* ����ƫ�õ�����mA��*/
void update_om_bias();


/* ���㷢�͹⹦�ʣ�dBm��*/
float calculate_om_tx_power(uint8_t pon_rate);

/* ���·��͹⹦�ʣ�dBm��*/
void update_om_tx_power();


/* ������չ⹦�ʣ�dBm��*/
float calculate_om_rx_power(uint8_t pon_rate);

/* ���½��չ⹦�ʣ�dBm��*/
void update_om_rx_power();


/* ���¹�ģ������������Ϣ */
void update_om_diagnose();

/* ���¹�ģ��ĸ澯��Ϣ */
void update_om_warning();





/***********************************************************************
	** �� �� ���� om_default_config_flash_read
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� uint8_t 1 ��ȡ�ɹ� 0 ��ȡʧ��
	** ���������� ��ȡ��ģ����Ʋ�������
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
uint8_t om_default_config_flash_read();


/***********************************************************************
	** �� �� ���� om_save_config_flash_reg_write
	** ��    �룺 uint8_t *pbuff �Ĵ�������
								uint32_t bufflen �ֽڳ���
	** ��    ���� ��
	** �� �� ֵ�� ��
	** ���������� �����ն�deemphֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void om_save_data_config_flash_write(uint8_t *pbuff,uint32_t bufflen);

/***********************************************************************
	** �� �� ���� om_default_config_flash_init
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� ��
	** ���������� ��ʼ����ģ����Ʋ�������
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void om_default_config_flash_init();

/***********************************************************************
	** �� �� ���� om_flash_block_data_calculate_crc32
	** ��    �룺 
	crc_start_address��crcУ����ʼ��ַ
	uint32_t size��У�����ݳ���
	** ��    ���� 
	CRC_DATA��crcУ����
	** �� �� ֵ�� ��
	** ���������� 32λcrcУ��
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
uint32_t om_flash_block_data_calculate_crc32(uint32_t crc_start_address, uint32_t 
			size);

/***********************************************************************
	** �� �� ���� om_crc32_reset
	** ��    �룺 ��
	
	** ��    ���� ��
	
	** �� �� ֵ�� ��
	** ���������� crc reset
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void om_crc32_reset();



/*****************************************************************************
 * �� �� ��  : ddm_process
 * �� �� ��  : gqhuan
 * ��������  : 2023��10��11��
 * ��������  : ��ʱˢ��DDM�������ֵ
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 
*****************************************************************************/
void ddm_process();

/*****************************************************************************
 * �� �� ��  : flash_config_init
 * �� �� ��  : fz
 * ��������  : 2023��12��5��
 * ��������  : 
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void flash_config_init();


/*****************************************************************************
 * �� �� ��  : default_config_apc_auto_enable
 * �� �� ��  : fz
 * ��������  : 2024��9��14��
 * ��������  : ʹ��Ĭ��ֵ������apc�Զ�ʹ��
 * �������  :SFF_MODULE_TYPE module_type, ��ģ������
 				uint8_t ctrl_enable  1-ʹ�ܣ�0-ȥʹ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void default_config_apc_auto_enable(SFF_MODULE_TYPE module_type,
			uint8_t ctrl_enable);

/*****************************************************************************
 * �� �� ��  : calibration_tx_i_50g_reg_write
 * �� �� ��  : gqhuan
 * ��������  : 2024��10��16��
 * ��������  : У׼50G����LD������б��slope�ͽؾ�offset
 * �������  : uint8_t *pbuff,
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void calibration_tx_i_50g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * �� �� ��  : calibration_tx_i_10g_reg_write
 * �� �� ��  : sjtu
 * ��������  : 2024��11��12��
 * ��������  : У׼10G����LD������б��slope�ͽؾ�offset
 * �������  : uint8_t *pbuff,
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void calibration_tx_i_10g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * �� �� ��  : calibration_tx_i_1g_reg_write
 * �� �� ��  : sjtu
 * ��������  : 2024��11��12��
 * ��������  : У׼1G����LD������б��slope�ͽؾ�offset
 * �������  : uint8_t *pbuff,
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void calibration_tx_i_1g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * �� �� ��  : calibration_tx_pwr_50g_reg_write
 * �� �� ��  : gqhuan
 * ��������  : 2024��10��16��
 * ��������  : У׼50G���͹⹦�ʵ�б��slope�ͽؾ�offset
 * �������  : uint8_t *pbuff,
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void calibration_tx_pwr_50g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * �� �� ��  : calibration_tx_pwr_10g_reg_write
 * �� �� ��  : sjtu
 * ��������  : 2024��11��12��
 * ��������  : У׼10G���͹⹦�ʵ�б��slope�ͽؾ�offset
 * �������  : uint8_t *pbuff,
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void calibration_tx_pwr_10g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * �� �� ��  : calibration_tx_pwr_1g_reg_write
 * �� �� ��  : sjtu
 * ��������  : 2024��11��12��
 * ��������  : У׼1G���͹⹦�ʵ�б��slope�ͽؾ�offset
 * �������  : uint8_t *pbuff,
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void calibration_tx_pwr_1g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * �� �� ��  : calibration_rx_pwr_50g_reg_write
 * ��    ��  : sjtu
 * ��������  : 2024��10��29��
 * ��������  : У׼50G���չ⹦�ʵĶ��κ���ϵ��x2��x1��x0
 * �������  : uint8_t *pbuff,
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void calibration_rx_pwr_50g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * �� �� ��  : calibration_rx_pwr_10g_reg_write
 * ��    ��  : sjtu
 * ��������  : 2024��11��12��
 * ��������  : У׼10G���չ⹦�ʵĶ��κ���ϵ��x2��x1��x0
 * �������  : uint8_t *pbuff,
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void calibration_rx_pwr_10g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * �� �� ��  : calibration_rx_pwr_1g_reg_write
 * ��    ��  : sjtu
 * ��������  : 2024��11��12��
 * ��������  : У׼1G���չ⹦�ʵĶ��κ���ϵ��x2��x1��x0
 * �������  : uint8_t *pbuff,
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void calibration_rx_pwr_1g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * �� �� ��  : om_default_config_flash_read_50g
 * ��    ��  : sjtu
 * ��������  : 2025��02��24��
 * ��������  : ��ȡ50Gģ������ò�����У׼����
 * �������  : 
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void om_default_config_flash_read_50g();

/*****************************************************************************
 * �� �� ��  : om_default_config_flash_read_10g
 * ��    ��  : sjtu
 * ��������  : 2025��02��24��
 * ��������  : ��ȡ10Gģ������ò�����У׼����
 * �������  : 
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void om_default_config_flash_read_10g();

/*****************************************************************************
 * �� �� ��  : om_default_config_flash_read_1g
 * ��    ��  : sjtu
 * ��������  : 2025��02��24��
 * ��������  : ��ȡ1Gģ������ò�����У׼����
 * �������  : 
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void om_default_config_flash_read_1g();

/*****************************************************************************
 * �� �� ��  : convert_2byte_to_uint16
 * ��    ��  : sjtu
 * ��������  : 2025��03��19��
 * ��������  : ���������ֽڵ����ݣ��������жϣ�������������
 * �������  : 
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
short convert_2byte_to_int(uint8_t value_high, uint8_t value_low);
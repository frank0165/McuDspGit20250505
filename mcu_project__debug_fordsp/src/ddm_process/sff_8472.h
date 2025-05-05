#include "gd32e501_eval.h"
#include "mcu_data_type.h"
#include "mcu_system_comm.h"
#include <stdint.h>
#include <math.h>
#include "gd32e501_crc.h"

/*DDM监控物理量ADC输出值*/
extern volatile DDM_ADC_OUT_VAL ddm_adc_out_val;

/*光模块默认参数*/
extern volatile OM_DEFAULT_CONFIG om_default_config;

/*光模块速率模式*/
extern volatile SFF_MODULE_TYPE sff_module_type;

/*光模块默认参数 */
extern volatile uint8_t default_config_value[FLASH_CONFIG_LENGTH];

/*************************************************************************
* 变量功能：DDM自动轮询开关
* 取值范围：SET or RESET
* 注意事项：对应虚拟寄存器:CMD_DDM_SWITCH_ATUO_PROCESS_REG
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






/* 更新壳体温度（℃）*/
void update_om_temperature();



/* 更新工作电压（V）*/
void update_om_voltage();


/* 更新偏置电流（mA）*/
void update_om_bias();


/* 计算发送光功率（dBm）*/
float calculate_om_tx_power(uint8_t pon_rate);

/* 更新发送光功率（dBm）*/
void update_om_tx_power();


/* 计算接收光功率（dBm）*/
float calculate_om_rx_power(uint8_t pon_rate);

/* 更新接收光功率（dBm）*/
void update_om_rx_power();


/* 更新光模块的数字诊断信息 */
void update_om_diagnose();

/* 更新光模块的告警信息 */
void update_om_warning();





/***********************************************************************
	** 函 数 名： om_default_config_flash_read
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： uint8_t 1 读取成功 0 读取失败
	** 功能描述： 读取光模块控制参数函数
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
uint8_t om_default_config_flash_read();


/***********************************************************************
	** 函 数 名： om_save_config_flash_reg_write
	** 输    入： uint8_t *pbuff 寄存器缓存
								uint32_t bufflen 字节长度
	** 输    出： 无
	** 返 回 值： 无
	** 功能描述： 设置收端deemph值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void om_save_data_config_flash_write(uint8_t *pbuff,uint32_t bufflen);

/***********************************************************************
	** 函 数 名： om_default_config_flash_init
	** 输    入： 无
	** 输    出： 无
	** 返 回 值： 无
	** 功能描述： 初始化光模块控制参数函数
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void om_default_config_flash_init();

/***********************************************************************
	** 函 数 名： om_flash_block_data_calculate_crc32
	** 输    入： 
	crc_start_address：crc校验起始地址
	uint32_t size：校验数据长度
	** 输    出： 
	CRC_DATA：crc校验结果
	** 返 回 值： 无
	** 功能描述： 32位crc校验
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
uint32_t om_flash_block_data_calculate_crc32(uint32_t crc_start_address, uint32_t 
			size);

/***********************************************************************
	** 函 数 名： om_crc32_reset
	** 输    入： 无
	
	** 输    出： 无
	
	** 返 回 值： 无
	** 功能描述： crc reset
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void om_crc32_reset();



/*****************************************************************************
 * 函 数 名  : ddm_process
 * 负 责 人  : gqhuan
 * 创建日期  : 2023年10月11日
 * 函数功能  : 定时刷新DDM五个参量值
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 
*****************************************************************************/
void ddm_process();

/*****************************************************************************
 * 函 数 名  : flash_config_init
 * 负 责 人  : fz
 * 创建日期  : 2023年12月5日
 * 函数功能  : 
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void flash_config_init();


/*****************************************************************************
 * 函 数 名  : default_config_apc_auto_enable
 * 负 责 人  : fz
 * 创建日期  : 2024年9月14日
 * 函数功能  : 使用默认值，启用apc自动使能
 * 输入参数  :SFF_MODULE_TYPE module_type, 光模块类型
 				uint8_t ctrl_enable  1-使能；0-去使能
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void default_config_apc_auto_enable(SFF_MODULE_TYPE module_type,
			uint8_t ctrl_enable);

/*****************************************************************************
 * 函 数 名  : calibration_tx_i_50g_reg_write
 * 负 责 人  : gqhuan
 * 创建日期  : 2024年10月16日
 * 函数功能  : 校准50G发端LD电流的斜率slope和截距offset
 * 输入参数  : uint8_t *pbuff,
 				uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void calibration_tx_i_50g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : calibration_tx_i_10g_reg_write
 * 负 责 人  : sjtu
 * 创建日期  : 2024年11月12日
 * 函数功能  : 校准10G发端LD电流的斜率slope和截距offset
 * 输入参数  : uint8_t *pbuff,
 				uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void calibration_tx_i_10g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : calibration_tx_i_1g_reg_write
 * 负 责 人  : sjtu
 * 创建日期  : 2024年11月12日
 * 函数功能  : 校准1G发端LD电流的斜率slope和截距offset
 * 输入参数  : uint8_t *pbuff,
 				uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void calibration_tx_i_1g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : calibration_tx_pwr_50g_reg_write
 * 负 责 人  : gqhuan
 * 创建日期  : 2024年10月16日
 * 函数功能  : 校准50G发送光功率的斜率slope和截距offset
 * 输入参数  : uint8_t *pbuff,
 				uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void calibration_tx_pwr_50g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : calibration_tx_pwr_10g_reg_write
 * 负 责 人  : sjtu
 * 创建日期  : 2024年11月12日
 * 函数功能  : 校准10G发送光功率的斜率slope和截距offset
 * 输入参数  : uint8_t *pbuff,
 				uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void calibration_tx_pwr_10g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : calibration_tx_pwr_1g_reg_write
 * 负 责 人  : sjtu
 * 创建日期  : 2024年11月12日
 * 函数功能  : 校准1G发送光功率的斜率slope和截距offset
 * 输入参数  : uint8_t *pbuff,
 				uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void calibration_tx_pwr_1g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : calibration_rx_pwr_50g_reg_write
 * 作    者  : sjtu
 * 创建日期  : 2024年10月29日
 * 函数功能  : 校准50G接收光功率的二次函数系数x2、x1、x0
 * 输入参数  : uint8_t *pbuff,
 				uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void calibration_rx_pwr_50g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : calibration_rx_pwr_10g_reg_write
 * 作    者  : sjtu
 * 创建日期  : 2024年11月12日
 * 函数功能  : 校准10G接收光功率的二次函数系数x2、x1、x0
 * 输入参数  : uint8_t *pbuff,
 				uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void calibration_rx_pwr_10g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : calibration_rx_pwr_1g_reg_write
 * 作    者  : sjtu
 * 创建日期  : 2024年11月12日
 * 函数功能  : 校准1G接收光功率的二次函数系数x2、x1、x0
 * 输入参数  : uint8_t *pbuff,
 				uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void calibration_rx_pwr_1g_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : om_default_config_flash_read_50g
 * 作    者  : sjtu
 * 创建日期  : 2025年02月24日
 * 函数功能  : 读取50G模块的配置参数及校准参数
 * 输入参数  : 
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void om_default_config_flash_read_50g();

/*****************************************************************************
 * 函 数 名  : om_default_config_flash_read_10g
 * 作    者  : sjtu
 * 创建日期  : 2025年02月24日
 * 函数功能  : 读取10G模块的配置参数及校准参数
 * 输入参数  : 
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void om_default_config_flash_read_10g();

/*****************************************************************************
 * 函 数 名  : om_default_config_flash_read_1g
 * 作    者  : sjtu
 * 创建日期  : 2025年02月24日
 * 函数功能  : 读取1G模块的配置参数及校准参数
 * 输入参数  : 
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void om_default_config_flash_read_1g();

/*****************************************************************************
 * 函 数 名  : convert_2byte_to_uint16
 * 作    者  : sjtu
 * 创建日期  : 2025年03月19日
 * 函数功能  : 接收两个字节的数据，做正负判断，并将负数解码
 * 输入参数  : 
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
short convert_2byte_to_int(uint8_t value_high, uint8_t value_low);
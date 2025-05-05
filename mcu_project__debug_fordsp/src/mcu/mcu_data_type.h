/***********************************************************************************

 * 文 件 名   : mcu_data_type.h
 * 负 责 人   : fz
 * 创建日期   : 2023年5月15日
 * 文件描述   : mcu的公共头文件
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/


#ifndef _MCU_DATA_TYPE_H_
#define _MCU_DATA_TYPE_H_

#include "gd32e501.h"


#define PRINT_BUFFER_MAX		16
typedef struct _PRINT_BUFFER_CONFIG_
{
	uint8_t idx;
	uint8_t buffer[PRINT_BUFFER_MAX];
}PRINT_BUFFER_CONFIG;


#define I2C_MASTER_BUFFER_MAX 				220

#define I2C_SLAVE_BUFFER_MAX				264
#define I2C_SLAVE_WRITE_READ_MAX			260

#define MCU_I2C_REGADDRESS_SIZE			7//由4变成7

/* add by fz, 20231206, 原因:i2c地址配置信息 */
typedef struct _I2C_ALL_ADDRESS_INFO_
{
	uint8_t reg_size;	/*寄存器长度*/
	int32_t slave_address; /*slave 地址*/
	uint8_t regaddress[MCU_I2C_REGADDRESS_SIZE + 1]; /*寄存器值*/
}I2C_ALL_ADDRESS_INFO;


/* add by fz, 20250310, 原因:定义中断分组为0 ,不抢断中断*/
#define NIVC_IRQ_GROUP			0

/* add by fz, 20250310, 原因:定义中断优先级 */
typedef enum _MCU_NIVC_IRQ_PRIORITY_
{
	I2C_SLAVE_IRQ_ERR_PRI = 0,
	I2C_SLAVE_IRQ_EVENT_PRI = 1,
	I2C_MASTER_IRQ_ERR_PRI = 2,
	I2C_MASTER_IRQ_EVENT_PRI = 3,	
	//TRIGGER_EXIT0_IRQ_PRI = 4,	
	TRIGGER_EXIT15_IRQ_PRI = 4,	
	
}MCU_NIVC_IRQ_PRIORITY;

/*0,no doing;1=ok,2=error*/
typedef enum _CRC_CHECK_RESULT_
{
	CRC_NO_DOING = 0,
	CRC_CHECK_OK,
	CRC_CHECK_ERROR,
	CRC_MALLOC_FAIL,
	CRC_NO_END_RESULT
}CRC_CHECK_RESULT;


/*专用芯片的i2c访问地址*/
typedef enum _I2C_DEVICE_ADDRESS_
{
	/*所使用的外接芯片实际地址*/
	I2C_8472_A0_ADDR = 0xA0,
	I2C_8472_A2_ADDR = 0xA2,
	I2C_8472_B0_ADDR = 0xB0,
	I2C_8472_B2_ADDR = 0xB2,
	I2C_8472_C0_ADDR = 0xC0,
	I2C_8472_C2_ADDR = 0xC2,
	
	I2C_8472_MEM_A0_ADDR = 0xD0,
	I2C_8472_MEM_B0_ADDR = 0xE0,
	I2C_8472_MEM_C0_ADDR = 0xF0,
	I2C_8472_MEM_A2_ADDR = 0xD2,
	I2C_8472_MEM_B2_ADDR = 0xE2,
	I2C_8472_MEM_C2_ADDR = 0xE8,

	/* add by fz, 20250103, 原因:用于读取flash中的配置 */
	I2C_FLASH_A8_ADDR = 0xA8,

	/*外置芯片tec的设备地址*/
	I2C_TEC_DEV_ADDR = 0x42,

	//TEST_TWO_REG_SLAVE_ADDR = 0xCC,
	
	/*特殊配置时所用到的虚拟地址*/
	I2C_MCU_SPEC_ADDR = 0xCE,
	I2C_OTHER_ADDR = 0xFF	
	
}I2C_DEVICE_ADDRESS;

typedef enum _I2C_8472_A2_REGADDR_
{
	SFF_DDM_REG = 0x60 //读取DDM参数时的首个寄存器
}I2C_8472_A2_REGADDR;


/* add by fz, 20230515, 原因:针对I2C_MCU_SPEC_ADDR所使用的寄存器*/
typedef enum _I2C_MCU_SPECIAL_REGADDR_
{
	TEC_VTEC_CTL_REG = 0x0,/*配置vtec时的寄存器，数据是2字节，uint16*/
	TEC_AUTO_CTL_REG = 0x1, /*临时测试使用，自动显示*/
	TEC_CTL_TEMP = 0x2, /*tec温度*/	
	//TEC_VTEC_TEST_REG = 0x3, //12字节
	TEC_CALC_CTRL_AUTO_REG = 0x4, /*1字节，用于pid自动控制*/
	TEC_TEMP_OBJ_CFG_REG = 0x5,		/*设定目标温度，2个字节,值是ADC*/
	TEC_PID_PARAM_CFG_REG = 0x6,		/*设定pid的值，12字节*/
	APD_SET_VOLTAGE_REG = 0x7,
	UPGRADE_APP_SOFTWARE_REG = 0x8, /*mcu升级时使用的reg*/
	CMD_OPTICAL_PASSWORD_LIMIT_REG = 0x9,      /*光模块密码限定*/
	TEC_XTEC_VALUE_REG = 0xA,       /*读取xtec反馈值*/
	
	/*版本基本信息:长度40字节，12字节date,9字节time,1字节工作区*/
	UPGRADE_DEV_VERSION_INFO_REG = 0xB, 

	/*升级firmware*/
	UPGRADE_FIRMWARE_REG = 0xC,

	
	CMD_SOA_ELECTRIC_REG = 0xD, //SOA
	CMD_NEG_VOLTAGE_REG = 0xF, //负压

	//光模块的DDM相关信息
	CMD_MODULE_DDM_INFO_REG = 0x10,	

	//启动DDM自动刷新过程
	CMD_DDM_SWITCH_ATUO_PROCESS_REG = 0x12,

	/*驱动电流*/
	CMD_IBIAS_DRV_LD_REG = 0x13,

	/*调制电压*/
	CMD_IMOD_DRV_LD_REG = 0x14,

	/*摆幅*/
	CMD_RX_SWING_DRV_LD_REG = 0x15,

	/*EQ*/
	CMD_RX_EQ_DRV_LD_REG = 0x16,
	
	/*Tx LD Cross Point Adjust*/
	CMD_TX_LD_CROSS_POINT_ADJUSt_REG = 0x17,

	/*TX LD De-Emphasis*/
	CMD_TX_LD_DE_EMPH_REG = 0x18,

	/*RX LD De-Emphasis*/
	CMD_RX_LD_DE_EMPH_REG = 0x19,

		/*RX_LOS_THRESHOLD,0x1847,SDA*/
	CMD_SIGNAL_DETECT_ASSERT_REG = 0x1A,

	/*RX_LOS_HYST_SELECT，0x1848,SDD*/
	CMD_SIGNAL_DETECT_DE_ASSERT_REG = 0x1B,

	/*通用命令*/
	CMD_COMMAND_MAP_REG = 0x1C,

	/*升级user boot区*/
	CMD_UPGRADE_BOOT_SOFTWARE_REG= 0x1D,

	/*通用的读命令，用于小属性读取，例如配置的长度，初步定义
		20 字节
	*/
	CMD_COMMON_READ_REG = 0x27,

	/*导入配置好的数据给光模块flash*/
	CMD_OPTICAL_MODULE_CFG_FLASH = 0x28,

	CMD_DDM_50G_MONITOR_REG = 0x29,
	CMD_DSP_TICKS_REG = 0x2A,
	CMD_DSP_FW_VERSION_REG = 0x2B,

    CMD_MONITOR_I2C_STATUS_REG = 0x2C,

    TEST_I2C_RESTART_REG = 0xE5,
    TEST_TEC_RESET_REG = 0xE6,
    TEST_DSP_FSL_RSTPIN_REG = 0xE7,
    TEST_DSP_FSL_INFO_REG = 0xE8,
    TEST_DSP_FSL_DOWNLOAD_REG = 0xE9,
	TEST_READ_PRINT_BUFF_REG = 0xEA,/*通用读取buff*/
	TEST_ADC_INFO_REG = 0xEB,
	TEST_GPIO_INFO_REG = 0xEC,	
	TEST_GPIO_PIN_REG = 0xED,
	TEST_DAC_PIN_REG = 0xEE,
	//TEST_TEC_SCL_SDA = 0xEF,		
	//TEST_TEC_EN_SD_REG = 0xF0,
	TEC_OTHER_TEST_REG
}I2C_MCUSPECIAL_REGADDR;


#define MSC_REG_1BYTE(x)				x[0]

#define MSC_PAYLOAD_REG_1BYTE(x)			(x + 1)

/*光模块功能密码长度*/
#define	OPT_MOD_LIMIT_PASSWORD_LENGTH		16

#define USER_ACCESS_YES			SET

#define USER_ACCESS_NO				RESET



#define FLASH_PAGE_SIZE			1024


/*mcu 8472协议中的flash专用*/
#define A0_REG_ADDRESS		0x0807FC00U
#define A2_REG_ADDRESS		0x0807F800U
#define B0_REG_ADDRESS		0x0807F400U
#define B2_REG_ADDRESS		0x0807F000U
#define C0_REG_ADDRESS		0x0807EC00U
#define C2_REG_ADDRESS		0x0807E800U
#define OM_TABLE_SFF_8472_DATA_LEN              256

//#define  TEST_REG_ADDRESS 	(B2_REG_ADDRESS - 0x400)

/*上位机从mcu的flash读取配置数据，定义一个总长度*/
#define HMI_CFG_FLASH_LEN			256

#define CRC32_RESULT_SIZE			4

#define UPGRADE_APP_START			0x00
#define UPGRADE_APP_DOING			0x01
#define UPGRADE_APP_END			0x02
#define UPGRADE_CRC_END			0x03


#define USERBOOTADDRESS			0x8000000
#define UPDATE_FLAG					(B2_REG_ADDRESS - 0x1400) //0x0807F000-0x1400=0x0807DC00
#define AAPPLICATIONADDRESS      	((uint32_t)0x08007800)  /* User start code A space */
#define BAPPLICATIONADDRESS     	((uint32_t)0x0801F800)  /* User start code B space */

//如果是100K,则是0x19000 = 0xc800 * 2,现在由0xc800改为0x19000
#define FWADDRESS					(UPDATE_FLAG - 0x19000)//0x0807DC00-0x19000=0x08064c00

#define AAPP_FLAG				0x7800  //0x8007800
#define BAPP_FLAG				0x17800//0x8017800

#define SECTION_A_FLAG				1
#define SECTION_B_FLAG				2
#define SECTION_NON_FLAG			0xff

#define ADC_OUT_NORM               100.0
#define ADC_OUT_BIT_NUMBER        65535

typedef struct _DDM_ADC_OUT_VAL_
{
	uint16_t temperature_adc_out;
	
	uint16_t voltage_adc_out_0;// 50g
	uint16_t ibias_adc_out_0;
	uint16_t tx_power_adc_out_0;
	uint16_t rx_power_adc_out_0;
	
	uint16_t voltage_adc_out_1;// 10g
	uint16_t ibias_adc_out_1;
	uint16_t tx_power_adc_out_1;
	uint16_t rx_power_adc_out_1;
	
	uint16_t voltage_adc_out_2;// 1g
	uint16_t ibias_adc_out_2;
	uint16_t tx_power_adc_out_2;
	uint16_t rx_power_adc_out_2;
}DDM_ADC_OUT_VAL;


typedef struct _RSSI_POWER_
{
	uint16_t rssi;
	float power;
}RSSI_POWER;

#define RSSI_TO_RXPOWER_COUNT			16

/*Optical module default config*/
typedef struct _OM_DEFAULT_CONFIG_
{
	uint8_t rx_deemph_0;
	uint8_t rx_los_threshold_0;
	uint8_t rx_los_hyst_0;
	uint8_t tx_cpa_0;
	uint16_t tx_ibias_0;
	uint16_t tx_imod_0;	
	uint16_t tx_deemph_0;
	uint16_t rx_eq_0;
	uint16_t rx_swing_0;
	float tx_soa_0;
	float tx_vea_0;	
	float rx_vapd_0;	
	float tec_target_temp;
	uint8_t tx_apc_en_0;
	uint16_t tx_apc_target_0;
	float tx_i_slope_0;
	float tx_i_offset_0;
	float tx_pwr_slope_0;
	float tx_pwr_offset_0;
	float rx_pwr_a_0;
	float rx_pwr_b_0;
	float rx_pwr_c_0;

	uint8_t rx_deemph_1;
	uint8_t rx_los_threshold_1;
	uint8_t rx_los_hyst_1;
	uint8_t tx_cpa_1;
	uint16_t tx_ibias_1;
	uint16_t tx_imod_1;	
	uint16_t tx_deemph_1;
	uint16_t rx_eq_1;
	uint16_t rx_swing_1;
	float tx_vea_1;	
	float rx_vapd_1;
	uint8_t tx_apc_en_1;
	uint16_t tx_apc_target_1;
	float tx_i_slope_1;
	float tx_i_offset_1;
	float tx_pwr_slope_1;
	float tx_pwr_offset_1;
	float rx_pwr_a_1;
	float rx_pwr_b_1;
	float rx_pwr_c_1;

	uint8_t rx_los_threshold_2;
	uint8_t rx_los_hyst_2;
	uint8_t tx_cpa_2;
	uint16_t tx_ibias_2;
	uint16_t tx_imod_2;	
	uint16_t rx_swing_2;
	float rx_vapd_2;
	uint8_t tx_apc_en_2;
	uint16_t tx_apc_target_2;
	float tx_i_slope_2;
	float tx_i_offset_2;
	float tx_pwr_slope_2;
	float tx_pwr_offset_2;
	float rx_pwr_a_2;
	float rx_pwr_b_2;
	float rx_pwr_c_2;
	
}OM_DEFAULT_CONFIG;

#define CONFIGADDRESS					(FWADDRESS - 0x400)
typedef enum _MCU_FLASH_CONFIG_VALUE_
{
	TX_IBIAS_VALUE_0_HIGH = 0x00,
	TX_IBIAS_VALUE_0_LOW = 0x01,
	TX_SOA_VALUE_0_HIGH = 0x02,
	TX_SOA_VALUE_0_LOW = 0x03,
	TX_VEA_VALUE_0_HIGH = 0x04,
	TX_VEA_VALUE_0_LOW = 0x05,
	TX_IMOD_VALUE_0_HIGH = 0x06,
	TX_IMOD_VALUE_0_LOW = 0x07,
	TX_CPA_VALUE_0_HIGH = 0x08,
	TX_CPA_VALUE_0_LOW = 0x09,
	TX_DEEMPH_VALUE_0_HIGH = 0x0A,
	TX_DEEMPH_VALUE_0_LOW = 0x0B,
	RX_VAPD_VALUE_0_HIGH = 0x0C,
	RX_VAPD_VALUE_0_LOW = 0x0D,
	RX_EQ_VALUE_0_HIGH = 0x0E,
	RX_EQ_VALUE_0_LOW = 0x0F,
	RX_SWING_VALUE_0_HIGH = 0x10,
	RX_SWING_VALUE_0_LOW = 0x11,
	RX_DEEMPH_VALUE_0_HIGH = 0x12,
	RX_DEEMPH_VALUE_0_LOW = 0x13,
	RX_LOS_THRESHOLD_VALUE_0_HIGH = 0x14,
	RX_LOS_THRESHOLD_VALUE_0_LOW = 0x15,
	RX_LOS_HYST_VALUE_0_HIGH = 0x16,
	RX_LOS_HYST_VALUE_0_LOW = 0x17,
	RX_TEC_TARGET_VALUE_HIGH = 0x18,
	RX_TEC_TARGET_VALUE_LOW = 0x19,
	
	TX_IBIAS_VALUE_1_HIGH = 0x1A,
	TX_IBIAS_VALUE_1_LOW = 0x1B,
	TX_VEA_VALUE_1_HIGH = 0x1C,
	TX_VEA_VALUE_1_LOW = 0x1D,
	TX_IMOD_VALUE_1_HIGH = 0x1E,
	TX_IMOD_VALUE_1_LOW = 0x1F,
	TX_CPA_VALUE_1_HIGH = 0x20,
	TX_CPA_VALUE_1_LOW = 0x21,
	TX_DEEMPH_VALUE_1_HIGH = 0x22,
	TX_DEEMPH_VALUE_1_LOW = 0x23,
	RX_VAPD_VALUE_1_HIGH = 0x24,
	RX_VAPD_VALUE_1_LOW = 0x25,
	RX_EQ_VALUE_1_HIGH = 0x26,
	RX_EQ_VALUE_1_LOW = 0x27,
	RX_SWING_VALUE_1_HIGH = 0x28,
	RX_SWING_VALUE_1_LOW = 0x29,
	RX_DEEMPH_VALUE_1_HIGH = 0x2A,
	RX_DEEMPH_VALUE_1_LOW = 0x2B,
	RX_LOS_THRESHOLD_VALUE_1_HIGH = 0x2C,
	RX_LOS_THRESHOLD_VALUE_1_LOW = 0x2D,
	RX_LOS_HYST_VALUE_1_HIGH = 0x2E,
	RX_LOS_HYST_VALUE_1_LOW = 0x2F,

	TX_IBIAS_VALUE_2_HIGH = 0x30,
	TX_IBIAS_VALUE_2_LOW = 0x31,
	TX_IMOD_VALUE_2_HIGH = 0x32,
	TX_IMOD_VALUE_2_LOW = 0x33,
	TX_CPA_VALUE_2_HIGH = 0x34,
	TX_CPA_VALUE_2_LOW = 0x35,
	RX_VAPD_VALUE_2_HIGH = 0x36,
	RX_VAPD_VALUE_2_LOW = 0x37,
	RX_SWING_VALUE_2_HIGH = 0x38,
	RX_SWING_VALUE_2_LOW = 0x39,
	RX_LOS_THRESHOLD_VALUE_2_HIGH = 0x3A,
	RX_LOS_THRESHOLD_VALUE_2_LOW = 0x3B,
	RX_LOS_HYST_VALUE_2_HIGH = 0x3C,
	RX_LOS_HYST_VALUE_2_LOW = 0x3D,

	APC_ENABLE_50G_CFG = 0x3E,
	APC_TARGET_VALUE_50G_CFG_HIGH = 0x3F,
	APC_TARGET_VALUE_50G_CFG_LOW = 0x40,
	APC_ENABLE_10G_CFG = 0x41,
	APC_TARGET_VALUE_10G_CFG_HIGH = 0x42,
	APC_TARGET_VALUE_10G_CFG_LOW = 0x43,
	APC_ENABLE_1G_CFG = 0x44,
	APC_TARGET_VALUE_1G_CFG_HIGH = 0x45,
	APC_TARGET_VALUE_1G_CFG_LOW = 0x46,
	
	TX_I_SLOPE_HIGH_50G = 0x47,
	TX_I_SLOPE_LOW_50G = 0x48,
	TX_I_OFFSET_HIGH_50G = 0x49,
	TX_I_OFFSET_LOW_50G = 0x4A,
	TX_PWR_SLOPE_HIGH_50G = 0x4B,
	TX_PWR_SLOPE_LOW_50G = 0x4C,
	TX_PWR_OFFSET_HIGH_50G = 0x4D,
	TX_PWR_OFFSET_LOW_50G = 0x4E,
	RX_PWR_A_HIGH_50G = 0x4F,
	RX_PWR_A_LOW_50G = 0x50,
	RX_PWR_B_HIGH_50G = 0x51,
	RX_PWR_B_LOW_50G = 0x52,
	RX_PWR_C_HIGH_50G = 0x53,
	RX_PWR_C_LOW_50G = 0x54,

	TX_I_SLOPE_HIGH_10G = 0x55,
	TX_I_SLOPE_LOW_10G = 0x56,
	TX_I_OFFSET_HIGH_10G = 0x57,
	TX_I_OFFSET_LOW_10G = 0x58,
	TX_PWR_SLOPE_HIGH_10G = 0x59,
	TX_PWR_SLOPE_LOW_10G = 0x5A,
	TX_PWR_OFFSET_HIGH_10G = 0x5B,
	TX_PWR_OFFSET_LOW_10G = 0x5C,
	RX_PWR_A_HIGH_10G = 0x5D,
	RX_PWR_A_LOW_10G = 0x5E,
	RX_PWR_B_HIGH_10G = 0x5F,
	RX_PWR_B_LOW_10G = 0x60,
	RX_PWR_C_HIGH_10G = 0x61,
	RX_PWR_C_LOW_10G = 0x62,

	TX_I_SLOPE_HIGH_1G = 0x63,
	TX_I_SLOPE_LOW_1G = 0x64,
	TX_I_OFFSET_HIGH_1G = 0x65,
	TX_I_OFFSET_LOW_1G = 0x66,
	TX_PWR_SLOPE_HIGH_1G = 0x67,
	TX_PWR_SLOPE_LOW_1G = 0x68,
	TX_PWR_OFFSET_HIGH_1G = 0x69,
	TX_PWR_OFFSET_LOW_1G = 0x6A,
	RX_PWR_A_HIGH_1G = 0x6B,
	RX_PWR_A_LOW_1G = 0x6C,
	RX_PWR_B_HIGH_1G = 0x6D,
	RX_PWR_B_LOW_1G = 0x6E,
	RX_PWR_C_HIGH_1G = 0x6F,
	RX_PWR_C_LOW_1G = 0x70,
	TT1_TMP = 0x71,
	TT2_TMP = 0x72,
	TT3_TMP = 0x73,
	TT4_TMP = 0x74,
	TT5_TMP = 0x75,
	TT6_TMP = 0x76,
	TT7_TMP = 0x77,
	
	//组成8的倍数，便于保存flash
	
	
	FLASH_CONFIG_LENGTH
}MCU_FLASH_CONFIG_VALUE;



typedef enum _SFF_MODULE_TYPE_
{
	SFF_50G_TYPE = 0,
	SFF_10G_TYPE = 1,
	SFF_1G_TYPE = 2

}SFF_MODULE_TYPE;

typedef enum _CMD_COMMON_EX_
{
	CFG_SAVE_FLASH_EX = 0,  //保存flash
	CFG_CLEAR_FLASH_EX = 1, //清除flash
	APC_AUTO_ENABLE_EX = 2, //APC自动使能
	APC_IPHOTO_RATE_EX = 3, //配置iphoto
	APC_TARGET_VALUE_EX = 4, //配置apc target
	CALIBRATION_TX_I_50G_CONFIG = 5,//配置50G电流校准参数
	CALIBRATION_TX_PWR_50G_CONFIG = 6,//配置50G发端功率校准参数
	CALIBRATION_RX_PWR_50G_CONFIG = 7,//配置50G收端功率校准参数
	CALIBRATION_TX_I_10G_CONFIG = 8,//配置10G电流校准参数
	CALIBRATION_TX_PWR_10G_CONFIG = 9,//配置10G发端功率校准参数
	CALIBRATION_RX_PWR_10G_CONFIG = 10,//配置10G收端功率校准参数
	CALIBRATION_TX_I_1G_CONFIG = 11,//配置1G电流校准参数
	CALIBRATION_TX_PWR_1G_CONFIG = 12,//配置1G发端功率校准参数
	CALIBRATION_RX_PWR_1G_CONFIG = 13//配置1G收端功率校准参数
		
}CMD_COMMON_EX;

#endif


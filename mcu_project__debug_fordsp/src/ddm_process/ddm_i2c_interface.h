#ifndef _DDM_I2C_INTERFACE_H_
#define _DDM_I2C_INTERFACE_H_

#include "gd32e501_it.h"
#include "string.h"
#include "mcu_system_comm.h"
#include "mcu_data_type.h"
#include "mcu_global_vars_param.h"
#include "sff_8472.h"
#include "ddm_sff_i2c_interface.h"
#include "ddm_50g_config_interface.h"
#include "ddm_10g_config_interface.h"
#include "ddm_1g_config_interface.h"
#include "update_comm.h"
#include "tec_comm.h"


//定义导入二进制文件数据到flash相关状态
#define BINARY_DATA_TO_FLASH_START 0x00
#define BINARY_DATA_TO_FLASH_DOING 0x01
#define BINARY_DATA_TO_FLASH_END 0x02
#define BINARY_DATA_TO_FLASH_CRC_END 0x03

/*****************************************************************************
 * 函 数 名  : apd_i2c_vcc_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : 设置VAPD设置
 * 输入参数  : uint8_t *pbuff,  第1个字节是寄存器
                                第2个字节是类型:50G, 10G,1G
                                后续两个字节是数值
                                
 				uint32_t bufflen pbuff长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c调用
 * 其    它  : 无

*****************************************************************************/
void apd_i2c_vcc_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : soa_i2c_ild_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : SOA电流设置
 * 输入参数  : uint8_t *pbuff,  第1个字节是寄存器
                                第2个字节是类型:50G, 10G,1G；这里只有50G
                                后续两个字节是数值
                                
 				uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c调用
 * 其    它  : 无

*****************************************************************************/
void soa_i2c_ild_reg_write(uint8_t *pbuff,uint32_t bufflen);
	
/*****************************************************************************
 * 函 数 名  : vea_i2c_vcc_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : EA负压设置
 * 输入参数  : uint8_t *pbuff,  第1个字节是寄存器
                                第2个字节是类型:50G, 10G,1G；这里只有50G,10G
                                后续两个字节是数值
                                
 				uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c调用
 * 其    它  : 无

*****************************************************************************/
void vea_i2c_vcc_reg_write(uint8_t *pbuff,uint32_t bufflen);
	

/*****************************************************************************
 * 函 数 名  : ibias_i2c_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : IBIAS电流设置
 * 输入参数  : uint8_t *pbuff,  第1个字节是寄存器
                                第2个字节是类型:50G, 10G,1G；
                                后续两个字节是数值
                                
 				uint32_t bufflen pbuff长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c调用
 * 其    它  : 无

*****************************************************************************/
void ibias_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen);
	
/*****************************************************************************
 * 函 数 名  : imod_i2c_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : IMOD调制电流设置
 * 输入参数  : uint8_t *pbuff,  第1个字节是寄存器
                                第2个字节是类型:50G, 10G,1G；
                                后续两个字节是数值
                                
 				uint32_t bufflen pbuff长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c调用
 * 其    它  : 无

*****************************************************************************/
void imod_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen);
	
/*****************************************************************************
 * 函 数 名  : swing_i2c_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : *RX_SWING收端摆幅设置
 * 输入参数  : uint8_t *pbuff,  第1个字节是寄存器
                                第2个字节是类型:50G, 10G,1G；
                                后续两个字节是数值
                                
 				uint32_t bufflen pbuff长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c调用
 * 其    它  : 无

*****************************************************************************/
void swing_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen);
	
/*****************************************************************************
 * 函 数 名  : rx_eq_i2c_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : RX_EQ收端均衡设置
 * 输入参数  : uint8_t *pbuff,  第1个字节是寄存器
                                第2个字节是类型:50G, 10G,1G；
                                后续两个字节是数值
                                
 				uint32_t bufflen pbuff长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c调用
 * 其    它  : 无

*****************************************************************************/
void rx_eq_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen);
	

 /*****************************************************************************
 * 函 数 名  : cpa_i2c_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : TxCross交叉点设置
 * 输入参数  : uint8_t *pbuff,  第1个字节是寄存器
                                第2个字节是类型:50G, 10G,1G；
                                后续两个字节是数值
                                
 				uint32_t bufflen pbuff长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c调用
 * 其    它  : 无

*****************************************************************************/
void cpa_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen);
	
/*****************************************************************************
 * 函 数 名  : tx_deemph_i2c_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : Tx_DeEmph发端去预加重设置
 * 输入参数  : uint8_t *pbuff,  第1个字节是寄存器
                                第2个字节是类型:50G, 10G；
                                后续两个字节是数值
                                
 				uint32_t bufflen pbuff长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c调用
 * 其    它  : 无

*****************************************************************************/
void tx_deemph_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen);
	
/*****************************************************************************
 * 函 数 名  : rx_deemph_i2c_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : Rx_DeEmph收端去预加重设置
 * 输入参数  : uint8_t *pbuff,  第1个字节是寄存器
                                第2个字节是类型:50G, 10G；
                                后续两个字节是数值
                                
 				uint32_t bufflen pbuff长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c调用
 * 其    它  : 无

*****************************************************************************/
void rx_deemph_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen);
	
/*****************************************************************************
 * 函 数 名  : rx_los_threshold_i2c_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : SDA设置 RX Loss Hyst
 * 输入参数  : uint8_t *pbuff,  第1个字节是寄存器
                                第2个字节是类型:50G, 10G；
                                后续两个字节是数值
                                
 				uint32_t bufflen pbuff长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : i2c调用
 * 其    它  : 无

*****************************************************************************/
void rx_los_threshold_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen);
	

 /***********************************************************************
	** 函 数 名： rx_los_hyst_i2c_reg_write
	** 输    入： uint8_t *pbuff 寄存器缓存
								uint32_t bufflen 字节长度
	** 输    出： 无
	** 返 回 值： 无
	** 功能描述： 设置收端信号丢失磁滞值
	** 作    者： gqhuan
	** 日    期： 
************************************************************************/
void rx_los_hyst_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen);

/*****************************************************************************
 * 函 数 名  : cmd_command_map_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2024年9月4日
 * 函数功能  : 通用命令的写功能
 * 输入参数  : uint8_t *pbuff, 输入数据
 			uint32_t bufflen   长度
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : CMD_COMMAND_MAP_REG = 0x1c

*****************************************************************************/
void cmd_command_map_reg_write(uint8_t *pbuff,uint32_t bufflen);



/*****************************************************************************
 * 函 数 名  : ddm_i2c_switch_auto_process_reg_write
 * 负 责 人  : fz
 * 创建日期  : 2023年5月23日
 * 函数功能  : 启动DDM自动刷新过程
 * 输入参数  : uint8_t *pbuff,
 				      uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : CMD_DDM_SWITCH_ATUO_PROCESS_REG = 0x12,
	

*****************************************************************************/
void ddm_i2c_switch_auto_process_reg_write(uint8_t *pbuff,uint32_t bufflen);


/*****************************************************************************
 * 函 数 名  : import_data_to_default_config_value
 * 负 责 人  : sjtu
 * 创建日期  : 2025年2月6日
 * 函数功能  : 导入二进制文件的数据，并将其赋值给default_config_value数组
 * 输入参数  : uint8_t *pbuff,
 				      uint32_t bufflen
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : CMD_OPTICAL_MODULE_CFG_FLASH = 0x28,
	

*****************************************************************************/
void import_data_to_default_config_value(uint8_t *pbuff, uint32_t bufflen);


/*****************************************************************************
 * 函 数 名  : import_binary_file_data_to_mcu_flash
 * 负 责 人  : sjtu
 * 创建日期  : 2025年2月10日
 * 函数功能  : 导入二进制文件的数据到flash
 * 输入参数  : uint8_t *p_buff,
 				      uint32_t buff_len
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : CMD_OPTICAL_MODULE_CFG_FLASH = 0x28,
	
*****************************************************************************/
void import_binary_file_data_to_mcu_flash(uint8_t *p_buff, uint32_t buff_len);


/*****************************************************************************
 * 函 数 名  : ddm_i2c_50g_monitor_reg_read
 * 负 责 人  : fz
 * 创建日期  : 2025年3月11日
 * 函数功能  : 回读50g 的监控值
 * 输入参数  : uint8_t regaddr  CMD_DDM_50G_MONITOR_REG
 				uint32_t bufflen pbuff的长度
 * 输出参数  : uint8_t *pbuff 回读的值
 * 返 回 值  : 无
 * 调用关系  : 上位机调用，用于调试
 * 其    它  : 

*****************************************************************************/

void ddm_i2c_50g_monitor_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t 
				bufflen);
#endif

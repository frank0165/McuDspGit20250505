/***********************************************************************************

 * 文 件 名   : dsp_fsl_i2c_interface.h
 * 负 责 人   : fangzhe
 * 创建日期   : 2025年4月18日
 * 文件描述   : dsp i2c接口
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#ifndef _DSP_FSL_I2C_INTERFACE_H_
#define _DSP_FSL_I2C_INTERFACE_H_



/*****************************************************************************
 * 函 数 名  : dsp_fsl_i2c_start_download_reg_write
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年4月18日
 * 函数功能  : 
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void dsp_fsl_i2c_start_download_reg_write(uint8_t *pbuff,uint32_t bufflen);


void dsp_fsl_i2c_info_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen);

void dsp_fsl_i2c_data_path_reg_write(uint8_t *pbuff,uint32_t bufflen);


void dsp_fsl_i2c_rst_pin_reg_write(uint8_t *pbuff,uint32_t bufflen);

#endif
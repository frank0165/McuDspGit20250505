/***********************************************************************************

 * �� �� ��   : dsp_fsl_i2c_interface.h
 * �� �� ��   : fangzhe
 * ��������   : 2025��4��18��
 * �ļ�����   : dsp i2c�ӿ�
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#ifndef _DSP_FSL_I2C_INTERFACE_H_
#define _DSP_FSL_I2C_INTERFACE_H_



/*****************************************************************************
 * �� �� ��  : dsp_fsl_i2c_start_download_reg_write
 * �� �� ��  : fangzhe
 * ��������  : 2025��4��18��
 * ��������  : 
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void dsp_fsl_i2c_start_download_reg_write(uint8_t *pbuff,uint32_t bufflen);


void dsp_fsl_i2c_info_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen);

void dsp_fsl_i2c_data_path_reg_write(uint8_t *pbuff,uint32_t bufflen);


void dsp_fsl_i2c_rst_pin_reg_write(uint8_t *pbuff,uint32_t bufflen);

#endif
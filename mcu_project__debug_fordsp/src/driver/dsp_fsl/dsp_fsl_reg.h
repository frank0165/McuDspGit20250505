/***********************************************************************************

 * �� �� ��   : dsp_fsl_reg.h
 * �� �� ��   : fangzhe
 * ��������   : 2025��4��16��
 * �ļ�����   : dsp�ļĴ���
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#ifndef _DSP_FSL_REG_H_
#define _DSP_FSL_REG_H_

/*APCʹ�ܣ�handle.WriteReg(0x10c, 0xffffffff)��ִ��һ�μ��ɣ���*/
#define DSP_APC_EN_REG     (0x10c << 2)

/*Bypassʹ��+Bypass_code<11:0>��handle.WriteReg(0x10f, 0x09601640)��bypassʹ�ܲ����80mA������*/
#define DSP_LD_IBIAS_REG    (0x10f << 2)

#define DSP_SOA_IBIAS_REG   (0x10c << 2)


#endif
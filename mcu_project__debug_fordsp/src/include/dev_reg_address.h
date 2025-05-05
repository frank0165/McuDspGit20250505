/***********************************************************************************

 * �� �� ��   : dev_reg_address.h
 * �� �� ��   : fangzhe
 * ��������   : 2025��3��30��
 * �ļ�����   : �����豸��ַ���߼Ĵ�����ַ
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#ifndef _DEV_REG_ADDRESS_H_
#define _DEV_REG_ADDRESS_H_

/* add by fangzhe, 20250330, ԭ��:50G driver��ַ */
#define GN7161_SLAVE_ADDRESS    0xAC

//50G dsp driver,д��ַ��0xAE;
//���ĵ�ַʵ����0xAC;((0x15 <<2 + 2)  << 1)
//DSPоƬ�Զ���д�ĵ�ַ���˸Ķ����ڱ������л�����0xAE,��Ϊreadʱ����
//master i2cЭ��ջ�����ڲ�����תΪ0xAC
#define DSP_FSL_SLAVE_ADDRESS    0xAE//((0x15 <<2 + 3)  << 1)

/* add by fangzhe, 20250330, ԭ��:10G driver��ַ */
#define GN7153_SLAVE_ADDRESS    0x48


/* add by fangzhe, 20250330, ԭ��:1G driver��ַ */
#define UX3326_SLAVE_ADDRESS    0xC6





#endif

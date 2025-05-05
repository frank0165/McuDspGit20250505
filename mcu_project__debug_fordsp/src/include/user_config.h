/***********************************************************************************

 * �� �� ��   : user_config.h
 * �� �� ��   : fz
 * ��������   : 2025��1��13��
 * �ļ�����   : mcu�������ļ�
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#ifndef _USER_CONFIG_H_
#define _USER_CONFIG_H_

#define CFG_YES			1
#define CFG_NO			0
#define A_SOFTWARE_VERSION				'A'
#define B_SOFTWARE_VERSION				'B'

#define MODULE_50G_10G_1G_OPTICAL			CFG_YES
#define MODULE_50G_10G_OPTICAL				CFG_NO
#define MODULE_50G_OPTICAL					CFG_NO

#define OPTICAL_MODELE_VERSION				A_SOFTWARE_VERSION

/* add by fz, 20250115, ԭ��:��ģ��ģ�� */
#if (MODULE_50G_10G_1G_OPTICAL == CFG_YES) && (OPTICAL_MODELE_VERSION == A_SOFTWARE_VERSION)

/* add by fz, 20250113, ԭ��:��ģA�汾���� */
/*ctl�������ѹ2*/

#define FH_IC_DSP_HARDWARE              CFG_YES
#define	FH_IC_SGM41296_HARDWARE		CFG_YES

#define FH_IC_SGM41295_HARDWARE		CFG_NO
#define FH_IC_SGM41282C_HARDWARE		CFG_YES
#define FH_IC_SGM2508_HARDWARE			CFG_YES

#define FH_IC_GN7161_HARDWARE			CFG_NO
#define FH_IC_GN7161_FIRMWARE_0Bv21_1_2_10		CFG_NO
#define FH_IC_GN7161_FIRMWARE_08v21_1_2_8		CFG_NO

#define FH_IC_GN7153_HARDWARE			CFG_YES
#define FH_IC_UX3326_HARDWARE			CFG_YES




#endif

/* add by fz, 20250115, ԭ��:��ģ��ģ�� */
#if (MODULE_50G_10G_OPTICAL == CFG_YES) && (OPTICAL_MODELE_VERSION == A_SOFTWARE_VERSION)

/* add by fz, 20250113, ԭ��:��ģA�汾���� */
/*ctl�������ѹ2*/

#define	FH_IC_SGM41296_HARDWARE		CFG_YES

#define FH_IC_SGM41295_HARDWARE		CFG_NO
#define FH_IC_SGM41282C_HARDWARE		CFG_YES
#define FH_IC_SGM2508_HARDWARE			CFG_YES

#define FH_IC_GN7161_HARDWARE			CFG_NO
#define FH_IC_GN7161_FIRMWARE_0Bv21_1_2_10		CFG_NO
#define FH_IC_GN7161_FIRMWARE_08v21_1_2_8		CFG_NO


#define FH_IC_GN7153_HARDWARE			CFG_YES
#define FH_IC_UX3326_HARDWARE			CFG_YES

#define FH_IC_DSP_HARDWARE              CFG_YES


#endif


/* add by fz, 20250115, ԭ��:1ģ��ģ�� */
#if (MODULE_50G_OPTICAL == CFG_YES) && (OPTICAL_MODELE_VERSION == A_SOFTWARE_VERSION)

/* add by fz, 20250113, ԭ��:��ģA�汾���� */
/*ctl�������ѹ2*/

#define	FH_IC_SGM41296_HARDWARE		CFG_YES

#define FH_IC_SGM41295_HARDWARE		CFG_YES
#define FH_IC_SGM41282C_HARDWARE		CFG_YES
#define FH_IC_SGM2508_HARDWARE			CFG_NO

#define FH_IC_GN7161_HARDWARE			CFG_YES
#define FH_IC_GN7161_FIRMWARE_0Bv21_1_2_10		CFG_YES
#define FH_IC_GN7161_FIRMWARE_08v21_1_2_8		CFG_NO


#define FH_IC_GN7153_HARDWARE			CFG_YES
#define FH_IC_UX3326_HARDWARE			CFG_YES


#endif

#endif

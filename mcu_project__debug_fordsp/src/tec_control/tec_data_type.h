/***********************************************************************************

 * �� �� ��   : tec_data_type.h
 * �� �� ��   : fangzhe
 * ��������   : 2025��3��23��
 * �ļ�����   : ����tec�����ݽṹ
 * ��Ȩ˵��   : Copyright (C) 2000-2025   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#ifndef _TEC_DATA_TYPE_H_
#define _TEC_DATA_TYPE_H_

#include "gd32e501.h"
#include "user_config.h"

typedef struct _TEC_GLOBAL_VARS_PARAM_
{
	/*************************************************************************
	* �������ܣ�tec��ctl�ĳ�ʼֵ������ѹ
	* ȡֵ��Χ����ʼֵΪ1.25v;����SGM1296оƬ�ֲᣬ1.25vʱ,tec����������
	* ע�������
	*************************************************************************/
	float g_ctl_voltage_set;


	/*************************************************************************
	* �������ܣ�tec ���Զ������� :��ȡ���������ѹ���¶ȵ�
	* ȡֵ��Χ��SET or RESET
	* ע�������Ӧ����Ĵ���:TEC_AUTO_REG,����û���õ�
	*************************************************************************/
	//uint8_t g_tec_auto_ctrl_flag;

	/*************************************************************************
	* �������ܣ�tec process��main�д�����
	* ȡֵ��Χ��SET�������У�RESET����رմ���
	* ע�������
	*************************************************************************/
	uint8_t g_tec_proc_flag;

	/*************************************************************************
	* �������ܣ�tec��pid�Զ����ƿ���
	* ȡֵ��Χ��SET or RESET
	* ע�������Ӧ����Ĵ���:TEC_CALC_CTRL_AUTO_REG
	*************************************************************************/
	uint8_t g_tec_calc_argum_auto_flag;



	/*************************************************************************
	* �������ܣ�tec��ctl����Ҫ������Ŀ���¶� * 100
	* ȡֵ��Χ��Ŀ���¶� * 100��Ϊ����
	* ע�������
	*************************************************************************/
	uint16_t g_tec_ctrl_temperautre_obj;

}TEC_GLOBAL_VARS_PARAM;

extern volatile TEC_GLOBAL_VARS_PARAM g_tec_vars_param;



#if defined(FH_IC_SGM41296_HARDWARE) && (FH_IC_SGM41296_HARDWARE == CFG_YES)

#include "sgm41296_tec.h"
#define TEC_CTL_DISABLE_VALUE		(SGM41296_CTL_ZERO_VOLTAGE)

#else

#error "not define TEC_CTL_DISABLE_VALUE"

#endif


/*ctl�������ѹ2*/
#define TEC_CTL_VOLTAGE_OUT_MAX			2

/*��С�����ѹ*/
#define TEC_CTL_VOLTAGE_OUT_MIN			0.45

/*�仯�Ĳ�ֵ��float��*/
#define TEC_CTL_MAX_FLOAT_OFFSET			0.1

/*�仯�Ĳ�ֵ ,int�ͣ�TEC_CTL_MAX_FLOAT_OFFSET * 100*/
#define TEC_CTL_MAX_INT_OFFSET				10

/*Ŀ���¶�50�ȣ���100*/
#define TEC_TEMP_OBJ				g_tec_vars_param.g_tec_ctrl_temperautre_obj//5000 

#endif



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcu_global_vars_param.h"

/*************************************************************************
* �������ܣ�mcu�ж���ȫ�ֱ�����װ�ɽṹ��
* ȡֵ��Χ��mcu�ж����ȫ�ֱ���
* ע�������
*************************************************************************/
volatile  GLOBAL_VARS_PARAM g_mcu_vars_param;


/*****************************************************************************
 * �� �� ��  : global_vars_param_init
 * �� �� ��  : fz
 * ��������  : 2025��2��21��
 * ��������  : ��ʼ��ȫ�ֱ���
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : 

*****************************************************************************/
void global_vars_param_init()
{	
	/* add by fz, 20250225, ԭ��:Ĭ���ǲ����� */
	
	g_mcu_vars_param.g_update_process_flag = RESET;
	g_mcu_vars_param.g_50g_ddm_sw_auto_process_flag = RESET;
	g_mcu_vars_param.g_10g_ddm_sw_auto_process_flag = RESET;
	g_mcu_vars_param.g_1g_ddm_sw_auto_process_flag = RESET;
	g_mcu_vars_param.g_ddm_sw_auto_process_flag = SET;


	g_mcu_vars_param.g_sys_tick_period = 0;

	/* add by fz, 20250220, ԭ��:ִ��pid�㷨ʱ��ʱ���� */
	g_mcu_vars_param.g_tec_pid_calc_ms_task = 0;

	/* add by fz, 20250212, ԭ��:����ddm��ѯ���� */
	g_mcu_vars_param.g_ddm_process_ms_task = 0;

	/* add by fz, 20250212, ԭ��:���ڴ�ӡ������� */
	g_mcu_vars_param.g_check_print_ms_task = 0;  

    g_mcu_vars_param.g_i2c_exception_irq_status_counter = 0;
	return;
	
}

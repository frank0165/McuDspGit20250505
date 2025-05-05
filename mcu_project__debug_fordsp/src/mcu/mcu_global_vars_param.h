#ifndef _MCU_GLOBAL_VARS_PARAM_
#define _MCU_GLOBAL_VARS_PARAM_

#include "gd32e501.h"

typedef struct _GLOBAL_VARS_PARAM_
{
	/* add by fz, 20250225, ԭ��:������ʶ */
	uint8_t g_update_process_flag;
	uint8_t g_50g_ddm_sw_auto_process_flag;
	
	uint8_t g_10g_ddm_sw_auto_process_flag;
	
	uint8_t g_1g_ddm_sw_auto_process_flag;
	
	uint8_t g_ddm_sw_auto_process_flag;

    /*trigger��������*/
    uint32_t g_trigger_count;


	uint32_t g_sys_tick_period;

/* add by fz, 20250220, ԭ��:ִ��pid�㷨ʱ��ʱ���� */
	uint32_t g_tec_pid_calc_ms_task;

/* add by fz, 20250212, ԭ��:����ddm��ѯ���� */
	uint32_t g_ddm_process_ms_task;

/* add by fz, 20250212, ԭ��:���ڴ�ӡ������� */
	uint32_t g_check_print_ms_task;

    uint32_t g_dsp_fw_ticks_ret;
    uint32_t g_dsp_fw_version_ret;  
    uint32_t g_i2c_exception_irq_status_counter;
	
}GLOBAL_VARS_PARAM __attribute__((aligned(4)));


extern volatile GLOBAL_VARS_PARAM g_mcu_vars_param;



/*��ʱ��ms(�������)*/
//#define MCU_TIMER_MS_PERIOD				g_mcu_vars_param.g_timer_iterrupt_period


/*��ʱ��sec(�����)*/
//#define MCU_TIMER_SECS_PERIOD				(MCU_TIMER_MS_PERIOD / 1000)

/*ϵͳ��ʱ������*/
/*ϵͳms ����*/
#define MCU_SYSTEM_MS_PERIOD					g_mcu_vars_param.g_sys_tick_period

/*ϵͳsecs ��*/
#define MCU_SYSTEM_SECS_PERIOD					(MCU_SYSTEM_MS_PERIOD / 1000)


#define TEC_PID_CALC_MS_TASK					g_mcu_vars_param.g_tec_pid_calc_ms_task


#define DDM_PROCESS_MS_TASK			g_mcu_vars_param.g_ddm_process_ms_task


#define PRINT_CHECK_MS_TASK			g_mcu_vars_param.g_check_print_ms_task


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
void global_vars_param_init();



#endif
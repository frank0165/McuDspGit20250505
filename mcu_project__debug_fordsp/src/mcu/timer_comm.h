
/******************************************************************************
*****

 * �� �� ��   : timer_common.h
 * �� �� ��   : fz
 * ��������   : 2023��4��12��
 * �ļ�����   : timerͨ���ӿ�
 * ��Ȩ˵��   : Copyright (C) 2000-2023   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

*******************************************************************************
****/


#ifndef _TIMER_COMMON_H_
#define _TIMER_COMMON_H_

#include "gd32e501.h"


/* delete by fz, 20250310, ԭ��:�˴���ʱ��ֻ�õ��ã���ʽ�汾�в��õ� */
#if 0
/*һ�㶨ʱ��������������ʱ���������µ�ʹ��*/
#define COMMON_TIMER						TIMER13
#define RCU_COMMON_TIMER					RCU_TIMER13
#define COMMON_TIMER_IRQn					TIMER13_IRQn
#define COMMON_TIMER_IRQHandler			TIMER13_IRQHandler
#endif

/* delete end by fz, 20250310 */

/*****************************************************************************
 * �� �� ��  : timer_process_init
 * �� �� ��  : fz
 * ��������  : 2023��7��20��
 * ��������  : ��ʱ��������̳�ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void timer_process_init(void);

//void timer_trigger_config_init(void);

//void timer_counter_config_init(void);

#endif
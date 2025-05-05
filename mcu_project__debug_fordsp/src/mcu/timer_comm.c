/***********************************************************************************

 * �� �� ��   : timer_comm.c
 * �� �� ��   : fz
 * ��������   : 2023��5��25��
 * �ļ�����   : ��ʱ��
 * ��Ȩ˵��   : Copyright (C) 2000-2023   ���ͨ�ſƼ��ɷ����޹�˾
 * ��    ��   : 
 * �޸���־   : 

***********************************************************************************/

#include <stdio.h>
#include "timer_comm.h"


/* delete by fz, 20250310, ԭ��:��ʽ�汾�в����ⲿ��ʱ��timer ,timerֻ���ڵ���*/

#if 0


/**
    \brief      configure the TIMER peripheral
    \param[in]  none
    \param[out] none
    \retval     none
  */
void timer_trigger_config_init(void)
{
    /* -----------------------------------------------------------------------
    TIMER2 configuration: generate 3 PWM signals with 3 different duty cycles:
    TIMER2CLK = SystemCoreClock / 100 = 1MHz, the PWM frequency is 62.5Hz.
    TIMER2 channel1 duty cycle = (8000/ 16000)* 100  = 50%
    ----------------------------------------------------------------------- */
    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;

    /* enable the TIMER clock */
    rcu_periph_clock_enable(RCU_TIMER0);
    /* deinit a TIMER */
    timer_deinit(TIMER0);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER2 configuration */
    timer_initpara.prescaler         = 99;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 15999;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER0, &timer_initpara);

    /* initialize TIMER channel output parameter struct */
    timer_channel_output_struct_para_init(&timer_ocinitpara);
    /* configure TIMER channel output function */
    timer_ocinitpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocinitpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocinitpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    timer_channel_output_config(TIMER0, TIMER_CH_3, &timer_ocinitpara);

    /* CH1 configuration in PWM mode0, duty cycle 50% */
    timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_3, 8000);
    timer_channel_output_mode_config(TIMER0, TIMER_CH_3, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER0, TIMER_CH_3, TIMER_OC_SHADOW_DISABLE);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER0);
			
    /* auto-reload preload enable */
    timer_enable(TIMER0);
}

/**
    \brief      configure the TIMER peripheral
    \param[in]  none
    \param[out] none
    \retval     none
  */
/*PA1, ��ʱ��TIMER1,*/



/*****************************************************************************
 * �� �� ��  : timer_device_config
 * �� �� ��  : fz
 * ��������  : 2023��7��20��
 * ��������  : ���ö�ʱ��peripheral
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : ��

*****************************************************************************/
void timer_device_config(void)
{
    /* ----------------------------------------------------------------------
------
    TIMER2 Configuration: 
    TIMER2CLK = SystemCoreClock/10000 = 10KHz, the period is 1s(10000/10000 = 
1s).��SysTick_Config()
    -------------------------------------------------------------------------
--- */
    timer_parameter_struct timer_initpara;

    /* enable the peripherals clock */
    rcu_periph_clock_enable(RCU_COMMON_TIMER);

    /* deinit a TIMER */
    timer_deinit(COMMON_TIMER);
	
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
	
    /* TIMER2 configuration */
	/*100M��ƵΪ10K;*/
    timer_initpara.prescaler         = 9999; /*10000 - 1,10KHz��Ƶ10000;9999*/
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE; /*���������ؼ���ģʽ��*/
    timer_initpara.counterdirection  = TIMER_COUNTER_UP; /*�������ϼ���ģʽ��*/

	/*9999; ���� 10000 - 1������10000����1 s;����10-1�� 1 ms,����10000/1000 = 10*/
    timer_initpara.period            = 9;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_init(COMMON_TIMER, &timer_initpara);

    /* clear channel 0 interrupt bit */
    timer_interrupt_flag_clear(COMMON_TIMER, TIMER_INT_FLAG_UP);
	
    /* enable the TIMER interrupt */
    timer_interrupt_enable(COMMON_TIMER, TIMER_INT_UP);
	
    /* enable a TIMER */
    timer_enable(COMMON_TIMER);

	nvic_irq_enable(COMMON_TIMER_IRQn, 0, 4);
	
}

#endif


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
void timer_process_init(void)
{
	//timer_device_config();

	/*��ʱ��*/
	
}



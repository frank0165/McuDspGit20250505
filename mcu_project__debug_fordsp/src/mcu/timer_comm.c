/***********************************************************************************

 * 文 件 名   : timer_comm.c
 * 负 责 人   : fz
 * 创建日期   : 2023年5月25日
 * 文件描述   : 定时器
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#include <stdio.h>
#include "timer_comm.h"


/* delete by fz, 20250310, 原因:正式版本中不用外部定时器timer ,timer只用于调试*/

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
/*PA1, 定时器TIMER1,*/



/*****************************************************************************
 * 函 数 名  : timer_device_config
 * 负 责 人  : fz
 * 创建日期  : 2023年7月20日
 * 函数功能  : 配置定时器peripheral
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
void timer_device_config(void)
{
    /* ----------------------------------------------------------------------
------
    TIMER2 Configuration: 
    TIMER2CLK = SystemCoreClock/10000 = 10KHz, the period is 1s(10000/10000 = 
1s).见SysTick_Config()
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
	/*100M分频为10K;*/
    timer_initpara.prescaler         = 9999; /*10000 - 1,10KHz分频10000;9999*/
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE; /*设置上升沿计数模式；*/
    timer_initpara.counterdirection  = TIMER_COUNTER_UP; /*设置向上计数模式；*/

	/*9999; 计数 10000 - 1，计数10000才是1 s;计数10-1是 1 ms,就是10000/1000 = 10*/
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
 * 函 数 名  : timer_process_init
 * 负 责 人  : fz
 * 创建日期  : 2023年7月20日
 * 函数功能  : 定时器处理过程初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 外部调用
 * 其    它  : 无

*****************************************************************************/
void timer_process_init(void)
{
	//timer_device_config();

	/*定时器*/
	
}



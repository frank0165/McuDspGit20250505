/***********************************************************************************

 * 文 件 名   : trigger_interrupt_mode.h
 * 负 责 人   : fz
 * 创建日期   : 2025年2月23日
 * 文件描述   : 设置trigger中断操作
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#ifndef _TRIGGER_INTERRUTP_MODE_H_
#define _TRIGGER_INTERRUTP_MODE_H_


#if 0
	/* enable and set key EXTI interrupt priority */
	nvic_irq_enable(EXTI0_1_IRQn, NIVC_IRQ_GROUP, TRIGGER_EXIT0_IRQ_PRI);
	/* connect key EXTI line to key GPIO pin */
	syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN0);
	/* configure key EXTI line */
	exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
	exti_interrupt_flag_clear(EXTI_0);//EXTI0_1_IRQHandler事件定义见Gd32e501_it.c

#endif

#define TRIGGER_EXTI_IRQn                EXTI4_15_IRQn
#define TRIGGER_EXI_GPIO_SOURCE      EXTI_SOURCE_GPIOB
#define TRIGGER_EXTI_GPIO_PIN     EXTI_SOURCE_PIN15
#define TRIGGER_EXTI_LINE           EXTI_15

/* this function handles external lines 0 to 1 interrupt request */
//void EXTI0_1_IRQHandler(void);
#define TRIGGER_EXTI_IRQHandler         EXTI4_15_IRQHandler

void mcu_trigger_mode_init();

#endif


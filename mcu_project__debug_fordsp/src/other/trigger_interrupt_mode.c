#include "gd32e501.h"
#include "trigger_interrupt_mode.h"
#include "mcu_data_type.h"
#include "mcu_pin_type.h"


//void timer_trigger_config_init(void)


/*****************************************************************************
 * 函 数 名  : mcu_trigger_gpion_init
 * 负 责 人  : fz
 * 创建日期  : 2025年2月25日
 * 函数功能  : mcu上的trigger脚初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void mcu_trigger_gpion_init()
{
	/* configure GPIO PB0 as EXTI */
	gpio_mode_set(GPIO_TRIGGER_PORT_GOLDFINGER, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_TRIGGER_PIN_GOLDFINGER);
	gpio_output_options_set(GPIO_TRIGGER_PORT_GOLDFINGER, GPIO_PUPD_NONE, GPIO_OSPEED_50MHZ, GPIO_TRIGGER_PIN_GOLDFINGER);
	
}


/*****************************************************************************
 * 函 数 名  : mcu_trigger_mode_init
 * 负 责 人  : fz
 * 创建日期  : 2025年2月25日
 * 函数功能  : 初始化trigger的中断方式
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void mcu_trigger_mode_init()
{
	mcu_trigger_gpion_init();

#if 0
	/* enable and set key EXTI interrupt priority */
	nvic_irq_enable(EXTI0_1_IRQn, NIVC_IRQ_GROUP, TRIGGER_EXIT0_IRQ_PRI);
	/* connect key EXTI line to key GPIO pin */
	syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN0);
	/* configure key EXTI line */
	exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
	exti_interrupt_flag_clear(EXTI_0);//EXTI0_1_IRQHandler事件定义见Gd32e501_it.c

    #define TRIGGER_EXTI_IRQn                EXTI4_15_IRQn
#define TRIGGER_EXI_GPIO_SOURCE      GPIOB
#define TRIGGER_EXTI_GPIO_PIN     EXTI_SOURCE_PIN15
#define TRIGGER_EXTI_LINE           EXTI_15

#endif

    /* add by fangzhe, 20250327, 原因:trigger脚换成pb15 */
/* enable and set key EXTI interrupt priority */
	nvic_irq_enable(TRIGGER_EXTI_IRQn, NIVC_IRQ_GROUP, TRIGGER_EXIT15_IRQ_PRI);
	/* connect key EXTI line to key GPIO pin */
	syscfg_exti_line_config(TRIGGER_EXI_GPIO_SOURCE, TRIGGER_EXTI_GPIO_PIN);
	/* configure key EXTI line */
	exti_init(TRIGGER_EXTI_LINE, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
	exti_interrupt_flag_clear(TRIGGER_EXTI_LINE);

    
}

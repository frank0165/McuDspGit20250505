#include "gd32e501.h"
#include "trigger_interrupt_mode.h"
#include "mcu_data_type.h"
#include "mcu_pin_type.h"


//void timer_trigger_config_init(void)


/*****************************************************************************
 * �� �� ��  : mcu_trigger_gpion_init
 * �� �� ��  : fz
 * ��������  : 2025��2��25��
 * ��������  : mcu�ϵ�trigger�ų�ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void mcu_trigger_gpion_init()
{
	/* configure GPIO PB0 as EXTI */
	gpio_mode_set(GPIO_TRIGGER_PORT_GOLDFINGER, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_TRIGGER_PIN_GOLDFINGER);
	gpio_output_options_set(GPIO_TRIGGER_PORT_GOLDFINGER, GPIO_PUPD_NONE, GPIO_OSPEED_50MHZ, GPIO_TRIGGER_PIN_GOLDFINGER);
	
}


/*****************************************************************************
 * �� �� ��  : mcu_trigger_mode_init
 * �� �� ��  : fz
 * ��������  : 2025��2��25��
 * ��������  : ��ʼ��trigger���жϷ�ʽ
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

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
	exti_interrupt_flag_clear(EXTI_0);//EXTI0_1_IRQHandler�¼������Gd32e501_it.c

    #define TRIGGER_EXTI_IRQn                EXTI4_15_IRQn
#define TRIGGER_EXI_GPIO_SOURCE      GPIOB
#define TRIGGER_EXTI_GPIO_PIN     EXTI_SOURCE_PIN15
#define TRIGGER_EXTI_LINE           EXTI_15

#endif

    /* add by fangzhe, 20250327, ԭ��:trigger�Ż���pb15 */
/* enable and set key EXTI interrupt priority */
	nvic_irq_enable(TRIGGER_EXTI_IRQn, NIVC_IRQ_GROUP, TRIGGER_EXIT15_IRQ_PRI);
	/* connect key EXTI line to key GPIO pin */
	syscfg_exti_line_config(TRIGGER_EXI_GPIO_SOURCE, TRIGGER_EXTI_GPIO_PIN);
	/* configure key EXTI line */
	exti_init(TRIGGER_EXTI_LINE, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
	exti_interrupt_flag_clear(TRIGGER_EXTI_LINE);

    
}

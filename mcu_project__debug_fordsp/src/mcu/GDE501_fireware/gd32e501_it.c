/*!
    \file    gd32e501_it.c
    \brief   interrupt service routines
    
    \version 2020-03-02, V1.0.0, firmware for GD32E501
    \version 2020-04-10, V1.0.1, firmware for GD32E501
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32e501_it.h"
#include "systick.h"
#include "mcu_global_vars_param.h"
#include "i2c_opt_ie_interface.h"
#include "timer_comm.h"
#include "trigger_interrupt_mode.h"


#if 0

/*定时器2的计数*/
volatile uint32_t g_timer_iterrupt_period = 0;

volatile uint32_t g_sys_tick_period = 0;

/* add by fz, 20250220, 原因:执行pid算法时的时间间隔 */
volatile uint32_t g_tec_pid_calc_ms_task = 0;

/* add by fz, 20250212, 原因:用于ddm轮询任务 */
volatile uint32_t g_ddm_process_ms_task = 0;

/* add by fz, 20250212, 原因:用于打印检查任务 */
volatile uint32_t g_check_print_ms_task = 0;

#endif

extern void ddm_50g_rssi_start_sample_adc_action();
extern void ddm_10g_rssi_start_sample_adc_action();
extern void ddm_1g_rssi_start_sample_adc_action();

/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while(1){
    }
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{
}

/*!
    \brief      this function handles I2C0 event interrupt request exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MASTER_A_EV_IRQHandler(void)
{  
  	master_i2c_event_irq_handler(MASTER_A_I2C);
}

/*!
    \brief      this function handles I2C0 error interrupt request exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MASTER_A_ER_IRQHandler(void)
{ 
   master_i2c_error_irq_handler(MASTER_A_I2C);
}

void MASTER_B_EV_IRQHandler(void)
{  
  	master_i2c_event_irq_handler(MASTER_B_I2C);
}

/*!
    \brief      this function handles I2C0 error interrupt request exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MASTER_B_ER_IRQHandler(void)
{ 
   master_i2c_error_irq_handler(MASTER_B_I2C);
}

/*!
    \brief      this function handles I2C1 event interrupt request exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SLAVE_EV_IRQHandler(void)
{  
	slave_event_irq_handler(SLAVE_I2C);
}

/*!
    \brief      this function handles I2C1 error interrupt request exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SLAVE_ER_IRQHandler(void)
{
  
  	slave_error_irq_handler();
}


/* delete by fz, 20250310, 原因:没用这个定时器，代码屏蔽掉 */

#if 0

/*!
    \brief      this function handles TIMER2 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void COMMON_TIMER_IRQHandler(void)
{
    if(SET == timer_interrupt_flag_get(COMMON_TIMER, TIMER_INT_FLAG_UP))
	{
        /* clear channel 0 interrupt bit */
        timer_interrupt_flag_clear(COMMON_TIMER, TIMER_INT_FLAG_UP);
		g_mcu_vars_param.g_timer_iterrupt_period++;
		
        
    }
}

#endif

/* delete end by fz, 20250310 */



/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{	
	g_mcu_vars_param.g_sys_tick_period++;
	g_mcu_vars_param.g_ddm_process_ms_task++;
	g_mcu_vars_param.g_check_print_ms_task++;
	g_mcu_vars_param.g_tec_pid_calc_ms_task++;
	
    delay_decrement();
}



/*!
    \brief      this function handles external lines 0 to 1 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/

void TRIGGER_EXTI_IRQHandler(void)
{
	uint16_t data = 0;
	if(RESET != exti_interrupt_flag_get(TRIGGER_EXTI_LINE)){
		/* enable ADC software trigger of burst mode*/
			
		g_mcu_vars_param.g_trigger_count++;

		/* add by fz, 20250303, 原因:先清除注入组转换标专 */
		ddm_50g_rssi_start_sample_adc_action();
		ddm_10g_rssi_start_sample_adc_action();
		ddm_1g_rssi_start_sample_adc_action();	

		 // 再清除外部中断标志；
		 //放在后是因为确保adc采样完成后才清除外部中断，避免adc采样未完成而产生
		 //新的外部中断
		exti_interrupt_flag_clear(TRIGGER_EXTI_LINE);
	
	}
}

#if 1
//uint8_t transmitter_buffer[] = "\n\rUSART interrupt test\n\r";
uint8_t g_usart_receiver_buffer[32];
//uint8_t usart_transfersize = TRANSMIT_SIZE;
uint8_t g_usart_receivesize = 32;
__IO uint8_t g_usart_txcount = 0; 
__IO uint16_t g_usart_rxcount = 0; 

/*!
    \brief      this function handles USART RBNE interrupt request and TBE 
interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USART0_IRQHandler(void)
{
    if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE)){
        /* receive data */
        g_usart_receiver_buffer[g_usart_rxcount++] = usart_data_receive(USART0);
        if(g_usart_rxcount == g_usart_receivesize){
            usart_interrupt_disable(USART0, USART_INT_RBNE);
        }
    }

    if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_TBE)){
        /* transmit data */
        usart_data_transmit(USART0, g_usart_receiver_buffer[g_usart_rxcount++]);
        if(g_usart_rxcount == g_usart_receivesize){
            usart_interrupt_disable(USART0, USART_INT_TBE);
        }
    }
}

#endif

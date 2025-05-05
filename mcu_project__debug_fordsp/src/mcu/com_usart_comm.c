/*!
    \file    main.c
    \brief   USART transmit and receive interrupt
    
    \version 2020-03-23, V1.0.0, demo for GD32E501
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without 
modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, 
this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright 
notice, 
       this list of conditions and the following disclaimer in the 
documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its 
contributors 
       may be used to endorse or promote products derived from this software 
without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS
" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING
, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA
, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32e501.h"
#include "mcu_pin_type.h"
#include "com_usart_comm.h"
#include <stdio.h>

#define ARRAYNUM(arr_nanme)      (uint32_t)(sizeof(arr_nanme) / sizeof(*(arr_nanme)))
//#define TRANSMIT_SIZE            (ARRAYNUM(transmitter_buffer) - 1)

void com_usart_gpio_config(void)
{
	
	/*******************usart PA9,PA10*************************************/
  /* connect port to USARTx_Tx */
	gpio_af_set(GPIO_USART_PORT, GPIO_AF_1, GPIO_USART_TX_PIN);
	
	/* connect port to USARTx_Rx */
	gpio_af_set(GPIO_USART_PORT, GPIO_AF_1, GPIO_USART_RX_PIN);

	/* configure USART Tx as alternate function push-pull */
	gpio_mode_set(GPIO_USART_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_USART_TX_PIN);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, 
		GPIO_USART_TX_PIN);

	/* configure USART Rx as alternate function push-pull */
	gpio_mode_set(GPIO_USART_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
	gpio_output_options_set(GPIO_USART_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, 
		GPIO_PIN_10);
	/********************** end *********************************************/
}

/*!
    \brief      initialize the USART configuration of the com
    \param[in]  none
    \param[out] none
    \retval     none
*/
void com_usart_init(void)
{
  
    /* USART configure */
    usart_deinit(USART_PERIPH);
    usart_word_length_set(USART_PERIPH, USART_WL_8BIT);
    usart_stop_bit_set(USART_PERIPH, USART_STB_1BIT);
    usart_parity_config(USART_PERIPH, USART_PM_NONE);
    usart_baudrate_set(USART_PERIPH, 115200U);
    usart_receive_config(USART_PERIPH, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART_PERIPH, USART_TRANSMIT_ENABLE);

    usart_enable(USART_PERIPH);
	usart_interrupt_enable(USART_PERIPH, USART_INT_TBE);

	com_usart_gpio_config();
}




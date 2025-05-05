/*!
    \file    gd32e501_cla.c
    \brief   CLA driver

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

#include "gd32e501_cla.h"

/*!
    \brief      reset CLA
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cla_deinit(void)
{
    rcu_periph_reset_enable(RCU_CLARST);
    rcu_periph_reset_disable(RCU_CLARST);
}

/*!
    \brief      enable CLA
    \param[in]  cla_periph: CLAx(x=0,1,2,3,,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cla_enable(cla_enum cla_periph)
{
    switch(cla_periph){
        case CLA0:
             CLA_GCTL |= CLA_GCTL_CLA0EN;
             break;
        case CLA1:
             CLA_GCTL |= CLA_GCTL_CLA1EN;
             break;
        case CLA2:
             CLA_GCTL |= CLA_GCTL_CLA2EN;
             break;
        case CLA3:
             CLA_GCTL |= CLA_GCTL_CLA3EN;
             break;
        case CLA4:
             CLA_GCTL |= CLA_GCTL_CLA4EN;
             break;
        case CLA5:
             CLA_GCTL |= CLA_GCTL_CLA5EN;
             break;
        case CLA6:
             CLA_GCTL |= CLA_GCTL_CLA6EN;
             break;
        case CLA7:
             CLA_GCTL |= CLA_GCTL_CLA7EN;
             break;
        default: 
             break;
    }
}

/*!
    \brief      disable CLA
    \param[in]  cla_periph: CLAx(x=0,1,2,3,,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cla_disable(cla_enum cla_periph)
{
    switch(cla_periph){
        case CLA0:
             CLA_GCTL &= (~CLA_GCTL_CLA0EN);
             break;
        case CLA1:
             CLA_GCTL &= (~CLA_GCTL_CLA1EN);
             break;
        case CLA2:
             CLA_GCTL &= (~CLA_GCTL_CLA2EN);
             break;
        case CLA3:
             CLA_GCTL &= (~CLA_GCTL_CLA3EN);
             break;
        case CLA4:
             CLA_GCTL &= (~CLA_GCTL_CLA4EN);
             break;
        case CLA5:
             CLA_GCTL &= (~CLA_GCTL_CLA5EN);
             break;
        case CLA6:
             CLA_GCTL &= (~CLA_GCTL_CLA6EN);
             break;
        case CLA7:
             CLA_GCTL &= (~CLA_GCTL_CLA7EN);
             break;
        default: 
             break;
    }
}

/*!
    \brief      get CLA output state
    \param[in]  cla_periph: CLAx(x=0,1,2,3,,4,5,6,7)
    \param[out] none
    \retval     cla_outputstatus_enum: CLA_OUTPUT_HIGH or CLA_OUTPUT_LOW
*/
cla_outputstatus_enum cla_output_state_get(cla_enum cla_periph)
{
    uint32_t state;
    uint32_t returnval;
    
    /* read cla status register */
    state = CLA_STAT;
    
    switch(cla_periph){
        case CLA0:
             returnval = (state & CLA_STAT_CLA0OUT);
             break;
        case CLA1:
             returnval = ((state & CLA_STAT_CLA1OUT)>>1);
             break;
        case CLA2:
             returnval = ((state & CLA_STAT_CLA2OUT)>>2);
             break;
        case CLA3:
             returnval = ((state & CLA_STAT_CLA3OUT)>>3);
             break;
        case CLA4:
             returnval = ((state & CLA_STAT_CLA4OUT)>>4);
             break;
        case CLA5:
             returnval = ((state & CLA_STAT_CLA5OUT)>>5);
             break;
        case CLA6:
             returnval = ((state & CLA_STAT_CLA6OUT)>>6);
             break;
        case CLA7:
             returnval = ((state & CLA_STAT_CLA7OUT)>>7);
             break;
        default:
             returnval = 0;
             break;
    }
    if(CLA_OUTPUT_HIGH == returnval){
        return CLA_OUTPUT_HIGH;
    }else{
        return CLA_OUTPUT_LOW;
    }
}

/*!
    \brief      configure signal selector input
    \param[in]  cla_periph: CLAx(x=0,1,2,3,,4,5,6,7)
    \param[in]  sigs: signal selector
                only one parameter can be selected which is shown as below:
                SIGS0: signal selector 0
                SIGS1: signal selector 1
    \param[in]  input: input of signal selector

     SIGS0 input selection:
     only one parameter can be selected which is shown as below:
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |  SIGS0[4:0]|      CLA0SIGS0             |      CLA1SIGS0             |      CLA2SIGS0             |     CLA3SIGS0            |      CLA4SIGS0             |      CLA5SIGS0             |      CLA6SIGS0             |     CLA7SIGS0            |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00000   | CLA0SIGS0_CLA0_ASYNC_OUT   | CLA1SIGS0_CLA0_ASYNC_OUT   | CLA2SIGS0_CLA0_ASYNC_OUT   | CLA3SIGS0_CLA0_ASYNC_OUT | CLA4SIGS0_CLA0_ASYNC_OUT   | CLA5SIGS0_CLA0_ASYNC_OUT   | CLA6SIGS0_CLA0_ASYNC_OUT   | CLA7SIGS0_CLA0_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00001   | CLA0SIGS0_CLA1_ASYNC_OUT   | CLA1SIGS0_CLA1_ASYNC_OUT   | CLA2SIGS0_CLA1_ASYNC_OUT   | CLA3SIGS0_CLA1_ASYNC_OUT | CLA4SIGS0_CLA1_ASYNC_OUT   | CLA5SIGS0_CLA1_ASYNC_OUT   | CLA6SIGS0_CLA1_ASYNC_OUT   | CLA7SIGS0_CLA1_ASYNC_OUT |
     -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00010   | CLA0SIGS0_CLA2_ASYNC_OUT   | CLA1SIGS0_CLA2_ASYNC_OUT   | CLA2SIGS0_CLA2_ASYNC_OUT   | CLA3SIGS0_CLA2_ASYNC_OUT | CLA4SIGS0_CLA2_ASYNC_OUT   | CLA5SIGS0_CLA2_ASYNC_OUT   | CLA6SIGS0_CLA2_ASYNC_OUT   | CLA7SIGS0_CLA2_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00011   | CLA3SIGS0_CLA3_ASYNC_OUT   | CLA1SIGS0_CLA3_ASYNC_OUT   | CLA2SIGS0_CLA3_ASYNC_OUT   | CLA3SIGS0_CLA3_ASYNC_OUT | CLA4SIGS0_CLA3_ASYNC_OUT   | CLA5SIGS0_CLA3_ASYNC_OUT   | CLA6SIGS0_CLA3_ASYNC_OUT   | CLA7SIGS0_CLA3_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00100   | CLA0SIGS0_TIMER1_TRGO      | CLA1SIGS0_TIMER1_TRGO      | CLA2SIGS0_TIMER1_TRGO      | CLA3SIGS0_TIMER1_TRGO    | CLA4SIGS0_TIMER1_TRGO      | CLA5SIGS0_TIMER1_TRGO      | CLA6SIGS0_TIMER1_TRGO      | CLA7SIGS0_TIMER1_TRGO    |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00101   | CLA0SIGS0_TIMER0_CH0       | CLA1SIGS0_TIMER0_CH0       | CLA2SIGS0_TIMER0_CH1       | CLA3SIGS0_TIMER0_CH2     | CLA4SIGS0_TIMER0_CH0       | CLA5SIGS0_TIMER0_CH0       | CLA6SIGS0_TIMER0_CH1       | CLA7SIGS0_TIMER0_CH2     |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00110   | CLA0SIGS0_TIMER0_CH1       | CLA1SIGS0_TIMER0_CH3       | CLA2SIGS0_TIMER0_CH3       | CLA3SIGS0_TIMER1_CH0     | CLA4SIGS0_TIMER0_CH1       | CLA5SIGS0_TIMER0_CH3       | CLA6SIGS0_TIMER0_CH3       | CLA7SIGS0_TIMER1_CH0     |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00111   | CLA0SIGS0_TIMER0_CH2       | CLA1SIGS0_TIMER1_CH0       | CLA2SIGS0_TIMER1_CH1       | CLA3SIGS0_TIMER1_CH1     | CLA4SIGS0_TIMER0_CH2       | CLA5SIGS0_TIMER1_CH0       | CLA6SIGS0_TIMER1_CH1       | CLA7SIGS0_TIMER1_CH1     |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01000   | CLA0SIGS0_CLAIN0           | CLA1SIGS0_CLAIN4           | CLA2SIGS0_CLAIN0           | CLA3SIGS0_CLAIN2         | CLA4SIGS0_CLAIN0           | CLA5SIGS0_CLAIN4           | CLA6SIGS0_CLAIN0           | CLA7SIGS0_CLAIN2         |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01001   | CLA0SIGS0_CLAIN2           | CLA1SIGS0_CLAIN5           | CLA2SIGS0_CLAIN1           | CLA3SIGS0_CLAIN3         | CLA4SIGS0_CLAIN2           | CLA5SIGS0_CLAIN5           | CLA6SIGS0_CLAIN1           | CLA7SIGS0_CLAIN3         |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01010   | CLA0SIGS0_CLAIN4           | CLA1SIGS0_CLAIN8           | CLA2SIGS0_CLAIN8           | CLA3SIGS0_CLAIN6         | CLA4SIGS0_CLAIN4           | CLA5SIGS0_CLAIN8           | CLA6SIGS0_CLAIN8           | CLA7SIGS0_CLAIN6         |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01011   | CLA0SIGS0_CLAIN6           | CLA1SIGS0_CLAIN10          | CLA2SIGS0_CLAIN9           | CLA3SIGS0_CLAIN7         | CLA4SIGS0_CLAIN6           | CLA5SIGS0_CLAIN10          | CLA6SIGS0_CLAIN9           | CLA7SIGS0_CLAIN7         |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01100   | CLA0SIGS0_CLAIN8           | CLA1SIGS0_CLAIN12          | CLA2SIGS0_CLAIN14          | CLA3SIGS0_CLAIN10        | CLA4SIGS0_CLAIN8           | CLA5SIGS0_CLAIN12          | CLA6SIGS0_CLAIN14          | CLA7SIGS0_CLAIN10        |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01101   | CLA0SIGS0_CLAIN10          | CLA1SIGS0_CLAIN13          | CLA2SIGS0_CLAIN15          | CLA3SIGS0_CLAIN11        | CLA4SIGS0_CLAIN10          | CLA5SIGS0_CLAIN13          | CLA6SIGS0_CLAIN15          | CLA7SIGS0_CLAIN11        |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01110   | CLA0SIGS0_CLAIN12          | CLA1SIGS0_CLAIN16          | CLA2SIGS0_CLAIN16          | CLA3SIGS0_CLAIN18        | CLA4SIGS0_CLAIN12          | CLA5SIGS0_CLAIN16          | CLA6SIGS0_CLAIN16          | CLA7SIGS0_CLAIN18        |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01111   | CLA0SIGS0_CLAIN14          | CLA1SIGS0_CLAIN18          | CLA2SIGS0_CLAIN17          | CLA3SIGS0_CLAIN19        | CLA4SIGS0_CLAIN14          | CLA5SIGS0_CLAIN18          | CLA6SIGS0_CLAIN17          | CLA7SIGS0_CLAIN19        |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    10000   | CLA0SIGS0_CLA4_ASYNC_OUT   | CLA1SIGS0_CLA4_ASYNC_OUT   | CLA2SIGS0_CLA4_ASYNC_OUT   | CLA3SIGS0_CLA4_ASYNC_OUT | CLA4SIGS0_CLA4_ASYNC_OUT   | CLA5SIGS0_CLA4_ASYNC_OUT   | CLA6SIGS0_CLA4_ASYNC_OUT   | CLA7SIGS0_CLA4_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    10001   | CLA0SIGS0_CLA5_ASYNC_OUT   | CLA1SIGS0_CLA5_ASYNC_OUT   | CLA2SIGS0_CLA5_ASYNC_OUT   | CLA3SIGS0_CLA5_ASYNC_OUT | CLA4SIGS0_CLA5_ASYNC_OUT   | CLA5SIGS0_CLA5_ASYNC_OUT   | CLA6SIGS0_CLA5_ASYNC_OUT   | CLA7SIGS0_CLA5_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------                  ------------------------------------------------------------------------------------------------------------------------
     |    10010   |           ---              | CLA1SIGS0_CLA6_ASYNC_OUT   | CLA2SIGS0_CLA6_ASYNC_OUT   | CLA3SIGS0_CLA6_ASYNC_OUT | CLA4SIGS0_CLA6_ASYNC_OUT   | CLA5SIGS0_CLA6_ASYNC_OUT   | CLA6SIGS0_CLA6_ASYNC_OUT   | CLA7SIGS0_CLA6_ASYNC_OUT |
     ------------------------------------------------------------------------------------------------------------- ------------------------------------------------------------------------------------------------------------------------------------
     |    10011   | CLA0SIGS0_CLA7_ASYNC_OUT   | CLA1SIGS0_CLA7_ASYNC_OUT   | CLA2SIGS0_CLA7_ASYNC_OUT   | CLA3SIGS0_CLA_7ASYNC_OUT | CLA4SIGS0_CLA7_ASYNC_OUT   | CLA5SIGS0_CLA7_ASYNC_OUT   | CLA6SIGS0_CLA7_ASYNC_OUT   | CLA7SIGS0_CLA_7ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     SIGS1 input selection:
     only one parameter can be selected which is shown as below:
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |  SIGS1[4:0]|      CLA0SIGS1             |      CLA1SIGS1             |       CLA2SIGS1            |     CLA3SIGS1            |      CLA4SIGS1             |      CLA5SIGS1             |       CLA6SIGS1            |     CLA7SIGS1            |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00000   | CLA0SIGS1_CLA0_ASYNC_OUT   | CLA1SIGS1_CLA0_ASYNC_OUT   | CLA2SIGS1_CLA0_ASYNC_OUT   | CLA3SIGS1_CLA0_ASYNC_OUT | CLA4SIGS1_CLA0_ASYNC_OUT   | CLA5SIGS1_CLA0_ASYNC_OUT   | CLA6SIGS1_CLA0_ASYNC_OUT   | CLA7SIGS1_CLA0_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00001   | CLA0SIGS1_CLA1_ASYNC_OUT   | CLA1SIGS1_CLA1_ASYNC_OUT   | CLA2SIGS1_CLA1_ASYNC_OUT   | CLA3SIGS1_CLA1_ASYNC_OUT | CLA4SIGS1_CLA1_ASYNC_OUT   | CLA5SIGS1_CLA1_ASYNC_OUT   | CLA6SIGS1_CLA1_ASYNC_OUT   | CLA7SIGS1_CLA1_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00010   | CLA0SIGS1_CLA2_ASYNC_OUT   | CLA1SIGS1_CLA2_ASYNC_OUT   | CLA2SIGS1_CLA2_ASYNC_OUT   | CLA3SIGS1_CLA2_ASYNC_OUT | CLA4SIGS1_CLA2_ASYNC_OUT   | CLA5SIGS1_CLA2_ASYNC_OUT   | CLA6SIGS1_CLA2_ASYNC_OUT   | CLA7SIGS1_CLA2_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00011   | CLA0SIGS1_CLA3_ASYNC_OUT   | CLA1SIGS1_CLA3_ASYNC_OUT   | CLA2SIGS1_CLA3_ASYNC_OUT   | CLA3SIGS1_CLA3_ASYNC_OUT | CLA4SIGS1_CLA3_ASYNC_OUT   | CLA5SIGS1_CLA3_ASYNC_OUT   | CLA6SIGS1_CLA3_ASYNC_OUT   | CLA7SIGS1_CLA3_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00100   | CLA0SIGS1_ADC_CONV         | CLA1SIGS1_ADC_CONV         | CLA2SIGS1_ADC_CONV         | CLA3SIGS1_ADC_CONV       | CLA4SIGS1_ADC_CONV         | CLA5SIGS1_ADC_CONV         | CLA6SIGS1_ADC_CONV         | CLA7SIGS1_ADC_CONV       |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00101   | CLA0SIGS1_TIMER0_CH3       | CLA1SIGS1_TIMER0_CH1       | CLA2SIGS1_TIMER0_CH0       | CLA3SIGS1_TIMER0_CH0     | CLA4SIGS1_TIMER0_CH3       | CLA5SIGS1_TIMER0_CH1       | CLA6SIGS1_TIMER0_CH0       | CLA7SIGS1_TIMER0_CH0     |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00110   | CLA0SIGS1_TIMER1_CH0       | CLA1SIGS1_TIMER0_CH2       | CLA2SIGS1_TIMER0_CH2       | CLA3SIGS1_TIMER0_CH1     | CLA4SIGS1_TIMER1_CH0       | CLA5SIGS1_TIMER0_CH2       | CLA6SIGS1_TIMER0_CH2       | CLA7SIGS1_TIMER0_CH1     |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    00111   | CLA0SIGS1_TIMER1_CH1       | CLA1SIGS1_TIMER1_CH1       | CLA2SIGS1_TIMER1_CH0       | CLA3SIGS1_TIMER0_CH3     | CLA4SIGS1_TIMER2_CH1       | CLA5SIGS1_TIMER2_CH1       | CLA6SIGS1_TIMER1_CH0       | CLA7SIGS1_TIMER0_CH3     |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01000   | CLA0SIGS1_CLAIN1           | CLA1SIGS1_CLAIN6           | CLA2SIGS1_CLAIN2           | CLA3SIGS1_CLAIN0         | CLA4SIGS1_CLAIN1           | CLA5SIGS1_CLAIN6           | CLA6SIGS1_CLAIN2           | CLA7SIGS1_CLAIN0         |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01001   | CLA0SIGS1_CLAIN3           | CLA1SIGS1_CLAIN7           | CLA2SIGS1_CLAIN3           | CLA3SIGS1_CLAIN1         | CLA4SIGS1_CLAIN3           | CLA5SIGS1_CLAIN7           | CLA6SIGS1_CLAIN3           | CLA7SIGS1_CLAIN1         |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01010   | CLA0SIGS1_CLAIN5           | CLA1SIGS1_CLAIN9           | CLA2SIGS1_CLAIN10          | CLA3SIGS1_CLAIN4         | CLA4SIGS1_CLAIN5           | CLA5SIGS1_CLAIN9           | CLA6SIGS1_CLAIN10          | CLA7SIGS1_CLAIN4         |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01011   | CLA0SIGS1_CLAIN6           | CLA1SIGS1_CLAIN11          | CLA2SIGS1_CLAIN11          | CLA3SIGS1_CLAIN5         | CLA4SIGS1_CLAIN6           | CLA5SIGS1_CLAIN11          | CLA6SIGS1_CLAIN11          | CLA7SIGS1_CLAIN5         |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01100   | CLA0SIGS1_CLAIN9           | CLA1SIGS1_CLAIN14          | CLA2SIGS1_CLAIN12          | CLA3SIGS1_CLAIN8         | CLA4SIGS1_CLAIN9           | CLA5SIGS1_CLAIN14          | CLA6SIGS1_CLAIN12          | CLA7SIGS1_CLAIN8         |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01101   | CLA0SIGS1_CLAIN11          | CLA1SIGS1_CLAIN15          | CLA2SIGS1_CLAIN13          | CLA3SIGS1_CLAIN9         | CLA4SIGS1_CLAIN11          | CLA5SIGS1_CLAIN15          | CLA6SIGS1_CLAIN13          | CLA7SIGS1_CLAIN9         |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01110   | CLA0SIGS1_CLAIN11          | CLA1SIGS1_CLAIN15          | CLA2SIGS1_CLAIN13          | CLA3SIGS1_CLAIN9         | CLA4SIGS1_CLAIN11          | CLA5SIGS1_CLAIN15          | CLA6SIGS1_CLAIN13          | CLA7SIGS1_CLAIN9         |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    01111   | CLA0SIGS1_CLAIN13          | CLA1SIGS1_CLAIN17          | CLA2SIGS1_CLAIN18          | CLA3SIGS1_CLAIN16        | CLA4SIGS1_CLAIN13          | CLA5SIGS1_CLAIN17          | CLA6SIGS1_CLAIN18          | CLA7SIGS1_CLAIN16        |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    10000   | CLA0SIGS1_CLA4_ASYNC_OUT   | CLA1SIGS1_CLA4_ASYNC_OUT   | CLA2SIGS1_CLA4_ASYNC_OUT   | CLA3SIGS1_CLA4_ASYNC_OUT | CLA4SIGS1_CLA4_ASYNC_OUT   | CLA5SIGS1_CLA4_ASYNC_OUT   | CLA6SIGS1_CLA4_ASYNC_OUT   | CLA7SIGS1_CLA4_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    10001   | CLA0SIGS1_CLA5_ASYNC_OUT   | CLA1SIGS1_CLA5_ASYNC_OUT   | CLA2SIGS1_CLA5_ASYNC_OUT   | CLA3SIGS1_CLA5_ASYNC_OUT | CLA4SIGS1_CLA5_ASYNC_OUT   | CLA5SIGS1_CLA5_ASYNC_OUT   | CLA6SIGS1_CLA5_ASYNC_OUT   | CLA7SIGS1_CLA5_ASYNC_OUT |
     -------------------------------------------------------------------------------------------------------------------------- ------------------------------------------------------------------------------------------------------------------------
     |    10010   |         ---                | CLA1SIGS1_CLA6_ASYNC_OUT   | CLA2SIGS1_CLA6_ASYNC_OUT   | CLA3SIGS1_CLA6_ASYNC_OUT | CLA4SIGS1_CLA6_ASYNC_OUT   | CLA5SIGS1_CLA6_ASYNC_OUT   | CLA6SIGS1_CLA6_ASYNC_OUT   | CLA7SIGS1_CLA6_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     |    10011   | CLA0SIGS1_CLA7_ASYNC_OUT   | CLA1SIGS1_CLA7_ASYNC_OUT   | CLA2SIGS1_CLA7_ASYNC_OUT   | CLA3SIGS1_CLA7_ASYNC_OUT | CLA4SIGS1_CLA7_ASYNC_OUT   | CLA5SIGS1_CLA7_ASYNC_OUT   | CLA6SIGS1_CLA7_ASYNC_OUT   | CLA7SIGS1_CLA7_ASYNC_OUT |
     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    \param[out] none
    \retval     none
*/
void cla_sigs_input_config(cla_enum cla_periph, cla_sigs_enum sigs, uint32_t input)
{
    if(SIGS0 == sigs){
        CLA_SIGS(cla_periph) &= (~CLA_SIGS_SIGS0);
        CLA_SIGS(cla_periph) |= input;
    }else{
        CLA_SIGS(cla_periph) &= (~CLA_SIGS_SIGS1);
        CLA_SIGS(cla_periph) |= input;
    }
}

/*!
    \brief      configure CLA LCU control register value
    \param[in]  cla_periph: CLAx(x=0,1,2,3,,4,5,6,7)
    \param[in]  lcuctl_value: the value need to set
    \param[out] none
    \retval     none
*/
void cla_lcu_control_config(cla_enum cla_periph, uint8_t lcuctl_value)
{
    CLA_LCUCTL(cla_periph) &= (~CLA_LCU);
    CLA_LCUCTL(cla_periph) |= LCUCTL(lcuctl_value);
}

/*!
    \brief      configure CLA output
    \param[in]  cla_periph: CLAx(x=0,1,2,3,,4,5,6,7)
    \param[in]  output: output of CLA
                only one parameter can be selected which is shown as below:
                FLIP_FLOP_OUTPUT: flip-flop output is selected as CLA output
                LUT_RESULT: LUT result is selected as CLA output
    \param[out] none
    \retval     none
*/
void cla_output_config(cla_enum cla_periph, uint32_t output)
{
    CLA_CTL(cla_periph) &= (~CLA_CTL_OSEL);
    CLA_CTL(cla_periph) |= output;
}

/*!
    \brief      enable CLA output
    \param[in]  cla_periph: CLAx(x=0,1,2,3,,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cla_output_enable(cla_enum cla_periph)
{
    CLA_CTL(cla_periph) |= CLA_CTL_OEN;
}

/*!
    \brief      disable CLA output
    \param[in]  cla_periph: CLAx(x=0,1,2,3,,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cla_output_disable(cla_enum cla_periph)
{
    CLA_CTL(cla_periph) &= (~CLA_CTL_OEN);
}

/*!
    \brief      reset the flip-flop output asynchronously
    \param[in]  cla_periph: CLAx(x=0,1,2,3,,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cla_flip_flop_output_reset(cla_enum cla_periph)
{
    CLA_CTL(cla_periph) |= CLA_CTL_FFRST;
}

/*!
    \brief      configure clock polarity of flip-flop
    \param[in]  cla_periph: CLAx(x=0,1,2,3,,4,5,6,7)
    \param[in]  polarity: clock polarity of flip-flop
                only one parameter can be selected which is shown as below:
                CLA_CLOCKPOLARITY_POSEDGE: clock posedge is valid
                CLA_CLOCKPOLARITY_NEGEDGE: clock negedge is valid
    \param[out] none
    \retval     none
*/
void cla_flip_flop_clockpolarity_config(cla_enum cla_periph, uint32_t polarity)
{
    CLA_CTL(cla_periph) &= (~CLA_CTL_CPOL);
    CLA_CTL(cla_periph) |= polarity;
}

/*!
    \brief      configure clock source of flip-flop 
    \param[in]  cla_periph: CLAx(x=0,1,2,3,,4,5,6,7)
    \param[in]  clock_source: clock source of flip-flop
                only one parameter can be selected which is shown as below:
                PRE_CLA_LUT_RESULT: the result of the previous CLA units
                SIGS0_OUTPUT: the signal selector output of SIGS0
                HCLK: HCLK
                TIMER_TRGO: TIMER_TRGO
    \param[out] none
    \retval     none
*/
void cla_flip_flop_clocksource_config(cla_enum cla_periph, uint32_t clock_source)
{
    CLA_CTL(cla_periph) &= (~CLA_CTL_CSEL);
    CLA_CTL(cla_periph) |= clock_source;
}

/*!
    \brief      check CLA flag is set or not
    \param[in]  flag: CLA flags,refer to cla_flag_enum
                only one parameter can be selected which is shown as below:
                CLA_FLAG_CLA0NF: CLA0 unit negedge flag
                CLA_FLAG_CLA0PF: CLA0 unit posedge flag
                CLA_FLAG_CLA1NF: CLA1 unit negedge flag
                CLA_FLAG_CLA1PF: CLA1 unit posedge flag
                CLA_FLAG_CLA2NF: CLA2 unit negedge flag
                CLA_FLAG_CLA2PF: CLA2 unit posedge flag
                CLA_FLAG_CLA3NF: CLA3 unit negedge flag
                CLA_FLAG_CLA3PF: CLA3 unit posedge flag
                CLA_FLAG_CLA4NF: CLA4 unit negedge flag
                CLA_FLAG_CLA4PF: CLA4 unit posedge flag
                CLA_FLAG_CLA5NF: CLA5 unit negedge flag
                CLA_FLAG_CLA5PF: CLA5 unit posedge flag
                CLA_FLAG_CLA6NF: CLA6 unit negedge flag
                CLA_FLAG_CLA6PF: CLA6 unit posedge flag
                CLA_FLAG_CLA7NF: CLA7 unit negedge flag
                CLA_FLAG_CLA7PF: CLA7 unit posedge flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cla_flag_get(cla_flag_enum flag)
{
    uint32_t interrupt_flag_register;
    uint32_t returnval;
    
    interrupt_flag_register = CLA_INTF;
    
    switch(flag){
        case CLA_FLAG_CLA0NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA0NF);
             break;
        case CLA_FLAG_CLA0PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA0PF)>>1;
             break;
        case CLA_FLAG_CLA1NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA1NF)>>2;
             break;
        case CLA_FLAG_CLA1PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA1PF)>>3;
             break;
        case CLA_FLAG_CLA2NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA2NF)>>4;
             break;
        case CLA_FLAG_CLA2PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA2PF)>>5;
             break;
        case CLA_FLAG_CLA3NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA3NF)>>6;
             break;
        case CLA_FLAG_CLA3PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA3PF)>>7;
             break;
        case CLA_FLAG_CLA4NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA4NF)>>8;
             break;
        case CLA_FLAG_CLA4PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA4PF)>>9;
             break;
        case CLA_FLAG_CLA5NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA5NF)>>10;
             break;
        case CLA_FLAG_CLA5PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA5PF)>>11;
             break;
        case CLA_FLAG_CLA6NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA6NF)>>12;
             break;
        case CLA_FLAG_CLA6PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA6PF)>>13;
             break;
        case CLA_FLAG_CLA7NF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA7NF)>>14;
             break;
        case CLA_FLAG_CLA7PF:
             returnval = (interrupt_flag_register & CLA_INTF_CLA7PF)>>15;
             break;
        default:
             returnval = 0;
             break;
    }
    if(SET == returnval){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CLA flag
    \param[in]  flag: CLA flags,refer to cla_flag_enum
                only one parameter can be selected which is shown as below:
                CLA_FLAG_CLA0NF: CLA0 unit negedge flag
                CLA_FLAG_CLA0PF: CLA0 unit posedge flag
                CLA_FLAG_CLA1NF: CLA1 unit negedge flag
                CLA_FLAG_CLA1PF: CLA1 unit posedge flag
                CLA_FLAG_CLA2NF: CLA2 unit negedge flag
                CLA_FLAG_CLA2PF: CLA2 unit posedge flag
                CLA_FLAG_CLA3NF: CLA3 unit negedge flag
                CLA_FLAG_CLA3PF: CLA3 unit posedge flag
                CLA_FLAG_CLA4NF: CLA4 unit negedge flag
                CLA_FLAG_CLA4PF: CLA4 unit posedge flag
                CLA_FLAG_CLA5NF: CLA5 unit negedge flag
                CLA_FLAG_CLA5PF: CLA5 unit posedge flag
                CLA_FLAG_CLA6NF: CLA6 unit negedge flag
                CLA_FLAG_CLA6PF: CLA6 unit posedge flag
                CLA_FLAG_CLA7NF: CLA7 unit negedge flag
                CLA_FLAG_CLA7PF: CLA7 unit posedge flag
    \param[out] none
    \retval     none
*/
void cla_flag_clear(cla_flag_enum flag)
{
    switch(flag){
        case CLA_FLAG_CLA0NF:
             CLA_INTF &= (~CLA_INTF_CLA0NF);
             break;
        case CLA_FLAG_CLA0PF:
             CLA_INTF &= (~CLA_INTF_CLA0PF);
             break;
        case CLA_FLAG_CLA1NF:
             CLA_INTF &= (~CLA_INTF_CLA1NF);
             break;
        case CLA_FLAG_CLA1PF:
             CLA_INTF &= (~CLA_INTF_CLA1PF);
             break;
        case CLA_FLAG_CLA2NF:
             CLA_INTF &= (~CLA_INTF_CLA2NF);
             break;
        case CLA_FLAG_CLA2PF:
             CLA_INTF &= (~CLA_INTF_CLA2PF);
             break;
        case CLA_FLAG_CLA3NF:
             CLA_INTF &= (~CLA_INTF_CLA3NF);
             break;
        case CLA_FLAG_CLA3PF:
             CLA_INTF &= (~CLA_INTF_CLA3PF);
             break;
        case CLA_FLAG_CLA4NF:
             CLA_INTF &= (~CLA_INTF_CLA4NF);
             break;
        case CLA_FLAG_CLA4PF:
             CLA_INTF &= (~CLA_INTF_CLA4PF);
             break;
        case CLA_FLAG_CLA5NF:
             CLA_INTF &= (~CLA_INTF_CLA5NF);
             break;
        case CLA_FLAG_CLA5PF:
             CLA_INTF &= (~CLA_INTF_CLA5PF);
             break;
        case CLA_FLAG_CLA6NF:
             CLA_INTF &= (~CLA_INTF_CLA6NF);
             break;
        case CLA_FLAG_CLA6PF:
             CLA_INTF &= (~CLA_INTF_CLA6PF);
             break;
        case CLA_FLAG_CLA7NF:
             CLA_INTF &= (~CLA_INTF_CLA7NF);
             break;
        case CLA_FLAG_CLA7PF:
             CLA_INTF &= (~CLA_INTF_CLA7PF);
             break;
        default:
            break;
    }
}

/*!
    \brief      enable CLA negedge interrupt
    \param[in]  clanie: CLA negedge interrupt enable
                only one parameter can be selected which is shown as below:
                CLA0NIE: CLA0 negedge interrupt enable
                CLA1NIE: CLA1 negedge interrupt enable
                CLA2NIE: CLA2 negedge interrupt enable
                CLA3NIE: CLA3 negedge interrupt enable
                CLA4NIE: CLA4 negedge interrupt enable
                CLA5NIE: CLA5 negedge interrupt enable
                CLA6NIE: CLA6 negedge interrupt enable
                CLA7NIE: CLA7 negedge interrupt enable
    \param[out] none
    \retval     none
*/
void cla_negedge_interrupt_enable(uint32_t clanie)
{
    CLA_INTE |= clanie;
}

/*!
    \brief      disable CLA negedge interrupt
    \param[in]  clanidis: CLA negedge interrupt disable
                only one parameter can be selected which is shown as below:
                CLA0NI_DISABLE: CLA0 negedge interrupt disable
                CLA1NI_DISABLE: CLA1 negedge interrupt disable
                CLA2NI_DISABLE: CLA2 negedge interrupt disable
                CLA3NI_DISABLE: CLA3 negedge interrupt disable
                CLA4NI_DISABLE: CLA4 negedge interrupt disable
                CLA5NI_DISABLE: CLA5 negedge interrupt disable
                CLA6NI_DISABLE: CLA6 negedge interrupt disable
                CLA7NI_DISABLE: CLA7 negedge interrupt disable
    \param[out] none
    \retval     none
*/
void cla_negedge_interrupt_disable(uint32_t clanidis)
{
    CLA_INTE &= (~clanidis);
}

/*!
    \brief      enable CLA posedge interrupt
    \param[in]  clapie: CLA posedge interrupt enable
                only one parameter can be selected which is shown as below:
                CLA0PIE: CLA0 posedge interrupt enable
                CLA1PIE: CLA1 posedge interrupt enable
                CLA2PIE: CLA2 posedge interrupt enable
                CLA3PIE: CLA3 posedge interrupt enable
                CLA4PIE: CLA4 posedge interrupt enable
                CLA5PIE: CLA5 posedge interrupt enable
                CLA6PIE: CLA6 posedge interrupt enable
                CLA7PIE: CLA7 posedge interrupt enable
    \param[out] none
    \retval     none
*/
void cla_posedge_interrupt_enable(uint32_t clapie)
{
    CLA_INTE |= clapie;
}

/*!
    \brief      disable CLA posedge interrupt
    \param[in]  clapidis: CLA posedge interrupt disable
                only one parameter can be selected which is shown as below:
                CLA0PI_DISABLE: CLA0 posedge interrupt disable
                CLA1PI_DISABLE: CLA1 posedge interrupt disable
                CLA2PI_DISABLE: CLA2 posedge interrupt disable
                CLA3PI_DISABLE: CLA3 posedge interrupt disable
                CLA4PI_DISABLE: CLA4 posedge interrupt disable
                CLA5PI_DISABLE: CLA5 posedge interrupt disable
                CLA6PI_DISABLE: CLA6 posedge interrupt disable
                CLA7PI_DISABLE: CLA7 posedge interrupt disable
    \param[out] none
    \retval     none
*/
void cla_posedge_interrupt_disable(uint32_t clapidis)
{
    CLA_INTE &= (~clapidis);
}

/*!
    \brief      check CLA interrupt flag is set or not 
    \param[in]  int_flag: CLA interrupt flags,refer to cla_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
                CLA_INT_FLAG_CLA0NF: CLA0 unit negedge interrupt flag
                CLA_INT_FLAG_CLA0PF: CLA0 unit posedge interrupt flag
                CLA_INT_FLAG_CLA1NF: CLA1 unit negedge interrupt flag
                CLA_INT_FLAG_CLA1PF: CLA1 unit posedge interrupt flag
                CLA_INT_FLAG_CLA2NF: CLA2 unit negedge interrupt flag
                CLA_INT_FLAG_CLA2PF: CLA2 unit posedge interrupt flag
                CLA_INT_FLAG_CLA3NF: CLA3 unit negedge interrupt flag
                CLA_INT_FLAG_CLA3PF: CLA3 unit posedge interrupt flag
                CLA_INT_FLAG_CLA4NF: CLA4 unit negedge interrupt flag
                CLA_INT_FLAG_CLA4PF: CLA4 unit posedge interrupt flag
                CLA_INT_FLAG_CLA5NF: CLA5 unit negedge interrupt flag
                CLA_INT_FLAG_CLA5PF: CLA5 unit posedge interrupt flag
                CLA_INT_FLAG_CLA6NF: CLA6 unit negedge interrupt flag
                CLA_INT_FLAG_CLA6PF: CLA6 unit posedge interrupt flag
                CLA_INT_FLAG_CLA7NF: CLA7 unit negedge interrupt flag
                CLA_INT_FLAG_CLA7PF: CLA7 unit posedge interrupt flag
    \param[out] none
    \retval     none
*/
FlagStatus cla_interrupt_flag_get(cla_interrupt_flag_enum int_flag)
{
    uint32_t cla_inte = CLA_INTE;
    uint32_t cla_intf = CLA_INTF;
    
    switch(int_flag){
        case CLA_INT_FLAG_CLA0NF:
             cla_inte = cla_inte & CLA_INTE_CLA0NIE;
             cla_intf = cla_intf & CLA_INTF_CLA0NF;
             break;
        case CLA_INT_FLAG_CLA0PF:
             cla_inte = cla_inte & CLA_INTE_CLA0PIE;
             cla_intf = cla_intf & CLA_INTF_CLA0PF;
             break;
        case CLA_INT_FLAG_CLA1NF:
             cla_inte = cla_inte & CLA_INTE_CLA1NIE;
             cla_intf = cla_intf & CLA_INTF_CLA1NF;
             break;
        case CLA_INT_FLAG_CLA1PF:
             cla_inte = cla_inte & CLA_INTE_CLA1PIE;
             cla_intf = cla_intf & CLA_INTF_CLA1PF;
             break;
        case CLA_INT_FLAG_CLA2NF:
             cla_inte = cla_inte & CLA_INTE_CLA2NIE;
             cla_intf = cla_intf & CLA_INTF_CLA2NF;
             break;
        case CLA_INT_FLAG_CLA2PF:
             cla_inte = cla_inte & CLA_INTE_CLA2PIE;
             cla_intf = cla_intf & CLA_INTF_CLA2PF;
             break;
        case CLA_INT_FLAG_CLA3NF:
             cla_inte = cla_inte & CLA_INTE_CLA3NIE;
             cla_intf = cla_intf & CLA_INTF_CLA3NF;
             break;
        case CLA_INT_FLAG_CLA3PF:
             cla_inte = cla_inte & CLA_INTE_CLA3PIE;
             cla_intf = cla_intf & CLA_INTF_CLA3PF;
             break;
        case CLA_INT_FLAG_CLA4NF:
             cla_inte = cla_inte & CLA_INTE_CLA4NIE;
             cla_intf = cla_intf & CLA_INTF_CLA4NF;
             break;
        case CLA_INT_FLAG_CLA4PF:
             cla_inte = cla_inte & CLA_INTE_CLA4PIE;
             cla_intf = cla_intf & CLA_INTF_CLA4PF;
             break;
        case CLA_INT_FLAG_CLA5NF:
             cla_inte = cla_inte & CLA_INTE_CLA5NIE;
             cla_intf = cla_intf & CLA_INTF_CLA5NF;
             break;
        case CLA_INT_FLAG_CLA5PF:
             cla_inte = cla_inte & CLA_INTE_CLA5PIE;
             cla_intf = cla_intf & CLA_INTF_CLA5PF;
             break;
        case CLA_INT_FLAG_CLA6NF:
             cla_inte = cla_inte & CLA_INTE_CLA6NIE;
             cla_intf = cla_intf & CLA_INTF_CLA6NF;
             break;
        case CLA_INT_FLAG_CLA6PF:
             cla_inte = cla_inte & CLA_INTE_CLA6PIE;
             cla_intf = cla_intf & CLA_INTF_CLA6PF;
             break;
        case CLA_INT_FLAG_CLA7NF:
             cla_inte = cla_inte & CLA_INTE_CLA7NIE;
             cla_intf = cla_intf & CLA_INTF_CLA7NF;
             break;
        case CLA_INT_FLAG_CLA7PF:
             cla_inte = cla_inte & CLA_INTE_CLA7PIE;
             cla_intf = cla_intf & CLA_INTF_CLA7PF;
             break;
        default:
             break;
    }
    if((0U != cla_inte) && (0U != cla_intf)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CLA interrupt flag
    \param[in]  int_flag: CLA interrupt flags,refer to cla_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
                CLA_INT_FLAG_CLA0NF: CLA0 unit negedge interrupt flag
                CLA_INT_FLAG_CLA0PF: CLA0 unit posedge interrupt flag
                CLA_INT_FLAG_CLA1NF: CLA1 unit negedge interrupt flag
                CLA_INT_FLAG_CLA1PF: CLA1 unit posedge interrupt flag
                CLA_INT_FLAG_CLA2NF: CLA2 unit negedge interrupt flag
                CLA_INT_FLAG_CLA2PF: CLA2 unit posedge interrupt flag
                CLA_INT_FLAG_CLA3NF: CLA3 unit negedge interrupt flag
                CLA_INT_FLAG_CLA3PF: CLA3 unit posedge interrupt flag
                CLA_INT_FLAG_CLA4NF: CLA4 unit negedge interrupt flag
                CLA_INT_FLAG_CLA4PF: CLA4 unit posedge interrupt flag
                CLA_INT_FLAG_CLA5NF: CLA5 unit negedge interrupt flag
                CLA_INT_FLAG_CLA5PF: CLA5 unit posedge interrupt flag
                CLA_INT_FLAG_CLA6NF: CLA6 unit negedge interrupt flag
                CLA_INT_FLAG_CLA6PF: CLA6 unit posedge interrupt flag
                CLA_INT_FLAG_CLA7NF: CLA7 unit negedge interrupt flag
                CLA_INT_FLAG_CLA7PF: CLA7 unit posedge interrupt flag
    \param[out] none
    \retval     none
*/
void cla_interrupt_flag_clear(cla_interrupt_flag_enum int_flag)
{
    switch(int_flag){
        case CLA_INT_FLAG_CLA0NF:
             CLA_INTF &= (~CLA_INTF_CLA0NF);
             break;
        case CLA_INT_FLAG_CLA0PF:
             CLA_INTF &= (~CLA_INTF_CLA0PF);
             break;
        case CLA_INT_FLAG_CLA1NF:
             CLA_INTF &= (~CLA_INTF_CLA1NF);
             break;
        case CLA_INT_FLAG_CLA1PF:
             CLA_INTF &= (~CLA_INTF_CLA1PF);
             break;
        case CLA_INT_FLAG_CLA2NF:
             CLA_INTF &= (~CLA_INTF_CLA2NF);
             break;
        case CLA_INT_FLAG_CLA2PF:
             CLA_INTF &= (~CLA_INTF_CLA2PF);
             break;
        case CLA_INT_FLAG_CLA3NF:
             CLA_INTF &= (~CLA_INTF_CLA3NF);
             break;
        case CLA_INT_FLAG_CLA3PF:
             CLA_INTF &= (~CLA_INTF_CLA3PF);
             break;
        case CLA_INT_FLAG_CLA4NF:
             CLA_INTF &= (~CLA_INTF_CLA4NF);
             break;
        case CLA_INT_FLAG_CLA4PF:
             CLA_INTF &= (~CLA_INTF_CLA4PF);
             break;
        case CLA_INT_FLAG_CLA5NF:
             CLA_INTF &= (~CLA_INTF_CLA5NF);
             break;
        case CLA_INT_FLAG_CLA5PF:
             CLA_INTF &= (~CLA_INTF_CLA5PF);
             break;
        case CLA_INT_FLAG_CLA6NF:
             CLA_INTF &= (~CLA_INTF_CLA6NF);
             break;
        case CLA_INT_FLAG_CLA6PF:
             CLA_INTF &= (~CLA_INTF_CLA6PF);
             break;
        case CLA_INT_FLAG_CLA7NF:
             CLA_INTF &= (~CLA_INTF_CLA7NF);
             break;
        case CLA_INT_FLAG_CLA7PF:
             CLA_INTF &= (~CLA_INTF_CLA7PF);
             break;
        default:
             break;
    }
}


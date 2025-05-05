/*!
    \file  gd32e501_cla.h
    \brief definitions for the CLA
    
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

#ifndef GD32E501_CLA_H
#define GD32E501_CLA_H

#include "gd32e501.h"

/*CLA definitions */
#define CLA                                CLA_BASE

/* registers definitions */
#define CLA_GCTL                           REG32((CLA) + 0x00000000U)                              /*!< CLA global control register */
#define CLA_INTE                           REG32((CLA) + 0x00000004U)                              /*!< CLA interrupt flag enable register */
#define CLA_INTF                           REG32((CLA) + 0x00000008U)                              /*!< CLA interrupt flag register */
#define CLA_STAT                           REG32((CLA) + 0x0000000CU)                              /*!< CLA status register */
#define CLA_SIGS(CLAx)                     REG32((CLA) + 0x00000010U + ((CLAx) * 0x0000000CU))     /*!< CLA multiplexer selection register */
#define CLA_LCUCTL(CLAx)                   REG32((CLA) + 0x00000014U + ((CLAx) * 0x0000000CU))     /*!< CLA LCU control register */
#define CLA_CTL(CLAx)                      REG32((CLA) + 0x00000018U + ((CLAx) * 0x0000000CU))     /*!< CLA control register */

/* bits definitions */
/* CLA_GCTL */
#define CLA_GCTL_CLA0EN                    BIT(0)                           /*!< CLA0 unit enable */
#define CLA_GCTL_CLA1EN                    BIT(1)                           /*!< CLA1 unit enable */
#define CLA_GCTL_CLA2EN                    BIT(2)                           /*!< CLA2 unit enable */
#define CLA_GCTL_CLA3EN                    BIT(3)                           /*!< CLA3 unit enable */
#define CLA_GCTL_CLA4EN                    BIT(4)                           /*!< CLA4 unit enable */
#define CLA_GCTL_CLA5EN                    BIT(5)                           /*!< CLA5 unit enable */
#define CLA_GCTL_CLA6EN                    BIT(6)                           /*!< CLA6 unit enable */
#define CLA_GCTL_CLA7EN                    BIT(7)                           /*!< CLA7 unit enable */

/* CLA_INTE */
#define CLA_INTE_CLA0NIE                   BIT(0)                           /*!< CLA0 uint negedge interrupt enable */
#define CLA_INTE_CLA0PIE                   BIT(1)                           /*!< CLA0 uint posedge interrupt enable */
#define CLA_INTE_CLA1NIE                   BIT(2)                           /*!< CLA1 uint negedge interrupt enable */
#define CLA_INTE_CLA1PIE                   BIT(3)                           /*!< CLA1 uint posedge interrupt enable */
#define CLA_INTE_CLA2NIE                   BIT(4)                           /*!< CLA2 uint negedge interrupt enable */
#define CLA_INTE_CLA2PIE                   BIT(5)                           /*!< CLA2 uint posedge interrupt enable */
#define CLA_INTE_CLA3NIE                   BIT(6)                           /*!< CLA3 uint negedge interrupt enable */
#define CLA_INTE_CLA3PIE                   BIT(7)                           /*!< CLA3 uint posedge interrupt enable */
#define CLA_INTE_CLA4NIE                   BIT(8)                           /*!< CLA4 uint negedge interrupt enable */
#define CLA_INTE_CLA4PIE                   BIT(9)                           /*!< CLA4 uint posedge interrupt enable */
#define CLA_INTE_CLA5NIE                   BIT(10)                          /*!< CLA5 uint negedge interrupt enable */
#define CLA_INTE_CLA5PIE                   BIT(11)                          /*!< CLA5 uint posedge interrupt enable */
#define CLA_INTE_CLA6NIE                   BIT(12)                          /*!< CLA6 uint negedge interrupt enable */
#define CLA_INTE_CLA6PIE                   BIT(13)                          /*!< CLA6 uint posedge interrupt enable */
#define CLA_INTE_CLA7NIE                   BIT(14)                          /*!< CLA7 uint negedge interrupt enable */
#define CLA_INTE_CLA7PIE                   BIT(15)                          /*!< CLA7 uint posedge interrupt enable */

/* CLA_INTF */
#define CLA_INTF_CLA0NF                    BIT(0)                           /*!< CLA0 uint negedge flag */
#define CLA_INTF_CLA0PF                    BIT(1)                           /*!< CLA0 uint posedge flag */
#define CLA_INTF_CLA1NF                    BIT(2)                           /*!< CLA1 uint negedge flag */
#define CLA_INTF_CLA1PF                    BIT(3)                           /*!< CLA1 uint posedge flag */
#define CLA_INTF_CLA2NF                    BIT(4)                           /*!< CLA2 uint negedge flag */
#define CLA_INTF_CLA2PF                    BIT(5)                           /*!< CLA2 uint posedge flag */
#define CLA_INTF_CLA3NF                    BIT(6)                           /*!< CLA3 uint negedge flag */
#define CLA_INTF_CLA3PF                    BIT(7)                           /*!< CLA3 uint posedge flag */
#define CLA_INTF_CLA4NF                    BIT(8)                           /*!< CLA4 uint negedge flag */
#define CLA_INTF_CLA4PF                    BIT(9)                           /*!< CLA4 uint posedge flag */
#define CLA_INTF_CLA5NF                    BIT(10)                          /*!< CLA5 uint negedge flag */
#define CLA_INTF_CLA5PF                    BIT(11)                          /*!< CLA5 uint posedge flag */
#define CLA_INTF_CLA6NF                    BIT(12)                          /*!< CLA6 uint negedge flag */
#define CLA_INTF_CLA6PF                    BIT(13)                          /*!< CLA6 uint posedge flag */
#define CLA_INTF_CLA7NF                    BIT(14)                          /*!< CLA7 uint negedge flag */
#define CLA_INTF_CLA7PF                    BIT(15)                          /*!< CLA7 uint posedge flag */

/* CLA_STAT */
#define CLA_STAT_CLA0OUT                   BIT(0)                           /*!< CLA0 unit output state */
#define CLA_STAT_CLA1OUT                   BIT(1)                           /*!< CLA1 unit output state */
#define CLA_STAT_CLA2OUT                   BIT(2)                           /*!< CLA2 unit output state */
#define CLA_STAT_CLA3OUT                   BIT(3)                           /*!< CLA3 unit output state */
#define CLA_STAT_CLA4OUT                   BIT(4)                           /*!< CLA4 unit output state */
#define CLA_STAT_CLA5OUT                   BIT(5)                           /*!< CLA5 unit output state */
#define CLA_STAT_CLA6OUT                   BIT(6)                           /*!< CLA6 unit output state */
#define CLA_STAT_CLA7OUT                   BIT(7)                           /*!< CLA7 unit output state */

/* CLAx_SIGS */
#define CLA_SIGS_SIGS1                      BITS(0,3)                        /*!< multiplexer 1 input selection */
#define CLA_SIGS_SIGS1_5                    BIT(14)                          /*!< the fifth bit of multiplexer 1 input selection */
#define CLA_SIGS_SIGS0                      BITS(4,7)                        /*!< multiplexer 0 input selection */
#define CLA_SIGS_SIGS0_5                    BIT(15)                          /*!< the fifth bit of multiplexer 0 input selection */

/* CLAx_LCUCTL */
#define CLA_LCU                            BITS(0,7)                        /*!< LCU control */

/* CLAx_CTL */
#define CLA_CTL_CSEL                       BITS(0,1)                        /*!< clock selection */
#define CLA_CTL_CPOL                       BIT(2)                           /*!< clock polarity*/
#define CLA_CTL_FFRST                      BIT(3)                           /*!< Flip- flop output reset */
#define CLA_CTL_OEN                        BIT(6)                           /*!< output enable */
#define CLA_CTL_OSEL                       BIT(7)                           /*!< output selection */

/* constants definitions */
/* CLA flags */
typedef enum
{
    /* flags in INTF register */
    CLA_FLAG_CLA0NF,                                                        /*!< CLA0 unit negedge flag */
    CLA_FLAG_CLA0PF,                                                        /*!< CLA0 unit posedge flag */
    CLA_FLAG_CLA1NF,                                                        /*!< CLA1 unit negedge flag */
    CLA_FLAG_CLA1PF,                                                        /*!< CLA1 unit posedge flag */
    CLA_FLAG_CLA2NF,                                                        /*!< CLA2 unit negedge flag */
    CLA_FLAG_CLA2PF,                                                        /*!< CLA2 unit posedge flag */
    CLA_FLAG_CLA3NF,                                                        /*!< CLA3 unit negedge flag */
    CLA_FLAG_CLA3PF,                                                        /*!< CLA3 unit posedge flag */
    CLA_FLAG_CLA4NF,                                                        /*!< CLA4 unit negedge flag */
    CLA_FLAG_CLA4PF,                                                        /*!< CLA4 unit posedge flag */
    CLA_FLAG_CLA5NF,                                                        /*!< CLA5 unit negedge flag */
    CLA_FLAG_CLA5PF,                                                        /*!< CLA5 unit posedge flag */
    CLA_FLAG_CLA6NF,                                                        /*!< CLA6 unit negedge flag */
    CLA_FLAG_CLA6PF,                                                        /*!< CLA6 unit posedge flag */
    CLA_FLAG_CLA7NF,                                                        /*!< CLA7 unit negedge flag */
    CLA_FLAG_CLA7PF                                                         /*!< CLA7 unit posedge flag */
}cla_flag_enum;

/* CLA interrupt flags */
typedef enum
{
    /* interrupt flags in INTF register */
    CLA_INT_FLAG_CLA0NF,                                                    /*!< CLA0 unit negedge interrupt flag */
    CLA_INT_FLAG_CLA0PF,                                                    /*!< CLA0 unit posedge interrupt flag */
    CLA_INT_FLAG_CLA1NF,                                                    /*!< CLA1 unit negedge interrupt flag */
    CLA_INT_FLAG_CLA1PF,                                                    /*!< CLA1 unit posedge interrupt flag */
    CLA_INT_FLAG_CLA2NF,                                                    /*!< CLA2 unit negedge interrupt flag */
    CLA_INT_FLAG_CLA2PF,                                                    /*!< CLA2 unit posedge interrupt flag */
    CLA_INT_FLAG_CLA3NF,                                                    /*!< CLA3 unit negedge interrupt flag */
    CLA_INT_FLAG_CLA3PF,                                                    /*!< CLA3 unit posedge interrupt flag */
    CLA_INT_FLAG_CLA4NF,                                                    /*!< CLA4 unit negedge interrupt flag */
    CLA_INT_FLAG_CLA4PF,                                                    /*!< CLA4 unit posedge interrupt flag */
    CLA_INT_FLAG_CLA5NF,                                                    /*!< CLA5 unit negedge interrupt flag */
    CLA_INT_FLAG_CLA5PF,                                                    /*!< CLA5 unit posedge interrupt flag */
    CLA_INT_FLAG_CLA6NF,                                                    /*!< CLA6 unit negedge interrupt flag */
    CLA_INT_FLAG_CLA6PF,                                                    /*!< CLA6 unit posedge interrupt flag */
    CLA_INT_FLAG_CLA7NF,                                                    /*!< CLA7 unit negedge interrupt flag */
    CLA_INT_FLAG_CLA7PF                                                     /*!< CLA7 unit posedge interrupt flag */
}cla_interrupt_flag_enum;

/* CLA units */
typedef enum
{
    CLA0,
    CLA1,
    CLA2,
    CLA3,
    CLA4,
    CLA5,
    CLA6,
    CLA7
}cla_enum;

/* CLA multiplexer */
typedef enum
{
    SIGS0,
    SIGS1
}cla_sigs_enum;

/* output state of CLAx unit */
typedef enum
{
    CLA_OUTPUT_LOW,
    CLA_OUTPUT_HIGH
}cla_outputstatus_enum;

/* negedge interrupt enable */
#define CLA0NIE                          CLA_INTE_CLA0NIE                   /*!< enable CLA0 unit negedge interrupt */
#define CLA1NIE                          CLA_INTE_CLA1NIE                   /*!< enable CLA1 unit negedge interrupt */
#define CLA2NIE                          CLA_INTE_CLA2NIE                   /*!< enable CLA2 unit negedge interrupt */
#define CLA3NIE                          CLA_INTE_CLA3NIE                   /*!< enable CLA3 unit negedge interrupt */
#define CLA4NIE                          CLA_INTE_CLA4NIE                   /*!< enable CLA4 unit negedge interrupt */
#define CLA5NIE                          CLA_INTE_CLA5NIE                   /*!< enable CLA5 unit negedge interrupt */
#define CLA6NIE                          CLA_INTE_CLA6NIE                   /*!< enable CLA6 unit negedge interrupt */
#define CLA7NIE                          CLA_INTE_CLA7NIE                   /*!< enable CLA7 unit negedge interrupt */

/* negedge interrupt disable */
#define CLA0NI_DISABLE                    CLA_INTE_CLA0NIE                   /*!< disable CLA0 unit negedge interrupt */
#define CLA1NI_DISABLE                    CLA_INTE_CLA1NIE                   /*!< disable CLA1 unit negedge interrupt */
#define CLA2NI_DISABLE                    CLA_INTE_CLA2NIE                   /*!< disable CLA2 unit negedge interrupt */
#define CLA3NI_DISABLE                    CLA_INTE_CLA3NIE                   /*!< disable CLA3 unit negedge interrupt */
#define CLA4NI_DISABLE                    CLA_INTE_CLA4NIE                   /*!< disable CLA4 unit negedge interrupt */
#define CLA5NI_DISABLE                    CLA_INTE_CLA5NIE                   /*!< disable CLA5 unit negedge interrupt */
#define CLA6NI_DISABLE                    CLA_INTE_CLA6NIE                   /*!< disable CLA6 unit negedge interrupt */
#define CLA7NI_DISABLE                    CLA_INTE_CLA7NIE                   /*!< disable CLA7 unit negedge interrupt */

/* posedge interrupt enable */
#define CLA0PIE                           CLA_INTE_CLA0PIE                   /*!< enable CLA0 unit  posedge interrupt */
#define CLA1PIE                           CLA_INTE_CLA1PIE                   /*!< enable CLA1 unit  posedge interrupt */
#define CLA2PIE                           CLA_INTE_CLA2PIE                   /*!< enable CLA2 unit  posedge interrupt */
#define CLA3PIE                           CLA_INTE_CLA3PIE                   /*!< enable CLA3 unit  posedge interrupt */
#define CLA4PIE                           CLA_INTE_CLA4PIE                   /*!< enable CLA4 unit  posedge interrupt */
#define CLA5PIE                           CLA_INTE_CLA5PIE                   /*!< enable CLA5 unit  posedge interrupt */
#define CLA6PIE                           CLA_INTE_CLA6PIE                   /*!< enable CLA6 unit  posedge interrupt */
#define CLA7PIE                           CLA_INTE_CLA7PIE                   /*!< enable CLA7 unit  posedge interrupt */

/* posedge interrupt disable */
#define CLA0PI_DISABLE                    CLA_INTE_CLAOPIE                   /*!< disable CLA0 unit  posedge interrupt */
#define CLA1PI_DISABLE                    CLA_INTE_CLA1PIE                   /*!< disable CLA1 unit  posedge interrupt */
#define CLA2PI_DISABLE                    CLA_INTE_CLA2PIE                   /*!< disable CLA2 unit  posedge interrupt */
#define CLA3PI_DISABLE                    CLA_INTE_CLA3PIE                   /*!< disable CLA3 unit  posedge interrupt */
#define CLA4PI_DISABLE                    CLA_INTE_CLA4PIE                   /*!< disable CLA0 unit  posedge interrupt */
#define CLA5PI_DISABLE                    CLA_INTE_CLA5PIE                   /*!< disable CLA1 unit  posedge interrupt */
#define CLA6PI_DISABLE                    CLA_INTE_CLA6PIE                   /*!< disable CLA2 unit  posedge interrupt */
#define CLA7PI_DISABLE                    CLA_INTE_CLA7PIE                   /*!< disable CLA3 unit  posedge interrupt */

/* multiplexer 0 input selection */
#define CLA_SIGS0(regval)                 (BITS(4,7) & ((uint32_t)(regval) << 4))
#define CLA0SIGS0_CLA0_ASYNC_OUT          CLA_SIGS0(0)                        /*!< the input of CLA0SIGS0 is CLA0_ASYNC_OUT */
#define CLA1SIGS0_CLA0_ASYNC_OUT          CLA_SIGS0(0)                        /*!< the input of CLA1SIGS0 is CLA0_ASYNC_OUT */
#define CLA2SIGS0_CLA0_ASYNC_OUT          CLA_SIGS0(0)                        /*!< the input of CLA2SIGS0 is CLA0_ASYNC_OUT */
#define CLA3SIGS0_CLA0_ASYNC_OUT          CLA_SIGS0(0)                        /*!< the input of CLA3SIGS0 is CLA0_ASYNC_OUT */
#define CLA4SIGS0_CLA0_ASYNC_OUT          CLA_SIGS0(0)                        /*!< the input of CLA4SIGS0 is CLA0_ASYNC_OUT */
#define CLA5SIGS0_CLA0_ASYNC_OUT          CLA_SIGS0(0)                        /*!< the input of CLA5SIGS0 is CLA0_ASYNC_OUT */
#define CLA6SIGS0_CLA0_ASYNC_OUT          CLA_SIGS0(0)                        /*!< the input of CLA6SIGS0 is CLA0_ASYNC_OUT */
#define CLA7SIGS0_CLA0_ASYNC_OUT          CLA_SIGS0(0)                        /*!< the input of CLA7SIGS0 is CLA0_ASYNC_OUT */

#define CLA0SIGS0_CLA1_ASYNC_OUT          CLA_SIGS0(1)                        /*!< the input of CLA0SIGS0 is CLA1_ASYNC_OUT */
#define CLA1SIGS0_CLA1_ASYNC_OUT          CLA_SIGS0(1)                        /*!< the input of CLA1SIGS0 is CLA1_ASYNC_OUT */
#define CLA2SIGS0_CLA1_ASYNC_OUT          CLA_SIGS0(1)                        /*!< the input of CLA2SIGS0 is CLA1_ASYNC_OUT */
#define CLA3SIGS0_CLA1_ASYNC_OUT          CLA_SIGS0(1)                        /*!< the input of CLA3SIGS0 is CLA1_ASYNC_OUT */
#define CLA4SIGS0_CLA1_ASYNC_OUT          CLA_SIGS0(1)                        /*!< the input of CLA4SIGS0 is CLA1_ASYNC_OUT */
#define CLA5SIGS0_CLA1_ASYNC_OUT          CLA_SIGS0(1)                        /*!< the input of CLA5SIGS0 is CLA1_ASYNC_OUT */
#define CLA6SIGS0_CLA1_ASYNC_OUT          CLA_SIGS0(1)                        /*!< the input of CLA6SIGS0 is CLA1_ASYNC_OUT */
#define CLA7SIGS0_CLA1_ASYNC_OUT          CLA_SIGS0(1)                        /*!< the input of CLA7SIGS0 is CLA1_ASYNC_OUT */

#define CLA0SIGS0_CLA2_ASYNC_OUT          CLA_SIGS0(2)                        /*!< the input of CLA0SIGS0 is CLA2_ASYNC_OUT */
#define CLA1SIGS0_CLA2_ASYNC_OUT          CLA_SIGS0(2)                        /*!< the input of CLA1SIGS0 is CLA2_ASYNC_OUT */
#define CLA2SIGS0_CLA2_ASYNC_OUT          CLA_SIGS0(2)                        /*!< the input of CLA2SIGS0 is CLA2_ASYNC_OUT */
#define CLA3SIGS0_CLA2_ASYNC_OUT          CLA_SIGS0(2)                        /*!< the input of CLA3SIGS0 is CLA2_ASYNC_OUT */
#define CLA4SIGS0_CLA2_ASYNC_OUT          CLA_SIGS0(2)                        /*!< the input of CLA4SIGS0 is CLA2_ASYNC_OUT */
#define CLA5SIGS0_CLA2_ASYNC_OUT          CLA_SIGS0(2)                        /*!< the input of CLA5SIGS0 is CLA2_ASYNC_OUT */
#define CLA6SIGS0_CLA2_ASYNC_OUT          CLA_SIGS0(2)                        /*!< the input of CLA6SIGS0 is CLA2_ASYNC_OUT */
#define CLA7SIGS0_CLA2_ASYNC_OUT          CLA_SIGS0(2)                        /*!< the input of CLA7SIGS0 is CLA2_ASYNC_OUT */

#define CLA0SIGS0_CLA3_ASYNC_OUT          CLA_SIGS0(3)                        /*!< the input of CLA0SIGS0 is CLA3_ASYNC_OUT */
#define CLA1SIGS0_CLA3_ASYNC_OUT          CLA_SIGS0(3)                        /*!< the input of CLA1SIGS0 is CLA3_ASYNC_OUT */
#define CLA2SIGS0_CLA3_ASYNC_OUT          CLA_SIGS0(3)                        /*!< the input of CLA2SIGS0 is CLA3_ASYNC_OUT */
#define CLA3SIGS0_CLA3_ASYNC_OUT          CLA_SIGS0(3)                        /*!< the input of CLA3SIGS0 is CLA3_ASYNC_OUT */
#define CLA4SIGS0_CLA3_ASYNC_OUT          CLA_SIGS0(3)                        /*!< the input of CLA4SIGS0 is CLA3_ASYNC_OUT */
#define CLA5SIGS0_CLA3_ASYNC_OUT          CLA_SIGS0(3)                        /*!< the input of CLA5SIGS0 is CLA3_ASYNC_OUT */
#define CLA6SIGS0_CLA3_ASYNC_OUT          CLA_SIGS0(3)                        /*!< the input of CLA6SIGS0 is CLA3_ASYNC_OUT */
#define CLA7SIGS0_CLA3_ASYNC_OUT          CLA_SIGS0(3)                        /*!< the input of CLA7SIGS0 is CLA3_ASYNC_OUT */

#define CLA0SIGS0_TIMER1_TRGO             CLA_SIGS0(4)                        /*!< the input of CLA0SIGS0 is TIMER1_TRGO */
#define CLA1SIGS0_TIMER2_TRGO             CLA_SIGS0(4)                        /*!< the input of CLA1SIGS0 is TIMER2_TRGO */
#define CLA2SIGS0_TIMER5_TRGO             CLA_SIGS0(4)                        /*!< the input of CLA2SIGS0 is TIMER5_TRGO */
#define CLA3SIGS0_TIMER6_TRGO             CLA_SIGS0(4)                        /*!< the input of CLA3SIGS0 is TIMER6_TRGO */
#define CLA4SIGS0_TIMER1_TRGO             CLA_SIGS0(4)                        /*!< the input of CLA4SIGS0 is TIMER1_TRGO */
#define CLA5SIGS0_TIMER2_TRGO             CLA_SIGS0(4)                        /*!< the input of CLA5SIGS0 is TIMER2_TRGO */
#define CLA6SIGS0_TIMER5_TRGO             CLA_SIGS0(4)                        /*!< the input of CLA6SIGS0 is TIMER5_TRGO */
#define CLA7SIGS0_TIMER6_TRGO             CLA_SIGS0(4)                        /*!< the input of CLA7SIGS0 is TIMER6_TRGO */

#define CLA0SIGS0_TIMER0_CH0              CLA_SIGS0(5)                        /*!< the input of CLA0SIGS0 is TIMER0_CH0 */
#define CLA1SIGS0_TIMER0_CH0              CLA_SIGS0(5)                        /*!< the input of CLA1SIGS0 is TIMER0_CH0 */
#define CLA2SIGS0_TIMER0_CH1              CLA_SIGS0(5)                        /*!< the input of CLA2SIGS0 is TIMER0_CH1 */
#define CLA3SIGS0_TIMER0_CH2              CLA_SIGS0(5)                        /*!< the input of CLA3SIGS0 is TIMER0_CH2 */
#define CLA4SIGS0_TIMER0_CH0              CLA_SIGS0(5)                        /*!< the input of CLA4SIGS0 is TIMER0_CH0 */
#define CLA5SIGS0_TIMER0_CH0              CLA_SIGS0(5)                        /*!< the input of CLA5SIGS0 is TIMER0_CH0 */
#define CLA6SIGS0_TIMER0_CH1              CLA_SIGS0(5)                        /*!< the input of CLA6SIGS0 is TIMER0_CH1 */
#define CLA7SIGS0_TIMER0_CH2              CLA_SIGS0(5)                        /*!< the input of CLA7SIGS0 is TIMER0_CH2 */

#define CLA0SIGS0_TIMER0_CH1              CLA_SIGS0(6)                        /*!< the input of CLA0SIGS0 is TIMER0_CH1 */
#define CLA1SIGS0_TIMER0_CH3              CLA_SIGS0(6)                        /*!< the input of CLA1SIGS0 is TIMER0_CH3 */
#define CLA2SIGS0_TIMER0_CH3              CLA_SIGS0(6)                        /*!< the input of CLA2SIGS0 is TIMER0_CH3 */
#define CLA3SIGS0_TIMER1_CH0              CLA_SIGS0(6)                        /*!< the input of CLA3SIGS0 is TIMER1_CH0 */
#define CLA4SIGS0_TIMER0_CH1              CLA_SIGS0(6)                        /*!< the input of CLA4SIGS0 is TIMER0_CH1 */
#define CLA5SIGS0_TIMER0_CH3              CLA_SIGS0(6)                        /*!< the input of CLA5SIGS0 is TIMER0_CH3 */
#define CLA6SIGS0_TIMER0_CH3              CLA_SIGS0(6)                        /*!< the input of CLA6SIGS0 is TIMER0_CH3 */
#define CLA7SIGS0_TIMER1_CH0              CLA_SIGS0(6)                        /*!< the input of CLA7SIGS0 is TIMER1_CH0 */

#define CLA0SIGS0_TIMER0_CH2              CLA_SIGS0(7)                        /*!< the input of CLA0SIGS0 is TIMER0_CH2 */
#define CLA1SIGS0_TIMER1_CH0              CLA_SIGS0(7)                        /*!< the input of CLA1SIGS0 is TIMER1_CH0 */
#define CLA2SIGS0_TIMER1_CH1              CLA_SIGS0(7)                        /*!< the input of CLA2SIGS0 is TIMER1_CH1 */
#define CLA3SIGS0_TIMER1_CH1              CLA_SIGS0(7)                        /*!< the input of CLA3SIGS0 is TIMER1_CH1 */
#define CLA4SIGS0_TIMER0_CH2              CLA_SIGS0(7)                        /*!< the input of CLA4SIGS0 is TIMER0_CH2 */
#define CLA5SIGS0_TIMER1_CH0              CLA_SIGS0(7)                        /*!< the input of CLA5SIGS0 is TIMER1_CH0 */
#define CLA6SIGS0_TIMER1_CH1              CLA_SIGS0(7)                        /*!< the input of CLA6SIGS0 is TIMER1_CH1 */
#define CLA7SIGS0_TIMER1_CH1              CLA_SIGS0(7)                        /*!< the input of CLA7SIGS0 is TIMER1_CH1 */

#define CLA0SIGS0_CLAIN0                  CLA_SIGS0(8)                        /*!< the input of CLA0SIGS0 is CLAIN0(PA15) */
#define CLA1SIGS0_CLAIN4                  CLA_SIGS0(8)                        /*!< the input of CLA1SIGS0 is CLAIN4(PB6) */
#define CLA2SIGS0_CLAIN0                  CLA_SIGS0(8)                        /*!< the input of CLA2SIGS0 is CLAIN0(PA15) */
#define CLA3SIGS0_CLAIN2                  CLA_SIGS0(8)                        /*!< the input of CLA3SIGS0 is CLAIN2(PB4) */
#define CLA4SIGS0_CLAIN0                  CLA_SIGS0(8)                        /*!< the input of CLA4SIGS0 is CLAIN0(PA15) */
#define CLA5SIGS0_CLAIN4                  CLA_SIGS0(8)                        /*!< the input of CLA5SIGS0 is CLAIN4(PB6) */
#define CLA6SIGS0_CLAIN0                  CLA_SIGS0(8)                        /*!< the input of CLA6SIGS0 is CLAIN0(PA15) */
#define CLA7SIGS0_CLAIN2                  CLA_SIGS0(8)                        /*!< the input of CLA7SIGS0 is CLAIN2(PB4) */

#define CLA0SIGS0_CLAIN2                  CLA_SIGS0(9)                        /*!< the input of CLA0SIGS0 is CLAIN2(PB4) */
#define CLA1SIGS0_CLAIN5                  CLA_SIGS0(9)                        /*!< the input of CLA1SIGS0 is CLAIN5(PB7) */
#define CLA2SIGS0_CLAIN1                  CLA_SIGS0(9)                        /*!< the input of CLA2SIGS0 is CLAIN1(PB3) */
#define CLA3SIGS0_CLAIN3                  CLA_SIGS0(9)                        /*!< the input of CLA3SIGS0 is CLAIN3(PB5) */
#define CLA4SIGS0_CLAIN2                  CLA_SIGS0(9)                        /*!< the input of CLA4SIGS0 is CLAIN2(PB4) */
#define CLA5SIGS0_CLAIN5                  CLA_SIGS0(9)                        /*!< the input of CLA5SIGS0 is CLAIN5(PB7) */
#define CLA6SIGS0_CLAIN1                  CLA_SIGS0(9)                        /*!< the input of CLA6SIGS0 is CLAIN1(PB3) */
#define CLA7SIGS0_CLAIN3                  CLA_SIGS0(9)                        /*!< the input of CLA7SIGS0 is CLAIN3(PB5) */

#define CLA0SIGS0_CLAIN4                  CLA_SIGS0(10)                       /*!< the input of CLA0SIGS0 is CLAIN4(PB6) */
#define CLA1SIGS0_CLAIN8                  CLA_SIGS0(10)                       /*!< the input of CLA1SIGS0 is CLAIN8(PB0) */
#define CLA2SIGS0_CLAIN8                  CLA_SIGS0(10)                       /*!< the input of CLA2SIGS0 is CLAIN8(PB0) */
#define CLA3SIGS0_CLAIN6                  CLA_SIGS0(10)                       /*!< the input of CLA3SIGS0 is CLAIN6(PB8) */
#define CLA4SIGS0_CLAIN4                  CLA_SIGS0(10)                       /*!< the input of CLA4SIGS0 is CLAIN4(PB6) */
#define CLA5SIGS0_CLAIN8                  CLA_SIGS0(10)                       /*!< the input of CLA5SIGS0 is CLAIN8(PB0) */
#define CLA6SIGS0_CLAIN8                  CLA_SIGS0(10)                       /*!< the input of CLA6SIGS0 is CLAIN8(PB0) */
#define CLA7SIGS0_CLAIN6                  CLA_SIGS0(10)                       /*!< the input of CLA7SIGS0 is CLAIN6(PB8) */

#define CLA0SIGS0_CLAIN6                  CLA_SIGS0(11)                       /*!< the input of CLA0SIGS0 is CLAIN6(PB8) */
#define CLA1SIGS0_CLAIN10                 CLA_SIGS0(11)                       /*!< the input of CLA1SIGS0 is CLAIN10(PB2) */
#define CLA2SIGS0_CLAIN9                  CLA_SIGS0(11)                       /*!< the input of CLA2SIGS0 is CLAIN9(PB1) */
#define CLA3SIGS0_CLAIN7                  CLA_SIGS0(11)                       /*!< the input of CLA3SIGS0 is CLAIN7(PB9) */
#define CLA4SIGS0_CLAIN6                  CLA_SIGS0(11)                       /*!< the input of CLA4SIGS0 is CLAIN6(PB8) */
#define CLA5SIGS0_CLAIN10                 CLA_SIGS0(11)                       /*!< the input of CLA5SIGS0 is CLAIN10(PB2) */
#define CLA6SIGS0_CLAIN9                  CLA_SIGS0(11)                       /*!< the input of CLA6SIGS0 is CLAIN9(PB1) */
#define CLA7SIGS0_CLAIN7                  CLA_SIGS0(11)                       /*!< the input of CLA7SIGS0 is CLAIN7(PB9) */

#define CLA0SIGS0_CLAIN8                  CLA_SIGS0(12)                       /*!< the input of CLA0SIGS0 is CLAIN8(PB0) */
#define CLA1SIGS0_CLAIN12                 CLA_SIGS0(12)                       /*!< the input of CLA1SIGS0 is CLAIN12(PA9) */
#define CLA2SIGS0_CLAIN14                 CLA_SIGS0(12)                       /*!< the input of CLA2SIGS0 is CLAIN14(PA11) */
#define CLA3SIGS0_CLAIN10                 CLA_SIGS0(12)                       /*!< the input of CLA3SIGS0 is CLAIN10(PB2) */
#define CLA4SIGS0_CLAIN8                  CLA_SIGS0(12)                       /*!< the input of CLA4SIGS0 is CLAIN8(PB0) */
#define CLA5SIGS0_CLAIN12                 CLA_SIGS0(12)                       /*!< the input of CLA5SIGS0 is CLAIN12(PA9) */
#define CLA6SIGS0_CLAIN14                 CLA_SIGS0(12)                       /*!< the input of CLA6SIGS0 is CLAIN14(PA11) */
#define CLA7SIGS0_CLAIN10                 CLA_SIGS0(12)                       /*!< the input of CLA7SIGS0 is CLAIN10(PB2) */

#define CLA0SIGS0_CLAIN10                 CLA_SIGS0(13)                       /*!< the input of CLA0SIGS0 is CLAIN10(PB2) */
#define CLA1SIGS0_CLAIN13                 CLA_SIGS0(13)                       /*!< the input of CLA1SIGS0 is CLAIN13(PA10) */
#define CLA2SIGS0_CLAIN15                 CLA_SIGS0(13)                       /*!< the input of CLA2SIGS0 is CLAIN15(PA12) */
#define CLA3SIGS0_CLAIN11                 CLA_SIGS0(13)                       /*!< the input of CLA3SIGS0 is CLAIN11(PA8) */
#define CLA4SIGS0_CLAIN10                 CLA_SIGS0(13)                       /*!< the input of CLA4SIGS0 is CLAIN10(PB2) */
#define CLA5SIGS0_CLAIN13                 CLA_SIGS0(13)                       /*!< the input of CLA5SIGS0 is CLAIN13(PA10) */
#define CLA6SIGS0_CLAIN15                 CLA_SIGS0(13)                       /*!< the input of CLA6SIGS0 is CLAIN15(PA12) */
#define CLA7SIGS0_CLAIN11                 CLA_SIGS0(13)                       /*!< the input of CLA7SIGS0 is CLAIN11(PA8) */

#define CLA0SIGS0_CLAIN12                 CLA_SIGS0(14)                       /*!< the input of CLA0SIGS0 is CLAIN12(PA9) */
#define CLA1SIGS0_CLAIN16                 CLA_SIGS0(14)                       /*!< the input of CLA1SIGS0 is CLAIN16(PF0) */
#define CLA2SIGS0_CLAIN16                 CLA_SIGS0(14)                       /*!< the input of CLA2SIGS0 is CLAIN16(PF0) */
#define CLA3SIGS0_CLAIN18                 CLA_SIGS0(14)                       /*!< the input of CLA3SIGS0 is CLAIN18(PA0) */
#define CLA4SIGS0_CLAIN12                 CLA_SIGS0(14)                       /*!< the input of CLA4SIGS0 is CLAIN12(PA9) */
#define CLA5SIGS0_CLAIN16                 CLA_SIGS0(14)                       /*!< the input of CLA5SIGS0 is CLAIN16(PF0) */
#define CLA6SIGS0_CLAIN16                 CLA_SIGS0(14)                       /*!< the input of CLA6SIGS0 is CLAIN16(PF0) */
#define CLA7SIGS0_CLAIN18                 CLA_SIGS0(14)                       /*!< the input of CLA7SIGS0 is CLAIN18(PA0) */

#define CLA0SIGS0_CLAIN14                 CLA_SIGS0(15)                       /*!< the input of CLA0SIGS0 is CLAIN14(PA11) */
#define CLA1SIGS0_CLAIN18                 CLA_SIGS0(15)                       /*!< the input of CLA1SIGS0 is CLAIN18(PA0) */
#define CLA2SIGS0_CLAIN17                 CLA_SIGS0(15)                       /*!< the input of CLA2SIGS0 is CLAIN17(PF1) */
#define CLA3SIGS0_CLAIN19                 CLA_SIGS0(15)                       /*!< the input of CLA3SIGS0 is CLAIN19(PA1) */
#define CLA4SIGS0_CLAIN14                 CLA_SIGS0(15)                       /*!< the input of CLA4SIGS0 is CLAIN14(PA11) */
#define CLA5SIGS0_CLAIN18                 CLA_SIGS0(15)                       /*!< the input of CLA5SIGS0 is CLAIN18(PA0) */
#define CLA6SIGS0_CLAIN17                 CLA_SIGS0(15)                       /*!< the input of CLA6SIGS0 is CLAIN17(PF1) */
#define CLA7SIGS0_CLAIN19                 CLA_SIGS0(15)                       /*!< the input of CLA7SIGS0 is CLAIN19(PA1) */

#define CLA0SIGS0_CLA4_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(0)        /*!< the input of CLA0SIGS0 is CLA4_ASYNC_OUT */
#define CLA1SIGS0_CLA4_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(0)        /*!< the input of CLA1SIGS0 is CLA4_ASYNC_OUT */
#define CLA2SIGS0_CLA4_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(0)        /*!< the input of CLA2SIGS0 is CLA4_ASYNC_OUT */
#define CLA3SIGS0_CLA4_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(0)        /*!< the input of CLA3SIGS0 is CLA4_ASYNC_OUT */
#define CLA4SIGS0_CLA4_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(0)        /*!< the input of CLA4SIGS0 is CLA4_ASYNC_OUT */
#define CLA5SIGS0_CLA4_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(0)        /*!< the input of CLA5SIGS0 is CLA4_ASYNC_OUT */
#define CLA6SIGS0_CLA4_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(0)        /*!< the input of CLA6SIGS0 is CLA4_ASYNC_OUT */
#define CLA7SIGS0_CLA4_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(0)        /*!< the input of CLA7SIGS0 is CLA4_ASYNC_OUT */

#define CLA0SIGS0_CLA5_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(1)        /*!< the input of CLA0SIGS0 is CLA5_ASYNC_OUT */
#define CLA1SIGS0_CLA5_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(1)        /*!< the input of CLA1SIGS0 is CLA5_ASYNC_OUT */
#define CLA2SIGS0_CLA5_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(1)        /*!< the input of CLA2SIGS0 is CLA5_ASYNC_OUT */
#define CLA3SIGS0_CLA5_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(1)        /*!< the input of CLA3SIGS0 is CLA5_ASYNC_OUT */
#define CLA4SIGS0_CLA5_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(1)        /*!< the input of CLA4SIGS0 is CLA5_ASYNC_OUT */
#define CLA5SIGS0_CLA5_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(1)        /*!< the input of CLA5SIGS0 is CLA5_ASYNC_OUT */
#define CLA6SIGS0_CLA5_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(1)        /*!< the input of CLA6SIGS0 is CLA5_ASYNC_OUT */
#define CLA7SIGS0_CLA5_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(1)        /*!< the input of CLA7SIGS0 is CLA5_ASYNC_OUT */

#define CLA1SIGS0_CLA6_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(2)        /*!< the input of CLA1SIGS0 is CLA6_ASYNC_OUT */
#define CLA2SIGS0_CLA6_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(2)        /*!< the input of CLA2SIGS0 is CLA6_ASYNC_OUT */
#define CLA3SIGS0_CLA6_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(2)        /*!< the input of CLA3SIGS0 is CLA6_ASYNC_OUT */
#define CLA4SIGS0_CLA6_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(2)        /*!< the input of CLA4SIGS0 is CLA6_ASYNC_OUT */
#define CLA5SIGS0_CLA6_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(2)        /*!< the input of CLA5SIGS0 is CLA6_ASYNC_OUT */
#define CLA6SIGS0_CLA6_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(2)        /*!< the input of CLA6SIGS0 is CLA6_ASYNC_OUT */
#define CLA7SIGS0_CLA6_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(2)        /*!< the input of CLA7SIGS0 is CLA6_ASYNC_OUT */

#define CLA0SIGS0_CLA7_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(3)        /*!< the input of CLA0SIGS0 is CLA7_ASYNC_OUT */
#define CLA1SIGS0_CLA7_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(3)        /*!< the input of CLA1SIGS0 is CLA7_ASYNC_OUT */
#define CLA2SIGS0_CLA7_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(3)        /*!< the input of CLA2SIGS0 is CLA7_ASYNC_OUT */
#define CLA3SIGS0_CLA7_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(3)        /*!< the input of CLA3SIGS0 is CLA7_ASYNC_OUT */
#define CLA4SIGS0_CLA7_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(3)        /*!< the input of CLA4SIGS0 is CLA7_ASYNC_OUT */
#define CLA5SIGS0_CLA7_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(3)        /*!< the input of CLA5SIGS0 is CLA7_ASYNC_OUT */
#define CLA6SIGS0_CLA7_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(3)        /*!< the input of CLA6SIGS0 is CLA7_ASYNC_OUT */
#define CLA7SIGS0_CLA7_ASYNC_OUT          CLA_SIGS_SIGS0_5|CLA_SIGS0(3)        /*!< the input of CLA7SIGS0 is CLA7_ASYNC_OUT */

/* multiplexer 1 input selection */
#define CLA_SIGS1(regval)                 (BITS(0,3) & ((uint32_t)(regval) << 0))
#define CLA0SIGS1_CLA0_ASYNC_OUT          CLA_SIGS1(0)                        /*!< the input of CLA0SIGS1 is CLA0_ASYNC_OUT */
#define CLA1SIGS1_CLA0_ASYNC_OUT          CLA_SIGS1(0)                        /*!< the input of CLA1SIGS1 is CLA0_ASYNC_OUT */
#define CLA2SIGS1_CLA0_ASYNC_OUT          CLA_SIGS1(0)                        /*!< the input of CLA2SIGS1 is CLA0_ASYNC_OUT */
#define CLA3SIGS1_CLA0_ASYNC_OUT          CLA_SIGS1(0)                        /*!< the input of CLA3SIGS1 is CLA0_ASYNC_OUT */
#define CLA4SIGS1_CLA0_ASYNC_OUT          CLA_SIGS1(0)                        /*!< the input of CLA4SIGS1 is CLA0_ASYNC_OUT */
#define CLA5SIGS1_CLA0_ASYNC_OUT          CLA_SIGS1(0)                        /*!< the input of CLA5SIGS1 is CLA0_ASYNC_OUT */
#define CLA6SIGS1_CLA0_ASYNC_OUT          CLA_SIGS1(0)                        /*!< the input of CLA6SIGS1 is CLA0_ASYNC_OUT */
#define CLA7SIGS1_CLA0_ASYNC_OUT          CLA_SIGS1(0)                        /*!< the input of CLA7SIGS1 is CLA0_ASYNC_OUT */

#define CLA0SIGS1_CLA1_ASYNC_OUT          CLA_SIGS1(1)                        /*!< the input of CLA0SIGS1 is CLA1_ASYNC_OUT */
#define CLA1SIGS1_CLA1_ASYNC_OUT          CLA_SIGS1(1)                        /*!< the input of CLA1SIGS1 is CLA1_ASYNC_OUT */
#define CLA2SIGS1_CLA1_ASYNC_OUT          CLA_SIGS1(1)                        /*!< the input of CLA2SIGS1 is CLA1_ASYNC_OUT */
#define CLA3SIGS1_CLA1_ASYNC_OUT          CLA_SIGS1(1)                        /*!< the input of CLA3SIGS1 is CLA1_ASYNC_OUT */
#define CLA4SIGS1_CLA1_ASYNC_OUT          CLA_SIGS1(1)                        /*!< the input of CLA4SIGS1 is CLA1_ASYNC_OUT */
#define CLA5SIGS1_CLA1_ASYNC_OUT          CLA_SIGS1(1)                        /*!< the input of CLA5SIGS1 is CLA1_ASYNC_OUT */
#define CLA6SIGS1_CLA1_ASYNC_OUT          CLA_SIGS1(1)                        /*!< the input of CLA6SIGS1 is CLA1_ASYNC_OUT */
#define CLA7SIGS1_CLA1_ASYNC_OUT          CLA_SIGS1(1)                        /*!< the input of CLA7SIGS1 is CLA1_ASYNC_OUT */

#define CLA0SIGS1_CLA2_ASYNC_OUT          CLA_SIGS1(2)                        /*!< the input of CLA0SIGS1 is CLA2_ASYNC_OUT */
#define CLA1SIGS1_CLA2_ASYNC_OUT          CLA_SIGS1(2)                        /*!< the input of CLA1SIGS1 is CLA2_ASYNC_OUT */
#define CLA2SIGS1_CLA2_ASYNC_OUT          CLA_SIGS1(2)                        /*!< the input of CLA2SIGS1 is CLA2_ASYNC_OUT */
#define CLA3SIGS1_CLA2_ASYNC_OUT          CLA_SIGS1(2)                        /*!< the input of CLA3SIGS1 is CLA2_ASYNC_OUT */
#define CLA4SIGS1_CLA2_ASYNC_OUT          CLA_SIGS1(2)                        /*!< the input of CLA4SIGS1 is CLA2_ASYNC_OUT */
#define CLA5SIGS1_CLA2_ASYNC_OUT          CLA_SIGS1(2)                        /*!< the input of CLA5SIGS1 is CLA2_ASYNC_OUT */
#define CLA6SIGS1_CLA2_ASYNC_OUT          CLA_SIGS1(2)                        /*!< the input of CLA6SIGS1 is CLA2_ASYNC_OUT */
#define CLA7SIGS1_CLA2_ASYNC_OUT          CLA_SIGS1(2)                        /*!< the input of CLA7SIGS1 is CLA2_ASYNC_OUT */

#define CLA0SIGS1_CLA3_ASYNC_OUT          CLA_SIGS1(3)                        /*!< the input of CLA0SIGS1 is CLA3_ASYNC_OUT */
#define CLA1SIGS1_CLA3_ASYNC_OUT          CLA_SIGS1(3)                        /*!< the input of CLA1SIGS1 is CLA3_ASYNC_OUT */
#define CLA2SIGS1_CLA3_ASYNC_OUT          CLA_SIGS1(3)                        /*!< the input of CLA2SIGS1 is CLA3_ASYNC_OUT */
#define CLA3SIGS1_CLA3_ASYNC_OUT          CLA_SIGS1(3)                        /*!< the input of CLA3SIGS1 is CLA3_ASYNC_OUT */
#define CLA4SIGS1_CLA3_ASYNC_OUT          CLA_SIGS1(3)                        /*!< the input of CLA4SIGS1 is CLA3_ASYNC_OUT */
#define CLA5SIGS1_CLA3_ASYNC_OUT          CLA_SIGS1(3)                        /*!< the input of CLA5SIGS1 is CLA3_ASYNC_OUT */
#define CLA6SIGS1_CLA3_ASYNC_OUT          CLA_SIGS1(3)                        /*!< the input of CLA6SIGS1 is CLA3_ASYNC_OUT */
#define CLA7SIGS1_CLA3_ASYNC_OUT          CLA_SIGS1(3)                        /*!< the input of CLA7SIGS1 is CLA3_ASYNC_OUT */

#define CLA0SIGS1_ADC_CONV                CLA_SIGS1(4)                        /*!< the input of CLA0SIGS1 is ADC_CONV */
#define CLA1SIGS1_ADC_CONV                CLA_SIGS1(4)                        /*!< the input of CLA1SIGS1 is ADC_CONV */
#define CLA2SIGS1_ADC_CONV                CLA_SIGS1(4)                        /*!< the input of CLA2SIGS1 is ADC_CONV */
#define CLA3SIGS1_ADC_CONV                CLA_SIGS1(4)                        /*!< the input of CLA3SIGS1 is ADC_CONV */
#define CLA4SIGS1_ADC_CONV                CLA_SIGS1(4)                        /*!< the input of CLA4SIGS1 is ADC_CONV */
#define CLA5SIGS1_ADC_CONV                CLA_SIGS1(4)                        /*!< the input of CLA5SIGS1 is ADC_CONV */
#define CLA6SIGS1_ADC_CONV                CLA_SIGS1(4)                        /*!< the input of CLA6SIGS1 is ADC_CONV */
#define CLA7SIGS1_ADC_CONV                CLA_SIGS1(4)                        /*!< the input of CLA7SIGS1 is ADC_CONV */

#define CLA0SIGS1_TIMER0_CH3              CLA_SIGS1(5)                        /*!< the input of CLA0SIGS1 is TIMER0_CH3 */
#define CLA1SIGS1_TIMER0_CH1              CLA_SIGS1(5)                        /*!< the input of CLA1SIGS1 is TIMER0_CH1 */
#define CLA2SIGS1_TIMER0_CH0              CLA_SIGS1(5)                        /*!< the input of CLA2SIGS1 is TIMER0_CH0 */
#define CLA3SIGS1_TIMER0_CH0              CLA_SIGS1(5)                        /*!< the input of CLA3SIGS1 is TIMER0_CH0 */
#define CLA4SIGS1_TIMER0_CH3              CLA_SIGS1(5)                        /*!< the input of CLA4SIGS1 is TIMER0_CH3 */
#define CLA5SIGS1_TIMER0_CH1              CLA_SIGS1(5)                        /*!< the input of CLA5SIGS1 is TIMER0_CH1 */
#define CLA6SIGS1_TIMER0_CH0              CLA_SIGS1(5)                        /*!< the input of CLA6SIGS1 is TIMER0_CH0 */
#define CLA7SIGS1_TIMER0_CH0              CLA_SIGS1(5)                        /*!< the input of CLA7SIGS1 is TIMER0_CH0 */

#define CLA0SIGS1_TIMER1_CH0              CLA_SIGS1(6)                        /*!< the input of CLA0SIGS1 is TIMER1_CH0 */
#define CLA1SIGS1_TIMER0_CH2              CLA_SIGS1(6)                        /*!< the input of CLA1SIGS1 is TIMER0_CH2 */
#define CLA2SIGS1_TIMER0_CH2              CLA_SIGS1(6)                        /*!< the input of CLA2SIGS1 is TIMER0_CH2 */
#define CLA3SIGS1_TIMER0_CH1              CLA_SIGS1(6)                        /*!< the input of CLA3SIGS1 is TIMER0_CH1 */
#define CLA4SIGS1_TIMER1_CH0              CLA_SIGS1(6)                        /*!< the input of CLA4SIGS1 is TIMER1_CH0 */
#define CLA5SIGS1_TIMER0_CH2              CLA_SIGS1(6)                        /*!< the input of CLA5SIGS1 is TIMER0_CH2 */
#define CLA6SIGS1_TIMER0_CH2              CLA_SIGS1(6)                        /*!< the input of CLA6SIGS1 is TIMER0_CH2 */
#define CLA7SIGS1_TIMER0_CH1              CLA_SIGS1(6)                        /*!< the input of CLA7SIGS1 is TIMER0_CH1 */

#define CLA0SIGS1_TIMER1_CH1              CLA_SIGS1(7)                        /*!< the input of CLA0SIGS1 is TIMER1_CH1 */
#define CLA1SIGS1_TIMER1_CH1              CLA_SIGS1(7)                        /*!< the input of CLA1SIGS1 is TIMER1_CH1 */
#define CLA2SIGS1_TIMER1_CH0              CLA_SIGS1(7)                        /*!< the input of CLA2SIGS1 is TIMER1_CH0 */
#define CLA3SIGS1_TIMER0_CH3              CLA_SIGS1(7)                        /*!< the input of CLA3SIGS1 is TIMER0_CH3 */
#define CLA4SIGS1_TIMER1_CH1              CLA_SIGS1(7)                        /*!< the input of CLA4SIGS1 is TIMER1_CH1 */
#define CLA5SIGS1_TIMER1_CH1              CLA_SIGS1(7)                        /*!< the input of CLA5SIGS1 is TIMER1_CH1 */
#define CLA6SIGS1_TIMER1_CH0              CLA_SIGS1(7)                        /*!< the input of CLA6SIGS1 is TIMER1_CH0 */
#define CLA7SIGS1_TIMER0_CH3              CLA_SIGS1(7)                        /*!< the input of CLA7SIGS1 is TIMER0_CH3 */

#define CLA0SIGS1_CLAIN1                  CLA_SIGS1(8)                        /*!< the input of CLA0SIGS1 is CLAIN1(PB3) */
#define CLA1SIGS1_CLAIN6                  CLA_SIGS1(8)                        /*!< the input of CLA1SIGS1 is CLAIN6(PB8) */
#define CLA2SIGS1_CLAIN2                  CLA_SIGS1(8)                        /*!< the input of CLA2SIGS1 is CLAIN2(PB4) */
#define CLA3SIGS1_CLAIN0                  CLA_SIGS1(8)                        /*!< the input of CLA3SIGS1 is CLAIN0(PA15) */
#define CLA4SIGS1_CLAIN1                  CLA_SIGS1(8)                        /*!< the input of CLA4SIGS1 is CLAIN1(PB3) */
#define CLA5SIGS1_CLAIN6                  CLA_SIGS1(8)                        /*!< the input of CLA5SIGS1 is CLAIN6(PB8) */
#define CLA6SIGS1_CLAIN2                  CLA_SIGS1(8)                        /*!< the input of CLA6SIGS1 is CLAIN2(PB4) */
#define CLA7SIGS1_CLAIN0                  CLA_SIGS1(8)                        /*!< the input of CLA7SIGS1 is CLAIN0(PA15) */

#define CLA0SIGS1_CLAIN3                  CLA_SIGS1(9)                        /*!< the input of CLA0SIGS1 is CLAIN3(PB5) */
#define CLA1SIGS1_CLAIN7                  CLA_SIGS1(9)                        /*!< the input of CLA1SIGS1 is CLAIN7(PB9) */
#define CLA2SIGS1_CLAIN3                  CLA_SIGS1(9)                        /*!< the input of CLA2SIGS1 is CLAIN3(PB5) */
#define CLA3SIGS1_CLAIN1                  CLA_SIGS1(9)                        /*!< the input of CLA3SIGS1 is CLAIN1(PB3) */
#define CLA4SIGS1_CLAIN3                  CLA_SIGS1(9)                        /*!< the input of CLA4SIGS1 is CLAIN3(PB5) */
#define CLA5SIGS1_CLAIN7                  CLA_SIGS1(9)                        /*!< the input of CLA5SIGS1 is CLAIN7(PB9) */
#define CLA6SIGS1_CLAIN3                  CLA_SIGS1(9)                        /*!< the input of CLA6SIGS1 is CLAIN3(PB5) */
#define CLA7SIGS1_CLAIN1                  CLA_SIGS1(9)                        /*!< the input of CLA7SIGS1 is CLAIN1(PB3) */

#define CLA0SIGS1_CLAIN5                  CLA_SIGS1(10)                       /*!< the input of CLA0SIGS1 is CLAIN5(PB7) */
#define CLA1SIGS1_CLAIN9                  CLA_SIGS1(10)                       /*!< the input of CLA1SIGS1 is CLAIN9(PB1) */
#define CLA2SIGS1_CLAIN10                 CLA_SIGS1(10)                       /*!< the input of CLA2SIGS1 is CLAIN10(PB2) */
#define CLA3SIGS1_CLAIN4                  CLA_SIGS1(10)                       /*!< the input of CLA3SIGS1 is CLAIN4(PB6) */
#define CLA4SIGS1_CLAIN5                  CLA_SIGS1(10)                       /*!< the input of CLA4SIGS1 is CLAIN5(PB7) */
#define CLA5SIGS1_CLAIN9                  CLA_SIGS1(10)                       /*!< the input of CLA5SIGS1 is CLAIN9(PB1) */
#define CLA6SIGS1_CLAIN10                 CLA_SIGS1(10)                       /*!< the input of CLA6SIGS1 is CLAIN10(PB2) */
#define CLA7SIGS1_CLAIN4                  CLA_SIGS1(10)                       /*!< the input of CLA7SIGS1 is CLAIN4(PB6) */

#define CLA0SIGS1_CLAIN6                  CLA_SIGS1(11)                       /*!< the input of CLA0SIGS1 is CLAIN6(PB9) */
#define CLA1SIGS1_CLAIN11                 CLA_SIGS1(11)                       /*!< the input of CLA1SIGS1 is CLAIN11(PA8) */
#define CLA2SIGS1_CLAIN11                 CLA_SIGS1(11)                       /*!< the input of CLA2SIGS1 is CLAIN11(PA8) */
#define CLA3SIGS1_CLAIN5                  CLA_SIGS1(11)                       /*!< the input of CLA3SIGS1 is CLAIN5(PB7) */
#define CLA4SIGS1_CLAIN6                  CLA_SIGS1(11)                       /*!< the input of CLA4SIGS1 is CLAIN6(PB9) */
#define CLA5SIGS1_CLAIN11                 CLA_SIGS1(11)                       /*!< the input of CLA5SIGS1 is CLAIN11(PA8) */
#define CLA6SIGS1_CLAIN11                 CLA_SIGS1(11)                       /*!< the input of CLA6SIGS1 is CLAIN11(PA8) */
#define CLA7SIGS1_CLAIN5                  CLA_SIGS1(11)                       /*!< the input of CLA7SIGS1 is CLAIN5(PB7) */

#define CLA0SIGS1_CLAIN9                  CLA_SIGS1(12)                       /*!< the input of CLA0SIGS1 is CLAIN9(PB1) */
#define CLA1SIGS1_CLAIN14                 CLA_SIGS1(12)                       /*!< the input of CLA1SIGS1 is CLAIN14(PA11) */
#define CLA2SIGS1_CLAIN12                 CLA_SIGS1(12)                       /*!< the input of CLA2SIGS1 is CLAIN12(PA9) */
#define CLA3SIGS1_CLAIN8                  CLA_SIGS1(12)                       /*!< the input of CLA3SIGS1 is CLAIN8(PB0) */
#define CLA4SIGS1_CLAIN9                  CLA_SIGS1(12)                       /*!< the input of CLA4SIGS1 is CLAIN9(PB1) */
#define CLA5SIGS1_CLAIN14                 CLA_SIGS1(12)                       /*!< the input of CLA5SIGS1 is CLAIN14(PA11) */
#define CLA6SIGS1_CLAIN12                 CLA_SIGS1(12)                       /*!< the input of CLA6SIGS1 is CLAIN12(PA9) */
#define CLA7SIGS1_CLAIN8                  CLA_SIGS1(12)                       /*!< the input of CLA7SIGS1 is CLAIN8(PB0) */
 
#define CLA0SIGS1_CLAIN11                 CLA_SIGS1(13)                       /*!< the input of CLA0SIGS1 is CLAIN11(PA8) */
#define CLA1SIGS1_CLAIN15                 CLA_SIGS1(13)                       /*!< the input of CLA1SIGS1 is CLAIN15(PA12) */
#define CLA2SIGS1_CLAIN13                 CLA_SIGS1(13)                       /*!< the input of CLA2SIGS1 is CLAIN13(PA10) */
#define CLA3SIGS1_CLAIN9                  CLA_SIGS1(13)                       /*!< the input of CLA3SIGS1 is CLAIN9(PB1) */
#define CLA4SIGS1_CLAIN11                 CLA_SIGS1(13)                       /*!< the input of CLA4SIGS1 is CLAIN11(PA8) */
#define CLA5SIGS1_CLAIN15                 CLA_SIGS1(13)                       /*!< the input of CLA5SIGS1 is CLAIN15(PA12) */
#define CLA6SIGS1_CLAIN13                 CLA_SIGS1(13)                       /*!< the input of CLA6SIGS1 is CLAIN13(PA10) */
#define CLA7SIGS1_CLAIN9                  CLA_SIGS1(13)                       /*!< the input of CLA7SIGS1 is CLAIN9(PB1) */

#define CLA0SIGS1_CLAIN13                 CLA_SIGS1(14)                       /*!< the input of CLA0SIGS1 is CLAIN13(PA10) */
#define CLA1SIGS1_CLAIN17                 CLA_SIGS1(14)                       /*!< the input of CLA1SIGS1 is CLAIN17(PF1) */
#define CLA2SIGS1_CLAIN18                 CLA_SIGS1(14)                       /*!< the input of CLA2SIGS1 is CLAIN18(PA0) */
#define CLA3SIGS1_CLAIN16                 CLA_SIGS1(14)                       /*!< the input of CLA3SIGS1 is CLAIN16(PF0) */
#define CLA4SIGS1_CLAIN13                 CLA_SIGS1(14)                       /*!< the input of CLA4SIGS1 is CLAIN13(PA10) */
#define CLA5SIGS1_CLAIN17                 CLA_SIGS1(14)                       /*!< the input of CLA5SIGS1 is CLAIN17(PF1) */
#define CLA6SIGS1_CLAIN18                 CLA_SIGS1(14)                       /*!< the input of CLA6SIGS1 is CLAIN18(PA0) */
#define CLA7SIGS1_CLAIN16                 CLA_SIGS1(14)                       /*!< the input of CLA7SIGS1 is CLAIN16(PF0) */

#define CLA0SIGS1_CLAIN15                 CLA_SIGS1(15)                       /*!< the input of CLA0SIGS1 is CLAIN15(PA12) */
#define CLA1SIGS1_CLAIN19                 CLA_SIGS1(15)                       /*!< the input of CLA1SIGS1 is CLAIN19(PA1) */
#define CLA2SIGS1_CLAIN19                 CLA_SIGS1(15)                       /*!< the input of CLA2SIGS1 is CLAIN19(PA1) */
#define CLA3SIGS1_CLAIN17                 CLA_SIGS1(15)                       /*!< the input of CLA3SIGS1 is CLAIN17(PF1) */
#define CLA4SIGS1_CLAIN15                 CLA_SIGS1(15)                       /*!< the input of CLA4SIGS1 is CLAIN15(PA12) */
#define CLA5SIGS1_CLAIN19                 CLA_SIGS1(15)                       /*!< the input of CLA5SIGS1 is CLAIN19(PA1) */
#define CLA6SIGS1_CLAIN19                 CLA_SIGS1(15)                       /*!< the input of CLA6SIGS1 is CLAIN19(PA1) */
#define CLA7SIGS1_CLAIN17                 CLA_SIGS1(15)                       /*!< the input of CLA7SIGS1 is CLAIN17(PF1) */

#define CLA0SIGS1_CLA4_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(0)        /*!< the input of CLA0SIGS1 is CLA4_ASYNC_OUT */
#define CLA1SIGS1_CLA4_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(0)        /*!< the input of CLA1SIGS1 is CLA4_ASYNC_OUT */
#define CLA2SIGS1_CLA4_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(0)        /*!< the input of CLA2SIGS1 is CLA4_ASYNC_OUT */
#define CLA3SIGS1_CLA4_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(0)        /*!< the input of CLA3SIGS1 is CLA4_ASYNC_OUT */
#define CLA4SIGS1_CLA4_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(0)        /*!< the input of CLA4SIGS1 is CLA4_ASYNC_OUT */
#define CLA5SIGS1_CLA4_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(0)        /*!< the input of CLA5SIGS1 is CLA4_ASYNC_OUT */
#define CLA6SIGS1_CLA4_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(0)        /*!< the input of CLA6SIGS1 is CLA4_ASYNC_OUT */
#define CLA7SIGS1_CLA4_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(0)        /*!< the input of CLA7SIGS1 is CLA4_ASYNC_OUT */

#define CLA0SIGS1_CLA5_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(1)        /*!< the input of CLA0SIGS1 is CLA5_ASYNC_OUT */
#define CLA1SIGS1_CLA5_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(1)        /*!< the input of CLA1SIGS1 is CLA5_ASYNC_OUT */
#define CLA2SIGS1_CLA5_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(1)        /*!< the input of CLA2SIGS1 is CLA5_ASYNC_OUT */
#define CLA3SIGS1_CLA5_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(1)        /*!< the input of CLA3SIGS1 is CLA5_ASYNC_OUT */
#define CLA4SIGS1_CLA5_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(1)        /*!< the input of CLA4SIGS1 is CLA5_ASYNC_OUT */
#define CLA5SIGS1_CLA5_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(1)        /*!< the input of CLA5SIGS1 is CLA5_ASYNC_OUT */
#define CLA6SIGS1_CLA5_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(1)        /*!< the input of CLA6SIGS1 is CLA5_ASYNC_OUT */
#define CLA7SIGS1_CLA5_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(1)        /*!< the input of CLA7SIGS1 is CLA5_ASYNC_OUT */

#define CLA1SIGS1_CLA6_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(2)        /*!< the input of CLA1SIGS1 is CLA6_ASYNC_OUT */
#define CLA2SIGS1_CLA6_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(2)        /*!< the input of CLA2SIGS1 is CLA6_ASYNC_OUT */
#define CLA3SIGS1_CLA6_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(2)        /*!< the input of CLA3SIGS1 is CLA6_ASYNC_OUT */
#define CLA4SIGS1_CLA6_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(2)        /*!< the input of CLA4SIGS1 is CLA6_ASYNC_OUT */
#define CLA5SIGS1_CLA6_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(2)        /*!< the input of CLA5SIGS1 is CLA6_ASYNC_OUT */
#define CLA6SIGS1_CLA6_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(2)        /*!< the input of CLA6SIGS1 is CLA6_ASYNC_OUT */
#define CLA7SIGS1_CLA6_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(2)        /*!< the input of CLA7SIGS1 is CLA6_ASYNC_OUT */

#define CLA0SIGS1_CLA7_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(3)        /*!< the input of CLA0SIGS1 is CLA7_ASYNC_OUT */
#define CLA1SIGS1_CLA7_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(3)        /*!< the input of CLA1SIGS1 is CLA7_ASYNC_OUT */
#define CLA2SIGS1_CLA7_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(3)        /*!< the input of CLA2SIGS1 is CLA7_ASYNC_OUT */
#define CLA3SIGS1_CLA7_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(3)        /*!< the input of CLA3SIGS1 is CLA7_ASYNC_OUT */
#define CLA4SIGS1_CLA7_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(3)        /*!< the input of CLA4SIGS1 is CLA7_ASYNC_OUT */
#define CLA5SIGS1_CLA7_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(3)        /*!< the input of CLA5SIGS1 is CLA7_ASYNC_OUT */
#define CLA6SIGS1_CLA7_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(3)        /*!< the input of CLA6SIGS1 is CLA7_ASYNC_OUT */
#define CLA7SIGS1_CLA7_ASYNC_OUT          CLA_SIGS_SIGS1_5|CLA_SIGS1(3)        /*!< the input of CLA7SIGS1 is CLA7_ASYNC_OUT */

/* LCU control */
#define LCUCTL(regval)                   (BITS(0,7) & ((uint32_t)(regval) << 0))

/* CLA output selection */
#define FLIP_FLOP_OUTPUT                 ((uint32_t )0x00000000U)           /*!< flip-flop output is selected as CLAx output */
#define LCU_RESULT                       CLA_CTL_OSEL                       /*!< LCU result is selected as CLAx output */

/* flip-flop clock polarity selection */
#define CLA_CLOCKPOLARITY_POSEDGE        ((uint32_t)0x00000000U)            /*!< the clock polarity of flip-flop is posedge */
#define CLA_CLOCKPOLARITY_NEGEDGE        CLA_CTL_CPOL                       /*!< the clock polarity of flip-flop is negedge */

/* flip-flop clock source selection */
#define PRE_CLA_LCU_RESULT               ((uint32_t)0x00000000U)            /*!< the LCU result of the previous CLA units */
#define SIGS0_OUTPUT                     ((uint32_t)0x00000001U)            /*!< the multiplexer output of SIGS0 */
#define HCLK                             ((uint32_t)0x00000002U)            /*!< HCLK */
#define TIMER_TRGO                       ((uint32_t)0x00000003U)            /*!< TIMER_TRGO */

/* function declarations */
/* CLA initialization and configuration functions */
/* reset CLA */
void cla_deinit(void);
/* enable CLA */
void cla_enable(cla_enum cla_periph);
/* disable CLA */
void cla_disable(cla_enum cla_periph);  
/* get CLA output state */
cla_outputstatus_enum cla_output_state_get(cla_enum cla_periph);
/* configure signal selector input */
void cla_sigs_input_config(cla_enum cla_periph, cla_sigs_enum sigs, uint32_t input);
/* configure CLA LCU control register value */
void cla_lcu_control_config(cla_enum cla_periph, uint8_t lcuctl_value);
/* configure CLA output */
void cla_output_config(cla_enum cla_periph, uint32_t output);
/* enable CLA output */
void cla_output_enable(cla_enum cla_periph);
/* disable CLA output */
void cla_output_disable(cla_enum cla_periph);

/* flip-flop configuration */
/* reset the flip-flop output asynchronously */
void cla_flip_flop_output_reset(cla_enum cla_periph);
/* configure clock polarity of flip-flop */
void cla_flip_flop_clockpolarity_config(cla_enum cla_periph, uint32_t polarity);
/* configure clock source of flip-flop */
void cla_flip_flop_clocksource_config(cla_enum cla_periph, uint32_t clock_source);

/* flag and interrupt functions */
/* check CLA flag is set or not */
FlagStatus cla_flag_get(cla_flag_enum flag);
/* clear CLA flag */
void cla_flag_clear(cla_flag_enum flag);
/* enable CLA negedge interrupt */
void cla_negedge_interrupt_enable(uint32_t clanie);
/* disable CLA negedge interrupt */
void cla_negedge_interrupt_disable(uint32_t clanidis);
/* enable CLA posedge interrupt */
void cla_posedge_interrupt_enable(uint32_t clapie);
/* disable CLA posedge interrupt */
void cla_posedge_interrupt_disable(uint32_t clapidis);
/* check CLA interrupt flag is set or not */
FlagStatus cla_interrupt_flag_get(cla_interrupt_flag_enum int_flag);
/* clear CLA interrupt flag */
void cla_interrupt_flag_clear(cla_interrupt_flag_enum int_flag);

#endif /* GD32E501_CLA_H */

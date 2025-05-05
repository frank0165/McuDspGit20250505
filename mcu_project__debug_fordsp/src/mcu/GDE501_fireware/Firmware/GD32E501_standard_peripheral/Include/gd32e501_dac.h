/*!
    \file    gd32e501_dac.h
    \brief   definitions for the DAC
    
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

#ifndef GD32E501_DAC_H
#define GD32E501_DAC_H

#include "gd32e501.h"

/* DACx(x=0,1,2,3) definitions */
#define DAC0                    DAC0_BASE
#define DAC1                    DAC1_BASE
#define DAC2                    (DAC1_BASE + 0x00000400U)
#define DAC3                    (DAC1_BASE + 0x00000800U)

/* registers definitions */
#define DAC_CTL(dacx)           REG32((dacx) + 0x00000000U)          /*!< DAC control register */
#define DAC_SWT(dacx)           REG32((dacx) + 0x00000004U)          /*!< DAC software trigger register */
#define OUT0_R12DH(dacx)        REG32((dacx) + 0x00000008U)          /*!< DACx_OUT0 12-bit right-aligned data holding register */
#define OUT0_L12DH(dacx)        REG32((dacx) + 0x0000000CU)          /*!< DACx_OUT0 12-bit left-aligned data holding register */
#define OUT0_R8DH(dacx)         REG32((dacx) + 0x00000010U)          /*!< DACx_OUT0 8-bit right-aligned data holding register */
#define OUT1_R12DH(dacx)        REG32((dacx) + 0x00000014U)          /*!< DACx_OUT1 12-bit right-aligned data holding register */
#define OUT1_L12DH(dacx)        REG32((dacx) + 0x00000018U)          /*!< DACx_OUT1 12-bit left-aligned data holding register */
#define OUT1_R8DH(dacx)         REG32((dacx) + 0x0000001CU)          /*!< DACx_OUT1 8-bit right-aligned data holding register */
#define DACC_R12DH(dacx)        REG32((dacx) + 0x00000020U)          /*!< DAC concurrent mode 12-bit right-aligned data holding register */
#define DACC_L12DH(dacx)        REG32((dacx) + 0x00000024U)          /*!< DAC concurrent mode 12-bit left-aligned data holding register */
#define DACC_R8DH(dacx)         REG32((dacx) + 0x00000028U)          /*!< DAC concurrent mode 8-bit right-aligned data holding register */
#define OUT0_DO(dacx)           REG32((dacx) + 0x0000002CU)          /*!< DACx_OUT0 data output register */
#define OUT1_DO(dacx)           REG32((dacx) + 0x00000030U)          /*!< DACx_OUT1 data output register */
#define DAC_STAT(dacx)          REG32((dacx) + 0x00000034U)          /*!< DAC status register */
#define DAC_OCTL(dacx)          REG32((dacx) + 0x00000080U)          /*!< DAC output control register */

/* bits definitions */
/* DAC_CTL */
#define DAC_CTL_DEN0            BIT(0)                               /*!< DACx_OUT0 enable/disable bit */
#define DAC_CTL_DBOFF0          BIT(1)                               /*!< DACx_OUT0 output buffer turn on/turn off bit */
#define DAC_CTL_DTEN0           BIT(2)                               /*!< DACx_OUT0 trigger enable/disable bit */
#define DAC_CTL_DTSEL0          BITS(3,5)                            /*!< DACx_OUT0 trigger source selection enable/disable bits */
#define DAC_CTL_DWM0            BITS(6,7)                            /*!< DACx_OUT0 noise wave mode */
#define DAC_CTL_DWBW0           BITS(8,11)                           /*!< DACx_OUT0 noise wave bit width */
#define DAC_CTL_DDMAEN0         BIT(12)                              /*!< DACx_OUT0 DMA enable/disable bit */
#define DAC_CTL_DDUDRIE0        BIT(13)                              /*!< DACx_OUT0 DMA underrun interrupt enable/disable bit */
#define DAC_CTL_DTSEL0_3        BIT(14)                              /*!< DACx_OUT0 trigger selection bit[3], refer to DTSEL1[2:0] */
#define DAC_CTL_DRSTMD0         BIT(15)                              /*!< DACx_OUT0 reset mode bit */
#define DAC_CTL_DEN1            BIT(16)                              /*!< DACx_OUT1 enable/disable bit */ 
#define DAC_CTL_DBOFF1          BIT(17)                              /*!< DACx_OUT1 output buffer turn on/turn off bit */
#define DAC_CTL_DTEN1           BIT(18)                              /*!< DACx_OUT1 trigger enable/disable bit */
#define DAC_CTL_DTSEL1          BITS(19,21)                          /*!< DACx_OUT1 trigger source selection enable/disable bits */
#define DAC_CTL_DWM1            BITS(22,23)                          /*!< DACx_OUT1 noise wave mode */
#define DAC_CTL_DWBW1           BITS(24,27)                          /*!< DACx_OUT1 noise wave bit width */
#define DAC_CTL_DDMAEN1         BIT(28)                              /*!< DACx_OUT1 DMA enable/disable bit */
#define DAC_CTL_DDUDRIE1        BIT(29)                              /*!< DACx_OUT1 DMA underrun interrupt enable/disable bit */
#define DAC_CTL_DTSEL1_3        BIT(30)                              /*!< DACx_OUT1 trigger selection bit[3], refer to DTSEL1[2:0] */
#define DAC_CTL_DRSTMD1         BIT(31)                              /*!< DACx_OUT1 reset mode bit */

/* DAC_SWT */                                                        
#define DAC_SWT_SWTR0           BIT(0)                               /*!< DACx_OUT0 software trigger bit, cleared by hardware */
#define DAC_SWT_SWTR1           BIT(1)                               /*!< DACx_OUT1 software trigger bit, cleared by hardware */

/* DAC0_R12DH */                                                     
#define OUT0_R12DH_DH           BITS(0,11)                           /*!< DACx_OUT0 12-bit right-aligned data bits */

/* DAC0_L12DH */                                                         
#define OUT0_L12DH_DH           BITS(4,15)                           /*!< DACx_OUT0 12-bit left-aligned data bits */

/* DAC0_R8DH */                                                          
#define OUT0_R8DH_DH            BITS(0,7)                            /*!< DACx_OUT0 8-bit right-aligned data bits */

/* DAC1_R12DH */                                                         
#define OUT1_R12DH_DH           BITS(0,11)                           /*!< DACx_OUT1 12-bit right-aligned data bits */

/* DAC1_L12DH */                                                         
#define OUT1_L12DH_DH           BITS(4,15)                           /*!< DACx_OUT1 12-bit left-aligned data bits */

/* DAC1_R8DH */                                                          
#define OUT1_R8DH_DH            BITS(0,7)                            /*!< DACx_OUT1 8-bit right-aligned data bits */

/* DACC_R12DH */                                                     
#define DACC_R12DH_OUT0_DH      BITS(0,11)                           /*!< DAC concurrent mode DACx_OUT0 12-bit right-aligned data bits */
#define DACC_R12DH_OUT1_DH      BITS(16,27)                          /*!< DAC concurrent mode DACx_OUT1 12-bit right-aligned data bits */

/* DACC_L12DH */                                                     
#define DACC_L12DH_OUT0_DH      BITS(4,15)                           /*!< DAC concurrent mode DACx_OUT0 12-bit left-aligned data bits */
#define DACC_L12DH_OUT1_DH      BITS(20,31)                          /*!< DAC concurrent mode DACx_OUT1 12-bit left-aligned data bits */

/* DACC_R8DH */                                                      
#define DACC_R8DH_OUT0_DH       BITS(0,7)                            /*!< DAC concurrent mode DACx_OUT0 8-bit right-aligned data bits */
#define DACC_R8DH_OUT1_DH       BITS(8,15)                           /*!< DAC concurrent mode DACx_OUT1 8-bit right-aligned data bits */

/* DAC0_DO */                                                        
#define DACx_OUT0_DO            BITS(0,11)                           /*!< DACx_OUT0 12-bit output data bits */

/* DAC1_DO */                                                        
#define DACx_OUT1_DO            BITS(0,11)                           /*!< DACx_OUT1 12-bit output data bits */

/* DAC_STAT */                                                       
#define DAC_STAT_DDUDR0         BIT(13)                              /*!< DACx_OUT0 DMA underrun flag */
#define DAC_STAT_DDUDR1         BIT(29)                              /*!< DACx_OUT1 DMA underrun flag */

/* DAC_OCTL */                                                       
#define DAC_OCTL_GS0            BIT(0)                               /*!< DACx_OUT0 output buffer gain selection */
#define DAC_OCTL_GS1            BIT(16)                              /*!< DACx_OUT1 output buffer gain selection */

/* constants definitions */
/* DAC trigger source */
#define CTL_DTSEL(regval)            (BITS(3,5) & ((uint32_t)(regval) << 3))
#define DAC_TRIGGER_T5_TRGO          CTL_DTSEL(0)                         /*!< TIMER5 TRGO */
#define DAC_TRIGGER_T14_TRGO         CTL_DTSEL(1)                         /*!< TIMER14 TRGO */
#define DAC_TRIGGER_T6_TRGO          CTL_DTSEL(2)                         /*!< TIMER6 TRGO */
#define DAC_TRIGGER_T2_TRGO          CTL_DTSEL(3)                         /*!< TIMER2 TRGO */
#define DAC_TRIGGER_T1_TRGO          CTL_DTSEL(4)                         /*!< TIMER1 TRGO */
#define DAC_TRIGGER_T0_TRGO          CTL_DTSEL(5)                         /*!< TIMER0 TRGO */
#define DAC_TRIGGER_EXTI_9           CTL_DTSEL(6)                         /*!< EXTI interrupt line9 event */
#define DAC_TRIGGER_SOFTWARE         CTL_DTSEL(7)                         /*!< software trigger */
#define DAC_TRIGGER_CLA0             (DAC_CTL_DTSEL0_3 | CTL_DTSEL(0))    /*!< CLA0 trigger */
#define DAC_TRIGGER_CLA1             (DAC_CTL_DTSEL0_3 | CTL_DTSEL(1))    /*!< CLA1 trigger */
#define DAC_TRIGGER_CLA2             (DAC_CTL_DTSEL0_3 | CTL_DTSEL(2))    /*!< CLA2 trigger */
#define DAC_TRIGGER_CLA3             (DAC_CTL_DTSEL0_3 | CTL_DTSEL(3))    /*!< CLA3 trigger */

/* DAC noise wave mode */
#define CTL_DWM(regval)              (BITS(6,7) & ((uint32_t)(regval) << 6))
#define DAC_WAVE_DISABLE             CTL_DWM(0)                           /*!< wave disable */
#define DAC_WAVE_MODE_LFSR           CTL_DWM(1)                           /*!< LFSR noise mode */
#define DAC_WAVE_MODE_TRIANGLE       CTL_DWM(2)                           /*!< triangle noise mode */

/* DAC noise wave bit width */
#define DWBW(regval)                 (BITS(8,11) & ((uint32_t)(regval) << 8))
#define DAC_WAVE_BIT_WIDTH_1         DWBW(0)                              /*!< bit width of the wave signal is 1 */
#define DAC_WAVE_BIT_WIDTH_2         DWBW(1)                              /*!< bit width of the wave signal is 2 */
#define DAC_WAVE_BIT_WIDTH_3         DWBW(2)                              /*!< bit width of the wave signal is 3 */
#define DAC_WAVE_BIT_WIDTH_4         DWBW(3)                              /*!< bit width of the wave signal is 4 */
#define DAC_WAVE_BIT_WIDTH_5         DWBW(4)                              /*!< bit width of the wave signal is 5 */
#define DAC_WAVE_BIT_WIDTH_6         DWBW(5)                              /*!< bit width of the wave signal is 6 */
#define DAC_WAVE_BIT_WIDTH_7         DWBW(6)                              /*!< bit width of the wave signal is 7 */
#define DAC_WAVE_BIT_WIDTH_8         DWBW(7)                              /*!< bit width of the wave signal is 8 */
#define DAC_WAVE_BIT_WIDTH_9         DWBW(8)                              /*!< bit width of the wave signal is 9 */
#define DAC_WAVE_BIT_WIDTH_10        DWBW(9)                              /*!< bit width of the wave signal is 10 */
#define DAC_WAVE_BIT_WIDTH_11        DWBW(10)                             /*!< bit width of the wave signal is 11 */
#define DAC_WAVE_BIT_WIDTH_12        DWBW(11)                             /*!< bit width of the wave signal is 12 */
   
/* unmask LFSR bits in DAC LFSR noise mode */          
#define DAC_LFSR_BIT0                DAC_WAVE_BIT_WIDTH_1                 /*!< unmask the LFSR bit0 */
#define DAC_LFSR_BITS1_0             DAC_WAVE_BIT_WIDTH_2                 /*!< unmask the LFSR bits[1:0] */
#define DAC_LFSR_BITS2_0             DAC_WAVE_BIT_WIDTH_3                 /*!< unmask the LFSR bits[2:0] */
#define DAC_LFSR_BITS3_0             DAC_WAVE_BIT_WIDTH_4                 /*!< unmask the LFSR bits[3:0] */
#define DAC_LFSR_BITS4_0             DAC_WAVE_BIT_WIDTH_5                 /*!< unmask the LFSR bits[4:0] */
#define DAC_LFSR_BITS5_0             DAC_WAVE_BIT_WIDTH_6                 /*!< unmask the LFSR bits[5:0] */
#define DAC_LFSR_BITS6_0             DAC_WAVE_BIT_WIDTH_7                 /*!< unmask the LFSR bits[6:0] */
#define DAC_LFSR_BITS7_0             DAC_WAVE_BIT_WIDTH_8                 /*!< unmask the LFSR bits[7:0] */
#define DAC_LFSR_BITS8_0             DAC_WAVE_BIT_WIDTH_9                 /*!< unmask the LFSR bits[8:0] */
#define DAC_LFSR_BITS9_0             DAC_WAVE_BIT_WIDTH_10                /*!< unmask the LFSR bits[9:0] */
#define DAC_LFSR_BITS10_0            DAC_WAVE_BIT_WIDTH_11                /*!< unmask the LFSR bits[10:0] */
#define DAC_LFSR_BITS11_0            DAC_WAVE_BIT_WIDTH_12                /*!< unmask the LFSR bits[11:0] */

/* DAC data alignment */
#define DATA_ALIGN(regval)           (BITS(0,1) & ((uint32_t)(regval) << 0))
#define DAC_ALIGN_12B_R              DATA_ALIGN(0)                        /*!< 12-bit right-aligned data */
#define DAC_ALIGN_12B_L              DATA_ALIGN(1)                        /*!< 12-bit left-aligned data */
#define DAC_ALIGN_8B_R               DATA_ALIGN(2)                        /*!< 8-bit right-aligned data */
                                                                     
/* triangle amplitude in DAC triangle noise mode */                  
#define DAC_TRIANGLE_AMPLITUDE_1     DAC_WAVE_BIT_WIDTH_1                 /*!< triangle amplitude is 1 */
#define DAC_TRIANGLE_AMPLITUDE_3     DAC_WAVE_BIT_WIDTH_2                 /*!< triangle amplitude is 3 */
#define DAC_TRIANGLE_AMPLITUDE_7     DAC_WAVE_BIT_WIDTH_3                 /*!< triangle amplitude is 7 */
#define DAC_TRIANGLE_AMPLITUDE_15    DAC_WAVE_BIT_WIDTH_4                 /*!< triangle amplitude is 15 */
#define DAC_TRIANGLE_AMPLITUDE_31    DAC_WAVE_BIT_WIDTH_5                 /*!< triangle amplitude is 31 */
#define DAC_TRIANGLE_AMPLITUDE_63    DAC_WAVE_BIT_WIDTH_6                 /*!< triangle amplitude is 63 */
#define DAC_TRIANGLE_AMPLITUDE_127   DAC_WAVE_BIT_WIDTH_7                 /*!< triangle amplitude is 127 */
#define DAC_TRIANGLE_AMPLITUDE_255   DAC_WAVE_BIT_WIDTH_8                 /*!< triangle amplitude is 255 */
#define DAC_TRIANGLE_AMPLITUDE_511   DAC_WAVE_BIT_WIDTH_9                 /*!< triangle amplitude is 511 */
#define DAC_TRIANGLE_AMPLITUDE_1023  DAC_WAVE_BIT_WIDTH_10                /*!< triangle amplitude is 1023 */
#define DAC_TRIANGLE_AMPLITUDE_2047  DAC_WAVE_BIT_WIDTH_11                /*!< triangle amplitude is 2047 */
#define DAC_TRIANGLE_AMPLITUDE_4095  DAC_WAVE_BIT_WIDTH_12                /*!< triangle amplitude is 4095 */

/* DAC output channel definitions */
#define DAC_OUT_0                    ((uint8_t)0x00U)                     /*!< DACx_OUT0 */
#define DAC_OUT_1                    ((uint8_t)0x01U)                     /*!< DACx_OUT1 */

/* DAC_OUT output buffer gain */
#define DAC_OUT_GAIN_1               ((uint32_t)0x00000000U)              /*!< DAC_OUT output buffer gain is 1 */
#define DAC_OUT_GAIN_2               ((uint32_t)0x00000001U)              /*!< DAC_OUT output buffer gain is 2 */

/* function declarations */
/* initialization functions */
/* deinitialize DAC */
void dac_deinit(uint32_t dac_periph);
/* enable DAC */
void dac_enable(uint32_t dac_periph, uint8_t dac_out);
/* disable DAC */
void dac_disable(uint32_t dac_periph, uint8_t dac_out);
/* enable DAC DMA function */
void dac_dma_enable(uint32_t dac_periph, uint8_t dac_out);
/* disable DAC DMA function */
void dac_dma_disable(uint32_t dac_periph, uint8_t dac_out); 
/* enable DAC output buffer */
void dac_output_buffer_enable(uint32_t dac_periph, uint8_t dac_out);
/* disable DAC output buffer */
void dac_output_buffer_disable(uint32_t dac_periph, uint8_t dac_out);
/* get DAC output value */
uint16_t dac_output_value_get(uint32_t dac_periph, uint8_t dac_out);
/* set DAC data holding register value */
void dac_data_set(uint32_t dac_periph, uint8_t dac_out, uint32_t dac_align, uint16_t data);
/* enable DAC reset persisting mode */
void dac_reset_mode_enable(uint32_t dac_periph, uint8_t dac_out);
/* disable DAC reset persisting mode */
void dac_reset_mode_disable(uint32_t dac_periph, uint8_t dac_out);

/* DAC trigger configuration */
/* enable DAC trigger */
void dac_trigger_enable(uint32_t dac_periph, uint8_t dac_out);
/* disable DAC trigger */
void dac_trigger_disable(uint32_t dac_periph, uint8_t dac_out);
/* configure DAC trigger source */
void dac_trigger_source_config(uint32_t dac_periph, uint8_t dac_out, uint32_t triggersource);
/* enable DAC software trigger */
void dac_software_trigger_enable(uint32_t dac_periph, uint8_t dac_out);
/* disable DAC software trigger */
void dac_software_trigger_disable(uint32_t dac_periph, uint8_t dac_out);

/* DAC wave mode configuration */
/* configure DAC wave mode */
void dac_wave_mode_config(uint32_t dac_periph, uint8_t dac_out, uint32_t wave_mode);
/* configure DAC wave bit width */
void dac_wave_bit_width_config(uint32_t dac_periph, uint8_t dac_out, uint32_t bit_width);
/* configure DAC LFSR noise mode */
void dac_lfsr_noise_config(uint32_t dac_periph, uint8_t dac_out, uint32_t unmask_bits);
/* configure DAC triangle noise mode */
void dac_triangle_noise_config(uint32_t dac_periph, uint8_t dac_out, uint32_t amplitude);
/* configure DAC output buffer gain */
void dac_buffer_gain_config(uint32_t dac_periph, uint8_t dac_out, uint32_t buffer_gain);

/* DAC concurrent mode configuration */
/* enable DAC concurrent mode */
void dac_concurrent_enable(uint32_t dac_periph);
/* disable DAC concurrent mode */
void dac_concurrent_disable(uint32_t dac_periph);
/* enable DAC concurrent software trigger */
void dac_concurrent_software_trigger_enable(uint32_t dac_periph);
/* disable DAC concurrent software trigger */
void dac_concurrent_software_trigger_disable(uint32_t dac_periph);
/* enable DAC concurrent buffer function */
void dac_concurrent_output_buffer_enable(uint32_t dac_periph);
/* disable DAC concurrent buffer function */
void dac_concurrent_output_buffer_disable(uint32_t dac_periph);
/* set DAC concurrent mode data holding register value */
void dac_concurrent_data_set(uint32_t dac_periph, uint32_t dac_align, uint16_t data0, uint16_t data1);

/* interrupt and flag functions */
/* get the specified DAC flag (DAC DMA underrun flag) */
FlagStatus dac_flag_get(uint32_t dac_periph, uint8_t dac_out);
/* clear the specified DAC flag (DAC DMA underrun flag) */
void dac_flag_clear(uint32_t dac_periph, uint8_t dac_out);
/* enable DAC interrupt (DAC DMA underrun interrupt) */
void dac_interrupt_enable(uint32_t dac_periph, uint8_t dac_out);
/* disable DAC interrupt (DAC DMA underrun interrupt) */
void dac_interrupt_disable(uint32_t dac_periph, uint8_t dac_out);
/* get the specified DAC interrupt flag (DAC DMA underrun interrupt flag) */
FlagStatus dac_interrupt_flag_get(uint32_t dac_periph, uint8_t dac_out);
/* clear the specified DAC interrupt flag (DAC DMA underrun interrupt flag) */
void dac_interrupt_flag_clear(uint32_t dac_periph, uint8_t dac_out); 

#endif /* GD32E501_DAC_H */

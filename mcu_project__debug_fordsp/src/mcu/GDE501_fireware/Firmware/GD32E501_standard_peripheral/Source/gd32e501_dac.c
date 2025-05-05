/*!
    \file    gd32e501_dac.c
    \brief   DAC driver
    
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

#include "gd32e501_dac.h"

/* DAC register bit offset */
#define OUT1_REG_OFFSET           ((uint32_t)0x00000010U)
#define DH_12BIT_OFFSET           ((uint32_t)0x00000010U)
#define DH_8BIT_OFFSET            ((uint32_t)0x00000008U)

/*!
    \brief      deinitialize DAC
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void dac_deinit(uint32_t dac_periph)
{
    switch(dac_periph){
    case DAC0:
        /* reset DAC0 */
        rcu_periph_reset_enable(RCU_DAC0RST);
        rcu_periph_reset_disable(RCU_DAC0RST);
        break;
    case DAC1:
        /* reset DAC1 */
        rcu_periph_reset_enable(RCU_DAC1RST);
        rcu_periph_reset_disable(RCU_DAC1RST);
        break;
    case DAC2:
        /* reset DAC2 */
        rcu_periph_reset_enable(RCU_DAC2RST);
        rcu_periph_reset_disable(RCU_DAC2RST);
        break;
    case DAC3:
        /* reset DAC3 */
        rcu_periph_reset_enable(RCU_DAC3RST);
        rcu_periph_reset_disable(RCU_DAC3RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable DAC
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DEN0;
    }else{
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DEN1;
    }
}

/*!
    \brief      disable DAC
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DEN0);
    }else{
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DEN1);
    }
}

/*!
    \brief      enable DAC DMA function
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_dma_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DDMAEN0;
    }else{
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DDMAEN1;
    }
}

/*!
    \brief      disable DAC DMA function
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_dma_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DDMAEN0);
    }else{
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DDMAEN1);
    }
}

/*!
    \brief      enable DAC output buffer
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_output_buffer_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DBOFF0);
    }else{
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DBOFF1);
    }
}

/*!
    \brief      disable DAC output buffer
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_output_buffer_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DBOFF0;
    }else{
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DBOFF1;
    }
}

/*!
    \brief      get DAC output value
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     DAC output data: 0~4095
*/
uint16_t dac_output_value_get(uint32_t dac_periph, uint8_t dac_out)
{
    uint16_t data = 0U;
    if(DAC_OUT_0 == dac_out){
        /* store the DAC_OUT0 output value */
        data = (uint16_t)OUT0_DO(dac_periph);
    }else{
        /* store the DAC_OUT1 output value */
        data = (uint16_t)OUT1_DO(dac_periph);
    }
    return data;
}

/*!
    \brief      set DAC data holding register value
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[in]  dac_align: DAC data alignment mode
                only one parameter can be selected which is shown as below:
      \arg        DAC_ALIGN_12B_R: 12-bit right-aligned data
      \arg        DAC_ALIGN_12B_L: 12-bit left-aligned data
      \arg        DAC_ALIGN_8B_R: 8-bit right-aligned data
    \param[in]  data: data to be loaded(0~4095)
    \param[out] none
    \retval     none
*/
void dac_data_set(uint32_t dac_periph, uint8_t dac_out, uint32_t dac_align, uint16_t data)
{
    /* DAC_OUT0 data alignment */
    if(DAC_OUT_0 == dac_out){
        switch(dac_align){
        /* 12-bit right-aligned data */
        case DAC_ALIGN_12B_R:
            OUT0_R12DH(dac_periph) = data;
            break;
        /* 12-bit left-aligned data */
        case DAC_ALIGN_12B_L:
            OUT0_L12DH(dac_periph) = data;
            break;
        /* 8-bit right-aligned data */
        case DAC_ALIGN_8B_R:
            OUT0_R8DH(dac_periph) = data;
            break;
        default:
            break;
        }
    }else{
        /* DAC_OUT1 data alignment */
        switch(dac_align){
        /* 12-bit right-aligned data */
        case DAC_ALIGN_12B_R:
            OUT1_R12DH(dac_periph) = data;
            break;
        /* 12-bit left-aligned data */
        case DAC_ALIGN_12B_L:
            OUT1_L12DH(dac_periph) = data;
            break;
        /* 8-bit right-aligned data */
        case DAC_ALIGN_8B_R:
            OUT1_R8DH(dac_periph) = data;
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      enable DAC reset persisting mode
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_reset_mode_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DRSTMD0;
    }else{
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DRSTMD1;
    }
}

/*!
    \brief      disable DAC reset persisting mode
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_reset_mode_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DRSTMD0);
    }else{
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DRSTMD1);
    }
}

/*!
    \brief      enable DAC trigger
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_trigger_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DTEN0;
    }else{
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DTEN1;
    }
}

/*!
    \brief      disable DAC trigger
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_trigger_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DTEN0);
    }else{
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DTEN1);
    }
}

/*!
    \brief      configure DAC trigger source
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[in]  triggersource: external trigger of DAC
                only one parameter can be selected which is shown as below:
      \arg        DAC_TRIGGER_T5_TRGO: TIMER5 TRGO
      \arg        DAC_TRIGGER_T14_TRGO: TIMER14 TRGO
      \arg        DAC_TRIGGER_T6_TRGO: TIMER6 TRGO
      \arg        DAC_TRIGGER_T2_TRGO: TIMER2 TRGO
      \arg        DAC_TRIGGER_T1_TRGO: TIMER1 TRGO
      \arg        DAC_TRIGGER_T0_TRGO: TIMER0 TRGO
      \arg        DAC_TRIGGER_EXTI_9: EXTI interrupt line9 event
      \arg        DAC_TRIGGER_SOFTWARE: software trigger
      \arg        DAC_TRIGGER_CLA0: CLA0 trigger
      \arg        DAC_TRIGGER_CLA1: CLA1 trigger
      \arg        DAC_TRIGGER_CLA2: CLA2 trigger
      \arg        DAC_TRIGGER_CLA3: CLA3 trigger
    \param[out] none
    \retval     none
*/
void dac_trigger_source_config(uint32_t dac_periph, uint8_t dac_out, uint32_t triggersource)
{
    if(DAC_OUT_0 == dac_out){
        /* configure DAC_OUT0 trigger source */
        DAC_CTL(dac_periph) &= (uint32_t)(~(DAC_CTL_DTSEL0 | DAC_CTL_DTSEL0_3));
        DAC_CTL(dac_periph) |= triggersource;
    }else{
        /* configure DAC_OUT1 trigger source */
        DAC_CTL(dac_periph) &= (uint32_t)(~(DAC_CTL_DTSEL1 | DAC_CTL_DTSEL1_3));
        DAC_CTL(dac_periph) |= (triggersource << OUT1_REG_OFFSET);
    }
}

/*!
    \brief      enable DAC software trigger
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \retval     none
*/
void dac_software_trigger_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_SWT(dac_periph) |= (uint32_t)DAC_SWT_SWTR0;
    }else{
        DAC_SWT(dac_periph) |= (uint32_t)DAC_SWT_SWTR1;
    }
}

/*!
    \brief      disable DAC software trigger
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_software_trigger_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_SWT(dac_periph) &= (uint32_t)(~DAC_SWT_SWTR0);
    }else{
        DAC_SWT(dac_periph) &= (uint32_t)(~DAC_SWT_SWTR1);
    }
}

/*!
    \brief      configure DAC wave mode
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[in]  wave_mode: DAC wave mode
                only one parameter can be selected which is shown as below:
      \arg        DAC_WAVE_DISABLE: wave mode disable
      \arg        DAC_WAVE_MODE_LFSR: LFSR noise mode
      \arg        DAC_WAVE_MODE_TRIANGLE: triangle noise mode
    \param[out] none
    \retval     none
*/
void dac_wave_mode_config(uint32_t dac_periph, uint8_t dac_out, uint32_t wave_mode)
{
    if(DAC_OUT_0 == dac_out){
        /* configure DAC_OUT0 wave mode */
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DWM0);
        DAC_CTL(dac_periph) |= wave_mode;
    }else{
        /* configure DAC_OUT1 wave mode */
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DWM1);
        DAC_CTL(dac_periph) |= (wave_mode << OUT1_REG_OFFSET);
    }
}

/*!
    \brief      configure DAC wave bit width
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[in]  bit_width: DAC noise wave bit width
                only one parameter can be selected which is shown as below:
      \arg        DAC_WAVE_BIT_WIDTH_1: bit width of the wave signal is 1
      \arg        DAC_WAVE_BIT_WIDTH_2: bit width of the wave signal is 2
      \arg        DAC_WAVE_BIT_WIDTH_3: bit width of the wave signal is 3
      \arg        DAC_WAVE_BIT_WIDTH_4: bit width of the wave signal is 4
      \arg        DAC_WAVE_BIT_WIDTH_5: bit width of the wave signal is 5
      \arg        DAC_WAVE_BIT_WIDTH_6: bit width of the wave signal is 6
      \arg        DAC_WAVE_BIT_WIDTH_7: bit width of the wave signal is 7
      \arg        DAC_WAVE_BIT_WIDTH_8: bit width of the wave signal is 8
      \arg        DAC_WAVE_BIT_WIDTH_9: bit width of the wave signal is 9
      \arg        DAC_WAVE_BIT_WIDTH_10: bit width of the wave signal is 10
      \arg        DAC_WAVE_BIT_WIDTH_11: bit width of the wave signal is 11
      \arg        DAC_WAVE_BIT_WIDTH_12: bit width of the wave signal is 12
    \param[out] none
    \retval     none
*/
void dac_wave_bit_width_config(uint32_t dac_periph, uint8_t dac_out, uint32_t bit_width)
{
    if(DAC_OUT_0 == dac_out){
        /* configure DAC_OUT0 wave bit width */
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DWBW0);
        DAC_CTL(dac_periph) |= bit_width;
    }else{
        /* configure DAC_OUT1 wave bit width */
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DWBW1);
        DAC_CTL(dac_periph) |= (bit_width << OUT1_REG_OFFSET);
    }
}

/*!
    \brief      configure DAC LFSR noise mode
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[in]  unmask_bits: LFSR noise unmask bits
                only one parameter can be selected which is shown as below:
      \arg        DAC_LFSR_BIT0: unmask the LFSR bit0
      \arg        DAC_LFSR_BITS1_0: unmask the LFSR bits[1:0]
      \arg        DAC_LFSR_BITS2_0: unmask the LFSR bits[2:0]
      \arg        DAC_LFSR_BITS3_0: unmask the LFSR bits[3:0]
      \arg        DAC_LFSR_BITS4_0: unmask the LFSR bits[4:0]
      \arg        DAC_LFSR_BITS5_0: unmask the LFSR bits[5:0]
      \arg        DAC_LFSR_BITS6_0: unmask the LFSR bits[6:0]
      \arg        DAC_LFSR_BITS7_0: unmask the LFSR bits[7:0]
      \arg        DAC_LFSR_BITS8_0: unmask the LFSR bits[8:0]
      \arg        DAC_LFSR_BITS9_0: unmask the LFSR bits[9:0]
      \arg        DAC_LFSR_BITS10_0: unmask the LFSR bits[10:0]
      \arg        DAC_LFSR_BITS11_0: unmask the LFSR bits[11:0]
    \param[out] none
    \retval     none
*/
void dac_lfsr_noise_config(uint32_t dac_periph, uint8_t dac_out, uint32_t unmask_bits)
{
    if(DAC_OUT_0 == dac_out){
        /* configure DAC_OUT0 LFSR noise mode */
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DWBW0);
        DAC_CTL(dac_periph) |= unmask_bits;
    }else{
        /* configure DAC_OUT1 LFSR noise mode */
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DWBW1);
        DAC_CTL(dac_periph) |= (unmask_bits << OUT1_REG_OFFSET);
    }
}

/*!
    \brief      configure DAC triangle noise mode
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[in]  amplitude: the amplitude of the triangle
                only one parameter can be selected which is shown as below:
      \arg        DAC_TRIANGLE_AMPLITUDE_1: triangle amplitude is 1
      \arg        DAC_TRIANGLE_AMPLITUDE_3: triangle amplitude is 3
      \arg        DAC_TRIANGLE_AMPLITUDE_7: triangle amplitude is 7
      \arg        DAC_TRIANGLE_AMPLITUDE_15: triangle amplitude is 15
      \arg        DAC_TRIANGLE_AMPLITUDE_31: triangle amplitude is 31
      \arg        DAC_TRIANGLE_AMPLITUDE_63: triangle amplitude is 63
      \arg        DAC_TRIANGLE_AMPLITUDE_127: triangle amplitude is 127
      \arg        DAC_TRIANGLE_AMPLITUDE_255: triangle amplitude is 255
      \arg        DAC_TRIANGLE_AMPLITUDE_511: triangle amplitude is 511
      \arg        DAC_TRIANGLE_AMPLITUDE_1023: triangle amplitude is 1023
      \arg        DAC_TRIANGLE_AMPLITUDE_2047: triangle amplitude is 2047
      \arg        DAC_TRIANGLE_AMPLITUDE_4095: triangle amplitude is 4095
    \param[out] none
    \retval     none
*/
void dac_triangle_noise_config(uint32_t dac_periph, uint8_t dac_out, uint32_t amplitude)
{
    if(DAC_OUT_0 == dac_out){
        /* configure DAC_OUT0 triangle noise mode */
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DWBW0);
        DAC_CTL(dac_periph) |= amplitude;
    }else{
        /* configure DAC_OUT1 triangle noise mode */
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DWBW1);
        DAC_CTL(dac_periph) |= (amplitude << OUT1_REG_OFFSET);
    }
}

/*!
    \brief      configure DAC output buffer gain
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[in]  buffer_gain: DAC_OUT output buffer gain
                only one parameter can be selected which is shown as below:
      \arg        DAC_OUT_GAIN_1: DAC_OUT output buffer gain is 1
      \arg        DAC_OUT_GAIN_2: DAC_OUT output buffer gain is 2
    \param[out] none
    \retval     none
*/
void dac_buffer_gain_config(uint32_t dac_periph, uint8_t dac_out, uint32_t buffer_gain)
{
    if(DAC_OUT_0 == dac_out){
        /* configure DAC_OUT0 triangle noise mode */
        DAC_OCTL(dac_periph) &= (uint32_t)(~DAC_OCTL_GS0);
        DAC_OCTL(dac_periph) |= buffer_gain;
    }else{
        /* configure DAC_OUT1 triangle noise mode */
        DAC_OCTL(dac_periph) &= (uint32_t)(~DAC_OCTL_GS1);
        DAC_OCTL(dac_periph) |= (buffer_gain << OUT1_REG_OFFSET);
    }
}

/*!
    \brief      enable DAC concurrent mode
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void dac_concurrent_enable(uint32_t dac_periph)
{
    uint32_t ctl = 0U;
    ctl = (uint32_t)(DAC_CTL_DEN0 | DAC_CTL_DEN1);
    DAC_CTL(dac_periph) |= (uint32_t)ctl;
}

/*!
    \brief      disable DAC concurrent mode
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void dac_concurrent_disable(uint32_t dac_periph)
{
    uint32_t ctl = 0U;
    ctl = (uint32_t)(DAC_CTL_DEN0 | DAC_CTL_DEN1);
    DAC_CTL(dac_periph) &= (uint32_t)(~ctl);
}

/*!
    \brief      enable DAC concurrent software trigger
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void dac_concurrent_software_trigger_enable(uint32_t dac_periph)
{
    uint32_t swt = 0U;
    swt = (uint32_t)(DAC_SWT_SWTR0 | DAC_SWT_SWTR1);
    DAC_SWT(dac_periph) |= (uint32_t)swt; 
}

/*!
    \brief      disable DAC concurrent software trigger
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void dac_concurrent_software_trigger_disable(uint32_t dac_periph)
{
    uint32_t swt = 0U;
    swt = (uint32_t)(DAC_SWT_SWTR0 | DAC_SWT_SWTR1);
    DAC_SWT(dac_periph) &= (uint32_t)(~swt);
}

/*!
    \brief      enable DAC concurrent buffer function
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void dac_concurrent_output_buffer_enable(uint32_t dac_periph)
{
    uint32_t ctl = 0U;
    ctl = (uint32_t)(DAC_CTL_DBOFF0 | DAC_CTL_DBOFF1);
    DAC_CTL(dac_periph) &= (uint32_t)(~ctl);
}

/*!
    \brief      disable DAC concurrent buffer function
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void dac_concurrent_output_buffer_disable(uint32_t dac_periph)
{
    uint32_t ctl = 0U;
    ctl = (uint32_t)(DAC_CTL_DBOFF0 | DAC_CTL_DBOFF1);
    DAC_CTL(dac_periph) |= (uint32_t)ctl;
}

/*!
    \brief      set DAC concurrent mode data holding register value
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_align: DAC data alignment mode
                only one parameter can be selected which is shown as below:
      \arg        DAC_ALIGN_12B_R: 12-bit right-aligned data
      \arg        DAC_ALIGN_12B_L: 12-bit left-aligned data
      \arg        DAC_ALIGN_8B_R: 8-bit right-aligned data
    \param[in]  data0: data to be loaded(0~4095)
    \param[in]  data1: data to be loaded(0~4095)
    \param[out] none
    \retval     none
*/
void dac_concurrent_data_set(uint32_t dac_periph, uint32_t dac_align, uint16_t data0, uint16_t data1)
{
    uint32_t data = 0U;
    switch(dac_align){
    /* 12-bit right-aligned data */
    case DAC_ALIGN_12B_R:
        data = (uint32_t)(((uint32_t)data1 << DH_12BIT_OFFSET) | data0);
        DACC_R12DH(dac_periph) = (uint32_t)data;
        break;
    /* 12-bit left-aligned data */
    case DAC_ALIGN_12B_L:
        data = (uint32_t)(((uint32_t)data1 << DH_12BIT_OFFSET) | data0);
        DACC_L12DH(dac_periph) = (uint32_t)data;
        break;
    /* 8-bit right-aligned data */
    case DAC_ALIGN_8B_R:
        data = (uint32_t)(((uint32_t)data1 << DH_8BIT_OFFSET) | data0);
        DACC_R8DH(dac_periph) = (uint32_t)data;
        break;
    default:
        break;
    }
}

/*!
    \brief      get the specified DAC flag(DAC DMA underrun flag)
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     the state of DAC bit(SET or RESET)
*/
FlagStatus dac_flag_get(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
       /* check DAC_OUT0 DMA underrun flag */
       if((uint8_t)RESET != (DAC_STAT(dac_periph) & DAC_STAT_DDUDR0)){
           return SET;
       }else{
           return RESET;
       }
    }else{
       /* check DAC_OUT1 DMA underrun flag */
       if((uint8_t)RESET != (DAC_STAT(dac_periph) & DAC_STAT_DDUDR1)){
           return SET;
       }else{
           return RESET;
       }
    }
}

/*!
    \brief      clear the specified DAC flag(DAC DMA underrun flag)
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_flag_clear(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_STAT(dac_periph) |= (uint32_t)DAC_STAT_DDUDR0;
    }else{
        DAC_STAT(dac_periph) |= (uint32_t)DAC_STAT_DDUDR1;
    }
}

/*!
    \brief      enable DAC interrupt(DAC DMA underrun interrupt)
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_interrupt_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DDUDRIE0;
    }else{
        DAC_CTL(dac_periph) |= (uint32_t)DAC_CTL_DDUDRIE1;
    }
}

/*!
    \brief      disable DAC interrupt(DAC DMA underrun interrupt)
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_interrupt_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DDUDRIE0);
    }else{
        DAC_CTL(dac_periph) &= (uint32_t)(~DAC_CTL_DDUDRIE1);
    }
}

/*!
    \brief      get the specified DAC interrupt flag(DAC DMA underrun interrupt flag)
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     the state of DAC interrupt flag(SET or RESET)
*/
FlagStatus dac_interrupt_flag_get(uint32_t dac_periph, uint8_t dac_out)
{
    uint32_t ddudr_flag = 0U, ddudrie_flag = 0U;
    /* check the DMA underrun flag and DAC DMA underrun interrupt enable flag */
    if(DAC_OUT_0 == dac_out){
        ddudr_flag = DAC_STAT(dac_periph) & DAC_STAT_DDUDR0;
        ddudrie_flag = DAC_CTL(dac_periph) & DAC_CTL_DDUDRIE0;
    }else{
        ddudr_flag = DAC_STAT(dac_periph) & DAC_STAT_DDUDR1;
        ddudrie_flag = DAC_CTL(dac_periph) & DAC_CTL_DDUDRIE1;
    }
    /*get DAC underrun interrupt flag status */
    if((RESET != ddudr_flag) && (RESET != ddudrie_flag)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear the specified DAC interrupt flag(DAC DMA underrun interrupt flag)
    \param[in]  dac_periph: DACx(x=0,1,2,3)
    \param[in]  dac_out: DAC_OUT_x(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_interrupt_flag_clear(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT_0 == dac_out){
        DAC_STAT(dac_periph) |= (uint32_t)DAC_STAT_DDUDR0;
    }else{
        DAC_STAT(dac_periph) |= (uint32_t)DAC_STAT_DDUDR1;
    }
}

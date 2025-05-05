;/*!
;    \file    startup_gd32e501.s
;    \brief   start up file
;
;    \version 2020-03-02, V1.0.0, firmware for GD32E501
;    \version 2020-04-10, V1.0.1, firmware for GD32E501
;    \version 2020-08-25, V1.0.2, firmware for GD32E501
;*/
;
;/*
;    Copyright (c) 2020, GigaDevice Semiconductor Inc.
;
;    Redistribution and use in source and binary forms, with or without modification, 
;are permitted provided that the following conditions are met:
;
;    1. Redistributions of source code must retain the above copyright notice, this 
;       list of conditions and the following disclaimer.
;    2. Redistributions in binary form must reproduce the above copyright notice, 
;       this list of conditions and the following disclaimer in the documentation 
;       and/or other materials provided with the distribution.
;    3. Neither the name of the copyright holder nor the names of its contributors 
;       may be used to endorse or promote products derived from this software without 
;       specific prior written permission.
;
;    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
;AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
;WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
;IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
;INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
;NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
;PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
;WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
;ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
;OF SUCH DAMAGE.
;*/

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)                         ; top of stack
        DCD     Reset_Handler                       ; Vector Number 1,Reset Handler

        DCD     NMI_Handler                         ; Vector Number 2,NMI Handler
        DCD     HardFault_Handler                   ; Vector Number 3,Hard Fault Handler
        DCD     MemManage_Handler                   ; Vector Number 4,MPU Fault Handler
        DCD     BusFault_Handler                    ; Vector Number 5,Bus Fault Handler
        DCD     UsageFault_Handler                  ; Vector Number 6,Usage Fault Handler
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     SVC_Handler                         ; Vector Number 11,SVCall Handler
        DCD     DebugMon_Handler                    ; Vector Number 12,Debug Monitor Handler
        DCD     0                                   ; Reserved
        DCD     PendSV_Handler                      ; Vector Number 14,PendSV Handler
        DCD     SysTick_Handler                     ; Vector Number 15,SysTick Handler

        ; External Interrupts
        DCD     WWDGT_IRQHandler                    ; 16:Window Watchdog Timer
        DCD     LVD_IRQHandler                      ; 17:LVD through EXTI Line detect
        DCD     RTC_IRQHandler                      ; 18:RTC through EXTI Line
        DCD     FMC_IRQHandler                      ; 19:FMC
        DCD     RCU_IRQHandler                      ; 20:RCU
        DCD     EXTI0_1_IRQHandler                  ; 21:EXTI Line 0 and EXTI Line 1
        DCD     EXTI2_3_IRQHandler                  ; 22:EXTI Line 2 and EXTI Line 3
        DCD     EXTI4_15_IRQHandler                 ; 23:EXTI Line 4 to EXTI Line 15
        DCD     0                                   ; Reserved
        DCD     DMA_Channel0_IRQHandler             ; 25:DMA Channel 0 
        DCD     DMA_Channel1_2_IRQHandler           ; 26:DMA Channel 1 and DMA Channel 2
        DCD     DMA_Channel3_4_IRQHandler           ; 27:DMA Channel 3 and DMA Channel 4
        DCD     ADC_CMP_IRQHandler                  ; 28:ADC and Comparator
        DCD     TIMER0_BRK_UP_TRG_COM_IRQHandler    ; 29:TIMER0 Break,Update,Trigger and Commutation
        DCD     TIMER0_Channel_IRQHandler           ; 30:TIMER0 Channel Capture Compare
        DCD     TIMER1_IRQHandler                   ; 31:TIMER1
        DCD     TIMER2_IRQHandler                   ; 32:TIMER2
        DCD     TIMER5_DAC0_1_IRQHandler            ; 33:TIMER5 and DAC0, DAC1
        DCD     TIMER6_DAC2_3_IRQHandler            ; 34:TIMER6 and DAC2, DAC3
        DCD     TIMER13_IRQHandler                  ; 35:TIMER13
        DCD     TIMER14_IRQHandler                  ; 36:TIMER14
        DCD     TIMER15_IRQHandler                  ; 37:TIMER15
        DCD     TIMER16_IRQHandler                  ; 38:TIMER16
        DCD     I2C0_EV_IRQHandler                  ; 39:I2C0 Event
        DCD     I2C1_EV_IRQHandler                  ; 40:I2C1 Event
        DCD     SPI0_IRQHandler                     ; 41:SPI0
        DCD     SPI1_IRQHandler                     ; 42:SPI1
        DCD     USART0_IRQHandler                   ; 43:USART0
        DCD     USART1_IRQHandler                   ; 44:USART1
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     I2C0_ER_IRQHandler                  ; 48:I2C0 Error
        DCD     0                                   ; Reserved
        DCD     I2C1_ER_IRQHandler                  ; 50:I2C1 Error
        DCD     I2C2_EV_IRQHandler                  ; 51:I2C2 Event
        DCD     I2C2_ER_IRQHandler                  ; 52:I2C2 Error
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     CLA_IRQHandler                      ; 55:CLA
        DCD     MDIO_IRQHandler                     ; 56:MDIO
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     DMA_Channel5_6_IRQHandler           ; 64:DMA Channel 5 and DMA Channel 6
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     SPI2_IRQHandler                     ; 67:SPI2
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     FPU_IRQHandler                      ; 84:FPU


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0
        
        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler
       
        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler
        
        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler
               
        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler
        
        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler
        
        PUBWEAK WWDGT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDGT_IRQHandler
        B WWDGT_IRQHandler
        
        PUBWEAK LVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LVD_IRQHandler
        B LVD_IRQHandler
        
        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler
        
        PUBWEAK FMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMC_IRQHandler
        B FMC_IRQHandler
        
        PUBWEAK RCU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCU_IRQHandler
        B RCU_IRQHandler
        
        PUBWEAK EXTI0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_1_IRQHandler
        B EXTI0_1_IRQHandler
        
        PUBWEAK EXTI2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_3_IRQHandler
        B EXTI2_3_IRQHandler
        
        PUBWEAK EXTI4_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_15_IRQHandler
        B EXTI4_15_IRQHandler
        
        PUBWEAK DMA_Channel0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_Channel0_IRQHandler
        B DMA_Channel0_IRQHandler
        
        PUBWEAK DMA_Channel1_2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_Channel1_2_IRQHandler
        B DMA_Channel1_2_IRQHandler
        
        PUBWEAK DMA_Channel3_4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_Channel3_4_IRQHandler
        B DMA_Channel3_4_IRQHandler
        
        PUBWEAK ADC_CMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_CMP_IRQHandler
        B ADC_CMP_IRQHandler
        
        PUBWEAK TIMER0_BRK_UP_TRG_COM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_BRK_UP_TRG_COM_IRQHandler
        B TIMER0_BRK_UP_TRG_COM_IRQHandler

        PUBWEAK TIMER0_Channel_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_Channel_IRQHandler
        B TIMER0_Channel_IRQHandler
        
        PUBWEAK TIMER1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER1_IRQHandler
        B TIMER1_IRQHandler
      
        PUBWEAK TIMER2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER2_IRQHandler
        B TIMER2_IRQHandler
      
        PUBWEAK TIMER5_DAC0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER5_DAC0_1_IRQHandler
        B TIMER5_DAC0_1_IRQHandler

        PUBWEAK TIMER6_DAC2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER6_DAC2_3_IRQHandler
        B TIMER6_DAC2_3_IRQHandler
        
        PUBWEAK TIMER13_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER13_IRQHandler
        B TIMER13_IRQHandler
        
        PUBWEAK TIMER14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER14_IRQHandler    
        B TIMER14_IRQHandler

        PUBWEAK TIMER15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER15_IRQHandler
        B TIMER15_IRQHandler

        PUBWEAK TIMER16_IRQHandler 
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER16_IRQHandler 
        B TIMER16_IRQHandler 
        
        PUBWEAK I2C0_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_EV_IRQHandler
        B I2C0_EV_IRQHandler
        
        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler
        
        PUBWEAK SPI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_IRQHandler
        B SPI0_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK USART0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART0_IRQHandler
        B USART0_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler
        
        PUBWEAK I2C0_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_ER_IRQHandler
        B I2C0_ER_IRQHandler

        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_ER_IRQHandler             
        B I2C1_ER_IRQHandler

        PUBWEAK I2C2_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_EV_IRQHandler
        B I2C2_EV_IRQHandler

        PUBWEAK I2C2_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_ER_IRQHandler
        B I2C2_ER_IRQHandler

        PUBWEAK CLA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CLA_IRQHandler
        B CLA_IRQHandler

        PUBWEAK MDIO_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MDIO_IRQHandler
        B MDIO_IRQHandler

        PUBWEAK DMA_Channel5_6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_Channel5_6_IRQHandler
        B DMA_Channel5_6_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FPU_IRQHandler
        B FPU_IRQHandler

        END
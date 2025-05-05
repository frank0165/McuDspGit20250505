# 1 "../../thd_dsp_download_release_V0_0/mailbox_i2c_interface.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 389 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "../../thd_dsp_download_release_V0_0/mailbox_i2c_interface.c" 2

# 1 "../../thd_dsp_download_release_V0_0/mailbox_i2c_interface.h" 1
# 16 "../../thd_dsp_download_release_V0_0/mailbox_i2c_interface.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 106 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h"
typedef enum IRQn
{

    NonMaskableInt_IRQn = -14,
    HardFault_IRQn = -13,
    MemoryManagement_IRQn = -12,
    BusFault_IRQn = -11,
    UsageFault_IRQn = -10,
    SVCall_IRQn = -5,
    DebugMonitor_IRQn = -4,
    PendSV_IRQn = -2,
    SysTick_IRQn = -1,

    WWDGT_IRQn = 0,
    LVD_IRQn = 1,
    RTC_IRQn = 2,
    FMC_IRQn = 3,
    RCU_IRQn = 4,
    EXTI0_1_IRQn = 5,
    EXTI2_3_IRQn = 6,
    EXTI4_15_IRQn = 7,
    DMA_Channel0_IRQn = 9,
    DMA_Channel1_2_IRQn = 10,
    DMA_Channel3_4_IRQn = 11,
    ADC_CMP_IRQn = 12,
    TIMER0_BRK_UP_TRG_COM_IRQn = 13,
    TIMER0_Channel_IRQn = 14,
    TIMER1_IRQn = 15,
    TIMER2_IRQn = 16,
    TIMER5_DAC0_1_IRQn = 17,
    TIMER6_DAC2_3_IRQn = 18,
    TIMER13_IRQn = 19,
    TIMER14_IRQn = 20,
    TIMER15_IRQn = 21,
    TIMER16_IRQn = 22,
    I2C0_EV_IRQn = 23,
    I2C1_EV_IRQn = 24,
    SPI0_IRQn = 25,
    SPI1_IRQn = 26,
    USART0_IRQn = 27,
    USART1_IRQn = 28,
    I2C0_ER_IRQn = 32,
    I2C1_ER_IRQn = 34,
    I2C2_EV_IRQn = 35,
    I2C2_ER_IRQn = 36,
    CLA_IRQn = 39,
    MDIO_IRQn = 40,
    DMA_Channel5_6_IRQn = 48,
    SPI2_IRQn = 51,
    FPU_IRQn = 68
} IRQn_Type;


# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 1
# 29 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3





# 1 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 1 3
# 56 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 3
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int int64_t;


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;





typedef signed char int_least8_t;
typedef signed short int int_least16_t;
typedef signed int int_least32_t;
typedef signed long long int int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long int uint_least64_t;




typedef signed int int_fast8_t;
typedef signed int int_fast16_t;
typedef signed int int_fast32_t;
typedef signed long long int int_fast64_t;


typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long int uint_fast64_t;






typedef signed int intptr_t;
typedef unsigned int uintptr_t;



typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
# 35 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 2 3
# 63 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/cmsis_version.h" 1 3
# 29 "../../mcu/GDE501_fireware/Firmware/CMSIS/cmsis_version.h" 3
# 64 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 2 3
# 206 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/cmsis_compiler.h" 1 3
# 47 "../../mcu/GDE501_fireware/Firmware/CMSIS/cmsis_compiler.h" 3
# 1 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 1 3
# 31 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
# 64 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

  struct __attribute__((packed)) T_UINT32 { uint32_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

  struct __attribute__((packed, aligned(1))) T_UINT16_WRITE { uint16_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

  struct __attribute__((packed, aligned(1))) T_UINT16_READ { uint16_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

  struct __attribute__((packed, aligned(1))) T_UINT32_WRITE { uint32_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

  struct __attribute__((packed, aligned(1))) T_UINT32_READ { uint32_t v; };
#pragma clang diagnostic pop
# 260 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U)
  {
    return op1;
  }
  return (op1 >> op2) | (op1 << (32U - op2));
}
# 295 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint8_t __CLZ(uint32_t value)
{
# 306 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
  if (value == 0U)
  {
    return 32U;
  }
  return __builtin_clz(value);
}
# 425 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __RRX(uint32_t value)
{
  uint32_t result;

  __asm volatile ("rrx %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}
# 440 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint8_t __LDRBT(volatile uint8_t *ptr)
{
  uint32_t result;

  __asm volatile ("ldrbt %0, %1" : "=r" (result) : "Q" (*ptr) );
  return ((uint8_t) result);
}
# 455 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint16_t __LDRHT(volatile uint16_t *ptr)
{
  uint32_t result;

  __asm volatile ("ldrht %0, %1" : "=r" (result) : "Q" (*ptr) );
  return ((uint16_t) result);
}
# 470 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __LDRT(volatile uint32_t *ptr)
{
  uint32_t result;

  __asm volatile ("ldrt %0, %1" : "=r" (result) : "Q" (*ptr) );
  return(result);
}
# 485 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __STRBT(uint8_t value, volatile uint8_t *ptr)
{
  __asm volatile ("strbt %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) );
}
# 497 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __STRHT(uint16_t value, volatile uint16_t *ptr)
{
  __asm volatile ("strht %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) );
}
# 509 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __STRT(uint32_t value, volatile uint32_t *ptr)
{
  __asm volatile ("strt %1, %0" : "=Q" (*ptr) : "r" (value) );
}
# 584 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint8_t __LDAB(volatile uint8_t *ptr)
{
  uint32_t result;

  __asm volatile ("ldab %0, %1" : "=r" (result) : "Q" (*ptr) : "memory" );
  return ((uint8_t) result);
}
# 599 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint16_t __LDAH(volatile uint16_t *ptr)
{
  uint32_t result;

  __asm volatile ("ldah %0, %1" : "=r" (result) : "Q" (*ptr) : "memory" );
  return ((uint16_t) result);
}
# 614 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __LDA(volatile uint32_t *ptr)
{
  uint32_t result;

  __asm volatile ("lda %0, %1" : "=r" (result) : "Q" (*ptr) : "memory" );
  return(result);
}
# 629 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __STLB(uint8_t value, volatile uint8_t *ptr)
{
  __asm volatile ("stlb %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) : "memory" );
}
# 641 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __STLH(uint16_t value, volatile uint16_t *ptr)
{
  __asm volatile ("stlh %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) : "memory" );
}
# 653 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __STL(uint32_t value, volatile uint32_t *ptr)
{
  __asm volatile ("stl %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) : "memory" );
}
# 737 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}
# 750 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}
# 762 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_CONTROL(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}
# 792 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_CONTROL(uint32_t control)
{
  __asm volatile ("MSR control, %0" : : "r" (control) : "memory");
  __builtin_arm_isb(0xF);
}
# 818 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_IPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static __inline uint32_t __get_APSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static __inline uint32_t __get_xPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static __inline uint32_t __get_PSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, psp" : "=r" (result) );
  return(result);
}
# 890 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_PSP(uint32_t topOfProcStack)
{
  __asm volatile ("MSR psp, %0" : : "r" (topOfProcStack) : );
}
# 914 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_MSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, msp" : "=r" (result) );
  return(result);
}
# 944 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}
# 995 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_PRIMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}
# 1025 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_PRIMASK(uint32_t priMask)
{
  __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}
# 1053 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __enable_fault_irq(void)
{
  __asm volatile ("cpsie f" : : : "memory");
}







__attribute__((always_inline)) static __inline void __disable_fault_irq(void)
{
  __asm volatile ("cpsid f" : : : "memory");
}







__attribute__((always_inline)) static __inline uint32_t __get_BASEPRI(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, basepri" : "=r" (result) );
  return(result);
}
# 1105 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_BASEPRI(uint32_t basePri)
{
  __asm volatile ("MSR basepri, %0" : : "r" (basePri) : "memory");
}
# 1130 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_BASEPRI_MAX(uint32_t basePri)
{
  __asm volatile ("MSR basepri_max, %0" : : "r" (basePri) : "memory");
}







__attribute__((always_inline)) static __inline uint32_t __get_FAULTMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, faultmask" : "=r" (result) );
  return(result);
}
# 1171 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  __asm volatile ("MSR faultmask, %0" : : "r" (faultMask) : "memory");
}
# 1208 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_PSPLIM(void)
{






  uint32_t result;
  __asm volatile ("MRS %0, psplim" : "=r" (result) );
  return result;

}
# 1256 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_PSPLIM(uint32_t ProcStackPtrLimit)
{






  __asm volatile ("MSR psplim, %0" : : "r" (ProcStackPtrLimit));

}
# 1300 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_MSPLIM(void)
{






  uint32_t result;
  __asm volatile ("MRS %0, msplim" : "=r" (result) );
  return result;

}
# 1347 "D:/D/app/kevil5/ARM/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_MSPLIM(uint32_t MainStackPtrLimit)
{






  __asm volatile ("MSR msplim, %0" : : "r" (MainStackPtrLimit));

}
# 48 "../../mcu/GDE501_fireware/Firmware/CMSIS/cmsis_compiler.h" 2 3
# 207 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 2 3
# 314 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef union
{
  struct
  {
    uint32_t _reserved0:16;
    uint32_t GE:4;
    uint32_t _reserved1:7;
    uint32_t Q:1;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} APSR_Type;
# 353 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:23;
  } b;
  uint32_t w;
} IPSR_Type;
# 371 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:7;
    uint32_t GE:4;
    uint32_t _reserved1:4;
    uint32_t T:1;
    uint32_t IT:2;
    uint32_t Q:1;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} xPSR_Type;
# 422 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef union
{
  struct
  {
    uint32_t nPRIV:1;
    uint32_t SPSEL:1;
    uint32_t FPCA:1;
    uint32_t SFPA:1;
    uint32_t _reserved1:28;
  } b;
  uint32_t w;
} CONTROL_Type;
# 461 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef struct
{
  volatile uint32_t ISER[16U];
        uint32_t RESERVED0[16U];
  volatile uint32_t ICER[16U];
        uint32_t RSERVED1[16U];
  volatile uint32_t ISPR[16U];
        uint32_t RESERVED2[16U];
  volatile uint32_t ICPR[16U];
        uint32_t RESERVED3[16U];
  volatile uint32_t IABR[16U];
        uint32_t RESERVED4[16U];
  volatile uint32_t ITNS[16U];
        uint32_t RESERVED5[16U];
  volatile uint8_t IPR[496U];
        uint32_t RESERVED6[580U];
  volatile uint32_t STIR;
} NVIC_Type;
# 497 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef struct
{
  volatile const uint32_t CPUID;
  volatile uint32_t ICSR;
  volatile uint32_t VTOR;
  volatile uint32_t AIRCR;
  volatile uint32_t SCR;
  volatile uint32_t CCR;
  volatile uint8_t SHPR[12U];
  volatile uint32_t SHCSR;
  volatile uint32_t CFSR;
  volatile uint32_t HFSR;
  volatile uint32_t DFSR;
  volatile uint32_t MMFAR;
  volatile uint32_t BFAR;
  volatile uint32_t AFSR;
  volatile const uint32_t ID_PFR[2U];
  volatile const uint32_t ID_DFR;
  volatile const uint32_t ID_ADR;
  volatile const uint32_t ID_MMFR[4U];
  volatile const uint32_t ID_ISAR[6U];
  volatile const uint32_t CLIDR;
  volatile const uint32_t CTR;
  volatile const uint32_t CCSIDR;
  volatile uint32_t CSSELR;
  volatile uint32_t CPACR;
  volatile uint32_t NSACR;
        uint32_t RESERVED3[92U];
  volatile uint32_t STIR;
        uint32_t RESERVED4[15U];
  volatile const uint32_t MVFR0;
  volatile const uint32_t MVFR1;
  volatile const uint32_t MVFR2;
        uint32_t RESERVED5[1U];
  volatile uint32_t ICIALLU;
        uint32_t RESERVED6[1U];
  volatile uint32_t ICIMVAU;
  volatile uint32_t DCIMVAC;
  volatile uint32_t DCISW;
  volatile uint32_t DCCMVAU;
  volatile uint32_t DCCMVAC;
  volatile uint32_t DCCSW;
  volatile uint32_t DCCIMVAC;
  volatile uint32_t DCCISW;
} SCB_Type;
# 929 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile const uint32_t ICTR;
  volatile uint32_t ACTLR;
  volatile uint32_t CPPWR;
} SCnSCB_Type;
# 954 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile const uint32_t CALIB;
} SysTick_Type;
# 1006 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef struct
{
  volatile union
  {
    volatile uint8_t u8;
    volatile uint16_t u16;
    volatile uint32_t u32;
  } PORT [32U];
        uint32_t RESERVED0[864U];
  volatile uint32_t TER;
        uint32_t RESERVED1[15U];
  volatile uint32_t TPR;
        uint32_t RESERVED2[15U];
  volatile uint32_t TCR;
        uint32_t RESERVED3[32U];
        uint32_t RESERVED4[43U];
  volatile uint32_t LAR;
  volatile const uint32_t LSR;
        uint32_t RESERVED5[1U];
  volatile const uint32_t DEVARCH;
        uint32_t RESERVED6[4U];
  volatile const uint32_t PID4;
  volatile const uint32_t PID5;
  volatile const uint32_t PID6;
  volatile const uint32_t PID7;
  volatile const uint32_t PID0;
  volatile const uint32_t PID1;
  volatile const uint32_t PID2;
  volatile const uint32_t PID3;
  volatile const uint32_t CID0;
  volatile const uint32_t CID1;
  volatile const uint32_t CID2;
  volatile const uint32_t CID3;
} ITM_Type;
# 1106 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t CYCCNT;
  volatile uint32_t CPICNT;
  volatile uint32_t EXCCNT;
  volatile uint32_t SLEEPCNT;
  volatile uint32_t LSUCNT;
  volatile uint32_t FOLDCNT;
  volatile const uint32_t PCSR;
  volatile uint32_t COMP0;
        uint32_t RESERVED1[1U];
  volatile uint32_t FUNCTION0;
        uint32_t RESERVED2[1U];
  volatile uint32_t COMP1;
        uint32_t RESERVED3[1U];
  volatile uint32_t FUNCTION1;
        uint32_t RESERVED4[1U];
  volatile uint32_t COMP2;
        uint32_t RESERVED5[1U];
  volatile uint32_t FUNCTION2;
        uint32_t RESERVED6[1U];
  volatile uint32_t COMP3;
        uint32_t RESERVED7[1U];
  volatile uint32_t FUNCTION3;
        uint32_t RESERVED8[1U];
  volatile uint32_t COMP4;
        uint32_t RESERVED9[1U];
  volatile uint32_t FUNCTION4;
        uint32_t RESERVED10[1U];
  volatile uint32_t COMP5;
        uint32_t RESERVED11[1U];
  volatile uint32_t FUNCTION5;
        uint32_t RESERVED12[1U];
  volatile uint32_t COMP6;
        uint32_t RESERVED13[1U];
  volatile uint32_t FUNCTION6;
        uint32_t RESERVED14[1U];
  volatile uint32_t COMP7;
        uint32_t RESERVED15[1U];
  volatile uint32_t FUNCTION7;
        uint32_t RESERVED16[1U];
  volatile uint32_t COMP8;
        uint32_t RESERVED17[1U];
  volatile uint32_t FUNCTION8;
        uint32_t RESERVED18[1U];
  volatile uint32_t COMP9;
        uint32_t RESERVED19[1U];
  volatile uint32_t FUNCTION9;
        uint32_t RESERVED20[1U];
  volatile uint32_t COMP10;
        uint32_t RESERVED21[1U];
  volatile uint32_t FUNCTION10;
        uint32_t RESERVED22[1U];
  volatile uint32_t COMP11;
        uint32_t RESERVED23[1U];
  volatile uint32_t FUNCTION11;
        uint32_t RESERVED24[1U];
  volatile uint32_t COMP12;
        uint32_t RESERVED25[1U];
  volatile uint32_t FUNCTION12;
        uint32_t RESERVED26[1U];
  volatile uint32_t COMP13;
        uint32_t RESERVED27[1U];
  volatile uint32_t FUNCTION13;
        uint32_t RESERVED28[1U];
  volatile uint32_t COMP14;
        uint32_t RESERVED29[1U];
  volatile uint32_t FUNCTION14;
        uint32_t RESERVED30[1U];
  volatile uint32_t COMP15;
        uint32_t RESERVED31[1U];
  volatile uint32_t FUNCTION15;
        uint32_t RESERVED32[934U];
  volatile const uint32_t LSR;
        uint32_t RESERVED33[1U];
  volatile const uint32_t DEVARCH;
} DWT_Type;
# 1292 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef struct
{
  volatile const uint32_t SSPSR;
  volatile uint32_t CSPSR;
        uint32_t RESERVED0[2U];
  volatile uint32_t ACPR;
        uint32_t RESERVED1[55U];
  volatile uint32_t SPPR;
        uint32_t RESERVED2[131U];
  volatile const uint32_t FFSR;
  volatile uint32_t FFCR;
  volatile uint32_t PSCR;
        uint32_t RESERVED3[759U];
  volatile const uint32_t TRIGGER;
  volatile const uint32_t ITFTTD0;
  volatile uint32_t ITATBCTR2;
        uint32_t RESERVED4[1U];
  volatile const uint32_t ITATBCTR0;
  volatile const uint32_t ITFTTD1;
  volatile uint32_t ITCTRL;
        uint32_t RESERVED5[39U];
  volatile uint32_t CLAIMSET;
  volatile uint32_t CLAIMCLR;
        uint32_t RESERVED7[8U];
  volatile const uint32_t DEVID;
  volatile const uint32_t DEVTYPE;
} TPI_Type;
# 1665 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile uint32_t FPCCR;
  volatile uint32_t FPCAR;
  volatile uint32_t FPDSCR;
  volatile const uint32_t MVFR0;
  volatile const uint32_t MVFR1;
} FPU_Type;
# 1795 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
typedef struct
{
  volatile uint32_t DHCSR;
  volatile uint32_t DCRSR;
  volatile uint32_t DCRDR;
  volatile uint32_t DEMCR;
        uint32_t RESERVED4[1U];
  volatile uint32_t DAUTHCTRL;
  volatile uint32_t DSCSR;
} CoreDebug_Type;
# 2096 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);

  reg_value = ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;
  reg_value &= ~((uint32_t)((0xFFFFUL << 16U) | (7UL << 8U)));
  reg_value = (reg_value |
                ((uint32_t)0x5FAUL << 16U) |
                (PriorityGroupTmp << 8U) );
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = reg_value;
}







static __inline uint32_t __NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) >> 8U));
}
# 2127 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
# 2144 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 2163 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __builtin_arm_dsb(0xF);
    __builtin_arm_isb(0xF);
  }
}
# 2182 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 2201 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
# 2216 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
# 2233 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline uint32_t __NVIC_GetActive(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 2322 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IPR[((uint32_t)IRQn)] = (uint8_t)((priority << (8U - 2U)) & (uint32_t)0xFFUL);
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - 2U)) & (uint32_t)0xFFUL);
  }
}
# 2344 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IPR[((uint32_t)IRQn)] >> (8U - 2U)));
  }
  else
  {
    return(((uint32_t)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - 2U)));
  }
}
# 2369 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2U)) ? (uint32_t)(2U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(2U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2U));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority & (uint32_t)((1UL << (SubPriorityBits )) - 1UL)))
         );
}
# 2396 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2U)) ? (uint32_t)(2U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(2U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2U));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority = (Priority ) & (uint32_t)((1UL << (SubPriorityBits )) - 1UL);
}
# 2419 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  vectors[(int32_t)IRQn + 16] = vector;
}
# 2434 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  return vectors[(int32_t)IRQn + 16];
}






__attribute__((__noreturn__)) static __inline void __NVIC_SystemReset(void)
{
  __builtin_arm_dsb(0xF);

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = (uint32_t)((0x5FAUL << 16U) |
                           (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) |
                            (1UL << 2U) );
  __builtin_arm_dsb(0xF);

  for(;;)
  {
    __builtin_arm_nop();
  }
}
# 2688 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline uint32_t SCB_GetFPUType(void)
{
  uint32_t mvfr0;

  mvfr0 = ((FPU_Type *) ((0xE000E000UL) + 0x0F30UL) )->MVFR0;
  if ((mvfr0 & ((0xFUL << 4U) | (0xFUL << 8U))) == 0x220U)
  {
    return 2U;
  }
  else if ((mvfr0 & ((0xFUL << 4U) | (0xFUL << 8U))) == 0x020U)
  {
    return 1U;
  }
  else
  {
    return 0U;
  }
}
# 2770 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD = (uint32_t)(ticks - 1UL);
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 2U) - 1UL);
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL = 0UL;
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL = (1UL << 2U) |
                   (1UL << 1U) |
                   (1UL );
  return (0UL);
}
# 2830 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
extern volatile int32_t ITM_RxBuffer;
# 2842 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL )) != 0UL) &&
      ((((ITM_Type *) (0xE0000000UL) )->TER & 1UL ) != 0UL) )
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0U].u32 == 0UL)
    {
      __builtin_arm_nop();
    }
    ((ITM_Type *) (0xE0000000UL) )->PORT[0U].u8 = (uint8_t)ch;
  }
  return (ch);
}
# 2863 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline int32_t ITM_ReceiveChar (void)
{
  int32_t ch = -1;

  if (ITM_RxBuffer != ((int32_t)0x5AA55AA5U))
  {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = ((int32_t)0x5AA55AA5U);
  }

  return (ch);
}
# 2883 "../../mcu/GDE501_fireware/Firmware/CMSIS\\core_cm33.h" 3
static __inline int32_t ITM_CheckChar (void)
{

  if (ITM_RxBuffer == ((int32_t)0x5AA55AA5U))
  {
    return (0);
  }
  else
  {
    return (1);
  }
}
# 160 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include/system_gd32e501.h" 1
# 46 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include/system_gd32e501.h"
extern uint32_t SystemCoreClock;



extern void SystemInit (void);

extern void SystemCoreClockUpdate (void);
# 161 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 2



typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;
# 215 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h"
# 1 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 1
# 39 "../../mcu/GDE501_fireware\\gd32e501_libopt.h"
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_adc.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_adc.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_adc.h" 2
# 295 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_adc.h"
void adc_deinit(void);

void adc_enable(void);

void adc_disable(void);



void adc_calibration_enable(void);

void adc_dma_mode_enable(void);

void adc_dma_mode_disable(void);

void adc_idma_mode_enable(void);

void adc_idma_mode_disable(void);



void adc_tempsensor_vrefint_enable(void);

void adc_tempsensor_vrefint_disable(void);



void adc_discontinuous_mode_config(uint8_t channel_group, uint8_t length);

void adc_special_function_config(uint32_t function, ControlStatus newvalue);



void adc_data_alignment_config(uint32_t data_alignment);

void adc_channel_length_config(uint8_t channel_group, uint32_t length);

void adc_regular_channel_config(uint8_t rank, uint8_t channel, uint32_t sample_time);

void adc_inserted_channel_config(uint8_t rank, uint8_t channel, uint32_t sample_time);

void adc_inserted_channel_offset_config(uint8_t inserted_channel, uint16_t offset);

void adc_inserted_channel_repeat_time_config(uint8_t time);



void adc_external_trigger_config(uint8_t channel_group, ControlStatus newvalue);

void adc_external_trigger_source_config(uint8_t channel_group, uint32_t external_trigger_source);

void adc_software_trigger_enable(uint8_t channel_group);



uint16_t adc_regular_data_read(void);

uint16_t adc_inserted_data_read(uint8_t inserted_channel);



void adc_watchdog_single_channel_enable(uint8_t channel);

void adc_watchdog_group_channel_enable(uint8_t channel_group);

void adc_watchdog_disable(void);

void adc_watchdog_threshold_config(uint16_t low_threshold, uint16_t high_threshold);



void adc_resolution_config(uint32_t resolution);

void adc_oversample_mode_config(uint8_t mode, uint16_t shift, uint8_t ratio);

void adc_oversample_mode_enable(void);

void adc_oversample_mode_disable(void);



FlagStatus adc_flag_get(uint32_t flag);

void adc_flag_clear(uint32_t flag);

void adc_interrupt_enable(uint32_t interrupt);

void adc_interrupt_disable(uint32_t interrupt);

FlagStatus adc_interrupt_flag_get(uint32_t flag);

void adc_interrupt_flag_clear(uint32_t flag);
# 40 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_crc.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_crc.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 41 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_crc.h" 2
# 93 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_crc.h"
void crc_deinit(void);

void crc_reverse_output_data_enable(void);

void crc_reverse_output_data_disable(void);


void crc_data_register_reset(void);

uint32_t crc_data_register_read(void);


uint8_t crc_free_data_register_read(void);

void crc_free_data_register_write(uint8_t free_data);


void crc_init_data_register_write(uint32_t init_data);

void crc_input_data_reverse_config(uint32_t data_reverse);


void crc_polynomial_size_set(uint32_t poly_size);

void crc_polynomial_set(uint32_t poly);


uint32_t crc_single_data_calculate(uint32_t sdata, uint8_t data_format);

uint32_t crc_block_data_calculate(void *array, uint32_t size, uint8_t data_format);
# 41 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_cla.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_cla.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_cla.h" 2
# 128 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_cla.h"
typedef enum
{

    CLA_FLAG_CLA0NF,
    CLA_FLAG_CLA0PF,
    CLA_FLAG_CLA1NF,
    CLA_FLAG_CLA1PF,
    CLA_FLAG_CLA2NF,
    CLA_FLAG_CLA2PF,
    CLA_FLAG_CLA3NF,
    CLA_FLAG_CLA3PF,
    CLA_FLAG_CLA4NF,
    CLA_FLAG_CLA4PF,
    CLA_FLAG_CLA5NF,
    CLA_FLAG_CLA5PF,
    CLA_FLAG_CLA6NF,
    CLA_FLAG_CLA6PF,
    CLA_FLAG_CLA7NF,
    CLA_FLAG_CLA7PF
}cla_flag_enum;


typedef enum
{

    CLA_INT_FLAG_CLA0NF,
    CLA_INT_FLAG_CLA0PF,
    CLA_INT_FLAG_CLA1NF,
    CLA_INT_FLAG_CLA1PF,
    CLA_INT_FLAG_CLA2NF,
    CLA_INT_FLAG_CLA2PF,
    CLA_INT_FLAG_CLA3NF,
    CLA_INT_FLAG_CLA3PF,
    CLA_INT_FLAG_CLA4NF,
    CLA_INT_FLAG_CLA4PF,
    CLA_INT_FLAG_CLA5NF,
    CLA_INT_FLAG_CLA5PF,
    CLA_INT_FLAG_CLA6NF,
    CLA_INT_FLAG_CLA6PF,
    CLA_INT_FLAG_CLA7NF,
    CLA_INT_FLAG_CLA7PF
}cla_interrupt_flag_enum;


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


typedef enum
{
    SIGS0,
    SIGS1
}cla_sigs_enum;


typedef enum
{
    CLA_OUTPUT_LOW,
    CLA_OUTPUT_HIGH
}cla_outputstatus_enum;
# 620 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_cla.h"
void cla_deinit(void);

void cla_enable(cla_enum cla_periph);

void cla_disable(cla_enum cla_periph);

cla_outputstatus_enum cla_output_state_get(cla_enum cla_periph);

void cla_sigs_input_config(cla_enum cla_periph, cla_sigs_enum sigs, uint32_t input);

void cla_lcu_control_config(cla_enum cla_periph, uint8_t lcuctl_value);

void cla_output_config(cla_enum cla_periph, uint32_t output);

void cla_output_enable(cla_enum cla_periph);

void cla_output_disable(cla_enum cla_periph);



void cla_flip_flop_output_reset(cla_enum cla_periph);

void cla_flip_flop_clockpolarity_config(cla_enum cla_periph, uint32_t polarity);

void cla_flip_flop_clocksource_config(cla_enum cla_periph, uint32_t clock_source);



FlagStatus cla_flag_get(cla_flag_enum flag);

void cla_flag_clear(cla_flag_enum flag);

void cla_negedge_interrupt_enable(uint32_t clanie);

void cla_negedge_interrupt_disable(uint32_t clanidis);

void cla_posedge_interrupt_enable(uint32_t clapie);

void cla_posedge_interrupt_disable(uint32_t clapidis);

FlagStatus cla_interrupt_flag_get(cla_interrupt_flag_enum int_flag);

void cla_interrupt_flag_clear(cla_interrupt_flag_enum int_flag);
# 42 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dac.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dac.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dac.h" 2
# 217 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dac.h"
void dac_deinit(uint32_t dac_periph);

void dac_enable(uint32_t dac_periph, uint8_t dac_out);

void dac_disable(uint32_t dac_periph, uint8_t dac_out);

void dac_dma_enable(uint32_t dac_periph, uint8_t dac_out);

void dac_dma_disable(uint32_t dac_periph, uint8_t dac_out);

void dac_output_buffer_enable(uint32_t dac_periph, uint8_t dac_out);

void dac_output_buffer_disable(uint32_t dac_periph, uint8_t dac_out);

uint16_t dac_output_value_get(uint32_t dac_periph, uint8_t dac_out);

void dac_data_set(uint32_t dac_periph, uint8_t dac_out, uint32_t dac_align, uint16_t data);

void dac_reset_mode_enable(uint32_t dac_periph, uint8_t dac_out);

void dac_reset_mode_disable(uint32_t dac_periph, uint8_t dac_out);



void dac_trigger_enable(uint32_t dac_periph, uint8_t dac_out);

void dac_trigger_disable(uint32_t dac_periph, uint8_t dac_out);

void dac_trigger_source_config(uint32_t dac_periph, uint8_t dac_out, uint32_t triggersource);

void dac_software_trigger_enable(uint32_t dac_periph, uint8_t dac_out);

void dac_software_trigger_disable(uint32_t dac_periph, uint8_t dac_out);



void dac_wave_mode_config(uint32_t dac_periph, uint8_t dac_out, uint32_t wave_mode);

void dac_wave_bit_width_config(uint32_t dac_periph, uint8_t dac_out, uint32_t bit_width);

void dac_lfsr_noise_config(uint32_t dac_periph, uint8_t dac_out, uint32_t unmask_bits);

void dac_triangle_noise_config(uint32_t dac_periph, uint8_t dac_out, uint32_t amplitude);

void dac_buffer_gain_config(uint32_t dac_periph, uint8_t dac_out, uint32_t buffer_gain);



void dac_concurrent_enable(uint32_t dac_periph);

void dac_concurrent_disable(uint32_t dac_periph);

void dac_concurrent_software_trigger_enable(uint32_t dac_periph);

void dac_concurrent_software_trigger_disable(uint32_t dac_periph);

void dac_concurrent_output_buffer_enable(uint32_t dac_periph);

void dac_concurrent_output_buffer_disable(uint32_t dac_periph);

void dac_concurrent_data_set(uint32_t dac_periph, uint32_t dac_align, uint16_t data0, uint16_t data1);



FlagStatus dac_flag_get(uint32_t dac_periph, uint8_t dac_out);

void dac_flag_clear(uint32_t dac_periph, uint8_t dac_out);

void dac_interrupt_enable(uint32_t dac_periph, uint8_t dac_out);

void dac_interrupt_disable(uint32_t dac_periph, uint8_t dac_out);

FlagStatus dac_interrupt_flag_get(uint32_t dac_periph, uint8_t dac_out);

void dac_interrupt_flag_clear(uint32_t dac_periph, uint8_t dac_out);
# 43 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dbg.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dbg.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dbg.h" 2
# 87 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dbg.h"
enum dbg_reg_idx
{
    DBG_IDX_CTL0 = 0x04U,
    DBG_IDX_CTL1 = 0x08U,
};


typedef enum
{
    DBG_FWDGT_HOLD = (((DBG_IDX_CTL0) << 6) | (8U)),
    DBG_WWDGT_HOLD = (((DBG_IDX_CTL0) << 6) | (9U)),
    DBG_TIMER0_HOLD = (((DBG_IDX_CTL0) << 6) | (10U)),
    DBG_TIMER1_HOLD = (((DBG_IDX_CTL0) << 6) | (11U)),
    DBG_TIMER2_HOLD = (((DBG_IDX_CTL0) << 6) | (12U)),
    DBG_TIMER5_HOLD = (((DBG_IDX_CTL0) << 6) | (19U)),
    DBG_TIMER6_HOLD = (((DBG_IDX_CTL0) << 6) | (20U)),
    DBG_TIMER13_HOLD = (((DBG_IDX_CTL0) << 6) | (27U)),
    DBG_TIMER14_HOLD = (((DBG_IDX_CTL1) << 6) | (16U)),
    DBG_TIMER15_HOLD = (((DBG_IDX_CTL1) << 6) | (17U)),
    DBG_TIMER16_HOLD = (((DBG_IDX_CTL1) << 6) | (18U)),
    DBG_I2C0_HOLD = (((DBG_IDX_CTL0) << 6) | (15U)),
    DBG_I2C1_HOLD = (((DBG_IDX_CTL0) << 6) | (16U)),
    DBG_I2C2_HOLD = (((DBG_IDX_CTL0) << 6) | (17U)),
    DBG_RTC_HOLD = (((DBG_IDX_CTL1) << 6) | (10U)),
}dbg_periph_enum;



void dbg_deinit(void);

uint32_t dbg_id_get(void);


void dbg_low_power_enable(uint32_t dbg_low_power);

void dbg_low_power_disable(uint32_t dbg_low_power);


void dbg_periph_enable(dbg_periph_enum dbg_periph);

void dbg_periph_disable(dbg_periph_enum dbg_periph);
# 44 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dma.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dma.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dma.h" 2
# 114 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dma.h"
typedef enum
{
    DMA_CH0 = 0,
    DMA_CH1,
    DMA_CH2,
    DMA_CH3,
    DMA_CH4,
    DMA_CH5,
    DMA_CH6,
} dma_channel_enum;


typedef struct
{
    uint32_t periph_addr;
    uint32_t periph_width;
    uint32_t memory_addr;
    uint32_t memory_width;
    uint32_t number;
    uint32_t priority;
    uint8_t periph_inc;
    uint8_t memory_inc;
    uint8_t direction;
} dma_parameter_struct;
# 218 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_dma.h"
void dma_deinit(dma_channel_enum channelx);

void dma_struct_para_init(dma_parameter_struct* init_struct);

void dma_init(dma_channel_enum channelx, dma_parameter_struct* init_struct);

void dma_circulation_enable(dma_channel_enum channelx);

void dma_circulation_disable(dma_channel_enum channelx);

void dma_memory_to_memory_enable(dma_channel_enum channelx);

void dma_memory_to_memory_disable(dma_channel_enum channelx);

void dma_channel_enable(dma_channel_enum channelx);

void dma_channel_disable(dma_channel_enum channelx);



void dma_periph_address_config(dma_channel_enum channelx, uint32_t address);

void dma_memory_address_config(dma_channel_enum channelx, uint32_t address);

void dma_transfer_number_config(dma_channel_enum channelx, uint32_t number);

uint32_t dma_transfer_number_get(dma_channel_enum channelx);

void dma_priority_config(dma_channel_enum channelx, uint32_t priority);

void dma_memory_width_config (dma_channel_enum channelx, uint32_t mwidth);

void dma_periph_width_config (dma_channel_enum channelx, uint32_t pwidth);

void dma_memory_increase_enable(dma_channel_enum channelx);

void dma_memory_increase_disable(dma_channel_enum channelx);

void dma_periph_increase_enable(dma_channel_enum channelx);

void dma_periph_increase_disable(dma_channel_enum channelx);

void dma_transfer_direction_config(dma_channel_enum channelx, uint8_t direction);



FlagStatus dma_flag_get(dma_channel_enum channelx, uint32_t flag);

void dma_flag_clear(dma_channel_enum channelx, uint32_t flag);

void dma_interrupt_enable(dma_channel_enum channelx, uint32_t source);

void dma_interrupt_disable(dma_channel_enum channelx, uint32_t source);

FlagStatus dma_interrupt_flag_get(dma_channel_enum channelx, uint32_t flag);

void dma_interrupt_flag_clear(dma_channel_enum channelx, uint32_t flag);
# 45 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_exti.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_exti.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 41 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_exti.h" 2
# 204 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_exti.h"
typedef enum
{
    EXTI_0 = ((uint32_t)((uint32_t)0x01U<<(0))),
    EXTI_1 = ((uint32_t)((uint32_t)0x01U<<(1))),
    EXTI_2 = ((uint32_t)((uint32_t)0x01U<<(2))),
    EXTI_3 = ((uint32_t)((uint32_t)0x01U<<(3))),
    EXTI_4 = ((uint32_t)((uint32_t)0x01U<<(4))),
    EXTI_5 = ((uint32_t)((uint32_t)0x01U<<(5))),
    EXTI_6 = ((uint32_t)((uint32_t)0x01U<<(6))),
    EXTI_7 = ((uint32_t)((uint32_t)0x01U<<(7))),
    EXTI_8 = ((uint32_t)((uint32_t)0x01U<<(8))),
    EXTI_9 = ((uint32_t)((uint32_t)0x01U<<(9))),
    EXTI_10 = ((uint32_t)((uint32_t)0x01U<<(10))),
    EXTI_11 = ((uint32_t)((uint32_t)0x01U<<(11))),
    EXTI_12 = ((uint32_t)((uint32_t)0x01U<<(12))),
    EXTI_13 = ((uint32_t)((uint32_t)0x01U<<(13))),
    EXTI_14 = ((uint32_t)((uint32_t)0x01U<<(14))),
    EXTI_15 = ((uint32_t)((uint32_t)0x01U<<(15))),
    EXTI_16 = ((uint32_t)((uint32_t)0x01U<<(16))),
    EXTI_17 = ((uint32_t)((uint32_t)0x01U<<(17))),
    EXTI_18 = ((uint32_t)((uint32_t)0x01U<<(18))),
    EXTI_19 = ((uint32_t)((uint32_t)0x01U<<(19))),
    EXTI_20 = ((uint32_t)((uint32_t)0x01U<<(20))),
    EXTI_21 = ((uint32_t)((uint32_t)0x01U<<(21))),
    EXTI_22 = ((uint32_t)((uint32_t)0x01U<<(22))),
    EXTI_23 = ((uint32_t)((uint32_t)0x01U<<(23))),
    EXTI_24 = ((uint32_t)((uint32_t)0x01U<<(24))),
    EXTI_25 = ((uint32_t)((uint32_t)0x01U<<(25))),
    EXTI_26 = ((uint32_t)((uint32_t)0x01U<<(26))),
    EXTI_27 = ((uint32_t)((uint32_t)0x01U<<(27))),
}exti_line_enum;


typedef enum
{
    EXTI_INTERRUPT = 0,
    EXTI_EVENT
}exti_mode_enum;


typedef enum
{
    EXTI_TRIG_RISING = 0,
    EXTI_TRIG_FALLING,
    EXTI_TRIG_BOTH,
    EXTI_TRIG_NONE
}exti_trig_type_enum;




void exti_deinit(void);

void exti_init(exti_line_enum linex, exti_mode_enum mode, exti_trig_type_enum trig_type);

void exti_interrupt_enable(exti_line_enum linex);

void exti_interrupt_disable(exti_line_enum linex);

void exti_event_enable(exti_line_enum linex);

void exti_event_disable(exti_line_enum linex);



void exti_software_interrupt_enable(exti_line_enum linex);

void exti_software_interrupt_disable(exti_line_enum linex);

FlagStatus exti_flag_get(exti_line_enum linex);

void exti_flag_clear(exti_line_enum linex);

FlagStatus exti_interrupt_flag_get(exti_line_enum linex);

void exti_interrupt_flag_clear(exti_line_enum linex);
# 46 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_fmc.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_fmc.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 41 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_fmc.h" 2
# 153 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_fmc.h"
typedef enum
{
    FMC_READY,
    FMC_BUSY,
    FMC_PGERR,
    FMC_PGAERR,
    FMC_WPERR,
    FMC_TOERR,
    FMC_ILLEGAL_OPERATION
}fmc_state_enum;


typedef struct
{
    uint16_t ob_spc;
    uint16_t ob_user;
    uint32_t ob_data;
    uint64_t ob_wp;
}option_byte_struct;


typedef enum
{
    DOUBLEWORD_SPC_USER_DATA = 0,
    DOUBLEWORD_WP = 1
}option_byte_enum;
# 281 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_fmc.h"
void fmc_unlock(void);

void fmc_bank0_unlock(void);

void fmc_bank1_unlock(void);

void fmc_lock(void);

void fmc_bank0_lock(void);

void fmc_bank1_lock(void);


void fmc_wscnt_set(uint8_t wscnt);

void fmc_prefetch_enable(void);

void fmc_prefetch_disable(void);

void fmc_cache_enable(void);

void fmc_cache_disable(void);

void fmc_cache_reset_enable(void);

void fmc_cache_reset_disable(void);


fmc_state_enum fmc_page_erase(uint32_t page_address);

fmc_state_enum fmc_mass_erase(void);

fmc_state_enum fmc_bank0_mass_erase(void);

fmc_state_enum fmc_bank1_mass_erase(void);

fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data);

fmc_state_enum otp_doubleword_program(uint32_t address, uint64_t data);



void ob_unlock(void);

void ob_lock(void);

void ob_reset(void);

fmc_state_enum ob_erase(void);

fmc_state_enum ob_write_protection_enable(uint32_t ob_wp);

fmc_state_enum ob_security_protection_config(uint16_t ob_spc);

fmc_state_enum ob_user_write(uint8_t ob_user);

fmc_state_enum ob_data_program(uint16_t data);

uint8_t ob_user_get(void);

uint16_t ob_data_get(void);

uint32_t ob_write_protection_get(void);

uint8_t ob_plevel_get(void);



FlagStatus fmc_bank0_flag_get(uint32_t flag);

FlagStatus fmc_bank1_flag_get(uint32_t flag);

void fmc_bank0_flag_clear(uint32_t flag);

void fmc_bank1_flag_clear(uint32_t flag);

void fmc_bank0_interrupt_enable(uint32_t interrupt);

void fmc_bank1_interrupt_enable(uint32_t interrupt);

void fmc_bank0_interrupt_disable(uint32_t interrupt);

void fmc_bank1_interrupt_disable(uint32_t interrupt);

FlagStatus fmc_bank0_interrupt_flag_get(uint32_t int_flag);

FlagStatus fmc_bank1_interrupt_flag_get(uint32_t int_flag);

void fmc_bank0_interrupt_flag_clear(uint32_t int_flag);

void fmc_bank1_interrupt_flag_clear(uint32_t int_flag);

fmc_state_enum fmc_bank0_state_get(void);

fmc_state_enum fmc_bank1_state_get(void);

fmc_state_enum fmc_bank0_ready_wait(uint32_t timeout);

fmc_state_enum fmc_bank1_ready_wait(uint32_t timeout);



fmc_state_enum boot_forbid(void);

fmc_state_enum swd_disable(void);
# 47 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_gpio.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_gpio.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_gpio.h" 2
# 281 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_gpio.h"
typedef FlagStatus bit_status;
# 355 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_gpio.h"
void gpio_deinit(uint32_t gpio_periph);

void gpio_mode_set(uint32_t gpio_periph, uint32_t mode, uint32_t pull_up_down, uint32_t pin);

void gpio_output_options_set(uint32_t gpio_periph, uint8_t otype, uint32_t speed, uint32_t pin);


void gpio_bit_set(uint32_t gpio_periph, uint32_t pin);

void gpio_bit_reset(uint32_t gpio_periph, uint32_t pin);

void gpio_bit_write(uint32_t gpio_periph, uint32_t pin, bit_status bit_value);

void gpio_port_write(uint32_t gpio_periph, uint16_t data);


FlagStatus gpio_input_bit_get(uint32_t gpio_periph, uint32_t pin);

uint16_t gpio_input_port_get(uint32_t gpio_periph);

FlagStatus gpio_output_bit_get(uint32_t gpio_periph, uint32_t pin);

uint16_t gpio_output_port_get(uint32_t gpio_periph);


void gpio_af_set(uint32_t gpio_periph, uint32_t alt_func_num, uint32_t pin);

void gpio_pin_lock(uint32_t gpio_periph, uint32_t pin);


void gpio_bit_toggle(uint32_t gpio_periph, uint32_t pin);

void gpio_port_toggle(uint32_t gpio_periph);
# 48 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_mdio.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_mdio.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_mdio.h" 2
# 190 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_mdio.h"
void mdio_deinit(void);

void mdio_software_reset(void);



uint32_t mdio_init(uint32_t phy_size, uint32_t phy_softaddr, uint32_t phy_sel, uint16_t devadd);

void mdio_phy_length_config(uint32_t phy_bit);

void mdio_soft_phyadr_set(uint32_t phy_soft);

void mdio_framefield_phyadr_config(uint32_t phy_sel);

void mdio_framefield_devadd_config(uint16_t type);

uint32_t mdio_phy_pin_read(void);

void mdio_timeout_config(uint16_t timeout);

void mdio_timeout_enable(void);

void mdio_timeout_disable(void);



uint16_t mdio_op_receive(void);

uint16_t mdio_phyadr_receive(void);

uint16_t mdio_devadd_receive(void);

uint16_t mdio_ta_receive(void);

uint16_t mdio_data_receive(void);

uint16_t mdio_address_receive(void);

void mdio_data_transmit(uint16_t data);




FlagStatus mdio_flag_get(uint32_t flag);

void mdio_flag_clear(uint32_t flag);

void mdio_interrupt_enable(uint32_t interrupt);

void mdio_interrupt_disable(uint32_t interrupt);
# 49 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_syscfg.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_syscfg.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_syscfg.h" 2
# 179 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_syscfg.h"
void syscfg_deinit(void);



void syscfg_bootmode_config(uint8_t syscfg_bootmode);


void syscfg_dma_remap_enable(uint32_t syscfg_dma_remap);

void syscfg_dma_remap_disable(uint32_t syscfg_dma_remap);


void syscfg_high_current_enable(uint32_t syscfg_high_current);

void syscfg_high_current_disable(uint32_t syscfg_high_current);


void syscfg_vref_enable(void);

void syscfg_vref_disable(void);


void syscfg_pin_reset_mode_config(uint32_t syscfg_pin_reset_mode);


void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin);

void syscfg_lock_config(uint32_t syscfg_lock);


void irq_latency_set(uint8_t irq_latency);


FlagStatus syscfg_flag_get(uint32_t syscfg_flag);

void syscfg_flag_clear(uint32_t syscfg_flag);
# 50 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_i2c.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_i2c.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_i2c.h" 2
# 177 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_i2c.h"
typedef enum
{
    I2C_INT_FLAG_TI = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((1U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(1U))),
    I2C_INT_FLAG_RBNE = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((2U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(2U))),
    I2C_INT_FLAG_ADDSEND = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((3U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(3U))),
    I2C_INT_FLAG_NACK = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((4U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(4U))),
    I2C_INT_FLAG_STPDET = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((5U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(5U))),
    I2C_INT_FLAG_TC = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((6U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(6U))),
    I2C_INT_FLAG_TCR = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((7U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(6U))),
    I2C_INT_FLAG_BERR = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((8U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(7U))),
    I2C_INT_FLAG_LOSTARB = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((9U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(7U))),
    I2C_INT_FLAG_OUERR = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((10U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(7U))),
    I2C_INT_FLAG_PECERR = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((11U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(7U))),
    I2C_INT_FLAG_TIMEOUT = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((12U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(7U))),
    I2C_INT_FLAG_SMBALT = (((uint32_t)(((uint32_t)0x00000018U)) << 22) | (uint32_t)((13U) << 16) | (((uint32_t)(((uint32_t)0x00000000U)) << 6) | (uint32_t)(7U))),
}i2c_interrupt_flag_enum;
# 276 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_i2c.h"
void i2c_deinit(uint32_t i2c_periph);

void i2c_timing_config(uint32_t i2c_periph, uint32_t psc, uint32_t scl_dely, uint32_t sda_dely);

void i2c_digital_noise_filter_config(uint32_t i2c_periph, uint32_t filter_length);


void i2c_master_clock_config(uint32_t i2c_periph, uint32_t sclh, uint32_t scll);

void i2c_master_addressing(uint32_t i2c_periph, uint32_t address, uint32_t trans_direction);

void i2c_address10_header_enable(uint32_t i2c_periph);

void i2c_address10_header_disable(uint32_t i2c_periph);

void i2c_address10_enable(uint32_t i2c_periph);

void i2c_address10_disable(uint32_t i2c_periph);

void i2c_automatic_end_enable(uint32_t i2c_periph);

void i2c_automatic_end_disable(uint32_t i2c_periph);


void i2c_slave_response_to_gcall_enable(uint32_t i2c_periph);

void i2c_slave_response_to_gcall_disable(uint32_t i2c_periph);

void i2c_stretch_scl_low_enable(uint32_t i2c_periph);

void i2c_stretch_scl_low_disable(uint32_t i2c_periph);

void i2c_address_config(uint32_t i2c_periph, uint32_t address, uint32_t addr_format);

void i2c_address_bit_compare_config(uint32_t i2c_periph, uint32_t compare_bits);

void i2c_address_disable(uint32_t i2c_periph);

void i2c_second_address_config(uint32_t i2c_periph, uint32_t address, uint32_t addr_mask);

void i2c_second_address_disable(uint32_t i2c_periph);

uint32_t i2c_recevied_address_get(uint32_t i2c_periph);

void i2c_slave_byte_control_enable(uint32_t i2c_periph);

void i2c_slave_byte_control_disable(uint32_t i2c_periph);

void i2c_nack_enable(uint32_t i2c_periph);

void i2c_nack_disable(uint32_t i2c_periph);


void i2c_enable(uint32_t i2c_periph);

void i2c_disable(uint32_t i2c_periph);

void i2c_start_on_bus(uint32_t i2c_periph);

void i2c_stop_on_bus(uint32_t i2c_periph);

void i2c_data_transmit(uint32_t i2c_periph, uint32_t data);

uint32_t i2c_data_receive(uint32_t i2c_periph);

void i2c_reload_enable(uint32_t i2c_periph);

void i2c_reload_disable(uint32_t i2c_periph);

void i2c_transfer_byte_number_config(uint32_t i2c_periph, uint32_t byte_number);

void i2c_dma_enable(uint32_t i2c_periph, uint8_t dma);

void i2c_dma_disable(uint32_t i2c_periph, uint8_t dma);

void i2c_pec_transfer(uint32_t i2c_periph);

void i2c_pec_enable(uint32_t i2c_periph);

void i2c_pec_disable(uint32_t i2c_periph);

uint32_t i2c_pec_value_get(uint32_t i2c_periph);


void i2c_smbus_alert_enable(uint32_t i2c_periph);

void i2c_smbus_alert_disable(uint32_t i2c_periph);

void i2c_smbus_default_addr_enable(uint32_t i2c_periph);

void i2c_smbus_default_addr_disable(uint32_t i2c_periph);

void i2c_smbus_host_addr_enable(uint32_t i2c_periph);

void i2c_smbus_host_addr_disable(uint32_t i2c_periph);

void i2c_extented_clock_timeout_enable(uint32_t i2c_periph);

void i2c_extented_clock_timeout_disable(uint32_t i2c_periph);

void i2c_clock_timeout_enable(uint32_t i2c_periph);

void i2c_clock_timeout_disable(uint32_t i2c_periph);

void i2c_bus_timeout_b_config(uint32_t i2c_periph, uint32_t timeout);

void i2c_bus_timeout_a_config(uint32_t i2c_periph, uint32_t timeout);

void i2c_idle_clock_timeout_config(uint32_t i2c_periph, uint32_t timeout);


FlagStatus i2c_flag_get(uint32_t i2c_periph, uint32_t flag);

void i2c_flag_clear(uint32_t i2c_periph, uint32_t flag);

void i2c_interrupt_enable(uint32_t i2c_periph, uint32_t interrupt);

void i2c_interrupt_disable(uint32_t i2c_periph, uint32_t interrupt);

FlagStatus i2c_interrupt_flag_get(uint32_t i2c_periph, i2c_interrupt_flag_enum int_flag);

void i2c_interrupt_flag_clear(uint32_t i2c_periph, i2c_interrupt_flag_enum int_flag);
# 51 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_fwdgt.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_fwdgt.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 41 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_fwdgt.h" 2
# 99 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_fwdgt.h"
void fwdgt_write_enable(void);

void fwdgt_write_disable(void);

void fwdgt_enable(void);


ErrStatus fwdgt_prescaler_value_config(uint16_t prescaler_value);

ErrStatus fwdgt_reload_value_config(uint16_t reload_value);

ErrStatus fwdgt_window_value_config(uint16_t window_value);

void fwdgt_counter_reload(void);

ErrStatus fwdgt_config(uint16_t reload_value, uint8_t prescaler_div);


FlagStatus fwdgt_flag_get(uint16_t flag);
# 52 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_pmu.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_pmu.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_pmu.h" 2
# 112 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_pmu.h"
void pmu_deinit(void);



void pmu_lvd_select(uint32_t lvdt_n);

void pmu_ldo_output_select(uint32_t ldo_output);

void pmu_lvd_disable(void);



void pmu_to_sleepmode(uint8_t sleepmodecmd);

void pmu_to_deepsleepmode(uint32_t ldo, uint8_t deepsleepmodecmd);

void pmu_to_standbymode(uint8_t standbymodecmd);

void pmu_wakeup_pin_enable(uint32_t wakeup_pin);

void pmu_wakeup_pin_disable(uint32_t wakeup_pin);



void pmu_backup_write_enable(void);

void pmu_backup_write_disable(void);



void pmu_flag_clear(uint32_t flag_clear);

FlagStatus pmu_flag_get(uint32_t flag);
# 53 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_rcu.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_rcu.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 41 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_rcu.h" 2
# 249 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_rcu.h"
typedef enum
{

    IDX_AHBEN = 0x14U,
    IDX_APB2EN = 0x18U,
    IDX_APB1EN = 0x1CU,

    IDX_AHBRST = 0x28U,
    IDX_APB2RST = 0x0CU,
    IDX_APB1RST = 0x10U,

    IDX_CTL0 = 0x00U,
    IDX_BDCTL = 0x20U,
    IDX_CTL1 = 0x34U,

    IDX_RSTSCK = 0x24U,

    IDX_INT = 0x08U,

    IDX_CFG0 = 0x04U,
    IDX_CFG2 = 0x30U
}reg_idx;


typedef enum
{

    RCU_DMA = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(0U)),
    RCU_CRC = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(6U)),
    RCU_CLA = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(15U)),
    RCU_GPIOA = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(17U)),
    RCU_GPIOB = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(18U)),
    RCU_GPIOC = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(19U)),
    RCU_GPIOD = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(20U)),
    RCU_GPIOF = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(22U)),


    RCU_CFGCMP = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(0U)),
    RCU_ADC = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(9U)),
    RCU_TIMER0 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(11U)),
    RCU_SPI0 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(12U)),
    RCU_USART0 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(14U)),
    RCU_TIMER14 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(16U)),
    RCU_TIMER15 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(17U)),
    RCU_TIMER16 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(18U)),
    RCU_DBGMCU = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(22U)),


    RCU_TIMER1 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(0U)),
    RCU_TIMER2 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(1U)),
    RCU_TIMER5 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(4U)),
    RCU_TIMER6 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(5U)),
    RCU_TIMER13 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(8U)),
    RCU_WWDGT = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(11U)),
    RCU_SPI1 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(14U)),
    RCU_SPI2 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(15U)),
    RCU_USART1 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(17U)),
    RCU_I2C0 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(21U)),
    RCU_I2C1 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(22U)),
    RCU_I2C2 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(24U)),
    RCU_MDIO = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(25U)),
    RCU_DAC2 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(26U)),
    RCU_DAC3 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(27U)),
    RCU_PMU = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(28U)),
    RCU_DAC0 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(29U)),
    RCU_DAC1 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(31U)),


    RCU_RTC = (((uint32_t)(IDX_BDCTL)<<6) | (uint32_t)(15U))
}rcu_periph_enum;


typedef enum
{

    RCU_SRAM_SLP = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(2U)),
    RCU_FMC_SLP = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(4U)),
}rcu_periph_sleep_enum;


typedef enum
{

    RCU_CLARST = (((uint32_t)(IDX_AHBRST)<<6) | (uint32_t)(15U)),
    RCU_GPIOARST = (((uint32_t)(IDX_AHBRST)<<6) | (uint32_t)(17U)),
    RCU_GPIOBRST = (((uint32_t)(IDX_AHBRST)<<6) | (uint32_t)(18U)),
    RCU_GPIOCRST = (((uint32_t)(IDX_AHBRST)<<6) | (uint32_t)(19U)),
    RCU_GPIODRST = (((uint32_t)(IDX_AHBRST)<<6) | (uint32_t)(20U)),
    RCU_GPIOFRST = (((uint32_t)(IDX_AHBRST)<<6) | (uint32_t)(22U)),


    RCU_CFGCMPRST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(0U)),
    RCU_ADCRST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(9U)),
    RCU_TIMER0RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(11U)),
    RCU_SPI0RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(12U)),
    RCU_USART0RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(14U)),
    RCU_TIMER14RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(16U)),
    RCU_TIMER15RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(17U)),
    RCU_TIMER16RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(18U)),


    RCU_TIMER1RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(0U)),
    RCU_TIMER2RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(1U)),
    RCU_TIMER5RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(4U)),
    RCU_TIMER6RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(5U)),
    RCU_TIMER13RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(8U)),
    RCU_WWDGTRST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(11U)),
    RCU_SPI1RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(14U)),
    RCU_SPI2RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(15U)),
    RCU_USART1RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(17U)),
    RCU_I2C0RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(21U)),
    RCU_I2C1RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(22U)),
    RCU_I2C2RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(24U)),
    RCU_MDIORST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(25U)),
    RCU_DAC2RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(26U)),
    RCU_DAC3RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(27U)),
    RCU_PMURST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(28U)),
    RCU_DAC0RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(29U)),
    RCU_DAC1RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(31U)),
}rcu_periph_reset_enum;


typedef enum
{
    RCU_FLAG_IRC40KSTB = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(1U)),
    RCU_FLAG_LXTALSTB = (((uint32_t)(IDX_BDCTL)<<6) | (uint32_t)(1U)),
    RCU_FLAG_IRC8MSTB = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(1U)),
    RCU_FLAG_HXTALSTB = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(17U)),
    RCU_FLAG_PLLSTB = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(25U)),
    RCU_FLAG_IRC28MSTB = (((uint32_t)(IDX_CTL1)<<6) | (uint32_t)(1U)),

    RCU_FLAG_V12RST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(23U)),
    RCU_FLAG_OBLRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(25U)),
    RCU_FLAG_EPRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(26U)),
    RCU_FLAG_PORRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(27U)),
    RCU_FLAG_SWRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(28U)),
    RCU_FLAG_FWDGTRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(29U)),
    RCU_FLAG_WWDGTRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(30U)),
    RCU_FLAG_LPRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(31U))
}rcu_flag_enum;


typedef enum
{
    RCU_INT_FLAG_IRC40KSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(0U)),
    RCU_INT_FLAG_LXTALSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(1U)),
    RCU_INT_FLAG_IRC8MSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(2U)),
    RCU_INT_FLAG_HXTALSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(3U)),
    RCU_INT_FLAG_PLLSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(4U)),
    RCU_INT_FLAG_IRC28MSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(5U)),
    RCU_INT_FLAG_CKM = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(7U)),
}rcu_int_flag_enum;


typedef enum
{
    RCU_INT_FLAG_IRC40KSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(16U)),
    RCU_INT_FLAG_LXTALSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(17U)),
    RCU_INT_FLAG_IRC8MSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(18U)),
    RCU_INT_FLAG_HXTALSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(19U)),
    RCU_INT_FLAG_PLLSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(20U)),
    RCU_INT_FLAG_IRC28MSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(21U)),
    RCU_INT_FLAG_CKM_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(23U)),
}rcu_int_flag_clear_enum;


typedef enum
{
    RCU_INT_IRC40KSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(8U)),
    RCU_INT_LXTALSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(9U)),
    RCU_INT_IRC8MSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(10U)),
    RCU_INT_HXTALSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(11U)),
    RCU_INT_PLLSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(12U)),
    RCU_INT_IRC28MSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(13U)),
}rcu_int_enum;


typedef enum
{
    RCU_ADCCK_IRC28M_DIV2 = 0U,
    RCU_ADCCK_IRC28M,
    RCU_ADCCK_APB2_DIV2,
    RCU_ADCCK_AHB_DIV3,
    RCU_ADCCK_APB2_DIV4,
    RCU_ADCCK_AHB_DIV5,
    RCU_ADCCK_APB2_DIV6,
    RCU_ADCCK_AHB_DIV7,
    RCU_ADCCK_APB2_DIV8,
    RCU_ADCCK_AHB_DIV9
}rcu_adc_clock_enum;


typedef enum
{
    RCU_HXTAL = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(16U)),
    RCU_LXTAL = (((uint32_t)(IDX_BDCTL)<<6) | (uint32_t)(0U)),
    RCU_IRC8M = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(0U)),
    RCU_IRC28M = (((uint32_t)(IDX_CTL1)<<6) | (uint32_t)(0U)),
    RCU_IRC40K = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(0U)),
    RCU_PLL_CK = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(24U))
}rcu_osci_type_enum;


typedef enum
{
    CK_SYS = 0U,
    CK_AHB,
    CK_APB1,
    CK_APB2,
    CK_ADC,
    CK_USART
}rcu_clock_freq_enum;
# 642 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_rcu.h"
void rcu_deinit(void);

void rcu_periph_clock_enable(rcu_periph_enum periph);

void rcu_periph_clock_disable(rcu_periph_enum periph);

void rcu_periph_clock_sleep_enable(rcu_periph_sleep_enum periph);

void rcu_periph_clock_sleep_disable(rcu_periph_sleep_enum periph);

void rcu_periph_reset_enable(rcu_periph_reset_enum periph_reset);

void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset);

void rcu_bkp_reset_enable(void);

void rcu_bkp_reset_disable(void);



void rcu_system_clock_source_config(uint32_t ck_sys);

uint32_t rcu_system_clock_source_get(void);

void rcu_ahb_clock_config(uint32_t ck_ahb);

void rcu_apb1_clock_config(uint32_t ck_apb1);

void rcu_apb2_clock_config(uint32_t ck_apb2);

void rcu_adc_clock_config(rcu_adc_clock_enum ck_adc);

void rcu_ckout_config(uint32_t ckout_src, uint32_t ckout_div);



void rcu_pll_config(uint32_t pll_src, uint32_t pll_mul);

void rcu_usart_clock_config(uint32_t ck_usart);

void rcu_i2c_clock_config(uint32_t i2c_periph, uint32_t ck_i2c);

void rcu_rtc_clock_config(uint32_t rtc_clock_source);

void rcu_hxtal_prediv_config(uint32_t hxtal_prediv);

void rcu_lxtal_drive_capability_config(uint32_t lxtal_dricap);



FlagStatus rcu_flag_get(rcu_flag_enum flag);

void rcu_all_reset_flag_clear(void);

FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag);

void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag_clear);

void rcu_interrupt_enable(rcu_int_enum stab_int);

void rcu_interrupt_disable(rcu_int_enum stab_int);



ErrStatus rcu_osci_stab_wait(rcu_osci_type_enum osci);

void rcu_osci_on(rcu_osci_type_enum osci);

void rcu_osci_off(rcu_osci_type_enum osci);

void rcu_osci_bypass_mode_enable(rcu_osci_type_enum osci);

void rcu_osci_bypass_mode_disable(rcu_osci_type_enum osci);

void rcu_hxtal_clock_monitor_enable(void);

void rcu_hxtal_clock_monitor_disable(void);


void rcu_irc8m_adjust_value_set(uint8_t irc8m_adjval);

void rcu_irc28m_adjust_value_set(uint8_t irc28m_adjval);

void rcu_voltage_key_unlock(void);

void rcu_deepsleep_voltage_set(uint32_t dsvol);


uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock);
# 54 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_rtc.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_rtc.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_rtc.h" 2
# 210 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_rtc.h"
typedef struct
{
    uint8_t rtc_year;
    uint8_t rtc_month;
    uint8_t rtc_date;
    uint8_t rtc_day_of_week;
    uint8_t rtc_hour;
    uint8_t rtc_minute;
    uint8_t rtc_second;
    uint16_t rtc_factor_asyn;
    uint16_t rtc_factor_syn;
    uint32_t rtc_am_pm;
    uint32_t rtc_display_format;
}rtc_parameter_struct;


typedef struct
{
    uint32_t rtc_alarm_mask;
    uint32_t rtc_weekday_or_date;
    uint8_t rtc_alarm_day;
    uint8_t rtc_alarm_hour;
    uint8_t rtc_alarm_minute;
    uint8_t rtc_alarm_second;
    uint32_t rtc_am_pm;
}rtc_alarm_struct;


typedef struct
{
    uint8_t rtc_timestamp_month;
    uint8_t rtc_timestamp_date;
    uint8_t rtc_timestamp_day;
    uint8_t rtc_timestamp_hour;
    uint8_t rtc_timestamp_minute;
    uint8_t rtc_timestamp_second;
    uint32_t rtc_am_pm;
}rtc_timestamp_struct;


typedef struct
{
    uint32_t rtc_tamper_source;
    uint32_t rtc_tamper_trigger;
    uint32_t rtc_tamper_filter;
    uint32_t rtc_tamper_sample_frequency;
    ControlStatus rtc_tamper_precharge_enable;
    uint32_t rtc_tamper_precharge_time;
    ControlStatus rtc_tamper_with_timestamp;
}rtc_tamper_struct;
# 493 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_rtc.h"
ErrStatus rtc_deinit(void);

ErrStatus rtc_init(rtc_parameter_struct* rtc_initpara_struct);

ErrStatus rtc_init_mode_enter(void);

void rtc_init_mode_exit(void);

ErrStatus rtc_register_sync_wait(void);


void rtc_current_time_get(rtc_parameter_struct* rtc_initpara_struct);

uint32_t rtc_subsecond_get(void);



void rtc_alarm_config(rtc_alarm_struct* rtc_alarm_time);

void rtc_alarm_subsecond_config(uint32_t mask_subsecond, uint32_t subsecond);

void rtc_alarm_get(rtc_alarm_struct* rtc_alarm_time);

uint32_t rtc_alarm_subsecond_get(void);

void rtc_alarm_enable(void);

ErrStatus rtc_alarm_disable(void);



void rtc_timestamp_enable(uint32_t edge);

void rtc_timestamp_disable(void);

void rtc_timestamp_get(rtc_timestamp_struct* rtc_timestamp);

uint32_t rtc_timestamp_subsecond_get(void);

void rtc_tamper_enable(rtc_tamper_struct* rtc_tamper);

void rtc_tamper_disable(uint32_t source);


void rtc_alter_output_config(uint32_t source, uint32_t mode);


ErrStatus rtc_calibration_config(uint32_t window, uint32_t plus, uint32_t minus);

void rtc_hour_adjust(uint32_t operation);

ErrStatus rtc_second_adjust(uint32_t add, uint32_t minus);


void rtc_bypass_shadow_enable(void);

void rtc_bypass_shadow_disable(void);


ErrStatus rtc_refclock_detection_enable(void);

ErrStatus rtc_refclock_detection_disable(void);



void rtc_interrupt_enable(uint32_t interrupt);

void rtc_interrupt_disable(uint32_t interrupt);

FlagStatus rtc_flag_get(uint32_t flag);

void rtc_flag_clear(uint32_t flag);
# 55 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_spi.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_spi.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_spi.h" 2
# 141 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_spi.h"
typedef struct
{
    uint32_t device_mode;
    uint32_t trans_mode;
    uint32_t frame_size;
    uint32_t nss;
    uint32_t endian;
    uint32_t clock_polarity_phase;
    uint32_t prescale;
}spi_parameter_struct;
# 328 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_spi.h"
void spi_i2s_deinit(uint32_t spi_periph);

void spi_struct_para_init(spi_parameter_struct* spi_struct);

ErrStatus spi_init(uint32_t spi_periph, spi_parameter_struct* spi_struct);

void spi_enable(uint32_t spi_periph);

void spi_disable(uint32_t spi_periph);


void i2s_init(uint32_t spi_periph, uint32_t mode, uint32_t standard, uint32_t ckpl);

void i2s_psc_config(uint32_t spi_periph, uint32_t audiosample, uint32_t frameformat, uint32_t mckout);

void i2s_enable(uint32_t spi_periph);

void i2s_disable(uint32_t spi_periph);



void spi_nss_output_enable(uint32_t spi_periph);

void spi_nss_output_disable(uint32_t spi_periph);

void spi_nss_internal_high(uint32_t spi_periph);

void spi_nss_internal_low(uint32_t spi_periph);


void spi_dma_enable(uint32_t spi_periph, uint8_t dma);

void spi_dma_disable(uint32_t spi_periph, uint8_t dma);


ErrStatus spi_data_frame_format_config(uint32_t spi_periph, uint16_t frame_format);

void spi_i2s_data_transmit(uint32_t spi_periph, uint16_t data);

uint16_t spi_i2s_data_receive(uint32_t spi_periph);

void spi_bidirectional_transfer_config(uint32_t spi_periph, uint32_t transfer_direction);



void spi_crc_polynomial_set(uint32_t spi_periph, uint16_t crc_poly);

uint16_t spi_crc_polynomial_get(uint32_t spi_periph);

void spi_crc_on(uint32_t spi_periph);

void spi_crc_off(uint32_t spi_periph);

void spi_crc_next(uint32_t spi_periph);

uint16_t spi_crc_get(uint32_t spi_periph, uint8_t crc);



void spi_ti_mode_enable(uint32_t spi_periph);

void spi_ti_mode_disable(uint32_t spi_periph);



void spi_nssp_mode_enable(uint32_t spi_periph);

void spi_nssp_mode_disable(uint32_t spi_periph);



void qspi_enable(uint32_t spi_periph);

void qspi_disable(uint32_t spi_periph);

void qspi_write_enable(uint32_t spi_periph);

void qspi_read_enable(uint32_t spi_periph);

void qspi_io23_output_enable(uint32_t spi_periph);

void qspi_io23_output_disable(uint32_t spi_periph);



void spi_fifo_access_size_config(uint32_t spi_periph, uint16_t fifo_access_size);

void spi_transmit_odd_config(uint32_t spi_periph, uint16_t odd);

void spi_receive_odd_config(uint32_t spi_periph, uint16_t odd);

void spi_crc_length_set(uint32_t spi_periph, uint16_t crc_length);



void spi_i2s_interrupt_enable(uint32_t spi_periph, uint8_t interrupt);

void spi_i2s_interrupt_disable(uint32_t spi_periph, uint8_t interrupt);

FlagStatus spi_i2s_interrupt_flag_get(uint32_t spi_periph, uint8_t interrupt);

FlagStatus spi_i2s_flag_get(uint32_t spi_periph, uint32_t flag);

void spi_crc_error_clear(uint32_t spi_periph);
# 56 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_timer.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_timer.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_timer.h" 2
# 261 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_timer.h"
typedef struct
{
    uint16_t prescaler;
    uint16_t alignedmode;
    uint16_t counterdirection;
    uint16_t clockdivision;
    uint32_t period;
    uint8_t repetitioncounter;
}timer_parameter_struct;


typedef struct
{
    uint16_t runoffstate;
    uint16_t ideloffstate;
    uint16_t deadtime;
    uint16_t breakpolarity;
    uint16_t outputautostate;
    uint16_t protectmode;
    uint16_t breakstate;
}timer_break_parameter_struct;


typedef struct
{
    uint16_t outputstate;
    uint16_t outputnstate;
    uint16_t ocpolarity;
    uint16_t ocnpolarity;
    uint16_t ocidlestate;
    uint16_t ocnidlestate;
}timer_oc_parameter_struct;


typedef struct
{
    uint16_t icpolarity;
    uint16_t icselection;
    uint16_t icprescaler;
    uint16_t icfilter;
}timer_ic_parameter_struct;
# 607 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_timer.h"
void timer_deinit(uint32_t timer_periph);

void timer_struct_para_init(timer_parameter_struct* initpara);

void timer_init(uint32_t timer_periph, timer_parameter_struct* initpara);

void timer_enable(uint32_t timer_periph);

void timer_disable(uint32_t timer_periph);

void timer_auto_reload_shadow_enable(uint32_t timer_periph);

void timer_auto_reload_shadow_disable(uint32_t timer_periph);

void timer_update_event_enable(uint32_t timer_periph);

void timer_update_event_disable(uint32_t timer_periph);

void timer_counter_alignment(uint32_t timer_periph, uint16_t aligned);

void timer_counter_up_direction(uint32_t timer_periph);

void timer_counter_down_direction(uint32_t timer_periph);

void timer_prescaler_config(uint32_t timer_periph, uint16_t prescaler, uint8_t pscreload);

void timer_repetition_value_config(uint32_t timer_periph, uint16_t repetition);

void timer_autoreload_value_config(uint32_t timer_periph, uint32_t autoreload);

void timer_counter_value_config(uint32_t timer_periph , uint32_t counter);

uint32_t timer_counter_read(uint32_t timer_periph);

uint16_t timer_prescaler_read(uint32_t timer_periph);

void timer_single_pulse_mode_config(uint32_t timer_periph, uint32_t spmode);

void timer_update_source_config(uint32_t timer_periph, uint32_t update);

void timer_ocpre_clear_source_config(uint32_t timer_periph, uint8_t ocpreclear);



void timer_dma_enable(uint32_t timer_periph, uint16_t dma);

void timer_dma_disable(uint32_t timer_periph, uint16_t dma);

void timer_channel_dma_request_source_select(uint32_t timer_periph, uint8_t dma_request);

void timer_dma_transfer_config(uint32_t timer_periph,uint32_t dma_baseaddr, uint32_t dma_lenth);

void timer_event_software_generate(uint32_t timer_periph, uint16_t event);



void timer_break_struct_para_init(timer_break_parameter_struct* breakpara);

void timer_break_config(uint32_t timer_periph, timer_break_parameter_struct* breakpara);

void timer_break_enable(uint32_t timer_periph);

void timer_break_disable(uint32_t timer_periph);

void timer_automatic_output_enable(uint32_t timer_periph);

void timer_automatic_output_disable(uint32_t timer_periph);

void timer_primary_output_config(uint32_t timer_periph, ControlStatus newvalue);

void timer_channel_control_shadow_config(uint32_t timer_periph, ControlStatus newvalue);

void timer_channel_control_shadow_update_config(uint32_t timer_periph, uint8_t ccuctl);



void timer_channel_output_struct_para_init(timer_oc_parameter_struct* ocpara);

void timer_channel_output_config(uint32_t timer_periph,uint16_t channel, timer_oc_parameter_struct* ocpara);

void timer_channel_output_mode_config(uint32_t timer_periph, uint16_t channel,uint16_t ocmode);

void timer_channel_output_pulse_value_config(uint32_t timer_periph, uint16_t channel, uint32_t pulse);

void timer_channel_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow);

void timer_channel_output_fast_config(uint32_t timer_periph, uint16_t channel, uint16_t ocfast);

void timer_channel_output_clear_config(uint32_t timer_periph,uint16_t channel,uint16_t occlear);

void timer_channel_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocpolarity);

void timer_channel_complementary_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnpolarity);

void timer_channel_output_state_config(uint32_t timer_periph, uint16_t channel, uint32_t state);

void timer_channel_complementary_output_state_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnstate);



void timer_channel_input_struct_para_init(timer_ic_parameter_struct* icpara);

void timer_input_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct* icpara);

void timer_channel_input_capture_prescaler_config(uint32_t timer_periph, uint16_t channel, uint16_t prescaler);

uint32_t timer_channel_capture_value_register_read(uint32_t timer_periph, uint16_t channel);

void timer_input_pwm_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct* icpwm);

void timer_hall_mode_config(uint32_t timer_periph, uint32_t hallmode);



void timer_input_trigger_source_select(uint32_t timer_periph, uint32_t intrigger);

void timer_master_output_trigger_source_select(uint32_t timer_periph, uint32_t outrigger);

void timer_slave_mode_select(uint32_t timer_periph,uint32_t slavemode);

void timer_master_slave_mode_config(uint32_t timer_periph, uint32_t masterslave);

void timer_external_trigger_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);

void timer_quadrature_decoder_mode_config(uint32_t timer_periph, uint32_t decomode, uint16_t ic0polarity, uint16_t ic1polarity);

void timer_internal_clock_config(uint32_t timer_periph);

void timer_internal_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t intrigger);

void timer_external_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t extrigger, uint16_t extpolarity,uint32_t extfilter);

void timer_external_clock_mode0_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);

void timer_external_clock_mode1_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);

void timer_external_clock_mode1_disable(uint32_t timer_periph);

void timer_channel_remap_config(uint32_t timer_periph,uint32_t remap);



void timer_write_chxval_register_config(uint32_t timer_periph, uint16_t ccsel);

void timer_output_value_selection_config(uint32_t timer_periph, uint16_t outsel);



void timer_interrupt_enable(uint32_t timer_periph, uint32_t interrupt);

void timer_interrupt_disable(uint32_t timer_periph, uint32_t interrupt);

FlagStatus timer_interrupt_flag_get(uint32_t timer_periph, uint32_t interrupt);

void timer_interrupt_flag_clear(uint32_t timer_periph, uint32_t interrupt);

FlagStatus timer_flag_get(uint32_t timer_periph, uint32_t flag);

void timer_flag_clear(uint32_t timer_periph, uint32_t flag);
# 57 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_usart.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_usart.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_usart.h" 2
# 220 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_usart.h"
typedef enum{

    USART_FLAG_REA = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(22U)),
    USART_FLAG_TEA = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(21U)),
    USART_FLAG_WU = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(20U)),
    USART_FLAG_RWU = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(19U)),
    USART_FLAG_SB = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(18U)),
    USART_FLAG_AM = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(17U)),
    USART_FLAG_BSY = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(16U)),
    USART_FLAG_ABD = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(15U)),
    USART_FLAG_ABDE = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(14U)),
    USART_FLAG_EB = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(12U)),
    USART_FLAG_RT = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(11U)),
    USART_FLAG_CTS = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(10U)),
    USART_FLAG_CTSF = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(9U)),
    USART_FLAG_LBD = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(8U)),
    USART_FLAG_TBE = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(7U)),
    USART_FLAG_TC = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(6U)),
    USART_FLAG_RBNE = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(5U)),
    USART_FLAG_IDLE = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(4U)),
    USART_FLAG_ORERR = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(3U)),
    USART_FLAG_NERR = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(2U)),
    USART_FLAG_FERR = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(1U)),
    USART_FLAG_PERR = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(0U)),

    USART_FLAG_EPERR = (((uint32_t)(0x000000C0U) << 6) | (uint32_t)(8U)),

    USART_FLAG_RFFINT = (((uint32_t)(0x000000D0U) << 6) | (uint32_t)(15U)),
    USART_FLAG_RFF = (((uint32_t)(0x000000D0U) << 6) | (uint32_t)(11U)),
    USART_FLAG_RFE = (((uint32_t)(0x000000D0U) << 6) | (uint32_t)(10U)),
}usart_flag_enum;


typedef enum
{

    USART_INT_FLAG_EB = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((12U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(27U))),
    USART_INT_FLAG_RT = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((11U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(26U))),
    USART_INT_FLAG_AM = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((17U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(14U))),
    USART_INT_FLAG_PERR = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((0U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(8U))),
    USART_INT_FLAG_TBE = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((7U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(7U))),
    USART_INT_FLAG_TC = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((6U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(6U))),
    USART_INT_FLAG_RBNE = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((5U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(5U))),
    USART_INT_FLAG_RBNE_ORERR = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((3U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(5U))),
    USART_INT_FLAG_IDLE = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((4U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(4U))),

    USART_INT_FLAG_LBD = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((8U) << 16) | (((uint32_t)(0x00000004U) << 6) | (uint32_t)(6U))),

    USART_INT_FLAG_WU = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((20U) << 16) | (((uint32_t)(0x00000008U) << 6) | (uint32_t)(22U))),
    USART_INT_FLAG_CTS = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((9U) << 16) | (((uint32_t)(0x00000008U) << 6) | (uint32_t)(10U))),
    USART_INT_FLAG_ERR_NERR = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((2U) << 16) | (((uint32_t)(0x00000008U) << 6) | (uint32_t)(0U))),
    USART_INT_FLAG_ERR_ORERR = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((3U) << 16) | (((uint32_t)(0x00000008U) << 6) | (uint32_t)(0U))),
    USART_INT_FLAG_ERR_FERR = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((1U) << 16) | (((uint32_t)(0x00000008U) << 6) | (uint32_t)(0U))),

    USART_INT_FLAG_RFF = (((uint32_t)(0x000000D0U) << 22) | (uint32_t)((15U) << 16) | (((uint32_t)(0x000000D0U) << 6) | (uint32_t)(9U))),
}usart_interrupt_flag_enum;


typedef enum
{

    USART_INT_EB = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(27U)),
    USART_INT_RT = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(26U)),
    USART_INT_AM = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(14U)),
    USART_INT_PERR = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(8U)),
    USART_INT_TBE = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(7U)),
    USART_INT_TC = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(6U)),
    USART_INT_RBNE = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(5U)),
    USART_INT_IDLE = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(4U)),

    USART_INT_LBD = (((uint32_t)(0x00000004U) << 6) | (uint32_t)(6U)),

    USART_INT_WU = (((uint32_t)(0x00000008U) << 6) | (uint32_t)(22U)),
    USART_INT_CTS = (((uint32_t)(0x00000008U) << 6) | (uint32_t)(10U)),
    USART_INT_ERR = (((uint32_t)(0x00000008U) << 6) | (uint32_t)(0U)),

    USART_INT_RFF = (((uint32_t)(0x000000D0U) << 6) | (uint32_t)(9U)),
}usart_interrupt_enum;


typedef enum {

    USART_DINV_ENABLE,
    USART_DINV_DISABLE,

    USART_TXPIN_ENABLE,
    USART_TXPIN_DISABLE,

    USART_RXPIN_ENABLE,
    USART_RXPIN_DISABLE,

    USART_SWAP_ENABLE,
    USART_SWAP_DISABLE,
}usart_invert_enum;
# 437 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_usart.h"
void usart_deinit(uint32_t usart_periph);

void usart_baudrate_set(uint32_t usart_periph, uint32_t baudval);

void usart_parity_config(uint32_t usart_periph, uint32_t paritycfg);

void usart_word_length_set(uint32_t usart_periph, uint32_t wlen);

void usart_stop_bit_set(uint32_t usart_periph, uint32_t stblen);

void usart_enable(uint32_t usart_periph);

void usart_disable(uint32_t usart_periph);

void usart_transmit_config(uint32_t usart_periph, uint32_t txconfig);

void usart_receive_config(uint32_t usart_periph, uint32_t rxconfig);



void usart_data_first_config(uint32_t usart_periph, uint32_t msbf);

void usart_invert_config(uint32_t usart_periph, usart_invert_enum invertpara);

void usart_overrun_enable(uint32_t usart_periph);

void usart_overrun_disable(uint32_t usart_periph);

void usart_oversample_config(uint32_t usart_periph, uint32_t oversamp);

void usart_sample_bit_config(uint32_t usart_periph, uint32_t osb);

void usart_receiver_timeout_enable(uint32_t usart_periph);

void usart_receiver_timeout_disable(uint32_t usart_periph);

void usart_receiver_timeout_threshold_config(uint32_t usart_periph, uint32_t rtimeout);

void usart_data_transmit(uint32_t usart_periph, uint32_t data);

uint16_t usart_data_receive(uint32_t usart_periph);



void usart_autobaud_detection_enable(uint32_t usart_periph);

void usart_autobaud_detection_disable(uint32_t usart_periph);

void usart_autobaud_detection_mode_config(uint32_t usart_periph, uint32_t abdmod);



void usart_address_config(uint32_t usart_periph, uint8_t addr);

void usart_address_detection_mode_config(uint32_t usart_periph, uint32_t addmod);

void usart_mute_mode_enable(uint32_t usart_periph);

void usart_mute_mode_disable(uint32_t usart_periph);

void usart_mute_mode_wakeup_config(uint32_t usart_periph, uint32_t wmethod);



void usart_lin_mode_enable(uint32_t usart_periph);

void usart_lin_mode_disable(uint32_t usart_periph);

void usart_lin_break_detection_length_config(uint32_t usart_periph, uint32_t lblen);



void usart_halfduplex_enable(uint32_t usart_periph);

void usart_halfduplex_disable(uint32_t usart_periph);



void usart_clock_enable(uint32_t usart_periph);

void usart_clock_disable(uint32_t usart_periph);

void usart_synchronous_clock_config(uint32_t usart_periph, uint32_t clen, uint32_t cph, uint32_t cpl);



void usart_guard_time_config(uint32_t usart_periph, uint32_t guat);

void usart_smartcard_mode_enable(uint32_t usart_periph);

void usart_smartcard_mode_disable(uint32_t usart_periph);

void usart_smartcard_mode_nack_enable(uint32_t usart_periph);

void usart_smartcard_mode_nack_disable(uint32_t usart_periph);

void usart_smartcard_mode_early_nack_enable(uint32_t usart_periph);

void usart_smartcard_mode_early_nack_disable(uint32_t usart_periph);

void usart_smartcard_autoretry_config(uint32_t usart_periph, uint32_t scrtnum);

void usart_block_length_config(uint32_t usart_periph, uint32_t bl);



void usart_irda_mode_enable(uint32_t usart_periph);

void usart_irda_mode_disable(uint32_t usart_periph);

void usart_prescaler_config(uint32_t usart_periph, uint32_t psc);

void usart_irda_lowpower_config(uint32_t usart_periph, uint32_t irlp);



void usart_hardware_flow_rts_config(uint32_t usart_periph, uint32_t rtsconfig);

void usart_hardware_flow_cts_config(uint32_t usart_periph, uint32_t ctsconfig);



void usart_hardware_flow_coherence_config(uint32_t usart_periph, uint32_t hcm);


void usart_rs485_driver_enable(uint32_t usart_periph);

void usart_rs485_driver_disable(uint32_t usart_periph);

void usart_driver_assertime_config(uint32_t usart_periph, uint32_t deatime);

void usart_driver_deassertime_config(uint32_t usart_periph, uint32_t dedtime);

void usart_depolarity_config(uint32_t usart_periph, uint32_t dep);



void usart_dma_receive_config(uint32_t usart_periph, uint32_t dmacmd);

void usart_dma_transmit_config(uint32_t usart_periph, uint32_t dmacmd);

void usart_reception_error_dma_disable(uint32_t usart_periph);

void usart_reception_error_dma_enable(uint32_t usart_periph);


void usart_wakeup_enable(uint32_t usart_periph);

void usart_wakeup_disable(uint32_t usart_periph);

void usart_wakeup_mode_config(uint32_t usart_periph, uint32_t wum);



void usart_receive_fifo_enable(uint32_t usart_periph);

void usart_receive_fifo_disable(uint32_t usart_periph);

uint8_t usart_receive_fifo_counter_number(uint32_t usart_periph);



FlagStatus usart_flag_get(uint32_t usart_periph, usart_flag_enum flag);

void usart_flag_clear(uint32_t usart_periph, usart_flag_enum flag);

void usart_interrupt_enable(uint32_t usart_periph, usart_interrupt_enum interrupt);

void usart_interrupt_disable(uint32_t usart_periph, usart_interrupt_enum interrupt);

void usart_command_enable(uint32_t usart_periph, uint32_t cmdtype);

FlagStatus usart_interrupt_flag_get(uint32_t usart_periph, usart_interrupt_flag_enum int_flag);

void usart_interrupt_flag_clear(uint32_t usart_periph, usart_interrupt_flag_enum int_flag);
# 58 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_wwdgt.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_wwdgt.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_wwdgt.h" 2
# 71 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_wwdgt.h"
void wwdgt_deinit(void);

void wwdgt_enable(void);


void wwdgt_counter_update(uint16_t counter_value);

void wwdgt_config(uint16_t counter, uint16_t window, uint32_t prescaler);


void wwdgt_interrupt_enable(void);

FlagStatus wwdgt_flag_get(void);

void wwdgt_flag_clear(void);
# 59 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_misc.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_misc.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 41 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_misc.h" 2
# 75 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_misc.h"
void nvic_priority_group_set(uint32_t nvic_prigroup);


void nvic_irq_enable(uint8_t nvic_irq, uint8_t nvic_irq_pre_priority, uint8_t nvic_irq_sub_priority);

void nvic_irq_disable(uint8_t nvic_irq);

void nvic_system_reset(void);


void nvic_vector_table_set(uint32_t nvic_vict_tab, uint32_t offset);


void system_lowpower_set(uint8_t lowpower_mode);

void system_lowpower_reset(uint8_t lowpower_mode);


void systick_clksource_set(uint32_t systick_clksource);
# 60 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 1 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_cmp.h" 1
# 39 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_cmp.h"
# 1 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 1
# 40 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_cmp.h" 2
# 70 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_cmp.h"
typedef enum
{
    CMP_HIGHSPEED = 0,
    CMP_MIDDLESPEED,
    CMP_LOWSPEED,
    CMP_VERYLOWSPEED
}operating_mode_enum;


typedef enum
{
    CMP_1_4VREFINT = 0,
    CMP_1_2VREFINT,
    CMP_3_4VREFINT,
    CMP_VREFINT,
    CMP_PA4_PA6,
    CMP_PA5_PA7,
    CMP_PA0,
    CMP_PA2
}inverting_input_enum;


typedef enum
{
    CMP_HYSTERESIS_NO = 0,
    CMP_HYSTERESIS_LOW,
    CMP_HYSTERESIS_MIDDLE,
    CMP_HYSTERESIS_HIGH
}cmp_hysteresis_enum;


typedef enum
{
    CMP_OUTPUT_NONE = 0,
    CMP_OUTPUT_TIMER0BKIN,
    CMP_OUTPUT_TIMER0IC0,
    CMP_OUTPUT_TIMER0OCPRECLR,
    CMP_OUTPUT_TIMER1IC3,
    CMP_OUTPUT_TIMER1OCPRECLR,
    CMP_OUTPUT_TIMER2IC0,
    CMP_OUTPUT_TIMER2OCPRECLR
}cmp_output_enum;
# 199 "../../mcu/GDE501_fireware/Firmware/GD32E501_standard_peripheral/Include\\gd32e501_cmp.h"
void cmp_deinit(void);

void cmp_mode_init(uint32_t cmp_periph, operating_mode_enum operating_mode, inverting_input_enum inverting_input, cmp_hysteresis_enum output_hysteresis);

void cmp_output_init(uint32_t cmp_periph, cmp_output_enum output_slection, uint32_t output_polarity);



void cmp_enable(uint32_t cmp_periph);

void cmp_disable(uint32_t cmp_periph);

void cmp_switch_enable(void);

void cmp_switch_disable(void);

void cmp_window_enable(void);

void cmp_window_disable(void);

void cmp_lock_enable(uint32_t cmp_periph);



uint32_t cmp_output_level_get(uint32_t cmp_periph);
# 61 "../../mcu/GDE501_fireware\\gd32e501_libopt.h" 2
# 216 "../../mcu/GDE501_fireware/Firmware/CMSIS/GD/GD32E501/Include\\gd32e501.h" 2
# 17 "../../thd_dsp_download_release_V0_0/mailbox_i2c_interface.h" 2
# 1 "../../mcu\\mcu_data_type.h" 1
# 21 "../../mcu\\mcu_data_type.h"
typedef struct _PRINT_BUFFER_CONFIG_
{
 uint8_t idx;
 uint8_t buffer[16];
}PRINT_BUFFER_CONFIG;
# 36 "../../mcu\\mcu_data_type.h"
typedef struct _I2C_ALL_ADDRESS_INFO_
{
 uint8_t reg_size;
 int32_t slave_address;
 uint8_t regaddress[7 + 1];
}I2C_ALL_ADDRESS_INFO;






typedef enum _MCU_NIVC_IRQ_PRIORITY_
{
 I2C_SLAVE_IRQ_ERR_PRI = 0,
 I2C_SLAVE_IRQ_EVENT_PRI = 1,
 I2C_MASTER_IRQ_ERR_PRI = 2,
 I2C_MASTER_IRQ_EVENT_PRI = 3,

 TRIGGER_EXIT15_IRQ_PRI = 4,

}MCU_NIVC_IRQ_PRIORITY;


typedef enum _CRC_CHECK_RESULT_
{
 CRC_NO_DOING = 0,
 CRC_CHECK_OK,
 CRC_CHECK_ERROR,
 CRC_MALLOC_FAIL,
 CRC_NO_END_RESULT
}CRC_CHECK_RESULT;



typedef enum _I2C_DEVICE_ADDRESS_
{

 I2C_8472_A0_ADDR = 0xA0,
 I2C_8472_A2_ADDR = 0xA2,
 I2C_8472_B0_ADDR = 0xB0,
 I2C_8472_B2_ADDR = 0xB2,
 I2C_8472_C0_ADDR = 0xC0,
 I2C_8472_C2_ADDR = 0xC2,

 I2C_8472_MEM_A0_ADDR = 0xD0,
 I2C_8472_MEM_B0_ADDR = 0xE0,
 I2C_8472_MEM_C0_ADDR = 0xF0,
 I2C_8472_MEM_A2_ADDR = 0xD2,
 I2C_8472_MEM_B2_ADDR = 0xE2,
 I2C_8472_MEM_C2_ADDR = 0xE8,


 I2C_FLASH_A8_ADDR = 0xA8,


 I2C_TEC_DEV_ADDR = 0x42,




 I2C_MCU_SPEC_ADDR = 0xCE,
 I2C_OTHER_ADDR = 0xFF

}I2C_DEVICE_ADDRESS;

typedef enum _I2C_8472_A2_REGADDR_
{
 SFF_DDM_REG = 0x60
}I2C_8472_A2_REGADDR;



typedef enum _I2C_MCU_SPECIAL_REGADDR_
{
 TEC_VTEC_CTL_REG = 0x0,
 TEC_AUTO_CTL_REG = 0x1,
 TEC_CTL_TEMP = 0x2,

 TEC_CALC_CTRL_AUTO_REG = 0x4,
 TEC_TEMP_OBJ_CFG_REG = 0x5,
 TEC_PID_PARAM_CFG_REG = 0x6,
 APD_SET_VOLTAGE_REG = 0x7,
 UPGRADE_APP_SOFTWARE_REG = 0x8,
 CMD_OPTICAL_PASSWORD_LIMIT_REG = 0x9,
 TEC_XTEC_VALUE_REG = 0xA,


 UPGRADE_DEV_VERSION_INFO_REG = 0xB,


 UPGRADE_FIRMWARE_REG = 0xC,


 CMD_SOA_ELECTRIC_REG = 0xD,
 CMD_NEG_VOLTAGE_REG = 0xF,


 CMD_MODULE_DDM_INFO_REG = 0x10,


 CMD_DDM_SWITCH_ATUO_PROCESS_REG = 0x12,


 CMD_IBIAS_DRV_LD_REG = 0x13,


 CMD_IMOD_DRV_LD_REG = 0x14,


 CMD_RX_SWING_DRV_LD_REG = 0x15,


 CMD_RX_EQ_DRV_LD_REG = 0x16,


 CMD_TX_LD_CROSS_POINT_ADJUSt_REG = 0x17,


 CMD_TX_LD_DE_EMPH_REG = 0x18,


 CMD_RX_LD_DE_EMPH_REG = 0x19,


 CMD_SIGNAL_DETECT_ASSERT_REG = 0x1A,


 CMD_SIGNAL_DETECT_DE_ASSERT_REG = 0x1B,


 CMD_COMMAND_MAP_REG = 0x1C,


 CMD_UPGRADE_BOOT_SOFTWARE_REG= 0x1D,




 CMD_COMMON_READ_REG = 0x27,


 CMD_OPTICAL_MODULE_CFG_FLASH = 0x28,

 CMD_DDM_50G_MONITOR_REG = 0x29,
 CMD_DSP_TICKS_REG = 0x2A,
 CMD_DSP_FW_VERSION_REG = 0x2B,

 TEST_READ_PRINT_BUFF_REG = 0xEA,
 TEST_ADC_INFO_REG = 0xEB,
 TEST_GPIO_INFO_REG = 0xEC,
 TEST_GPIO_PIN_REG = 0xED,
 TEST_DAC_PIN_REG = 0xEE,


 TEC_OTHER_TEST_REG
}I2C_MCUSPECIAL_REGADDR;
# 251 "../../mcu\\mcu_data_type.h"
typedef struct _DDM_ADC_OUT_VAL_
{
 uint16_t temperature_adc_out;

 uint16_t voltage_adc_out_0;
 uint16_t ibias_adc_out_0;
 uint16_t tx_power_adc_out_0;
 uint16_t rx_power_adc_out_0;

 uint16_t voltage_adc_out_1;
 uint16_t ibias_adc_out_1;
 uint16_t tx_power_adc_out_1;
 uint16_t rx_power_adc_out_1;

 uint16_t voltage_adc_out_2;
 uint16_t ibias_adc_out_2;
 uint16_t tx_power_adc_out_2;
 uint16_t rx_power_adc_out_2;
}DDM_ADC_OUT_VAL;


typedef struct _RSSI_POWER_
{
 uint16_t rssi;
 float power;
}RSSI_POWER;




typedef struct _OM_DEFAULT_CONFIG_
{
 uint8_t rx_deemph_0;
 uint8_t rx_los_threshold_0;
 uint8_t rx_los_hyst_0;
 uint8_t tx_cpa_0;
 uint16_t tx_ibias_0;
 uint16_t tx_imod_0;
 uint16_t tx_deemph_0;
 uint16_t rx_eq_0;
 uint16_t rx_swing_0;
 float tx_soa_0;
 float tx_vea_0;
 float rx_vapd_0;
 float tec_target_temp;
 uint8_t tx_apc_en_0;
 uint16_t tx_apc_target_0;
 float tx_i_slope_0;
 float tx_i_offset_0;
 float tx_pwr_slope_0;
 float tx_pwr_offset_0;
 float rx_pwr_a_0;
 float rx_pwr_b_0;
 float rx_pwr_c_0;

 uint8_t rx_deemph_1;
 uint8_t rx_los_threshold_1;
 uint8_t rx_los_hyst_1;
 uint8_t tx_cpa_1;
 uint16_t tx_ibias_1;
 uint16_t tx_imod_1;
 uint16_t tx_deemph_1;
 uint16_t rx_eq_1;
 uint16_t rx_swing_1;
 float tx_vea_1;
 float rx_vapd_1;
 uint8_t tx_apc_en_1;
 uint16_t tx_apc_target_1;
 float tx_i_slope_1;
 float tx_i_offset_1;
 float tx_pwr_slope_1;
 float tx_pwr_offset_1;
 float rx_pwr_a_1;
 float rx_pwr_b_1;
 float rx_pwr_c_1;

 uint8_t rx_los_threshold_2;
 uint8_t rx_los_hyst_2;
 uint8_t tx_cpa_2;
 uint16_t tx_ibias_2;
 uint16_t tx_imod_2;
 uint16_t rx_swing_2;
 float rx_vapd_2;
 uint8_t tx_apc_en_2;
 uint16_t tx_apc_target_2;
 float tx_i_slope_2;
 float tx_i_offset_2;
 float tx_pwr_slope_2;
 float tx_pwr_offset_2;
 float rx_pwr_a_2;
 float rx_pwr_b_2;
 float rx_pwr_c_2;

}OM_DEFAULT_CONFIG;


typedef enum _MCU_FLASH_CONFIG_VALUE_
{
 TX_IBIAS_VALUE_0_HIGH = 0x00,
 TX_IBIAS_VALUE_0_LOW = 0x01,
 TX_SOA_VALUE_0_HIGH = 0x02,
 TX_SOA_VALUE_0_LOW = 0x03,
 TX_VEA_VALUE_0_HIGH = 0x04,
 TX_VEA_VALUE_0_LOW = 0x05,
 TX_IMOD_VALUE_0_HIGH = 0x06,
 TX_IMOD_VALUE_0_LOW = 0x07,
 TX_CPA_VALUE_0_HIGH = 0x08,
 TX_CPA_VALUE_0_LOW = 0x09,
 TX_DEEMPH_VALUE_0_HIGH = 0x0A,
 TX_DEEMPH_VALUE_0_LOW = 0x0B,
 RX_VAPD_VALUE_0_HIGH = 0x0C,
 RX_VAPD_VALUE_0_LOW = 0x0D,
 RX_EQ_VALUE_0_HIGH = 0x0E,
 RX_EQ_VALUE_0_LOW = 0x0F,
 RX_SWING_VALUE_0_HIGH = 0x10,
 RX_SWING_VALUE_0_LOW = 0x11,
 RX_DEEMPH_VALUE_0_HIGH = 0x12,
 RX_DEEMPH_VALUE_0_LOW = 0x13,
 RX_LOS_THRESHOLD_VALUE_0_HIGH = 0x14,
 RX_LOS_THRESHOLD_VALUE_0_LOW = 0x15,
 RX_LOS_HYST_VALUE_0_HIGH = 0x16,
 RX_LOS_HYST_VALUE_0_LOW = 0x17,
 RX_TEC_TARGET_VALUE_HIGH = 0x18,
 RX_TEC_TARGET_VALUE_LOW = 0x19,

 TX_IBIAS_VALUE_1_HIGH = 0x1A,
 TX_IBIAS_VALUE_1_LOW = 0x1B,
 TX_VEA_VALUE_1_HIGH = 0x1C,
 TX_VEA_VALUE_1_LOW = 0x1D,
 TX_IMOD_VALUE_1_HIGH = 0x1E,
 TX_IMOD_VALUE_1_LOW = 0x1F,
 TX_CPA_VALUE_1_HIGH = 0x20,
 TX_CPA_VALUE_1_LOW = 0x21,
 TX_DEEMPH_VALUE_1_HIGH = 0x22,
 TX_DEEMPH_VALUE_1_LOW = 0x23,
 RX_VAPD_VALUE_1_HIGH = 0x24,
 RX_VAPD_VALUE_1_LOW = 0x25,
 RX_EQ_VALUE_1_HIGH = 0x26,
 RX_EQ_VALUE_1_LOW = 0x27,
 RX_SWING_VALUE_1_HIGH = 0x28,
 RX_SWING_VALUE_1_LOW = 0x29,
 RX_DEEMPH_VALUE_1_HIGH = 0x2A,
 RX_DEEMPH_VALUE_1_LOW = 0x2B,
 RX_LOS_THRESHOLD_VALUE_1_HIGH = 0x2C,
 RX_LOS_THRESHOLD_VALUE_1_LOW = 0x2D,
 RX_LOS_HYST_VALUE_1_HIGH = 0x2E,
 RX_LOS_HYST_VALUE_1_LOW = 0x2F,

 TX_IBIAS_VALUE_2_HIGH = 0x30,
 TX_IBIAS_VALUE_2_LOW = 0x31,
 TX_IMOD_VALUE_2_HIGH = 0x32,
 TX_IMOD_VALUE_2_LOW = 0x33,
 TX_CPA_VALUE_2_HIGH = 0x34,
 TX_CPA_VALUE_2_LOW = 0x35,
 RX_VAPD_VALUE_2_HIGH = 0x36,
 RX_VAPD_VALUE_2_LOW = 0x37,
 RX_SWING_VALUE_2_HIGH = 0x38,
 RX_SWING_VALUE_2_LOW = 0x39,
 RX_LOS_THRESHOLD_VALUE_2_HIGH = 0x3A,
 RX_LOS_THRESHOLD_VALUE_2_LOW = 0x3B,
 RX_LOS_HYST_VALUE_2_HIGH = 0x3C,
 RX_LOS_HYST_VALUE_2_LOW = 0x3D,

 APC_ENABLE_50G_CFG = 0x3E,
 APC_TARGET_VALUE_50G_CFG_HIGH = 0x3F,
 APC_TARGET_VALUE_50G_CFG_LOW = 0x40,
 APC_ENABLE_10G_CFG = 0x41,
 APC_TARGET_VALUE_10G_CFG_HIGH = 0x42,
 APC_TARGET_VALUE_10G_CFG_LOW = 0x43,
 APC_ENABLE_1G_CFG = 0x44,
 APC_TARGET_VALUE_1G_CFG_HIGH = 0x45,
 APC_TARGET_VALUE_1G_CFG_LOW = 0x46,

 TX_I_SLOPE_HIGH_50G = 0x47,
 TX_I_SLOPE_LOW_50G = 0x48,
 TX_I_OFFSET_HIGH_50G = 0x49,
 TX_I_OFFSET_LOW_50G = 0x4A,
 TX_PWR_SLOPE_HIGH_50G = 0x4B,
 TX_PWR_SLOPE_LOW_50G = 0x4C,
 TX_PWR_OFFSET_HIGH_50G = 0x4D,
 TX_PWR_OFFSET_LOW_50G = 0x4E,
 RX_PWR_A_HIGH_50G = 0x4F,
 RX_PWR_A_LOW_50G = 0x50,
 RX_PWR_B_HIGH_50G = 0x51,
 RX_PWR_B_LOW_50G = 0x52,
 RX_PWR_C_HIGH_50G = 0x53,
 RX_PWR_C_LOW_50G = 0x54,

 TX_I_SLOPE_HIGH_10G = 0x55,
 TX_I_SLOPE_LOW_10G = 0x56,
 TX_I_OFFSET_HIGH_10G = 0x57,
 TX_I_OFFSET_LOW_10G = 0x58,
 TX_PWR_SLOPE_HIGH_10G = 0x59,
 TX_PWR_SLOPE_LOW_10G = 0x5A,
 TX_PWR_OFFSET_HIGH_10G = 0x5B,
 TX_PWR_OFFSET_LOW_10G = 0x5C,
 RX_PWR_A_HIGH_10G = 0x5D,
 RX_PWR_A_LOW_10G = 0x5E,
 RX_PWR_B_HIGH_10G = 0x5F,
 RX_PWR_B_LOW_10G = 0x60,
 RX_PWR_C_HIGH_10G = 0x61,
 RX_PWR_C_LOW_10G = 0x62,

 TX_I_SLOPE_HIGH_1G = 0x63,
 TX_I_SLOPE_LOW_1G = 0x64,
 TX_I_OFFSET_HIGH_1G = 0x65,
 TX_I_OFFSET_LOW_1G = 0x66,
 TX_PWR_SLOPE_HIGH_1G = 0x67,
 TX_PWR_SLOPE_LOW_1G = 0x68,
 TX_PWR_OFFSET_HIGH_1G = 0x69,
 TX_PWR_OFFSET_LOW_1G = 0x6A,
 RX_PWR_A_HIGH_1G = 0x6B,
 RX_PWR_A_LOW_1G = 0x6C,
 RX_PWR_B_HIGH_1G = 0x6D,
 RX_PWR_B_LOW_1G = 0x6E,
 RX_PWR_C_HIGH_1G = 0x6F,
 RX_PWR_C_LOW_1G = 0x70,
 TT1_TMP = 0x71,
 TT2_TMP = 0x72,
 TT3_TMP = 0x73,
 TT4_TMP = 0x74,
 TT5_TMP = 0x75,
 TT6_TMP = 0x76,
 TT7_TMP = 0x77,




 FLASH_CONFIG_LENGTH
}MCU_FLASH_CONFIG_VALUE;



typedef enum _SFF_MODULE_TYPE_
{
 SFF_50G_TYPE = 0,
 SFF_10G_TYPE = 1,
 SFF_1G_TYPE = 2

}SFF_MODULE_TYPE;

typedef enum _CMD_COMMON_EX_
{
 CFG_SAVE_FLASH_EX = 0,
 CFG_CLEAR_FLASH_EX = 1,
 APC_AUTO_ENABLE_EX = 2,
 APC_IPHOTO_RATE_EX = 3,
 APC_TARGET_VALUE_EX = 4,
 CALIBRATION_TX_I_50G_CONFIG = 5,
 CALIBRATION_TX_PWR_50G_CONFIG = 6,
 CALIBRATION_RX_PWR_50G_CONFIG = 7,
 CALIBRATION_TX_I_10G_CONFIG = 8,
 CALIBRATION_TX_PWR_10G_CONFIG = 9,
 CALIBRATION_RX_PWR_10G_CONFIG = 10,
 CALIBRATION_TX_I_1G_CONFIG = 11,
 CALIBRATION_TX_PWR_1G_CONFIG = 12,
 CALIBRATION_RX_PWR_1G_CONFIG = 13

}CMD_COMMON_EX;
# 18 "../../thd_dsp_download_release_V0_0/mailbox_i2c_interface.h" 2
# 1 "../../mcu\\mcu_system_comm.h" 1
# 31 "../../mcu\\mcu_system_comm.h"
# 1 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 1 3
# 53 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    typedef unsigned int size_t;
# 68 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    typedef __builtin_va_list __va_list;
# 87 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
typedef struct __fpos_t_struct {
    unsigned long long int __pos;





    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
# 108 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
typedef struct __FILE FILE;
# 119 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
struct __FILE {
    union {
        long __FILE_alignment;



        char __FILE_size[84];

    } __FILE_opaque;
};
# 138 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;
# 224 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int remove(const char * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int rename(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 243 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *tmpfile(void);






extern __attribute__((__nothrow__)) char *tmpnam(char * );
# 265 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fclose(FILE * ) __attribute__((__nonnull__(1)));
# 275 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fflush(FILE * );
# 285 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *fopen(const char * __restrict ,
                           const char * __restrict ) __attribute__((__nonnull__(1,2)));
# 329 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *freopen(const char * __restrict ,
                    const char * __restrict ,
                    FILE * __restrict ) __attribute__((__nonnull__(2,3)));
# 342 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void setbuf(FILE * __restrict ,
                    char * __restrict ) __attribute__((__nonnull__(1)));






extern __attribute__((__nothrow__)) int setvbuf(FILE * __restrict ,
                   char * __restrict ,
                   int , size_t ) __attribute__((__nonnull__(1)));
# 370 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int fprintf(FILE * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 393 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int _fprintf(FILE * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));





#pragma __printf_args
extern __attribute__((__nothrow__)) int printf(const char * __restrict , ...) __attribute__((__nonnull__(1)));






#pragma __printf_args
extern __attribute__((__nothrow__)) int _printf(const char * __restrict , ...) __attribute__((__nonnull__(1)));





#pragma __printf_args
extern __attribute__((__nothrow__)) int sprintf(char * __restrict , const char * __restrict , ...) __attribute__((__nonnull__(1,2)));








#pragma __printf_args
extern __attribute__((__nothrow__)) int _sprintf(char * __restrict , const char * __restrict , ...) __attribute__((__nonnull__(1,2)));






#pragma __printf_args
extern __attribute__((__nothrow__)) int __ARM_snprintf(char * __restrict , size_t ,
                     const char * __restrict , ...) __attribute__((__nonnull__(3)));


#pragma __printf_args
extern __attribute__((__nothrow__)) int snprintf(char * __restrict , size_t ,
                     const char * __restrict , ...) __attribute__((__nonnull__(3)));
# 460 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int _snprintf(char * __restrict , size_t ,
                      const char * __restrict , ...) __attribute__((__nonnull__(3)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int fscanf(FILE * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 503 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __scanf_args
extern __attribute__((__nothrow__)) int _fscanf(FILE * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int scanf(const char * __restrict , ...) __attribute__((__nonnull__(1)));








#pragma __scanf_args
extern __attribute__((__nothrow__)) int _scanf(const char * __restrict , ...) __attribute__((__nonnull__(1)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int sscanf(const char * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 541 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __scanf_args
extern __attribute__((__nothrow__)) int _sscanf(const char * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));







extern __attribute__((__nothrow__)) int vfscanf(FILE * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int vscanf(const char * __restrict , __va_list) __attribute__((__nonnull__(1)));
extern __attribute__((__nothrow__)) int vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));

extern __attribute__((__nothrow__)) int _vfscanf(FILE * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int _vscanf(const char * __restrict , __va_list) __attribute__((__nonnull__(1)));
extern __attribute__((__nothrow__)) int _vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int __ARM_vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));

extern __attribute__((__nothrow__)) int vprintf(const char * __restrict , __va_list ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int _vprintf(const char * __restrict , __va_list ) __attribute__((__nonnull__(1)));





extern __attribute__((__nothrow__)) int vfprintf(FILE * __restrict ,
                    const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));
# 584 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int vsprintf(char * __restrict ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));
# 594 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int __ARM_vsnprintf(char * __restrict , size_t ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));

extern __attribute__((__nothrow__)) int vsnprintf(char * __restrict , size_t ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));
# 609 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int _vsprintf(char * __restrict ,
                      const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));





extern __attribute__((__nothrow__)) int _vfprintf(FILE * __restrict ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));





extern __attribute__((__nothrow__)) int _vsnprintf(char * __restrict , size_t ,
                      const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));
# 635 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int __ARM_asprintf(char ** , const char * __restrict , ...) __attribute__((__nonnull__(2)));
extern __attribute__((__nothrow__)) int __ARM_vasprintf(char ** , const char * __restrict , __va_list ) __attribute__((__nonnull__(2)));
# 649 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fgetc(FILE * ) __attribute__((__nonnull__(1)));
# 659 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) char *fgets(char * __restrict , int ,
                    FILE * __restrict ) __attribute__((__nonnull__(1,3)));
# 673 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fputc(int , FILE * ) __attribute__((__nonnull__(2)));
# 683 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fputs(const char * __restrict , FILE * __restrict ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) int getc(FILE * ) __attribute__((__nonnull__(1)));
# 704 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    extern __attribute__((__nothrow__)) int (getchar)(void);
# 713 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) char *gets(char * ) __attribute__((__nonnull__(1)));
# 725 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int putc(int , FILE * ) __attribute__((__nonnull__(2)));
# 737 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    extern __attribute__((__nothrow__)) int (putchar)(int );






extern __attribute__((__nothrow__)) int puts(const char * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int ungetc(int , FILE * ) __attribute__((__nonnull__(2)));
# 778 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t fread(void * __restrict ,
                    size_t , size_t , FILE * __restrict ) __attribute__((__nonnull__(1,4)));
# 794 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t __fread_bytes_avail(void * __restrict ,
                    size_t , FILE * __restrict ) __attribute__((__nonnull__(1,3)));
# 810 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t fwrite(const void * __restrict ,
                    size_t , size_t , FILE * __restrict ) __attribute__((__nonnull__(1,4)));
# 822 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fgetpos(FILE * __restrict , fpos_t * __restrict ) __attribute__((__nonnull__(1,2)));
# 833 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fseek(FILE * , long int , int ) __attribute__((__nonnull__(1)));
# 850 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fsetpos(FILE * __restrict , const fpos_t * __restrict ) __attribute__((__nonnull__(1,2)));
# 863 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) long int ftell(FILE * ) __attribute__((__nonnull__(1)));
# 877 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void rewind(FILE * ) __attribute__((__nonnull__(1)));
# 886 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void clearerr(FILE * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int feof(FILE * ) __attribute__((__nonnull__(1)));




extern __attribute__((__nothrow__)) int ferror(FILE * ) __attribute__((__nonnull__(1)));




extern __attribute__((__nothrow__)) void perror(const char * );
# 917 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int _fisatty(FILE * ) __attribute__((__nonnull__(1)));



extern __attribute__((__nothrow__)) void __use_no_semihosting_swi(void);
extern __attribute__((__nothrow__)) void __use_no_semihosting(void);
# 32 "../../mcu\\mcu_system_comm.h" 2
# 47 "../../mcu\\mcu_system_comm.h"
void fh_delay_ms(uint32_t ms);
# 61 "../../mcu\\mcu_system_comm.h"
void fh_delay_us(uint32_t us);
# 78 "../../mcu\\mcu_system_comm.h"
void system_delay_ms(uint32_t ms);
# 93 "../../mcu\\mcu_system_comm.h"
uint32_t system_get_current_ticks();


void flash_read(uint8_t *outputdata,uint32_t addr_start,uint16_t data_len);


int32_t flash_write(uint8_t *inputdata,uint32_t addr_start,uint16_t data_len);







void fmc_erase_single_page(uint32_t start_addr);
# 124 "../../mcu\\mcu_system_comm.h"
uint8_t search_bisection_temp_by_adc(uint16_t adc_value,
   uint16_t* tec_table,
   uint16_t tec_count,
   uint8_t scale,
   uint32_t* temp);
# 144 "../../mcu\\mcu_system_comm.h"
void set_u16( uint8_t *buf, uint16_t val);
# 159 "../../mcu\\mcu_system_comm.h"
uint16_t get_u16(uint8_t * pVal);
# 174 "../../mcu\\mcu_system_comm.h"
void set_u32(uint8_t *buf, uint32_t val);
# 188 "../../mcu\\mcu_system_comm.h"
uint32_t get_u32(uint8_t *pVal);
# 19 "../../thd_dsp_download_release_V0_0/mailbox_i2c_interface.h" 2
# 1 "../../mcu\\mcu_global_vars_param.h" 1





typedef struct _GLOBAL_VARS_PARAM_
{

 uint8_t g_update_process_flag;
 uint8_t g_50g_ddm_sw_auto_process_flag;

 uint8_t g_10g_ddm_sw_auto_process_flag;

 uint8_t g_1g_ddm_sw_auto_process_flag;

 uint8_t g_ddm_sw_auto_process_flag;


    uint32_t g_trigger_count;


 uint32_t g_sys_tick_period;


 uint32_t g_tec_pid_calc_ms_task;


 uint32_t g_ddm_process_ms_task;


 uint32_t g_check_print_ms_task;

    uint32_t g_dsp_fw_ticks_ret;
    uint32_t g_dsp_fw_version_ret;
    uint8_t g_dsp_ticks_array[12];
    uint8_t g_dsp_version_array[24];

}GLOBAL_VARS_PARAM __attribute__((aligned(4)));


extern volatile GLOBAL_VARS_PARAM g_mcu_vars_param;
# 81 "../../mcu\\mcu_global_vars_param.h"
void global_vars_param_init();
# 20 "../../thd_dsp_download_release_V0_0/mailbox_i2c_interface.h" 2

void mailbox_i2c_dsp_ticks_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen);

void mailbox_i2c_dsp_fw_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen);
# 3 "../../thd_dsp_download_release_V0_0/mailbox_i2c_interface.c" 2
# 1 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 1 3
# 58 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) void *memcpy(void * __restrict ,
                    const void * __restrict , size_t ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) void *memmove(void * ,
                    const void * , size_t ) __attribute__((__nonnull__(1,2)));
# 77 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strcpy(char * __restrict , const char * __restrict ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) char *strncpy(char * __restrict , const char * __restrict , size_t ) __attribute__((__nonnull__(1,2)));
# 93 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strcat(char * __restrict , const char * __restrict ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) char *strncat(char * __restrict , const char * __restrict , size_t ) __attribute__((__nonnull__(1,2)));
# 117 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) int memcmp(const void * , const void * , size_t ) __attribute__((__nonnull__(1,2)));







extern __attribute__((__nothrow__)) int strcmp(const char * , const char * ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) int strncmp(const char * , const char * , size_t ) __attribute__((__nonnull__(1,2)));
# 141 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) int strcasecmp(const char * , const char * ) __attribute__((__nonnull__(1,2)));







extern __attribute__((__nothrow__)) int strncasecmp(const char * , const char * , size_t ) __attribute__((__nonnull__(1,2)));
# 158 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) int strcoll(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 169 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) size_t strxfrm(char * __restrict , const char * __restrict , size_t ) __attribute__((__nonnull__(2)));
# 193 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) void *memchr(const void * , int , size_t ) __attribute__((__nonnull__(1)));
# 209 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strchr(const char * , int ) __attribute__((__nonnull__(1)));
# 218 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) size_t strcspn(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 232 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strpbrk(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 247 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strrchr(const char * , int ) __attribute__((__nonnull__(1)));
# 257 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) size_t strspn(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 270 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strstr(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 280 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) char *strtok(char * __restrict , const char * __restrict ) __attribute__((__nonnull__(2)));
extern __attribute__((__nothrow__)) char *_strtok_r(char * , const char * , char ** ) __attribute__((__nonnull__(2,3)));
# 321 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) void *memset(void * , int , size_t ) __attribute__((__nonnull__(1)));





extern __attribute__((__nothrow__)) char *strerror(int );







extern __attribute__((__nothrow__)) size_t strlen(const char * ) __attribute__((__nonnull__(1)));






extern __attribute__((__nothrow__)) size_t strlcpy(char * , const char * , size_t ) __attribute__((__nonnull__(1,2)));
# 362 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) size_t strlcat(char * , const char * , size_t ) __attribute__((__nonnull__(1,2)));
# 388 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\string.h" 3
extern __attribute__((__nothrow__)) void _membitcpybl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitcpybb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitcpyhl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitcpyhb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitcpywl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitcpywb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovebl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovebb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovehl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovehb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovewl(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) void _membitmovewb(void * , const void * , int , int , size_t ) __attribute__((__nonnull__(1,2)));
# 4 "../../thd_dsp_download_release_V0_0/mailbox_i2c_interface.c" 2

void mailbox_i2c_dsp_ticks_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
 uint32_t value = 0;
    uint32_t idx = 0;
    uint32_t i = 0;



 if(0 == pbuff)
 {
  return;
 }

 set_u32(pbuff,g_mcu_vars_param.g_dsp_fw_ticks_ret);
    idx += 4;

    for(i = 0; i < 8;i++)
    {
        pbuff[idx + i] = g_mcu_vars_param.g_dsp_ticks_array[i];
    }

 return;
}

void mailbox_i2c_dsp_fw_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
 uint32_t value = 0;
    uint32_t idx = 0;
    uint32_t i = 0;



 if(0 == pbuff)
 {
  return;
 }

 set_u32(pbuff,g_mcu_vars_param.g_dsp_fw_version_ret);
    idx += 4;

    for(i = 0; i < 18;i++)
    {

        pbuff[idx + i] = g_mcu_vars_param.g_dsp_version_array[i];
    }

 return;
}

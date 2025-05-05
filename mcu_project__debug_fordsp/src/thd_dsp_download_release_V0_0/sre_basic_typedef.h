/* 
 * typedef for different language style
 * Copyright 2022-2022 Tauren Semiconductor.
 * Create data: 2022-7-20
 * auther:
 */
#ifndef _SRE_BASIC_TYPEDEF_H_
#define _SRE_BASIC_TYPEDEF_H_

#include "stdint.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef unsigned char UINT8;
typedef signed char INT8;
typedef unsigned short UINT16;
typedef char CHAR;
typedef short INT16;
typedef unsigned int UINT32;
typedef int INT32;
typedef long long INT64;
typedef unsigned long long UINT64;
typedef uintptr_t UINTPTR;
typedef void VOID;
typedef char SRE_BOOL;
typedef double DOUBLE;
typedef float FLOAT;
#define RW
#define RO
#define RW
#define WC
#define WP
#define SRE_YES  1
#define SRE_NO   0
#define SRE_TRUE 1
#define SRE_FALSE 0
#define UINT8_INVALID  0xFF
#define UINT16_INVALID  0xFFFF
#define UINT32_INVALID  0xFFFFFFFF
#define SRE_ENABLE 1
#define SRE_DISABLE 0
#ifndef NULL
#define NULL ((VOID *)0)
#endif
#define SRE_SUCCESS (UINT32)0
#define SRE_FAIL    (UINT32)1

#define CHIP_IS_BCDRV100     0
#define CHIP_IS_DSPV100      1
#define CHIP_IS_BCDR201V100  2
#define CHIP_IS_BCDRHS       3

#if (CHIP_TYPE == CHIP_IS_DSPV100)
#define CHIP_IS_DSP          SRE_YES
#define CHIP_IS_BCDR         SRE_NO
#endif

#if ((CHIP_TYPE == CHIP_IS_BCDRV100) || (CHIP_TYPE == CHIP_IS_BCDR201V100) || (CHIP_TYPE == CHIP_IS_BCDRHS))
#define CHIP_IS_DSP          SRE_NO
#define CHIP_IS_BCDR         SRE_YES
#endif

#define DSP_50GPAM4_SOFT CHIP_IS_DSP
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

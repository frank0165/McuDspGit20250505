/* 
 * def for different language style and func
 * Copyright 2022-2022 Tauren Semiconductor.
 * Create data: 2022-7-20
 * auther:
 */
#ifndef _SRE_BASIC_DEF_H_
#define _SRE_BASIC_DEF_H_

#include "sre_basic_typedef.h"
#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define DIV_U64_REM(x, y, r) *(r)=(((UINT64)(x))%(y))
#define DIV_U64(x, y) ((UINT64)(x)/(UINT64)(y))
#define DIV_S64(x, y) ((INT64)(x)/(INT64)(y))
#define UINT16_LSB_UINT8(data)   (UINT8)((data) & 0xff)
#define UINT16_MSB_UINT8(data)   (UINT8)(((data) >> 8) & 0xff)
#define TR_GET_BYTE(w, p) (UINT8)(((w) >> (p)) & 0xFF)
#define TR_POW2_48   ((UINT64)1u << 48)
#define TR_MAXUINT48 (TR_POW2_48 - 1)
#define U16_MAX        ((UINT16)~0U)
#define S16_MAX        ((INT16)(U16_MAX >> 1))
#define U64MSB 0x8000000000000000ull
#define SRE_ABS(val) (((val) > 0) ? (val) : -(val))
#define min_t(type, x, y) ({            \
    type __min1 = (x);            \
    type __min2 = (y);            \
    __min1 < __min2 ? __min1 : __min2; })



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

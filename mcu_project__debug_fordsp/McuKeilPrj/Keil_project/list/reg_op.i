# 1 "../../src/thd_dsp_download_release_V0_0/reg_op.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 389 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "../../src/thd_dsp_download_release_V0_0/reg_op.c" 2








# 1 "../../src/thd_dsp_download_release_V0_0/reg_op.h" 1
# 13 "../../src/thd_dsp_download_release_V0_0/reg_op.h"
# 1 "../../src/thd_dsp_download_release_V0_0/sre_basic_typedef.h" 1
# 10 "../../src/thd_dsp_download_release_V0_0/sre_basic_typedef.h"
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
# 11 "../../src/thd_dsp_download_release_V0_0/sre_basic_typedef.h" 2



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
# 14 "../../src/thd_dsp_download_release_V0_0/reg_op.h" 2
# 1 "../../src/thd_dsp_download_release_V0_0/mailbox_reg.h" 1
# 21 "../../src/thd_dsp_download_release_V0_0/mailbox_reg.h"
typedef union RptMcuStaS {
    UINT32 val;
    struct {
           UINT32 rptHaltFromTile0: 1;
           UINT32 rptWfiFromTile0: 1;
           UINT32 rptCeaseFromTile0: 1;
           UINT32 rptDebugFromTile0: 1;
           UINT32 rsv0: 28;
    } bits;
} RptMcuStaS;


typedef union CfgMcuBusMemS {
    UINT32 val;
    struct {
           UINT32 cfgMemDslplv: 1;
           UINT32 cfgMemRtsel: 2;
           UINT32 cfgMemWtsel: 2;
           UINT32 cfgMemWasen: 1;
           UINT32 cfgMemWassel: 2;
           UINT32 rsv0: 24;
    } bits;
} CfgMcuBusMemS;


typedef union CfgRiscvMemS {
    UINT32 val;
    struct {
           UINT32 cfgBusMemShutDown: 1;
           UINT32 cfgBusMemDeepSleep: 1;
           UINT32 cfgRiscvMem0ShutDown: 1;
           UINT32 cfgRiscvMem0DeepSleep: 1;
           UINT32 cfgRiscvMem1ShutDown: 1;
           UINT32 cfgRiscvMem1DeepSleep: 1;
           UINT32 rsv0: 26;
    } bits;
} CfgRiscvMemS;



typedef struct MailboxRegTbl {
       volatile UINT32 mailbox[0x40];
       volatile UINT32 mcuBootSta;
       volatile UINT32 sramRemapAddr;
       volatile UINT32 sramRemapData;
       volatile UINT32 downloafdFwEn;
       volatile UINT32 mcuEnable;
       volatile UINT32 mcuRtcDiv;
       volatile UINT32 extInterruptsEnMask;
       volatile UINT32 extInterrupts;
       volatile UINT32 rptMcuSta;
       volatile UINT32 apbBypassArbEn;
       volatile UINT32 cfgMcuBusMem;
       volatile UINT32 cfgRiscvMem;
} MailboxRegTbl;
# 15 "../../src/thd_dsp_download_release_V0_0/reg_op.h" 2






VOID MCU_DelayUs(UINT32 us);
extern UINT32 g_regMaxOpNum;
VOID dsp_fsl_reg_write(UINT32 reg, UINT32 val);
VOID dsp_fsl_reg_read(UINT32 reg, UINT32 *val);
VOID dsp_fsl_continue_write(UINT32 reg, UINT8 *buff, UINT32 buffLen);
VOID dsp_fsl_continue_read(UINT32 addr, UINT8 *Buff, UINT32 buffLen);
# 10 "../../src/thd_dsp_download_release_V0_0/reg_op.c" 2

# 1 "../../src/thd_dsp_download_release_V0_0/sre_errcode.h" 1
# 12 "../../src/thd_dsp_download_release_V0_0/reg_op.c" 2


UINT32 g_regMaxOpNum = 40;
void fh_delay_us(uint32_t us);
VOID MCU_DelayUs(UINT32 us)
{
    fh_delay_us(us);
}

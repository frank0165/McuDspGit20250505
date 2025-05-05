# 1 "../../src/thd_dsp_download_release_V0_0/dsp_hpll_init.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 389 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "../../src/thd_dsp_download_release_V0_0/dsp_hpll_init.c" 2








# 1 "../../src/thd_dsp_download_release_V0_0/sre_basic_def.h" 1
# 10 "../../src/thd_dsp_download_release_V0_0/sre_basic_def.h"
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
# 11 "../../src/thd_dsp_download_release_V0_0/sre_basic_def.h" 2
# 10 "../../src/thd_dsp_download_release_V0_0/dsp_hpll_init.c" 2
# 1 "../../src/thd_dsp_download_release_V0_0/lane_mode_api.h" 1
# 18 "../../src/thd_dsp_download_release_V0_0/lane_mode_api.h"
typedef enum LaneRateModeE {
    LANE_MODE_INVALID = 0,
    LANE_MODE_1P244 = 1,
    LANE_MODE_1P25,
    LANE_MODE_2P488,
    LANE_MODE_2P5,
    LANE_MODE_3P125,
    LANE_MODE_5P,
    LANE_MODE_9P95,
    LANE_MODE_10P3125,
    LANE_MODE_12P44,
    LANE_MODE_12P5,
    LANE_MODE_24P88_NRZ,
    LANE_MODE_24P88_PAM4,
    LANE_MODE_25P78125_NRZ,
    LANE_MODE_25P78125_PAM4,
    LANE_MODE_26P5625_NRZ,
    LANE_MODE_26P5625_PAM4,
    LANE_MODE_49P76_NRZ,
    LANE_MODE_49P76_PAM4,
    LANE_MODE_51P5625_NRZ,
    LANE_MODE_51P5625_PAM4,
    LANE_MODE_53P125_NRZ,
    LANE_MODE_53P125_PAM4,
    LANE_MODE_NUM
} LaneRateModeE;

typedef enum LaneDataBitWidthE {
    DATA_BIT_WIDTH_8 = 0,
    DATA_BIT_WIDTH_16,
    DATA_BIT_WIDTH_32,
    DATA_BIT_WIDTH_64,
    DATA_BIT_WIDTH_NUM
} LaneDataBitWidthE;

typedef struct SystemChipRunS {
    UINT32 rxRunMask;
    UINT32 txRunMask;
} SystemChipRunS;




typedef union LaneRateMode {
    UINT8 val;
    struct {
        UINT8 rateMode: 6;
        UINT8 dataWidth: 2;
    } bits;
} LaneRateMode;
typedef union LaneModeCfg {
    UINT32 val;
    struct {
        LaneRateMode rxRate;
        LaneRateMode txRate[3];
    } hostBits;
    struct {
        LaneRateMode rxRate[3];
        LaneRateMode txRate;
    } lineBits;
} LaneModeCfg;

typedef struct SystemParaInitS {
    UINT32 isCfgFlag;
    UINT32 rxEnableMask;
    UINT32 txEnableMask;
    LaneModeCfg laneModeCfg[2];
} SystemParaInitS;
typedef struct SystemParaInitOutS {
    UINT32 rxEnableMask;
    UINT32 txEnableMask;
    LaneModeCfg laneModeCfg[2];
} SystemParaInitOutS;



typedef struct TxDatapathParaS {
    UINT8 txDEncodeAdd : 1;
    UINT8 txEncode1dEn : 1;
    UINT8 txDataInv : 1;
    UINT8 txGrayEn : 1;
    UINT8 txSwapEn : 1;
    UINT8 txLutSel : 1;
    UINT8 txLutGear : 2;
} TxDatapathParaS;
typedef struct RxDatapathParaS {
    UINT8 rxSel1d : 1;
    UINT8 rxEn1d : 1;
    UINT8 rxDataInv : 1;
    UINT8 rxGrayEn : 1;
    UINT8 rxSwapEn : 1;
    UINT8 rxBurstEn : 1;
    UINT8 rsv : 2;
} RxDatapathParaS;

typedef union LaneDatapathModeCfg{
    UINT32 val;
    struct {
        RxDatapathParaS hostRxDatapathCfg;
        TxDatapathParaS hostTxDatapathCfg;
        RxDatapathParaS lineRxDatapathCfg;
        TxDatapathParaS lineTxDatapathCfg;
    } bits;
} LaneDatapathModeCfg;
typedef struct SystemDatapathParaInitS {
    UINT32 isCfgFlag;
    UINT32 rxCfgMask;
    UINT32 txCfgMask;
    LaneDatapathModeCfg laneDatapathCfg;
} SystemDatapathParaInitS;
typedef struct SystemDatapathParaOutS {
    UINT32 rxCfgMask;
    UINT32 txCfgMask;
    LaneDatapathModeCfg laneDatapathCfg;
} SystemDatapathParaOutS;

typedef struct SystemCalibParaInitS {
    UINT32 isCfgFlag;
    UINT32 rxCfgMask;
    UINT32 txCfgMask;
} SystemCalibParaInitS;
typedef struct SystemCalibParaInitRspS {
    UINT32 rxCfgMask;
    UINT32 txCfgMask;
} SystemCalibParaInitRspS;

typedef struct SystemCalibParaAddrRspS {
    UINT32 baseAddr;
    UINT32 headLen;
    UINT32 oneLaneLen;
} SystemCalibParaAddrRspS;




typedef union SigLaneDatapathCfgS {
    UINT32 val;
    struct {
        RxDatapathParaS rxDatapathCfg;
        UINT8 rsv0;
        TxDatapathParaS txDatapathCfg;
        UINT8 rsv1;
    } bits;
} SigLaneDatapathCfgS;
typedef struct SystemSigLaneParaS {
    UINT32 laneType;
    UINT32 enCfg;
    LaneModeCfg laneModeCfg;
    SigLaneDatapathCfgS datapathCfg;
} SystemSigLaneParaS;




typedef union LaneShutdownCfgS {
    UINT32 val;
    struct {
        UINT16 laneType;
        UINT8 rxDownFlag;
        UINT8 txDownFlag;
    } bits;
} LaneShutdownCfgS;
typedef struct SystemLaneShutdownS {
    UINT32 laneNum;
    LaneShutdownCfgS cfg[2];
} SystemLaneShutdownS;



typedef struct TrxPrbsParaS {
    UINT8 prbsEn : 1;
    UINT8 prbsPatSel : 3;
    UINT8 prbsPatInv : 1;
    UINT8 rsv : 3;
} TrxPrbsParaS;

typedef struct TxPrbsUserSetS {
    UINT32 valid : 1;
    UINT32 prbsBlen : 20;
    UINT32 rateMode : 5;
    UINT32 rsv : 6;
} TxPrbsUserSetS;

typedef union LaneTxPrbsBasicCfgS {
    UINT32 val;
    TrxPrbsParaS bits;
} LaneTxPrbsBasicCfgS;

typedef union LaneTxPrbsMultiUserCfgS {
    UINT32 val;
    TxPrbsUserSetS bits;
} LaneTxPrbsMultiUserCfgS;
typedef struct SystemLaneTxPrbsCfgS {
    UINT32 laneType;
    LaneTxPrbsBasicCfgS prbsPara;
    LaneTxPrbsMultiUserCfgS multiUserCfg[3];
} SystemLaneTxPrbsCfgS;



typedef union LaneRxBerCmdS {
    UINT32 val;
    TrxPrbsParaS bits;
} LaneRxBerCmdS;

typedef struct SystemLaneRxBerCmdS {
    UINT32 laneType;
    LaneRxBerCmdS prbsPara;
    UINT32 cycleHigh;
    UINT32 cycleLow;
} SystemLaneRxBerCmdS;

typedef struct SystemLaneRxBerOutS {
    UINT32 laneType;
    UINT32 berLowVal;
    UINT32 berHighVal;
    UINT32 cycleHigh;
    UINT32 cycleLow;
} SystemLaneRxBerOutS;
# 11 "../../src/thd_dsp_download_release_V0_0/dsp_hpll_init.c" 2
# 1 "../../src/thd_dsp_download_release_V0_0/sre_errcode.h" 1
# 12 "../../src/thd_dsp_download_release_V0_0/dsp_hpll_init.c" 2
# 1 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 1 3
# 157 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
extern __attribute__((__pcs__("aapcs"))) unsigned __ARM_dcmp4(double , double );
extern __attribute__((__pcs__("aapcs"))) unsigned __ARM_fcmp4(float , float );







extern __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_fpclassifyf(float );
extern __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_fpclassify(double );



static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_isfinitef(float __x)
{
    return (((*(unsigned *)&(__x)) >> 23) & 0xff) != 0xff;
}
static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_isfinite(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff) != 0x7ff;
}



static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_isinff(float __x)
{
    return ((*(unsigned *)&(__x)) << 1) == 0xff000000;
}
static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_isinf(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) << 1) == 0xffe00000) && ((*(unsigned *)&(__x)) == 0);
}



static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_islessgreaterf(float __x, float __y)
{
    unsigned __f = __ARM_fcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);
}
static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_islessgreater(double __x, double __y)
{
    unsigned __f = __ARM_dcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);
}





static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_isnanf(float __x)
{
    return (0x7f800000 - ((*(unsigned *)&(__x)) & 0x7fffffff)) >> 31;
}
static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_isnan(double __x)
{
    unsigned __xf = (*(1 + (unsigned *)&(__x))) | (((*(unsigned *)&(__x)) == 0) ? 0 : 1);
    return (0x7ff00000 - (__xf & 0x7fffffff)) >> 31;
}



static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_isnormalf(float __x)
{
    unsigned __xe = ((*(unsigned *)&(__x)) >> 23) & 0xff;
    return (__xe != 0xff) && (__xe != 0);
}
static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_isnormal(double __x)
{
    unsigned __xe = ((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff;
    return (__xe != 0x7ff) && (__xe != 0);
}



static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_signbitf(float __x)
{
    return (*(unsigned *)&(__x)) >> 31;
}
static __inline __attribute__((__nothrow__)) __attribute__((__pcs__("aapcs"))) int __ARM_signbit(double __x)
{
    return (*(1 + (unsigned *)&(__x))) >> 31;
}
# 266 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
  typedef float float_t;
  typedef double double_t;
# 282 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
extern const int math_errhandling;







extern __attribute__((__nothrow__)) double acos(double );



extern __attribute__((__nothrow__)) double asin(double );





extern __attribute__((__nothrow__)) __attribute__((__const__)) double atan(double );



extern __attribute__((__nothrow__)) double atan2(double , double );





extern __attribute__((__nothrow__)) double cos(double );




extern __attribute__((__nothrow__)) double sin(double );





extern void __use_accurate_range_reduction(void);



extern __attribute__((__nothrow__)) double tan(double );





extern __attribute__((__nothrow__)) double cosh(double );




extern __attribute__((__nothrow__)) double sinh(double );






extern __attribute__((__nothrow__)) __attribute__((__const__)) double tanh(double );



extern __attribute__((__nothrow__)) double exp(double );






extern __attribute__((__nothrow__)) double frexp(double , int * ) __attribute__((__nonnull__(2)));







extern __attribute__((__nothrow__)) double ldexp(double , int );




extern __attribute__((__nothrow__)) double log(double );





extern __attribute__((__nothrow__)) double log10(double );



extern __attribute__((__nothrow__)) double modf(double , double * ) __attribute__((__nonnull__(2)));





extern __attribute__((__nothrow__)) double pow(double , double );






extern __attribute__((__nothrow__)) double sqrt(double );
# 410 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
    static __inline double _sqrt(double __x) { return sqrt(__x); }



    __attribute__((__always_inline__)) static float __sqrtf(float f) {
      __asm__ __volatile__(



      "vsqrt.f32 %0, %0"

      : "+w"(f));
      return f;
    }

    static __inline float _sqrtf(float __x) { return __sqrtf(__x); }
# 435 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
extern __attribute__((__nothrow__)) __attribute__((__const__)) double ceil(double );


extern __attribute__((__nothrow__)) __attribute__((__const__)) double fabs(double );



extern __attribute__((__nothrow__)) __attribute__((__const__)) double floor(double );



extern __attribute__((__nothrow__)) double fmod(double , double );
# 467 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
extern __attribute__((__nothrow__)) double acosh(double );



extern __attribute__((__nothrow__)) double asinh(double );



extern __attribute__((__nothrow__)) double atanh(double );



extern __attribute__((__nothrow__)) double cbrt(double );



static __inline __attribute__((__nothrow__)) __attribute__((__const__)) double copysign(double __x, double __y)



{
    (*(1 + (unsigned *)&(__x))) = ((*(1 + (unsigned *)&(__x))) & 0x7fffffff) | ((*(1 + (unsigned *)&(__y))) & 0x80000000);
    return __x;
}
static __inline __attribute__((__nothrow__)) __attribute__((__const__)) float copysignf(float __x, float __y)



{
    (*(unsigned *)&(__x)) = ((*(unsigned *)&(__x)) & 0x7fffffff) | ((*(unsigned *)&(__y)) & 0x80000000);
    return __x;
}
extern __attribute__((__nothrow__)) double erf(double );



extern __attribute__((__nothrow__)) double erfc(double );



extern __attribute__((__nothrow__)) double expm1(double );
# 533 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
extern __attribute__((__nothrow__)) double hypot(double , double );






extern __attribute__((__nothrow__)) int ilogb(double );



extern __attribute__((__nothrow__)) int ilogbf(float );



extern __attribute__((__nothrow__)) int ilogbl(long double );
# 646 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
extern __attribute__((__nothrow__)) double lgamma (double );




extern __attribute__((__nothrow__)) double log1p(double );



extern __attribute__((__nothrow__)) double logb(double );



extern __attribute__((__nothrow__)) float logbf(float );



extern __attribute__((__nothrow__)) long double logbl(long double );



extern __attribute__((__nothrow__)) double nextafter(double , double );




extern __attribute__((__nothrow__)) float nextafterf(float , float );




extern __attribute__((__nothrow__)) long double nextafterl(long double , long double );




extern __attribute__((__nothrow__)) double nexttoward(double , long double );




extern __attribute__((__nothrow__)) float nexttowardf(float , long double );




extern __attribute__((__nothrow__)) long double nexttowardl(long double , long double );




extern __attribute__((__nothrow__)) double remainder(double , double );



extern __attribute__((__nothrow__)) __attribute__((__const__)) double rint(double );



extern __attribute__((__nothrow__)) double scalbln(double , long int );



extern __attribute__((__nothrow__)) float scalblnf(float , long int );



extern __attribute__((__nothrow__)) long double scalblnl(long double , long int );



extern __attribute__((__nothrow__)) double scalbn(double , int );



extern __attribute__((__nothrow__)) float scalbnf(float , int );



extern __attribute__((__nothrow__)) long double scalbnl(long double , int );
# 740 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
extern __attribute__((__nothrow__)) __attribute__((__const__)) float fabsf(float);
static __inline __attribute__((__nothrow__)) __attribute__((__const__)) float _fabsf(float __f) { return fabsf(__f); }
extern __attribute__((__nothrow__)) float sinf(float );
extern __attribute__((__nothrow__)) float cosf(float );
extern __attribute__((__nothrow__)) float tanf(float );
extern __attribute__((__nothrow__)) float acosf(float );
extern __attribute__((__nothrow__)) float asinf(float );
extern __attribute__((__nothrow__)) float atanf(float );
extern __attribute__((__nothrow__)) float atan2f(float , float );
extern __attribute__((__nothrow__)) float sinhf(float );
extern __attribute__((__nothrow__)) float coshf(float );
extern __attribute__((__nothrow__)) float tanhf(float );
extern __attribute__((__nothrow__)) float expf(float );
extern __attribute__((__nothrow__)) float logf(float );
extern __attribute__((__nothrow__)) float log10f(float );
extern __attribute__((__nothrow__)) float powf(float , float );
extern __attribute__((__nothrow__)) float sqrtf(float );
extern __attribute__((__nothrow__)) float ldexpf(float , int );
extern __attribute__((__nothrow__)) float frexpf(float , int * ) __attribute__((__nonnull__(2)));
extern __attribute__((__nothrow__)) __attribute__((__const__)) float ceilf(float );
extern __attribute__((__nothrow__)) __attribute__((__const__)) float floorf(float );
extern __attribute__((__nothrow__)) float fmodf(float , float );
extern __attribute__((__nothrow__)) float modff(float , float * ) __attribute__((__nonnull__(2)));
# 780 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
__attribute__((__nothrow__)) long double acosl(long double );
__attribute__((__nothrow__)) long double asinl(long double );
__attribute__((__nothrow__)) long double atanl(long double );
__attribute__((__nothrow__)) long double atan2l(long double , long double );
__attribute__((__nothrow__)) long double ceill(long double );
__attribute__((__nothrow__)) long double cosl(long double );
__attribute__((__nothrow__)) long double coshl(long double );
__attribute__((__nothrow__)) long double expl(long double );
__attribute__((__nothrow__)) long double fabsl(long double );
__attribute__((__nothrow__)) long double floorl(long double );
__attribute__((__nothrow__)) long double fmodl(long double , long double );
__attribute__((__nothrow__)) long double frexpl(long double , int* ) __attribute__((__nonnull__(2)));
__attribute__((__nothrow__)) long double ldexpl(long double , int );
__attribute__((__nothrow__)) long double logl(long double );
__attribute__((__nothrow__)) long double log10l(long double );
__attribute__((__nothrow__)) long double modfl(long double , long double * ) __attribute__((__nonnull__(2)));
__attribute__((__nothrow__)) long double powl(long double , long double );
__attribute__((__nothrow__)) long double sinl(long double );
__attribute__((__nothrow__)) long double sinhl(long double );
__attribute__((__nothrow__)) long double sqrtl(long double );
__attribute__((__nothrow__)) long double tanl(long double );
__attribute__((__nothrow__)) long double tanhl(long double );






extern __attribute__((__nothrow__)) float acoshf(float );
__attribute__((__nothrow__)) long double acoshl(long double );
extern __attribute__((__nothrow__)) float asinhf(float );
__attribute__((__nothrow__)) long double asinhl(long double );
extern __attribute__((__nothrow__)) float atanhf(float );
__attribute__((__nothrow__)) long double atanhl(long double );
__attribute__((__nothrow__)) long double copysignl(long double , long double );
extern __attribute__((__nothrow__)) float cbrtf(float );
__attribute__((__nothrow__)) long double cbrtl(long double );
extern __attribute__((__nothrow__)) float erff(float );
__attribute__((__nothrow__)) long double erfl(long double );
extern __attribute__((__nothrow__)) float erfcf(float );
__attribute__((__nothrow__)) long double erfcl(long double );
extern __attribute__((__nothrow__)) float expm1f(float );
__attribute__((__nothrow__)) long double expm1l(long double );
extern __attribute__((__nothrow__)) float log1pf(float );
__attribute__((__nothrow__)) long double log1pl(long double );
extern __attribute__((__nothrow__)) float hypotf(float , float );
__attribute__((__nothrow__)) long double hypotl(long double , long double );
extern __attribute__((__nothrow__)) float lgammaf(float );
__attribute__((__nothrow__)) long double lgammal(long double );
extern __attribute__((__nothrow__)) float remainderf(float , float );
__attribute__((__nothrow__)) long double remainderl(long double , long double );
extern __attribute__((__nothrow__)) float rintf(float );
__attribute__((__nothrow__)) long double rintl(long double );







extern __attribute__((__nothrow__)) double exp2(double );
extern __attribute__((__nothrow__)) float exp2f(float );
__attribute__((__nothrow__)) long double exp2l(long double );
extern __attribute__((__nothrow__)) double fdim(double , double );
extern __attribute__((__nothrow__)) float fdimf(float , float );
__attribute__((__nothrow__)) long double fdiml(long double , long double );
# 855 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
extern __attribute__((__nothrow__)) double fma(double , double , double );
extern __attribute__((__nothrow__)) float fmaf(float , float , float );

static __inline __attribute__((__nothrow__)) long double fmal(long double __x, long double __y, long double __z) { return (long double)fma((double)__x, (double)__y, (double)__z); }


extern __attribute__((__nothrow__)) __attribute__((__const__)) double fmax(double , double );
extern __attribute__((__nothrow__)) __attribute__((__const__)) float fmaxf(float , float );
__attribute__((__nothrow__)) long double fmaxl(long double , long double );
extern __attribute__((__nothrow__)) __attribute__((__const__)) double fmin(double , double );
extern __attribute__((__nothrow__)) __attribute__((__const__)) float fminf(float , float );
__attribute__((__nothrow__)) long double fminl(long double , long double );
extern __attribute__((__nothrow__)) double log2(double );
extern __attribute__((__nothrow__)) float log2f(float );
__attribute__((__nothrow__)) long double log2l(long double );
extern __attribute__((__nothrow__)) long lrint(double );
extern __attribute__((__nothrow__)) long lrintf(float );

static __inline __attribute__((__nothrow__)) long lrintl(long double __x) { return lrint((double)__x); }


extern __attribute__((__nothrow__)) long long llrint(double );
extern __attribute__((__nothrow__)) long long llrintf(float );

static __inline __attribute__((__nothrow__)) long long llrintl(long double __x) { return llrint((double)__x); }


extern __attribute__((__nothrow__)) long lround(double );
extern __attribute__((__nothrow__)) long lroundf(float );

static __inline __attribute__((__nothrow__)) long lroundl(long double __x) { return lround((double)__x); }


extern __attribute__((__nothrow__)) long long llround(double );
extern __attribute__((__nothrow__)) long long llroundf(float );

static __inline __attribute__((__nothrow__)) long long llroundl(long double __x) { return llround((double)__x); }


extern __attribute__((__nothrow__)) __attribute__((__const__)) double nan(const char * );
extern __attribute__((__nothrow__)) __attribute__((__const__)) float nanf(const char * );

static __inline __attribute__((__nothrow__)) __attribute__((__const__)) long double nanl(const char *__t) { return (long double)nan(__t); }
# 908 "D:\\D\\app\\kevil5\\ARM\\ARMCLANG\\Bin\\..\\include\\math.h" 3
extern __attribute__((__nothrow__)) __attribute__((__const__)) double nearbyint(double );
extern __attribute__((__nothrow__)) __attribute__((__const__)) float nearbyintf(float );
__attribute__((__nothrow__)) long double nearbyintl(long double );
extern __attribute__((__nothrow__)) double remquo(double , double , int * );
extern __attribute__((__nothrow__)) float remquof(float , float , int * );

static __inline long double remquol(long double __x, long double __y, int *__q) { return (long double)remquo((double)__x, (double)__y, __q); }


extern __attribute__((__nothrow__)) __attribute__((__const__)) double round(double );
extern __attribute__((__nothrow__)) __attribute__((__const__)) float roundf(float );
__attribute__((__nothrow__)) long double roundl(long double );
extern __attribute__((__nothrow__)) double tgamma(double );
extern __attribute__((__nothrow__)) float tgammaf(float );
__attribute__((__nothrow__)) long double tgammal(long double );
extern __attribute__((__nothrow__)) __attribute__((__const__)) double trunc(double );
extern __attribute__((__nothrow__)) __attribute__((__const__)) float truncf(float );
__attribute__((__nothrow__)) long double truncl(long double );
# 13 "../../src/thd_dsp_download_release_V0_0/dsp_hpll_init.c" 2

# 1 "../../src/thd_dsp_download_release_V0_0/reg_op.h" 1
# 14 "../../src/thd_dsp_download_release_V0_0/reg_op.h"
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
# 15 "../../src/thd_dsp_download_release_V0_0/dsp_hpll_init.c" 2
# 31 "../../src/thd_dsp_download_release_V0_0/dsp_hpll_init.c"
UINT16 g_acqCode = 0;

typedef enum DspPllModeType {
    DSP_DS_ATE_MODE = 0,
    DSP_DS_ACQ_MODE,
    DSP_DS_SLLP_MODE,
    DSP_US_NOR_MODE
} DspPllModeType;

typedef enum PllClkSrcE {
    PLL_DS_XTAL_SRC = 0,
    PLL_DS_CDR_SRC,
    PLL_US_HPLL_REFCLK_SRC,
    PLL_US_XTAL_SRC,
    PLL_US_CDR_SRC,
    PLL_SRC_NUM
} PllClkSrcE;

typedef union PuResetnPllS {
    UINT32 val;
    struct {
           UINT32 puPll: 1;
           UINT32 rsv0: 15;
           UINT32 rstnPll: 1;
           UINT32 rsv1: 15;
    } bits;
} PuResetnPllS;

typedef union RegRefSelS {
    UINT32 val;
    struct {
           UINT32 regRef1Sel: 1;
           UINT32 regRef2Sel: 1;
           UINT32 regDivPostSel: 2;
           UINT32 regFbcFdiv: 24;
           UINT32 rsv0: 4;
    } bits;
} RegRefSelS;
typedef union PllReg0S {
    UINT32 val;
    struct {
           UINT32 ampJudeg: 2;
           UINT32 freqJudge: 2;
           UINT32 byAmp: 1;
           UINT32 byFreq: 1;
           UINT32 bySllp: 1;
           UINT32 regPllModeSel: 1;
           UINT32 regPllV2IIrefSel: 1;
           UINT32 regRefckSel: 1;
           UINT32 sllpStep: 3;
           UINT32 tempClkSel: 1;
           UINT32 regRefclkPredivSel: 2;
           UINT32 ampCaliDivr: 14;
           UINT32 rsv0: 2;
    } bits;
} PllReg0S;

typedef union PllReg1S {
    UINT32 val;
    struct {
           UINT32 ampCtrlLoad: 6;
           UINT32 rsv0: 2;
           UINT32 freqCaliCnt1Size: 3;
           UINT32 rsv1: 1;
           UINT32 freqCaliCnt2Size: 3;
           UINT32 rsv2: 1;
           UINT32 freqLoad: 16;
    } bits;
} PllReg1S;

typedef union PllReg3S {
    UINT32 val;
    struct {
           UINT32 regLdo120P9VSelbit3: 1;
           UINT32 regVddrCoreSel: 3;
           UINT32 regVddrCpSel: 3;
           UINT32 regIcpSel: 5;
           UINT32 regKvcoSel: 2;
           UINT32 regFracModeEn: 1;
           UINT32 regFracValid: 1;
           UINT32 regVddrDivClkSel: 3;
           UINT32 regVddrPiSel: 3;
           UINT32 shortrOv: 1;
           UINT32 bypassPll: 1;
           UINT32 enPllOv: 1;
           UINT32 regLdo120P5VSel: 4;
           UINT32 regLdo120P9VSelbit2to0: 3;
    } bits;
} PllReg3S;
typedef union PllReg4S {
    UINT32 val;
    struct {
           UINT32 regPiIbiashSelbit5: 1;
           UINT32 regPiResSel: 3;
           UINT32 regPiDlySel: 2;
           UINT32 regIndSw: 1;
           UINT32 regPiIbiaslSel: 6;
           UINT32 regPiResetExt: 1;
           UINT32 rsv0: 2;
           UINT32 regLpfCap2Sel: 3;
           UINT32 regLpfResSel: 3;
           UINT32 regDsmDivSel: 2;
           UINT32 regPuPi0P9V: 1;
           UINT32 regPd12PiIdac: 1;
           UINT32 regPiCkdetEn: 1;
           UINT32 regPiIbiashSelbit4to0: 5;
    } bits;
} PllReg4S;
typedef union PllReg5S {
    UINT32 val;
    struct {
           UINT32 regDccBypassNbit10to2: 9;
           UINT32 regDccBypass: 1;
           UINT32 regDccCkrefEn: 1;
           UINT32 regDccCmpbSel: 1;
           UINT32 regDccLoadEn: 1;
           UINT32 regDccSkewEn: 1;
           UINT32 regDccStepEn: 1;
           UINT32 rsv0: 1;
           UINT32 regDccAsn: 6;
           UINT32 regDccAsp: 6;
           UINT32 regPuDccCmp: 1;
           UINT32 regResetDcc: 1;
           UINT32 regDccBypassNbit1to0: 2;
    } bits;
} PllReg5S;
typedef union PllReg8S {
    UINT32 val;
    struct {
           UINT32 regDpllEn: 1;
           UINT32 regDpllLoadEn: 1;
           UINT32 regDpllFracSel: 2;
           UINT32 regDpllEnIntgSatDet: 1;
           UINT32 regDpllEnFracSatDet: 1;
           UINT32 regDpllUpDnSwap: 1;
           UINT32 regModeDutySel: 1;
           UINT32 rsv1: 8;
           UINT32 regDpllPdivRef: 11;
           UINT32 rsv0: 5;
    } bits;
} PllReg8S;

typedef union PllReg11S {
    UINT32 val;
    struct {
           UINT32 regHrx1CdrSel: 1;
           UINT32 regHrx2CdrSel: 1;
           UINT32 regCkRxCdrDivEn: 1;
           UINT32 regCkRxCdrDivRatio: 5;
           UINT32 regDivToApcPdiv: 8;
           UINT32 regDivToLpllPdiv: 13;
           UINT32 regDivToLpllEn: 1;
           UINT32 regDivToLpllRst: 1;
           UINT32 regPllFbdivEnReflessMode: 1;
    } bits;
} PllReg11S;


typedef union PllReg12S {
    UINT32 val;
    struct {
           UINT32 regEnPllOw: 1;
           UINT32 regEnPllOwVal: 1;
           UINT32 regRxCdrFllUpPolarity: 1;
           UINT32 regRxCdrFllUpSel: 1;
           UINT32 regRstPllOwVal: 1;
           UINT32 regRstPllOw: 1;
           UINT32 regFbdivEnOwVal: 1;
           UINT32 regFbdivEnOw: 1;
           UINT32 regDivToApcPdiv: 5;
           UINT32 regDivToApcEn: 1;
           UINT32 regDivToApcRst: 1;
           UINT32 rsv1: 1;
           UINT32 regDivToDigPdiv: 13;
           UINT32 regDivToDigEn: 1;
           UINT32 regDivToDigRst: 1;
           UINT32 rsv0: 1;
    } bits;
} PllReg12S;
typedef struct PllRegTbl {
       volatile UINT32 puResetnPll;
       volatile UINT32 pllRegRefSel;
       volatile UINT32 pllRegFbcPdiv;
       volatile UINT32 pllTempCodePll;
       volatile UINT32 pllTempVldPll;
       volatile UINT32 pllReg0;
       volatile UINT32 pllReg1;
       volatile UINT32 pllReg2;
       volatile UINT32 pllReg3;
       volatile UINT32 pllReg4;
       volatile UINT32 pllReg5;
       volatile UINT32 pllReg6;
       volatile UINT32 pllReg7;
       volatile UINT32 pllReg8;
       volatile UINT32 pllReg9;
       volatile UINT32 pllReg10;
       volatile UINT32 pllReg11;
       volatile UINT32 pllReg12;
       volatile UINT32 pllRpt0;
       volatile UINT32 pllRpt1;
       volatile UINT32 pllRpt2;
       volatile UINT32 pllRpt3;
       volatile UINT32 pllPllLock;
       volatile UINT32 pllPllLockLos;
} PllRegTbl;

VOID SREI_PllFreCodeSet(PllRegTbl *pllTbl, UINT32 pdiv, UINT32 frac)
{
    RegRefSelS fracCfg;
    PllReg3S vaild;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllRegFbcPdiv)), pdiv);
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllRegRefSel)), &(fracCfg.val));
    fracCfg.bits.regFbcFdiv = frac;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllRegRefSel)), fracCfg.val);
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg3)), &(vaild.val));
    vaild.bits.regFracValid = 0;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg3)), vaild.val);
    MCU_DelayUs(1);
    vaild.bits.regFracValid = 1;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg3)), vaild.val);
    MCU_DelayUs(1);
    vaild.bits.regFracValid = 0;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg3)), vaild.val);
    MCU_DelayUs(1);
    vaild.bits.regFracValid = 1;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg3)), vaild.val);
    MCU_DelayUs(1);
    vaild.bits.regFracValid = 0;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg3)), vaild.val);
}

VOID SREI_PllDutyCycleSet(PllRegTbl *pllTbl, UINT8 en)
{
    PllReg5S dutyCfg;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg5)), &(dutyCfg.val));
    dutyCfg.bits.regDccStepEn = 0x1;
    dutyCfg.bits.regDccCmpbSel = 0x1;
    dutyCfg.bits.regDccCkrefEn = 0x1;
    dutyCfg.bits.regPuDccCmp = 0x1;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllRegRefSel)), dutyCfg.val);
}
VOID SREI_HostPllSllpBypass(UINT8 bypassEn)
{
    PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
    PllReg0S bypassCfg;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg0)), &(bypassCfg.val));
    bypassCfg.bits.bySllp = bypassEn;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg0)), bypassCfg.val);
}

VOID SREI_AnaRxAcqEn(UINT8 en)
{
    UINT32 acqEnReg;
    volatile UINT32 *rxBaseAddr;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)(0x100 << 2);
    rxBaseAddr = &anaRxTbl[0x44];
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&rxBaseAddr[34])), &(acqEnReg));
    acqEnReg &= ~(0x1 << 27);
    acqEnReg |= ((UINT32)en << 27);
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&rxBaseAddr[34])), acqEnReg);
    acqEnReg &= ~(0x1 << 26);
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&rxBaseAddr[34])), acqEnReg);
    acqEnReg |= ((UINT32)en << 26);
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&rxBaseAddr[34])), acqEnReg);
}


VOID SREI_AnaRxCdrEn(UINT8 en)
{
    UINT32 cdrEnReg;
    volatile UINT32 *rxBaseAddr;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)(0x100 << 2);
    rxBaseAddr = &anaRxTbl[0x44];
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&rxBaseAddr[0])), &(cdrEnReg));
    cdrEnReg &= ~(0X1 << 31);
    cdrEnReg |= ((UINT32)en << 31);
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&rxBaseAddr[0])), cdrEnReg);
}

UINT32 PllFreqCodeGet(VOID)
{
    return (UINT32)(g_acqCode);
}

VOID SREI_HostPllAcqSet(UINT8 acqEn, UINT8 loadEn)
{
    PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
    UINT32 freqCode;
    PllReg0S bypassCfg;
    PllReg1S freCfg;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg0)), &(bypassCfg.val));
    bypassCfg.bits.byAmp = acqEn;
    bypassCfg.bits.byFreq = acqEn;
    bypassCfg.bits.bySllp = acqEn;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg0)), bypassCfg.val);

    if (acqEn == 1) {
        SREI_AnaRxAcqEn(acqEn);
        SREI_AnaRxCdrEn(acqEn);
    }

    if (loadEn == 1) {
        freqCode = PllFreqCodeGet();
        dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg1)), &(freCfg.val));
        freCfg.bits.freqLoad = freqCode;
        dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg1)), freCfg.val);
    }
}

VOID SREI_HostPllOpenLoop(UINT8 owEn, UINT8 owVal)
{
    PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
    PllReg12S openLoopCfg;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg12)), &(openLoopCfg.val));
    openLoopCfg.bits.regEnPllOwVal = owVal;
    openLoopCfg.bits.regEnPllOw = owEn;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg12)), openLoopCfg.val);
}

VOID SREI_HostPllSllpLoopFromRx(UINT8 en)
{
    PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
    PllReg12S loopCfg;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg12)), &(loopCfg.val));
    loopCfg.bits.regRxCdrFllUpPolarity = 0x0;
    loopCfg.bits.regRxCdrFllUpSel = en;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg12)), loopCfg.val);
}
VOID SREI_PllClkSel(UINT8 clkSrc)
{
    PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
    PllReg0S clkSelReg;
    PllReg11S cdrSelReg;
    RegRefSelS refSelReg;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg0)), &(clkSelReg.val));
    if ((clkSrc == PLL_DS_XTAL_SRC) || (clkSrc == PLL_US_HPLL_REFCLK_SRC) || (clkSrc == PLL_US_XTAL_SRC)) {
        clkSelReg.bits.regRefckSel = 0;
    } else {
        clkSelReg.bits.regRefckSel = 1;
    }
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg0)), clkSelReg.val);
    if (clkSrc < PLL_US_HPLL_REFCLK_SRC) {
        return;
    }
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg11)), &(cdrSelReg.val));
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllRegRefSel)), &(refSelReg.val));
    if (clkSrc == PLL_US_HPLL_REFCLK_SRC) {
        cdrSelReg.bits.regHrx1CdrSel = 0x0;
        cdrSelReg.bits.regHrx2CdrSel = 0x0;
        refSelReg.bits.regRef1Sel = 0x1;
        refSelReg.bits.regRef2Sel = 0x0;
    } else if (clkSrc == PLL_US_XTAL_SRC) {
        cdrSelReg.bits.regHrx1CdrSel = 0x0;
        cdrSelReg.bits.regHrx2CdrSel = 0x0;
        refSelReg.bits.regRef1Sel = 0x0;
        refSelReg.bits.regRef2Sel = 0x1;
    } else {
        cdrSelReg.bits.regHrx1CdrSel = 0x1;
        cdrSelReg.bits.regHrx2CdrSel = 0x1;
        refSelReg.bits.regRef1Sel = 0x0;
        refSelReg.bits.regRef2Sel = 0x0;
    }
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg11)), cdrSelReg.val);
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllRegRefSel)), refSelReg.val);

}

VOID SREI_PllFbdivEnReflessMode(UINT8 enReflessMode)
{
    PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
    PllReg11S cfgVal;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg11)), &(cfgVal.val));
    cfgVal.bits.regPllFbdivEnReflessMode = enReflessMode;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg11)), cfgVal.val);
    return;
}


VOID SREI_AnaRxDtlManualEn(UINT8 en)
{
    UINT32 dtlManReg;
    volatile UINT32 *rxBaseAddr;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)(0x100 << 2);
    rxBaseAddr = &anaRxTbl[0x44];
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&rxBaseAddr[15])), &(dtlManReg));
    dtlManReg &= ~0x3;
    dtlManReg |= ((UINT32)en << 0);
    dtlManReg |= ((UINT32)en << 1);
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&rxBaseAddr[15])), dtlManReg);
}
VOID SREI_AnaRxCdrAcqEn(UINT8 en)
{
    UINT32 cdrEnReg;
    volatile UINT32 *rxBaseAddr;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)(0x100 << 2);
    rxBaseAddr = &anaRxTbl[0x44];
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&rxBaseAddr[29])), &(cdrEnReg));
    cdrEnReg &= ~(0x1 << 25);
    cdrEnReg |= ((UINT32)en << 25);
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&rxBaseAddr[29])), cdrEnReg);
}

VOID SREI_AnaRxDtlLowGainEn(UINT8 en)
{
    UINT32 dtlGainReg;
    volatile UINT32 *rxBaseAddr;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)(0x100 << 2);
    rxBaseAddr = &anaRxTbl[0x44];
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&rxBaseAddr[34])), &(dtlGainReg));
    dtlGainReg |= 0x1 << 24;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&rxBaseAddr[34])), dtlGainReg);
}

SRE_BOOL SREI_AnaCdrIsLock(VOID)
{
    UINT32 cdrLock;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)(0x100 << 2);
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&anaRxTbl[0x3e])), &(cdrLock));
    if ((cdrLock & 0x1) == 0x1) {
        return 1;
    } else {
        return 0;
    }
}

UINT16 SREI_PllAcqCodeGet(VOID)
{
    PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
    UINT32 rpt;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllRpt1)), &(rpt));
    return (UINT16)(rpt & 0xfff);
}

SRE_BOOL SREI_PllIsLock()
{
    PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
    UINT32 lock;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllPllLock)), &(lock));
    if (lock == 0x1) {
        return 1;
    } else {
        return 0;
    }
}
SRE_BOOL SREI_PllIsHisUnLock()
{
    PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
    UINT32 lock;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllPllLockLos)), &(lock));
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllPllLockLos)), 1);
    if (lock == 0x1) {
        return 1;
    } else {
        return 0;
    }
}
VOID SREI_PllFracDsmDivConfig(VOID)
{
   PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
   PllReg4S pllReg4;
   dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg4)), &(pllReg4.val));
   pllReg4.bits.regDsmDivSel = 0;
   dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg4)), pllReg4.val);
}
VOID SREI_PllFracModeCfg(UINT8 fracMode)
{
    PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
    PllReg3S pllReg3;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg3)), &(pllReg3.val));
    pllReg3.bits.regFracModeEn = fracMode;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg3)), pllReg3.val);
}
UINT32 SRE_HpllInit(UINT8 en, DOUBLE refClk, DOUBLE fre, UINT8 mode, UINT8 postDivRatio)
{
    PllRegTbl *pllTbl = (PllRegTbl *)(0x1c0 << 2);
    volatile UINT32 *iicTbl = (volatile UINT32 *)(0x80 << 2);
    PllReg8S dpllCfg;
    PllReg12S pllBypassCfg;
    PuResetnPllS puCfg;
    UINT32 pdiv;
    UINT32 frac;
    UINT8 vcoDiv;
    UINT8 clkSrc;
    RegRefSelS divPostCfg;
    PllReg11S hpllRefclkSrcDibRatio;

    puCfg.val = 0;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&iicTbl[1])), puCfg.val);
    if (en == 0) {
        return (UINT32)0;
    }
    puCfg.bits.puPll = 0x1;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&iicTbl[1])), puCfg.val);
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg12)), &(pllBypassCfg.val));
    UINT32 digDiv = (UINT32)(ceil(fre / 200000000) / 2 + 1);
    pllBypassCfg.bits.regDivToDigPdiv = digDiv;
    if ((mode == DSP_DS_ACQ_MODE) || (mode == DSP_DS_SLLP_MODE)) {
        pllBypassCfg.bits.regRstPllOw = 0x1;
        pllBypassCfg.bits.regRstPllOwVal = 0x1;
        dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg12)), pllBypassCfg.val);
    } else {
        pllBypassCfg.bits.regRstPllOw = 0x0;
        pllBypassCfg.bits.regRstPllOwVal = 0x0;
        dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg12)), pllBypassCfg.val);
    }

    if ((mode == DSP_DS_ACQ_MODE) || (mode == DSP_DS_SLLP_MODE)) {
        SREI_HostPllAcqSet(1, 1);
        SREI_AnaRxDtlManualEn(1);
        SREI_AnaRxCdrAcqEn(1);
        SREI_AnaRxDtlLowGainEn(0);
        SREI_HostPllOpenLoop(1, 0x0);
        SREI_PllFbdivEnReflessMode(1);
    } else if (mode == DSP_DS_ATE_MODE) {
        SREI_HostPllAcqSet(0, 0);
        SREI_AnaRxDtlManualEn(0);
        SREI_AnaRxCdrAcqEn(0);
        SREI_AnaRxDtlLowGainEn(0);
        SREI_HostPllOpenLoop(0, 0x0);
        SREI_PllFbdivEnReflessMode(0);
    }
    if (mode == DSP_DS_SLLP_MODE) {
        SREI_HostPllSllpLoopFromRx(1);
    } else if ((mode == DSP_DS_ACQ_MODE) || (mode == DSP_DS_ATE_MODE)) {
        SREI_HostPllSllpLoopFromRx(0);
    }

    if (mode == DSP_DS_ATE_MODE) {
        clkSrc = PLL_DS_XTAL_SRC;
    } else if ((mode == DSP_DS_ACQ_MODE) || (mode == DSP_DS_SLLP_MODE)) {
        clkSrc = PLL_DS_CDR_SRC;
    } else if (mode == DSP_US_NOR_MODE) {
        clkSrc = PLL_US_HPLL_REFCLK_SRC;
    } else {
        clkSrc = PLL_US_CDR_SRC;
    }
    SREI_PllClkSel(clkSrc);


    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg8)), &(dpllCfg.val));
    dpllCfg.bits.regDpllFracSel = 0x0;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg8)), dpllCfg.val);



    UINT8 fracMode = 1;
    if (fracMode == 0) {
        pdiv = (UINT32)floor(fre / refClk);
        frac = (UINT32)((fre / refClk / pdiv - 1) * (0x1 << 26)) & 0xffffff;
        SREI_PllFreCodeSet(pllTbl, pdiv, frac);
    } else {
        pdiv = (UINT32)floor(fre / refClk / 4);
        frac = (UINT32)((fre / refClk / pdiv - 1) * (0x1 << 25)) & 0xffffff;
        SREI_PllFreCodeSet(pllTbl, pdiv, frac);
        SREI_PllFracDsmDivConfig();
    }
    SREI_PllFracModeCfg(fracMode);


    vcoDiv = postDivRatio;
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllRegRefSel)), &(divPostCfg.val));
    divPostCfg.bits.regDivPostSel = vcoDiv;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllRegRefSel)), divPostCfg.val);
    dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg11)), &(hpllRefclkSrcDibRatio.val));
    if (vcoDiv == 1) {
        hpllRefclkSrcDibRatio.bits.regDivToLpllPdiv = 0X50 >> 1;
    } else {
        hpllRefclkSrcDibRatio.bits.regDivToLpllPdiv = 0X50;
    }
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg11)), hpllRefclkSrcDibRatio.val);


    if ((mode == DSP_DS_ACQ_MODE) || (mode == DSP_DS_SLLP_MODE)) {
        dsp_fsl_reg_read((UINT32)((UINTPTR)(&pllTbl->pllReg12)), &(pllBypassCfg.val));
        pllBypassCfg.bits.regRstPllOw = 0x1;
        pllBypassCfg.bits.regRstPllOwVal = 0x0;
        dsp_fsl_reg_write((UINT32)((UINTPTR)(&pllTbl->pllReg12)), pllBypassCfg.val);
    }
    puCfg.bits.rstnPll = 0x1;
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&iicTbl[1])), puCfg.val);

   MCU_DelayUs(1000);
    if ((mode == DSP_DS_ACQ_MODE) || (mode == DSP_DS_SLLP_MODE)) {
        if (SREI_AnaCdrIsLock() == 0) {
            return ((0x11 << 24) | (9));
        }
        if (mode == DSP_DS_ACQ_MODE) {
            SREI_HostPllOpenLoop(1, 0x1);
        }
    }
    if (mode == DSP_DS_ATE_MODE) {
        g_acqCode = SREI_PllAcqCodeGet();
    }
    return (UINT32)0;
}


UINT64 g_hpllFre[LANE_MODE_NUM] = {
    [LANE_MODE_INVALID] = 12441600000,
    [LANE_MODE_1P244] = 4976640000,
    [LANE_MODE_1P25] = 10000000000,
    [LANE_MODE_2P488] = 4976640000,
    [LANE_MODE_2P5] = 10000000000,
    [LANE_MODE_3P125] = 6250000000,
    [LANE_MODE_5P] = 5000000000,
    [LANE_MODE_9P95] = 4976640000,
    [LANE_MODE_10P3125] = 10312500000,
    [LANE_MODE_12P44] = 6220800000,
    [LANE_MODE_12P5] = 6250000000,
    [LANE_MODE_24P88_NRZ] = 12441600000,
    [LANE_MODE_24P88_PAM4] = 12441600000,
    [LANE_MODE_25P78125_NRZ] = 12890625000,
    [LANE_MODE_25P78125_PAM4] = 12890625000,
    [LANE_MODE_26P5625_NRZ] = 13281250000,
    [LANE_MODE_26P5625_PAM4] = 13281250000,
    [LANE_MODE_49P76_NRZ] = 12441600000,
    [LANE_MODE_49P76_PAM4] = 12441600000,
    [LANE_MODE_51P5625_NRZ] = 12890625000,
    [LANE_MODE_51P5625_PAM4] = 12890625000,
    [LANE_MODE_53P125_NRZ] = 13281250000,
    [LANE_MODE_53P125_PAM4] = 13281250000,
};







UINT32 SRE_HpllSetup(UINT8 workMode)
{
    UINT8 isLock;
    UINT16 freCode;
    UINT32 waitCnt;
    UINT32 *workModeCfg = (UINT32 *)(0x0 << 2);
    dsp_fsl_reg_write((UINT32)((UINTPTR)(&workModeCfg[0])), workMode);
    UINT8 postDivRatio;
    if (workMode >= LANE_MODE_24P88_NRZ && workMode <= LANE_MODE_26P5625_PAM4) {
        postDivRatio = 1;
    } else {
        postDivRatio = 0;
    }
    SRE_HpllInit(1, 38400000, g_hpllFre[workMode], 0, postDivRatio);
    waitCnt = 0;
    do {
        MCU_DelayUs(10);
        isLock = SREI_PllIsLock();
        waitCnt++;
    } while ((isLock == 0) && (waitCnt < 1000));
    isLock = SREI_PllIsLock();
    if (isLock != 1) {
        return ((0x11 << 24) | (0x25));
    }
    freCode = SREI_PllAcqCodeGet();

    return (UINT32)0;
}

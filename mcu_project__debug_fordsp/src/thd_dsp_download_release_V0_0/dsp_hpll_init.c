/* 
 * ana host pllåŠŸèƒ½å‡½æ•°
 * Copyright 2024-2025 Tauren Semiconductor.
 * Create data: 2025-4-7
 * auther: zhanglaipeng
 */


#include "sre_basic_def.h"
#include "lane_mode_api.h"
#include "sre_errcode.h"
#include "math.h"
#ifdef EXT_CTRL_MCU
#include "reg_op.h"
#endif

#ifdef _GCC_TOOLS_
VOID I2C_RegisterWrite(UINT32 addr, UINT32 val);
VOID I2C_RegisterRead(UINT32 addr, UINT32 val);

#define RegisterRead(val, reg) I2C_RegisterRead((UINT32)((UINTPTR)(&reg) >> 2), &(val))
#define RegisterWrite(reg, val) I2C_RegisterWrite((UINT32)((UINTPTR)(&reg) >> 2), val)
#endif


#define HPLL_BASEADDR                   (0x1c0 << 2)
#define ANA_BASEADDR                    (0x100 << 2)
#define IIC_CFG_BASEADDR                (0x80 << 2)
#define WORKMODE_BASEADDR               (0x0 << 2)

UINT16 g_acqCode = 0;

typedef enum DspPllModeType {
    DSP_DS_ATE_MODE = 0,        // hostrx linetx
    DSP_DS_ACQ_MODE,            // hostrx linetx
    DSP_DS_SLLP_MODE,           // hostrx linetx
    DSP_US_NOR_MODE             // linerx hosttx
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
        RW UINT32 puPll: 1;
        RO UINT32 rsv0: 15;
        RW UINT32 rstnPll: 1;
        RO UINT32 rsv1: 15;
    } bits;
} PuResetnPllS;

typedef union RegRefSelS {
    UINT32 val;
    struct {
        RW UINT32 regRef1Sel: 1;
        RW UINT32 regRef2Sel: 1;
        RW UINT32 regDivPostSel: 2;
        RW UINT32 regFbcFdiv: 24;
        RO UINT32 rsv0: 4;
    } bits;
} RegRefSelS;
typedef union PllReg0S {
    UINT32 val;
    struct {
        RW UINT32 ampJudeg: 2;
        RW UINT32 freqJudge: 2;
        RW UINT32 byAmp: 1;
        RW UINT32 byFreq: 1;
        RW UINT32 bySllp: 1;
        RW UINT32 regPllModeSel: 1;
        RW UINT32 regPllV2IIrefSel: 1;
        RW UINT32 regRefckSel: 1;
        RW UINT32 sllpStep: 3;
        RW UINT32 tempClkSel: 1;
        RW UINT32 regRefclkPredivSel: 2;
        RW UINT32 ampCaliDivr: 14;
        RO UINT32 rsv0: 2;
    } bits;
} PllReg0S;

typedef union PllReg1S {
    UINT32 val;
    struct {
        RW UINT32 ampCtrlLoad: 6;
        RO UINT32 rsv0: 2;
        RW UINT32 freqCaliCnt1Size: 3;
        RO UINT32 rsv1: 1;
        RW UINT32 freqCaliCnt2Size: 3;
        RO UINT32 rsv2: 1;
        RW UINT32 freqLoad: 16;
    } bits;
} PllReg1S;

typedef union PllReg3S {
    UINT32 val;
    struct {
        RW UINT32 regLdo120P9VSelbit3: 1;
        RW UINT32 regVddrCoreSel: 3;
        RW UINT32 regVddrCpSel: 3;
        RW UINT32 regIcpSel: 5;
        RW UINT32 regKvcoSel: 2;
        RW UINT32 regFracModeEn: 1;
        RW UINT32 regFracValid: 1;
        RW UINT32 regVddrDivClkSel: 3;
        RW UINT32 regVddrPiSel: 3;
        RW UINT32 shortrOv: 1;
        RW UINT32 bypassPll: 1;
        RW UINT32 enPllOv: 1;
        RW UINT32 regLdo120P5VSel: 4;
        RW UINT32 regLdo120P9VSelbit2to0: 3;
    } bits;
} PllReg3S;
typedef union PllReg4S {
    UINT32 val;
    struct {
        RW UINT32 regPiIbiashSelbit5: 1;
        RW UINT32 regPiResSel: 3;
        RW UINT32 regPiDlySel: 2;
        RW UINT32 regIndSw: 1;
        RW UINT32 regPiIbiaslSel: 6;
        RW UINT32 regPiResetExt: 1;
        RO UINT32 rsv0: 2;
        RW UINT32 regLpfCap2Sel: 3;
        RW UINT32 regLpfResSel: 3;
        RW UINT32 regDsmDivSel: 2;
        RW UINT32 regPuPi0P9V: 1;
        RW UINT32 regPd12PiIdac: 1;
        RW UINT32 regPiCkdetEn: 1;
        RW UINT32 regPiIbiashSelbit4to0: 5;
    } bits;
} PllReg4S;
typedef union PllReg5S {
    UINT32 val;
    struct {
        RW UINT32 regDccBypassNbit10to2: 9;
        RW UINT32 regDccBypass: 1;
        RW UINT32 regDccCkrefEn: 1;
        RW UINT32 regDccCmpbSel: 1;
        RW UINT32 regDccLoadEn: 1;
        RW UINT32 regDccSkewEn: 1;
        RW UINT32 regDccStepEn: 1;
        RO UINT32 rsv0: 1;
        RW UINT32 regDccAsn: 6;
        RW UINT32 regDccAsp: 6;
        RW UINT32 regPuDccCmp: 1;
        RW UINT32 regResetDcc: 1;
        RW UINT32 regDccBypassNbit1to0: 2;
    } bits;
} PllReg5S;
typedef union PllReg8S {
    UINT32 val;
    struct {
        RW UINT32 regDpllEn: 1;
        RW UINT32 regDpllLoadEn: 1;
        RW UINT32 regDpllFracSel: 2;
        RW UINT32 regDpllEnIntgSatDet: 1;
        RW UINT32 regDpllEnFracSatDet: 1;
        RW UINT32 regDpllUpDnSwap: 1;
        RW UINT32 regModeDutySel: 1;
        RO UINT32 rsv1: 8;
        RW UINT32 regDpllPdivRef: 11;
        RO UINT32 rsv0: 5;
    } bits;
} PllReg8S;

typedef union PllReg11S {
    UINT32 val;
    struct {
        RW UINT32 regHrx1CdrSel: 1;
        RW UINT32 regHrx2CdrSel: 1;
        RW UINT32 regCkRxCdrDivEn: 1;
        RW UINT32 regCkRxCdrDivRatio: 5;
        RW UINT32 regDivToApcPdiv: 8;
        RW UINT32 regDivToLpllPdiv: 13;
        RW UINT32 regDivToLpllEn: 1;
        RW UINT32 regDivToLpllRst: 1;
        RW UINT32 regPllFbdivEnReflessMode: 1;
    } bits;
} PllReg11S;

/***********regBlock HPLL member: pllReg12 def offset: 0x11*********************************/
typedef union PllReg12S {
    UINT32 val;
    struct {
        RW UINT32 regEnPllOw: 1;
        RW UINT32 regEnPllOwVal: 1;
        RW UINT32 regRxCdrFllUpPolarity: 1;
        RW UINT32 regRxCdrFllUpSel: 1;
        RW UINT32 regRstPllOwVal: 1;
        RW UINT32 regRstPllOw: 1;
        RW UINT32 regFbdivEnOwVal: 1;
        RW UINT32 regFbdivEnOw: 1;
        RW UINT32 regDivToApcPdiv: 5;
        RW UINT32 regDivToApcEn: 1;
        RW UINT32 regDivToApcRst: 1;
        RO UINT32 rsv1: 1;
        RW UINT32 regDivToDigPdiv: 13;
        RW UINT32 regDivToDigEn: 1;
        RW UINT32 regDivToDigRst: 1;
        RO UINT32 rsv0: 1;
    } bits;
} PllReg12S;
typedef struct PllRegTbl {
    RW volatile UINT32 puResetnPll;
    RW volatile UINT32 pllRegRefSel;
    RW volatile UINT32 pllRegFbcPdiv;
    RW volatile UINT32 pllTempCodePll;
    RW volatile UINT32 pllTempVldPll;
    RW volatile UINT32 pllReg0;
    RW volatile UINT32 pllReg1;
    RW volatile UINT32 pllReg2;
    RW volatile UINT32 pllReg3;
    RW volatile UINT32 pllReg4;
    RW volatile UINT32 pllReg5;
    RW volatile UINT32 pllReg6;
    RW volatile UINT32 pllReg7;
    RW volatile UINT32 pllReg8;
    RW volatile UINT32 pllReg9;
    RW volatile UINT32 pllReg10;
    RW volatile UINT32 pllReg11;
    RW volatile UINT32 pllReg12;
    RO volatile UINT32 pllRpt0;
    RO volatile UINT32 pllRpt1;
    RO volatile UINT32 pllRpt2;
    RO volatile UINT32 pllRpt3;
    RO volatile UINT32 pllPllLock;
    WC volatile UINT32 pllPllLockLos;
} PllRegTbl;

VOID SREI_PllFreCodeSet(PllRegTbl *pllTbl, UINT32 pdiv, UINT32 frac)
{
    RegRefSelS fracCfg;
    PllReg3S vaild;
    RegisterWrite(pllTbl->pllRegFbcPdiv, pdiv);
    RegisterRead(fracCfg.val, pllTbl->pllRegRefSel);
    fracCfg.bits.regFbcFdiv = frac;
    RegisterWrite(pllTbl->pllRegRefSel, fracCfg.val);
    RegisterRead(vaild.val, pllTbl->pllReg3);
    vaild.bits.regFracValid = 0;
    RegisterWrite(pllTbl->pllReg3, vaild.val);
    MCU_DelayUs(1);
    vaild.bits.regFracValid = 1;
    RegisterWrite(pllTbl->pllReg3, vaild.val);
    MCU_DelayUs(1);
    vaild.bits.regFracValid = 0;
    RegisterWrite(pllTbl->pllReg3, vaild.val);
    MCU_DelayUs(1);
    vaild.bits.regFracValid = 1;
    RegisterWrite(pllTbl->pllReg3, vaild.val);
    MCU_DelayUs(1);
    vaild.bits.regFracValid = 0;
    RegisterWrite(pllTbl->pllReg3, vaild.val);
}

VOID SREI_PllDutyCycleSet(PllRegTbl *pllTbl, UINT8 en)
{
    PllReg5S dutyCfg;
    RegisterRead(dutyCfg.val, pllTbl->pllReg5);
    dutyCfg.bits.regDccStepEn = 0x1;
    dutyCfg.bits.regDccCmpbSel = 0x1;
    dutyCfg.bits.regDccCkrefEn = 0x1;
    dutyCfg.bits.regPuDccCmp = 0x1;
    RegisterWrite(pllTbl->pllRegRefSel, dutyCfg.val);
}
VOID SREI_HostPllSllpBypass(UINT8 bypassEn)
{
    PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
    PllReg0S bypassCfg;
    RegisterRead(bypassCfg.val, pllTbl->pllReg0);
    bypassCfg.bits.bySllp = bypassEn;
    RegisterWrite(pllTbl->pllReg0, bypassCfg.val);
}

VOID SREI_AnaRxAcqEn(UINT8 en)
{
    UINT32 acqEnReg;
    volatile UINT32 *rxBaseAddr;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)ANA_BASEADDR;
    rxBaseAddr = &anaRxTbl[0x44];
    RegisterRead(acqEnReg, rxBaseAddr[34]);
    acqEnReg &= ~(0x1 << 27);
    acqEnReg |= ((UINT32)en << 27);
    RegisterWrite(rxBaseAddr[34], acqEnReg);
    acqEnReg &= ~(0x1 << 26);
    RegisterWrite(rxBaseAddr[34], acqEnReg);
    acqEnReg |= ((UINT32)en << 26);
    RegisterWrite(rxBaseAddr[34], acqEnReg);
}


VOID SREI_AnaRxCdrEn(UINT8 en)
{
    UINT32 cdrEnReg;
    volatile UINT32 *rxBaseAddr;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)ANA_BASEADDR;
    rxBaseAddr = &anaRxTbl[0x44];
    RegisterRead(cdrEnReg, rxBaseAddr[0]);
    cdrEnReg &= ~(0X1 << 31);
    cdrEnReg |= ((UINT32)en << 31);
    RegisterWrite(rxBaseAddr[0], cdrEnReg);
}

UINT32 PllFreqCodeGet(VOID)
{
    return (UINT32)(g_acqCode);
}

VOID SREI_HostPllAcqSet(UINT8 acqEn, UINT8 loadEn)
{
    PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
    UINT32 freqCode;
    PllReg0S bypassCfg;
    PllReg1S freCfg;
    RegisterRead(bypassCfg.val, pllTbl->pllReg0);
    bypassCfg.bits.byAmp = acqEn;
    bypassCfg.bits.byFreq = acqEn;
    bypassCfg.bits.bySllp = acqEn;
    RegisterWrite(pllTbl->pllReg0, bypassCfg.val);

    if (acqEn == SRE_ENABLE) {
        SREI_AnaRxAcqEn(acqEn);
        SREI_AnaRxCdrEn(acqEn);
    }

    if (loadEn == SRE_ENABLE) {
        freqCode = PllFreqCodeGet();
        RegisterRead(freCfg.val, pllTbl->pllReg1);
        freCfg.bits.freqLoad = freqCode;
        RegisterWrite(pllTbl->pllReg1, freCfg.val);
    }
}

VOID SREI_HostPllOpenLoop(UINT8 owEn, UINT8 owVal)
{
    PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
    PllReg12S openLoopCfg;
    RegisterRead(openLoopCfg.val, pllTbl->pllReg12);
    openLoopCfg.bits.regEnPllOwVal = owVal;
    openLoopCfg.bits.regEnPllOw = owEn;
    RegisterWrite(pllTbl->pllReg12, openLoopCfg.val);
}

VOID SREI_HostPllSllpLoopFromRx(UINT8 en)
{
    PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
    PllReg12S loopCfg;
    RegisterRead(loopCfg.val, pllTbl->pllReg12);
    loopCfg.bits.regRxCdrFllUpPolarity = 0x0;
    loopCfg.bits.regRxCdrFllUpSel = en;
    RegisterWrite(pllTbl->pllReg12, loopCfg.val);
}
VOID SREI_PllClkSel(UINT8 clkSrc)
{
    PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
    PllReg0S clkSelReg;
    PllReg11S cdrSelReg;
    RegRefSelS refSelReg;
    RegisterRead(clkSelReg.val, pllTbl->pllReg0);
    if ((clkSrc == PLL_DS_XTAL_SRC) || (clkSrc == PLL_US_HPLL_REFCLK_SRC) || (clkSrc == PLL_US_XTAL_SRC)) {
        clkSelReg.bits.regRefckSel = 0;
    } else {
        clkSelReg.bits.regRefckSel = 1;
    }
    RegisterWrite(pllTbl->pllReg0, clkSelReg.val);
    if (clkSrc < PLL_US_HPLL_REFCLK_SRC) {
        return;
    }
    RegisterRead(cdrSelReg.val, pllTbl->pllReg11);
    RegisterRead(refSelReg.val, pllTbl->pllRegRefSel);
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
    RegisterWrite(pllTbl->pllReg11, cdrSelReg.val);
    RegisterWrite(pllTbl->pllRegRefSel, refSelReg.val);

}

VOID SREI_PllFbdivEnReflessMode(UINT8 enReflessMode)
{
    PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
    PllReg11S cfgVal;
    RegisterRead(cfgVal.val, pllTbl->pllReg11);
    cfgVal.bits.regPllFbdivEnReflessMode = enReflessMode;
    RegisterWrite(pllTbl->pllReg11, cfgVal.val);
    return;
}


VOID SREI_AnaRxDtlManualEn(UINT8 en)
{
    UINT32 dtlManReg;
    volatile UINT32 *rxBaseAddr;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)ANA_BASEADDR;
    rxBaseAddr = &anaRxTbl[0x44];
    RegisterRead(dtlManReg, rxBaseAddr[15]);
    dtlManReg &= ~0x3;
    dtlManReg |= ((UINT32)en << 0);
    dtlManReg |= ((UINT32)en << 1);
    RegisterWrite(rxBaseAddr[15], dtlManReg);
}
VOID SREI_AnaRxCdrAcqEn(UINT8 en)
{
    UINT32 cdrEnReg;
    volatile UINT32 *rxBaseAddr;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)ANA_BASEADDR;
    rxBaseAddr = &anaRxTbl[0x44];
    RegisterRead(cdrEnReg, rxBaseAddr[29]);
    cdrEnReg &= ~(0x1 << 25);
    cdrEnReg |= ((UINT32)en << 25);
    RegisterWrite(rxBaseAddr[29], cdrEnReg);
}

VOID SREI_AnaRxDtlLowGainEn(UINT8 en)
{
    UINT32 dtlGainReg;
    volatile UINT32 *rxBaseAddr;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)ANA_BASEADDR;
    rxBaseAddr = &anaRxTbl[0x44];
    RegisterRead(dtlGainReg, rxBaseAddr[34]);
    dtlGainReg |= 0x1 << 24;
    RegisterWrite(rxBaseAddr[34], dtlGainReg);
}

SRE_BOOL SREI_AnaCdrIsLock(VOID)
{
    UINT32 cdrLock;
    volatile UINT32 *anaRxTbl = (volatile UINT32 *)ANA_BASEADDR;
    RegisterRead(cdrLock, anaRxTbl[0x3e]);
    if ((cdrLock & 0x1) == 0x1) {
        return SRE_TRUE;
    } else {
        return SRE_FALSE;
    }
}

UINT16 SREI_PllAcqCodeGet(VOID)
{
    PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
    UINT32 rpt;
    RegisterRead(rpt, pllTbl->pllRpt1);
    return (UINT16)(rpt & 0xfff);
}

SRE_BOOL SREI_PllIsLock()
{
    PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
    UINT32 lock;
    RegisterRead(lock, pllTbl->pllPllLock);
    if (lock == 0x1) {
        return SRE_TRUE;
    } else {
        return SRE_FALSE;
    }
}
SRE_BOOL SREI_PllIsHisUnLock()
{
    PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
    UINT32 lock;
    RegisterRead(lock, pllTbl->pllPllLockLos);
    RegisterWrite(pllTbl->pllPllLockLos, 1);
    if (lock == 0x1) {
        return SRE_TRUE;
    } else {
        return SRE_FALSE;
    }
}
VOID SREI_PllFracDsmDivConfig(VOID)
{
   PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
   PllReg4S pllReg4;
   RegisterRead(pllReg4.val, pllTbl->pllReg4);
   pllReg4.bits.regDsmDivSel = 0;
   RegisterWrite(pllTbl->pllReg4, pllReg4.val); 
}
VOID SREI_PllFracModeCfg(UINT8 fracMode)
{
    PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
    PllReg3S pllReg3;
    RegisterRead(pllReg3.val, pllTbl->pllReg3);
    pllReg3.bits.regFracModeEn = fracMode;
    RegisterWrite(pllTbl->pllReg3, pllReg3.val);
}
UINT32 SRE_HpllInit(UINT8 en, DOUBLE refClk, DOUBLE fre, UINT8 mode, UINT8 postDivRatio)
{
    PllRegTbl *pllTbl = (PllRegTbl *)HPLL_BASEADDR;
    volatile UINT32 *iicTbl = (volatile UINT32 *)IIC_CFG_BASEADDR;
    PllReg8S dpllCfg;
    PllReg12S pllBypassCfg;
    PuResetnPllS puCfg;
    UINT32 pdiv;
    UINT32 frac;
    UINT8 vcoDiv;
    UINT8 clkSrc;
    RegRefSelS divPostCfg;
    PllReg11S hpllRefclkSrcDibRatio;
    // step 2 pd pu
    puCfg.val = 0;
    RegisterWrite(iicTbl[1], puCfg.val);
    if (en == SRE_DISABLE) {
        return SRE_SUCCESS;
    }
    puCfg.bits.puPll = 0x1;
    RegisterWrite(iicTbl[1], puCfg.val);
    RegisterRead(pllBypassCfg.val, pllTbl->pllReg12);
    UINT32 digDiv = (UINT32)(ceil(fre / 200000000) / 2 + 1);
    pllBypassCfg.bits.regDivToDigPdiv = digDiv;
    if ((mode == DSP_DS_ACQ_MODE) || (mode == DSP_DS_SLLP_MODE)) {
        pllBypassCfg.bits.regRstPllOw = 0x1;
        pllBypassCfg.bits.regRstPllOwVal = 0x1;
        RegisterWrite(pllTbl->pllReg12, pllBypassCfg.val);
    } else {
        pllBypassCfg.bits.regRstPllOw = 0x0;
        pllBypassCfg.bits.regRstPllOwVal = 0x0;
        RegisterWrite(pllTbl->pllReg12, pllBypassCfg.val);
    }
    // step2.1 acq ÅäÖÃ
    if ((mode == DSP_DS_ACQ_MODE) || (mode == DSP_DS_SLLP_MODE)) {
        SREI_HostPllAcqSet(SRE_ENABLE, SRE_ENABLE);
        SREI_AnaRxDtlManualEn(SRE_ENABLE);
        SREI_AnaRxCdrAcqEn(SRE_ENABLE);
        SREI_AnaRxDtlLowGainEn(SRE_DISABLE);
        SREI_HostPllOpenLoop(SRE_ENABLE, 0x0);
        SREI_PllFbdivEnReflessMode(SRE_ENABLE);
    } else if (mode == DSP_DS_ATE_MODE) {
        SREI_HostPllAcqSet(SRE_DISABLE, SRE_DISABLE);
        SREI_AnaRxDtlManualEn(SRE_DISABLE);
        SREI_AnaRxCdrAcqEn(SRE_DISABLE);
        SREI_AnaRxDtlLowGainEn(SRE_DISABLE);
        SREI_HostPllOpenLoop(SRE_DISABLE, 0x0);
        SREI_PllFbdivEnReflessMode(SRE_DISABLE);
    }
    if (mode == DSP_DS_SLLP_MODE) {
        SREI_HostPllSllpLoopFromRx(SRE_ENABLE);
    } else if ((mode == DSP_DS_ACQ_MODE) || (mode == DSP_DS_ATE_MODE)) {
        SREI_HostPllSllpLoopFromRx(SRE_DISABLE);
    }
    // step3 refclksel ·ÅÖÃÔÚ³õÊ¼»¯Ç°Ãæ£¬¼õÉÙÈë²Î¸öÊý
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

    // step 4 dpll¹¦ÄÜÅäÖÃ
    RegisterRead(dpllCfg.val, pllTbl->pllReg8);
    dpllCfg.bits.regDpllFracSel = 0x0;
    RegisterWrite(pllTbl->pllReg8, dpllCfg.val);

   // step 5 ÎÂ²¹
    // step 6 Ð¡Êý·ÖÆµÖµÅäÖÃ
    UINT8 fracMode = 1;
    if (fracMode == 0) { // æ•´æ•°åˆ†é¢‘
        pdiv = (UINT32)floor(fre / refClk);
        frac = (UINT32)((fre / refClk / pdiv - 1) * (0x1 << 26)) & 0xffffff;
        SREI_PllFreCodeSet(pllTbl, pdiv, frac);
    } else { // å°æ•°åˆ†é¢‘£¬Ð¡Êý·ÖÆµ
        pdiv = (UINT32)floor(fre / refClk / 4);
        frac = (UINT32)((fre / refClk / pdiv - 1) * (0x1 << 25)) & 0xffffff;
        SREI_PllFreCodeSet(pllTbl, pdiv, frac);
        SREI_PllFracDsmDivConfig();
    }
    SREI_PllFracModeCfg(fracMode);

    // step 7 é…ç½®åˆ†é¢‘æ¯”
    vcoDiv = postDivRatio;
    RegisterRead(divPostCfg.val, pllTbl->pllRegRefSel);
    divPostCfg.bits.regDivPostSel = vcoDiv;
    RegisterWrite(pllTbl->pllRegRefSel, divPostCfg.val);
    RegisterRead(hpllRefclkSrcDibRatio.val, pllTbl->pllReg11);
    if (vcoDiv == SRE_ENABLE) {
        hpllRefclkSrcDibRatio.bits.regDivToLpllPdiv = 0X50 >> 1;
    } else {
        hpllRefclkSrcDibRatio.bits.regDivToLpllPdiv = 0X50;
    }
    RegisterWrite(pllTbl->pllReg11, hpllRefclkSrcDibRatio.val);

    // step8 é‡Šæ”¾reset
    if ((mode == DSP_DS_ACQ_MODE) || (mode == DSP_DS_SLLP_MODE)) {
        RegisterRead(pllBypassCfg.val, pllTbl->pllReg12);
        pllBypassCfg.bits.regRstPllOw = 0x1;
        pllBypassCfg.bits.regRstPllOwVal = 0x0;
        RegisterWrite(pllTbl->pllReg12, pllBypassCfg.val);
    }
    puCfg.bits.rstnPll = 0x1;
    RegisterWrite(iicTbl[1], puCfg.val);
   // MCU_DelayUs(100);
   MCU_DelayUs(1000);
    if ((mode == DSP_DS_ACQ_MODE) || (mode == DSP_DS_SLLP_MODE)) {
        if (SREI_AnaCdrIsLock() == SRE_FALSE) {
            return PLL_WAIT_CDR_LOCK_OVERTIME_ERR;
        }
        if (mode == DSP_DS_ACQ_MODE) {
            SREI_HostPllOpenLoop(SRE_ENABLE, 0x1);
        }
    }
    if (mode == DSP_DS_ATE_MODE) {
        g_acqCode = SREI_PllAcqCodeGet();
    }
    return SRE_SUCCESS;
}


UINT64 g_hpllFre[LANE_MODE_NUM] = {
    [LANE_MODE_INVALID]         = 12441600000,
    [LANE_MODE_1P244]           = 4976640000,
    [LANE_MODE_1P25]            = 10000000000,
    [LANE_MODE_2P488]           = 4976640000,
    [LANE_MODE_2P5]             = 10000000000,
    [LANE_MODE_3P125]           = 6250000000,
    [LANE_MODE_5P]              = 5000000000,
    [LANE_MODE_9P95]            = 4976640000,
    [LANE_MODE_10P3125]         = 10312500000,
    [LANE_MODE_12P44]           = 6220800000,
    [LANE_MODE_12P5]            = 6250000000,
    [LANE_MODE_24P88_NRZ]       = 12441600000,
    [LANE_MODE_24P88_PAM4]      = 12441600000,
    [LANE_MODE_25P78125_NRZ]    = 12890625000,
    [LANE_MODE_25P78125_PAM4]   = 12890625000,
    [LANE_MODE_26P5625_NRZ]     = 13281250000,
    [LANE_MODE_26P5625_PAM4]    = 13281250000,
    [LANE_MODE_49P76_NRZ]       = 12441600000,
    [LANE_MODE_49P76_PAM4]      = 12441600000,
    [LANE_MODE_51P5625_NRZ]     = 12890625000,
    [LANE_MODE_51P5625_PAM4]    = 12890625000,
    [LANE_MODE_53P125_NRZ]      = 13281250000,
    [LANE_MODE_53P125_PAM4]     = 13281250000,
};


/*
´Ëº¯ÊýÖ»¸ºÔðÏÂÐÐPLL£¬ÉÏÐÐµÄPLLÓÉFW¸ºÔð
workModeÈ¡ÖµÓÚg_hpllFre
*/

UINT32 SRE_HpllSetup(UINT8 workMode)
{
    UINT8 isLock;
    UINT16 freCode;
    UINT32 waitCnt;
    UINT32 *workModeCfg = (UINT32 *)WORKMODE_BASEADDR;
    RegisterWrite(workModeCfg[0], workMode);
    UINT8 postDivRatio;
    if (workMode >= LANE_MODE_24P88_NRZ && workMode <= LANE_MODE_26P5625_PAM4) {
        postDivRatio = 1;
    } else {
        postDivRatio = 0;
    }
    SRE_HpllInit(SRE_ENABLE, 38400000, g_hpllFre[workMode], 0, postDivRatio);
    waitCnt = 0;
    do {
        MCU_DelayUs(10);
        isLock = SREI_PllIsLock();
        waitCnt++;
    } while ((isLock == SRE_FALSE) && (waitCnt < 1000));
    isLock = SREI_PllIsLock();
    if (isLock != SRE_TRUE) {
        return HPLL_LOCK_ERR;
    }
    freCode = SREI_PllAcqCodeGet();
    // printf("freq code:%d\n\r", freCode);
    return SRE_SUCCESS;
}

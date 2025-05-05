/***********************************************************************************

 * 文 件 名   : dsp_fsl_reg.h
 * 负 责 人   : fangzhe
 * 创建日期   : 2025年4月16日
 * 文件描述   : dsp的寄存器
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#ifndef _DSP_FSL_REG_H_
#define _DSP_FSL_REG_H_

/*APC使能：handle.WriteReg(0x10c, 0xffffffff)（执行一次即可）；*/
#define DSP_APC_EN_REG     (0x10c << 2)

/*Bypass使能+Bypass_code<11:0>：handle.WriteReg(0x10f, 0x09601640)（bypass使能并输出80mA电流）*/
#define DSP_LD_IBIAS_REG    (0x10f << 2)

#define DSP_SOA_IBIAS_REG   (0x10c << 2)


#endif
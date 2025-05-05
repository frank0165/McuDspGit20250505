/***********************************************************************************

 * 文 件 名   : dev_reg_address.h
 * 负 责 人   : fangzhe
 * 创建日期   : 2025年3月30日
 * 文件描述   : 定义设备定址或者寄存器地址
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#ifndef _DEV_REG_ADDRESS_H_
#define _DEV_REG_ADDRESS_H_

/* add by fangzhe, 20250330, 原因:50G driver地址 */
#define GN7161_SLAVE_ADDRESS    0xAC

//50G dsp driver,写地址是0xAE;
//读的地址实质是0xAC;((0x15 <<2 + 2)  << 1)
//DSP芯片对读与写的地址做了改动；在本程序中还是用0xAE,当为read时，由
//master i2c协议栈做了内部处理转为0xAC
#define DSP_FSL_SLAVE_ADDRESS    0xAE//((0x15 <<2 + 3)  << 1)

/* add by fangzhe, 20250330, 原因:10G driver地址 */
#define GN7153_SLAVE_ADDRESS    0x48


/* add by fangzhe, 20250330, 原因:1G driver地址 */
#define UX3326_SLAVE_ADDRESS    0xC6





#endif

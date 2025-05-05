/***********************************************************************************

 * 文 件 名   : dsp_fsl.c
 * 负 责 人   : fangzhe
 * 创建日期   : 2025年3月26日
 * 文件描述   : dsp_fsl驱动
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#include "user_config.h"
#include "stdio.h"
#include "string.h"

#if defined( FH_IC_DSP_HARDWARE) && (FH_IC_DSP_HARDWARE == CFG_YES)

#include "mcu_data_type.h"
#include "dsp_fsl.h"
#include "ip_op.h"
#include "mcu_pin_type.h"
#include "mcu_system_comm.h"
#include "i2c_opt_ie.h"
#include "dev_reg_address.h"
#include "mcu_global_vars_param.h"
//#include "reg_op.h"

void dsp_fsl_reg_read(uint32_t reg,uint32_t *val);

void dsp_fsl_reset()
{
     gpio_bit_reset(GPIO_DSP_RST_PORT, GPIO_DSP_RST_PIN);
    fh_delay_ms(1000);
    gpio_bit_set(GPIO_DSP_RST_PORT, GPIO_DSP_RST_PIN);
    

   // gpio_mode_set(GPIO_50G_TXDISBL_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,GPIO_50G_TXDISBL_EN );    
	//gpio_output_options_set(GPIO_50G_TXDISBL_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_50G_TXDISBL_EN);
	gpio_bit_set(GPIO_50G_TXDISBL_PORT,GPIO_50G_TXDISBL_EN);

}


/*****************************************************************************
 * 函 数 名  : dsp_gpio_init
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月26日
 * 函数功能  : dsp的gpio初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void dsp_gpio_init()
{
    /* configure GPIO PA12 as RESET */ 
	gpio_mode_set(GPIO_DSP_RST_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_DSP_RST_PIN);    
	gpio_output_options_set(GPIO_DSP_RST_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_DSP_RST_PIN);
    
	/* configure GPIO PA1 as 50G_TXDSBL ，50G,10G,1G共用*/ 
	gpio_mode_set(GPIO_50G_TXDISBL_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,GPIO_50G_TXDISBL_EN );    
	gpio_output_options_set(GPIO_50G_TXDISBL_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_50G_TXDISBL_EN);

    /* configure GPIO PA11 as 50G LOCK ，*/ 
	gpio_mode_set(GPIO_50G_LOCK_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,GPIO_50G_LOCK_PIN );    
	gpio_output_options_set(GPIO_50G_LOCK_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_50G_LOCK_PIN);

    
      /* configure GPIO PB4 as 50G_READY ，*/ 
	gpio_mode_set(GPIO_50G_READY_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,GPIO_50G_READY_PIN );    
	gpio_output_options_set(GPIO_50G_READY_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_50G_READY_PIN);

         /* configure GPIO PB5 as 50G_LOSS ，*/ 
	gpio_mode_set(GPIO_50G_LOSS_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,GPIO_50G_LOSS_PIN );    
	gpio_output_options_set(GPIO_50G_LOSS_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_50G_LOSS_PIN);

          /* configure GPIO PF4 as D1V8_en ，*/ 
	gpio_mode_set(D1V8_EN_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,D1V8_EN_PIN );    
	gpio_output_options_set(D1V8_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, D1V8_EN_PIN);

    gpio_mode_set(D1V2_EN_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,D1V2_EN_PIN );    
	gpio_output_options_set(D1V2_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, D1V2_EN_PIN);

    gpio_mode_set(D0V75_EN_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,D0V75_EN_PIN );    
	gpio_output_options_set(D0V75_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, D0V75_EN_PIN);

   
    
}


void dsp_fsl_txdisable_ctrl(uint8_t ctr_switch)
{
    if(ctr_switch == 0)
    {
        gpio_bit_reset(GPIO_50G_TXDISBL_PORT,GPIO_50G_TXDISBL_EN);
    }
    else
    {
        gpio_bit_set(GPIO_50G_TXDISBL_PORT,GPIO_50G_TXDISBL_EN);
    }
}

extern void master_dsp_fsl_reg_4byte_size_read(uint32_t slave_address,uint32_t reg,uint8_t *p_buffer,
	uint32_t buffer_len);


extern void ddm_50g_set_rx_vapd(float apd_vcc);


/*****************************************************************************
 * 函 数 名  : dsp_fsl_init
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年3月26日
 * 函数功能  : dsp初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void dsp_fsl_init()
{
    uint32_t val = 0xffffffff;
    uint32_t startSecs =0;
    uint32_t endSecs = 0;
    uint32_t ret = 0;
    dsp_gpio_init();  
    
    /* add by fangzhe, 20250401, 原因:dsp的rst脚是复位，否则芯片无法正常工作 */
    dsp_fsl_reset();
    fh_delay_ms(10);

    //ddm_50g_set_rx_vapd(18);
    
    //LANE_MODE_49P76_PAM4 = 18
   // SRE_DspSetUp(18, 0x8064c00);  
   // system_delay_ms(1000);

 
     
   
    //0x00010000
    //0x00010001
    //0x0000000s
    
}

uint32_t dsp_fsl_ic_download()
{
    uint32_t ret = 0;
    uint32_t reg_addr = 0;
    uint32_t val = 0;

    
   ret = SRE_DspSetUp(18, 0x8064c00);  
     system_delay_ms(1000);

#if 0
         //临时借用这个操作，后需一定要删除。
    reg_addr = 0x00000430;
    val = 0xffffffff;
    dsp_fsl_reg_write(reg_addr, val);

    reg_addr = 0x0000043c;
    val = 0x09601640;
    dsp_fsl_reg_write(reg_addr, val);

    reg_addr = 0x00000438;
    val = 0x64066480;
    dsp_fsl_reg_write(reg_addr, val);
#endif
     return ret;

}

void dsp_fsl_reg_write(uint32_t reg,uint32_t val)
{
    uint8_t txBuff[12];
    set_u32(txBuff,reg);
    set_u32(&txBuff[4],val);
    master_dsp_fsl_reg_4byte_write(DSP_FSL_SLAVE_ADDRESS, txBuff, 8);
    return;
}

void dsp_fsl_reg_read(uint32_t reg,uint32_t *val)
{
    uint8_t rxBuff[12];
    if(NULL == val)
    {
        return;
    }
    master_dsp_fsl_reg_4byte_size_read(DSP_FSL_SLAVE_ADDRESS,reg,rxBuff,4);

    *val = get_u32(rxBuff);
}

void dsp_fsl_continue_write(uint32_t reg,uint8_t *buff,uint32_t buff_len)
{
    uint8_t txBuff[200];
    uint32_t reg_size = sizeof(reg);
    if((reg_size + buff_len) > sizeof(txBuff)|| NULL == buff)
    {
        return;
    }
    set_u32(txBuff,reg);
    memcpy(&txBuff[4],buff,buff_len);
    master_dsp_fsl_reg_4byte_write(DSP_FSL_SLAVE_ADDRESS, txBuff, buff_len + reg_size);
}

void dsp_fsl_continue_read(uint32_t addr, uint8_t *Buff, uint32_t len)
{
    if(NULL == Buff)
    {
        return;
    }
    master_dsp_fsl_reg_4byte_size_read(DSP_FSL_SLAVE_ADDRESS,addr,Buff,len);

    return;
}

void dsp_fsl_apc_auto_enable_ctrl(uint8_t ctrl_switch)
{
    if(ctrl_switch)
    {
        
    }
    else
    {
        
    }
}

extern char SREI_PllIsLock();
void dsp_fsl_run_hpll()
{
    if(1 != SREI_PllIsLock())
    {
        SRE_HpllSetup(18);
    }

    return;
}

void dsp_fsl_run_ds_cali()
{
    
}



#endif

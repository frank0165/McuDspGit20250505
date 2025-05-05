#include <stdio.h>
#include <string.h>
#include "mcu_data_type.h"
#include "mcu_system_comm.h"
#include "thermistor_rth.h"
#include "mcu_global_vars_param.h"
#include "ip_op.h"
#include "dsp_fsl.h"
#include "mcu_pin_type.h"



/*****************************************************************************
 * 函 数 名  : dsp_fsl_i2c_start_download_reg_write
 * 负 责 人  : fangzhe
 * 创建日期  : 2025年4月18日
 * 函数功能  : 
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void dsp_fsl_i2c_start_download_reg_write(uint8_t *pbuff,uint32_t bufflen)
{		
    printf("download\r\n");

    uint16_t tmp_volt = 0;
	/*参数检查*/
	if(NULL == pbuff)
	{
		return;
	}

	/*检查对应的寄存器*/
	if(pbuff[0] != TEST_DSP_FSL_DOWNLOAD_REG)
	{
		return;
	}

   // dsp_fsl_reset();
	dsp_fsl_ic_download();
   
}

//TEST_DSP_FSL_INFO_REG


uint8_t g_dsp_info[40];
uint8_t g_dsp_pll[20];

void dsp_fsl_i2c_info_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
	/*参数初始化*/	

    uint32_t inputPara[10];
    uint32_t outputPara[10];
    uint32_t ret = 0;
	
	/* add by fz, 20230625, 原因:参数合法值检查 */
	if(TEST_DSP_FSL_INFO_REG != regaddr)
	{
		return;
	}

	if(NULL == pbuff)
	{
		return;
	}	
    

   memcpy(pbuff,g_dsp_info,16);
   memcpy(&pbuff[16],g_dsp_pll,8);
    

	return;
    
	
}

void data_path_config_init(uint8_t flg)
{
    uint32_t inputPara[10];
    uint32_t outputPara[10];
    uint32_t ret = 0;  
    
    
     memset(inputPara, 0, sizeof(SystemDatapathParaInitS));
     memset(outputPara, 0, sizeof(SystemDatapathParaInitS));
    SystemDatapathParaInitS *dataPath = (SystemDatapathParaInitS *)inputPara;
    dataPath->isCfgFlag = 1;
    dataPath->rxCfgMask = 3;
    dataPath->txCfgMask = 3;
    // dataPath->laneDatapathCfg.bits.hostRxDatapathCfg.val = 0;
    dataPath->laneDatapathCfg.bits.hostRxDatapathCfg.rxGrayEn = 1;
    dataPath->laneDatapathCfg.bits.hostRxDatapathCfg.rxSwapEn = 1;
    // dataPath->laneDatapathCfg.bits.hostTxDatapathCfg.val = 0;
    // dataPath->laneDatapathCfg.bits.lineRxDatapathCfg.val = 0;
    dataPath->laneDatapathCfg.bits.lineRxDatapathCfg.rxGrayEn = 1;
    dataPath->laneDatapathCfg.bits.lineRxDatapathCfg.rxSwapEn = 1;
    // dataPath->laneDatapathCfg.bits.lineTxDatapathCfg.val = 0;

     dataPath->laneDatapathCfg.bits.lineTxDatapathCfg.txLutSel = flg;

      // func 0x0001_xxxx cata
      //0x0001_0001
    ret = SRE_CmdSend(API_PARA_INIT_CAT, DATAPATH_PARA_INIT, inputPara, outputPara, 9);
    if (ret != SRE_SUCCESS) 
    {
        
    }

    memset(inputPara, 0, sizeof(SystemDatapathParaInitS));
    memset(outputPara, 0, sizeof(SystemDatapathParaInitS));
    dataPath->isCfgFlag = 0;//获取配置

    #if 0
    dataPath->rxCfgMask = 3;
    dataPath->txCfgMask = 3;
    // dataPath->laneDatapathCfg.bits.hostRxDatapathCfg.val = 0;
    dataPath->laneDatapathCfg.bits.hostRxDatapathCfg.rxGrayEn = 1;
    dataPath->laneDatapathCfg.bits.hostRxDatapathCfg.rxSwapEn = 1;
    // dataPath->laneDatapathCfg.bits.hostTxDatapathCfg.val = 0;
    // dataPath->laneDatapathCfg.bits.lineRxDatapathCfg.val = 0;
    dataPath->laneDatapathCfg.bits.lineRxDatapathCfg.rxGrayEn = 1;
    dataPath->laneDatapathCfg.bits.lineRxDatapathCfg.rxSwapEn = 1;
    // dataPath->laneDatapathCfg.bits.lineTxDatapathCfg.val = 0;

    dataPath->laneDatapathCfg.bits.lineTxDatapathCfg.txLutSel = flg;
    #endif
    
    /*读取datapath*/
    ret = SRE_CmdSend(API_PARA_INIT_CAT, DATAPATH_PARA_INIT, inputPara, outputPara, 9);
    if (ret != SRE_SUCCESS) 
    {
        
    }
    
   // system_delay_ms(delay);

    inputPara[0] = 0x1;
    inputPara[1] = 0x2;
     // func 0x0000_xxxx cata
    ret = SRE_CmdSend(API_RUN_CTRL_CAT, CHIP_RUN, inputPara, outputPara, 9);
    if (ret != SRE_SUCCESS) 
    {
        
    }    
}

void dsp_fsl_i2c_data_path_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
    uint32_t flg = 0;
    /*参数检查*/
	if(NULL == pbuff)
	{
		return;
	}

	/*检查对应的寄存器*/
	if(pbuff[0] != TEST_DSP_FSL_INFO_REG)
	{
		return;
	}

    flg = pbuff[1];

    if(flg > 0)
    {
        data_path_config_init(1);
    }
    else
    {
         data_path_config_init(0);
    }
    
}


void dsp_fsl_i2c_rst_pin_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
    uint32_t time = 0;
    /*参数检查*/
	if(NULL == pbuff)
	{
		return;
	}

	/*检查对应的寄存器*/
	if(pbuff[0] != TEST_DSP_FSL_RSTPIN_REG)
	{
		return;
	}

  // dsp_fsl_reset();

  time = get_u32(&pbuff[1]);

    if(0 == time)
    {
        time = 500;
    }

    gpio_bit_reset(GPIO_DSP_RST_PORT, GPIO_DSP_RST_PIN);
    fh_delay_ms(time);
    gpio_bit_set(GPIO_DSP_RST_PORT, GPIO_DSP_RST_PIN);
    

   // gpio_mode_set(GPIO_50G_TXDISBL_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,GPIO_50G_TXDISBL_EN );    
	//gpio_output_options_set(GPIO_50G_TXDISBL_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_50G_TXDISBL_EN);
	gpio_bit_set(GPIO_50G_TXDISBL_PORT,GPIO_50G_TXDISBL_EN);

}

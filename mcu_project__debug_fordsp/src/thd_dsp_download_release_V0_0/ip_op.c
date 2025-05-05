/* 
 * 外部操作功能函数
 * Copyright 2022-2023 Tauren Semiconductor.
 * Create data: 2023-9-22
 * auther: zhanglaipeng
 * email: laipeng.zhang@taurentch.net
 */

#include "do_api.h"
#include "reg_op.h"
#include "sre_basic_typedef.h"
#include "ip_op.h"
#include "sre_errcode.h"
#include "string.h"
#include "mcu_global_vars_param.h"
#include "mcu_system_comm.h"

VOID SRE_McuEnable(UINT8 en)
{
    MailboxRegTbl *mangeTbl = (MailboxRegTbl *)BYQIYUN_IP_BASE_ADDR;
    RegisterWrite(mangeTbl->mcuEnable, (UINT32)en);
}

VOID SRE_WriteBuff2Sram(UINT32 sramAddr, UINT32 *buff, UINT32 wordsLen)
{
    MailboxRegTbl *mangeTbl = (MailboxRegTbl *)BYQIYUN_IP_BASE_ADDR;
    #if (defined(EXT_CTRL_MCU) || defined(_GCC_TOOLS_))
    UINT32 wrodSend = 0;
    UINT32 wordOnce;
    while (wrodSend < wordsLen) {
        RegisterWrite(mangeTbl->sramRemapAddr, sramAddr + (wrodSend * 4));
        if ((wrodSend + g_regMaxOpNum) > wordsLen) {
            wordOnce = wordsLen - wrodSend;
        } else {
            wordOnce = g_regMaxOpNum;
        }
        RegisterWriteContinue(&mangeTbl->sramRemapData, &buff[wrodSend], wordOnce);
        wrodSend += wordOnce;
    }
    #else
    RegisterWrite(mangeTbl->sramRemapAddr, sramAddr);
    RegisterWriteContinue(&mangeTbl->sramRemapData, &buff[0], wordsLen);
    #endif
}

VOID SRE_DownloadFirmware(FwSecS *fwManage)
{
    MailboxRegTbl *mangeTbl = (MailboxRegTbl *)BYQIYUN_IP_BASE_ADDR;
    UINT32 i;
    UINT32 addr;
    RegisterWrite(mangeTbl->mcuEnable, SRE_DISABLE);
    RegisterWrite(mangeTbl->downloafdFwEn, SRE_ENABLE);
    RegisterWrite(mangeTbl->mcuEnable, SRE_ENABLE);
    addr = (UINT32)(UINTPTR)(&fwManage->fwBuff[0]);

    /* add by fangzhe, 20250504, ԭ��:������ʹ�� ��ֹԽ��
        û��fw�İ��ӣ��˴�����0xffffffff
    */
    if(fwManage->secNum > 7)
    {
        return;
    }
    
    for (i = 0; i < fwManage->secNum; i++) {
        SRE_WriteBuff2Sram(fwManage->secInfo[2 * i], (UINT32 *)addr, fwManage->secInfo[2 * i + 1] >> 2);
        addr += fwManage->secInfo[2 * i + 1];
    }
    RegisterWrite(mangeTbl->mcuEnable, SRE_DISABLE);
    RegisterWrite(mangeTbl->downloafdFwEn, SRE_DISABLE);
    RegisterWrite(mangeTbl->mcuEnable, SRE_ENABLE);
}

VOID SRE_GetSramBuff(UINT32 sramAddr, UINT32 *buff, UINT32 wordLen)
{
    MailboxRegTbl *mangeTbl = (MailboxRegTbl *)BYQIYUN_IP_BASE_ADDR;
    #if (defined(EXT_CTRL_MCU) || defined(_GCC_TOOLS_))
    UINT32 wrodRead = 0;
    UINT32 wordOnce;
    while (wrodRead < wordLen) {
        RegisterWrite(mangeTbl->sramRemapAddr, sramAddr + (wrodRead * 4));
        if ((wrodRead + g_regMaxOpNum) > wordLen) {
            wordOnce = wordLen - wrodRead;
        } else {
            wordOnce = g_regMaxOpNum;
        }
        RegisterReadContinue(&mangeTbl->sramRemapData, &buff[wrodRead], wordOnce);
        wrodRead += wordOnce;
    }
    #else
    RegisterWrite(mangeTbl->sramRemapAddr, sramAddr);
    RegisterReadContinue(&mangeTbl->sramRemapData, &buff[0], wordLen);
    #endif
}


/*
UINT32 funcCata    函数功能分类编号 0-API_FUNC_CATA_NUM
UINT32 func        函数编号 见do_api.h
UINT32 *inputPara  输入参数数组 数组长度依据函数类型不同入参个数也不同
UINT32 *outputPara 出参数组 数组长度依据函数类型不同出参个数也不同
UINT8 needWait     是否需要阻塞式等待返回结果 非0时表示需要等待返回结果
*/
UINT32 SRE_CmdSend(UINT32 funcCata, UINT32 func, UINT32 *inputPara, UINT32 *outputPara, UINT8 needWait)
{
    MailBoxManage *mangeTbl = (MailBoxManage *)BYQIYUN_IP_BASE_ADDR;
    UINT8 i;
    DoOpCmdS *op = (DoOpCmdS *)g_sreFuncArr[funcCata];
    DoOpCmdS *funPara;
    UINT32 waitTimeCntMs = 0;
    UINT32 timeOutMs;
    UINT32 finishedFlag;
    UINT32 ret;
    UINT32 startTimeCntMs = 0;
    funPara = &op[func];
    RegisterWrite(mangeTbl->cmd.funDef, (funcCata << 16) | func);
    if ((funPara->inputParaNum != 0) && (inputPara == NULL)) {
        return ERR_INPARA_IS_NULL;
    }
    for (i = 0; i < funPara->inputParaNum; i++) {
        RegisterWrite(mangeTbl->cmd.inPara[i], inputPara[i]);
    }
    RegisterWrite(mangeTbl->cmd.cmdFlag, FUNC_CMD_MAGIC_WORD);
    if (needWait == 0) {
        return SRE_SUCCESS;
    }
    timeOutMs = funPara->timeOutMs;

    
    timeOutMs = 15000;/*10 secs*/
    startTimeCntMs = MCU_SYSTEM_MS_PERIOD;
    do {
        RegisterRead(finishedFlag, mangeTbl->re.cmdFlag);
        waitTimeCntMs = MCU_SYSTEM_MS_PERIOD - startTimeCntMs;
        
        // waitTimeCntMs = ;//todo 获取已经等待的时长
    } while (((finishedFlag & FUNC_FININSH_MAGIC_MASK) != FUNC_FININSH_MAGIC_WORD) && (waitTimeCntMs < timeOutMs));
    if (waitTimeCntMs >= timeOutMs) {
        return ERR_WAITFOR_RSP_TIMEOUT;
    }
    RegisterRead(ret, mangeTbl->re.ret);
    if ((funPara->outputParaNum != 0) && (outputPara == NULL)) {
        return ERR_OUTPARA_IS_NULL;
    }
    for (i = 0; i < funPara->outputParaNum; i++) {
        RegisterRead(outputPara[i], mangeTbl->re.outPara[i]);
    }
    return ret;
}

UINT32 SRE_GetCmdResult(UINT32 funcCata, UINT32 func, UINT32 *outputPara, UINT32 *finish)
{
    MailBoxManage *mangeTbl = (MailBoxManage *)BYQIYUN_IP_BASE_ADDR;
    UINT8 i;
    DoOpCmdS *op = (DoOpCmdS *)g_sreFuncArr[funcCata];
    DoOpCmdS *funPara;
    UINT32 finishedFlag;
    UINT32 ret;
    funPara = &op[func];
    RegisterRead(finishedFlag, mangeTbl->re.cmdFlag);

    if ((finishedFlag & FUNC_FININSH_MAGIC_MASK) != FUNC_FININSH_MAGIC_WORD) {
        *finish = 0;
        return SRE_SUCCESS;
    }
    *finish = 1;
    RegisterRead(ret, mangeTbl->re.ret);
    if ((funPara->outputParaNum != 0) && (outputPara == NULL)) {
        return ERR_OUTPARA_IS_NULL;
    }
    for (i = 0; i < funPara->outputParaNum; i++) {
        RegisterRead(outputPara[i], mangeTbl->re.outPara[i]);
    }
    return ret;
}


 //LANE_MODE_49P76_PAM4 = 18
extern uint8_t g_dsp_info[40];
 extern uint8_t g_dsp_pll[20];
UINT32 SRE_DspSetUp(UINT8 workMode, UINT32 fwAddr)
{
    uint32_t inputPara[10];
    uint32_t outputPara[10];
    uint32_t ret = 0;   
    uint32_t idx = 0;
    uint32_t ms_delay = 0;
    uint32_t val = 0xffffffff;
    uint32_t startTimeMs = 0;
    uint32_t endTimeMs = 0;
    
   
   MailboxRegTbl *mangeTbl = (MailboxRegTbl *)BYQIYUN_IP_BASE_ADDR;

    memset(g_dsp_info,0,sizeof(g_dsp_info));
    memcpy(g_dsp_info,"First",6);  
    memset(g_dsp_pll,0,sizeof(g_dsp_pll));
      
    #if 0/*ԭ����*/
    ret = SRE_HpllSetup(workMode);
    if (ret != SRE_SUCCESS) {

        memset(g_dsp_info,0,sizeof(g_dsp_info));
        memcpy(g_dsp_info,"PLL:",5);
        set_u32(&g_dsp_info[6],ret);       
        return ret;
    }
    #endif

#if 1 
       /*���Դ���*/
    startTimeMs = MCU_SYSTEM_MS_PERIOD;
    do
    {
        endTimeMs = MCU_SYSTEM_MS_PERIOD - startTimeMs;
        ret = SRE_HpllSetup(workMode);
    }while(ret != SRE_SUCCESS && endTimeMs <100);
    
    if (ret != SRE_SUCCESS) 
    {

        memset(g_dsp_pll,0,sizeof(g_dsp_pll));
        memcpy(g_dsp_pll,"PLL:",5);
        set_u32(&g_dsp_pll[6],ret);       
        return ret;
    }
    else
    {
         memcpy(g_dsp_pll,"PLLOK:",7);
    }
 #endif   

    /*�����ж���ʱ����ʱ�ӳ�100ms --->200ms*/
    system_delay_ms(100);

#if 0
    val = 0xffffffff;
    RegisterRead(val,mangeTbl->mcuEnable);
    if(val == 0)
    {
         memset(g_dsp_info,0,sizeof(g_dsp_info));
         memcpy(g_dsp_info,"mcu1:",6);
         set_u32(&g_dsp_info[10],val);
         return val;
    }
#endif    
    SRE_DownloadFirmware((FwSecS *)fwAddr); 

    val = 0xffffffff;
    RegisterRead(val,mangeTbl->mcuEnable);
    if(val == 0)
    {
         memset(g_dsp_info,0,sizeof(g_dsp_info));
         memcpy(g_dsp_info,"mcu2:",6);
         set_u32(&g_dsp_info[10],val);
         return val;
    }
   
     
    ret = SRE_CmdSend(API_DFX_CTRL_CAT, MCU_TICK_GET, inputPara, outputPara, 1);
    if (ret != SRE_SUCCESS) 
     {
         memset(g_dsp_info,0,sizeof(g_dsp_info));
         memcpy(g_dsp_info,"Tick:",6);
         set_u32(&g_dsp_info[10],ret);
        return ret;
    }  

    val = 0xffffffff;
    RegisterRead(val,mangeTbl->mcuEnable);
    if(val == 0)
    {
         memset(g_dsp_info,0,sizeof(g_dsp_info));
         memcpy(g_dsp_info,"mcu3:",6);
         set_u32(&g_dsp_info[10],val);
         return val;
    }
   
    ret = SRE_CmdSend(API_DFX_CTRL_CAT, VERSION_GET, inputPara, outputPara, 9);
    if (ret != SRE_SUCCESS) 
    {
        memset(g_dsp_info,0,sizeof(g_dsp_info));
        memcpy(g_dsp_info,"Version:",8);
        set_u32(&g_dsp_info[10],ret);
    }

     val = 0xffffffff;
    RegisterRead(val,mangeTbl->mcuEnable);
    if(val == 0)
    {
         memset(g_dsp_info,0,sizeof(g_dsp_info));
         memcpy(g_dsp_info,"mcu4:",6);
         set_u32(&g_dsp_info[10],val);
         return val;
    }
   
    memset(outputPara,0,sizeof(outputPara));

    SystemParaInitS *modePara = (SystemParaInitS *)inputPara;

#if 1
    //�μ���0x0001_0000�����ó�ʼ������
    modePara->isCfgFlag = 1; //���ñ�ʶ,para0   
    modePara->txEnableMask = 0x3; //tx(Host,Lineʹ��);para2
    modePara->rxEnableMask = 0x3;//rx(Host,Lineʹ��);para1

    //�μ�,para3

    /* add begin by fangzhe, 20250429, ԭ��:����host */
    /*����ģʽLANE_MODE_49P76_PAM4*/
    modePara->laneModeCfg[0].hostBits.rxRate.bits.rateMode = LANE_MODE_49P76_PAM4;

    /*λ��64*/
    modePara->laneModeCfg[0].hostBits.rxRate.bits.dataWidth = DATA_BIT_WIDTH_64;

    /*����ģʽLANE_MODE_24P88_NRZ*/
    modePara->laneModeCfg[0].hostBits.txRate[0].bits.rateMode = LANE_MODE_24P88_NRZ;

    /*λ��32*/
    modePara->laneModeCfg[0].hostBits.txRate[0].bits.dataWidth = DATA_BIT_WIDTH_32;

    /*��С�����ʣ�LANE_MODE_INVALID���ù���*/
    modePara->laneModeCfg[0].hostBits.txRate[1].bits.rateMode = LANE_MODE_INVALID;
    modePara->laneModeCfg[0].hostBits.txRate[1].bits.dataWidth = DATA_BIT_WIDTH_8;
    modePara->laneModeCfg[0].hostBits.txRate[2].bits.rateMode = LANE_MODE_INVALID;
    modePara->laneModeCfg[0].hostBits.txRate[2].bits.dataWidth = DATA_BIT_WIDTH_8;

    /* add end by fangzhe, 20250429 */


    /* add begin by fangzhe, 20250429, ԭ��:����LANE�� */
    //�μ�para4
    /*����ģʽ:LANE_MODE_49P76_NRZ*/
    modePara->laneModeCfg[1].lineBits.txRate.bits.rateMode = LANE_MODE_49P76_NRZ;
    modePara->laneModeCfg[1].lineBits.txRate.bits.dataWidth = DATA_BIT_WIDTH_64;

    /*����ģʽ:LANE_MODE_24P88_NRZ*/
    modePara->laneModeCfg[1].lineBits.rxRate[0].bits.rateMode = LANE_MODE_24P88_NRZ;
    modePara->laneModeCfg[1].lineBits.rxRate[0].bits.dataWidth = DATA_BIT_WIDTH_32;
    modePara->laneModeCfg[1].lineBits.rxRate[1].bits.rateMode = LANE_MODE_INVALID;
    modePara->laneModeCfg[1].lineBits.rxRate[1].bits.dataWidth = DATA_BIT_WIDTH_8;
    modePara->laneModeCfg[1].lineBits.rxRate[2].bits.rateMode = LANE_MODE_INVALID;
    modePara->laneModeCfg[1].lineBits.rxRate[2].bits.dataWidth = DATA_BIT_WIDTH_8;

    // func 0x0001_xxxx cata
    //0x0001_0000
    ret = SRE_CmdSend(API_PARA_INIT_CAT, CHIP_MODE_INIT, inputPara, outputPara, 9);
    if (ret != SRE_SUCCESS) {

        memset(g_dsp_info,0,sizeof(g_dsp_info));
        memcpy(g_dsp_info,"para1:",6);
        set_u32(&g_dsp_info[10],ret);
       return ret;
    }

    val = 0xffffffff;
    RegisterRead(val,mangeTbl->mcuEnable);
    if(val == 0)
    {
         memset(g_dsp_info,0,sizeof(g_dsp_info));
         memcpy(g_dsp_info,"mcu5:",6);
         set_u32(&g_dsp_info[10],val);
         return val;
    }
  #endif
   

  //  system_delay_ms(delay);
  
   memset(inputPara, 0, sizeof(SystemDatapathParaInitS));
   memset(outputPara,0,sizeof(outputPara));

    //�μ���:0x0001_0001,Datapath������ʼ��
    SystemDatapathParaInitS *dataPath = (SystemDatapathParaInitS *)inputPara;
    dataPath->isCfgFlag = 1;//para0
    dataPath->rxCfgMask = 3; //para1
    dataPath->txCfgMask = 0x3; //para2

    /*start ����para3*/
    dataPath->laneDatapathCfg.bits.hostRxDatapathCfg.rxGrayEn = 0;
    dataPath->laneDatapathCfg.bits.hostRxDatapathCfg.rxSwapEn = 0;
    dataPath->laneDatapathCfg.bits.lineRxDatapathCfg.rxGrayEn = 0;
    dataPath->laneDatapathCfg.bits.lineRxDatapathCfg.rxSwapEn = 0;

    /*�¼�LutSel,������*/
    /*
    line tx lut����ѡ��0:ֱͨ�� (û������)
        1:����rate���ã�����API_PARA_INIT_CAT���õ�para3��tx���ʣ�������ѡ��
    */
    dataPath->laneDatapathCfg.bits.lineTxDatapathCfg.txLutSel = 0;

    /*0������ͣ�3��ߡ����ͳ��������*/
    dataPath->laneDatapathCfg.bits.lineTxDatapathCfg.txLutGear = 3;

    /*ͬ��*/
    dataPath->laneDatapathCfg.bits.hostTxDatapathCfg.txLutSel = 0;
    dataPath->laneDatapathCfg.bits.hostTxDatapathCfg.txLutGear = 3;
    /*end ����para3*/

      // func 0x0001_xxxx cata
      //0x0001_0001
    ret = SRE_CmdSend(API_PARA_INIT_CAT, DATAPATH_PARA_INIT, inputPara, outputPara, 9);
    if (ret != SRE_SUCCESS) 
    {
        memset(g_dsp_info,0,sizeof(g_dsp_info));
        memcpy(g_dsp_info,"paraIn:",8);
        set_u32(&g_dsp_info[10],ret);
    }
    
    memset(outputPara,0,sizeof(outputPara));

   /*0x0000_0000
    У׼�����ܿ��أ�ChipRun��������ģ�� ���� У׼���й���
     */
#if 1
    /*�μ���0x0000_0000,���п���*/
    inputPara[0] = 0x1;//01,para0; host_rx enable��line_rx disable
    inputPara[1] = 0x2;//10,para1;host_tx-disable,line_tx-enable;
     // func 0x0000_xxxx cata
     //0x0000_0000
     /*У׼�����ܿ��أ�ChipRun��������ģ�� ���� У׼���й���
     */
    ret = SRE_CmdSend(API_RUN_CTRL_CAT, CHIP_RUN, inputPara, outputPara, 9);
    if (ret != SRE_SUCCESS) 
    {
        memset(g_dsp_info,0,sizeof(g_dsp_info));
        memcpy(g_dsp_info,"run1:",5);
        set_u32(&g_dsp_info[10],ret);
       // return ret;
    }  

    val = 0xffffffff;
    RegisterRead(val,mangeTbl->mcuEnable);
    if(val == 0)
    {
         memset(g_dsp_info,0,sizeof(g_dsp_info));
         memcpy(g_dsp_info,"mcu6:",6);
         set_u32(&g_dsp_info[10],val);
         return val;
    }
#endif
    //system_delay_ms(delay);


   // memcpy(&g_dsp_info[16],""
 //  set_u32(&g_dsp_info[16],ret);   

#if 1
    //���п���,Ŀǰֻ��Ч1����Ч0�������Ὺ�Žӿ�
    //Ҳ����˵������1����޷���ԭΪ0��
    inputPara[0] = 0x2;// bit: 10
    inputPara[1] = 0x1;//bit:01
    ret = SRE_CmdSend(API_RUN_CTRL_CAT, CHIP_RUN, inputPara, outputPara, 9);
    if (ret != SRE_SUCCESS) {
        memset(g_dsp_info,0,sizeof(g_dsp_info));
        memcpy(g_dsp_info,"Up:",5);
        set_u32(&g_dsp_info[10],ret);
    }
#endif    
    return SRE_SUCCESS;
}

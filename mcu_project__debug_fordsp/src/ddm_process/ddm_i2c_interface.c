
#include "ddm_i2c_interface.h"

/*****************************************************************************
 * �� �� ��  : apc_target_voltage_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : apc�Զ�����ʱ��Ŀ��ֵ������ı���
 * �������  : uint8_t *pbuff,
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void apc_target_voltage_reg_write(uint8_t *pbuff,uint32_t bufflen)
{	
	float vol_real = 0.0;
	uint16_t vol_value = 0;
	if(NULL == pbuff || bufflen < 5)
	{
		return;
	}

	if(APC_TARGET_VALUE_EX != pbuff[1] || CMD_COMMAND_MAP_REG != pbuff[0])		
	{
		return;
	}	

	vol_value = get_u16(&pbuff[3]);
	vol_real = vol_value * 0.1;
	//printf("vol_real = %f\n",vol_real);
	
	if(SFF_50G_TYPE == pbuff[2])
	{		
		default_config_value[APC_TARGET_VALUE_50G_CFG_HIGH] = pbuff[3];
		default_config_value[APC_TARGET_VALUE_50G_CFG_LOW] = pbuff[4];		
		ddm_50g_apc_target_voltage(vol_real);
	}
	else if(SFF_10G_TYPE == pbuff[2])
	{		
		default_config_value[APC_TARGET_VALUE_10G_CFG_HIGH] = pbuff[3];
		default_config_value[APC_TARGET_VALUE_10G_CFG_LOW] = pbuff[4];
		ddm_10g_apc_target_voltage(vol_real);		
		
	}
	else if(SFF_1G_TYPE == pbuff[2])
	{		
		default_config_value[APC_TARGET_VALUE_1G_CFG_HIGH] = pbuff[3];
		default_config_value[APC_TARGET_VALUE_1G_CFG_LOW] = pbuff[4];
		ddm_1g_apc_target_voltage(vol_real);
		
		
	}
}


/*****************************************************************************
 * �� �� ��  : apc_auto_enable_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : apcʹ���Զ�����
 * �������  : uint8_t *pbuff,
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void apc_auto_enable_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	if(NULL == pbuff || bufflen < 4)
	{
		return;
	}

	if(APC_AUTO_ENABLE_EX != pbuff[1] || CMD_COMMAND_MAP_REG != pbuff[0])		
	{
		return;
	}

	
	if(SFF_50G_TYPE == pbuff[2])
	{
		default_config_value[APC_ENABLE_50G_CFG] = pbuff[3];			
		ddm_50g_apc_auto_enable(pbuff[3]);
		
	}
	else if(SFF_10G_TYPE == pbuff[2])
	{
		default_config_value[APC_ENABLE_10G_CFG] = pbuff[3];	
		//gn7153_apc_auto_enable_ctrl(pbuff[3]);
		ddm_10g_apc_auto_enable(pbuff[3]);
	}
	else if(SFF_1G_TYPE == pbuff[2])
	{
		default_config_value[APC_ENABLE_1G_CFG] = pbuff[3];	
		//ux3326_apc_auto_enable_ctrl(pbuff[3]);
		ddm_1g_apc_auto_enable(pbuff[3]);
	}

	return;
}



/*****************************************************************************
 * �� �� ��  : apd_i2c_vcc_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : ����VAPD����
 * �������  : uint8_t *pbuff,  ��1���ֽ��ǼĴ���
                                ��2���ֽ�������:50G, 10G,1G
                                ���������ֽ�����ֵ
                                
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c����
 * ��    ��  : ��

*****************************************************************************/
void apd_i2c_vcc_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t *ptr = pbuff + 1;
	uint16_t apd_value;
	apd_value = get_u16((ptr + 1));//��λ���·�����Ϊ ʵ��ֵ*10�����ڱ���
	float apd_vcc = apd_value * 0.1; //APDʵ��ֵ
	
	if((*ptr) == SFF_50G_TYPE){
		if(apd_vcc <= 35){			
			ddm_50g_set_rx_vapd(apd_vcc);
			default_config_value[RX_VAPD_VALUE_0_HIGH] = apd_value >> 8;
			default_config_value[RX_VAPD_VALUE_0_LOW] = apd_value & 0xFF;
		}
		else{
			default_config_value[RX_VAPD_VALUE_0_HIGH] = 0;
			default_config_value[RX_VAPD_VALUE_0_LOW] = 0;
		}
	}
	
	if((*ptr) == SFF_10G_TYPE){
		if(apd_vcc <= 40){
			ddm_10g_set_rx_vapd(apd_vcc);
			default_config_value[RX_VAPD_VALUE_1_HIGH] = apd_value >> 8;
			default_config_value[RX_VAPD_VALUE_1_LOW] = apd_value & 0xFF;
		}
		else{
			default_config_value[RX_VAPD_VALUE_1_HIGH] = 0;
			default_config_value[RX_VAPD_VALUE_1_LOW] = 0;
		}
	}
	
	if((*ptr) == SFF_1G_TYPE){
		if(apd_vcc <= 50){
		
			ddm_1g_set_rx_vapd(apd_vcc);
			default_config_value[RX_VAPD_VALUE_2_HIGH] = apd_value >> 8;
			default_config_value[RX_VAPD_VALUE_2_LOW] = apd_value & 0xFF;
		}
		else{
			default_config_value[RX_VAPD_VALUE_2_HIGH] = 0;
			default_config_value[RX_VAPD_VALUE_2_LOW] = 0;
		}
	}	
}


/*****************************************************************************
 * �� �� ��  : soa_i2c_ild_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : SOA��������
 * �������  : uint8_t *pbuff,  ��1���ֽ��ǼĴ���
                                ��2���ֽ�������:50G, 10G,1G������ֻ��50G
                                ���������ֽ�����ֵ
                                
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c����
 * ��    ��  : ��

*****************************************************************************/
void soa_i2c_ild_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t *ptr = pbuff + 1;
	uint16_t ild_value;
	ild_value = get_u16((ptr + 1));
	float ild = ild_value * 0.1;

	if((*ptr) == SFF_50G_TYPE){
		if(ild <= 100){
			
			ddm_50g_set_soa_ild(ild);
			default_config_value[TX_SOA_VALUE_0_HIGH] = ild_value >> 8;
			default_config_value[TX_SOA_VALUE_0_LOW] = ild_value & 0xFF;
		}
		else{
			default_config_value[TX_SOA_VALUE_0_HIGH] = 0;
			default_config_value[TX_SOA_VALUE_0_LOW] = 0;
		}
		
	}

}
	

/*****************************************************************************
 * �� �� ��  : vea_i2c_vcc_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : EA��ѹ����
 * �������  : uint8_t *pbuff,  ��1���ֽ��ǼĴ���
                                ��2���ֽ�������:50G, 10G,1G������ֻ��50G,10G
                                ���������ֽ�����ֵ
                                
 				uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c����
 * ��    ��  : ��

*****************************************************************************/
void vea_i2c_vcc_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t *ptr = pbuff + 1;
	uint16_t vea_value;
	vea_value = get_u16((ptr + 1));
	float vea_vcc = vea_value * 0.01;
	
	if((*ptr) == SFF_50G_TYPE){
		if(vea_vcc <= 2){			
			default_config_value[TX_VEA_VALUE_0_HIGH] = vea_value >> 8;
			default_config_value[TX_VEA_VALUE_0_LOW] = vea_value & 0xFF;
			ddm_50g_set_ea(vea_vcc);
		}
		else{
			default_config_value[TX_VEA_VALUE_0_HIGH] = 0;
			default_config_value[TX_VEA_VALUE_0_LOW] = 0;
		}
	}
	
	if((*ptr) == SFF_10G_TYPE){
		if(vea_vcc <= 2){
			ddm_10g_set_ea(vea_vcc);
			default_config_value[TX_VEA_VALUE_1_HIGH] = vea_value >> 8;
			default_config_value[TX_VEA_VALUE_1_LOW] = vea_value & 0xFF;
		}
		else{
			default_config_value[TX_VEA_VALUE_1_HIGH] = 0;
			default_config_value[TX_VEA_VALUE_1_LOW] = 0;
		}
	}

}
	

/*****************************************************************************
 * �� �� ��  : ibias_i2c_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : IBIAS��������
 * �������  : uint8_t *pbuff,  ��1���ֽ��ǼĴ���
                                ��2���ֽ�������:50G, 10G,1G��
                                ���������ֽ�����ֵ
                                
 				uint32_t bufflen pbuff����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c����
 * ��    ��  : ��

*****************************************************************************/
void ibias_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t *ptr = pbuff + 1;
	uint16_t ibias_value;
	ibias_value = get_u16((ptr + 1));
	float ibias_mA = ibias_value * 0.1;
	
	if((*ptr) == SFF_50G_TYPE){
		if(ibias_mA <= 120){
		
			uint16_t ibias_adc_set_val = ibias_mA / 0.188;			
			ddm_50g_set_ld_ibias(ibias_adc_set_val);
			default_config_value[TX_IBIAS_VALUE_0_HIGH] = ibias_value >> 8;
			default_config_value[TX_IBIAS_VALUE_0_LOW] = ibias_value & 0xFF;
		}
		else{
			default_config_value[TX_IBIAS_VALUE_0_HIGH] = 0;
			default_config_value[TX_IBIAS_VALUE_0_LOW] = 0;
		}
	}
	
	if((*ptr) == SFF_10G_TYPE){
		if(ibias_mA <= 120){
			uint16_t ibias_adc_set_val = ibias_mA / 0.154;
			ddm_10g_set_ld_ibias(ibias_adc_set_val);
			default_config_value[TX_IBIAS_VALUE_1_HIGH] = ibias_value >> 8;
			default_config_value[TX_IBIAS_VALUE_1_LOW] = ibias_value & 0xFF;
		}
		else{
			default_config_value[TX_IBIAS_VALUE_1_HIGH] = 0;
			default_config_value[TX_IBIAS_VALUE_1_LOW] = 0;
		}
	}
	
	if((*ptr) == SFF_1G_TYPE){
		if(ibias_mA <= 100){
			uint16_t ibias_adc_set_val = ibias_mA / 0.124;
			ddm_1g_set_ld_ibias(ibias_adc_set_val);
			default_config_value[TX_IBIAS_VALUE_2_HIGH] = ibias_value >> 8;
			default_config_value[TX_IBIAS_VALUE_2_LOW] = ibias_value & 0xFF;
		}
		else{
			default_config_value[TX_IBIAS_VALUE_2_HIGH] = 0;
			default_config_value[TX_IBIAS_VALUE_2_LOW] = 0;
		}
	}

}
	
	
/*****************************************************************************
 * �� �� ��  : imod_i2c_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : IMOD���Ƶ�������
 * �������  : uint8_t *pbuff,  ��1���ֽ��ǼĴ���
                                ��2���ֽ�������:50G, 10G,1G��
                                ���������ֽ�����ֵ
                                
 				uint32_t bufflen pbuff����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c����
 * ��    ��  : ��

*****************************************************************************/
void imod_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t *ptr = pbuff + 1;
	uint16_t imod_value;
	imod_value = get_u16((ptr + 1));
	uint16_t imod_mV = imod_value * 0.1;
	
	if((*ptr) == SFF_50G_TYPE){
		if(imod_mV <= 700){
			ddm_50g_set_ld_imod(imod_mV);			
			default_config_value[TX_IMOD_VALUE_0_HIGH] = imod_value >> 8;
			default_config_value[TX_IMOD_VALUE_0_LOW] = imod_value & 0xFF;
		}
		else{
			default_config_value[TX_IMOD_VALUE_0_HIGH] = 0;
			default_config_value[TX_IMOD_VALUE_0_LOW] = 0;
		}
		
	}

		
	if((*ptr) == SFF_10G_TYPE){
		if(imod_mV <= 2500){
			
			ddm_10g_set_ld_imod(imod_mV);
			default_config_value[TX_IMOD_VALUE_1_HIGH] = imod_value >> 8;
			default_config_value[TX_IMOD_VALUE_1_LOW] = imod_value & 0xFF;
		}
		else{
			default_config_value[TX_IMOD_VALUE_1_HIGH] = 0;
			default_config_value[TX_IMOD_VALUE_1_LOW] = 0;
		}
	}
	
	if((*ptr) == SFF_1G_TYPE){
		if(imod_mV <= 100){
			//ux3326_set_ld_imod(imod_mV);
			ddm_1g_set_ld_imod(imod_mV);
			default_config_value[TX_IMOD_VALUE_2_HIGH] = imod_value >> 8;
			default_config_value[TX_IMOD_VALUE_2_LOW] = imod_value & 0xFF;
		}
		else{
			default_config_value[TX_IMOD_VALUE_2_HIGH] = 0;
			default_config_value[TX_IMOD_VALUE_2_LOW] = 0;
		}
	}


}
	

/*****************************************************************************
 * �� �� ��  : swing_i2c_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : *RX_SWING�ն˰ڷ�����
 * �������  : uint8_t *pbuff,  ��1���ֽ��ǼĴ���
                                ��2���ֽ�������:50G, 10G,1G��
                                ���������ֽ�����ֵ
                                
 				uint32_t bufflen pbuff����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c����
 * ��    ��  : ��

*****************************************************************************/
void swing_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t *ptr = pbuff + 1;
	uint16_t swing_value;//��ѹ���ñ���0-100
	swing_value = get_u16((ptr + 1));
	uint16_t swing_real = swing_value * 0.1;
	
	if((*ptr) == SFF_50G_TYPE){
		if(swing_real <= 180){
		
			default_config_value[RX_SWING_VALUE_0_HIGH] = swing_value >> 8;
			default_config_value[RX_SWING_VALUE_0_LOW] = swing_value & 0xFF;
			ddm_50g_set_rx_swing(swing_real);
		}
		else{
			default_config_value[RX_SWING_VALUE_0_HIGH] = 0;
			default_config_value[RX_SWING_VALUE_0_LOW] = 0;
		}
	}

	if((*ptr) == SFF_10G_TYPE){
		if(swing_real <= 15){
			ddm_10g_set_rx_swing(swing_real);
			default_config_value[RX_SWING_VALUE_1_HIGH] = swing_value >> 8;
			default_config_value[RX_SWING_VALUE_1_LOW] = swing_value & 0xFF;
		}
		else{
			default_config_value[RX_SWING_VALUE_1_HIGH] = 0;
			default_config_value[RX_SWING_VALUE_1_LOW] = 0;
		}
	}
	
	if((*ptr) == SFF_1G_TYPE){
		if(swing_real <= 171){// 12-171: 900-1670mV
			ddm_1g_set_rx_swing(swing_real);
			default_config_value[RX_SWING_VALUE_2_HIGH] = swing_value >> 8;
			default_config_value[RX_SWING_VALUE_2_LOW] = swing_value & 0xFF;
		}
		else{
			default_config_value[RX_SWING_VALUE_2_HIGH] = 0;
			default_config_value[RX_SWING_VALUE_2_LOW] = 0;
		}
	}

	
}
	
/*****************************************************************************
 * �� �� ��  : rx_eq_i2c_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : RX_EQ�ն˾�������
 * �������  : uint8_t *pbuff,  ��1���ֽ��ǼĴ���
                                ��2���ֽ�������:50G, 10G,1G��
                                ���������ֽ�����ֵ
                                
 				uint32_t bufflen pbuff����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c����
 * ��    ��  : ��

*****************************************************************************/
void rx_eq_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen)
{	
	uint8_t *ptr = pbuff + 1;
	uint16_t eq_value;//��ѹ���ñ���0-100
	eq_value = get_u16((ptr + 1));
	uint16_t eq_real = eq_value * 0.1;
	
	if((*ptr) == SFF_50G_TYPE){
		if(eq_real <= 127){
			
			default_config_value[RX_EQ_VALUE_0_HIGH] = eq_value >> 8;
			default_config_value[RX_EQ_VALUE_0_LOW] = eq_value & 0xFF;
			ddm_50g_set_rx_eq_boost(eq_real);
		}
		else{
			default_config_value[RX_EQ_VALUE_0_HIGH] = 0;
			default_config_value[RX_EQ_VALUE_0_LOW] = 0;
		}
	}

	if((*ptr) == SFF_10G_TYPE){
		if(eq_real <= 31){
			ddm_10g_set_rx_eq_boost(eq_real);
			default_config_value[RX_EQ_VALUE_1_HIGH] = eq_value >> 8;
			default_config_value[RX_EQ_VALUE_1_LOW] = eq_value & 0xFF;
		}
		else{
			default_config_value[RX_EQ_VALUE_1_HIGH] = 0;
			default_config_value[RX_EQ_VALUE_1_LOW] = 0;
		}
	}

	
}
	

 /*****************************************************************************
 * �� �� ��  : cpa_i2c_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : TxCross���������
 * �������  : uint8_t *pbuff,  ��1���ֽ��ǼĴ���
                                ��2���ֽ�������:50G, 10G,1G��
                                ���������ֽ�����ֵ
                                
 				uint32_t bufflen pbuff����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c����
 * ��    ��  : ��

*****************************************************************************/
void cpa_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t *ptr = pbuff + 1;
	uint16_t cpa_value;//���ñ���0-100
	cpa_value = get_u16((ptr + 1));
	uint8_t cpa_real = cpa_value * 0.1;
	
	if((*ptr) == SFF_50G_TYPE){
		if(cpa_real <= 31){
			
			default_config_value[TX_CPA_VALUE_0_HIGH] = cpa_value >> 8;
			default_config_value[TX_CPA_VALUE_0_LOW] = cpa_value & 0xFF;
			ddm_50g_set_tx_ld_cpa(cpa_real);
		}
		else{
			default_config_value[TX_CPA_VALUE_0_HIGH] = 0;
			default_config_value[TX_CPA_VALUE_0_LOW] = 0;
		}
	}


	if((*ptr) == SFF_10G_TYPE){
		if(cpa_real <= 63){
			ddm_10g_set_tx_ld_cpa(cpa_real);
			default_config_value[TX_CPA_VALUE_1_HIGH] = cpa_value >> 8;
			default_config_value[TX_CPA_VALUE_1_LOW] = cpa_value & 0xFF;
		}
		else{
			default_config_value[TX_CPA_VALUE_1_HIGH] = 0;
			default_config_value[TX_CPA_VALUE_1_LOW] = 0;
		}
	}
	
	if((*ptr) == SFF_1G_TYPE){
		if(cpa_real <= 63){
			ddm_1g_set_tx_ld_cpa(cpa_real);
			default_config_value[TX_CPA_VALUE_2_HIGH] = cpa_value >> 8;
			default_config_value[TX_CPA_VALUE_2_LOW] = cpa_value & 0xFF;
		}
		else{
			default_config_value[TX_CPA_VALUE_2_HIGH] = 0;
			default_config_value[TX_CPA_VALUE_2_LOW] = 0;
		}
	}

}
	

/*****************************************************************************
 * �� �� ��  : tx_deemph_i2c_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : Tx_DeEmph����ȥԤ��������
 * �������  : uint8_t *pbuff,  ��1���ֽ��ǼĴ���
                                ��2���ֽ�������:50G, 10G��
                                ���������ֽ�����ֵ
                                
 				uint32_t bufflen pbuff����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c����
 * ��    ��  : ��

*****************************************************************************/
void tx_deemph_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t *ptr = pbuff + 1;
	uint16_t tx_deemph_value;//���ñ���0-100
	tx_deemph_value = get_u16((ptr + 1));
	uint16_t tx_deemph_real = tx_deemph_value * 0.1;
	
	if((*ptr) == SFF_50G_TYPE){
		if(tx_deemph_real <= 1023){			
			default_config_value[TX_DEEMPH_VALUE_0_HIGH] = tx_deemph_value >> 8;
			default_config_value[TX_DEEMPH_VALUE_0_LOW] = tx_deemph_value & 0xFF;
			ddm_50g_set_tx_ld_deempth(tx_deemph_real);
		}
		else{
			default_config_value[TX_DEEMPH_VALUE_0_HIGH] = 0;
			default_config_value[TX_DEEMPH_VALUE_0_LOW] = 0;
		}
	}


	if((*ptr) == SFF_10G_TYPE){
		if(tx_deemph_real <= 31){
			ddm_10g_set_tx_ld_deempth(tx_deemph_real);
			default_config_value[TX_DEEMPH_VALUE_1_HIGH] = tx_deemph_value >> 8;
			default_config_value[TX_DEEMPH_VALUE_1_LOW] = tx_deemph_value & 0xFF;
		}
		else{
			default_config_value[TX_DEEMPH_VALUE_1_HIGH] = 0;
			default_config_value[TX_DEEMPH_VALUE_1_LOW] = 0;
		}
	}

	
}
	
	/*Rx_DeEmph�ն�ȥԤ��������*/
/*****************************************************************************
 * �� �� ��  : rx_deemph_i2c_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : Rx_DeEmph�ն�ȥԤ��������
 * �������  : uint8_t *pbuff,  ��1���ֽ��ǼĴ���
                                ��2���ֽ�������:50G, 10G��
                                ���������ֽ�����ֵ
                                
 				uint32_t bufflen pbuff����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c����
 * ��    ��  : ��

*****************************************************************************/
void rx_deemph_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t *ptr = pbuff + 1;
	uint16_t rx_deemph_value;//���ñ���0-100
	rx_deemph_value = get_u16((ptr + 1));
	uint8_t rx_deemph_real = rx_deemph_value * 0.1;
	
	if((*ptr) == SFF_50G_TYPE){
		if(rx_deemph_real <= 15){
			default_config_value[RX_DEEMPH_VALUE_0_HIGH] = rx_deemph_value >> 8;
			default_config_value[RX_DEEMPH_VALUE_0_LOW] = rx_deemph_value & 0xFF;
			ddm_50g_set_rx_drv_deemph(rx_deemph_real);
		}
		else{
			default_config_value[RX_DEEMPH_VALUE_0_HIGH] = 0;
			default_config_value[RX_DEEMPH_VALUE_0_LOW] = 0;
		}
	}

	if((*ptr) == SFF_10G_TYPE){
		if(rx_deemph_real <= 15){
			ddm_10g_set_rx_drv_deemph(rx_deemph_real);
			default_config_value[RX_DEEMPH_VALUE_1_HIGH] = rx_deemph_value >> 8;
			default_config_value[RX_DEEMPH_VALUE_1_LOW] = rx_deemph_value & 0xFF;
		}
		else{
			default_config_value[RX_DEEMPH_VALUE_1_HIGH] = 0;
			default_config_value[RX_DEEMPH_VALUE_1_LOW] = 0;
		}
	}

}
	
	/*SDA���� RX Loss Hyst*/
/*****************************************************************************
 * �� �� ��  : rx_los_threshold_i2c_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : SDA���� RX Loss Hyst
 * �������  : uint8_t *pbuff,  ��1���ֽ��ǼĴ���
                                ��2���ֽ�������:50G, 10G��
                                ���������ֽ�����ֵ
                                
 				uint32_t bufflen pbuff����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : i2c����
 * ��    ��  : ��

*****************************************************************************/
void rx_los_threshold_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t *ptr = pbuff + 1;
	uint16_t rx_los_threshold_value;//���ñ���0-100
	rx_los_threshold_value = get_u16((ptr + 1));
	uint8_t rx_los_threshold_real = rx_los_threshold_value * 0.1;
	
	if((*ptr) == SFF_50G_TYPE){
		if(rx_los_threshold_real <= 63){			
			ddm_50g_set_rx_los_threshold(rx_los_threshold_real);

			default_config_value[RX_LOS_THRESHOLD_VALUE_0_HIGH] = 
rx_los_threshold_value >> 8;
			default_config_value[RX_LOS_THRESHOLD_VALUE_0_LOW] = 
rx_los_threshold_value & 0xFF;

		}
		else{
			default_config_value[RX_LOS_THRESHOLD_VALUE_0_HIGH] = 0;
			default_config_value[RX_LOS_THRESHOLD_VALUE_0_LOW] = 0;
		}
	}


	if((*ptr) == SFF_10G_TYPE){
		if(rx_los_threshold_real <= 63){
						ddm_10g_set_rx_los_threshold(rx_los_threshold_real);

			default_config_value[RX_LOS_THRESHOLD_VALUE_1_HIGH] = 
rx_los_threshold_value >> 8;
			default_config_value[RX_LOS_THRESHOLD_VALUE_1_LOW] = 
rx_los_threshold_value & 0xFF;
		}
		else{
			default_config_value[RX_LOS_THRESHOLD_VALUE_1_HIGH] = 0;
			default_config_value[RX_LOS_THRESHOLD_VALUE_1_LOW] = 0;
		}
	}
	
	if((*ptr) == SFF_1G_TYPE){
		if(rx_los_threshold_real <= 255){
						ddm_1g_set_rx_los_threshold(rx_los_threshold_real);

			default_config_value[RX_LOS_THRESHOLD_VALUE_2_HIGH] = 
rx_los_threshold_value >> 8;
			default_config_value[RX_LOS_THRESHOLD_VALUE_2_LOW] = 
rx_los_threshold_value & 0xFF;
		}
		else{
			default_config_value[RX_LOS_THRESHOLD_VALUE_2_HIGH] = 0;
			default_config_value[RX_LOS_THRESHOLD_VALUE_2_LOW] = 0;
		}
	}

	
}
	
	/**/
/***********************************************************************
	** �� �� ���� rx_los_hyst_i2c_reg_write
	** ��    �룺 uint8_t *pbuff �Ĵ�������
								uint32_t bufflen �ֽڳ���
	** ��    ���� ��
	** �� �� ֵ�� ��
	** ���������� �����ն��źŶ�ʧ����ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void rx_los_hyst_i2c_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t *ptr = pbuff + 1;
	uint16_t rx_los_hyst_value;//���ñ���0-100
	rx_los_hyst_value = get_u16((ptr + 1));
	uint8_t rx_los_hyst_real = rx_los_hyst_value * 0.1;
	
	if((*ptr) == SFF_50G_TYPE){
		if(rx_los_hyst_real <= 31){
			default_config_value[RX_LOS_HYST_VALUE_0_HIGH] = rx_los_hyst_value >> 8;
			default_config_value[RX_LOS_HYST_VALUE_0_LOW] = rx_los_hyst_value & 0xFF;
			ddm_50g_set_rx_los_hyst(rx_los_hyst_real);
		}
		else{
			default_config_value[RX_LOS_HYST_VALUE_0_HIGH] = 0;
			default_config_value[RX_LOS_HYST_VALUE_0_LOW] = 0;
		}
	}

	if((*ptr) == SFF_10G_TYPE){
		if(rx_los_hyst_real <= 31){
			ddm_10g_set_rx_los_hyst(rx_los_hyst_real);
			default_config_value[RX_LOS_HYST_VALUE_1_HIGH] = rx_los_hyst_value >> 8;
			default_config_value[RX_LOS_HYST_VALUE_1_LOW] = rx_los_hyst_value & 0xFF;
		}
		else{
			default_config_value[RX_LOS_HYST_VALUE_1_HIGH] = 0;
			default_config_value[RX_LOS_HYST_VALUE_1_LOW] = 0;
		}
	}
	
	if((*ptr) == SFF_1G_TYPE){
		if(rx_los_hyst_real <= 3){
			ddm_1g_set_rx_los_hyst(rx_los_hyst_real);
			default_config_value[RX_LOS_HYST_VALUE_2_HIGH] = rx_los_hyst_value >> 8;
			default_config_value[RX_LOS_HYST_VALUE_2_LOW] = rx_los_hyst_value & 0xFF;
		}
		else{
			default_config_value[RX_LOS_HYST_VALUE_2_HIGH] = 0;
			default_config_value[RX_LOS_HYST_VALUE_2_LOW] = 0;
		}
	}

	
}



/*****************************************************************************
 * �� �� ��  : cmd_command_map_reg_write
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : ͨ�������д����
 * �������  : uint8_t *pbuff, ��������
 			uint32_t bufflen   ����
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : 
 * ��    ��  : CMD_COMMAND_MAP_REG = 0x1c

*****************************************************************************/
void cmd_command_map_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint32_t type = 0;	
	if(NULL == pbuff || bufflen < 2)
	{
		return;
	}

	type = pbuff[1];
	switch(type)
	{
		case CFG_SAVE_FLASH_EX:
		{
			om_save_data_config_flash_write(pbuff,bufflen);
			break;
		}
		case CFG_CLEAR_FLASH_EX:
		{
			om_erase_data_config_flash_write(pbuff,bufflen);
			break;
		}
		case APC_AUTO_ENABLE_EX:
		{
			apc_auto_enable_reg_write(pbuff,bufflen);
			break;
		}
		case APC_IPHOTO_RATE_EX:
		{
			break;
		}
		case APC_TARGET_VALUE_EX:
		{
			apc_target_voltage_reg_write(pbuff,bufflen);
			break;
		}
		case CALIBRATION_TX_I_50G_CONFIG:
		{
			calibration_tx_i_50g_reg_write(pbuff,bufflen);
			break;
		}
		case CALIBRATION_TX_PWR_50G_CONFIG:
		{
			calibration_tx_pwr_50g_reg_write(pbuff,bufflen);
			break;
		}
		case CALIBRATION_RX_PWR_50G_CONFIG:
		{
			calibration_rx_pwr_50g_reg_write(pbuff,bufflen);
			break;
		}
		case CALIBRATION_TX_I_10G_CONFIG:
		{
			calibration_tx_i_10g_reg_write(pbuff,bufflen);
			break;
		}
		case CALIBRATION_TX_PWR_10G_CONFIG:
		{
			calibration_tx_pwr_10g_reg_write(pbuff,bufflen);
			break;
		}
		case CALIBRATION_RX_PWR_10G_CONFIG:
		{
			calibration_rx_pwr_10g_reg_write(pbuff,bufflen);
			break;
		}
		case CALIBRATION_TX_I_1G_CONFIG:
		{
			calibration_tx_i_1g_reg_write(pbuff,bufflen);
			break;
		}
		case CALIBRATION_TX_PWR_1G_CONFIG:
		{
			calibration_tx_pwr_1g_reg_write(pbuff,bufflen);
			break;
		}
		case CALIBRATION_RX_PWR_1G_CONFIG:
		{
			calibration_rx_pwr_1g_reg_write(pbuff,bufflen);
			break;
		}
		default:
		{
			break;
		}
			
	}


return;
	
}

/*****************************************************************************
 * �� �� ��  : ddm_i2c_switch_auto_process_reg_write
 * �� �� ��  : fz
 * ��������  : 2023��5��23��
 * ��������  : ����DDM�Զ�ˢ�¹���
 * �������  : uint8_t *pbuff,
 				      uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : CMD_DDM_SWITCH_ATUO_PROCESS_REG = 0x12,
	

*****************************************************************************/
void ddm_i2c_switch_auto_process_reg_write(uint8_t *pbuff,uint32_t bufflen)
{
	uint8_t reg = 0;

	/*�������*/
	if(NULL == pbuff || bufflen < 3)
	{
		return;
	}

	reg |= pbuff[0];

	if(reg != CMD_DDM_SWITCH_ATUO_PROCESS_REG)
	{
		return;
	}

	switch(pbuff[1])
	{
		case SFF_50G_TYPE:
		{
			g_mcu_vars_param.g_50g_ddm_sw_auto_process_flag = pbuff[2];
			break;
		}
		case SFF_10G_TYPE:
		{
			g_mcu_vars_param.g_10g_ddm_sw_auto_process_flag = pbuff[2];
			break;
		}
		case SFF_1G_TYPE:
		{
			g_mcu_vars_param.g_1g_ddm_sw_auto_process_flag = pbuff[2];
			break;
		}
		default:
		{
			break;
		}
	}
	
#if (MCU_DEBUG_FUNS_CFG == MCU_CFG_YES)	
	{
		printf("DDM(50G,10G,1G) = %u\r\n",g_50g_ddm_sw_auto_process_flag,
						g_10g_ddm_sw_auto_process_flag,
						g_1g_ddm_sw_auto_process_flag);
	}
#endif
	
}


/*****************************************************************************
 * �� �� ��  : import_binary_file_data_to_mcu_flash
 * �� �� ��  : sjtu
 * ��������  : 2025��2��10��
 * ��������  : ����������ļ������ݵ�flash
 * �������  : uint8_t *pbuff,
 				      uint32_t bufflen
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ڲ�����
 * ��    ��  : CMD_OPTICAL_MODULE_CFG_FLASH = 0x28,
	
*****************************************************************************/

// ���ڽ�����λ���·������ݣ������浽 Flash �ĺ���
void import_binary_file_data_to_mcu_flash(uint8_t *p_buff, uint32_t buff_len) {
    uint32_t write_len;
    ErrStatus ret;

    if (p_buff == NULL || buff_len < 2) {
        return;
    }

    if (p_buff[0] != CMD_OPTICAL_MODULE_CFG_FLASH) {
        return;
    }

    switch (p_buff[1]) {
        case BINARY_DATA_TO_FLASH_START:  // ��ʼ��־

			/* add by fz, 20250303, ԭ��:���������������Ϊset,ֹͣddm��ѯ */
			g_mcu_vars_param.g_update_process_flag = SET; 
            ret = upate_mem_is_alloc();
            if (ret == ERROR) {
                ret = update_mem_malloc();
                if (ret == ERROR) {
                    // �����ڴ����ʧ��
                    return;
                }
            }
            update_mem_all_memset();
            g_pkt_rx = 0;
            g_pkt_count_to_flash = 0;
            g_page_idx = 0;
            break;
        case BINARY_DATA_TO_FLASH_DOING:  // �����б�־
            write_len = buff_len - 2;
            g_pkt_rx += write_len;

            ret = upate_mem_is_alloc();
            if (ret == ERROR) {
                return;
            }

            if ((g_update_mem_idx + write_len) > FLASH_PAGE_SIZE) {
                comm_update_write_to_flash(CONFIGADDRESS);
                g_update_mem_idx = 0;
            }

            memcpy(g_update_mem_ptr + g_update_mem_idx, p_buff + 2, write_len);
            g_update_mem_idx += write_len;
            break;
        case BINARY_DATA_TO_FLASH_END:  // ������־
            comm_update_write_to_flash(CONFIGADDRESS);
            break;
        default:
            break;
    }
}


/*****************************************************************************
 * �� �� ��  : ddm_i2c_50g_monitor_reg_read
 * �� �� ��  : fz
 * ��������  : 2025��3��11��
 * ��������  : �ض�50g �ļ��ֵ
 * �������  : uint8_t regaddr  CMD_DDM_50G_MONITOR_REG
 				uint32_t bufflen pbuff�ĳ���
 * �������  : uint8_t *pbuff �ض���ֵ
 * �� �� ֵ  : ��
 * ���ù�ϵ  : ��λ�����ã����ڵ���
 * ��    ��  : 

*****************************************************************************/

void ddm_i2c_50g_monitor_reg_read(uint8_t regaddr,uint8_t *pbuff,uint32_t bufflen)
{
	uint16_t adc_value = 0;
	float voltage = 0.0;
	if(regaddr != CMD_DDM_50G_MONITOR_REG)
	{
		return;
	}

	adc_value = ddm_50g_get_monitor_adc();
	
	voltage = MCU_REF_VOLTAGE / MCU_12BIT_RANGE * adc_value;
	//printf("adc(%u,voltage(%.2f))\r\n",adc_value,voltage);

	set_u16(pbuff, adc_value);
	
	return;
}

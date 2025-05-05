/***********************************************************************
	* �� �� ���� ux3326.c
	* �� �� �ˣ� gqhuan
	* �������ڣ� 2024-06
	* �ļ������� UX3326 1G BOSA Driver���ܺ���
	* ��Ȩ˵���� Copyright (c) 1999-2024    ���ͨ�ſƼ��ɷ����޹�˾
	* ��    ���� 
	* �޸���־�� 
************************************************************************/

#include "ux3326.h"
#include "mcu_pin_type.h"
#include "mcu_data_type.h"
#include "i2c_comm.h"
#include "sff_8472.h"

#if defined(FH_IC_UX3326_HARDWARE) && (FH_IC_UX3326_HARDWARE == CFG_YES)

//extern volatile DDM_ADC_OUT_VAL ddm_adc_out_val;//�ⲿddm��ر���ADCֵ
//extern volatile OM_DEFAULT_CONFIG om_default_config; //�ⲿ��ģ��Ĭ�ϲ���

/* driver config reg */
volatile uint8_t t0[UX3326_CONFIG_REG_LEN] =
{
		0x02,	/*	0	0x00 */
		0x1E,	/*	1	0x01 *//*���Ͷ˼��Է�ת*/
		0x4D,	/*	2	0x02 *//*bit1 CL_OLN 0x4FΪ�ջ�ģʽ bit3-4 MPD��λ*/
		0xC8,	/*	3	0x03 */
		0x00,	/*	4	0x04 */
		0x00,	/*	5	0x05 */
		0x00,	/*	6	0x06 */
		0x00,	/*	7	0x07 */
		0x0C,	/*	8	0x08 */
		0x02,	/*	9	0x09 */
		0x10,	/*	10	0x0A */
		0x00,	/*	11	0x0B */
		0x20,	/*	12	0x0C */
		0x1F,	/*	13	0x0D */
		0x00,	/*	14	0x0E */
		0x00,	/*	15	0x0F */
		0x00,	/*	16	0x10 */
		0x00,	/*	17	0x11 */
		0x41,	/*	18	0x12 *//*	RX ���Է�ת */
		0xAB,	/*	19	0x13 */
		0xF2,	/*	20	0x14 */ 
		0x88,	/*	21	0x15 */ 
		0x40,	/*	22	0x16 */ 
		0xAC,	/*	23	0x17 */ 
		0x00,	/*	24	0x18 */ 
		0xF8,	/*	25	0x19 */ 
		0x84,	/*	26	0x1A */ 
		0x80,	/*	27	0x1B */ 
		0x20,	/*	28	0x1C */ 
		0x00,	/*	29	0x1D */
		0x00,	/*	30	0x1E */
		0x00,	/*	31	0x1F */
		0x00,	/*	32	0x20 */
		0x00,	/*	33	0x21 */
		0x36,	/*	34	0x22 */
		0x0F,	/*	35	0x23 */ 
		0x00,	/*	36	0x24 */
		0x00,	/*	37	0x25 */
		0x00,	/*	38	0x26 */
		0x55	/*	39	0x27 */
};

/***********************************************************************
	** �� �� ���� ux3326_init
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� ux3326��ʼ��
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_init()
{
		/* GPIO��ʼ�� */
		ux3326_gpio_init();
  
		/* оƬreset */
		ux3326_reset();
	
		/* ��ʼ���Ĵ������� */
		ux3326_normal_setting();

		/* ʹ��ADC���� */
//		ux3326_adc();
 
}

/***********************************************************************
	** �� �� ���� ux3326_gpio_init
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� ux3326���ų�ʼ��
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_gpio_init()
{
	/* configure GPIO PA2 as RESET */ 
	gpio_mode_set(GPIO_1G_RESET_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_10G_RST_PIN);    
	gpio_output_options_set(GPIO_1G_RESET_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_10G_RST_PIN);
	
	/* configure GPIO PC12 as TX_FAULT */ 
	gpio_mode_set(GPIO_1G_TX_FAULT_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_1G_TX_FAULT_PIN);    
	gpio_output_options_set(GPIO_1G_TX_FAULT_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_1G_TX_FAULT_PIN);
	
	/* configure GPIO PC13 as SD */ 
	gpio_mode_set(GPIO_1G_SD_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_1G_SD_PIN);    
	gpio_output_options_set(GPIO_1G_SD_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_1G_SD_PIN);
	
}

/***********************************************************************
	** �� �� ���� ux3326_reset
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� ux3326��λ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_reset()
{
	/* RST�ߵ�ƽ */
	gpio_bit_reset(GPIO_1G_RESET_PORT, GPIO_1G_RRESET_PIN);
	system_delay_ms(10);
	gpio_bit_set(GPIO_1G_RESET_PORT, GPIO_1G_RRESET_PIN);
    
}

/***********************************************************************
	** �� �� ���� ux3326_soft_txdsbl_ctrl
	** ��    �룺 uint8_t ctrl_switch 0-enable 1-disable
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� UX3326 ���ʹ��/ȥʹ��TXDSBL
					bit3: 1-Disable, 0-Enable��ʵ�ʲ�����datasheet�����෴
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_soft_txdsbl_ctrl(uint8_t ctrl_switch)
{
	if(ctrl_switch == 1){
		uint8_t tx_ld_soft_txdsbl_reg[2];
		tx_ld_soft_txdsbl_reg[0] = 0x00;//0x00-TX_CTRL1
		tx_ld_soft_txdsbl_reg[1] = 0x0A;//disable
		master_reg_byte_write(UX3326_SLAVE_ADDRESS, tx_ld_soft_txdsbl_reg, 2);
	}
	else{
		uint8_t tx_ld_soft_txdsbl_reg[2];
		tx_ld_soft_txdsbl_reg[0] = 0x00;//0x00-TX_CTRL1
		tx_ld_soft_txdsbl_reg[1] = 0x02;//enable
		master_reg_byte_write(UX3326_SLAVE_ADDRESS, tx_ld_soft_txdsbl_reg, 2);
	}
	
}

/***********************************************************************
	** �� �� ���� ux3326_normal_setting
	** ��    �룺 ��
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� ux3326��ʼ������
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_normal_setting()
{
	uint16_t i;
	uint8_t reg_val[2];
	
	/* д��Ĵ���������Ϣ */
	for(i=0;i<UX3326_CONFIG_REG_LEN;i++)
	{
		reg_val[0] = i;
		reg_val[1] = t0[i];
		master_reg_byte_write(UX3326_SLAVE_ADDRESS, reg_val, 2);
	}
	
}

/***********************************************************************
	** �� �� ���� ux3326_source_sink_select
	** ��    �룺 uint8_t ctrl_switch 1-enable source 0-enable sink
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� ux3326ѡ��Դ�޶�
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_source_sink_select(uint8_t ctrl_switch)
{	
		uint8_t value[2];
		value[0] = 0x61;//0x61-TXSDO_REG26
    if(ctrl_switch == 1){
			value[1] = 0x09;
		}
		else{
			value[1] = 0x11;
		}
		master_reg_byte_write(UX3326_SLAVE_ADDRESS,value, 2);
}

/***********************************************************************
	** �� �� ���� ux3326_get_temperature
	** ��    �룺 float* temperature
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� ux3326��ȡ�¶�ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_get_temperature(float* temperature)
{
	uint8_t temp_data_lo[1];
	uint8_t temp_data_hi[1];
	float slope = 1.92;
	float offset = 0.0;
	uint16_t temp_data = 0;
	
	master_reg_1byte_size_read(UX3326_SLAVE_ADDRESS, 0x2E, temp_data_hi, 1);
	master_reg_1byte_size_read(UX3326_SLAVE_ADDRESS, 0x2F, temp_data_lo, 1);
	
	temp_data = temp_data_hi[0] * 256 + temp_data_lo[0];
	*temperature = (slope * temp_data + offset) / 256;

}

/***********************************************************************
	** �� �� ���� ux3326_get_voltage
	** ��    �룺 float* voltage
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� ux3326��ȡ��ѹֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_get_voltage(float* vcc)
{
	uint8_t vcc_data_lo[1];
	uint8_t vcc_data_hi[1];
	float slope = 0.924;
	float offset = 120;
	uint16_t vcc_data = 0;
	
	master_reg_1byte_size_read(UX3326_SLAVE_ADDRESS, 0x30, vcc_data_hi, 1);
	master_reg_1byte_size_read(UX3326_SLAVE_ADDRESS, 0x31, vcc_data_lo, 1);
	
	vcc_data = vcc_data_hi[0] * 256 + vcc_data_lo[0];
	*vcc = (slope * vcc_data + offset) * 0.0001;
	ddm_adc_out_val.voltage_adc_out_2 = vcc_data;
}

/***********************************************************************
	** �� �� ���� ux3326_get_ld_ibias
	** ��    �룺 float* vcc
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� ux3326��ȡ��������������ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_get_ld_ibias(float* ibias)
{
	uint8_t ibias_data_lo[1];
	uint8_t ibias_data_hi[1];
	//float slope = 0.8646;
	//float offset = 0.0;
	uint16_t ibias_data = 0;
	uint16_t adc_out = 0;
	
	master_reg_1byte_size_read(UX3326_SLAVE_ADDRESS, 0x32, ibias_data_hi, 1);
	master_reg_1byte_size_read(UX3326_SLAVE_ADDRESS, 0x33, ibias_data_lo, 1);
	
	adc_out = ibias_data_hi[0] * 256 + ibias_data_lo[0];
	
	
	*ibias = (om_default_config.tx_i_slope_2 * adc_out + om_default_config.tx_i_offset_2) * 0.002;
	ddm_adc_out_val.ibias_adc_out_2 = adc_out;

}

/***********************************************************************
	** �� �� ���� ux3326_set_ld_ibias
	** ��    �룺 uint16_t ibias
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� UX3326���ü�������������ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_set_ld_ibias(uint16_t ibias){
	uint8_t ibias_set_val[2];
	//set_u16(ibias_set_val, ibias);
	ibias_set_val[0] = ibias & 3;
	ibias_set_val[1] = ibias >> 2;
	
	/* �ֶ�д��LDƫ�õ��� */
	uint8_t lower_value[2];
	uint8_t upper_value[2];
	upper_value[0] = 0x04;//0x04-BIAS HI
	lower_value[0] = 0x05;//0x05-BIAS LO
	upper_value[1] = ibias_set_val[1];//bit[7:0]=7F 9F
	master_reg_byte_write(UX3326_SLAVE_ADDRESS, upper_value, 2);
	lower_value[1] = ibias_set_val[0];//bit[1:0]=0 04
	master_reg_byte_write(UX3326_SLAVE_ADDRESS, lower_value, 2);
	
}
/***********************************************************************
	** �� �� ���� ux3326_set_ld_imod
	** ��    �룺 uint16_t imod ���Ƶ���
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� UX3326����LD���Ƶ���ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_set_ld_imod(uint16_t imod)
{
	uint8_t txsdo_imod_lo[2];
	uint8_t txsdo_imod_hi[2];
	
	txsdo_imod_hi[0] = 0x06;//0x06-IMOD_H
	txsdo_imod_lo[0] = 0x07;//0x07-IMOD_L
	
	uint16_t code = imod / 0.112;
	txsdo_imod_hi[1] = code >> 2;
	txsdo_imod_lo[1] = code & 3;
	
	master_reg_byte_write(UX3326_SLAVE_ADDRESS,txsdo_imod_hi, 2);
	master_reg_byte_write(UX3326_SLAVE_ADDRESS,txsdo_imod_lo, 2);
}
/***********************************************************************
	** �� �� ���� ux3326_get_mpd_ibias
	** ��    �룺 float* txpower
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� ux3326��ȡ�������������ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_get_mpd_ibias(float* mpd_ibias)
{
	uint8_t impd_data_lo[1];
	uint8_t impd_data_hi[1];
	uint16_t impd_data = 0;
	
	master_reg_1byte_size_read(UX3326_SLAVE_ADDRESS, 0x34, impd_data_hi, 1);
	master_reg_1byte_size_read(UX3326_SLAVE_ADDRESS, 0x35, impd_data_lo, 1);
	
	impd_data = impd_data_hi[0] * 256 + impd_data_lo[0];
	*mpd_ibias = impd_data;
	ddm_adc_out_val.tx_power_adc_out_2 = impd_data;

}

/***********************************************************************
	** �� �� ���� ux3326_set_tx_ld_cpa
	** ��    �룺 uint8_t value����������ֵ
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� ux3326���÷��˽�������ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_set_tx_ld_cpa(uint8_t value)
{
	uint8_t txsdo_cpa_val[2];
	
	txsdo_cpa_val[0] = 0x0A;//0x0A-TX_CTRL11 
	txsdo_cpa_val[1] = value;
	
	master_reg_byte_write(UX3326_SLAVE_ADDRESS,txsdo_cpa_val, 2);
	
}

/***********************************************************************
	** �� �� ���� ux3326_set_rx_swing
	** ��    �룺 uint16_t value��swing����ֵ
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� UX3326�����ն������ڷ�
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_set_rx_swing(uint16_t value)
{
	uint8_t rx_swing_val_reg[2];
	rx_swing_val_reg[0] = 0x13; //0x13-RX_CTRL2
	rx_swing_val_reg[1] = value; 
	master_reg_byte_write(UX3326_SLAVE_ADDRESS, rx_swing_val_reg, 2);
}

/***********************************************************************
	** �� �� ���� ux3326_set_rx_los_threshold
	** ��    �룺 uint8_t los_th �źŶ�ʧ��ֵ
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� UX3326�����ն��źŶ�ʧ��ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_set_rx_los_threshold(uint8_t los_th){
	uint8_t rx_los_threshold[2];
	rx_los_threshold[0] = 0x1C;//0x1C-LOS_CTRL_REG1
	rx_los_threshold[1] = los_th;
	master_reg_byte_write(UX3326_SLAVE_ADDRESS,rx_los_threshold, 2);
	
}

/***********************************************************************
	** �� �� ���� ux3326_set_rx_los_hyst
	** ��    �룺 uint8_t los_hyst �źŶ�ʧ����ֵ
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� UX3326�����ն��źŶ�ʧ����ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_set_rx_los_hyst(uint8_t los_hyst){
	uint8_t rx_los_hyst[2];
	uint8_t rx_los_hyst_old;
	uint8_t mask = 0xE7;//1110 0111

	rx_los_hyst[0] = 0x14;//0x14-LRX_CTRL3 HYS_SD[4:3]
	
	master_reg_1byte_size_read(UX3326_SLAVE_ADDRESS, 0x14, &rx_los_hyst_old, 1);

	rx_los_hyst_old = rx_los_hyst_old & mask;
	rx_los_hyst[1] = (rx_los_hyst_old | (los_hyst << 3));
	master_reg_byte_write(UX3326_SLAVE_ADDRESS,rx_los_hyst, 2);
	
}

/***********************************************************************
	** �� �� ���� ux3326_temperaturel_Sample_Average
	** ��    �룺 float* temperature����β����¶ȵ�ƽ��ֵ
	** ��    ���� ��
	** �� �� ֵ�� void
	** ���������� ux3326�¶Ȳ����ϱ���ƽ��ֵ
	** ��    �ߣ� gqhuan
	** ��    �ڣ� 
************************************************************************/
void ux3326_temperaturel_Sample_Average(float* temperature)
{
    float temp = 0.0;
		float temp_sum = 0.0;
    uint8_t degree = 3;  //���Ĵ������� 2^3
    for(int i = 0;i < (1 << degree);i++)
    {
        //��ȡADC����
		ux3326_get_temperature(&temp);
        temp_sum += temp;
        //fh_delay_us(1000);
		system_delay_ms(1);
    }
    
    //����ѭ��8�ζ�ȡ,��� >>3λ���ǳ���8
    * temperature = temp_sum / 8;

}

/*****************************************************************************
 * �� �� ��  : ux3326_apc_auto_enable_ctrl
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : apc�Զ�����ʹ��
 * �������  : uint8_t ctrl_switch  1--ʹ�ܣ�
                                    0--ȥʹ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void ux3326_apc_auto_enable_ctrl(uint8_t ctrl_switch)
{
	uint8_t value[10];
	uint8_t tx_reg0x0_value = 0;
	uint8_t tx_reg0x2_value = 0;
	uint8_t reg = 0x0;

	memset(value,0,sizeof(value));

	/*reg_0x0:[1:1]APC circuit enable bit. */
	reg = 0x0;
	master_reg_1byte_size_read(UX3326_SLAVE_ADDRESS, reg, &tx_reg0x0_value,1);

	/*reg_0x2: [1:1] CL_OLN */
	reg = 0x02;
	master_reg_1byte_size_read(UX3326_SLAVE_ADDRESS, reg, &tx_reg0x2_value,1);

	tx_reg0x0_value |= (0x1 << 1);
	if(1 == ctrl_switch)
	{
		tx_reg0x2_value |= (0x1 << 1);
	}
	else
	{		
		tx_reg0x2_value &= ~(0x1 << 1);
	}

	value[0] = 0x0;
	value[1] = tx_reg0x0_value;
	master_reg_byte_write(UX3326_SLAVE_ADDRESS, value, 2);

	value[0] = 0x2;
	value[1] = tx_reg0x2_value;
	master_reg_byte_write(UX3326_SLAVE_ADDRESS, value, 2);

	return;
}


/*****************************************************************************
 * �� �� ��  : ux3326_apc_target_voltage
 * �� �� ��  : fz
 * ��������  : 2024��9��4��
 * ��������  : ����apcĿ���ѹ
 * �������  : float voltage_target :APCĿ���ѹֵ
 * �������  : ��
 * �� �� ֵ  : ��
 * ���ù�ϵ  : �ⲿ����
 * ��    ��  : ��

*****************************************************************************/
void ux3326_apc_target_voltage(float voltage_target)
{	
	uint8_t tx_imod_lo[2];
	uint8_t tx_imod_hi[2];
	uint16_t temp_data = 0;
	float temp_float = 0.0;

	//I_PA_SET DAC  Operational Range:0 to 750uA; Typical Step Size:0.78uA
	temp_float = (voltage_target > 750) ? 750 : voltage_target;
	
	temp_data = temp_float / 0.78;
		
	tx_imod_hi[0] = 0x08;//PA_SET(9:2) 
	tx_imod_lo[0] = 0x09;//PA_SET(1:0) 

	tx_imod_hi[1] = temp_data >> 2;
	tx_imod_lo[1] = temp_data & 0x3;
	
	master_reg_byte_write(UX3326_SLAVE_ADDRESS, tx_imod_hi, 2);
	master_reg_byte_write(UX3326_SLAVE_ADDRESS, tx_imod_lo, 2);

	return;
}

#endif



#include <stdio.h>
#include "gd32e501.h"
#include "mcu_pin_type.h"
#include "mcu_data_type.h"
#include "mcu_system_comm.h"
#include "thermistor_rth.h"
#include "adc_sample_interface.h"
#include "sff_8472.h"

#if defined(FH_IC_SGM41296_HARDWARE) && (FH_IC_SGM41296_HARDWARE == CFG_YES)
#include "sgm41296_tec.h"
#else

#error "not define tec device!"

#endif

//extern volatile DDM_ADC_OUT_VAL ddm_adc_out_val;//外部ddm监控变量ADC值

/*************************************************************************
* 变量功能：固定电阻10K, Vcc:2.5v, 热敏电阻对应的ADC,	
* 取值范围：数组下标0表示-40度，最大125度
* 注意事项：无
*************************************************************************/
uint16_t g_tec_temp_adc[] = {
	3978,
	3970,
	3962,
	3953,
	3944,
	3934,
	3924,
	3914,
	3902,
	3891,
	3878,
	3865,
	3852,
	3837,
	3822,
	3807,
	3790,
	3773,
	3755,
	3737,
	3717,
	3697,
	3675,
	3653,
	3630,
	3606,
	3581,
	3555,
	3529,
	3501,
	3473,
	3444,
	3413,
	3382,
	3350,
	3317,
	3283,
	3249,
	3213,
	3177,
	3140,
	3101,
	3062,
	3023,
	2982,
	2941,
	2900,
	2858,
	2815,
	2772,
	2728,
	2684,
	2639,
	2594,
	2549,
	2504,
	2458,
	2413,
	2367,
	2321,
	2275,
	2230,
	2184,
	2138,
	2093,
	2048,
	2003,
	1959,
	1915,
	1871,
	1828,
	1785,
	1742,
	1700,
	1659,
	1618,
	1578,
	1539,
	1500,
	1461,
	1424,
	1387,
	1351,
	1315,
	1280,
	1246,
	1213,
	1180,
	1148,
	1116,
	1086,
	1056,
	1027,
	999,
	971,
	944,
	918,
	892,
	867,
	843,
	819,
	796,
	774,
	752,
	731,
	710,
	690,
	671,
	652,
	634,
	616,
	598,
	581,
	565,
	549,
	534,
	519,
	504,
	490,
	477,
	463,
	451,
	438,
	426,
	415,
	403,
	392,
	381,
	371,
	361,
	352,
	342,
	333,
	324,
	316,
	307,
	299,
	291,
	284,
	276,
	269,
	262,
	255,
	249,
	242,
	236,
	230,
	224,
	219,
	213,
	208,
	202,
	198,
	192,
	188,
	183,
	179,
	175,
	170,
	166,
	162,
	158,
	155,
	151,
	147,
	144
};


/* add by fz, 20231013, 原因:壳温对应的adc,[-40,125],刻度是5 */
/*************************************************************************
* 变量功能：固定电阻10K, Vcc:2.5v, 热敏电阻对应的ADC,	
* 取值范围：数组下标0表示-40度，最大125度，刻度为5
* 注意事项：无
*************************************************************************/
uint16_t g_case_temp_adc[] = {
	3807,
	3734,
	3648,
	3549,
	3437,
	3312,
	3176,
	3029,
	2873,
	2711,
	2545,
	2377,
	2211,
	2048,
	1891,
	1741,
	1600,
	1465,
	1341,
	1226,
	1121,
	1024,
	937,
	857,
	785,
	719,
	660,
	607,
	559,
	516,
	478,
	443,
	411,
	383
};

/*****************************************************************************
 * 函 数 名  : calc_temp_value
 * 负 责 人  : fz
 * 创建日期  : 2023年5月24日
 * 函数功能  : 利用插值法计算温度
 * 输入参数  : uint16_t* tec_table, 数组表
			uint16_t tec_count, 数组中的元素
			uint16_t leftn,		数组中左位
			uint16_t rightn,    数组中右位
			uint16_t adc_value  需要计算的adc
 * 输出参数  : uint32_t* temp   温度的整数，原数据*100，保留两位小数
 * 返 回 值  : 无
 * 调用关系  : 内部调用 (find_adc_temp)
 * 其    它  : 因为tec 热敏电阻是[-40,120],刻度是1,所以数组下标表示温度
 [0,160]=>[-40,120]

*****************************************************************************/
void calc_temp_value(uint16_t* tec_table,
	uint16_t tec_count,
	uint16_t leftn,
	uint16_t rightn,
	uint16_t adc_value,
	uint32_t* temp)
{
	/* add by fz, 20230625, 原因:参数合法性检查 */
	if (NULL == tec_table || tec_count < 1 || NULL == temp)
	{
		return;
	}

	/* add by fz, 20230625, 原因:参数合法性检查 */
	if (leftn > rightn || rightn >= tec_count)
	{
		return;
	}

	/* add by fz, 20230625, 原因:插值计算 */
	if (leftn == rightn)
	{
		*temp = leftn * CALC_FLOAT_PARAM;
	}
	else
	{
		*temp = leftn * CALC_FLOAT_PARAM +
			(*(tec_table + leftn) - adc_value) * CALC_FLOAT_PARAM / (*(tec_table + 
			leftn) - *(tec_table + rightn));
	}

}



/*****************************************************************************
 * 函 数 名  : find_adc_temp
 * 负 责 人  : fz
 * 创建日期  : 2023年5月27日
 * 函数功能  : 查找温度
 * 输入参数  : uint16_t adc_value,  要查找的adc
				uint16_t* tec_table,   数据表
				uint16_t tec_count		数据表中的元素个数
 * 输出参数  : uint32_t* temp   输出找到的数据 (温度)
，因为保留两小数，因此数据是*100
 * 返 回 值  : ERROR-失败;SUCCESS成功
 * 调用关系  : 内部调用
 * 其    它  : 二叉法查找法

*****************************************************************************/
uint32_t find_adc_temp(uint16_t adc_value, uint16_t* tec_table, uint16_t 
		tec_count,uint32_t* temp)
{
	/*参数初始化*/
	uint16_t left_n = 0;
	uint16_t right_n = 0;
	uint16_t mid = 0;	

	/*参数合法性检查*/
	if (NULL == tec_table || tec_count < 1 || NULL == temp)
	{
		return ERROR;
	}
	right_n = tec_count - 1;

	if (adc_value < *(tec_table + right_n))
	{
		adc_value = *(tec_table + right_n);
	}
	else if(adc_value > *tec_table)
	{
		adc_value = *tec_table;
	}

	/* add by fz, 20230625, 原因:二叉法查找及计算 */
	while (left_n <= right_n)
	{
		mid = (left_n + right_n) / 2;
		if (*(tec_table + mid) == adc_value)
		{
			calc_temp_value(tec_table, 
				tec_count, 
				mid,
				mid, 
				adc_value,
				temp);
			return SUCCESS;
		}
		else if (adc_value < *(tec_table + mid))
		{
			left_n = mid + 1;
			if (left_n > right_n)
			{
				calc_temp_value(tec_table, 
					tec_count, 
					right_n - 1, 
					right_n, 
					adc_value, 
					temp);
				return SUCCESS;
			}

		}
		else
		{
			right_n = mid - 1;
			if (right_n < left_n)
			{
				calc_temp_value(tec_table,
					tec_count, 
					left_n - 1,
					left_n, 
					adc_value, 
					temp);
				return SUCCESS;
			}			
		}

	}

	return ERROR;

}


/*****************************************************************************
 * 函 数 名  : get_tec_therm_temperature
 * 负 责 人  : fz
 * 创建日期  : 2023年7月19日
 * 函数功能  : 获取热敏电阻的温度
 * 输入参数  : 无
 * 输出参数  : float *temp  温度
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  : 无

*****************************************************************************/
void get_tec_therm_temperature(float *temp)
{
	float vtherm = 0.0;	
	uint32_t value = 0;
	uint16_t adc_value = 0;
	if(NULL == temp)
	{
		return;
	}
	
#if defined(FH_IC_SGM41296_HARDWARE) && (FH_IC_SGM41296_HARDWARE == CFG_YES)
	adc_value = sgm41296_tec_get_therm_adc();
#else
#error "not define tec device!"
#endif

	find_adc_temp(adc_value,g_tec_temp_adc,
		sizeof(g_tec_temp_adc) / sizeof(g_tec_temp_adc[0]),
		&value);

	vtherm = value;
	vtherm /= CALC_FLOAT_PARAM;
	vtherm -= TEC_RTH_TEMP_ZERO;
	*temp = vtherm;
		
}

/*****************************************************************************
 * 函 数 名  : get_case_therm_temperature
 * 负 责 人  : fz
 * 创建日期  : 2023年10月13日
 * 函数功能  : 获取壳温度
 * 输入参数  : 无
 * 输出参数  : float *temp 温度
 * 返 回 值  : 无
 * 调用关系  : 外部接口
 * 其    它  :  case热敏电阻[-40,125],刻度是5,这里scale = 5

*****************************************************************************/
void get_case_therm_temperature(float *temp)
{
	float vtherm = 0.0;	
	uint32_t value = 0;
	uint16_t adc_value = 0;
	
	if(NULL == temp)
	{
		return;
	}
	
	adc_value = adc_dma_channel_sample_average(CASE_ADC_IN);
	
	ddm_adc_out_val.temperature_adc_out = adc_value;
	
	search_bisection_temp_by_adc(adc_value,g_case_temp_adc,
		sizeof(g_case_temp_adc) / sizeof(g_case_temp_adc[0]),
		5,
		&value);

	vtherm = value;
	vtherm /= CALC_FLOAT_PARAM;

	/*减掉40还原到真实温度*/
	vtherm -= CASE_RTH_TEMP_ZERO;
	*temp = vtherm;
	return;
	
}




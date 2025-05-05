/***********************************************************************************

 * 文 件 名   : mcu_pin_type.h
 * 负 责 人   : fz
 * 创建日期   : 2023年6月16日
 * 文件描述   : mcu的pin脚定义
 * 版权说明   : Copyright (C) 2000-2023   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#ifndef _MCU_PIN_TYPE_H_
#define _MCU_PIN_TYPE_H_

#include "gd32e501.h"
#include "user_config.h"


/*上位机访问mcu的slave*/
//#define SLAVE_I2C 							I2C2
//oo
#define GPIO_I2C_SLAVE_PORT 		GPIOB
#define	GPIO_I2C_SLAVE_SCL  		GPIO_PIN_6
#define	GPIO_I2C_SLAVE_SDA 		GPIO_PIN_7
#define GPIO_I2C_SLAVE_AF			GPIO_AF_4


/*mcu读写外设芯片，master i2c*/
//#define MASTER_A_I2C	,50G			I2C1
//00
#define	GPIO_I2C_MASTER_A_PORT 		GPIOB
#define	GPIO_I2C_MASTER_A_SCL 			GPIO_PIN_10
#define	GPIO_I2C_MASTER_A_SDA 			GPIO_PIN_11
#define GPIO_I2C_MASTER_A_AF			GPIO_AF_1


/*master i2c0,MASTER_B_I2C,10G				I2C0*/
//oo
#define	GPIO_I2C_MASTER_B_PORT 		GPIOB
#define	GPIO_I2C_MASTER_B_SCL 			GPIO_PIN_8
#define	GPIO_I2C_MASTER_B_SDA 			GPIO_PIN_9
#define GPIO_I2C_MASTER_B_AF			GPIO_AF_1


/*壳体温度*/
//oo
#define GPIO_CASE_PORT				GPIOB
#define GPIO_CASE_AD_PIN			GPIO_PIN_2
#define CASE_ADC_IN					ADC_CHANNEL_4

/* add by fz, 20230616, 原因:usart pin定义 */
#define GPIO_USART_PORT			GPIOA
#define GPIO_USART_TX_PIN			GPIO_PIN_9
#define GPIO_USART_RX_PIN			GPIO_PIN_10
#define USART_PERIPH				USART0

/* add by gqhuan, 20240830, 原因:金手指触发 */
//#define	GPIO_TRIGGER_PORT_GOLDFINGER 			GPIOB
//#define	GPIO_TRIGGER_PIN_GOLDFINGER  			GPIO_PIN_0

/* modify by fangzhe, 20250326, 原因:DSP方案换成pb15 */
//oo
#define	GPIO_TRIGGER_PORT_GOLDFINGER 			GPIOB
#define	GPIO_TRIGGER_PIN_GOLDFINGER  			GPIO_PIN_15

//oo
#define D1V8_EN_PORT                        GPIOF
#define D1V8_EN_PIN                       GPIO_PIN_4

//oo
#define D1V2_EN_PORT                        GPIOF
#define D1V2_EN_PIN                       GPIO_PIN_5

//oo
#define D0V75_EN_PORT                        GPIOF
#define D0V75_EN_PIN                       GPIO_PIN_6



#if defined(FH_IC_DSP_HARDWARE) && (FH_IC_DSP_HARDWARE == CFG_YES)

//oo
#define GPIO_50G_TXDISBL_PORT          GPIOA
#define GPIO_50G_TXDISBL_EN           GPIO_PIN_1

//oo
#define GPIO_50G_LOCK_PORT      GPIOA
#define GPIO_50G_LOCK_PIN          GPIO_PIN_11

//oo
#define GPIO_50G_RXSD_PORT          GPIOA
#define GPIO_50G_RXSD_PIN          GPIO_PIN_15



//00
#define GPIO_DSP_RST_PORT           GPIOA
#define GPIO_DSP_RST_PIN           GPIO_PIN_12

//oo
#define GPIO_50G_READY_PORT         GPIOB
#define GPIO_50G_READY_PIN         GPIO_PIN_4

//00
#define GPIO_50G_LOSS_PORT         GPIOB
#define GPIO_50G_LOSS_PIN         GPIO_PIN_5


#endif



#if defined(FH_IC_SGM41296_HARDWARE) && (FH_IC_SGM41296_HARDWARE == CFG_YES)


/**************TEC control****************/
//00
#define	GPIO_TEC_VCTL_PORT 		GPIOA
#define	GPIO_TEC_VCTL_PIN 			GPIO_PIN_6 /*used to VCTL*/
#define TEC_VCTL_DAC_PERIPH		DAC1
#define TEC_VCTL_DAC_OUT			DAC_OUT_0


	
/* add by fz, 20230524, 原因:热敏电阻AD采样引脚通道 */
//oo
#define	GPIO_THERM_PORT 			GPIOC
#define	GPIO_THERM_AD_PIN 			GPIO_PIN_1
#define TEC_THERM_ADC_IN			ADC_CHANNEL_11

/*TEC反馈引脚*/
//oo
#define	GPIO_ITEC_PORT 			GPIOC
#define	GPIO_ITEC_AD_PIN 			GPIO_PIN_0
#define XTEC_ADC_IN					ADC_CHANNEL_10//10

/* add by fz, 20230616, 原因:定义tec上的en,sd使能脚 ;默认为高电平*/
//00
#define GPIO_TEC_SD_PORT			GPIOC
#define GPIO_TEC_SD_PIN			GPIO_PIN_6//GPIO_PIN_4,光模块改为pc6

//oo
#define GPIO_TEC_EN_PORT			GPIOC
#define GPIO_TEC_EN_PIN			GPIO_PIN_7//GPIO_PIN_5,光模块改为pc7

#endif




/* 50G */
#if defined( FH_IC_GN7161_HARDWARE) && (FH_IC_GN7161_HARDWARE == CFG_YES)

#endif


/* 10G */
#if defined( FH_IC_GN7153_HARDWARE) && (FH_IC_GN7153_HARDWARE == CFG_YES)

//oo
#define GPIO_10G_RST_PORT           GPIOA
#define GPIO_10G_RST_PIN           GPIO_PIN_3


//00
#define GPIO_10G_RXSD_PORT          GPIOA
#define GPIO_10G_RXSD_PIN          GPIO_PIN_8

//oo,监控，以前没用到
#define GPIO_MODNR_10G_PORT            GPIOB
#define GPIO_MODNR_10G_PIN              GPIO_PIN_13


#endif

/* 1G */
#if defined( FH_IC_UX3326_HARDWARE) && (FH_IC_UX3326_HARDWARE == CFG_YES)

//oo
#define GPIO_1G_RESET_PORT          GPIOA
#define GPIO_1G_RRESET_PIN           GPIO_PIN_2

//00
#define GPIO_1G_TX_FAULT_PORT       GPIOC
#define GPIO_1G_TX_FAULT_PIN      GPIO_PIN_12

//oo
#define GPIO_1G_SD_PORT             GPIOC
#define GPIO_1G_SD_PIN             GPIO_PIN_13

#endif

#if defined( FH_IC_SGM41282C_HARDWARE) && (FH_IC_SGM41282C_HARDWARE == CFG_YES)



/* add by fangzhe, 20250325, 原因:1G */


//oo
#define	GPIO_RSSI_PORT_1G 				GPIOA
#define	GPIO_RSSI_AD_PIN_1G 			GPIO_PIN_0
#define RSSI_ADC_IN_1G					ADC_CHANNEL_0

//00
#define	GPIO_VS_PORT_1G 				GPIOA
#define	GPIO_VS_DA_PIN_1G 				GPIO_PIN_5
#define VS_DAC_PERIPH_1G				DAC0
#define VS_DAC_OUT_1G					DAC_OUT_1

//oo
#define	GPIO_EN_PORT_1G 				GPIOC
#define	GPIO_EN_PIN_1G 				GPIO_PIN_15

//oo
#define	GPIO_GAIN_PORT_1G 				GPIOF
#define	GPIO_GAIN_PIN_1G 				GPIO_PIN_1

//oo
#define	GPIO_THXOR_PORT_1G 			GPIOF
#define	GPIO_THXOR_PIN_1G				GPIO_PIN_0

/* add by fangzhe, 20250325, 原因:10G */
#define	GPIO_RSSI_PORT_10G 			GPIOB
#define	GPIO_RSSI_AD_PIN_10G 			GPIO_PIN_3
#define RSSI_ADC_IN_10G				ADC_CHANNEL_5

//oo
#define	GPIO_VS_PORT_10G 				GPIOC
#define	GPIO_VS_DA_PIN_10G 			GPIO_PIN_4
#define VS_DAC_PERIPH_10G				DAC2
#define VS_DAC_OUT_10G					DAC_OUT_0

//oo
#define	GPIO_EN_PORT_10G 				GPIOC
#define	GPIO_EN_PIN_10G 				GPIO_PIN_3

//oo
#define	GPIO_GAIN_PORT_10G 			GPIOB
#define	GPIO_GAIN_PIN_10G 				GPIO_PIN_0

//00
#define	GPIO_THXOR_PORT_10G 			GPIOB
#define	GPIO_THXOR_PIN_10G				GPIO_PIN_12





/* add by fangzhe, 20250325, 原因:50G */
//oo
#define	GPIO_RSSI_PORT_50G 			GPIOC
#define	GPIO_RSSI_AD_PIN_50G 			GPIO_PIN_2
#define RSSI_ADC_IN_50G				ADC_CHANNEL_12

//oo
#define	GPIO_VS_PORT_50G 				GPIOA
#define	GPIO_VS_DA_PIN_50G 			GPIO_PIN_4
#define VS_DAC_PERIPH_50G				DAC0
#define VS_DAC_OUT_50G					DAC_OUT_0

//oo
#define	GPIO_EN_PORT_50G 				GPIOC
#define	GPIO_EN_PIN_50G 				GPIO_PIN_9

//oo
#define	GPIO_GAIN_PORT_50G 			GPIOC
#define	GPIO_GAIN_PIN_50G 				GPIO_PIN_11

//oo
#define	GPIO_THXOR_PORT_50G 			GPIOC
#define	GPIO_THXOR_PIN_50G 			GPIO_PIN_10


#endif

/* add by gqhuan, 20240830, 原因:SGM41295管脚定义 */
#if defined(FH_IC_SGM41295_HARDWARE) && (FH_IC_SGM41295_HARDWARE == CFG_YES)
#define	GPIO_LD_EN_PORT_50G 			GPIOA
#define	GPIO_LD_EN_PIN_50G 			GPIO_PIN_11

/* add by fz, 20250304, 原因:PB1用于采样 */
#define GPIO_LD_MON_PORT_50G			GPIOB
#define GPIO_LD_MON_PIN_50G			GPIO_PIN_1
#define LD_50G_MON_ADC_IN				ADC_CHANNEL_9
#endif


/* add by gqhuan, 20240830, 原因:SGM2508管脚定义 */
#if defined(FH_IC_SGM2508_HARDWARE) && (FH_IC_SGM2508_HARDWARE == CFG_YES)

//00
#define GPIO_EA_50G_VBIAS_EN_PORT          GPIOC
#define GPIO_EA_50G_VBIAS_EN_PIN          GPIO_PIN_8

//oo
#define GPIO_50G_EA_CTL_PORT        GPIOC
#define GPIO_50G_EA_CTL_PIN         GPIO_PIN_5
#define EA_50G_CTL_PERIPH           DAC2
#define EA_50G_CTL_DAC_OUT          DAC_OUT_1

//oo
#define	GPIO_EA_CTL_PORT_10G 			GPIOA
#define	GPIO_EA_CTL_PIN_10G 			GPIO_PIN_7
#define EA_CTL_DAC_PERIPH_10G			DAC1
#define EA_CTL_DAC_OUT_10G				DAC_OUT_1

//oo
#define	GPIO_EA_EN_PORT_10G 			GPIOB
#define	GPIO_EA_EN_PIN_10G 			GPIO_PIN_14







#endif

#define MCU_DAC_0				0
#define MCU_DAC_1				1

#define MCU_DAC_OUT_0			0
#define MCU_DAC_OUT_1			1

#define MCU_GPIO_A			0
#define MCU_GPIO_B			1
#define MCU_GPIO_C			2
#define MCU_GPIO_D			3
#define MCU_GPIO_F			4


#endif

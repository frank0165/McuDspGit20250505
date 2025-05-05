/***********************************************************************************

 * 文 件 名   : i2c_opt_ie_data_type.h
 * 负 责 人   : fangzhe
 * 创建日期   : 2025年3月23日
 * 文件描述   : i2c协议栈数据类型
 * 版权说明   : Copyright (C) 2000-2025   烽火通信科技股份有限公司
 * 其    他   : 
 * 修改日志   : 

***********************************************************************************/

#ifndef _I2C_OPT_IE_DATA_TYPE_H_
#define _I2C_OPT_IE_DATA_TYPE_H_

#include "gd32e501.h"
#include "mcu_data_type.h"


#define PRE_LESS_LATER(len1,len2)  ((len1) <= (len2))

#define SLAVE_I2C 							I2C2
#define	SLAVE_EV_IRQn						I2C2_EV_IRQn
#define SLAVE_ER_IRQn						I2C2_ER_IRQn
#define SLAVE_EV_IRQHandler				I2C2_EV_IRQHandler
#define SLAVE_ER_IRQHandler				I2C2_ER_IRQHandler
							

//50G
#define MASTER_A_I2C						I2C1
#define	MASTER_A_EV_IRQn					I2C1_EV_IRQn
#define MASTER_A_ER_IRQn					I2C1_ER_IRQn
#define MASTER_A_EV_IRQHandler				I2C1_EV_IRQHandler
#define MASTER_A_ER_IRQHandler				I2C1_ER_IRQHandler

//10G
#define MASTER_B_I2C						I2C0
#define	MASTER_B_EV_IRQn					I2C0_EV_IRQn
#define MASTER_B_ER_IRQn					I2C0_ER_IRQn
#define MASTER_B_EV_IRQHandler				I2C0_EV_IRQHandler
#define MASTER_B_ER_IRQHandler				I2C0_ER_IRQHandler


#define CHECK_DEV_ERR_I2C(dev_i2c)		(MASTER_A_I2C != dev_i2c && MASTER_B_I2C != dev_i2c)




#define SLAVE_RECEIVE_ADDR()				g_i2c_global_vars.g_receive_address

/* add by fz, 20230515, 原因:i2c回调接口数目 */
#define I2C_CALL_BACK_ITEMS	20

/* add by fz, 20231206, 原因:i2c的slave配置信息 */
typedef struct _I2C_SLAVE_BUFF_CFG_
{
	uint8_t read_flag;	/*i2c的状态，0-表示初始;1-表示读标识;其它未定，目前没用到*/
	uint32_t buffer_idx; /*slave_buffer下标*/
	
	I2C_ALL_ADDRESS_INFO address_info;	/*地址配置信息*/

	/*存入i2c的数据*/
	uint8_t slave_buffer[I2C_SLAVE_BUFFER_MAX];
	
}I2C_SLAVE_BUFF_CFG;


/*i2c回读的callback*/
typedef void (*I2C_READ_CFG_CALLBACK)(I2C_ALL_ADDRESS_INFO *p_slave_info,
	uint8_t *p_buff,
	uint32_t buff_len);

/*i2c回读的数据结构*/
typedef struct _I2C_READ_CFG_CALLBACK_HANDLE_
{
	uint32_t slave_address;
	I2C_READ_CFG_CALLBACK callback;
}I2C_READ_CFG_CALLBACK_HANDLE;



				
/*****************************************************************************
 * 函 数 名  : 回调函数的I2C写接口
 * 负 责 人  : fz
 * 创建日期  : 2023年7月17日
 * 函数功能  : i2c的写功能
 * 输入参数  : uint32_t slave_address    设备地址
 				uint8_t *p_buff          写入的内容；首字节p_buff[0]是寄存器
 			   uint32_t buff_len		p_buff的长度
 * 输出参数  : 无
 * 返 回 值  : 无
 * 调用关系  : 内部调用
 * 其    它  : 无

*****************************************************************************/
typedef void (*I2C_WRITE_CFG_CALLBACK)(uint32_t slave_address,uint8_t *p_buff,uint32_t buff_len);



/* add by fz, 20230515, 原因:i2c的写的回调数据结构 */
typedef struct _I2C_WRITE_CFG_CALLBACK_HANDLE_
{
	uint32_t slave_address;
	I2C_WRITE_CFG_CALLBACK callback;
}I2C_WRITE_CFG_CALLBACK_HANDLE;


/* add by fz, 20231206, 原因:i2c的master配置信息 */
typedef struct _I2C_MASTER_BUFF_CFG_
{
	uint8_t read_flag;	/*i2c的状态标识，0-初始状态;1-read状态;2-write状态*/
	uint32_t buffer_idx; /*master_buffer下标*/
	
	I2C_ALL_ADDRESS_INFO address_info;	
	uint8_t master_buffer[I2C_MASTER_BUFFER_MAX];
	
}I2C_MASTER_BUFF_CFG;



#define GET_MASTER_CFG_OF_I2C(dev_i2c)		(MASTER_A_I2C == dev_i2c) ? \
									&g_ai2c_master_info_cfg : &g_bi2c_master_info_cfg	

/* add begin by fz, 20230515, 原因:自定义i2c中断中的状态事件 */
typedef enum _MCU_I2C_INT_STATUS_
{
	I2C_INT_RBNE_STATUS = 0,
	I2C_INT_TC_STATUS,
	I2C_INT_ADDSEND_STATUS,
	I2C_INT_STPDET_STATUS,
	I2C_INT_TI_STATUS,
	I2C_INT_NACK_STATUS,
	I2C_INT_NON_STATUS,
	I2C_INT_STAT_TR_STATUS
	
}MCU_I2C_INT_STATUS;

/* add by fz, 20231206, 原因:i2c的lock */
typedef enum _I2C_LOCK_SEM_
{
	I2C_LOCK_IDLE = RESET,
	I2C_LOCK_BUSY = SET
	
}I2C_LOCK_SEM;

 
/*设定mcu的地址*/
#define MCU_I2C_ADDRESS7 0x82

/*设定i2c的slave second地址，见寄存器手册*/
#define MCU_SECOND_ADDRESS7	0x83




typedef struct _MasterI2cStatus_
{
    uint32_t I2cA_RegAddr;
    uint32_t I2cB_RegAddr;
    union 
    {
        uint32_t I2cStatus;
        struct {
         uint32_t MasterAWork: 1; /*0为write,1为read*/
         uint32_t MasterA_Scl: 1;
         uint32_t MasterA_Sda: 1;
         uint32_t MasterA_Irq: 4;
         uint32_t MasterBWork: 1; /*0为write,1为read*/
         uint32_t MasterB_Scl: 1;
         uint32_t MasterB_Sda: 1;
         uint32_t MasterB_Irq: 4;     
            }bits;   
    }I2cOp;
}MasterI2cStatus;

#if 0

/*slave接收的地址*/
volatile uint32_t g_receive_address = 0;

/*************************************************************************
* 变量功能：i2c slave中断模式中，read handle标识
* 取值范围：RESET-read未发生；SET-read发生；
* 注意事项：无
*************************************************************************/
volatile uint8_t g_slave_read_handle_flag = RESET;

/*************************************************************************
* 变量功能：i2c slave中断模式中，write handle标识
* 取值范围：RESET-write未发生；SET-write发生；
* 注意事项：无
*************************************************************************/
volatile uint8_t g_slave_write_handle_flag = RESET;

/*************************************************************************
* 变量功能：i2c slave中断模式中，receive handle标识
* 取值范围：RESET-receive未发生；SET-receive发生；
* 注意事项：无
*************************************************************************/
volatile uint8_t g_slave_receive_handle_flag = RESET;

/*************************************************************************
* 变量功能：i2c slave中断模式中, 地址匹配时设置处理标识位
* 取值范围：RESET-当前中断中处理；SET-中断外处理地址匹配；
* 注意事项：无
*************************************************************************/
volatile uint8_t g_slave_address_handle_flag = RESET;

/*************************************************************************
* 变量功能：i2c中断模式中，write doing 
* 取值范围：I2C_LOCK_IDLE-空闲;I2C_LOCK_BUSY-busy
* 注意事项：无
*************************************************************************/
volatile uint8_t g_write_doing_flag = I2C_LOCK_IDLE;

/*************************************************************************
* 变量功能：i2c中断模式中，read doing 
* 取值范围：I2C_LOCK_IDLE-空闲;I2C_LOCK_BUSY-busy
* 注意事项：无
*************************************************************************/
volatile uint8_t g_read_doing_flag = I2C_LOCK_IDLE;
#endif

typedef struct _I2C_GLOBAL_VARS_PARAM_
{

    /*slave接收的地址*/
    uint32_t g_receive_address;
    MasterI2cStatus g_master_i2c_status;
    
    /*master i2c 状机是否空闲，SET空闲,RESET不空闲*/
    uint8_t g_master_i2c_irq_status_pre;// I2C_INT_STPDET_STATUS;//I2C_INT_NON_STATUS;

/*************************************************************************
* 变量功能：i2c slave中断模式中，read handle标识
* 取值范围：RESET-read未发生；SET-read发生；
* 注意事项：无
*************************************************************************/
    uint8_t g_slave_read_handle_flag;

/*************************************************************************
* 变量功能：i2c slave中断模式中，write handle标识
* 取值范围：RESET-write未发生；SET-write发生；
* 注意事项：无
*************************************************************************/
    uint8_t g_slave_write_handle_flag;

/*************************************************************************
* 变量功能：i2c slave中断模式中，receive handle标识
* 取值范围：RESET-receive未发生；SET-receive发生；
* 注意事项：无
*************************************************************************/
    uint8_t g_slave_receive_handle_flag;

/*************************************************************************
* 变量功能：i2c slave中断模式中, 地址匹配时设置处理标识位
* 取值范围：RESET-当前中断中处理；SET-中断外处理地址匹配；
* 注意事项：无
*************************************************************************/
    uint8_t g_slave_address_handle_flag;

/*************************************************************************
* 变量功能：i2c中断模式中，write doing 
* 取值范围：I2C_LOCK_IDLE-空闲;I2C_LOCK_BUSY-busy
* 注意事项：无
*************************************************************************/
    uint8_t g_write_doing_flag;

/*************************************************************************
* 变量功能：i2c中断模式中，read doing 
* 取值范围：I2C_LOCK_IDLE-空闲;I2C_LOCK_BUSY-busy
* 注意事项：无
*************************************************************************/
    uint8_t g_read_doing_flag;

    /* add by fz, 20231106, 原因:光模块访问标识 */
    uint8_t g_user_access_flag;

}I2C_GLOBAL_VARS_PARAM;

#endif
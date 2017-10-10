#ifndef _BMS20_H_
#define _BMS20_H_
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : BMS.h
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,05,26
//* Description        : 该文件作为系统头文件，对该项目的系统参数进行定义和对所有全局变量进行全局声明
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------每个项目必须要修改的参数---------------------------------------------------------
//----------------------------------------------------------------------------------------------------

///////////////////////////////////系统参数//////////////////////////////////

#define PROJECT_NAME                278     //项目代号

#define StoreAHState                0       //定义是否可以存储
#define BMU_NUMBER                  18      //BMU个数
#define G_BMU_CIRCLE_FLAG           0x3FFFF //BMU个数
#define CELL_NUM                    612     //电池节数
#define CELL_TEMP_NUM               51      //15*3+3*2 = 51, 18*3 = 54.
#define CELL_VOL_GROUP              304     //the number of cell voltage group, 612/3=304, 3 cells/group
#define CELL_TEMP_GROUP             17      //the number of cell temperature group, 51/3=17, 3 temps/group
//#define C                         150     //充电倍率
#define SetCap                      150     //充电倍率  为了区分C  C查找起来太多了  
#define EleBand_Max_Current			500
#define FastChg_Max_Current			240

#define DubugMode                   1       //发送状态机报文

//////////////////////////////////直流快充//////////////////////////////////
#define HIGHEST_ALLOWED_CHARGE_CV   3.65    //最大允许充电单体电压 CV
#define HIGHEST_ALLOWED_CHARGE_V    744.6   //最大允许充电总电压 V   3.65*204=744.6
#define LOWEST_ALLOWED_CHARGE_V     673.2   //最低允许充电总电压 V   3.3*204=673.2

#define HIGHEST_ALLOWED_CHARGE_T    57      //最大允许充电和工作温度   57
#define LOWEST_ALLOWED_CHARGE_T     0       //最低允许充电温度   0
#define LOWEST_ALLOWED_WORK_T       -30     //最低允许工作温度   -30

#define CHARGE_CUTDOWN_CV1          3.55    //第一次降流电压
#define CHARGE_CUTDOWN_CV2          3.55    //第二次降流电压
#define HIGHEST_ALLOWED_CHARGE_A    300.0   //直流最大允许充电电流 A
#define SYS_NOMINAL_AH              150     //系统额定容量 AH
#define SYS_NOMINAL_V               652.8   //系统额定电压 V//3.2*204= 652.8
#define SYS_KWH                     97.9    //系统能量  //150*652.8=97920WH
#define LOWEST_ALLOWED_DISCHARGE_V  510     //最小允许充电总电压 V   2.5*204=510
#define CONSTANT_VOL_WORK           1       //恒压工作
#define CONSTANT_CURT_WORK          2       //恒流工作
#define CELL_TYPE                   3       //01铅酸电池;02镍氢电池;03:磷酸铁锂;04:锰酸铁锂;
                                            //05:钴酸锂;06:三元;07:聚合物;08:钛酸锂;FFH:其他
                                          
#define HIGHEST_VOL                 7344    //CML充电机规格:最大输出能力  3.6*204*10
#define LOWEST_VOL                  6528    //CML充电机规格:最小输出能力   3.2*204*10

#define POWER_SUPPLY 24	// when it's 24 means the BMS power supply is 24V.	
// below is the 24V power supply
#if(POWER_SUPPLY == 24)
#define CC2VOLHIGH                  7.5     //CC2测量范围高
#define CC2VOLLOW                   4.2     //CC2测量范围低
#else
#define CC2VOLHIGH                  7.5     //CC2测量范围高
#define CC2VOLLOW                   2.0     //CC2测量范围低
#endif

////////////////////////加热参数配置//////////////////////////////////////////////
#define HIGHEST_ALLOWED_HEAT_CHARGE_V       673.2   //最大允许加热充电总电压 V   3.3*204=673.2
#define HIGHEST_ALLOWED_HEAT_CHARGE_C       2.13    //最大允许加热充电电流 A                       ??
#define START_ALLOWED_PreHEAT_CHARGE_TEM    0       //开启预加热阀值  上电如果小于此值 直接进入加热                               ??
#define STOP_ALLOWED_PreHEAT_CHARGE_TEM     5       //关闭预加热阀值                                  ??
#define START_ALLOWED_HEAT_CHARGE_TEM       10      //开启加热阀值 上电如果小于此值 进入边充电边加热 
#define STOP_ALLOWED_HEAT_CHARGE_TEM        15      //关闭加热阀值 
#define BACK_HEAT_TEM                       -1      //关闭加热阀值 
#define COOL_TYPE                           3       //1 自然冷却 2：风扇冷却 3：水冷
#define Chg_Socet_Max_Temperatue_lv1		85
#define Chg_Socet_Max_Temperatue_lv2		120
///////////////////////BMS最后保护的阀值///////////////////////
#define LOWEST_CELL_VOL     2.0		//放电最小单体电压
#define HIGHEST_CELL_VOL    3.85	//充电单体最大单体电压
#define HIGHEST_BATT_VOL    775		//最大总电压3.8*204 = 775.2
#define HIGHEST_TEM         62		//最高温度62

//////////////////////BMS功率变化速度//////////////////////////
#define POWERSPEED  0.5       //功率的变化速度

//////////////////////高压等级:BMS绝缘计算采样电阻值//////////////////////////
#define RESVALUE  0.2       //采样电阻为0.2K

//////////////////////BMS标定高压时的配置电压//////////////////////////
#define HIGHVOL_19    350       //发送0x19时对应的电压
#define HIGHVOL_23    550      //发送0x23时对应的电压

#include <hidef.h>      /* common defines and macros */
#include <string.h>
#include "derivative.h"      /* derivative-specific definitions */
//底层头文件
#include  "mc9s12gpio.h"
#include  "74hc595.h"
#include  "adc.h"
#include  "bmn.h"
#include  "mscan.h"
#include  "RTI.h"
#include  "sd2405.h"
#include  "dflash.h"
#include  "ProcessBMU.h"
#include  "current.h"
#include  "SocAHintegral.h"
#include  "Record.h"
#include  "Storage.h"
#include  "M95M02.h"
#include  "Connect.h"
//应用层头文件
#include  "Machine.h"
#include  "VehicleCAN.h"
#include  "InnerCAN.h"
#include  "FastChargeCAN.h"
#include  "SOF.h"
#include  "feedBack.h"
#include  "SocAdjust.h"
#include  "Heat.h"
#include  "MachineControl.h"
//#include "BatteryOverVoltage1_types.h"
#include "Fault.h"
#include "24LC64.h"
#include "InitBMS.h"
#include "mc9s12Isr.h"
#include "ParameterSetting.h"
#include "Q1Q2calculate.h"
#include "Task.h"
#include "DC_ChangerProcess.h"
#include "AC_ChangerProcess.h"
#include "ads1015.h"
#include "lookup_Table_Tem_NEW20170204.h"

#include "Q1.h"
#include "CellTempUnbalance.h"
#include "YoungMan_LT.h"

//#include "Isolation.h"
//*******************************************
//*******************************************
#define  uchar unsigned char
#define  uint  unsigned int
#define  ulong unsigned long

#define U8  uchar
#define U16 uint
#define U32 ulong

#define  HIGH 0
#define  LOW 1

#define ON	1
#define OFF	0

#define on	1
#define off	0

// 任务结构
typedef struct _TASK_COMPONENTS
{
    uchar Run;                 // 程序运行标记：0-不运行，1运行
    uint Timer;                // 计时器
    uint ItvTime;              // 任务运行间隔时间
    void (*TaskHook)(void);    // 要运行的任务函数
} TASK_COMPONENTS;       // 任务定义
/////////
//************************************************************************
//************************************************************************
// 任务清单
typedef enum _TASK_LIST
{
    TASK_CURRENT,
    TASK_SOC,
    TASK_BMU,            
    TASK_VOLTAGE,             
    TASK_INSULATION,             
    TASK_REPORT2PC,
    TASK_STAT_MACHINE,
    TASK_FAULT,
    TASK_RECORD,
    //TASK_DC_RECHARGE,
    TASKS_MAX      // 总的可供分配的定时任务数目                                     
} TASK_LIST;

////////
enum slaveNumber
{
    S0,
    S1,
    S2,
    S3,
    S4,
    S5,
    S6,
    S7
};

//*******************************************
//*******************************************
enum parameter_list
{
    PARA_SOC_VALUE,    //SOC实际值
    //PARA_DISCHARGE_RATIO,//过电流
    PARA_POSRELAY_PSTATE,//总正继电器粘连故障  relayPstate
    //PARA_SINGLE_CAPACITY,  //单体电池容量AH
    PARA_PRECHARGE_RELAY_PSTATE,//预充继电器粘连故障
    PARA_WHOLE_CAPACITY,//电池组总容量
    PARA_BMU_NUMBER,//  电池数量

    PARA_DIFFERENCE_SINGLE_V, // 单体电压均衡值
    PARA_DIFFERENCE_SINGLE_T, // 电池温度均衡值
    PARA_BALANCE_ON_VOLTAGE, //均衡开启电压值
    PARA_BALANCE_OFF_VOLTAGE,//均衡关闭电压值
    PARA_O_SOC_VALUE,// soc高

    PARA_OO_SOC_VALUE,// soc过高
    PARA_L_SOC_VALUE,//soc低
    PARA_LL_SOC_VALUE,//soc过低
    PARA_O_WHOLE_VOLTAGE, // 总电压值高
    PARA_OO_WHOLE_VOLTAGE, // 总电压值极高

    PARA_L_WHOLE_VOLTAGE, // 总电压值低
    PARA_LL_WHOLE_VOLTAGE, // 总电压值极低
    PARA_O_CELL_VOLTAGE, // 单体电压高（过压值）
    PARA_OO_CELL_VOLTAGE, // 单体电压极高
    PARA_L_CELL_VOLTAGE,//  单体电压低(欠压值)

    PARA_LL_CELL_VOLTAGE,//  单体电压极低
    PARA_O_TEMPERATURE,//过温
    PARA_OO_TEMPERATURE,//温度极高
    PARA_L_TEMPERATURE, // 温度低
    PARA_LL_TEMPERATURE, // 温度极低

    PARA_O_CONSISTENCY_V, //电压一致性差
    PARA_OO_CONSISTENCY_V,//电压一致性极差
    PARA_O_CONSISTENCY_T, //温度一致性差
    PARA_OO_CONSISTENCY_T,//温度一致性极差
    PARA_CURRENT,//   过电流值

    PARA_HIGHEST_RECHARGE_VOLTAGE,//允许最高充电端电压
    PARA_HIGHEST_RECHARGE_CURRENT,//最大允许充电电流 
    PARA_HIGHEST_RECHARGE_CURRENT_TIME,//允许最大充电电流时间
    PARA_HIGHEST_DISCHARGE_CURRENT,//最大允许放电电流 
    PARA_HIGHEST_CHARGE_CURRENT_TIME,//允许放电电流最大电流时间

    PARA_L_ISOLATION_RESISTANCE, //  绝缘电阻低值
    PARA_LL_ISOLATION_RESISTANCE, //  绝缘电阻过低值

    PARA_ENDFLAG
};
enum storage_list 
{
    INDEX,
    TOTAL_VOLTAGE,
    TOTAL_CURRENT,
    PARA_SOC_DISPLAY, // SOC值
    SYS_CONTACTORS_STATE,  //总正总负继电器状态

    PARA_ERROR_LEVER,//故障等级值  1:1级故障  2:2级故障
    CAUTION_FLAG_1,
    CAUTION_FLAG_2,
    CAUTION_FLAG_3,
    CAUTION_FLAG_4,

    SYS_REALTIME_SECOND,
    SYS_REALTIME_MINUTE,
    SYS_REALTIME_HOUR,
    SYS_REALTIME_WEEK,
    SYS_REALTIME_DAY,

    SYS_REALTIME_MONTH,
    SYS_REALTIME_YEAR,
    CELL_MAX_TEM,
    CELL_MIN_TEM,
    CELL_AVERAGE_TEM,

    CELL_MAX_VOLTAGE,
    CELL_MIN_VOLTAGE,
    CELL_AVERAGE_VOLTAGE,
    SYS_INSULATION_P,
    SYS_INSULATION_N,
    
    VOLT_K1,
    VOLT_B1,
    VOLT_K2,
    VOLT_B2,
    VOLT_K3,
    VOLT_B3,
    
    VERIFICATION  //校验
};

enum storage_cell_vol_list 
{  
    CELL_VOLTAGE_0,
    CELL_VOLTAGE_1,
    CELL_VOLTAGE_2,
    CELL_VOLTAGE_3,
    CELL_VOLTAGE_4,
    CELL_VOLTAGE_5,
    CELL_VOLTAGE_6,
    CELL_VOLTAGE_7,
    CELL_VOLTAGE_8,
    CELL_VOLTAGE_9,

    CELL_VOLTAGE_10,
    CELL_VOLTAGE_11,
    CELL_VOLTAGE_12,
    CELL_VOLTAGE_13,
    CELL_VOLTAGE_14,
    CELL_VOLTAGE_15,
    CELL_VOLTAGE_16,
    CELL_VOLTAGE_17,
    CELL_VOLTAGE_18,
    CELL_VOLTAGE_19,

    CELL_VOLTAGE_20,
    CELL_VOLTAGE_21,
    CELL_VOLTAGE_22,
    CELL_VOLTAGE_23,
    CELL_VOLTAGE_24,
    CELL_VOLTAGE_25,
    CELL_VOLTAGE_26,
    CELL_VOLTAGE_27,
    CELL_VOLTAGE_28,
    CELL_VOLTAGE_29,

    CELL_VOLTAGE_30,
    CELL_VOLTAGE_31,
    CELL_VOLTAGE_32,
    CELL_VOLTAGE_33,
    CELL_VOLTAGE_34,
    CELL_VOLTAGE_35,
    CELL_VOLTAGE_36
    
};

typedef struct {
	U16	cell_V[BMU_NUMBER][CELL_NUMBER];	// all BMU's cell voltage
	U8	cell_T[BMU_NUMBER][Tem_NUMBER];		// all BMU's cell temperature
	
	U16	cell_V_max[BMU_NUMBER];				// each BMU's cell max voltage
	U16	cell_V_min[BMU_NUMBER];				// each BMU's cell min voltage
	
	U8	cell_T_max[BMU_NUMBER];				// each BMU's cell max temperature
	U8	cell_T_min[BMU_NUMBER];				// each BMU's cell min temperature

	U8	cell_V_max_group_num[BMU_NUMBER];				// the max voltage in the BMU's LTC6802 number
	U8	cell_V_min_group_num[BMU_NUMBER];				// the min voltage in the BMU's LTC6802 number
	U8	cell_V_max_num[BMU_NUMBER];			// the max voltage in the BMU's LTC6802's cell number
	U8	cell_V_min_num[BMU_NUMBER];			// the min voltage in the BMU's LTC6802's cell number

	U8	cell_T_max_group_num[BMU_NUMBER];	// the max temperature in the BMU's LTC6802 number
	U8	cell_T_min_group_num[BMU_NUMBER];	// the min temperature in the BMU's LTC6802 number
	U8	cell_T_max_num[BMU_NUMBER];			// the max temperature in the BMU's LTC6802's cell number
	U8	cell_T_min_num[BMU_NUMBER];			// the min temperature in the BMU's LTC6802's cell number
} BMU_CELL_MSG;

typedef struct{
	U16 CellVoltageMax;
	U16 CellVoltageMin;
	
	U8	CellVoltageMaxPackNum;
	U8	CellVoltageMinPackNum;
	
	U8	CellVoltageMaxNum;
	U8	CellVoltageMinNum;
	
	U8	CellTempMax;
	U8	CellTempMin;

	U8	CellTempMaxPackNum;
	U8	CellTempMinPackNum;

	U8	CellTempMaxNum;
	U8	CellTempMinNum;
}BMS_CELL_MSG;


#define DEVICE_SERIAL_NUMBER 0x11    //	部件序列号 1byte
#define HARDWARE_VERSION 0x01    //	硬件版本 低4位有效   
#define SOFTWARE_VERSION 0x01   // 	软件版本 低4位有效
#define COMMUNICATION_VERSION 0x01  // 通讯协议版本 低4位有效

//#define ParamNUMBER 38
#define ENDFLAG 96

#define DISCHARGING 0 //放电
#define FASTRECHARGING 1  //快充
#define RECHARGING 2  //充电
#define TESTSTATE 4  //调试模式

//************ main.c ****************************************
extern unsigned char BMS_SW_Version[8];
extern unsigned char BMUOK;
extern unsigned char HeatFlag; //上电前温度标志位

extern BMU_CELL_MSG			g_bmu_msg;
extern BMS_CELL_MSG			g_bms_msg;
extern U_BMS_STATUS_TYPE	g_bms_status;
extern U_BMS_FAULT_TYPE		g_bms_fault_msg;
extern U_TMS_BMS_MSG		g_TMS_BMS_msg;
extern U_BMS_TMS_MSG		g_BMS_TMS_msg;

 //***********************************************************************************
//*******************************the end**********************************************
//************************************************************************************
///////////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////////////////

#endif

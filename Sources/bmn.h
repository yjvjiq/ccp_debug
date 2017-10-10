//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : bmn.h
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,05,26
//* Description        : 本程序用于计算总电压v1,v2,v3和绝缘阻值Rp,Rn,定义了所有采集电压绝缘的全局变量
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////////////
// Defines
typedef union{
	unsigned char byte;
	struct {
		byte flag0:1;       //CANRx标定判断
		byte flag1:1;       //60s 滤波标志 60s= Filter_N*6
		byte flag2:1;       //未用
		byte flag3:1;       //100V 以上标定
		byte flag4:1;       //200V 标定
		byte flag5:1;       //200V 标定
		byte flag6:1;       //400V 标定
		byte flag7:1;       //400V 标定
	}Bit;
}BMNVPNFLAG ;    //BMN VPN标定任务标志   

/////////////////////////////////////////////////////////////////////////////////////////

#define  CANID_BMNVPN    0x18FF0212
#define  CANID_RPNTOGND  0x18FF0312

#define  CANID_RPTOGND   0x18FF0700
#define  CANID_RNTOGND   0x18FF0800

//BJUID
#define BMN_Part_SerialNum   0x22        //部件序列号
#define BMN_HW_Version       0x02        //硬件版本
#define BMN_SW_Version       0x23        //软件版本
#define BMN_CAN_Pro_Version  0x08        //通讯协议版本


//BMSID
//BMS->BJU
//#define  CANID_BMSID   0x18FF0100
//PC->BJU
//#define  CANID_BMNCC1  0x18FF025A   //兼容PC配置模式   Vpn250V
#define  CANID_BMNCC1  0x18FF0A00   //兼容PC配置模式   Vpn250V
#define  CANID_BMNCC2  0x18FF0800   //绝缘检测使能或禁止。1=使能；0=禁止
/////////////////////////////////////////////////////////////////////////////////////////
// Variables
/////////////////////////////////////////////////////////////////////////////////////////
extern BMNVPNFLAG      BMNVPNflag;
extern unsigned int Vpn_K1;              //
extern  int Vpn_B1;                       //
extern unsigned int Vpn_K2;              //
extern  int Vpn_B2;                       //
extern unsigned int Vpn_K3;              //
extern  int Vpn_B3;                       //

extern float V51_Voltage_CAL_Value;                 //V5两端电压值（开关1闭合，开关2断开）
extern float V52_Voltage_CAL_Value;                  //V5两端电压值（开关1断开，开关2闭合）
//extern long Rp_Vpn_Value;
//extern long Rn_Vpn_Value;
extern float Rp_Vpn_Value;
extern float Rn_Vpn_Value;

extern unsigned int   V51_Voltage_AD_Value; 
extern unsigned int  V52_Voltage_AD_Value;
extern float	g_highVoltageV1; //电池电压
extern float g_highVoltageV2; //预充电继电器与预充电阻之间的电压
extern float g_highVoltageV3;//预充电继电器另一边的电压

extern unsigned char flagV51;
extern unsigned char flagV52;
extern unsigned char ads1110Worked;

extern unsigned int Vpn1_Voltage_AD_Value;        //电池总电压1采样值     0.01V  100~500V   100.00~500.00
//extern unsigned int Vpn1_Voltage_CAL_Value;       //电池总电压1计算值     0.01V  100~500V   100.00~500.00
extern long Vpn1_Voltage_CAL_Value;       //电池总电压1计算值     0.01V  100~500V   100.00~500.00
extern unsigned int Vpn2_Voltage_AD_Value;        //电池总电压2采样值     0.01V  100~500V   100.00~500.00
//extern unsigned int Vpn2_Voltage_CAL_Value;       //电池总电压2计算值     0.01V  100~500V   100.00~500.00
extern long Vpn2_Voltage_CAL_Value;       //电池总电压2计算值     0.01V  100~500V   100.00~500.00
extern unsigned int Vpn3_Voltage_AD_Value;        //电池总电压3采样值     0.01V  100~500V   100.00~500.00
//extern unsigned int Vpn3_Voltage_CAL_Value;       //电池总电压3计算值     0.01V  100~500V   100.00~500.00
extern long Vpn3_Voltage_CAL_Value;       //电池总电压3计算值     0.01V  100~500V   100.00~500.00
/////////////////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////////////////

//extern void Task01_BMN_Init(void);
extern void Task02_BMN_GlobalVariables_Init(void);
//extern void Task03_BMN_MCU_Init(void);
extern void Task04_BMN_FEED_COP(void);

//extern void Task06_BMN_DATA_RECALL(void);
//extern void Task07_BMN_DATA_SAVE(void);
extern void Task08_BMN_ReInit(void);
 
extern void Task09_BMN_GlobalVariables_Clear(void);

extern void Task11_Vpn_StartAD_Polling(void);
extern void Task13_Vpn_Value_Calibrate(void);
extern void Task14_R_Vp_GND_Value_Polling(void);
extern void Task15_R_Vn_GND_Value_Polling(void);
extern void Task17_Rp_Rn_Value_Calculate_Filter(void);

extern void Task21_CAN_SendGouup1(void);
extern void Task22_CAN_SendGouup2(void);

extern void TaskVoltage(void);
extern void TaskInsulation(void);

extern unsigned int GetU1adValue(void);
extern unsigned int GetU2adValue(void);
extern unsigned int GetU3adValue(void);
extern unsigned int GetInsulateVoltAd(void);
extern void TurnOffInsulation(void);
//***************************************************************************************
//***************************************************************************************
//***************************************************************************************
//***************************************************************************************


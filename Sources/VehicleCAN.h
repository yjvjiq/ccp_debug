//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : fotun_Logistics
//* File Name          : VehicleCAN.h
//* Author             : WsM
//* Version            : V1.0.0
//* Start Date         : 2016.7.8
//* Description        : 该文件根据项目通信协议发送相关的报文到整车或交流充电机
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

//////////////////////VCU发送的//////////////////////////
typedef union{
	unsigned char byte;
	
	struct {
		byte flag			:5;
		byte Finish_PreChg	:1;	//bit1      VCU预充电完成
		byte flag1			:2;	//bit4~7    快充继电器状态
	}Bit;
}VCU_REQUEST;

typedef union{
	unsigned char byte;
	
	struct {
		byte CellVolReq		:1;	//bit0      电池包各节点单体电压
		byte CellTempReq	:1;	//bit1      电池包各节点温度
		byte PackMessageReq	:1;	//bit2      电池包信息  
		byte flag			:5;	//bit3~7    预留
	}Bit;
}VCU_CELLREQUEST;

typedef union{
	unsigned char byte;
	
	struct {
		byte VCULife		:4;	//bit0~bit3 VCULife
		byte PowerOnOffReq	:2;	//bit4~bit5 高压上下电指令
		byte flag			:2;	//bit6~7    预留
	}Bit;
}VCU_CONTROL;


typedef union{
	unsigned char byte;
	
	struct {
		byte flag1					:2;	//bit0~1    预留
		byte Charge_Switch			:1;	//bit2      充电开关
		byte rise_Eleband_Switch	:1;	//bit3      降弓开关
		byte flag2					:1;	//bit4      预留
		byte downC_OK				:1;	//bit5      降弓到位
		byte flag3					:2;	//bit6~7    预留
	}Bit;
}VCU_CHGCONTROL;

typedef union{
	unsigned char byte;
	struct{
		byte flag1					:5;	//bit0~5    预留
		byte Eleband_feedback_alarm	:1;	//bit6      预留
		byte rise_Eleband_No_OK		:1;	//bit7
		byte rise_Eleband_Switch	:1;	//bit8    预留
	}Bit;
}VCU_CHGCONTROL_2;

typedef union{
	unsigned char byte;
	
	struct {
		byte flag1			:2;	//bit0~1    预留
		byte falg2			:2; //bit2~3
		byte Parking_Brake	:2;	//bit4~5    驻车信号
		byte flag2			:2;	//bit6~7    预留
	}Bit;
}VCU_PARKINGBRAKE;
//////////////////////VCU发送的//////////////////////////



////////////////////// BMS status, send out//////////////////////////
typedef union{
	unsigned char byte;
	
	struct {
		byte BMS_Life	:4;	//bit0~bit3 life
		byte St_BMS		:4;	//bit4~bit7 BMS当前状态
	}Bit;
}STATUS_GROUP1;

typedef union{
	unsigned char byte;
	
	struct {
		byte BMS_PowerOff_Req	:2;	//bit0~bit1 BMS高压下电请求,自定义的
		byte St_BMS_Balance		:2;	//bit2~bit3 当前均衡状态
		byte St_Ele_Relay		:2;	//bit4~bit5 受电带接触器连接状态
		byte St_CHG_Connect		:2;	//bit6~bit7 充电连接状态
	}Bit;
}STATUS_GROUP2;

typedef union{
	unsigned char byte;
	
	struct {
		byte St_CHG_Mode	:2;	//bit0~bit1 充电模式 
		byte St_Charge		:2;	//bit2~bit3 充电状态
		byte Fault_Level	:2;	//bit4~bit5 故障等级
		byte St_N_Relay		:1;	//bit6      负极继电器状态？？？？？？？？？？？
		byte St_P_Relay		:1;	//bit7      正极继电器状态？？？？？？？？？？自定义的
	}Bit;
}STATUS_GROUP3;

typedef union{
	unsigned char byte;
	struct {
	  byte St_BMS_System	:1;	//bit0      BMS系统状态位
	  byte St_BMU_System	:1;	//bit1      BMU系统状态位
	  byte St_LECU_System	:2;	//bit2~bit3 BMU系统状态位
	  byte St_Bat_Fault		:2;	//bit4~bit5 电池组故障状态
	  byte Mode_BMS_Work	:2;	//bit6~bit7 当前电池工作状态 
     		       
	}Bit;
}STATUS_GROUP4;
//////////////////////  BMS send out status type define end///////////////////


//////////////////////BMS fault msg, send out/////////////////////////////////
typedef union{
	unsigned char byte;
	
	struct {
		byte F0_Fire_Warning	:2;	//bit0~1    火灾预警
		byte F2_Ele_Relay_Con	:2;	//bit2~3    充电插座过温
		byte flag				:4;	//bit4~7    预留
	}Bit;
}ERROR_GROUP0;

typedef union{
	unsigned char byte;
	
	struct {
		byte St_CHG_Allow			:1;  //bit0     充电允许状态位
		byte St_DisCHG_Allow		:1;  //bit1     放电允许状态位
		byte F2_DCChg_Neg_Relay_Con	:1;  //bit2     直流充电负接触器粘连故障
		byte F3_Ele_Relay_Con		:1;  //bit3     受电带充电正接触器粘连
		byte F4_Ch_Over_I			:2;  //bit4~5   充电过流
		byte F6_Ins_Err				:2;  //bit6~7   绝缘电阻低
	}Bit;
}ERROR_GROUP1;    

typedef union{
	unsigned char byte;
	
	struct {
		byte F0_Cell_Over_V		:2;  //bit0~1   单体电池过压
		byte F2_Cell_Under_V	:2;  //bit2~3   单体电池欠压
		byte F4_Temp_Over		:2;  //bit4~5   单体温度过温
		byte flag				:2;  //bit6~7   电池组差异（系统不匹配）预留
	}Bit;
}ERROR_GROUP2; 

typedef union{
	unsigned char byte;
	
	struct {
		byte F0_Sub_Com_Err		:1; //bit0      内部通讯故障
		byte F1_V_CAN_Err		:1; //bit1      外网CAN通信故障
		byte F2_P_Con_Err		:1; //bit2      主正继电器粘连
		byte F3_PreCha_Failure	:1; //bit3      预充电失败
		byte F4_N_Con_Err		:1; //bit4      主负继电器粘连
		byte F5_DC_Con_Err		:1; //bit5      外接充电正接触器粘连
		byte F6_DisChg_Over_I	:2; //bit6~7    放电电流过大
	}Bit;
}ERROR_GROUP3; 

typedef union{
	unsigned char byte;
	
	struct {
		byte F0_SOC_Low		:2;  //bit6~7   SOC低
		byte F2_SOC_Over	:2;  //bit4~5   SOC高
		byte F4_Bat_Under_V	:2;  //bit2~3   电池欠压
		byte F6_Bat_Over_V	:2;  //bit0~1   电池过压
	}Bit;
}ERROR_GROUP4; 

typedef union{
	unsigned char byte;
	struct {
		byte F0_FeedB_Over_I	:2;  //bit0~1   回馈过流
		byte F2_Cell_Dif_T		:2;  //bit2~3   单体温差过大
		byte F4_Cell_Dif_V		:2;  //bit4~5   电池单体压差大
		byte F6_Cell_Under_T	:2;  //bit6~7   单体温度低
	}Bit;
}ERROR_GROUP5;

typedef union{
	unsigned char byte;
	
	struct {
		byte F0_Power_Vol	:1;	//bit0  整车供电24V异常报警
		byte F1_HLVol_Lock	:1;	//bit1  高低压互锁
		byte F2_SOC_Change	:1;	//bit2  SOC跳变
		byte F3_BMS_Protect	:1;	//bit3  BMS极限故障自我保护
		byte F4_flag1		:1;	//bit4  预留
		byte F5_Chg_C_Over	:1;	//bit5  充电电流超限
		byte F6_flag2		:1;	//bit6  预留
		byte F7_Chg_Ins_Low	:1;	//bit7  充电绝缘低报警
	}Bit;
}ERROR_GROUP6;

typedef union{
	unsigned char byte;
	
	struct {
		byte flag				:4;  //bit0~3   预留
		byte F4_HC_Rel_Error	:1;  //bit4     热管理机组接触器故障（只针对水冷系统）
		byte F5_HC_Error		:1;  //bit5	    热管理机组系统故障（只针对热管理系统）
		byte F6_H_Neg_Rel		:1;  //bit6     电池组加热负极接触器故障
		byte F7_H_Pos_Rel		:1;  //bit7     电池组加热正极接触器故障
	}Bit;
}ERROR_GROUP7;

typedef struct{
	byte BMS_Life				:4; //bit0~bit3 life
	byte BMS_HV_Sts				:4; //bit4~bit7 HV ON/pre-charge/HV OFF/ HV on invalid

	byte Attach_Relay_Sts		:2; //bit0~bit1 the attachment relay status.
	byte BMS_Balance_Sts 		:2; //bit2~bit3 the current balance status.
	byte EleBand_Relay_Sts		:2; //bit4~bit5 electric band connect status.
	byte Charger_Connect_Sts	:2; //bit6~bit7 charger connect status
	
	byte Chg_Mode_Sts			:2; //bit0~bit1
	byte Charge_Sts				:2; //bit2~bit3
	byte Fault_Level			:2; //bit4~bit5 
	byte Relay_N_Sts			:1;	//bit6 		self added, not in the vehicle CAN protocal.
	byte Relay_P_Sts 			:1; //bit7		self added, not in the vehicle CAN protocal.
}S_BMS_STATUS_TYPE;

typedef union{
	S_BMS_STATUS_TYPE status;
	byte data[3];
}U_BMS_STATUS_TYPE;

typedef struct{
	byte Fire_Warning_Flt		:2; //bit0~1	火灾预警
	byte ChgSocket_Adhesion_Flt	:2; //bit2~3	充电插座过温
	byte rsvd_0					:4; //bit4~7	预留
	
	byte Bms_Power_Supply_Alarm	:1; //bit0	整车供电24V异常报警
	byte HLVol_Lock_Alram		:1; //bit1	high and low voltage interlock
	byte SOC_Hop_Alarm			:1; //bit2	SOC跳变
	byte BMS_Self_Protect 		:1; //bit3	BMS极限故障自我保护
	byte rsvd_1_4				:1; //bit4	预留
	byte Chg_OverCurrent_Alarm	:1; //bit5	充电电流超限
	byte rsvd_1_6				:1; //bit6	预留
	byte Chg_Ins_Low_Alarm 		:1; //bit7	充电绝缘低报警
	
	byte BMS_Sys_Flt_Sts	  	:1; //bit0
	byte BMU_Sys_Flt_Sts	  	:1; //bit1
	byte LECU_Sys_Sts			:2; //bit2~bit3
	byte Pack_Flt_Sts	  		:2; //bit4~bit5
	byte Bat_ChgDischg_Mode  	:2; //bit6~bit7 
	
	byte Chg_Allow_State		:1;  //bit0 	充电允许状态位
	byte DisChg_Allow_State		:1;  //bit1 	放电允许状态位
	byte KChg_N_Adhesion_Flt	:1;  //bit2 	直流充电负接触器粘连故障
	byte KEleBand_P_Adhesion_Flt:1;  //bit3 	受电带充电正接触器粘连
	byte Chg_OverCurrent_Flt	:2;  //bit4~5	充电过流
	byte Ins_Low_flt 			:2;  //bit6~7	绝缘电阻低
	
	byte Cell_V_High_Flt 		:2;  //bit0~1	单体电池过压
	byte Cell_V_Low_Flt			:2;  //bit2~3	单体电池欠压
	byte Cell_T_High_Flt		:2;  //bit4~5	单体温度过温
	byte Pack_V_Diff_Flt		:2;  //bit6~7	电池组差异（系统不匹配）预留
	
	byte InnerCAN_Com_Flt 		:1; //bit0		内部通讯故障
	byte ExternalCAN_Com_Flt	:1; //bit1		外网CAN通信故障
	byte Kp_Adhesion_Flt		:1; //bit2		主正继电器粘连
	byte PreChg_Fail_Flt		:1; //bit3		预充电失败
	byte Kn_Adhesion_Flt		:1; //bit4		主负继电器粘连
	byte KFastChg_P_Adhesion_Flt:1; //bit5		外接充电正接触器粘连
	byte DisChg_OverCurrent_Flt	:2; //bit6~7	放电电流过大
	
	byte SOC_Low_Flt 			:2;  //bit6~7	SOC低
	byte SOC_High_Flt			:2;  //bit4~5	SOC高
	byte Pack_V_Low_Flt 		:2;  //bit2~3	电池欠压
	byte Pack_V_High_Flt		:2;  //bit0~1	电池过压
	
	byte FeedBack_OverCurrentFlt:2;  //bit0~1	回馈过流
	byte Cell_T_Diff_Flt		:2;  //bit2~3	单体温差过大
	byte Cell_V_Diff_Flt		:2;  //bit4~5	电池单体压差大
	byte Cell_T_Low_Flt			:2;  //bit6~7	单体温度低
	
	byte rsvd_8_03				:4;  //bit0~3	预留
	byte Heat_Machine_Flt		:1;  //bit4 	热管理机组接触器故障（只针对水冷系统）
	byte Heat_Sys_Flt			:1;  //bit5 	热管理机组接触器故障（只针对热管理系统）
	byte KHeat_N_Flt			:1;  //bit6 	电池组加热负极接触器故障
	byte KHeat_P_Flt			:1;  //bit7 	电池组加热正极接触器故障

	byte rsvd_9_03				:4;
	byte HVBranch_CircuitOff_Flt:2;
	byte HVBranch_V_Diff_Flt	:2;
}S_BMS_FAULT_TYPE;

typedef union{
	S_BMS_FAULT_TYPE fault;
	byte data[10];
}U_BMS_FAULT_TYPE;

//////////////////////BMS fault msg, send out end/////////////////////////////////

typedef struct{
	byte mode_cmd			:2;//bit0~bit1
	byte rsvd_0_2_4			:3;
	byte HV_on_request		:1;
	byte chg_mode			:1;
	byte HV_relay_status	:1;

	word pack_volt;
	
	byte rsvd_3;

	byte T_goal;
	byte CellTempMax;
	byte CellTempMin;
	byte rsvd_7;
} S_BMS_TMS_MSG;

typedef union{
	S_BMS_TMS_MSG msg;
	byte data[8];
} U_BMS_TMS_MSG;

typedef struct{
	byte mode_status			:2;//bit0~bit1
	byte rsvd_0_2_6				:5;
	byte TMS_HV_status			:1;

	byte TMS_T_out;
	byte TMS_T_in;
	byte freeze_T;
	byte compressor_frequency;
	byte HV_Volt;
	byte HV_Current;
	byte rsvd_7_0_5				:6;
	byte fault_level			:2;
}S_TMS_BMS_MSG;

typedef union{
	S_TMS_BMS_MSG msg;
	byte data[8];
}U_TMS_BMS_MSG;


//******************************************************************************
//* 以下是用于外部的变量
//******************************************************************************
extern VCU_REQUEST VCU_Request;			//0x0CFF0BEF
extern VCU_CELLREQUEST VCU_CellRequest;	//0x1801D2D0
extern VCU_CONTROL VCU_Control;			//0x1802D2D0
extern VCU_CHGCONTROL VCU_ChgControl;	//0x0C0217A7
extern VCU_CHGCONTROL_2 VCU_ChgControl_2;	//0x0C0217A7
extern VCU_PARKINGBRAKE VCU_ParkBrake;	//0x18FEF117

extern STATUS_GROUP1 status_group1;
extern STATUS_GROUP2 status_group2;
extern STATUS_GROUP3 status_group3;
extern STATUS_GROUP4 status_group4;

extern ERROR_GROUP0 Error_Group0;
extern ERROR_GROUP1 Error_Group1;
extern ERROR_GROUP2 Error_Group2;
extern ERROR_GROUP3 Error_Group3;
extern ERROR_GROUP4 Error_Group4;
extern ERROR_GROUP5 Error_Group5;
extern ERROR_GROUP6 Error_Group6;
extern ERROR_GROUP7 Error_Group7;

extern float g_SOH;

extern float BiggestDischargeCurt;          //最大放电电流
extern float BiggestFeedbackCurt;           //最大回馈电流
extern float BiggestDisCurtContinuous;      //最大持续放电电流
extern float BiggestFeedbackCurtContinuous; //最大持续回馈电流

extern float BiggestDischargePower;         //最大瞬时放电功率
extern float BiggestFeedbackPower;          //最大瞬时回馈功率
extern float BiggestDisPowerContinuous;     //最大持续放电功率
extern float BiggestFeedbackContinuous;     //最大持续回馈功率

extern unsigned int chargeRemainderTime;    //剩余充电时间


extern unsigned char St_heatManage;         //动力电池热管理状态：0没工作；1加热过程中；2cooling

extern unsigned long int chargeAH;          //实际充电总安时
extern unsigned long int dischargeAH;       //实际放电总安时
extern unsigned int Charge_Times;           //充电次数
extern float DC_ChargePower;                //充电电量
extern float VehicleSpeed;                  //车速信号
extern unsigned char WiFiLife;
//******************************************************************************
//* 以下是用于外部的函数
//******************************************************************************

extern void BMS_To_VCU_BasicMsg0(void);
extern void BMS_To_VCU_BasicMsg1(void);
extern void BMS_To_VCU_BasicMsg2(void);
extern void BMS_To_VCU_CHGMsg1(void);

extern void BMS_To_VCU_BatteryMsg1(void);
extern void BMS_To_VCU_BatteryMsg2(void);
extern void BMS_To_VCU_BatteryMsg3(void);
extern void BMS_To_VCU_BatteryMsg4(void);
extern void BMS_To_VCU_BatteryMsg5(void);
extern void BMS_To_VCU_BatteryMsg6(void);
extern void BMS_To_VCU_BatteryMsg7(void);
extern void BMS_To_VCU_BatteryMsg8(void);
extern void BMS_To_VCU_BatCellVolData(void);
extern void BMS_To_VCU_BatCellTempData(void);
extern void BMS_VCU_WIFI(void);
                    


extern void bmsToPcTestCar(void);
extern void bmsToPcTestCar1(void);
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////end/////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

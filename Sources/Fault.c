//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : 青年浦江6123
//* File Name          : Fault.c
//* Author             : SLX
//* Version            : V1.0.0
//* Start Date         : 2016.11.30
//* Description        : 该文件 对系统的各级故障判断
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "BMS20.h"
//#include "Fault.h"
#include "TotalVoltageOverVoltage.h"
#include "TotalVoltageUnderVoltage.h"
#include "DisChargeOverCurrent.h"
#include "ChargeOverCurrent.h"
#include "CellOverVoltage.h"
#include "CellUnderVoltage.h"
#include "CurrentSensorFault.h"
#include "CellVolUnbalance.h"
#include "BatteryTemperatureLow.h"
#include "BatteryTemperatureHigh.h"
#include "socLow.h"
#include "IsolationLow.h"
#include "ChargeSocketOverTemp.h"
#include "Supply24V.h"
#include "PackFault.h"

///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 

//***********************************************************************************
//***********************************************************************************
//typedef struct{
	/* g_caution_Flag_1 */
//	U8 Pack_UV_Flt_lv3		:1; //bit0
//	U8 CellUV_Flt_lv3		:1;	//bit1
//	U8 SystemVoltageOV		:1;
//	U8 CellVoltageOV		:1;
//	U8 LowIsolation			:1;
//	U8 CellTemperatureOT	:1;
//	U8 CellTemperatureUT	:1;
//	U8 ChargeOC				:1;	//bit7

//	
//}CAUTION_FLAG_TYPE;

unsigned char	g_caution_Flag_1 = 0;//BMS故障状态 FOR 上位机
unsigned char	g_caution_Flag_2 = 0;
unsigned char	g_caution_Flag_3 = 0;
unsigned char	g_caution_Flag_4 = 0;
unsigned int	g_errorCounter;
unsigned char	ACCha_Flag_BST = 0;
unsigned char	ACCOverTime = 0;//交流充电机通信故障
unsigned char	VCU_ParkBrakeOverTime = 0;
unsigned char	VCUOverTime = 0;//与VCU通讯故障
unsigned char	SBMSOverTime = 0;//与另一主板SBMS通讯故障
unsigned char	BMU_OverTime[BMU_NUMBER] = 0;

//unsigned char CarErrorLevel = 0;

CUTDISCURT0  CutDisCurt0;
CUTDISCURT50 CutDisCurt50;
//CUTDISCURT70 CutDisCurt70;

CUTCHACURT0 CutChaCurt0;
CUTCHACURT50 CutChaCurt50;
//CUTCHACURT70 CutChaCurt70;

CUTDCCHACURT0 CutDCChaCurt0;
CUTDCCHACURT50 CutDCChaCurt50;
//CUTDCCHACURT70 CutDCChaCurt70;

CUTACCHACURT0 CutACChaCurt0;
CUTACCHACURT50 CutACChaCurt50;
//CUTACCHACURT70 CutACChaCurt70;

unsigned char test1=0;

//declaration for the function in fault.c below
int TurnOffAllRelay(void);

typedef enum{
	HV_On_Status = 0,	// 0
	PreChg_Status,		// 1
	HV_Off_Status,		// 2
	HV_On_Invalid_Status// 3
} e_BMS_HV_STATUS;

//******************************************************************************
//* Function name:    ErrorToCarPC
//* Description:     不同故障的处理方式
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
/*void ErrorToCarPC(unsigned char Err1,unsigned char Err2,unsigned char Err3,unsigned char Err4,unsigned char *CarError,
                  unsigned char *PCErrorLevel1,unsigned char *PCErrorLevel2, unsigned char *PCErrorLevel3)//
{
    if(Err1==1)//如果1级故障 
    {
        *CarError=1;
        *PCErrorLevel1 |= 0x04;//to PC
    } 
    else//没有1级故障
    {           
        if(Err1==1)//如果有二级故障
        {
            *CarError=2;
            *PCErrorLevel2=1;//to PC
        } 
        else//如果没有二级故障
        {
            *CarError=0;
            *PCErrorLevel2=0;//to PC                      
            if(Err1==1)//如果有三级故障
            {
                *CarError=3;
                *PCErrorLevel3=1;//to PC 
            } 
            else//如果三级无故障
            {
                *CarError=0;
                *PCErrorLevel3=0;//to PC 
                if(Err1==1)//4级故障
                    *CarError = 4;                
                else  //无4级
                    *CarError = 0;                              
            }
        }
    }
} */
//******************************************************************************
//* Function name:    errorSystemVoltageOV
//* Description:      电池包总电压过压故障 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorSystemVoltageOV(void) 
{
    unsigned char Error[4]={0};
    unsigned char i;
    unsigned char Level=0; 
	float reharge_pack_v = 0;
	
    //judge by different BMS work mode, as the input is different.
	if(g_BmsModeFlag == DISCHARGING){ //discharge mode.
        Level=TotalVoltageOverVoltage_custom(g_systemVoltage,g_highVoltageV3,DISCHARGING);
	}
	else if(g_BmsModeFlag == FASTRECHARGING){//fast charge mode.
        Level=TotalVoltageOverVoltage_custom(g_systemVoltage,g_highVoltageV4,FASTRECHARGING);
	}
	else if(g_BmsModeFlag == RECHARGING){ // ACC charge mode.(re-charging mode)
		if(g_highVoltageV5 >= g_highVoltageV6){
			reharge_pack_v = g_highVoltageV5;
		}
		else{
			reharge_pack_v = g_highVoltageV6;
		}
        Level=TotalVoltageOverVoltage_custom(g_systemVoltage,reharge_pack_v,RECHARGING);
	}
	
    Error_Group4.Bit.F6_Bat_Over_V = Level;//send to vehicle CAN.
    g_bms_fault_msg.fault.Pack_V_High_Flt = Level; //the same as above.

    ///////////////////The fault level process and send out/////////////////////////   
    for(i=1;i<4;i++){
       if(i==Level) {
           Error[i]=1;
       }
    }
	//level 1 process
	Can554Byte2.Bit.F2_systemOV1 				= Error[1]; // send to PC software.
    
    //level 2 process
    Can554Byte0.Bit.F2_systemOV2				= Error[2]; // send to PC software.
    CutChaCurt50.Bit.F0_Battery_Over_Voltage2	= Error[2];
    CutDCChaCurt0.Bit.F0_Battery_Over_Voltage21	= Error[2];
    CutACChaCurt0.Bit.F0_Battery_Over_Voltage21	= Error[2];
    
    //level 3 process
    if(Error[3] == 1){
        g_caution_Flag_1 |= 0x04;// 0000 0100
    }
    else
    {
//		if(stateCode == 30){
		if(g_BmsModeFlag == DISCHARGING){
            g_caution_Flag_1 &= 0xfb;//ffff 1011
        }
    }
    CutChaCurt0.Bit.F0_Battery_Over_Voltage1	= Error[3];
    CutDCChaCurt0.Bit.F0_Battery_Over_Voltage21	= Error[3];
    CutACChaCurt0.Bit.F0_Battery_Over_Voltage21	= Error[3];
}
//******************************************************************************
//* Function name:    errorSystemVoltageUV
//* Description:      电池包总电压欠压故障 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorSystemVoltageUV(void) //恢复,上报
{
    unsigned char i;
    unsigned char Error[4]={0};
    unsigned char Level=0; 
    ///////////////////上报故障等级数/////////////////////////
    
    Level = TotalVoltageUnderVoltage_custom(g_systemVoltage,g_highVoltageV3); 
    
    for(i=1;i<4;i++) 
       if(i==Level) 
           Error[i]=1;
       
    Error_Group4.Bit.F4_Bat_Under_V = Level;//整车CAN赋值
    g_bms_fault_msg.fault.Pack_V_Low_Flt = Level;
	
    //1级故障处理
    Can554Byte2.Bit.F0_systemUV1=Error[1]; //to PC
    
    //2级处理
    Can554Byte0.Bit.F0_systemUV2=Error[2];//to PC
    CutDisCurt50.Bit.F0_Battery_Under_Voltage2=Error[2];
    
    //3级处理 
    if(Error[3] == 1) 
    {
        g_caution_Flag_1 |= 0x01;
        status_group1.Bit.St_BMS = HV_Off_Status;		//BMS HV OFF
        g_bms_status.status.BMS_HV_Sts = HV_Off_Status;	//BMS HV OFF
    }
    CutDisCurt0.Bit.F0_Battery_Under_Voltage1 = Error[3];
}

//******************************************************************************
//* Function name:    errorDischargeOC
//* Description:      放电过流故障  一级
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorDischargeOC(void) //恢复;上报不处理 
{
    unsigned char Error[4]={0};
    unsigned char i;
    unsigned char Level=0; 
    float curtValue=0;

    curtValue = BiggestDischargeCurt;
    
    ////////////////////////上报故障等级////////////////////////
    Level=DisChargeOverCurrent_custom(g_systemCurrent,curtValue);  
    for(i=1;i<4;i++) 
        if(i==Level) 
            Error[i]=1;
     
    Error_Group3.Bit.F6_DisChg_Over_I = Level;//整车CAN赋值 
    g_bms_fault_msg.fault.DisChg_OverCurrent_Flt = Level;
	
//	//1级故障处理
	Can554Byte3.Bit.F0_DisChaOCurt1=Error[1];

//	//2级故障处理
	Can554Byte1.Bit.F0_DisChaOCurt2=Error[2];//to PC
//	CutDisCurt50.Bit.F1_DisCharge_Over_Current2=Error[2];

//	//3级故障处理
//	if(Error[3]) 
//    {
//        g_caution_Flag_2 |= 0x01;//to PC
//        //status_group2.Bit.BMS_PowerOff_Req = 2;//BMS高压下电请求
//    }

//	CutDisCurt0.Bit.F2_DisCharge_Over_Current1=Error[3];
}
//******************************************************************************
//* Function name:    errorChargeOC
//* Description:      充电过流故障和回馈过流故障同一模型 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorChargeOC(void)
{
    unsigned char Error[4]={0};
    unsigned char i;
    unsigned char Level=0; 
    float curtValue=0;
    
    if(g_BmsModeFlag == DISCHARGING)//放电模式
    {
        curtValue = BiggestFeedbackCurt; //回馈电流为负值
    }
    else if((g_BmsModeFlag == FASTRECHARGING)||(g_BmsModeFlag == RECHARGING)) //快充模式
    {
        curtValue = m_askcurrent;
    }
    ///////////////////上报故障等级数/////////////////////////    
    Level=ChargeOverCurrent_custom((-g_systemCurrent),curtValue);
    for(i=1;i<4;i++) 
        if(i==Level) 
            Error[i]=1;
    
    if(g_BmsModeFlag == DISCHARGING){
        Error_Group5.Bit.F0_FeedB_Over_I = Level;//整车CAN赋值,瞬时功率
        g_bms_fault_msg.fault.FeedBack_OverCurrentFlt = Level;
    }
    else
    {
        Error_Group1.Bit.F4_Ch_Over_I = Level;//整车CAN赋值,充电功率
        g_bms_fault_msg.fault.Chg_OverCurrent_Flt = Level;
    }
	
    if(Level>=1){
        Error_Group6.Bit.F5_Chg_C_Over = 1;//整车CAN赋值,充电电流超限报警
        g_bms_fault_msg.fault.Chg_OverCurrent_Alarm = 1;
    }
    else{
        Error_Group6.Bit.F5_Chg_C_Over = 0;//整车CAN赋值,充电电流超限报警
        g_bms_fault_msg.fault.Chg_OverCurrent_Alarm = 0;
    }
	
//	//1级故障处理
	Can554Byte2.Bit.F7_ChangerOCurt1=Error[1];//to PC
    
//	//2级故障处理
	Can554Byte0.Bit.F7_ChangerOCurt2=Error[2];//to PC
    
//	//3级故障处理
//	if(Error[3])
//	{
//		g_caution_Flag_1 |=0x80;//to PC
//		if(g_BmsModeFlag == DISCHARGING){
//			status_group2.Bit.BMS_PowerOff_Req = 2;//BMS高压下电请求
//		}
//	 }

//	CutChaCurt0.Bit.F2_Charge_Over_Current1=Error[3];
//	CutDCChaCurt0.Bit.F3_Charge_Over_Current1=Error[3];
//	CutACChaCurt0.Bit.F3_Charge_Over_Current1=Error[3];
}

//******************************************************************************
//* Function name:    errorCellVoltageOV
//* Description:      单体过压故障,1级故障不恢复,2,3,4级故障可恢复,直流除外,若直流上报2级故障,可以到1也可以到3,如果1级直接不恢复  
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorCellVoltageOV(void)
{
    unsigned char Error[4]={0};
    unsigned char i;
    unsigned char Level=0;
	
    //上报故障等级等级数 
    Level = CellOverVoltage_custom(g_highestCellVoltage,g_BmsModeFlag);      
    for(i=1;i<4;i++){
       if(i == Level){
           Error[i] = 1;
       }
    }
    
    Error_Group2.Bit.F0_Cell_Over_V = Level;//will be send to vehicle CAN
    g_bms_fault_msg.fault.Cell_V_High_Flt = Level;
	
    //level 1 process
    Can554Byte2.Bit.F3_cellOV1					= Error[1];
//	CutChaCurt70.Bit.F2_Cell_Over_Voltage3		= Error[1];
	CutACChaCurt0.Bit.F4_Cell_Over_Voltage321	= Error[1];
	CutDCChaCurt0.Bit.F4_Cell_Over_Voltage321	= Error[1];
	
	//level 2 process
	Can554Byte0.Bit.F3_cellOV2					= Error[2];//to PC
	CutChaCurt50.Bit.F2_Cell_Over_Voltage2		= Error[2];
	CutDCChaCurt0.Bit.F4_Cell_Over_Voltage321	= Error[2];
	CutACChaCurt0.Bit.F4_Cell_Over_Voltage321	= Error[2];
	
	//level 3 process
	if(Error[3])
	{
	    g_caution_Flag_1 |= 0x08;//to PC
	    if(g_BmsModeFlag == DISCHARGING){
	        status_group1.Bit.St_BMS = HV_Off_Status;//BMS staus is HV OFF
	        g_bms_status.status.BMS_HV_Sts = HV_Off_Status;
	    }
	}
	CutDisCurt0.Bit.F10_Cell_Over_Voltage1		= Error[3];
	CutChaCurt0.Bit.F3_Cell_Over_Voltage1		= Error[3];
	CutACChaCurt0.Bit.F4_Cell_Over_Voltage321	= Error[3];
	CutDCChaCurt0.Bit.F4_Cell_Over_Voltage321	= Error[3];
}
//******************************************************************************
//* Function name:   errorCellVoltageUV
//* Description:     单体电压欠压故障  
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorCellVoltageUV(void)//上报不处理,充电不上报,恢复
{
    unsigned char i;
    unsigned char Error[4]={0};
    unsigned char Level=0; 
	
    Level=CellUnderVoltage_custom(g_lowestCellVoltage);
    for(i=1;i<4;i++){
        if(i==Level){
            Error[i]=1;
        }
    }
	
    Error_Group2.Bit.F2_Cell_Under_V = Level;//整车CAN赋值
    g_bms_fault_msg.fault.Cell_V_Low_Flt = Level;
	
    //1级故障处理
    Can554Byte2.Bit.F1_cellUV1=Error[1];//to PC
//	CutDisCurt70.Bit.F2_Cell_Under_Voltage3=Error[1];
	
    //2级故障处理
	Can554Byte0.Bit.F1_cellUV2=Error[2];//to PC
	CutDisCurt50.Bit.F2_Cell_Under_Voltage2=Error[2];
	 
	//3级故障处理
	if(Error[3] == 1)
	{
		g_caution_Flag_1 |= 0x02;//to PC
		status_group1.Bit.St_BMS = HV_Off_Status;//BMS status is HV OFF
		g_bms_status.status.BMS_HV_Sts = HV_Off_Status;
	}
	CutDisCurt0.Bit.F3_Cell_Under_Voltage1 = Error[3];
	CutChaCurt0.Bit.F10_Cell_Under_Voltage1 = Error[3];
}

//******************************************************************************
//* Function name:    errorCurrSensor
//* Description:      电流传感器故障 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorCurrSensorIniatial(void) //上电前检测2次
{
    unsigned char i;
    unsigned char Error[4]={0};
    unsigned char Level=0; 

    Level=CurrentSensorFault_custom(g_systemCurrent);
    for(i=1;i<4;i++)
        if(i==Level)
            Error[i]=1;
        
    if(Error[1] == 1){
        g_caution_Flag_3 |=0x02; //to PC      //电流传感器故障
	}
	
    //hardware_error2.Bit.F7_I_Ga_Err = 1;
//	if(g_BmsModeFlag == DISCHARGING) 
//	{
//	    CutDisCurt0.Bit.F4_I_Sener_Err = 1;
//	    CutChaCurt0.Bit.F4_I_Sener_Err = 1;
//	    status_group2.Bit.BMS_PowerOff_Req = 2;//BMS高压下电请求 
//	}
//	else if(g_BmsModeFlag == FASTRECHARGING)
//	    CutDCChaCurt0.Bit.F5_I_Sener_Err =1;
//	else if(g_BmsModeFlag == RECHARGING)
//	    CutACChaCurt0.Bit.F5_I_Sener_Err =1;
//	           
//	}   
}

//******************************************************************************
//* Function name:    errorCurrSensor
//* Description:      温度传感器故障 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************

//******************************************************************************
//* Function name:    errorCellUnbalance
//* Description:    单体电压不均衡故障 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorCellUnbalance(void)//
{
	unsigned char Error[4]={0};
	unsigned char i;
	unsigned char Level=0;

	//上报故障等级     
	Level=CellVolUnbalance_custom(g_highestCellVoltage,g_lowestCellVoltage);
	for(i=1;i<4;i++){
       if(i==Level){
           Error[i]=1;
       }
	}
	   
	Error_Group5.Bit.F4_Cell_Dif_V = Level;//整车CAN赋值 
	g_bms_fault_msg.fault.Cell_V_Diff_Flt = Level;
	
	//2级故障处理
	Can554Byte1.Bit.F2_CellUnbalance2		= Error[2];//to PC
	CutDisCurt50.Bit.F3_CellUnbalance2		= Error[2];
	CutChaCurt50.Bit.F6_CellUnbalance2		= Error[2];
	CutDCChaCurt50.Bit.F6_CellUnbalance2	= Error[2];
	CutACChaCurt50.Bit.F5_CellUnbalance2	= Error[2];
}

//******************************************************************************
//* Function name:    errorTemUnbalance
//* Description:    单体温度不均衡故障 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorTemUnbalance(void)//
{
	unsigned char Error[4]={0};
	unsigned char i;
	unsigned char Level;
	//float Tmp_H,Tmp_L;
	//Tmp_H=(float)g_highestTemperature;
	//Tmp_L=(float)g_lowestTemperature;

    //上报故障等级
    Level = CellTempUnbalance_custom(g_highestTemperature,g_lowestTemperature);
	
    for(i=1;i<4;i++){
       if(i==Level){
           Error[i]=1;
       }
    }
	
    Error_Group5.Bit.F2_Cell_Dif_T = Level;//整车CAN赋值 
	g_bms_fault_msg.fault.Cell_T_Diff_Flt = Level;
	
	//1级故障处理
	Can554Byte3.Bit.F3_tempUnbalance1=Error[1];//to PC

	//2级故障处理
	Can554Byte1.Bit.F3_tempUnbalance2		= Error[2];//to PC
	CutDisCurt50.Bit.F4_tempUnbalance2		= Error[2];
	CutChaCurt50.Bit.F3_tempUnbalance2		= Error[2];
	CutDCChaCurt50.Bit.F1_tempUnbalance2	= Error[2];
	CutACChaCurt50.Bit.F1_tempUnbalance2	= Error[2];
}

//******************************************************************************
//* Function name:   errorCellTemperatureUT
//* Description:     单体温度过低故障 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorCellTemperatureUT(void)//
{
	unsigned char i;
	unsigned char Error[4]={0}; 
	unsigned char Level=0;
	//float t;
	//t= (float)g_lowestTemperature;

	//上报故障等级
	Level=BatteryTemperatureLow_custom(g_lowestTemperature);
	for(i=1;i<4;i++){
       if(i==Level){
           Error[i]=1;
       }
    }
    
	Error_Group5.Bit.F6_Cell_Under_T=Level;//整车CAN赋值
	g_bms_fault_msg.fault.Cell_T_Low_Flt = Level;
	
	//1级故障处理
	Can554Byte2.Bit.F6_cellUT1=Error[1];

	//2级故障处理
	Can554Byte0.Bit.F6_cellUT2=Error[2];
    
	 //3级故障处理
	if(Error[3] == 1) 
	{
		g_caution_Flag_1 |= 0x40;//to PC
		if(g_BmsModeFlag == DISCHARGING){
			status_group1.Bit.St_BMS = HV_Off_Status;//BMS状态高压断开
			g_bms_status.status.BMS_HV_Sts = HV_Off_Status; // HV OFF
		}
	}
	CutDisCurt0.Bit.F6_Under_Temp1		= Error[3];
	CutChaCurt0.Bit.F6_Under_Temp1		= Error[3];
	CutDCChaCurt0.Bit.F7_Under_Temp1	= Error[3];
	CutACChaCurt0.Bit.F7_Under_Temp1	= Error[3];
}

//******************************************************************************
//* Function name:    errorCellTemperatureOT
//* Description:      单体温度过高故障  一级
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorCellTemperatureOT(void)//
{
	unsigned char i;
	unsigned char Error[4]={0}; 
	unsigned char Level=0; 
	//float t;
	//t= (float)g_highestTemperature;

	//上报故障等级
	Level=BatteryTemperatureHigh_custom(g_highestTemperature);

	for(i=1;i<4;i++){
       if(i==Level){
           Error[i]=1;
       }
    }
    
	Error_Group2.Bit.F4_Temp_Over = Level;//整车CAN赋值
	g_bms_fault_msg.fault.Cell_T_High_Flt = Level;
	
	//1级故障处理
	Can554Byte2.Bit.F5_cellOT1=Error[1];
//	CutDisCurt70.Bit.F4_Over_Temp3=Error[1];
//	CutChaCurt70.Bit.F4_Over_Temp3=Error[1];
//	CutDCChaCurt70.Bit.F3_Over_Temp3=Error[1];
//	CutACChaCurt70.Bit.F3_Over_Temp3=Error[1];
	
	//2级故障处理
	Can554Byte0.Bit.F5_cellOT2=Error[2];//to PC
	CutDisCurt50.Bit.F5_Over_Temp2=Error[2];
	CutChaCurt50.Bit.F4_Over_Temp2=Error[2];
	CutDCChaCurt50.Bit.F2_Over_Temp2=Error[2];
	CutACChaCurt50.Bit.F2_Over_Temp2=Error[2];
    
    //3级故障处理
    if(Error[3])
    {  
        g_caution_Flag_1 |= 0x20;//to PC
        if(g_BmsModeFlag == DISCHARGING)
            status_group1.Bit.St_BMS = HV_Off_Status;
            g_bms_status.status.BMS_HV_Sts = HV_Off_Status;
    }
    CutDisCurt0.Bit.F5_Over_Temp1=Error[3];
    CutChaCurt0.Bit.F5_Over_Temp1=Error[3];
    CutDCChaCurt0.Bit.F6_Over_Temp1=Error[3];
    CutACChaCurt0.Bit.F6_Over_Temp1=Error[3];
}

//******************************************************************************
//* Function name:    errorSOCLow
//* Description:      SOC低故障 一级
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorSOCLow(void)
{
	unsigned char i;
	unsigned char Error[4]={0}; 
	unsigned char Level=0;
	//float t;

	//上报故障等级
	Level=socLow_custom(Can_g_socValue);
	for(i=1;i<4;i++) 
       if(i==Level) 
           Error[i]=1;
       
	Error_Group4.Bit.F0_SOC_Low=Level;//整车CAN赋值 
	g_bms_fault_msg.fault.SOC_Low_Flt = Level;
	
	//1级故障处理
	Can554Byte3.Bit.F1_SOCLow1=Error[1];

	//2级故障处理
	Can554Byte1.Bit.F1_SOCLow2=Error[2];
}

//******************************************************************************
//* Function name:    errorLowIsolation
//* Description:      绝缘电阻过低故障 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void errorLowIsolation(void) 
{
	unsigned char i;
	unsigned char Error[4]={0};
	unsigned char Level=0; 
	float LowInsolation;
	
	if(Rn_Vpn_Value <= Rp_Vpn_Value)
        LowInsolation = Rn_Vpn_Value;
    else
        LowInsolation = Rp_Vpn_Value;
    
	Level=IsolationLow_custom(LowInsolation);
	for(i=1;i<4;i++)
      if(i==Level)
        Error[i]=1;
      
    Error_Group1.Bit.F6_Ins_Err = Level;//整车CAN赋值
	g_bms_fault_msg.fault.Ins_Low_flt = Level;  
	
    if(Level>=1){
        Error_Group6.Bit.F7_Chg_Ins_Low = 1;//充电绝缘过低报警
		g_bms_fault_msg.fault.Chg_Ins_Low_Alarm = 1;
    }
	else{
        Error_Group6.Bit.F7_Chg_Ins_Low = 0;
		g_bms_fault_msg.fault.Chg_Ins_Low_Alarm = 0;
	}
	
    //1级故障处理
    Can554Byte2.Bit.F4_insulationLow1=Error[1];//to PC
//	CutDCChaCurt70.Bit.F4_Low_Isolation3=Error[1]; //没有70降了，只上报不处理 
//	CutACChaCurt70.Bit.F4_Low_Isolation3=Error[1];
	
//	CutACChaCurt0.Bit.F8_Low_Isolation1=Error[2];//慢充不检测
    
    //2级故障处理
    Can554Byte0.Bit.F4_insulationLow2=Error[2];//to PC
    CutDCChaCurt50.Bit.F3_Low_Isolation2=Error[2];
//	CutACChaCurt50.Bit.F3_Low_Isolation2=Error[2];
	
    //3级故障处理
    if(Error[3])
        g_caution_Flag_1 |= 0x10;//to PC
	CutDCChaCurt0.Bit.F8_Low_Isolation1=Error[3];
}

//******************************************************************************
//* Function name:    DCChangerComError
//* Description:      与直流充电机通信故障（包括超时故障）
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void DCChangerComError(void)
{
	if(OverTimeState==1)
	{
		CutDCChaCurt0.Bit.F1_Communication_With_Charger=1;//故障动作
		g_caution_Flag_2 |=0x80; //for 内部CAN
		Error_Group3.Bit.F1_V_CAN_Err =1; //整车CAN
		g_bms_fault_msg.fault.ExternalCAN_Com_Flt = 1;
	}
}
//******************************************************************************
//* Function name:    ACChangerComError
//* Description:      与受电弓充电机通信故障（包括超时故障）
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void ACChangerComError(void)
{
    ACCOverTime++;
    if(ACCOverTime >= 30)//30s没有接收到充电机报文
    {
        CutACChaCurt0.Bit.F1_Communication_With_Charger=1;
        g_caution_Flag_2 |=0x10; //for 内部CAN
        Error_Group3.Bit.F1_V_CAN_Err =1; //整车CAN
        fastend3 |= (1<<6);
		g_bms_fault_msg.fault.ExternalCAN_Com_Flt = 1;
    }
}
//******************************************************************************
//* Function name:    VCUComError
//* Description:      与整车通信故障
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void VCUComError(void)
{
	VCUOverTime++;
	if(g_BmsModeFlag == RECHARGING){
		VCU_ParkBrakeOverTime++;
		VCUOverTime = 0;
	}
	
	if((VCUOverTime >= 30)
		||((VCU_ParkBrakeOverTime >= 30) && (g_BmsModeFlag == RECHARGING)))//30s没有接收到充电机报文
	{
		CutDisCurt0.Bit.F7_VCU_Communiction=1;
		CutChaCurt0.Bit.F7_VCU_Communiction=1;
		//g_caution_Flag_2 |=0x10; //for 内部CAN
		Error_Group3.Bit.F1_V_CAN_Err = 1; //整车CAN
		status_group1.Bit.St_BMS = HV_Off_Status;//BMS状态高压断开
		if(g_BmsModeFlag == RECHARGING){
			fastend3 |= (1<<6); // other fault.
		}
		g_bms_fault_msg.fault.ExternalCAN_Com_Flt = 1;
		g_bms_status.status.BMS_HV_Sts = HV_Off_Status;
	}
}
//******************************************************************************
//* Function name:    innerCommOT3
//* Description:      内部通讯故障  三级
//* EntryParameter : None
//* ReturnValue    : Bool类型 0-无；1-有
//******************************************************************************
void innerCommOT3(void) 
{
	U8 cnt = 0;
	U8 BMU_overTime_flag_t = 0;
	
    SBMSOverTime++;
	
	for(cnt = 0; cnt < BMU_NUMBER; cnt++){
		BMU_OverTime[cnt]++;
		if(BMU_OverTime[cnt] >= 30){
			BMU_overTime_flag_t = 1;
		}
	}
	
    if(((g_caution_Flag_3 & 0x01) != 0)
		||(SBMSOverTime >= 30)
		||(BMU_overTime_flag_t == 1)) //BMU内部通讯故障或与SBMS故障
    {
        status_group1.Bit.St_BMS =2;//BMS状态高压断开
        CutDisCurt0.Bit.F1_Inner_Communiction=1;
        CutChaCurt0.Bit.F1_Inner_Communiction=1;
        CutDCChaCurt0.Bit.F2_Inner_Communiction=1;
        CutACChaCurt0.Bit.F2_Inner_Communiction=1;
        
        Error_Group3.Bit.F0_Sub_Com_Err = 1;//整车CAN赋值 
        g_bms_fault_msg.fault.InnerCAN_Com_Flt = 1;
    } 
}

//******************************************************************************
//* Function name:    Charge_Check
//* Description:      电流正负检测 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void Charge_Check(void) 
{
	static unsigned char Check_Num=0;
	
	if(((g_BmsModeFlag == FASTRECHARGING)||(g_BmsModeFlag == RECHARGING))
		&&((g_systemCurrent > 2) && g_bms_msg.CellVoltageMin <= 25000)) 
	{
		Check_Num++;
		if(Check_Num>=100) 
		{
			ACCha_Flag_BST=1;
			CutDCChaCurt0.Bit.F9_Charge_Count1=1;
			CutACChaCurt0.Bit.F9_Charge_Count1=1;
			Can554Byte3.Bit.F4_ChargeCurDirError = 1;
			if(Check_Num>=250) //如果发生了100次，该算法要求必须下电。
				Check_Num=101;
        }
    }
}

//******************************************************************************
//* Function name:    CHG_SocketOT
//* Description:      充电插座过温 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void CHG_SocketOT(void) 
{
    unsigned char i;
    unsigned char Error[4]={0}; 
    unsigned char Level=0;
    float tmax = 0;
    
    if(DCTem1 >= DCTem2)
        tmax = DCTem1 + 40;
    else
        tmax = DCTem2 + 40;
    
    //上报故障等级
    if(tmax >= 0){ //必须大于0
        Level = ChargeSocketOverTemp_custom((unsigned char)tmax);
    }
	else{ 
        Level = 0;
	}
	
    for(i=1;i<4;i++) 
       if(i == Level) 
           Error[i] = 1;

	if(Error_Group0.Bit.F2_Ele_Relay_Con <= Level){
	    Error_Group0.Bit.F2_Ele_Relay_Con = Level;//整车CAN赋值     
		g_bms_fault_msg.fault.KEleBand_P_Adhesion_Flt = Level;
		
	    ///////2级故障处理
	    CutDCChaCurt50.Bit.F5_CHG_Socket2 = Error[2];
	    
	    /////3级故障处理 
	    CutDCChaCurt0.Bit.F12_CHG_Socket1 = Error[3];
	}
}
//******************************************************************************
//* Function name:    Fire_Warning
//* Description:      火灾预警 
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void Fire_Warning(void)
{
    if((Error_Group0.Bit.F0_Fire_Warning==1)
		||(Error_Group0.Bit.F0_Fire_Warning==2)) 
    {
        CutDisCurt50.Bit.F6_Fire_Warning2=1;
        CutChaCurt50.Bit.F5_Fire_Warning2=1;
        CutDCChaCurt50.Bit.F4_Fire_Warning2=1;
        CutACChaCurt50.Bit.F4_Fire_Warning2=1;
    } 
    else if(Error_Group0.Bit.F0_Fire_Warning==3) 
    {   
        CutDisCurt0.Bit.F8_Fire_Warning1=1;
        CutChaCurt0.Bit.F8_Fire_Warning1=1;
        CutDCChaCurt0.Bit.F10_Fire_Warning1=1;
        CutACChaCurt0.Bit.F10_Fire_Warning1=1;
        if(g_BmsModeFlag == DISCHARGING){
            status_group1.Bit.St_BMS = HV_Off_Status;//BMS状态高压断开
            g_bms_status.status.BMS_HV_Sts = HV_Off_Status;
        }
    }
}

//******************************************************************************
//* Function name:    PowerSupplyError
//* Description:      供电电源异常
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void PowerSupplyError(void)//
{
    unsigned char i;
    unsigned char Error[4]={0}; 
    unsigned char Level=0;

    //send the fault level
	if(g_BmsModeFlag == FASTRECHARGING)
	{
		if(g_BST_send_ok != 1) // if not send BST, then detect the fault.
		{
			Level = Supply24V_custom(PowerVOL);
		}
	}
	else
	{
		Level = Supply24V_custom(PowerVOL);
	}
	
    for(i=1;i<4;i++) 
       if(i == Level) 
           Error[i] = 1;
    
    //1级故障处理 上报故障  
    if(Error[1]) 
    {
		g_bms_fault_msg.fault.Bms_Power_Supply_Alarm = 1;
        Error_Group6.Bit.F0_Power_Vol=1;//整车CAN上报
        /*CutDisCurt0.Bit.F9_Supply_Power1=1;
        CutChaCurt0.Bit.F9_Supply_Power1=1;
        CutDCChaCurt0.Bit.F11_Supply_Power1=1;
        CutACChaCurt0.Bit.F11_Supply_Power1=1;
        */
    } 
}

void Pack_branch_Disconnect_Fault(void){
	byte level = 0;

	level = PackFault_custom(g_SBMS_current1, g_SBMS_current2, g_systemCurrent);

	if(level != 0){
		switch(stateCode){
			case 30:
			{
				CutDisCurt50.Bit.F6_Fire_Warning2=1;
				CutChaCurt50.Bit.F5_Fire_Warning2=1;
			}
			break;
			case 170:
			{
				CutDisCurt0.Bit.F8_Fire_Warning1=1;
				CutChaCurt0.Bit.F8_Fire_Warning1=1;
				CutDCChaCurt0.Bit.F10_Fire_Warning1=1;
				CutACChaCurt0.Bit.F10_Fire_Warning1=1;
				OffState = 1;
			}
			break;
			case 110:
			{
				CutDisCurt0.Bit.F8_Fire_Warning1=1;
				CutChaCurt0.Bit.F8_Fire_Warning1=1;
				CutDCChaCurt0.Bit.F10_Fire_Warning1=1;
				CutACChaCurt0.Bit.F10_Fire_Warning1=1;
				PantographOff = 1;
			}
			break;
			default:
			break;
		}
		g_bms_fault_msg.fault.HVBranch_CircuitOff_Flt = level;
	}
}

//**********************************************************************
//* Function name:   CarFaultDone
//* Description:     行车过程中故障的处理
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void CarFaultDone()
{
    //////////////////////////////行车发送高压下电请求/////////////////////
    
    if(g_BmsModeFlag == DISCHARGING) //行车发送高压下电请求
    {
        if((Error_Group4.Bit.F4_Bat_Under_V ==3)	//总电压过压3级
//		||(Error_Group3.Bit.F6_DisChg_Over_I == 3)	//放电过流3级
//		||(Error_Group5.Bit.F0_FeedB_Over_I == 3)	//回馈过流3级
		||(Error_Group2.Bit.F0_Cell_Over_V==3)		//单体电压过压3级
		||(Error_Group2.Bit.F2_Cell_Under_V == 3)	//单体电压欠压3级
		||(Error_Group5.Bit.F6_Cell_Under_T == 3)	//单体温度过低3级
		||(Error_Group2.Bit.F4_Temp_Over == 3)		//单体温度过高3级
		||(Error_Group3.Bit.F1_V_CAN_Err)			//外网通讯故障（与VCU
		||(Error_Group3.Bit.F0_Sub_Com_Err)			//内网通讯故障
		||(Error_Group0.Bit.F0_Fire_Warning==3)		//火灾预警3级
//		||(Error_Group6.Bit.F0_Power_Vol)			//整车CAN上报
		){
			HighVolPowerOff=1;
			Error_Group1.Bit.St_DisCHG_Allow = 1;//放电允许状态位不允许
			g_bms_fault_msg.fault.DisChg_Allow_State = 1; // not allowed
       }
    }
    //////////////////////////////快充发送高压下电请求////////////////////
    else if(g_BmsModeFlag == FASTRECHARGING)      
    {      
        if((Error_Group4.Bit.F6_Bat_Over_V>=2)		//总电压过压2级、3级
//		||(Error_Group1.Bit.F4_Ch_Over_I == 3)		//充电过流3级
		||(Error_Group2.Bit.F0_Cell_Over_V>=1)		//单体电压过压1,2,3级
		||(Error_Group5.Bit.F6_Cell_Under_T == 3)	//单体温度过低3级
		||(Error_Group2.Bit.F4_Temp_Over == 3)		//单体温度过高3级
		||(Error_Group1.Bit.F6_Ins_Err == 3)		//绝缘低
		||(Error_Group3.Bit.F1_V_CAN_Err)			//外网通讯故障（与直流充电机通讯故障?
		||(Error_Group3.Bit.F0_Sub_Com_Err)			//内网通讯故障
		||(ACCha_Flag_BST == 1)						//电流方向异常故障
		||(Error_Group0.Bit.F0_Fire_Warning==3)		//火灾预警3级
//		||(Error_Group6.Bit.F0_Power_Vol)			//整车CAN上报
		||(Error_Group0.Bit.F2_Ele_Relay_Con ==3)	//充电插座过温
        )
        {
            OffState=1;//快充请求下电
            Error_Group1.Bit.St_CHG_Allow = 1; //充电允许状态位不允许
            g_bms_fault_msg.fault.Chg_Allow_State = 1;
        }
    }
    //////////////////////////////受电弓充电发送高压下电请求///////////////
    else if(g_BmsModeFlag == RECHARGING)      
    {      
        if((Error_Group4.Bit.F6_Bat_Over_V>=2)		//总电压过压2级、3级
//		||(Error_Group1.Bit.F4_Ch_Over_I == 3)		//充电过流3级
		||(Error_Group2.Bit.F0_Cell_Over_V >= 1)		//单体电压过压1,2,3级
		||(Error_Group5.Bit.F6_Cell_Under_T == 3)	//单体温度过低3级
		||(Error_Group2.Bit.F4_Temp_Over == 3)		//单体温度过高3级
		||(Error_Group3.Bit.F1_V_CAN_Err)			//外网通讯故障（与受电弓通讯故障?
		||(Error_Group3.Bit.F0_Sub_Com_Err)			//内网通讯故障
		||(ACCha_Flag_BST == 1)						//电流方向异常故障
		||(Error_Group0.Bit.F0_Fire_Warning==3)		//火灾预警3级
//		||(Error_Group6.Bit.F0_Power_Vol)			//整车CAN上报
		||(Error_Group0.Bit.F2_Ele_Relay_Con ==3)	//充电插座过温
		||(acc_Connect == 0) // ON signal disapper
        )
        {
            PantographOff=1;//受电弓请求下电
            Error_Group1.Bit.St_CHG_Allow = 1; //充电允许状态位不允许
            g_bms_fault_msg.fault.Chg_Allow_State = 1;
        }
    }
}
//******************************************************************************
//* Function name:   BMSProtect
//* Description:     BMS最后的保护,不受状态机控制，强制断高压
//* EntryParameter : None
//* ReturnValue    : Bool类型 0-无；1-有
//******************************************************************************
void BMSProtect(void)//有风险，如果OffState判断失败,最好用实际电压比较********** 
{
    static unsigned char LCDelaytime=0;
    static unsigned char FastChgHCDelaytime=0;
	static unsigned char EleBandChgHCDelaytime=0;
    static unsigned char HTDelaytime=0;
    static unsigned char HBaDelaytime=0;
	static U16 DisChg_cnt_t = 0;
	static U16 FastChg_cnt_t = 0;
	static U16 EleBandChg_cnt_t = 0;
	static U16 HT_cnt_t = 0;
	
    if(g_BmsModeFlag == DISCHARGING)
    {
        if((g_lowestCellVoltage<=LOWEST_CELL_VOL)&&(g_lowestCellVoltage!=0))
        {
            LCDelaytime++;
            if(LCDelaytime>10)
            {
                LCDelaytime = 10;
				Error_Group6.Bit.F3_BMS_Protect = 1;
				g_bms_fault_msg.fault.BMS_Self_Protect = 1;
				DisChg_cnt_t++;
				if(DisChg_cnt_t >= 30){
					DisChg_cnt_t = 30;
					Kp_Switch(OFF);
					Kn_Switch(OFF);
//					TurnOffAllRelay();
				}
            }
        } 
        else
        {
            LCDelaytime=0;
			DisChg_cnt_t = 0;
        }
    }
	else
	{
		LCDelaytime=0;
		DisChg_cnt_t = 0;
	}
	
	if(g_BmsModeFlag == FASTRECHARGING){
		if((g_highestCellVoltage >= HIGHEST_CELL_VOL)
			|| (g_systemVoltage >= HIGHEST_BATT_VOL)
			|| (g_highVoltageV4 >= HIGHEST_BATT_VOL)){
			FastChgHCDelaytime++;
			if(FastChgHCDelaytime >= 10){
				FastChgHCDelaytime = 10;
				Error_Group6.Bit.F3_BMS_Protect = 1;
				g_bms_fault_msg.fault.BMS_Self_Protect = 1; // the same as above.
				FastChg_cnt_t++;
				if(FastChg_cnt_t >= 30){
					FastChg_cnt_t = 30;
//					TurnOffAllRelay();
//					KChg_N_Switch(OFF);
					KFastChg_P_Switch(OFF);
					Kp_Switch(OFF);
					Kn_Switch(OFF);
				}
			}
		}
		else{
			FastChg_cnt_t = 0;
			FastChgHCDelaytime = 0;
		}
	}
	else{
		FastChg_cnt_t = 0;
		FastChgHCDelaytime = 0;
	}

	if(g_BmsModeFlag == RECHARGING){
		if(g_highestCellVoltage >= HIGHEST_CELL_VOL
			|| (g_systemVoltage >= HIGHEST_BATT_VOL)
			|| (g_highVoltageV5 >= HIGHEST_BATT_VOL)
			|| (g_highVoltageV6 >= HIGHEST_BATT_VOL)){
			EleBandChgHCDelaytime++;
			if(EleBandChgHCDelaytime >= 10){
				EleBandChgHCDelaytime = 10;
				Error_Group6.Bit.F3_BMS_Protect = 1;
				g_bms_fault_msg.fault.BMS_Self_Protect = 1; // the same as above.
				EleBandChg_cnt_t++;
				if(EleBandChg_cnt_t >= 30){
					EleBandChg_cnt_t = 30;
//					TurnOffAllRelay();
//					KChg_N_Switch(OFF);
					KEleBand_P_Switch(OFF);
					Kp_Switch(OFF);
					Kn_Switch(OFF);
				}
			}
		}
		else{
			EleBandChg_cnt_t = 0;
			EleBandChgHCDelaytime = 0;
		}
	}
	else{
		EleBandChg_cnt_t = 0;
		EleBandChgHCDelaytime = 0;
	}
	
    if(g_highestTemperature >= (HIGHEST_TEM + 40) )//10s
    {
        HTDelaytime++;
        if(HTDelaytime>=10)
        {
            HTDelaytime=10;
			Error_Group6.Bit.F3_BMS_Protect = 1;
			g_bms_fault_msg.fault.BMS_Self_Protect = 1; // the same as above.
			
			HT_cnt_t++;
			if(HT_cnt_t >= 30){
				HT_cnt_t = 30;
				TurnOffAllRelay();
			}
        }
    }
    else
    {
        HTDelaytime=0;
		HT_cnt_t = 0;
    }
}
//******************************************************************************
//* Function name:   FaultLevel
//* Description:     故障等级处理
//* EntryParameter : None
//* ReturnValue    : 有无故障：0-无；1-有
//******************************************************************************
void FaultLevel(void)
{
    if((Error_Group4.Bit.F6_Bat_Over_V == 3)  //总电压过压3级
    ||(Error_Group4.Bit.F4_Bat_Under_V == 3)  //总电压欠压3级
    //||(Error_Group3.Bit.F6_DisChg_Over_I == 3) //放电过流3级
    //||(Error_Group5.Bit.F0_FeedB_Over_I == 3)   //回馈过流3级
    ||(Error_Group1.Bit.F4_Ch_Over_I == 3)      //充电过流3级
    ||(Error_Group2.Bit.F0_Cell_Over_V == 3)    //单体电压过压3级
    ||(Error_Group2.Bit.F2_Cell_Under_V == 3)   //单体电压欠压3级
    ||(Error_Group5.Bit.F6_Cell_Under_T == 3)  //单体温度过低3级
    ||(Error_Group2.Bit.F4_Temp_Over == 3)     //单体温度过高3级
    ||(Error_Group1.Bit.F6_Ins_Err == 3)       //绝缘低
    ||(Error_Group0.Bit.F0_Fire_Warning==3)       //火灾预警3级
    ||(Error_Group3.Bit.F1_V_CAN_Err)//外网通讯故障（与直流充电机、与受电弓、VCU)
    ||(Error_Group3.Bit.F0_Sub_Com_Err)//内网通讯故障
    //||(Error_Group6.Bit.F0_Power_Vol)//整车CAN上报
    ||(Error_Group0.Bit.F2_Ele_Relay_Con ==3)//充电插座过温
    ||(ACCha_Flag_BST) //充电电流方向异常
    ||(RelayErrorPowerOff)//继电器下电故障
    ||(HV_Lock_Error_state() == 1)
    )
    {
        status_group3.Bit.Fault_Level = 3;//严重故障，降功率为0
        status_group4.Bit.St_BMS_System = 1;//BMS系统状态位 故障 只有出现3级故障上报
    } 
    else if((Error_Group4.Bit.F6_Bat_Over_V == 2)//总电压过压2级
    ||(Error_Group4.Bit.F4_Bat_Under_V == 2)     //总电压欠压2级
    ||(Error_Group3.Bit.F6_DisChg_Over_I == 2)   //放电过流2级
    ||(Error_Group5.Bit.F0_FeedB_Over_I == 2)    //回馈过流2级
    ||(Error_Group1.Bit.F4_Ch_Over_I == 2)       //充电过流2级
    ||(Error_Group2.Bit.F0_Cell_Over_V == 2)     //单体电压过压2级
    ||(Error_Group2.Bit.F2_Cell_Under_V == 2)    //单体电压欠压2级
    ||(Error_Group5.Bit.F4_Cell_Dif_V == 2)      //单体电压不均衡2级
    ||(Error_Group5.Bit.F2_Cell_Dif_T == 2)      //单体温度不均衡2级
    ||(Error_Group5.Bit.F6_Cell_Under_T == 2)    //单体温度过低2级
    ||(Error_Group2.Bit.F4_Temp_Over == 2)       //单体温度过高2级
    ||(Error_Group4.Bit.F0_SOC_Low == 2)         //SOC低2级
    ||(Error_Group1.Bit.F6_Ins_Err == 2)        //绝缘低
    ||(Error_Group0.Bit.F0_Fire_Warning==2)       //火灾预警2级
    //||(Error_Group6.Bit.F0_Power_Vol)//整车CAN上报
    ||(Error_Group0.Bit.F2_Ele_Relay_Con ==2)//充电插座过温
    ||(g_bms_fault_msg.fault.HVBranch_CircuitOff_Flt == 2)
    )
    {
        status_group3.Bit.Fault_Level = 2;//轻微，降功率至50%
    } 
    else if((Error_Group4.Bit.F6_Bat_Over_V) //总电压过压1级
    ||(Error_Group4.Bit.F4_Bat_Under_V)      //总电压欠压1级
    ||(Error_Group3.Bit.F6_DisChg_Over_I)    //放电过流1级
    ||(Error_Group5.Bit.F0_FeedB_Over_I)     //回馈过流1级
    ||(Error_Group1.Bit.F4_Ch_Over_I)        //充电过流1级
    ||(Error_Group2.Bit.F0_Cell_Over_V)      //单体电压过压1级
    ||(Error_Group2.Bit.F2_Cell_Under_V)     //单体电压欠压1级
    ||(Error_Group5.Bit.F2_Cell_Dif_T)     //单体温度不均衡1级
    ||(Error_Group5.Bit.F6_Cell_Under_T)   //单体温度过低1级
    ||(Error_Group2.Bit.F4_Temp_Over)      //单体温度过高1级
    ||(Error_Group4.Bit.F0_SOC_Low)        //SOC低1级
    ||(Error_Group1.Bit.F6_Ins_Err)         //绝缘低
    ||((g_caution_Flag_3 &0x02)!=0) //to PC   //电流传感器故障
    ||(Error_Group0.Bit.F0_Fire_Warning)       //火灾预警2级
    ||(Error_Group6.Bit.F0_Power_Vol)//整车CAN上报
    )
    {
        status_group3.Bit.Fault_Level = 1;//一般
    } 
    else 
    {
        status_group3.Bit.Fault_Level = 0;//无故障
    }
}
//******************************************************************************
//* Function name:    FaultProcess
//* Description:      检测各种故障: 其中三级故障为最严重故障
//* EntryParameter : None
//* ReturnValue    : 有无故障：0-无；1-有  
//******************************************************************************
unsigned char TaskFaultProcess(void) 
{
	unsigned char lever = 0;
	//unsigned char i,j,k=0;
	static unsigned char caution1=0;
	static unsigned char caution2=0;
	static unsigned char caution3=0;
	static unsigned char caution4=0;
	
	errorSystemVoltageOV();//总电压过压
	errorChargeOC();   //充电过流 
	Pack_branch_Disconnect_Fault();
	if(g_BmsModeFlag == DISCHARGING) 
	{
		errorSystemVoltageUV();//总电压欠压
		errorDischargeOC();//放电过流
	}
	if(g_BmsModeFlag == FASTRECHARGING)
	{
		errorLowIsolation();//绝缘过低
		CHG_SocketOT(); //充电插座过温 
	}

	
    if((g_BmsModeFlag == FASTRECHARGING)||(g_BmsModeFlag == RECHARGING))
    {
		DCChangerComError();//直流充电通信故障
//		if(CHMStep != 0) //means start to communicate with the charger.
//		{
//		}
        Charge_Check();//充电电流正负检测
    }
    
    if(g_BmsModeFlag == RECHARGING) //慢充模式
    {
		if(CHMStep != 0)//means start to communicate with the charger.
		{
        	ACChangerComError();
			VCUComError();//与VCU通讯故障
		}
    }
    else if(g_BmsModeFlag == DISCHARGING)//行车模式 
    {
        errorCellVoltageUV();//单体电压过低 
        errorSOCLow();//SOC低
        VCUComError();//与VCU通讯故障
    }                        
    innerCommOT3();//内部通信故障 
    errorCellVoltageOV(); //单体电压过高 
    errorCurrSensorIniatial(); //电流传感器故障
    errorCellUnbalance();//单体电压不均衡
    errorTemUnbalance();//单体温度不均衡
    errorCellTemperatureOT();//单体温度过高
    errorCellTemperatureUT();//单体温度过低
    Fire_Warning();//火灾预警
    PowerSupplyError();//供电电源异常
    
    
    FaultLevel(); //故障等级判断

    BMSProtect();////////BMS最后断继电器

    //*****************************************************************************************
    //******************************************************************************************
    ////////////当故障与之前相比，没有变化时，不进行存储，只有1分钟才存储；如果有更新，才进行存储
    if((caution1^g_caution_Flag_1)||(caution2^g_caution_Flag_2)||(caution3^g_caution_Flag_3)||(caution4^g_caution_Flag_4))
    {
        StoreSysVariable();//保存SOC值和故障信息
    }
	
	caution1 =  g_caution_Flag_1;
	caution2 =  g_caution_Flag_2;
	caution3 =  g_caution_Flag_3;
	caution4 =  g_caution_Flag_4;
	//////////////////////////////////////////////////////////////////
	////Caution_Flag_4：Bit 0：高压母线连接故障；Bit 1：烟雾检测故障；    
	///////////////////  
	g_storageSysVariable[PARA_ERROR_LEVER] = lever;
	g_storageSysVariable[CAUTION_FLAG_1] = g_caution_Flag_1;	
	g_storageSysVariable[CAUTION_FLAG_2] = g_caution_Flag_2;	
	g_storageSysVariable[CAUTION_FLAG_3] = g_caution_Flag_3;	
	g_storageSysVariable[CAUTION_FLAG_4] = g_caution_Flag_4;	

	return g_storageSysVariable[PARA_ERROR_LEVER];   
}
//******************************************************************************
//* Function name:   TurnOffAllRelay
//* Description:     BMS最后的保护,不受状态机控制，强制断高压
//* EntryParameter : 断开所有继电器
//* ReturnValue    : void
//******************************************************************************
int TurnOffAllRelay(void)//
{
    openNegRelay();
    delay(25000); //19ms
    openPosRelay();
    delay(25000); //19ms
    TurnOff_INA2K();//fast charge positive relay.
    delay(25000); //19ms
    TurnOff_INA1K();//EleBand positive relay.
    delay(25000); //19ms
    TurnOff_INBK();//pre-charge relay.
    delay(25000); //19ms
    TurnOff_INHK();//heat relay.
    delay(25000); //19ms
    Error_Group6.Bit.F3_BMS_Protect = 1;//整车CAN赋值 BMS极限故障自我保护
}
//********************************************************************************************
//***********************************the end*************************************************
//********************************************************************************************
//********************************************************************************************

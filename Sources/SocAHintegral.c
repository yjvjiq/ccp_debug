//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : S133
//* File Name          : SocAHintegral.c
//* Author             : judy
//* Version            : V1.0.0
//* Start Date         : 2016.2.14
//* Description        : 该文件用于调整在不同情况下SOC值
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "SocAHintegral.h"
#include  "current.h"
#include  "sd2405.h"
#include  "BMS20.h"
//-------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//float g_socValue=0;  //实际SOC
//float First_g_socValue=0;  //第一次上电时的SOC


float g_socValue=0;  //实际SOC
float g_socValue_Start=0;  //实际SOC修正后初始值
float Can_g_socValue=0;//上报SOC
float Can_g_socValue_Start;//上报的SOC初始值
float First_g_socValue=0;  //第一次上电时的SOC
float StoreAHSOC=0;
//float First_Can_g_socValue=0;  //第一次上电时的SOC
float FactorA=1;//系数(温度系数*SOH)

float g_energyOfUsed=0; //已用电池容量
float g_leftEnergy=0;    //剩余电池容量
//float g_usefulCapacity;//可用电池容量
float g_originalCapacity;//原始总容量Q0
float g_realNominalCap=0;//实际额定容量Q1
float Q2=0;//显示SOC用Q2

//************************************************************************
//* Function name:TaskSocProcess
//* Description:每秒计算并保存上报SOC，每分钟保存一次
//* EntryParameter : None
//* ReturnValue    : None
//************************************************************************
/*void CanSocIntegral(void) 
{
    float CANSOC=0;
    if(g_BmsModeFlag == DISCHARGING)
    {
        if(First_g_socValue!=0)
            CANSOC= Can_g_socValue_Start*g_socValue/First_g_socValue/FactorA+(1.0-1.0/FactorA)*Can_g_socValue_Start; 
        else//如果
        {          
            CANSOC=0;
        }
    }
    else if((g_BmsModeFlag == FASTRECHARGING)||(g_BmsModeFlag == RECHARGING))
    {
        if(First_g_socValue!=1)
            CANSOC = (1.0-Can_g_socValue_Start)*(g_socValue-First_g_socValue)/(1.0-First_g_socValue)/FactorA+Can_g_socValue_Start;   
         else
         {
            CANSOC=1;
         }
            
    } 
    else if(g_BmsModeFlag == TESTSTATE)
    {
        CANSOC=g_socValue;
    }
    if(CANSOC<=0)
        CANSOC=0;
    else if(CANSOC>=1)
        CANSOC=1;
    Can_g_socValue=CANSOC;
} */
//************************************************************************
//* Function name:TaskSocProcess
//* Description:每秒计算并保存上报SOC，每分钟保存一次
//* EntryParameter : None
//* ReturnValue    : None
//************************************************************************
void CanSocIntegral(void) 
{
    float CANSOC=0;
    if(g_BmsModeFlag == DISCHARGING)
    {
        if(First_g_socValue!=0)
            CANSOC= Can_g_socValue_Start*g_socValue/First_g_socValue/FactorA+(1.0-1.0/FactorA)*Can_g_socValue_Start; 
        else//如果
        {          
            CANSOC=0;
        }
    }
    else if((g_BmsModeFlag == FASTRECHARGING)||(g_BmsModeFlag == RECHARGING))
    {
        if(First_g_socValue!=1)
        {
          
            CANSOC = (1.0-Can_g_socValue_Start)*(g_socValue-First_g_socValue)/(1.0-First_g_socValue)/FactorA+Can_g_socValue_Start;  
            if(ChargerStopState==0)
            {
                if(CANSOC>=0.993)
                    CANSOC = 0.993;
            }
        }
        else
        {
           CANSOC=1;
        }
            
    } 
    else if(g_BmsModeFlag == TESTSTATE)
    {
        CANSOC=g_socValue;
    }
    if(CANSOC<=0)
        CANSOC=0;
    else if(CANSOC>=1)
        CANSOC=1;
    Can_g_socValue=CANSOC;
}
//************************************************************************
//* Function name:TaskSocProcess
//* Description:每秒计算并保存SOC，每分钟保存一次历史记录
//* EntryParameter : None
//* ReturnValue    : None
//************************************************************************
void SocIntegral(void) 
{
    float ft=0;
    
    g_leftEnergy = g_socValue*(g_realNominalCap*3600);  //剩余容量
				
		if(g_systemCurrent<=0)// //充电
		{
				if(g_BmsModeFlag == FASTRECHARGING)//快充时计算
				    DC_ChargePower+= (-g_systemCurrent*g_highVoltageV1/1000/3600);//充电电量（输出电量）
				
				if(g_leftEnergy<=g_realNominalCap*3600)//如果容量未满
				{ 
						ft = g_leftEnergy-g_energyOfUsed;
						g_socValue = ft/(g_realNominalCap*3600);
						CanSocIntegral();
				}
		}
				
		if(g_systemCurrent>0)// //放电
		{
			//if(g_leftEnergy>=1.0)
			if(g_leftEnergy>=0)
			{    
				ft = g_leftEnergy-g_energyOfUsed;
				g_socValue = ft/(g_realNominalCap*3600);
				CanSocIntegral();					               				
			}
		} //end of 放电
						 			
		if(g_socValue>=1.0)	
  	{
				g_socValue = 1.0;
				g_leftEnergy = g_socValue*(g_realNominalCap*3600);
				g_energyOfUsed=0;
				//Can_g_socValue_Start=1;
				//CanSocIntegral();
		}   
		if(g_socValue<=0)
		{								
				g_socValue = 0;
				g_leftEnergy = 0;
				g_energyOfUsed=0;
				//Can_g_socValue_Start=0;
				//CanSocIntegral();			 
		}	
}
//******************************************************************************************
//******************************************************************************************
//******************************************************************************************
//*******************************************************************************************


//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : s133
//* File Name          : FeedBack.h
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2015.7.13
//* Description        : 头文件
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

#include "BMS20.h"
//******************************************************************************
//* Function name:   ChagerCurtCutOff
//* Description:     故障处理,有故障后降低充电功率
//* EntryParameter : void
//* ReturnValue    : 故障等级：1 降为0；2降为20%; 3降为50%
//******************************************************************************
unsigned char ChagerCurtCutOff(void)
{
    unsigned char ErrorLever=0;
   
    if(CutChaCurt0.word!=0)
    {
        ErrorLever=3;
        //state_group3.Bit.St_Power_Reduce = 1;//降功率标志位
    } 
    else if(CutChaCurt50.word!=0)
    {
        ErrorLever=2;
        //state_group3.Bit.St_Power_Reduce = 1;//降功率标志位
    } 
    /*else if(CutChaCurt70.word!=0)
    {
        ErrorLever=3;
        //state_group3.Bit.St_Power_Reduce = 1;//降功率标志位
    } */
    else
    {
        ErrorLever=0;
       // if((CutDisCurt0.word==0)&&(CutDisCurt50.word==0))
        //    state_group3.Bit.St_Power_Reduce = 0;//降功率标志位
    } 
    return ErrorLever; 
}
//******************************************************************************
//* Function name:   ChagerCurtCutDone
//* Description:     故障处理,有故障后降低充电功率
//* EntryParameter : 故障等级,经过查表后的电流值,Mode=1or2(30s=1,5min=2);
//* ReturnValue    : 降低后的电流值
//*备注：            CurrentValue：当前SOC,Tem下查表的值;DischargeCurrentOn降低后的值(CurrentValue*系数)
//*备注:             CurrentDisCurrent:当前上报值,不经过查表(CurrentDisCurrent=BiggestDischargePower)
//******************************************************************************
float ChagerCurtCutDone(unsigned char ErrorLever,float CurrentValue,unsigned char Mode)
{
    float ChargeCurrentOn=0;//电流降到多少
    float CurrentChaCurrent=0;//不经过查表
    unsigned char ReturnDone=0;
    
    if(Mode==1)
        CurrentChaCurrent = BiggestFeedbackCurt;//该值不经过查表,显示当前的功率值
        //CurrentChaCurrent = BiggestFeedbackPower;//该值不经过查表,显示当前的功率值
    else if(Mode==2)
        CurrentChaCurrent = BiggestFeedbackCurtContinuous;//该值不经过查表,显示当前的功率值 
        //CurrentChaCurrent = BiggestFeedbackContinuous;//该值不经过查表,显示当前的功率值 
           
    if(ErrorLever==3)
    {      
        ChargeCurrentOn=0;
        ReturnDone=1;
    }
    else if(ErrorLever==2)
    {      
        ChargeCurrentOn=0.5*CurrentValue;
        ReturnDone=1;
    }
    /*else if(ErrorLever==3)
    {      
        ChargeCurrentOn=0.7*CurrentValue;
    }*/ 
        
    if(CurrentChaCurrent<=ChargeCurrentOn)//不经过查表的值小于当前降低功率后的值
    {
        
        CurrentChaCurrent=CurrentChaCurrent+POWERSPEED;
        if(CurrentChaCurrent>=ChargeCurrentOn)
        {              
            CurrentChaCurrent=ChargeCurrentOn;//放电电流为0.2,如果不恢复则断高压
        }
        return CurrentChaCurrent;
    }
    else 
    {
        CurrentChaCurrent=CurrentChaCurrent-POWERSPEED;
        if(CurrentChaCurrent<=ChargeCurrentOn)
        {              
            CurrentChaCurrent=ChargeCurrentOn;//放电电流为0.2,如果不恢复则断高压
        }
        return CurrentChaCurrent;
    }
}
//******************************************************************************
//* Function name:   PulseRechargePowerAdjust1
//* Description:     根据平均温度调整最大允许再生脉冲充电电流30s
//* EntryParameter : tem, soc 平均温度，SOC值
//* ReturnValue    : fc 返回的回馈电流值  
//******************************************************************************
float PulseRechargePowerAdjust1(void) 
{   
    static float current1=0; //回馈电流暂存值1
    static float current2=0; //回馈电流暂存值2;
    //static unsigned int leftTime=0;
    static float fc=0;//返回的回馈电流值
    float BigCharCurrent = 0; 
    static unsigned char FirstTime=0;
    static unsigned char changeFlag=0;
    unsigned char ReduceCurt=0;//降电流的等级
    float BigChaPowerCutDown;//降电流到多少,用于故障恢复后线性变化 
    float ReturnValue=0;
    
    YoungM_PulseRechargePowerAdjust();//调用
    BigCharCurrent = BiggestFeedbackCurt_Model;
     
    /*if(Tavg>0+40)
    { 
        if((BigCharCurrent*g_highVoltageV1/1000)>=100)
            BigCharCurrent=100000/g_highVoltageV1; 
    } 
    else if(Tavg>=(-15+40))
    {
        if((BigCharCurrent*g_highVoltageV1/1000)>=20)
            BigCharCurrent=20000/g_highVoltageV1; 
    }*/
    
    fc=BigCharCurrent;//for test
    
    ReduceCurt=ChagerCurtCutOff();//get the fault level of reduce power fault.
    if(ReduceCurt!=0)//有故障
    {
        if(ReduceCurt==3)
            BigChaPowerCutDown=0;
        else if(ReduceCurt==2)
            BigChaPowerCutDown=0.5*BigCharCurrent;
        
        fc = BigChaPowerCutDown; 
        current1 = BigChaPowerCutDown; 
        FirstTime=1; 
        ReturnValue=ChagerCurtCutDone(ReduceCurt,BigCharCurrent,DISCURT30s);
        return ReturnValue;   
    }
	
    if(FirstTime==0) //第一次进入,只进入一次
    {
        fc=BigCharCurrent; 
        current1 = BigCharCurrent; 
        FirstTime=1;         
    }
    else//再次进入
    {
        if(changeFlag==0)//原值为0，所以current2为第二次进入该函数时的值
        {
            current2=BigCharCurrent;//最新的电流值
        }
        if(current1!=current2) //如果两者不等，说明第一与第二次不等
        {
            changeFlag=1;//设置变化标志位
            if(current1>current2) 
            {
                fc=current1-POWERSPEED;// 每20ms变化0.5kw,7ms调用一次，21ms降低0.51KW
                current1=fc;
                if(current1<=current2)
                {
                    fc=current2;
                    changeFlag=0; 
                }
            }
            else if(current1<current2) 
            {
                fc=current1+POWERSPEED;// 每5ms变化0.05kw
                current1=fc;
                if(current1>=current2) 
                {
                    
                    fc=current2;
                    changeFlag=0;
                }
            }
        } 
        else 
        {
            changeFlag=0; 
        }
    }
 
    return fc; 
}

//******************************************************************************
//* Function name:   ContinueRechargeCurt
//* Description:     根据平均温度调整最大允许再生脉冲充电电流5min
//* EntryParameter : tem, soc 平均温度，SOC值
//* ReturnValue    : fc 返回的回馈电流值  
//******************************************************************************
float ContinueRechargeCurt(void) 
{   
	static float current1=0; //回馈电流暂存值1
	static float current2=0; //回馈电流暂存值2;
//	static unsigned int leftTime=0;
	static float fc=0;//返回的回馈电流值
	float BigCharCurrent = 0;

	static unsigned char FirstTime=0;
	static unsigned char changeFlag=0;
//	static unsigned int ii=0;
//	static unsigned int jj=0;
//	static unsigned char TimeoutFlag1=0;
//	static unsigned char TimeoutFlag2=0;
//	static unsigned char CloseFlag=0;
    
    unsigned char ReduceCurt=0;//降电流的等级
    float BigChaPowerCutDown;//降电流到多少,用于故障恢复后线性变化    
        
    //BigCharCurrent = feedbacksustain_20161129_qingnian_custom(soc,tem);
    
    BigCharCurrent = BiggestFeedbackCurt_Model;
    
    if(BigCharCurrent>=SetCap)
    {
        BigCharCurrent=SetCap;
    }
       
    ReduceCurt=ChagerCurtCutOff();//判断是否有降功率的故障
    if(ReduceCurt!=0)//有故障
    {
        if(ReduceCurt==3)
            BigChaPowerCutDown=0;
        else if(ReduceCurt==2)
            BigChaPowerCutDown=0.5*BigCharCurrent;
        
        fc = BigChaPowerCutDown; 
        current1 = BigChaPowerCutDown; 
        FirstTime=1;
        BiggestFeedbackCurtContinuous=ChagerCurtCutDone(ReduceCurt,BigCharCurrent,DISCURT5min);
        return BiggestFeedbackCurtContinuous;   
    }

    if(FirstTime==0) //第一次进入,只进入一次
    {
        fc=BigCharCurrent; 
        current1 = BigCharCurrent; 
        FirstTime=1;         
    }
    else//再次进入
    {
        if(changeFlag==0)//原值为0，所以current2为第二次进入该函数时的值
        {
            current2=BigCharCurrent;//最新的电流值
      
        }
        
        if(current1!=current2) //如果两者不等，说明第一与第二次不等
        {
            changeFlag=1;//设置变化标志位
            if(current1>current2)
            {
                fc=current1-POWERSPEED;// 每20ms变化0.5kw,7ms调用一次，21ms降低0.51KW
                current1=fc;
                if(current1<=current2)
                {
                    fc=current2;
                    changeFlag=0; 
                }
            }
            else if(current1<current2) 
            {
                fc=current1+POWERSPEED;// 每5ms变化0.05kw
                current1=fc;
                if(current1>=current2) 
                {
                    
                    fc=current2;
                    changeFlag=0;
                }
            }
        } 
        else 
        {
            changeFlag=0; 
        }
    }
 
    return fc; 
}
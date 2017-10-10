
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : 青年浦江
//* File Name          : SOF.c
//* Author             : 孙丽雪
//* Version            : V1.0.0
//* Start Date         : 2016.11.30
//* Description        : 该文件用于查表计算SOF当前值
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "BMS20.h" 

//******************************************************************************
//* Function name:   DischagerCurtCutOff
//* Description:     故障处理,有故障后降低放电功率
//* EntryParameter : void
//* ReturnValue    : 故障等级：1 降为0；2降为50%; 3降为70%
//******************************************************************************
unsigned char DischagerCurtCutOff(void)
{
    unsigned char ErrorLever=0;

    if(CutDisCurt0.word!=0)
    {
        ErrorLever=3;
    } 
    else if(CutDisCurt50.word!=0)
    {
        ErrorLever=2;
    }
    /*else if(CutDisCurt70.word!=0)
    {
        ErrorLever=3;
    }*/ 
    else 
    {
        ErrorLever=0;
    }  
    return ErrorLever; 
    

}
//******************************************************************************
//* Function name:   DischagerCurtCutDone
//* Description:     故障处理,有故障后降低放电功率
//* EntryParameter : 故障等级,经过查表后的电流值,Mode=1or2(30s=1,5min=2);
//* ReturnValue    : 降低后的电流值
//*备注：            CurrentValue：当前SOC,Tem下查表的值;DischargeCurrentOn降低后的值(CurrentValue*系数)
//*备注:             CurrentDisCurrent:当前上报值,不经过查表(CurrentDisCurrent=BiggestDischargePower)
//******************************************************************************
float DischagerCurtCutDone(unsigned char ErrorLever,float CurrentValue,unsigned char Mode)
{
    float DischargeCurrentOn=0;//电流降到多少
    float CurrentDisCurrent=0;//不经过查表
    unsigned char ReturnDone=0;
    
    if(Mode==1)
        CurrentDisCurrent = BiggestDischargeCurt;//该值不经过查表,显示当前的功率值
    else if(Mode==2)
        CurrentDisCurrent = BiggestDisCurtContinuous;//该值不经过查表,显示当前的功率值 
           
    if(ErrorLever==3)
    {      
        DischargeCurrentOn=0;
        ReturnDone=1;
    }
    else if(ErrorLever==2)
    {      
        DischargeCurrentOn=0.5*CurrentValue;
        ReturnDone=1;
    }
    /*else if(ErrorLever==3)
    {      
        DischargeCurrentOn=0.7*CurrentValue;
        
    }*/     
    if(CurrentDisCurrent<=DischargeCurrentOn)//不经过查表的值小于当前降低功率后的值
    {
        CurrentDisCurrent=CurrentDisCurrent+POWERSPEED;
        if(CurrentDisCurrent>=DischargeCurrentOn)
        {              
            CurrentDisCurrent=DischargeCurrentOn;//放电电流为0.2,如果不恢复则断高压
        }
        return CurrentDisCurrent;
    }
    else 
    {
        CurrentDisCurrent=CurrentDisCurrent-POWERSPEED;
        if(CurrentDisCurrent<=DischargeCurrentOn)
        {              
            CurrentDisCurrent=DischargeCurrentOn;//放电电流为0.2,如果不恢复则断高压
        }
        return CurrentDisCurrent;
    }
}
//******************************************************************************
//* Function name:   BigDischargePowerAdjust
//* Description:     New SOF 
//* EntryParameter : 温度，SOC，当前最大允许功率或电流值
//* ReturnValue    : bigPowerCurrent当前最大允许放电功率或电流
//******************************************************************************
float BigDischargePowerAdjust()
{
    static float power1=0; //放电功率暂存值1
    static float power2=0; //放电功率暂存值2
    static unsigned char counter=0;//2次回馈功率计数
    static unsigned char changeFlag=0;//功率线性变化时标志位
    static unsigned char FirstOn=0;
    unsigned char ReduceCurt=0;//故障等级1,2,3的返回值
    float BigDisPower=0; //最大允许放电功率的中间变量，防止查表得到的数中断直接发送
    float BigDisPowerCutDown=0;//不同故障下,电流降低到多少
    float ReturnValue=0;
    static float pc=0;//最大允许放电功率/电流 返回值
    
    BigDisPower=BiggestDischargeCurt;
    
    YoungMa_BigDischargePowerAdjust();
    BigDisPower=BiggestDischargeCurt_Model;
    ReduceCurt=DischagerCurtCutOff();//判断是否有降功率的故障
    if(ReduceCurt!=0)//有故障
    {
        if(ReduceCurt==3)
            BigDisPowerCutDown=0;
        else if(ReduceCurt==2)
            BigDisPowerCutDown=0.5*BigDisPower;
        //else if(ReduceCurt==3)
        //    BigDisPowerCutDown=0.7*BigDisPower;
        pc = BigDisPowerCutDown; 
        power1 = BigDisPowerCutDown; 
        FirstOn=1; 
        ReturnValue=DischagerCurtCutDone(ReduceCurt,BigDisPower,DISCURT30s);
        return ReturnValue; 
    }
    if(FirstOn==0) //第一次进入
    {
        pc=BigDisPower; 
        power1 = BigDisPower; 
        FirstOn=1;         
    } 
    else//再次进入
    {
        if(changeFlag==0)//原值为0，所以power2为第二次进入该函数时的值
            power2=BigDisPower;
     
        if(power1!=power2) //如果两者不等，说明第一与第二次不等
        {
            changeFlag=1;//设置变化标志位
            if(power1>power2) 
            {
                pc=power1-POWERSPEED;// 每20ms变化0.5kw,7ms调用一次，21ms降低0.51KW
                power1=pc;
                if(power1<=power2)
                {
                    
                    pc=power2;
                    changeFlag=0; 
                }
            }
            else if(power1<power2) 
            {
                pc=power1+POWERSPEED;// 每5ms变化0.05kw
                power1=pc;
                if(power1>=power2) 
                {
                    
                    pc=power2;
                    changeFlag=0;
                }
            }
        } 
        else 
        {
            changeFlag=0; 
        }
    
    } 
 
    return pc; 
    
}
//******************************************************************************
//* Function name:   BigDischargePowerContinuous
//* Description:     New SOF 
//* EntryParameter : 温度，SOC，当前最大允许功率或电流值
//* ReturnValue    : bigPowerCurrent当前最大允许放电功率或电流
//******************************************************************************
float BigDischargePowerContinuous()
{
    static float power1=0; //放电功率暂存值1
    static float power2=0; //放电功率暂存值2
    static unsigned char counter=0;//2次回馈功率计数
    static unsigned char changeFlag=0;//功率线性变化时标志位
    static unsigned char FirstOn=0;
    unsigned char ReduceCurt=0;
    float BigDisPower=0; //最大允许放电功率的中间变量，防止查表得到的数中断直接发送
    float BigDisPowerCutDown=0;
    static float pc=0;//最大允许放电功率/电流 返回值
    
   
    BigDisPower=BiggestDischargeCurt_Model;
    if(BigDisPower>=SetCap)
    {
        BigDisPower=SetCap;
    }
    ReduceCurt = DischagerCurtCutOff();
    if(ReduceCurt!=0)//有故障
    {
        if(ReduceCurt==3)
            BigDisPowerCutDown=0;
        else if(ReduceCurt==2)
            BigDisPowerCutDown=0.5*BigDisPower;
        //else if(ReduceCurt==3)
        //    BigDisPowerCutDown=0.7*BigDisPower;
        pc = BigDisPowerCutDown;//故障恢复后,线性变化回来 
        power1 = BigDisPowerCutDown; //故障恢复后,线性变化回来 
        FirstOn=1; 
        BiggestDisCurtContinuous=DischagerCurtCutDone(ReduceCurt,BigDisPower,DISCURT5min);
        return BiggestDisCurtContinuous; 
    }
    if(FirstOn==0) //第一次进入
    {
        pc=BigDisPower; 
        power1 = BigDisPower; 
        FirstOn=1;         
    } 
    else//再次进入
    {
        if(changeFlag==0)//原值为0，所以power2为第二次进入该函数时的值
            power2=BigDisPower;
     
        if(power1!=power2) //如果两者不等，说明第一与第二次不等
        {
            changeFlag=1;//设置变化标志位
            if(power1>power2) 
            {
                pc=power1-POWERSPEED;// 每20ms变化0.5kw,7ms调用一次，21ms降低0.51KW
                power1=pc;
                if(power1<=power2)
                {
                    
                    pc=power2;
                    changeFlag=0; 
                }
            }
            else if(power1<power2) 
            {
                pc=power1+POWERSPEED;// 每5ms变化0.05kw
                power1=pc;
                if(power1>=power2) 
                {
                    
                    pc=power2;
                    changeFlag=0;
                }
            }
        } 
        else 
        {
            changeFlag=0; 
        }
    } 
    return pc; 
}
//***********************************************************************************************
//************************************************************************************************
//************************************the end*****************************************************
//************************************************************************************************
//***********************************************************************************************
//************************************************************************************************
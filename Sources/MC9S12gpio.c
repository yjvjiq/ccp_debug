//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : gpio.C
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,06,02
//* Description        : 该程序针对9s12xep100的IO口进行定义和设置，同时判断系统的输入信号
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------


#include "derivative.h" /* include peripheral declarations */
#include "BMS20.h"

//**********************************************************************
//* Function name:   gpioInit
//* Description:     IO口初始化
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void gpioInit(void) 
{
    DDRP |= 0xfe;

    DDRK &= 0x7f;  //设定PK7为输入   
    DDRA |= 0x01;  //portA0 方向为输出 即 SW_POWER口    
    DDRA &= 0x3f;  //portA PA6（CP） PA7（CC2）为输入
    DDRS |= 0x03;  //PS0,PS1为输出口
    DDRM |= 0x80;  //pm7 as output
    //DDRB |= 0x10;  //PB4 as WDI 外部看门狗输入
    
    ATD0DIENL |= 0xe0;  //将AN05 AN06 AN07模拟输入口设置为 数字使能
    ATD0DIENH |= 0xe0;  //将AN13 AN14 AN15模拟输入口设置为 数字使能
    DDR1AD0 &= 0xbf;//PAD06 为输入 IN1
    DDR0AD0 &= 0xdf;//PAD13 为输入IN2
    DDR1AD0 &= 0xdf;//PAD05 为输入 IN3
    DDR0AD0 &= 0x7f;//PAD15 为输入IN+
    DDR1AD0 &= 0x7f;//PAD07 为输入 IN-
    DDR0AD0 &= 0xbf;//PAD14 为输入INh
    IRQCR &= 0xBF;
 
}
//**********************************************************************
//* Function name:   turnOnLED0
//* Description:     点亮LED0的灯
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void turnOnLED0(void)      //控制LED0的灯
{
    PTP |= 0x02;     //输出PP2=1;
}
//**********************************************************************
//* Function name:   turnOffLED0
//* Description:     熄灭LED0
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void turnOffLED0(void) 
{
    PTP &= 0xfd;     //输出PP2=0;
}
//**********************************************************************
//* Function name:   turnOnSW_Power
//* Description:     闭合SW_POWER开关
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void turnOnSW_Power(void)//控制SW_POWER开关
{

    PORTA |= 0x01;  //输出PA0=1
}
//**********************************************************************
//* Function name:   turnOffSW_Power
//* Description:     断开SW_POWER开关
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void turnOffSW_Power(void)//
{

    PORTA &= 0xfe;   //输出PA1=0
}
//**********************************************************************
//* Function name:   turnOnDO1
//* Description:     打开开关DO1
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void turnOnDO1(void) 
{
     PTS |= 0x02;  //打开开关DO1
}
//**********************************************************************
//* Function name:   turnOffDO1
//* Description:     断开DO1
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void turnOffDO1(void) 
{
     PTS &= 0xfd;  //闭合开关DO1
}
//**********************************************************************
//* Function name:   turnOnDO2
//* Description:     打开开关 D02
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void turnOnDO2(void) 
{
     PTS |= 0x01;  //打开开关 D02
}
//**********************************************************************
//* Function name:   turnOffDO2
//* Description:     断开开关DO2
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void turnOffDO2(void) 
{
     PTS &= 0xfe;  //闭合开关DO2
}
//*******************************************
//************以下是各个开关量对应的反馈值
//**********所有反馈返回0表示连接上，返回1表示断开************************
//**********************************************************************
//* Function name:   input1_state
//* Description:     充电反馈
//* EntryParameter : None
//* ReturnValue    : 返回0表示连接上，返回1表示断开
//**********************************************************************
unsigned char input1_state(void)    //IN1          ///test充电反馈
{
    unsigned char t;
    
    t=0;   
    if (PT1AD0 & 0x40) 
    {
        while(t<10) 
        {
            t++;
            if ((PT1AD0 & 0x40)==0) 
                return 0;         
            if(t>=10)
                return 1; 
        }
    }    
    return 0;        
}
//**********************************************************************
//* Function name:   input2_state
//* Description:     in2状态
//* EntryParameter : None
//* ReturnValue    : 返回0表示连接上，返回1表示断开
//**********************************************************************
unsigned char input2_state(void)    //IN2
{
    if (PT0AD0 & 0x20) 
        return 1;    
    return 0;        
}
//**********************************************************************
//* Function name:   input3_state
//* Description:     in3
//* EntryParameter : None
//* ReturnValue    : 返回0表示连接上，返回1表示断开
//**********************************************************************
unsigned char input3_state(void)                 //////test INPUT2
{
    if (PT1AD0 & 0x20) 
      return 1;    
    return 0;
          
}
//**********************************************************************
//* Function name:   inputP_state
//* Description:     IN+  正极反馈
//* EntryParameter : None
//* ReturnValue    : 返回0表示连接上，返回1表示断开
//**********************************************************************
unsigned char inputP_state(void)   //IN+         /////test 正极反馈
{                        
    if (PT0AD0 & 0x80) 
        return 1;    
    return 0;        
}
//**********************************************************************
//* Function name:   inputN_state
//* Description:     IN- 负极反馈
//* EntryParameter : None
//* ReturnValue    : 返回0表示连接上，返回1表示断开
//**********************************************************************
unsigned char inputN_state(void)  //IN-
{
    if (PT1AD0 & 0x80) 
        return 1;    
    return 0;        
}
//**********************************************************************
//* Function name:   inputH_state
//* Description:     INh     高低压互锁   
//* EntryParameter : None
//* ReturnValue    : 返回0表示连接上，返回1表示断开
//**********************************************************************
unsigned char inputH_state(void)   //INh      ///////////////高低压互锁   
{
    if (PT0AD0 & 0x40) 
        return 1;    
    return 0;        
}

unsigned char HV_Lock_Error_state(void){
	return inputH_state();
}
//**********************************************************************
//* Function name:   input4_state
//* Description:     IN4
//* EntryParameter : None
//* ReturnValue    : 返回0表示连接上，返回1表示断开
//**********************************************************************
unsigned char input4_state(void)   //IN4
{
    if (PORTA & 0x02) 
        return 1;    
    return 0; 
            
}
//**********************************************************************
//* Function name:   input5_state
//* Description:     CC2 = IN5
//* EntryParameter : None
//* ReturnValue    : 返回0表示连接上，返回1表示断开
//**********************************************************************
unsigned char input5_state(void)      //CC2 = IN5
{
    if (PORTA & 0x80) 
      return 1;    
    return 0; 
          
}
//**********************************************************************
//* Function name:   input6_state
//* Description:     IN6  = CP
//* EntryParameter : None
//* ReturnValue    : 返回0表示连接上，返回1表示断开
//**********************************************************************
unsigned char input6_state(void)      //PP0  = IN6   ///////test CP
{
    if (PTP & 0x01) 
        return 1;    
    return 0;           
}
//**********************************************************************
//* Function name:   inputAll_state
//* Description:     
//* EntryParameter : None
//* ReturnValue    : 返回0表示无反馈；1表示有反馈
//**********************************************************************
unsigned char inputAll_state(void) 
{
    if(!input1_state())
        return 0;
     
    if(!input2_state())
        return 0;
     
    if(!input3_state())
        return 0;
     
    if(!input4_state())
        return 0;
     
    if(!inputP_state())
        return 0;
     
    if(!inputN_state())
        return 0;
     
    if(!inputH_state())
        return 0;
          
    return 1;
}

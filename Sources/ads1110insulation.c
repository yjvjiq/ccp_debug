//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : ads1110insulation.C
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,05,26
//* Description        : 本程序采用IIC通信方式； 4兆PIC16F877,是ADS1100,ADS1110的通用程序,用于绝缘阻值计算功能
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

#include "derivative.h" /* include peripheral declarations */
#include "BMS20.h"

#define uch unsigned char
#define unint unsigned int

#define SCL4  PTP_PTP6
#define SDA4_DIR DDRP_DDRP7  //1--output  0---input
#define SDA4  PTP_PTP7

unsigned char TMR1L_iso,TMR1H_iso,TMR2_iso;

//**********************************************************************
//* Function name:   delay10usU4  
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void delay10usU4() 
{
    unint j;
    for(j=0;j<5;j++);
}
//**********************************************************************
//* Function name:   startU4  
//* Description:     开始信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void startU4 (void)       //开始
{
    SDA4_DIR =1;
    asm("nop");
    SDA4=1;
    asm("nop");
    SCL4=1;
    delay10usU4();
    SDA4=0;
    asm("nop");  
    SCL4=0;    
    delay10usU4();
}
//**********************************************************************
//* Function name:   stopU4
//* Description:     结束信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void stopU4(void)             //结束
{ 
    SDA4_DIR =1;
    SDA4=0;
    asm("nop");
    SCL4=1;
    delay10usU4();
    SDA4=1;
    delay10usU4();
    SCL4=0;
    delay10usU4();       
}
//**********************************************************************
//* Function name:   checkU4
//* Description:     检查应答信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************    
uch checkU4(void)    //  检查应答信号
{  
    uch ACK;
    
    SDA4_DIR =0;   //注意，此处方向变换应该在时钟为低的时候
    SCL4=0;
    delay10usU4();
    SCL4=1;    
    delay10usU4();             
    asm("nop");
    asm("nop");
    if (SDA4 )
    {
        ACK = 1;
    }
    else
    {
        ACK = 0;
    }    
    SCL4=0;    
    asm("nop");    
    return(ACK);
}
//**********************************************************************
//* Function name:   sendBYTE_U4
//* Description:     发送一个字节
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************       
void sendBYTE_U4(uch data)   //  发送一个字节
{
    uch bitcount=8;               //发送8位

    SDA4_DIR =1;
    do
    { 
        SCL4=0;              //在时钟大于4u秒期间写数据         
        if((data&0x80)==0x80)   
        {
            SDA4=1;         //写 1
        }
        else  
        {
            SDA4=0;        //写 0
        }  
        delay10usU4();     
        SCL4=1;
        delay10usU4();
        data=data<<1;
        bitcount--;
    } while(bitcount);
    SCL4=0;
      
}   
//**********************************************************************
//* Function name:   reciveBYTE_U4 
//* Description:     接收一个字节
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
uch reciveBYTE_U4(void)             //接受一个字节
{
    uch temp1=0;
    uch bitcount1=8;

    SDA4_DIR =0;
    asm("nop");
    asm("nop");
    asm("nop");
    do
    { 
        SCL4=0;              //在时钟大于4u秒期间读数据
        delay10usU4();
        SCL4=1;
        delay10usU4();  
        if(SDA4)                //读 1
        { 
            temp1=temp1|0x01;    
        }
        else                     //读 0
        {
            temp1=temp1&0xfe;
        }

        if(bitcount1-1)
        {
            temp1=temp1<<1; 
        }
        bitcount1--;  
    }while(bitcount1);
    SCL4=0;
    asm("nop");
    return(temp1);
}  
//**********************************************************************
//* Function name:   ackU4 
//* Description:     发送连续读信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************    
void ackU4(void)          //  发送连续读信号
{ 
    SDA4_DIR =1;
    SDA4=0;
    SCL4=0;
    delay10usU4();
    SCL4=1;
    delay10usU4();
    SCL4=0;
    delay10usU4();
}
//**********************************************************************
//* Function name:   nackU4
//* Description:     发送不连续读信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************        
void nackU4(void)        //  发送不连续读信号
{ 
    SDA4_DIR =1;
    SDA4=1; 
    delay10usU4();  
    SCL4=1;
    delay10usU4();
    SCL4=0;
}  
//**********************************************************************
//* Function name:   wrtoIIC_U4
//* Description:     写器件地址和配置字
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************  
void wrtoIIC_U4(uch data)     //写器件地址和配置字
{ 
    uch i;
    
    i=20;
    startU4();               //开始写
    sendBYTE_U4(0x90);         //写器件地址（写）       
    do
    {
      i--;
    }while(checkU4()&&(i>0));       //等待应答   
     
    sendBYTE_U4(data);      //写配置字
    delay10usU4();
    i=20;
    do
    {
       i--;        
    }while(checkU4()&&(i>0));       
    stopU4();            //结束写    
             
}
/*
void resetIIC(uch data) 
{
    start();               //开始写
    sendBYTE(0x00);         //写器件地址（写）       
    do
    {
      ;
    }while(check());       //等待应答   
     
    sendBYTE(data);      //写配置字
    delay10us();
    do
    {
       ;        
    }while(check());        
    stop();            //结束写 

}
*/
//**********************************************************************
//* Function name:   rdfromIIC_U4
//* Description:     从ADS1100中读出数据
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void rdfromIIC_U4(void)       //从ADS1100中读出数据
{   
    uch i;
    
    i=20;
    startU4();                  //开始读
    sendBYTE_U4(0x91);           //写器件地址（读）
    do
    {
        i--;
    }while(checkU4()&&(i>0));     //等待应答           
    TMR1H_iso=reciveBYTE_U4();     // 读高8位
    ackU4();                  //连续读
    TMR1L_iso=reciveBYTE_U4();     //读低8位
    ackU4();                  //连续读
    TMR2_iso=reciveBYTE_U4();      //读配置字
    nackU4();
    stopU4();                  //结束读
   
} 
//**********************************************************************
//* Function name:   GetInsulateVoltAd 
//* Description:     获取绝缘通道电压AD值
//* EntryParameter : None
//* ReturnValue    : AD值
//**********************************************************************     
unsigned int GetInsulateVoltAd(void)
{   
    unsigned char i;
    unsigned long buffer=0;
    unsigned int ad=0;

    wrtoIIC_U4(0x8c); 
              
    for(i=0;i<8;i++) 
    {      
        rdfromIIC_U4();   
        buffer += (((unsigned long)TMR1H_iso&0xffff)<<8) | (unsigned long)TMR1L_iso; 
    }
    ad = buffer>>3;
    return ad;
      
}  

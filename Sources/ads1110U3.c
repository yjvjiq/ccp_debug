//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : ads1110U3.C
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,05,26
//* Description        : 本程序采用IIC通信方式； 是ADS1100,ADS1110的通用程序,用于系统总电压V3的计算
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "derivative.h" /* include peripheral declarations */

#define uch unsigned char
#define unint unsigned int

#define SCL3  PTM_PTM7
#define SDA3_DIR DDRM_DDRM6  //1--output  0---input
#define SDA3  PTM_PTM6

///// below for test
//#define SCL3  PTP_PTP2
//#define SDA3_DIR DDRP_DDRP3  //1--output  0---input
//#define SDA3  PTP_PTP3

unsigned char TMR1L_U3,TMR1H_U3,TMR2_U3;
//**********************************************************************
//* Function name:   delay10usU3
//* Description:     延时
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void delay10usU3() 
{
    unint j;
    for(j=0;j<5;j++);
}
//**********************************************************************
//* Function name:   startU3
//* Description:     开始
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void startU3 (void)       //开始
{
    SDA3_DIR =1;
    asm("nop");
    SDA3=1;
    asm("nop");
    SCL3=1;
    delay10usU3();
    SDA3=0;
    asm("nop");  
    SCL3=0;    
    delay10usU3();
}
//**********************************************************************
//* Function name:   stopU3
//* Description:     结束
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void stopU3(void)             //结束
{ 
    SDA3_DIR =1;
    SDA3=0;
    asm("nop");
    SCL3=1;
    delay10usU3();
    SDA3=1;
    delay10usU3();
    SCL3=0;
    delay10usU3();       
}
//**********************************************************************
//* Function name:   checkU3
//* Description:     检查应答信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************    
uch checkU3(void)    //  检查应答信号
{  
    uch ACK;
    
    SDA3_DIR =0;   //注意，此处方向变换应该在时钟为低的时候
    SCL3=0;
    delay10usU3();
    SCL3=1;    
    delay10usU3();             
    asm("nop");
    asm("nop");
    if (SDA3 )
    {
        ACK = 1;
    }
    else
    {
        ACK = 0;
    } 
       
    SCL3=0;    
    asm("nop");    
    return(ACK);
}
//**********************************************************************
//* Function name:   sendBYTE_U3
//* Description:     发送一个字节
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************          
void sendBYTE_U3(uch data)   //  发送一个字节
{
    uch bitcount=8;               //发送8位

    SDA3_DIR =1;
    do
    { 
        SCL3=0;              //在时钟大于4u秒期间写数据         
        if((data&0x80)==0x80)   
        {
            SDA3=1;         //写 1
        }
        else  
        {
            SDA3=0;        //写 0
        }  
        delay10usU3();     
        SCL3=1;
        delay10usU3();
        data=data<<1;
        bitcount--;
    } while(bitcount);
    SCL3=0;      
}   
//**********************************************************************
//* Function name:   reciveBYTE_U3
//* Description:     接收一个字节
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
uch reciveBYTE_U3(void)             //接收一个字节
{
    uch temp1=0;
    uch bitcount1=8;

    SDA3_DIR =0;
    asm("nop");
    asm("nop");
    asm("nop");
    do
    { 
        SCL3=0;              //在时钟大于4u秒期间读数据
        delay10usU3();
        SCL3=1;
        delay10usU3();  
        if(SDA3)                //读 1
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
    SCL3=0;
    asm("nop");
    return(temp1);
}  
//**********************************************************************
//* Function name:   ackU3
//* Description:     发送连续读信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************    
void ackU3(void)          //  发送连续读信号
{ 
    SDA3_DIR =1;
    SDA3=0;
    SCL3=0;
    delay10usU3();
    SCL3=1;
    delay10usU3();
    SCL3=0;
    delay10usU3();
}
//**********************************************************************
//* Function name:   nackU3
//* Description:     发送不连续读信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************     
void nackU3(void)        //  发送不连续读信号
{ 
    SDA3_DIR =1;
    SDA3=1; 
    delay10usU3();  
    SCL3=1;
    delay10usU3();
    SCL3=0;
}  
//**********************************************************************
//* Function name:   wrtoIIC_U3
//* Description:     写器件地址和配置字
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************  
void wrtoIIC_U3(uch data)     //写器件地址和配置字
{ 
    uch i;

    i =20;
    
    startU3();               //开始写
    sendBYTE_U3(0x90);         //写器件地址（写）       
    do
    {
      i--;
    }while((checkU3()&&(i>0)));       //等待应答   
    
    sendBYTE_U3(data);      //写配置字
    delay10usU3();
    i =20;
    do
    {
       i--;        
    }while((checkU3()&&(i>0)));       
    stopU3();            //结束写    
            
}
//**********************************************************************
//* Function name:   rdfromIIC_U3
//* Description:     从ADS1100中读出数据
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void rdfromIIC_U3(void)       //从ADS1100中读出数据
{   
    uch i;

    i =20;  
    startU3();                  //开始读
    sendBYTE_U3(0x91);           //写器件地址（读）
    do
    {
         i--;
    }while((checkU3()&&(i>0)));      //等待应答
            
    TMR1H_U3=reciveBYTE_U3();     // 读高8位
    ackU3();                  //连续读
    TMR1L_U3=reciveBYTE_U3();     //读低8位
    ackU3();                  //连续读
    TMR2_U3=reciveBYTE_U3();      //读配置字
   
    nackU3();
    stopU3();                  //结束读
   
} 
//**********************************************************************
//* Function name:   GetU3adValue
//* Description:     获取绝缘通道电压AD值
//* EntryParameter : None
//* ReturnValue    : AD值
//**********************************************************************      
unsigned int GetU3adValue(void)
{   
    //unsigned char i;
    //unsigned long buffer=0;
    unsigned int ad=0;

    wrtoIIC_U3(0x84);        
    /*
    for(i=0;i<8;i++) 
    {   
        rdfromIIC_U3();
        buffer += (((unsigned long)TMR1H_U3&0xffff)<<8) | (unsigned long)TMR1L_U3; 
    }
    ad = buffer>>3;              //结果除以8
    */
    rdfromIIC_U3();
    ad += (((unsigned long)TMR1H_U3&0xffff)<<8) | (unsigned long)TMR1L_U3; 
    return ad;
      
}  

////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
///////////////////////////////////////END///////////////////////////////
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : ads1110U1.C
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,05,26
//* Description        : 本程序采用IIC通信方式； 是ADS1100,ADS1110的通用程序,用于系统总电压V1的计算
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

#include "derivative.h" /* include peripheral declarations */

#define uch unsigned char
#define unint unsigned int

#define SCL1  PTP_PTP4
#define SDA1_DIR DDRP_DDRP5  //1--output  0---input
#define SDA1  PTP_PTP5
/////////////// below for test/////////
//#define SCL1  PTP_PTP2
//#define SDA1_DIR DDRP_DDRP3  //1--output  0---input
//#define SDA1  PTP_PTP3
///////////////test/////////
unsigned char TMR1L_U1,TMR1H_U1,TMR2_U1;
//**********************************************************************
//* Function name:   delay10usU1
//* Description:     延时
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void delay10usU1() 
{
    unint j;
    for(j=0;j<5;j++);
}
//**********************************************************************
//* Function name:   startU1
//* Description:     开始
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void startU1 (void)       //开始
{
    SDA1_DIR =1;
    asm("nop");
    SDA1=1;
    asm("nop");
    SCL1=1;
    delay10usU1();
    SDA1=0;
    asm("nop");  
    SCL1=0;    
    delay10usU1();
}
//**********************************************************************
//* Function name:   stopU1
//* Description:     结束
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void stopU1(void)             //结束
{ 
    SDA1_DIR =1;
    SDA1=0;
    asm("nop");
    SCL1=1;
    delay10usU1();
    SDA1=1;
    delay10usU1();
    SCL1=0;
    delay10usU1();       
}
//**********************************************************************
//* Function name:   checkU1
//* Description:     检查应答信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************    
uch checkU1(void)    //  检查应答信号
{  
    uch ACK;
    
    SDA1_DIR =0;   //注意，此处方向变换应该在时钟为低的时候
    SCL1=0;
    delay10usU1();
    SCL1=1;    
    delay10usU1();             
    asm("nop");
    asm("nop");
    if (SDA1 )
    {
        ACK = 1;
    }
    else
    {
        ACK = 0;
    } 
       
    SCL1=0;    
    asm("nop");    
    return(ACK);
}
//**********************************************************************
//* Function name:   sendBYTE_U1
//* Description:     发送一个字节
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************      
void sendBYTE_U1(uch data)   //  发送一个字节
{
    uch bitcount=8;               //发送8位

    SDA1_DIR =1;
    do
    { 
        SCL1=0;              //在时钟大于4u秒期间写数据         
        if((data&0x80)==0x80)   
        {
            SDA1=1;         //写 1
        }
        else  
        {
            SDA1=0;        //写 0
        }  
        delay10usU1();     
        SCL1=1;
        delay10usU1();
        data=data<<1;
        bitcount--;
    } while(bitcount);
    SCL1=0;
    SDA1=0;        //写 0
      
}   
//**********************************************************************
//* Function name:   reciveBYTE_U1
//* Description:     接受一个字节
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
uch reciveBYTE_U1(void)             //接受一个字节
{
    uch temp1=0;
    uch bitcount1=8;

    
    SDA1_DIR =0;
    asm("nop");
    asm("nop");
    asm("nop");
    do
    { 
        SCL1=1;
        delay10usU1();  
        if(SDA1)                //读 1
        { 
            temp1=temp1|0x01;    
        }
        else                     //读 0
        {
            temp1=temp1&0xfe;
        }
        SCL1=0;              //在时钟大于4u秒期间读数据
        delay10usU1();

        if(bitcount1-1)
        {
            temp1=temp1<<1;
        }
        bitcount1--;  
    }while(bitcount1);
    asm("nop");
    return(temp1);
}  
//**********************************************************************
//* Function name:   ackU1
//* Description:     发送连续读信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************    
void ackU1(void)          //  发送连续读信号
{ 
    SDA1_DIR =1;
    SDA1=0;
    SCL1=0;
    delay10usU1();
    SCL1=1;
    delay10usU1();
    SCL1=0;
    delay10usU1();  
    SDA1=1;
}
//**********************************************************************
//* Function name:   nackU1
//* Description:     发送不连续读信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************     
void nackU1(void)        //  发送不连续读信号
{ 
    SDA1_DIR =1;
    SDA1=1; 
    delay10usU1();  
    SCL1=1;
    delay10usU1();
    SCL1=0;
    SDA1=0; 
}  
//**********************************************************************
//* Function name:   wrtoIIC_U1
//* Description:     写器件地址和配置字
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************   
void wrtoIIC_U1(uch data)     //写器件地址和配置字
{ 
    uch i;

    i =20;
    startU1();               //开始写
    sendBYTE_U1(0x90);         //写器件地址（写）       
    do
    {
      i--;
    }while(checkU1()&&(i>0));       //等待应答  
    //}while(checkU1());
     
    sendBYTE_U1(data);      //写配置字
    delay10usU1();
    
    i=20;
    do
    {
       i--;         
    }while(checkU1()&&(i>0)); 
    //}while(checkU1());         
    stopU1();            //结束写    
             
}

//**********************************************************************
//* Function name:   resetIIC_U1
//* Description:     复位器件
//* EntryParameter : None
//* ReturnValue    : None
//********************************************************************** 
/*
void resetIIC_U1(uch data) 
{
    startU1();               //开始写
    sendBYTE_U1(0x00);         //写器件地址（写）       
    do
    {
      ;
    }while(checkU1());       //等待应答   
     
    sendBYTE_U1(data);      //写配置字
    delay10usU1();
    do
    {
       ;        
    }while(checkU1());        
    stopU1();            //结束写 

}    
*/
//**********************************************************************
//* Function name:   rdfromIIC_U1
//* Description:     从ADS1100中读出数据
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void rdfromIIC_U1(void)       //从ADS1100中读出数据
{   
    uch i;

    i =20;
    
    startU1();                  //开始读
    sendBYTE_U1(0x91);           //写器件地址（读）
    do
    {
         i--;
    }while(checkU1()&&(i>0));    //等待应答
    //}while(checkU1());
               
    TMR1H_U1=reciveBYTE_U1();     // 读高8位
    ackU1();                  //连续读
    TMR1L_U1=reciveBYTE_U1();     //读低8位
    ackU1();                  //连续读
    TMR2_U1=reciveBYTE_U1();      //读配置字
    nackU1();
    stopU1();                  //结束读
   
} 
//**********************************************************************
//* Function name:   GetU1adValue
//* Description:     获取绝缘通道电压AD值
//* EntryParameter : None
//* ReturnValue    : AD值
//**********************************************************************          
unsigned int GetU1adValue(void)
{   
    //unsigned char i;
    unsigned long buffer=0;
    unsigned int ad=0;
      
    wrtoIIC_U1(0x84);      
    /*
    for(i=0;i<8;i++) 
    {   
        rdfromIIC_U1();
        buffer += (((unsigned long)TMR1H_U1&0xffff)<<8) | (unsigned long)TMR1L_U1; 
    }
    ad = buffer>>3;              //结果除以8
    */
    rdfromIIC_U1();
    ad += (((unsigned long)TMR1H_U1&0xffff)<<8) | (unsigned long)TMR1L_U1;
    return ad;
      
}  

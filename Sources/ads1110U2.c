//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : ads1110U2.C
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,05,26
//* Description        : 本程序采用IIC通信方式； 是ADS1100,ADS1110的通用程序,用于系统总电压V2的计算
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "derivative.h" /* include peripheral declarations */

#define uch unsigned char
#define unint unsigned int

#define SCL2  PTP_PTP2
#define SDA2_DIR DDRP_DDRP3  //1--output  0---input
#define SDA2  PTP_PTP3

///// below for test
//#define SCL2  PTP_PTP4
//#define SDA2_DIR DDRP_DDRP5  //1--output  0---input
//#define SDA2  PTP_PTP5

unsigned char TMR1L_U2,TMR1H_U2,TMR2_U2;
//**********************************************************************
//* Function name:   delay10us
//* Description:     延时
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void delay10us() 
{
    unint j;
    for(j=0;j<5;j++);
}
//**********************************************************************
//* Function name:   start
//* Description:     开始
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void start (void)       //开始
{
    SDA2_DIR =1;
    asm("nop");
    SDA2=1;
    asm("nop");
    SCL2=1;
    delay10us();
    SDA2=0;
    asm("nop");  
    SCL2=0;    
    delay10us();
}
//**********************************************************************
//* Function name:   stop
//* Description:     结束
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void stop(void)             //结束
{ 
    
    
    SDA2_DIR =1;
    asm("nop");
    SDA2=0;
    
    SCL2=1;
    delay10us();
    SDA2=1;
    delay10us();
    SCL2=0;
    delay10us(); 
          
}
//**********************************************************************
//* Function name:   check
//* Description:     检查应答信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************    
uch check(void)    //  检查应答信号
{  
    uch ACK;
    
    SDA2_DIR =0;   //注意，此处方向变换应该在时钟为低的时候
    SCL2=0;
    delay10us();
    SCL2=1;    
    delay10us();             
    asm("nop");
    asm("nop");
    if (SDA2 )
    {
        ACK = 1;
    }
    else
    {
        ACK = 0;
    }    
    SCL2=0;    
    asm("nop");    
    return(ACK);
}
//**********************************************************************
//* Function name:   sendBYTE
//* Description:     发送一个字节
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************     
void sendBYTE(uch data)   //  发送一个字节
{
    uch bitcount=8;               //发送8位

    SDA2_DIR =1;
    do
    { 
        SCL2=0;              //在时钟大于4u秒期间写数据         
        if((data&0x80)==0x80)   
        {
            SDA2=1;         //写 1
        }
        else  
        {
            SDA2=0;        //写 0
        }  
        delay10us();     
        SCL2=1;
        delay10us();
        data=data<<1;
        bitcount--;
    } while(bitcount);
    SCL2=0;
      
}   
//**********************************************************************
//* Function name:   reciveBYTE
//* Description:     接受一个字节
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
uch reciveBYTE(void)             //接受一个字节
{
    uch temp1=0;
    uch bitcount1=8;

    SDA2_DIR =0;
    asm("nop");
    asm("nop");
    asm("nop");
    do
    { 
        SCL2=0;              //在时钟大于4u秒期间读数据
        delay10us();
        SCL2=1;
        delay10us();  
        if(SDA2)                //读 1
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
    SCL2=0;
    asm("nop");
    return(temp1);
}  
//**********************************************************************
//* Function name:   ack
//* Description:     发送连续读信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************    
void ack(void)          //  发送连续读信号
{ 
    SDA2_DIR =1; 
    SDA2=0;  
    SCL2=0;
    delay10us();
    SCL2=1;
    delay10us();
    SCL2=0;
    delay10us();
}
//**********************************************************************
//* Function name:   nack
//* Description:     发送不连续读信号
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************     
void nack(void)        //  发送不连续读信号
{ 
    
    SDA2_DIR =1;
    SDA2=1; 
    asm("nop"); 
    SCL2=1;
    delay10us();
    SDA2=0; 
    SCL2=0;
    delay10us();
    
}  
//**********************************************************************
//* Function name:   wrtoIIC
//* Description:     写器件地址和配置字
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************   
void wrtoIIC(uch data)     //写器件地址和配置字
{ 
    uch i;

    i =20;
    start();               //开始写
    sendBYTE(0x90);         //写器件地址（写）       
    do
    {
      i--;
    }while(check()&&(i>0));        //等待应答   
     
    sendBYTE(data);      //写配置字
    delay10us();
    
    i=20;
    do
    {
       i--;        
    }while(check()&&(i>0));        
    stop();            //结束写    
             
}

//**********************************************************************
//* Function name:   resetIIC
//* Description:     复位器件
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
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
//* Function name:   rdfromIIC
//* Description:     从ADS1100中读出数据
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void rdfromIIC(void)       //从ADS1100中读出数据
{   
    uch i;

    i =20;
    start();                  //开始读
    sendBYTE(0x91);           //写器件地址（读）
    do
    {
        i-- ;
    //}while(check());      //等待应答 
    }while(check()&&(i>0));            
    TMR1H_U2=reciveBYTE();     // 读高8位
    ack();                  //连续读
    TMR1L_U2=reciveBYTE();     //读低8位
    ack();                  //连续读
    TMR2_U2=reciveBYTE();      //读配置字
    nack();
  
    stop();                  //结束读
   
} 
//**********************************************************************
//* Function name:   GetU2adValue
//* Description:     获取绝缘通道电压AD值
//* EntryParameter : None
//* ReturnValue    : AD值
//**********************************************************************      
unsigned int GetU2adValue(void)
{   
    //unsigned char i;
    unsigned long buffer=0;
    unsigned int ad=0;

    wrtoIIC(0x84);
    /*           
    for(i=0;i<8;i++) 
    {      
        rdfromIIC(); 
        buffer += (((unsigned long)TMR1H_U2&0xffff)<<8) | (unsigned long)TMR1L_U2; 
    }
    ad = buffer>>3;              //结果除以8
    */
    rdfromIIC(); 
    ad += (((unsigned long)TMR1H_U2&0xffff)<<8) | (unsigned long)TMR1L_U2; 
    return ad;
      
}  

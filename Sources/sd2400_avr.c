//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : sd2400_avr.c
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,05,26
//* Description        : 该程序针对实时时钟芯片SD2400进行时间的设置和读取
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "derivative.h" /* include peripheral declarations */

#define  uchar unsigned char
#define  uint  unsigned int
#define  ulong unsigned long int
//数据sda的位设置
#define sda_in	    DDRJ &= 0xbf   	   //数据设置输入
#define sda_out	    DDRJ |= 0x40       //数据设置输出
#define sda_setb    PTJ |= 0x40        //数据拉高      
#define sda_clr     PTJ &= 0xbf        //数据拉低      
#define sda_r       (PTJ & 0x40)       //数据读取  
//时钟scl的位设置
#define scl_in	    DDRJ &= 0x7f       //时钟设置输入
#define scl_out	    DDRJ |= 0x80       //时钟设置输出
#define scl_setb    PTJ |= 0x80        //时钟拉高      
#define scl_clr     PTJ &= 0x7f        //时钟拉低      
#define scl_r       (PTJ & 0x80)       //时钟读取 
//===============
#define true  1
#define false 0
//===============
unsigned char CurrentTime[7];//

void WriteTimeOn(void);
void WriteTimeOff(void);
//====================================================================
/*延时子程序*/
/*
void delay_ms(uint time)    	       //11.0592M,time=1表示延时1ms
{
    uint i;
    for(;time>0;time--)
    for(i=0;i<1571;i++);
    asm("nop");
    asm("nop");
    asm("nop");
}
*/
//**********************************************************************
//* Function name:   delay_1us
//* Description:     延时
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void delay_1us(void)        	       //11.0592M, 1us延时函数
{
    asm("nop");
}
//**********************************************************************
//* Function name:   delay_us
//* Description:     延时
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void delay_us(uint time)     	       //11.0592M, Nus延时函数
{
    uint i;
    for (i=0;i<time;i++)
    asm("nop");
}  
//=====================================================================  
//**********************************************************************
//* Function name:   I2CStart
//* Description:     开启SD2400的I2C总线
//* EntryParameter : None
//* ReturnValue    : true， false
//**********************************************************************
uchar I2CStart(void)
{
    sda_out;
  	scl_out;
  	delay_1us();
      	sda_setb;	
  	scl_setb;	
  	delay_us(5);
  	sda_in;
  	delay_us(5);
  	if(!sda_r)return false;		//SDA线为低电平则总线忙,退出
  	sda_out;
  	delay_1us();
  	sda_clr;	
  	delay_us(10);
  	sda_in;    	
  	delay_us(10);
  	while(sda_r)return false;	//SDA线为高电平则总线出错,退出
  	scl_clr;	
  	delay_us(5);
  	return true;
}
//**********************************************************************
//* Function name:   I2CStop
//* Description:     关闭SD2400的I2C总线
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void I2CStop(void)
{
    scl_out;
  	sda_out;
  	delay_1us();
  	sda_clr;
  	delay_1us();
  	scl_clr;
  	delay_us(5);
  	scl_setb;
  	delay_us(2);
  	sda_setb;
}
//**********************************************************************
//* Function name:   I2CAck
//* Description:     发送 ACK
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void I2CAck(void)
{	
    scl_out;
  	sda_out;
  	delay_1us();
  	sda_clr;	
  	delay_1us();
  	scl_clr;	
  	delay_us(5);
  	scl_setb;	
  	delay_us(5);
  	scl_clr;	
}
//**********************************************************************
//* Function name:   I2CNoAck
//* Description:     发送NO ACK
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void I2CNoAck(void)
{	
    scl_out;
  	sda_out;
  	delay_1us();
  	sda_setb;	
  	delay_1us();
  	scl_clr;	
  	delay_us(5);
  	scl_setb;	
  	delay_us(5);
  	scl_clr;	
}
//**********************************************************************
//* Function name:   I2CWaitAck
//* Description:     读取ACK信号
//* EntryParameter : None
//* ReturnValue    : 返回为:1=有ACK,0=无ACK
//**********************************************************************
uchar I2CWaitAck(void) 			 //返回为:1=有ACK,0=无ACK
{
  	uchar errtime=255;
  	
  	scl_out;
  	sda_in;
  	delay_1us();
  	scl_clr;	
  	delay_us(5);
  	scl_setb;	
  	delay_1us();
  	sda_in;
  	delay_1us();
  	while(sda_r)	
  	{
    		errtime--;
    		delay_1us();
    		if(!errtime)
    		{
        		delay_us(10);
        		scl_clr;
        		return false;
        }
  	}
  	scl_clr;	
  	return true;
}
//**********************************************************************
//* Function name:   I2CSendByte
//* Description:     MCU向SD2400发送一个字节//数据从高位到低位
//* EntryParameter : 命令字节
//* ReturnValue    : None
//**********************************************************************              
void I2CSendByte(unsigned char demand)		 //数据从高位到低位
{
  	uchar bd=8; 
  	                                                       
  	sda_out;
  	scl_out;
		while(bd--)
		{
  			scl_clr;  
  			delay_1us();
  			if(demand&0x80)
  			{
  			    sda_setb;
  			}
  			else
  			{
  			    sda_clr;
  			}
  			demand<<=1;
  			delay_us(3);
  			scl_setb;
  			delay_us(3);
		}
		scl_clr;	      
}
//**********************************************************************
//* Function name:   I2CReceiveByte
//* Description:     MCU从SD2400读入一字节//数据从高位到低位//
//* EntryParameter : None
//* ReturnValue    : 一个字节
//**********************************************************************
uchar I2CReceiveByte(void) 		//数据从高位到低位//
{
  	uchar bl=8;
  	uchar ddata=0;
  	
  	scl_out;
  	delay_1us();
  	delay_1us();
  	sda_in;			 	//c51中为SDA=1;端口切换为输入状态！！
  	delay_1us();
  	while(bl--)
  	{
        ddata<<=1;              //数据从高位开始读取
    		delay_1us();
    		scl_clr;
    		delay_us(5);	        //从高位开始 ddata|=SDA;ddata<<=1
    		scl_setb;
    		delay_us(5);	
    		if(sda_r)
    		{
    			  ddata|=0x01;
    		}  		  		
  	}
  	scl_clr;
  	return ddata;
}
//**********************************************************************
//* Function name:   I2CReadDate
//* Description:     读SD2400实时数据寄存器
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void I2CReadDate(void)
{
  	unsigned char n;
  	
  	I2CStart();
  	I2CSendByte(0x65); 
  	I2CWaitAck();
  	for(n=0;n<7;n++)
  	{
    		CurrentTime[n]=I2CReceiveByte()&0x7f;
    		if (n!=6)        	 //最后一个数据不应答
    		{
    			  I2CAck();
    		}
  	}
  	I2CNoAck();
  	delay_1us();
  	I2CStop();
}
//**********************************************************************
//* Function name:   WriteTimeOn
//* Description:     写SD2400允许程序
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void WriteTimeOn(void)
{		
  	I2CStart();
  	I2CSendByte(0x64);      
  	I2CWaitAck();   
    I2CSendByte(0x10);		//设置写地址10H      
  	I2CWaitAck();	
  	I2CSendByte(0x80);		//置WRTC1=1      
  	I2CWaitAck();
  	I2CStop(); 
  	
  	I2CStart();
  	I2CSendByte(0x64);      
  	I2CWaitAck();   
    I2CSendByte(0x0F);		//设置写地址0FH      
  	I2CWaitAck();	
  	I2CSendByte(0x84);		//置WRTC2,WRTC3=1      
  	I2CWaitAck();
  	I2CStop(); 
	
}
//**********************************************************************
//* Function name:   I2CWriteDate
//* Description:     写SD2400实时数据寄存器
//* EntryParameter : 数据地址指针
//* ReturnValue    : None
//**********************************************************************
void I2CWriteDate(unsigned char *pSecDa)
{		

    WriteTimeOn();

  	I2CStart();
  	I2CSendByte(0x64);      
  	I2CWaitAck();   
    I2CSendByte(0x00);		//设置写起始地址      
  	I2CWaitAck();	
  	I2CSendByte(*pSecDa);		// second     
  	I2CWaitAck();	
  	I2CSendByte(*(pSecDa+1));		//minute      
  	I2CWaitAck();	
  	I2CSendByte(0x80|*(pSecDa+2));		//hour ,二十四小时制     
  	I2CWaitAck();	
  	I2CSendByte(*(pSecDa+3));		//week      
  	I2CWaitAck();	
  	I2CSendByte(*(pSecDa+4));		//day      
  	I2CWaitAck();	
  	I2CSendByte(*(pSecDa+5));		//month      
  	I2CWaitAck();	
  	I2CSendByte(*(pSecDa+6));		//year      
  	I2CWaitAck();	
  	I2CStop();

  	I2CStart();
  	I2CSendByte(0x64);      
  	I2CWaitAck();   
    I2CSendByte(0x12);		//设置写起始地址      
  	I2CWaitAck();		
    I2CSendByte(0x00);		//清零数字调整寄存器      
  	I2CWaitAck();        
  	I2CStop();  
  	
  	WriteTimeOff();      
}
//**********************************************************************
//* Function name:   WriteTimeOff
//* Description:     写SD2400禁止程序
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void WriteTimeOff(void)
{		
  	I2CStart();
  	I2CSendByte(0x64);
  	I2CWaitAck();   
    I2CSendByte(0x0F);		//设置写地址0FH      
  	I2CWaitAck();	
  	I2CSendByte(0x0) ;		//置WRTC2,WRTC3=0      
  	I2CWaitAck();
  	I2CSendByte(0x0) ;		//置WRTC1=0(10H地址)      
  	I2CWaitAck();
  	I2CStop(); 
}


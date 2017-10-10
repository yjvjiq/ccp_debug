//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : m95m02.C
//* Author             : Kong XiangYu
//* Version            : V1.0.0
//* Start Date         : Mar. 14, 2015
//* Description        : 该程序针对芯片m95m02进行读写，该芯片存储系统的历史记录信息，最多800条记录
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

#include "derivative.h" /* include peripheral declarations */
#include "BMS20.h"

//**********************************************************************
//* Function name:   delayXusAtM95
//* Description:     m95m02延时
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void delayXusAtM95(unsigned int x) 
{
    unsigned int i; 
    for (i=0;i<x;i++);
}
//**********************************************************************
//* Function name:   InitialAtM95M02
//* Description:     M95M02初始化
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void InitialAtM95M02(void)
{
    SPI0CR1 &= 0xbf;    //禁止SPI0模式
    DDRS |= 0xe4;     //设置CS SCK, SI,RES方向为输出,1110 0100 
    DDRS &= 0xef;    //SO方向默认为输入1110 1111 
 
    PTS |= 0x84;  // 设置HOLD位为高电平，芯片不处于暂停状态1000 0010
    delayXusAtM95(50);

}
//**********************************************************************
//* Function name:   cs_up
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void cs_up()
{
    PTS |= 0x04; //片选为高
}   
//**********************************************************************
//* Function name:   cs_down
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void cs_down()
{
    PTS &= 0xfb;
}
//=============================================================================================
//"Clock Contrl .
//=============================================================================================
//**********************************************************************
//* Function name:   sck_up
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void sck_up()
{
    PTS |= 0x40;//0100 0000 PS6=1
}
//**********************************************************************
//* Function name:   sck_down
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void sck_down()
{
    PTS &= 0xbf;//1011 1111 PS6=0
}
//=============================================================================================
//"Data Out Contrl .
//=============================================================================================
//**********************************************************************
//* Function name:   si_up
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void si_up()
{
    PTS |= 0x20; //0010 0000 PS5=0 SI(单片机SPI输出)
}
//**********************************************************************
//* Function name:   si_down
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void si_down()
{
    PTS &= 0xdf; // 1101 1111 PS5=1 SI（单片机SPI输出)
}

//**********************************************************************
//* Function name:   Byte_Out
//* Description:     "EXIT:SCK=1;CS=0; 单片机往EEPROM写一位，上升沿，在输出指令的时候用.
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Byte_Out(uchar bb)
{
    uchar flag;
	  uchar i;
	
	  for(i=0;i<8;i++)
	  {

    		flag=bb&0x80;		
    		if(flag==0x80)		
    		{
    			  si_up();
    		}
    		else
    		{
    			  si_down();
    		}
 
    		sck_up();		//"CLK上升沿,将数据一位数据送入器件EEPROM，上升沿写入一位
    
    		sck_down();		//"时钟下降
    
    		bb<<=1;
	  }
	
}
//**********************************************************************
//* Function name:   Byte_In
//* Description:     //"EXIT:SCK=1;CS=0; 单片机从EEPROM里读一位.下降沿有效，读ROM的时候用
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
uchar Byte_In()
{
  	uchar x=0;
  	uchar i;
  	uchar flag;
  	for(i=0;i<8;i++)
  	{
    		x<<=1;	
    		flag= PTS & 0x10;		//读取SO的数据
    		if(flag==0x10)
    		{
    			x++;
    		}
    	
    		delayXusAtM95(15);
    		sck_up();
    	
    		sck_down();		//"CLK下降沿,使器件送出一位到线上
    		delayXusAtM95(15); 
    
    	
  	}
  	return(x);
}
//**********************************************************************
//* Function name:   M95_Write_Enable
//* Description:     M95写使能(WREN)
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void M95_Write_Enable() 
{
    cs_down();
    delay_1us();//必须加
   	
    Byte_Out(0x06);
    delay_1us(); //必须加
    delayXusAtM95(5); 			
    cs_up();
   delay_1us();//必须加
  
}
//**********************************************************************
//* Function name:   M95_Write_Disable
//* Description:     M95写不使能(WRDI)
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void M95_Write_Disable() 
{
    cs_down();	
    Byte_Out(0x04);
    delayXusAtM95(5); 			
    cs_up();
    delayXusAtM95(5);
}
//**********************************************************************
//* Function name:   M95_Read_Register
//* Description:     M95读寄存器状态(RDSR)
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
uchar M95_Read_Register(void) 
{
    uchar bb;
    cs_down();
    delayXusAtM95(5);	
    Byte_Out(0x05);
  
    bb=Byte_In();
   			
    cs_up();

    return(bb); 
  
}
//**********************************************************************
//* Function name:   M95_Write_Register
//* Description:     M95写寄存器状态(WRSR)
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void M95_Write_Register( uchar R_status) 
{
    M95_Write_Enable();//使能写 
    //while(M95_Read_Register()&0x02);
    
    cs_down();	
    Byte_Out(0x01);
    Byte_Out(R_status);			
    cs_up();
    delayXusAtM95(50);
   
  
}
//**********************************************************************
//* Function name:   M95_Write_Addr
//* Description:     M95写24位地址  //注意：写额外扩展的地址时A10=1，也就是0x000004xx
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void M95_Write_Addr(ulong addr) 
{

    uchar i;
    ulong flag;    	
    for(i=0;i<16;i++)		
    {
    
        flag=addr&0x00800000;	
        if(flag==0x00800000)	
        {
        	  si_up();
        }
        else
        {
        	  si_down();
        }
      
        sck_up();		//"CLK上升沿,将数据一位数据送入器件
        delayXusAtM95(5);
        sck_down();		//"CLK下降
       
        addr<<=1;
    }
    
    for(i=0;i<8;i++)		
    {
        
        flag=addr&0x00800000;	
        if(flag==0x00800000)	
        {
        	  si_up();
        }
        else
        {
        	  si_down();
        }
       
        sck_up();		//"CLK上升沿,将数据一位数据送入器件
       
        delayXusAtM95(5);
        sck_down();		//"CLK下降
        addr<<=1;
    }

     
}

//**********************************************************************
//* Function name:   M95_Read_Memory
//* Description:     M95读内存（READ)
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void M95_Read_Memory(unsigned long ba,uchar *str,unsigned int count) 
{
    while(M95_Read_Register()&0x01);
    cs_down();
   
    delayXusAtM95(5);//必须加延时	
    Byte_Out(0x03);
   
    M95_Write_Addr(ba);
 
    while(count!=0)                         //"read COUNT byte
    {
        *str = Byte_In();
        str++;
        count--;
        delayXusAtM95(10); //必须得加
    }

    cs_up();

  
}
//**********************************************************************
//* Function name:   M95_Write_Memory
//* Description:     M95写内存(WRITE)
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
/////////////////////////////////
//void M95_Write_Memory(ulong ba,uchar *str,unsigned char count) 
void M95_Write_Memory(ulong ba,uchar *str,unsigned int count) 
{
   
    M95_Write_Enable(); //使能写0x06 0b0000 0110
    while(M95_Read_Register()&0x01); 

    cs_down();
    delayXusAtM95(5);
    Byte_Out(0x02);
 
    M95_Write_Addr(ba); //
   
    while(count!=0)                         //"read COUNT byte
    {
        Byte_Out(*str);
       
        str++;
        count--;
       
    }
    
    //加延时//
    cs_up();
   
    while(M95_Read_Register()&0x01); //说明还在写
  
}

//**********************************************************************
//* Function name:   M95_Read_IP_Memory
//* Description:     M95读Read Identification Page内存（RDID)
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
//void M95_Read_IP_Memory(ulong ba,uchar *str,unsigned char count) 
void M95_Read_IP_Memory(ulong ba,uchar *str,unsigned int count) 
{
    cs_down();	
    Byte_Out(0x83);
    M95_Write_Addr(ba); //注意地址的格式，第十位必须为0
    while(count!=0)                         //"read COUNT byte
    {
        *str = Byte_In();
        str++;
        count--;
    }
    //加延时//
    cs_up();
  
}
//**********************************************************************
//* Function name:   M95_Write_IP_Memory
//* Description:     M95写Read Identification Page内存(WRID)
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void M95_Write_IP_Memory(ulong ba,uchar *str,unsigned char count) 
{
    M95_Write_Enable(); //不需要使能写 
    cs_down();	
    Byte_Out(0x82);
    M95_Write_Addr(ba); //注意地址的格式，第十位必须为0
    while(count!=0)                         //"read COUNT byte
    {
        *str = Byte_In();
        str++;
        count--;
    }
    //加延时//
    cs_up();
  
}
//**********************************************************************
//* Function name:   M95_Read_Lock
//* Description:     M95读Read Lock Status（RDLS)
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
uchar M95_Read_Lock(ulong ba) 
{
    uchar bb;
    cs_down();	
    Byte_Out(0x83);
    M95_Write_Addr(ba); //注意地址的格式，第十位必须为1
    bb=Byte_In();
    cs_up();
    return(bb);
  
}
//**********************************************************************
//* Function name:   M95_Write_Lock
//* Description:     M95锁定ID只读(LID)
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void M95_Write_Lock( uchar R_status,ulong ba) 
{
    M95_Write_Enable();//使能写 

    cs_down();	
    Byte_Out(0x82);
    M95_Write_Addr(ba);
    Byte_Out(R_status);	//注意：xxxx xx1x		
    cs_up();

}

//**********************************************************************
//**************************** the end **********************************
//**********************************************************************
//**********************************************************************
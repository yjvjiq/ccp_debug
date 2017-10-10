//******************A301长安主板温度检测*********************************
//***开始时间：2013年4月15日*********************************************
/****作者：fencer*********************************************
 * FileName:        DS18B20.C
 * Dependencies:    
 * Processor:       Freescale MC2S12XEP100
 * Compiler:       	CodeWarriorV5.0 or higher
 * Linker:          MPLINK 03.70.00 or higher
 * Company:         DALASS 
 ********************************************************************** */
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "BMS20.h" 

#define uchar unsigned char
#define uint unsigned int
#define DQ_set    PORTA |= 0x20        //数据拉高      
#define DQ_clr    PORTA &= 0xdf       //数据拉低 
/******************************************
此延时函数针对的是12Mhz的晶振
delay(0):延时518us 误差:518-2*256=6
delay(26):延时7us   （原帖写"5us"是错的）
delay(98):延时25us    误差:25-20=5
delay(178):延时45us    误差:45-40=5
delay(820):延时205us 误差:205-200=5
delay(1620):延时405us 误差:405-400=5
*******************************************/
void delay18b20(unsigned int i) 
{
  int j,k;

  //for(j=i;j>0;j--)
  //    for(k=5;k>0;k--); 
  for(j=i;j>0;j--)
      for(k=5;k>0;k--); 
 
}

/*****************DS18B20******************/
void Init_Ds18b20(void)     //DS18B20初始化send reset and initialization command
{
    /*
    uchar presence=1;
    
    while(presence)
    {  
        DDRE |= 0x01;
        delay18b20(5);
        DQ_set;                     //DQ复位,不要也可行。
        delay18b20(10);                  //稍做延时
        DQ_clr;                    //单片机拉低总线
        delay18b20(750);                //精确延时，维持至少480us
        DQ_set;
        DDRE &= 0xFE;                  //释放总线，即拉高了总线
        delay18b20(80);
         
        if(PORTE&0x01)
            presence=1;
        else
            presence=0;
        delay18b20(650); //此处延时有足够,确保能让DS18B20发出存在脉冲
        delay18b20(650); 
    }
    */
    DDRA |= 0x20;

    DQ_clr; 
    //delay18b20(750);                //精确延时，维持至少480us
    delay18b20(200);    //500us
    DQ_set;
    delay18b20(20);    //50us

}

uchar Read_One_Byte()       //读取一个字节的数据read a byte date
                            //读数据时,数据以字节的最低有效位先从总线移出
{
    uchar i   = 0;
    uchar dat = 0;
    
    for(i=8;i>0;i--)
    {
       DDRA |= 0x20;
       delay18b20(1);
       DQ_clr;                  //将总线拉低，要在1us之后释放总线
                               //单片机要在此下降沿后的15us内读数据才会有效。
       delay18b20(1);                 //至少维持了1us,表示读时序开始
       dat >>= 1;               //让从总线上读到的位数据，依次从高位移动到低位。
       DQ_set;                  //释放总线，此后DS18B20会控制总线,把数据传输到总线上
       delay18b20(3);
       DDRA &= 0xdf;
       delay18b20(10);                 //延时7us,此处参照推荐的读时序图，尽量把控制器采样时间放到读时序后的15us内的最后部分
       if(PORTA&0x20)                   //控制器进行采样
       {
        dat |= 0x80;            //若总线为1,即DQ为1,那就把dat的最高位置1;若为0,则不进行处理,保持为0
       }        
       delay18b20(30);               //此延时不能少，确保读时序的长度60us。
    }
    return (dat);
}

void Write_One_Byte(uchar dat)
{
    uchar i = 0;
    uchar temp;
    for(i=8;i>0;i--)
    {
        DDRA |= 0x20;
        delay18b20(1);
        DQ_clr;                        //拉低总线
        delay18b20(1);                       //至少维持了1us,表示写时序(包括写0时序或写1时序)开始
        temp = dat&0x01;                 //从字节的最低位开始传输
        if(temp==1)                              //指令dat的最低位赋予给总线,必须在拉低总线后的15us内,
            DQ_set;                              //因为15us后DS18B20会对总线采样。
        delay18b20(30);                     //必须让写时序持续至少60us
        DQ_set;                        //写完后,必须释放总线,
        dat >>= 1;
        delay18b20(3);
    }
}

int get_tmp()                   //获取温度get the temperature
{
    uchar a,b;
    int  temp;
   
    //DisableInterrupts;
    Init_Ds18b20();                //初始化
    delay18b20(30);
    Write_One_Byte(0xcc);          //忽略ROM指令
    Write_One_Byte(0x44);          //温度转换指令
    
    Init_Ds18b20();                 //初始化
    delay18b20(30);
    Write_One_Byte(0xcc);          //忽略ROM指令
    Write_One_Byte(0xbe);          //读暂存器指令
    delay18b20(30);
    a = Read_One_Byte();           //读取到的第一个字节为温度LSB
    b = Read_One_Byte();           //读取到的第一个字节为温度MSB

    temp = b&0x0f;                      //先把高八位有效数据赋于temp
    temp <<= 8;                    //把以上8位数据从temp低八位移到高八位
    temp = temp|a;                //两字节合成一个整型变量
    if((b&0x0f)>=0x08)
    {
      temp=temp+1-4095;      
    }
    temp=temp*6.25;              //得到真实十进制温度值
    
    //EnableInterrupts;            //因为DS18B20可以精确到0.0625度
                                //所以读回数据的最低位代表的是0.0625度                            
    return temp;
}
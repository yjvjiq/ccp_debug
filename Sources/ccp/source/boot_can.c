/*******************************************************************************

  File Name   : boot_can.c
  Date        : 14.08.2001
  Version     : 1.0
  Desciption  : free CAN driver for CCP without using interrupts

*******************************************************************************/


// -----------------------------------------------------------------------------
// INCLUDE FILES
// -----------------------------------------------------------------------------
//#include <iod60.h>               // standard HC12 IO
#include "ccppar.h"              // CPP config file
#include "boot_can.h"            // CAN driver

#include <mc9s12xep100.h>
#include <hidef.h>
//#include "derivative.h" /* include peripheral declarations */

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// VARIABLES and Structs
// -----------------------------------------------------------------------------
unsigned int g_ccp_dto_id;              // global DTO-ID
unsigned int g_ccp_cro_id;              // global CRO-ID
unsigned char send_buf = 0;



struct can_msg     //发送报文的结构体
{
    unsigned int id;
    Bool RTR;
    unsigned char tx_data[8];
    unsigned char rx_data[8];
    unsigned char len;
    unsigned char prty;
};

struct can_msg msg; 
/*************************************************************/
/*                        初始化CAN0                         */
/*************************************************************/
void ccpBootInit (int cro_id, int dto_id)
{
  g_ccp_dto_id = dto_id;       // handover IDs (CRO, DTO)
  g_ccp_cro_id = cro_id;
   
  if(CAN0CTL0_INITRQ==0)       // 查询是否进入初始化状态   
    CAN0CTL0_INITRQ =1;        // 进入初始化状态

  while (CAN0CTL1_INITAK==0);  //等待进入初始化状态

  CAN0BTR0_SJW = 0;            //设置同步
  CAN0BTR0_BRP = 7;            //设置波特率  
  CAN0BTR1 = 0x1c;             //设置时段1和时段2的Tq个数 ,总线频率为250kb/s

// 关闭滤波器                                  
  CAN0IDMR0 = 0xFF;
  CAN0IDMR1 = 0xFF;
  CAN0IDMR2 = 0xFF;
  CAN0IDMR3 = 0xFF;
  CAN0IDMR4 = 0xFF;
  CAN0IDMR5 = 0xFF;
  CAN0IDMR6 = 0xFF;
  CAN0IDMR7 = 0xFF; 

  CAN0CTL1 = 0xC0;             //使能MSCAN模块,设置为一般运行模式、使用总线时钟源 

  CAN0CTL0 = 0x00;             //返回一般模式运行

  while(CAN0CTL1_INITAK);      //等待回到一般运行模式

  while(CAN0CTL0_SYNCH==0);    //等待总线时钟同步

  CAN0RIER_RXFIE = 0;          //禁止接收中断    
}
int ccpBootTransmitCrmPossible( void ) {
//  return ((msCAN12.CTFLG & TXE0) == 1);        // return 1 if so

  do
  {
    // 寻找空闲的缓冲器
    CAN0TBSEL=CAN0TFLG;
    send_buf=CAN0TBSEL;
  }  
  while(!send_buf);
  return(TRUE);
}

/*************************************************************/
/*                       CAN0发送                            */
/*************************************************************/
int ccpBootTransmitCrm (unsigned char *array_msg)
{
  msg.id = g_ccp_dto_id;

  if(msg.len > 8)
    return(FALSE);

  // 检查总线时钟
  if(CAN0CTL0_SYNCH==0)
    return(FALSE);

  send_buf = 0;
  do
  {
    // 寻找空闲的缓冲器
    CAN0TBSEL=CAN0TFLG;
    send_buf=CAN0TBSEL;
  }
  
  while(!send_buf); 
 
  // 写入标识符
  CAN0TXIDR0 = (unsigned char)(msg.id>>3);
  CAN0TXIDR1 = (unsigned char)(msg.id<<5);
  
    if(msg.RTR)
    // RTR = 阴性
    CAN0TXIDR1 |= 0x10;
    
  // 写入数据
  CAN0TXDSR0 = *array_msg;
  CAN0TXDSR1 = *(array_msg+1);
  CAN0TXDSR2 = *(array_msg+2);
  CAN0TXDSR3 = *(array_msg+3);
  CAN0TXDSR4 = *(array_msg+4);
  CAN0TXDSR5 = *(array_msg+5);
  CAN0TXDSR6 = *(array_msg+6);
  CAN0TXDSR7 = *(array_msg+7);
     
  // 写入数据长度
  CAN0TXDLR = msg.len;

  
  // 写入优先级
  CAN0TXTBPR = msg.prty;
  
  // 清 TXx 标志 (缓冲器准备发送)
  CAN0TFLG = send_buf;
  
  return(TRUE);  
}
/*************************************************************/
/*                       CAN0接收                            */
/*************************************************************/
int ccpBootReceiveCro (unsigned char *array_msg)
{

  // 检测接收标志
  if(!(CAN0RFLG_RXF))
    return(FALSE);
  
  // 检测 CAN协议报文模式 （一般/扩展） 标识符
  if(CAN0RXIDR1_IDE)
    // IDE = Recessive (Extended Mode)
    return(FALSE);

  // 读标识符
  msg.id = (unsigned int)(CAN0RXIDR0<<3) | 
            (unsigned char)(CAN0RXIDR1>>5);
  
  if(CAN0RXIDR1&0x10)
    msg.RTR = TRUE;
  else
    msg.RTR = FALSE;
 
  // 读取数据长度 
  msg.len = CAN0RXDLR;
  
 *array_msg = CAN0RXDSR0;
 *(array_msg+1) = CAN0RXDSR1;
 *(array_msg+2) = CAN0RXDSR2;
 *(array_msg+3) = CAN0RXDSR3;
 *(array_msg+4) = CAN0RXDSR4;
 *(array_msg+5) = CAN0RXDSR5;
 *(array_msg+6) = CAN0RXDSR6;
 *(array_msg+7) = CAN0RXDSR7;
   

  // 清 RXF 标志位 (缓冲器准备接收)
  CAN0RFLG = 0x01;
  if (msg.id == g_ccp_cro_id) 
    return(TRUE);            // if correctly received, return 1
    //return(TRUE);     
}



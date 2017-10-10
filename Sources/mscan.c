//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : mscan.C
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,06,02
//* Description        : 该程序针对9s12xep100的几个CAN模块进行初始化和输入输出处理
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include <hidef.h>      /* common defines and macros */
#include <string.h>
#include "derivative.h" /* include peripheral declarations */
#include "mscan.h"

//**********************************************************************
//* Function name:   MSCANInit
//* Description:     MSCAN Peripheral Initialization CAN0--车载  CAN1--充电 CAN2--内部
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void MSCANInit(void)
{
    //char sj,p;
    //char t_seg1, t_seg2;
    
    /*
    if (!CAN0CTL0&0x01)                  
        CAN0CTL0 =0x01;// Active MSCAN initialization mode    
    while (!CAN0CTL1&0x01);// Wait until the MSCAN is in initialization mode  
    */
    
    if (!CAN1CTL0&0x01)                  
        CAN1CTL0 =0x01;// Active MSCAN initialization mode    
    while (!CAN1CTL1&0x01);// Wait until the MSCAN is in initialization mode  
    
    if (!CAN2CTL0&0x01)                  
        CAN2CTL0 =0x01;// Active MSCAN initialization mode    
    while (!CAN2CTL1&0x01);// Wait until the MSCAN is in initialization mode  
    
        
    /*
    sj = (SJW-1)<<6;
    p = (BRP-1);    
    // Configures SJW and Tq clock Baud Rate Prescaler
    CAN0BTR0 = (sj|p);    
    t_seg1 = (TSEG1-1);
    t_seg2 = (TSEG2-1)<<4;    
    // Configure Time Segment 1 and 2, and one Sample per bit
    CAN0BTR1 = (t_seg1 | t_seg2);
    */    
    CAN0BTR0 = 0x03;           // 250k波特率, 16M bus clock
    CAN0BTR1 = 0x58;    
         
    //CAN0BTR0 = 0x01;           // 500k波特率, 16M bus clock
    //CAN0BTR1 = 0x1c; 
    
    CAN1BTR0 = 0x03;           // 250k波特率, 16M bus clock
    CAN1BTR1 = 0x58;  
    
    //CAN1BTR0 = 0x01;           // 500k波特率, 16M bus clock
    //CAN1BTR1 = 0x1c;   
    
    CAN2BTR0 = 0x03;           // 250k波特率, 16M bus clock
    CAN2BTR1 = 0x58;      
       
    //CAN0IDAC = 0x20; //ID 8位接收模式  // Disables all the Filters  
    CAN1IDAC = 0x20; //ID 8位接收模式  
    CAN2IDAC = 0x20; //ID 8位接收模式  
    
                             
    CAN0IDMR0 = 0xFF;
    CAN0IDMR1 = 0xFF;
    CAN0IDMR2 = 0xFF;
    CAN0IDMR3 = 0xFF;
    CAN0IDMR4 = 0xFF;
    CAN0IDMR5 = 0xFF;
    CAN0IDMR6 = 0xFF;
    CAN0IDMR7 = 0xFF;
   
    CAN1IDMR0 = 0xFF;
    CAN1IDMR1 = 0xFF;
    CAN1IDMR2 = 0xFF;
    CAN1IDMR3 = 0xFF;
    CAN1IDMR4 = 0xFF;
    CAN1IDMR5 = 0xFF;
    CAN1IDMR6 = 0xFF;
    CAN1IDMR7 = 0xFF;
    
    CAN2IDMR0 = 0xFF;
    CAN2IDMR1 = 0xFF;
    CAN2IDMR2 = 0xFF;
    CAN2IDMR3 = 0xFF;
    CAN2IDMR4 = 0xFF;
    CAN2IDMR5 = 0xFF;
    CAN2IDMR6 = 0xFF;
    CAN2IDMR7 = 0xFF;
  
    // Enable MSCAN and normal operation and select the bus clock as MSCAN clock source
    //CAN0CTL1 = 0xC0;
    // Enable MSCAN and normal operation and select the oscillator clock as MSCAN clock source

    CAN0CTL1 = 0x80;    //16M oscillator  as the bus clock
    CAN1CTL1 = 0x80;    //16M oscillator  as the bus clock
    CAN2CTL1 = 0x80;    //16M oscillator  as the bus clock
      
    CAN0CTL0 = 0x00;// Active MSCAN Normal Operation
    CAN1CTL0 = 0x00;
    CAN2CTL0 = 0x00;
      
    while(CAN0CTL1&0x01);// Wait until the MSCAN operates normally
    while(CAN1CTL1&0x01);
    while(CAN2CTL1&0x01);
      
    while(!(CAN0CTL0&0x10));// Wait until MSCAN is synchronized to the CAN bus
    while(!(CAN1CTL0&0x10));
    while(!(CAN2CTL0&0x10));
          
    CAN0RIER = 0x01;//Enable receiver interrupt所有CAN都中断接收
    CAN1RIER = 0x01;
}

//**********************************************************************
//* Function name:   TurnOnCan2Rx
//* Description:     断开开关DO2
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void TurnOnCan2Rx(void)//
{
     CAN2RIER |= 0x01;
}
//**********************************************************************
//* Function name:   TurnOffCan2Rx
//* Description:     断开开关DO2
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void TurnOffCan2Rx(void)//
{
     CAN2RIER &= 0xfe;
}

//**********************************************************************
//* Function name:   MSCAN0SendMsg
//* Description:     MSCAN0 Send Message Routine
//* EntryParameter : CAN 报文信息
//* ReturnValue    : TRUE:发送成功 FALSE:失败
//**********************************************************************
Bool MSCAN0SendMsg(struct can_msg msg)
{
    unsigned char n_tx_buf, i;
    unsigned long pp=0;
   
    if(!(CAN0CTL0&0x10))// Checks synchronization to CAN bus
        return(FALSE);
   
    n_tx_buf = 0;
   
    do
    {    
        // Looks for a free buffer
        n_tx_buf =  CAN0TFLG;
        CAN0TBSEL=n_tx_buf;
        n_tx_buf=CAN0TBSEL;
        i++;
        if(i>=200)
            return(FALSE);
    }while(!n_tx_buf); 
     
     
   // CAN0TIDR0 = (unsigned char)(msg.id>>3);// Write standard Identifier
   // CAN0TIDR1 = (unsigned char)(msg.id<<5);
    
    pp = msg.id>>15;//Write Extended Identifier
    CAN0TIDR0 = (unsigned char)(pp>>6);//Write Extended Identifier
    CAN0TIDR1 = ((unsigned char)(msg.id>>13)&0xe0) |  0x18 | ((unsigned char)(msg.id>>15)&0x07);
    CAN0TIDR2 = (unsigned char)(msg.id>>7);
    CAN0TIDR3 = (unsigned char)(msg.id<<1);
  
    //if(msg.RTR)
      // RTR=Recessive
    //  CAN0TIDR1 |= 0x10;
        
    for(i = 0; i < 8; i++)// Write Data Segment
        *((&CAN0TDSR0)+i) = msg.data[i];
        
    //CAN0TDLR = 8; // Write Data Length
    CAN0TDLR = msg.len;// Write Data Length 
      
    //CAN0TTBPR = msg.prty;// Write Priority
      
    CAN0TFLG = n_tx_buf;// Clear TXx Flag (buffer ready to transmission)
    
    return(TRUE);
    
}

//**********************************************************************
//* Function name:   MSCAN1SendMsg
//* Description:     MSCAN1 Send Message Routine
//* EntryParameter : CAN 报文信息
//* ReturnValue    : TRUE:发送成功 FALSE:失败
//**********************************************************************
Bool MSCAN1SendMsg(struct can_msg msg)
{
    unsigned char n_tx_buf, i;
    unsigned long pp=0;
    
    //if(msg.len > MAX_LEN)// Checks len validity
    //    return(FALSE);    
    if(!(CAN1CTL0&0x10))// Checks synchronization to CAN bus
        return(FALSE);
    
    n_tx_buf = 0;
    do
    {    
        // Looks for a free buffer
        n_tx_buf =  CAN1TFLG;
        CAN1TBSEL=n_tx_buf;
        n_tx_buf=CAN1TBSEL;
        i++;
        if(i>=200)
            return(FALSE);
    }while(!n_tx_buf);
    
    //CAN1TIDR0 = (unsigned char)(msg.id>>3);// Write standard Identifier
    //CAN1TIDR1 = (unsigned char)(msg.id<<5);
      
    pp = msg.id>>15;//Write Extended Identifier
    CAN1TIDR0 = (unsigned char)(pp>>6);//Write Extended Identifier
    CAN1TIDR1 = ((unsigned char)(msg.id>>13)&0xe0) |  0x18 | ((unsigned char)(msg.id>>15)&0x07);
    CAN1TIDR2 = (unsigned char)(msg.id>>7);
    CAN1TIDR3 = (unsigned char)(msg.id<<1);
    
    //if(msg.RTR)
      // RTR=Recessive
    //  CAN1TIDR1 |= 0x10;
       
    for(i = 0; i < 8; i++)// Write Data Segment
        *((&CAN1TDSR0)+i) = msg.data[i];
       
    CAN1TDLR = msg.len;// Write Data Length 
     
    //CAN1TTBPR = msg.prty;// Write Priority
     
    CAN1TFLG = n_tx_buf;// Clear TXx Flag (buffer ready to transmission)
    
    return(TRUE);
    
}
//**********************************************************************
//* Function name:   MSCAN2SendMsg
//* Description:     MSCAN2 Send Message Routine
//* EntryParameter : CAN 报文信息
//* ReturnValue    : TRUE:发送成功 FALSE:失败
//**********************************************************************
Bool MSCAN2SendMsg(struct can_msg msg)
{
    unsigned char n_tx_buf, i;
    unsigned long pp=0;
    
    //if(msg.len > MAX_LEN)// Checks len validity
    //    return(FALSE);
    
    if(!(CAN2CTL0&0x10))// Checks synchronization to CAN bus
        return(FALSE);
    
    n_tx_buf = 0;
    do
    {    
        // Looks for a free buffer
        n_tx_buf =  CAN2TFLG;
        CAN2TBSEL=n_tx_buf;
        n_tx_buf=CAN2TBSEL;
        i++;
        if(i>=200)
            return(FALSE);
    }while(!n_tx_buf); 
    
    //CAN2TIDR0 = (unsigned char)(msg.id>>3);// Write standard Identifier
    //CAN2TIDR1 = (unsigned char)(msg.id<<5);
    
    pp = msg.id>>15;//Write Extended Identifier
    CAN2TIDR0 = (unsigned char)(pp>>6);//Write Extended Identifier
    CAN2TIDR1 = ((unsigned char)(msg.id>>13)&0xe0) |  0x18 | ((unsigned char)(msg.id>>15)&0x07);
    CAN2TIDR2 = (unsigned char)(msg.id>>7);
    CAN2TIDR3 = (unsigned char)(msg.id<<1);
    
    //if(msg.RTR)
    //    RTR=Recessive
    //  CAN2TIDR1 |= 0x10;
        
    for(i = 0; i < 8; i++)
        *((&CAN2TDSR0)+i) = msg.data[i];// Write Data Segment
       
    CAN2TDLR = 8; // Write Data Length  
    //CAN2TTBPR = msg.prty;// Write Priority
      
    CAN2TFLG = n_tx_buf;// Clear TXx Flag (buffer ready to transmission)
    
    return(TRUE);
   
}

//*********************************************************************
//*********************************************************************
//************************  end file  **********************************
//*********************************************************************



//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : mscan.h
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,06,02
//* Description        : 该程序针对9s12xep100的几个CAN模块变量进行定义
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//
// NOTES:
//
// - The following parameters are calculated according to application note
//   AN1798.
// - Only standard identifiers are used.
//
/////////////////////////////////////////////////////////////////////////////////////////
//
// fNBT = 125000 bit/s
// CANCLK = 4000000 Hz
// tBUS = 25 ns (0.5 m * 5*10^-9 sm^-1)
// tTx = 500 ns
// tRx = 500 ns
//
// NBT = 10
// Tq = 0.75ns
// P = 3
// SYNC_SEG = 1Tq
// PROP_SEG = 3Tq
// PHASE_SEG1 = 3Tq
// PHASE_SEG2 = 3Tq
// RJW = 3
// OscToll = 1.1811%
//
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////////////////
#define   SJW     3     // Synchronization Jump Width (value between 1 and 4 Tq) 
#define   BRP     10     // Baud Rate Prescaler (Value between 1 and 64)
#define   TSEG1   4     // Time segment one Bit Time (value between 1 and 16 Tq)
                        // TSEG1 = PROP_SEG + PHASE_SEG1  
#define   TSEG2   3     // Time segment two Bit Time (value between 1 and 8 Tq)
                        // TSEG2 = PHASE_SEG2
#define   MAX_LEN 8     // Max Data Frame

/////////////////////////////////////////////////////////////////////////////////////////
// Variables
/////////////////////////////////////////////////////////////////////////////////////////
struct can_msg 
{
    unsigned long id;
    Bool RTR;
    unsigned char data[8];
    unsigned char len;
    unsigned char prty;
};
struct can_msg_1 
{
    unsigned long id;
    Bool RTR;
    unsigned char data[1];
    unsigned char len;
    unsigned char prty;
};
struct can_msg_2 
{
    unsigned long id;
    Bool RTR;
    unsigned char data[2];
    unsigned char len;
    unsigned char prty;
};
struct can_msg_3 
{
    unsigned long id;
    Bool RTR;
    unsigned char data[3];
    unsigned char len;
    unsigned char prty;
};
struct can_msg_4 
{
    unsigned long id;
    Bool RTR;
    unsigned char data[4];
    unsigned char len;
    unsigned char prty;
};
struct can_msg_5 
{
    unsigned long id;
    Bool RTR;
    unsigned char data[5];
    unsigned char len;
    unsigned char prty;
};
struct can_msg_6 
{
    unsigned long id;
    Bool RTR;
    unsigned char data[6];
    unsigned char len;
    unsigned char prty;
};
struct can_msg_7 
{
    unsigned long id;
    Bool RTR;
    unsigned char data[7];
    unsigned char len;
    unsigned char prty;
};
struct can_msg_8 
{
    unsigned long id;
    Bool RTR;
    unsigned char data[8];
    unsigned char len;
    unsigned char prty;
};
/////////////////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////////////////

extern void MSCANInit(void);
extern void TurnOnCan2Rx(void);
extern void TurnOffCan2Rx(void);
extern Bool MSCAN0SendMsg(struct can_msg msg);
extern Bool MSCAN1SendMsg(struct can_msg msg);
extern Bool MSCAN2SendMsg(struct can_msg msg);
//*********************************************
//*********************************************
//*********************************************


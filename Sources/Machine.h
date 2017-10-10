
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : S133
//* File Name          : Machine.h
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2015.7.13
//* Description        : 该文件是对CAN发送的报文进行BIT定义
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
extern unsigned int tmr_p1;
extern unsigned int tmr_p2;
extern unsigned int tmr_p3;
extern unsigned int tmr_p4;
extern unsigned int tmr_p5;
extern unsigned int tmr_p6;
extern unsigned char bmsSelfcheckCounter;
extern unsigned char  prechargeFinished;    //预充电完成标志位

extern unsigned char  acc_Connect;
extern unsigned char preChargeON;

extern unsigned char MSDError;                 //MSD故障
extern unsigned char N_RelayConnetError;       //负极继电器粘连
extern unsigned char N_RelayDisConError;       //负极继电器断路
extern unsigned char PreCha_RelayConError;     //预充继电器粘连
extern unsigned char P_RelayConError;          //正极继电器粘连
extern unsigned char PreCha_RelayDisConError;  //预充继电器断路
extern unsigned char P_RelayDisConError;       //正极继电器断路
extern unsigned char CCHG_RelayConError;  //受电弓充电继电器粘连
extern unsigned char DCCHG_RelayConError;  //快充继电器粘连
extern unsigned char CCHG_RelayDisConError;  //受电弓充电继电器断路
extern unsigned char DCCHG_RelayDisConError;  //快充继电器断路
extern unsigned char CHG_N_RelayConError;      //充电负粘连
extern unsigned char CHG_N_RelayDisConError;      //充电负断路
extern unsigned char Cha_ResDisConError;       //预充电阻断路
extern unsigned char PreCha_Error;             //预充电失败
extern unsigned char SelfCheck;                //BMS自检结果: 2,未通过;1通过
extern unsigned char RelayErrorPowerOff;       //继电器下电故障 
//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
extern void VehiclePowerOffLogic(void);
extern void closeNegRelay(void);
extern void openNegRelay(void);
extern void closePosRelay(void);  
extern void openPosRelay(void);
extern void HighVoltDetectPart1(void);
extern void HighVoltDetectPart2(void);
extern void HighVoltDetectPart3(void);
//extern void PRelayConnectTest(void);
//extern void NRelayConnectTest(void);
//extern unsigned char GetTavg(unsigned char LowTem,unsigned char HighTem); 
 //extern unsigned char GetTavgProcess(unsigned char LowTem,unsigned char HighTem); 
extern void GetTavgProcess(void);
//**********************************************************
//***********************************************************
//***********************************************************
//**********************************************************
//***********************************************************
//***********************************************************
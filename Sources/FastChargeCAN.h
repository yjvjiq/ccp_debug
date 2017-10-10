//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : s133
//* File Name          : FastChargeCAN.h
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2015.7.13
//* Description        : 该文件是对CAN发送的报文进行BIT定义
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
extern unsigned char BEMError1;
extern unsigned char BEMError2;
extern unsigned char BEMError3;
extern unsigned char BEMError4;
extern unsigned char PGN[3];
extern unsigned int DCLeftTime; 
extern void cpuToCHMBHM(void);
extern void cpuToCHMBRM(void);
extern void cpuToCHMBRMDATA1(void);
extern void cpuToCHMBRMDATA2(void);
extern void cpuToCHMBRMDATA3(void);
extern void cpuToCHMBRMDATA4(void);
extern void cpuToCHMBRMDATA5(void);
extern void cpuToCHMBRMDATA6(void);
extern void cpuToCHMBRMDATA7(void);
extern void cpuToCHMBCP(void);
extern void cpuToCHMBCPDATA1(void);
extern void cpuToCHMBCPDATA2(void);
extern void cpuToCHMBRO(void);
extern void cpuToCHMBCL(void);
extern void cpuToCHMBCS(void);
extern void cpuToCHMBCSDATA1(void);
extern void cpuToCHMBCSDATA2(void);
extern void cpuToCHMBSM(void);
extern void cpuToCHMBST(void);
extern void cpuToCHMBSD(void);
extern void cpuToCHMBEM(void);
extern void J1939_TP_CM_Abort(void);
//***************************************************
//***************************************************
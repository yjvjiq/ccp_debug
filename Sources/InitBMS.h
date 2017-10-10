//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : 恩驰
//* File Name          : InitBMS.h
//* Author             : Kxy
//* Version            : V1.0.0
//* Start Date         : 2016,07,12
//* Description        : 该文件作为系统头文件，对该项目的系统参数进行定义和对所有全局变量进行全局声明
//----------------------------------------------------------------------------------------------------
#define ParamNUMBER 38
extern unsigned char g_BmsModeFlag; //3:快充充电2:慢充充电 1:放电
extern unsigned char OCVState;//0:OCV没有发生,1：OCV已经发送
extern void delay(unsigned int t); 
extern void parametersClean(void);
extern float g_defaultSysParameters[ParamNUMBER];
extern float g_sysPara[ParamNUMBER];

extern void InitialBMS(void);
extern void InitialSoc(void);
extern float ReadEndFlag(void);
extern void InitDefaultParam(void); 
extern void Interrupt_Priority_Set(void);
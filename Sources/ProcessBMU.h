//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : S133
//* File Name          : ProcessBMU.h
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2015.7.13
//* Description        : 该文件是BMU处理函数头文件
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#ifndef _PROCESSBMU_H_
#define _PROCESSBMU_H_

#define LTC6802_NUM			5   // 每个BMU的6802的个数
#define CELL_NUMBER         36  //每个6802对应的单体个数
#define Tem_NUMBER          3   //每个6802对应的温度个数
#define SLAVE_NUMBER_BEIQI  8   //北汽要求的从板个数
///////////////////////////////////////////////////////////////////////////////////////////
//************ ProcessBMU.c ****************************************
extern float g_highestCellVoltage;
extern float g_lowestCellVoltage;
extern float g_averageVoltage; //平均单体电压
extern float g_systemVoltage;      //系统电压=单体电压累加总电压
extern unsigned char g_highestTemperature;
extern unsigned char g_lowestTemperature;
extern unsigned char g_averageTemperature;
extern unsigned char Tavg;

extern unsigned char g_bmu2_number_v[BMU_NUMBER];
extern unsigned char g_cell_number_v[BMU_NUMBER][5];
extern unsigned char g_bmu2_number_t[BMU_NUMBER];
extern unsigned char g_cell_number_t[BMU_NUMBER][5];

extern unsigned long g_circleFlag; //一个循环完成的标志
extern unsigned long g_configFlag;//收到配置信息标志，用于判断BMU个数，6805组数和单体个数

extern void BMU_initial(void);
extern void BMU_Processure(void);
extern unsigned char bmuProcess2(void);
//************************************************************************
//************************************************************************
//*************************the end****************************************
//************************************************************************
//************************************************************************
#endif
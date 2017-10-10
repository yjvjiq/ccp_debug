//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : dflash.h
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2015.7.13
//* Description        : 该程序针对飞思卡尔公司 9s12xep100内部D_Flash 的读写演示程序
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//************************************************
/*
typedef unsigned char   UINT8;      //unsigned 8 bit definition
typedef unsigned int  UINT16;     //unsigned 16 bit definition
typedef unsigned long   UINT32;     //unsigned 32 bit definition
typedef signed char     INT8;       //signed 8 bit definition
typedef short           INT16;      //signed 16 bit definition
typedef long int        INT32;      //signed 32 bit definition
*/
//************************************************

//#ifndef _DFLASH_H 
//#define _DFLASH_H
extern int    DataBuffer[4];
extern void DFlash_Init(void);
extern void DFlash_Write_Word(unsigned int ADDR16);
extern unsigned int FSL_ReadDFlash (unsigned int destination);
extern void DFlash_Erase_Sector(unsigned int ADDR16);

//#endif
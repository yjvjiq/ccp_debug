//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : RTI.c
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,05,26
//* Description        : 该程序针对RTI定时器模块进行初始化
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "derivative.h" /* include peripheral declarations */
#include "BMS20.h"

long absoluteTime = 0;
//**********************************************************************
//* Function name:   RTIInit
//* Description:     RTI定时器初始化
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void RTIInit(void) 
{
    /* setup of the RTI interrupt frequency */
    /* adjusted to get 1 millisecond (1.024 ms) with 16 MHz oscillator */
    RTICTL = 0x1F; // set RTI prescaler   16*2^10  1ms       16M/(16*2^10)=975 Hz  
    CRGINT = 0x80; // enable RTI interrupts
    //CRGINT = 0x00; // enable RTI interrupts   
}

//**********************************************************************
//**********************************************************************
void startTimeBase(void)
{
    //absoluteTime = 0;
    RTIInit(); 
}

//**********************************************************************
//* Function name:   PIT0_Init
//* Description:     PIT0定时器初始化
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void PIT0_Init(void) 
{

/*
  // Configures the PIT (Periodic Interrupt Timer) 
  // to generate a periodic interrupt of 5ms (Interrupt on channel 0)
  PITCE = 0x01;
  PITINTE = 0x01;
  PITLD0 = 10000;
  PITCFLMT = 0xA0;
*/


//Config1-PIT CH0 10ms
    PITCFLMT  &= 0x7F;          //Disable PIT Module
    PITMUX     = 0x0C;          //Ch0/1 use macro timer 0,Ch2/3 use macro timer 1
    while (PITTF&0x01) 
        PITTF =0x01;  //Clear Timer Ch0 overflow flag by writing a one.
    PITMTLD0 =  8-1;            //Macro timer0 load =   8, output->Busclk/8   to 16bit-timer
//    PITMTLD1 =  160-1;          //Macro timer1 load = 160, output->BusClk/160 to 16bit-timer
    PITLD0   = 20000-1;         //Ch0: (PITMTLD+1)*(PITLD+1)/fBUS=8*10000*125ns=10ms  100Hz@8M 10ms
    //PITLD0   = 50000-1;           //10ms
    PITINTE  |=0x01;            ///Enable the PIT Ch0 interrupt
    //PITINTE  = 0x00;            ///Enable the PIT Ch0 interrupt    
    PITCE    |=0x01;            //Enable the PIT Ch0
    PITCFLMT |=0xA0;            //Enable PIT Module,PIT counters are stalled when in freeze mode  

}

//**********************************************************************
//**********************************************************************
//**********************************************************************
//**********************************************************************
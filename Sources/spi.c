//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : spi.c
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,05,26
//* Description        : �ó������9s12xep100��SPIģ���������
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "derivative.h" /* include peripheral declarations */
#include "spi.h"
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
unsigned char WRCFGR[6]={0xF3,0x00,0x00,0x00,0x92,0x94};  //Configuration (CFG) Register Group��WR
//unsigned char WRCFGR[6]={0xF3,0x00,0xF0,0x0F,0x64,0xA6};  //Configuration (CFG) Register Group��WR

//10-cell mode,Vref powered down No,�趨��������:13ms,UV/OV�Ƚ�����:130ms
//0x8E --UV=3.4v,
//0x96 --OV=3.6v,

//0x92 --UV=3.5v,
//0x94 --OV=3.55v,

//**********************************************************************
//* Function name:   SPI_Init
//* Description:     SPI��ʼ��// ����500kbps 
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void SPI_Init(void)
{								
    // SS�����Զ�SS���
    SPI0CR1  = 0x11;       //
    SPI0CR2  = 0x10;       //SS�����Զ�SS��� 
    SPI0BR   = 0x70;      //BaudRateDivisor = (SPPR + 1)* 2^(SPR + 1)=2
                          //BaudRate = 1M/2 = 500K   
    SPI0CR1   = SPI0CR1|0x40; // SPI Enable

    // SS�����Զ�SS���
    SPI0CR1_SPE=    0;    //SPI��ʹ��
    SPI0CR1_SPIE=   0;    //SPI�����жϲ�ʹ��
    SPI0CR1_SPTIE=  0;    //SPI�����жϲ�ʹ��
    SPI0CR1_MSTR=   1;    //1-��/0-��
    SPI0CR1_CPOL=   1;    //ʱ�Ӽ���ѡ��  0--����ʱ��/1--����ʱ��
    SPI0CR1_CPHA=   1;    //ʱ����λ  0-�����ز���/1-ż���ز���
    SPI0CR1_SSOE=   1;    //��ѡ�����ʹ��
    SPI0CR1_LSBFE=  0;    //0-�ȴ��͸�λ(MSB)/1-�ȴ��͵�λ(LSB)

    SPI0CR2_MODFEN= 1;    //0-ss������SPI;1-ssȡ����MODFEN
    SPI0BR=     0x01;    //BaudRateDivisor = (SPPR + 1)* 2^(SPR + 1)=2
                        //BaudRate = 2M/4 = 500K
    
    SPI0CR1_SPE=    1;    //SPIʹ��  
   
}
//**********************************************************************
//* Function name:   SPI_Write_Byte
//* Description:     дSPIһ���ֽڳ���
//* EntryParameter : Ҫд����ֽ�
//* ReturnValue    : None
//**********************************************************************
void SPI_Write_Byte(unsigned char val)
{
	  SPI0DR = val;
	  while(!(SPI0SR_SPTEF));
	  return;
}
//**********************************************************************
//* Function name:   SPI_Read_Byte
//* Description:     SPI��һ���ֽ� 
//* EntryParameter : None
//* ReturnValue    : һ���ֽ�
//**********************************************************************
unsigned char SPI_Read_Byte(void)
{ 	
  	//while(!(SPIS_SPRF));
  	while(!(SPI0SR_SPIF));
  	return (unsigned char)SPI0DR;

}

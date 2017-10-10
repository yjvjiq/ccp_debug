//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : dflash.C
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2015.7.13
//* Description        : 该程序针对飞思卡尔公司 9s12xep100内部D_Flash 的读写演示程序
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

//#include "dflash.h"      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#define FLASH_PRESCALER 0x0F  //flash prescaler for 16MHz oscillator

#define GLOBAL_DFLASH_START_ADDR    0x100000    //Global Address
typedef volatile unsigned short VUINT16;  
#define READ16(address)                 ((unsigned int)(*(VUINT16 *__near)(address)))

/* Macros used for Reading D-Flash */
#define DFLASH_LOWEST_START_PAGE        0x00
#define DFLASH_START                    0x00100000 //d_flash 起始地址
#define DFLASH_PAGE_SIZE                0x0400     //
#define DFLASH_PAGE_WINDOW_START        0x0800
  
int    DataBuffer[4];//={0xaaaa,0x5678,0x9abc,0xdef0};//数据缓存区，只能一次写入四个数据
//**********************************************************************
//* Function name:   DFlash_Init
//* Description:     初始化 
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
//#pragma CODE_SEG RAM_CODE

void DFlash_Init(void)
{
    /*
    while((FSTAT & FSTAT_CCIF_MASK) == 0);  //wait if command in progress
    FCLKDIV=0x0F;                    // 15.75<=OSCLK=16M<=16.80，(0x0F)
    FCNFG=0x00;                      // disable Interrupt
    while(FCLKDIV_FDIVLD==0);        //等待时钟设置成功FCLKDIV_FDIVLD==1
    */
    FCLKDIV = FLASH_PRESCALER;  //set flash prescaler
}
//#pragma CODE_SEG DEFAULT
//**********************************************************************
//* Function name:   DFlash_Write_Word
//* Description:     写DFlash a word or some words (four) 
//* EntryParameter : 器件地址
//* ReturnValue    : None
//**********************************************************************
//#pragma CODE_SEG RAM_CODE
void DFlash_Write_Word(unsigned int ADDR16)
{
    //while(FSTAT_CCIF==0); 
    while((FSTAT & FSTAT_CCIF_MASK) == 0);  //wait if command in progress
    if(FSTAT&0x30)      
    { 
        FSTAT |=0x30; //注意不可以用//FSTAT_ACCERR=1 命令经行清标志，否则将造成无法flash读写  
                                    //FSTAT_FPVIOL=1
    }
    FCCOBIX=0x00; 
    
    //FCCOBHI=0x11;         //FCMD(操作命令),Program D-Flash
    //FCCOBLO=0x10;         //(地址高8位,第一位为0) D-FLASH block address
    FCCOB = 0x1110;
    
    FCCOBIX=0x01;  //地址后16位
    FCCOB=ADDR16;         //Global Address Of Word To Be Program
    
    FCCOBIX=0x02;  //Word 0 program value
    FCCOB=DataBuffer[0];

    FCCOBIX=0x03;  //word1,if desired
    FCCOB=DataBuffer[1];

    FCCOBIX=0x04;  //word2,if desired
    FCCOB=DataBuffer[2];

    FCCOBIX=0x05;  //word3,if desired
    FCCOB=DataBuffer[3];  
      
    //FSTAT_CCIF=1;         //lanuch command,写1清零
    FSTAT = 0x80;       //launch command
       
    //while(FSTAT_CCIF==0);
    while((FSTAT & FSTAT_CCIF_MASK) == 0);  //wait if command in progress
}
//#pragma CODE_SEG DEFAULT
//**********************************************************************
//* Function name:   FSL_ReadDFlash
//* Description:     读取D_Flash 某位置的数据
//* EntryParameter : 器件位置地址
//* ReturnValue    : 一个字数据
//**********************************************************************
//读取D_Flash 某位置的数据
//#pragma CODE_SEG RAM_CODE
unsigned int FSL_ReadDFlash (unsigned int destination)
{
    unsigned char   saveEpage;          /* save EPAGE register */
    unsigned char   epage;              /* for setting EPAGE register */
    unsigned int   data;              /* to store the data read */

    /* Save the current EPAGE value */
    saveEpage = EPAGE;

    /* Calculate the page value of the global Address passed */
    epage = (unsigned char)((DFLASH_LOWEST_START_PAGE)+(destination >>10));
    /* Write the calculate page value in the EPAGE register */
    EPAGE=epage;
    /* Read the data from the D-Flash, by converting the global address to logical address */
    data = READ16((destination & (DFLASH_PAGE_SIZE - 1)) + DFLASH_PAGE_WINDOW_START);

    /* Restore the EPAGE register */
    EPAGE= saveEpage;

    return(data);
}
//#pragma CODE_SEG DEFAULT
//**********************************************************************
//* Function name:   DFlash_Erase_Sector
//* Description:     擦除sector程序 The Erase D-Flash Sector operation will erase all addresses
//*                  in a sector of the D-Flash block.
//* EntryParameter : 器件地址
//* ReturnValue    : None
//**********************************************************************
//#pragma CODE_SEG RAM_CODE
void DFlash_Erase_Sector(unsigned int ADDR16)
{   
    //while(FSTAT_CCIF==0);
    while((FSTAT & FSTAT_CCIF_MASK) == 0);  //wait if command in progress
    if(FSTAT&0x30)
        FSTAT |=0x30;
    
    FCCOBIX=0x00;
    //FCCOBHI=0x12;           //FCMD=0x12  Erase D-Flash Sector  
    //FCCOBLO=0x10;           //D-FLASH block address
    FCCOB = 0x1210;
    FCCOBIX=0x01;    //Global address anywhere within
    FCCOB=ADDR16;           //the sector to be erased
    //FSTAT_CCIF=1;           //launch command
    FSTAT = 0x80;       //launch command
    //while(FSTAT_CCIF==0);
    while((FSTAT & FSTAT_CCIF_MASK) == 0);  //wait if command in progress
}
//#pragma CODE_SEG DEFAULT
/*************************************************/

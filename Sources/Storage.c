
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : S133
//* File Name          : Storage.c
//* Author             : judy
//* Version            : V1.0.0
//* Start Date         : 2016.2.14
//* Description        : 该文件用于存储或读出相关参数，如SOC，系统参数、可用容量等
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "derivative.h" /* include peripheral declarations */
#include "BMS20.h" 
#include "Storage.h"
//---------------------------------------------------------------------------------------------------
//******************************************************************************
//* Function name:   LoadParamter
//* Description:     从24C64下载系统保存的参数
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void LoadParamter(void)
{	
  	Read24c64_Byte(ParaBaseAddr,(unsigned char* )g_sysPara,ParamNUMBER*4);  //读出所保存的系统参数

    //g_BMU_CIRCLE_FLAG = 0x11111111;	//8个BMU
	  /*
  	switch((unsigned int)g_sysPara[PARA_BMU_NUMBER])//根据BMU的个数，确定相应的配置信息，能够知道是否所有的单体数据已经发了一轮
  	{
  	  case 1:
  	    g_BMU_CIRCLE_FLAG = 0x0000001;
  	    break;
  	  case 2:
  	    g_BMU_CIRCLE_FLAG = 0x0000011;
  	    break; 
  	  case 3:
  	    g_BMU_CIRCLE_FLAG = 0x0000111;
  	    break;                                            z
  	  case 4:
  	    g_BMU_CIRCLE_FLAG = 0x0001111;
  	    break; 
  	  case 5:
  	    g_BMU_CIRCLE_FLAG = 0x0011111;
  	    break;
  	  case 6:
  	    g_BMU_CIRCLE_FLAG = 0x0111111;
  	    break;  
  	  case 7:
  	    g_BMU_CIRCLE_FLAG = 0x1111111;
  	    break;      
  	  default:
  	    break;
    }  
    */

}
//******************************************************************************
//* Function name:   StoreParameter
//* Description:     重新写入系统参数
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void StoreParameter(void)
{	
	  Write24c64_Byte(ParaBaseAddr,(unsigned char* )g_sysPara,ParamNUMBER*4);  //重新写入系统参数
}
//******************************************************************************
//* Function name:   StoreSocRealvalue
//* Description:     保存SOC实际值与显示SOC值
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void StoreSocRealvalue(void)//
{
    unsigned int DBuffer[1],DBuffer2[1]; 
    //unsigned int DBuffer1;
    unsigned int checksoc0,checksoc1;
    
    DBuffer[0]= (unsigned int)(g_socValue*1000);
    checksoc0 = DBuffer[0];
    
    /////////正确//////////
    DBuffer2[0]= (unsigned int)(Can_g_socValue*1000);
    checksoc1 = DBuffer2[0];
    /////////正确//////////
    
    DisableInterrupts;
    Write24c64_Byte(SOC_ADDR,(unsigned char* )DBuffer,2);//真实SOC 
    Read24c64_Byte(SOC_ADDR,(unsigned char* )DBuffer,2); 
    
    /////////正确//////////
    Write24c64_Byte(Can_SOC_ADDR,(unsigned char*)DBuffer2,2);//上报SOC 
    Read24c64_Byte(Can_SOC_ADDR,(unsigned char*)DBuffer2,2);
    /////////正确//////////
    
    
    if(checksoc0 != DBuffer[0])
        g_socValue=0.44;
    
     if(checksoc1 != DBuffer2[0])
        Can_g_socValue=0.44;
     
    EnableInterrupts;
}
//******************************************************************************
//* Function name:   StoreQ1value
//* Description:     保存修改后的Q1值
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void StoreQ1value(void)//
{
    unsigned int DBuffer[1]; 
    unsigned int checkQ1;
    
    DBuffer[0]= (unsigned int)(g_realNominalCap*100);
    checkQ1 = DBuffer[0];
    
    
    DisableInterrupts;
    Write24c64_Byte(Q1_ADDR,(unsigned char* )DBuffer,2);//真实SOC 
    Read24c64_Byte(Q1_ADDR,(unsigned char* )DBuffer,2); 
    if(checkQ1 != DBuffer[0])
        g_realNominalCap=241;
     
    EnableInterrupts;
}
//******************************************************************************
//* Function name:   ReadOutSocStoreValue
//* Description:     读出保存的SOC值
//* EntryParameter : None
//* ReturnValue    : SOC值
//******************************************************************************
float ReadOutSocStoreValue(void) 
{
    float s=0;
    unsigned int DBuffer[1]; 
    
    DisableInterrupts;
    Read24c64_Byte(SOC_ADDR,(unsigned char* )DBuffer,2); 
    EnableInterrupts;
    s= DBuffer[0]/1000.0;
    
    return s;

}

//******************************************************************************
//* Function name:   ReadOutCanSocStoreValue
//* Description:     读出保存的Q1值
//* EntryParameter : None
//* ReturnValue    : SOC值
//******************************************************************************
float ReadOutQ1StoreValue(void) 
{
    float s=0;
    unsigned int DBuffer[1]; 
    
    DisableInterrupts;
    Read24c64_Byte(Q1_ADDR,(unsigned char* )DBuffer,2); 
    EnableInterrupts;
    if((DBuffer[0]==0)||(DBuffer[0]==0xffff))
        s=SetCap;    
    else
        s= DBuffer[0]/100.0;
    
    return s;

}

//******************************************************************************
//* Function name:   ReadOutCanSocStoreValue
//* Description:     读出保存的SOC值
//* EntryParameter : None
//* ReturnValue    : SOC值
//******************************************************************************
float ReadOutCanSocStoreValue(void) 
{
    float s=0;
    unsigned int DBuffer[1]; 
    
    DisableInterrupts;
    Read24c64_Byte(Can_SOC_ADDR,(unsigned char* )DBuffer,2); 
    EnableInterrupts;
    s= DBuffer[0]/1000.0;
    
    return s;

}

//******************************************************************************
//* Function name:   StoreChargeAH
//* Description:     保存所有充放电总容量
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void StoreChargeDischargeAH(void)//
{
    unsigned long DBuffer[1]; 
    static unsigned char RecordState=0;
    
    //chargeAH=0;
    DBuffer[0]= chargeAH;
    DisableInterrupts;
    Write24c64_Byte(AH_CHARGE_ADDR,(unsigned char* )DBuffer,4); 
    EnableInterrupts;
    
    //dischargeAH=0;
    DBuffer[0]= dischargeAH;
    DisableInterrupts;
    Write24c64_Byte(AH_DISCHARGE_ADDR,(unsigned char* )DBuffer,4); 
    EnableInterrupts;
    

}
//******************************************************************************
//* Function name:   StoreChargeTime
//* Description:     保存所有充电次数
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void StoreChargeTime(void)
{
    unsigned int DBuffer1[1];
    unsigned int DBuffer2[1]; 
    DBuffer1[0]= Charge_Times;
    DisableInterrupts;
    Write24c64_Byte(ChangerTime_ADDR,(unsigned char* )DBuffer1,2);
    Read24c64_Byte(ChangerTime_ADDR,(unsigned char* )DBuffer2,2); 
    EnableInterrupts;
}
//******************************************************************************
//* Function name:   StoreDischargeAH
//* Description:     读出所有充放电总容量
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void ReadChargeDischargeAH(void) 
{

    //unsigned long int DBuffer[1];
    long DBuffer[1];
    unsigned int Times[1];   
    
    DisableInterrupts;
    Read24c64_Byte(AH_CHARGE_ADDR,(unsigned char* )DBuffer,4); 
    EnableInterrupts;
    if(DBuffer[0]==0xffffffff)
        chargeAH=0;
    else
        chargeAH=DBuffer[0];
  
    DisableInterrupts;
    Read24c64_Byte(AH_DISCHARGE_ADDR,(unsigned char* )DBuffer,4); 
    EnableInterrupts;
    if(DBuffer[0]==0xffffffff)
        dischargeAH=0;
    else
        dischargeAH=DBuffer[0];
    
    DisableInterrupts;
    Read24c64_Byte(ChangerTime_ADDR,(unsigned char* )Times,2); 
    EnableInterrupts;
    if(Times[0]==0xffff)
        Charge_Times=0;
    else
        Charge_Times=Times[0];

}
//**********************************************************************
//* Function name:   Task06_BMN_DATA_RECALL
//* Description:     从24c64里读出3路电压的KB值
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void KB_DATA_RECALL(void)
{
    
    int buffer[7] = {0};
    int ch=0,t=3;
    unsigned char i;
  
    do
    {
        //Read24c64_Byte(VPN_KB_ADDRESS,(unsigned char* )buffer,14);
        Read24c64_Byte(VPN_KB_ADDRESS,(unsigned char* )buffer,14);
        for(i=0;i<6;i++)
            ch += buffer[i];    
        ch +=1;
        t--; 
        //t=0;//for test  
    }while((ch!=buffer[6])&&(t>0));  
    Vpn_K1 = buffer[0];
    Vpn_B1 = buffer[1];
    Vpn_K2 = buffer[2];
    Vpn_B2 = buffer[3];
    Vpn_K3 = buffer[4];
    Vpn_B3 = buffer[5];
    if((t==0)||(Vpn_K1==0xffff))//如果全是0xffff或者验证不通过,则调用单片机存储的数据
    {
        Vpn_K1 = FSL_ReadDFlash(0x0300);
        Vpn_B1 = FSL_ReadDFlash(0x0302);
        Vpn_K2 = FSL_ReadDFlash(0x0304);
        Vpn_B2 = FSL_ReadDFlash(0x0306);
        Vpn_K3 = FSL_ReadDFlash(0x0308);
        Vpn_B3 = FSL_ReadDFlash(0x030A);
    }
    
    
}        
//**********************************************************************
//* Function name:   Task07_BMN_DATA_SAVE
//* Description:     把3路电压的KB值保存到24c64里
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void KB_DATA_SAVE(void)
{
  
    int buffer[7];
    int ch=0;
    unsigned char i;

    buffer[0]= Vpn_K1;
    buffer[1]= Vpn_B1;
    buffer[2]= Vpn_K2;
    buffer[3]= Vpn_B2;
    buffer[4]= Vpn_K3;
    buffer[5]= Vpn_B3;

    for(i=0;i<6;i++)    
        ch+= buffer[i]; 
    ch++;        
    buffer[6] =ch; 
    
    ch=0;
    do
    {
        Write24c64_Byte(VPN_KB_ADDRESS,(unsigned char* )buffer,14);  //write into at45db161 at 300
        Read24c64_Byte(VPN_KB_ADDRESS,(unsigned char* )buffer,14);
        for(i=0;i<6;i++)
            ch += buffer[i];    
        ch +=1;   
    }while(ch!=buffer[6]);
    
    
    DFlash_Erase_Sector(0x0300); //必须先擦除一个扇区
    DataBuffer[0]= Vpn_K1;
    DataBuffer[1]= Vpn_B1; 
    DataBuffer[2]= Vpn_K2;
    DataBuffer[3]= Vpn_B2;
    DFlash_Write_Word(0x0300);//
    
    //DFlash_Erase_Sector(0x0308); //必须先擦除一个扇区
    DataBuffer[0]= Vpn_K3;
    DataBuffer[1]= Vpn_B3; 
    DataBuffer[2]= 0xffff;
    DataBuffer[3]= 0xffff;
    //DataBuffer[2]= Vpn_B3;
    //DataBuffer[3]= Vpn_B3;
    DFlash_Write_Word(0x0308);//
     
}
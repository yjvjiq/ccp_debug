//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : S133
//* File Name          : Record.c
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2014.5.7
//* Description        : ¸ÃÎÄ¼þ×¨ÃÅÓÃÓÚÀúÊ·¼ÇÂ¼´¦Àí²¿·Ö¹¦ÄÜ£»Ã¿·ÖÖÓ´æ´¢Ò»´ÎÊý¾ÝÒÔ¼°ÓÐ¹ÊÕÏ·¢ÉúÊ±¼´Ê±´æ´¢
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "derivative.h" /* include peripheral declarations */
#include "BMS20.h" 

//*************************************************************************************************
unsigned int g_storageSysVariableOut[STORE_NUMBER]= 
{
    0,  //¼ÇÂ¼Ë÷Òý
    0,  //ÏµÍ³×ÜµçÑ¹
    0,  //ÏµÍ³×ÜµçÁ÷
    1.0,  //SOCÏÔÊ¾Öµ
    0,   //¼ÌµçÆ÷×´Ì¬
    0.0,   //¹ÊÕÏµÈ¼¶
    0,    //¹ÊÕÏÐÅÏ¢1
    0,   //¹ÊÕÏÐÅÏ¢2
    0,   //¹ÊÕÏÐÅÏ¢3
    0,   //¹ÊÕÏÐÅÏ¢4
    0,//second        10
    0,//minute////////11
    0,//hour
    0,//week
    0,//day
    0,//month
    0, //year
    0,//×î¸ßµ¥ÌåÎÂ¶È
    0,//×îµÍµ¥ÌåÎÂ¶È
    0,//Æ½¾ùÎÂ¶È
    0, //×î¸ßµ¥ÌåµçÑ¹
    0, //×îµÍµ¥ÌåµçÑ¹
    0, //Æ½¾ùµçÑ¹
    1000,//¾øÔµ×èÖµÕý
    1000,//¾øÔµ×èÖµ¸º
    198,
    4000,
    198,
    4000,
    198,
    4000,
    0   //Ð£Ñé
};
unsigned char g_storageSysVariableT[36];
/*unsigned int g_storageSysVariableCell[200]= //´æ´¢200¸öµ¥ÌåµçÑ¹ÓÃ
{  
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0
};*/
/*unsigned int g_storageSysVariableCellOut[200]= //¶Á³ö200¸öµ¥ÌåµçÑ¹ÓÃ
{  
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0
};*/

unsigned int g_storageSysVariableCell[36]= //´æ´¢200¸öµ¥ÌåµçÑ¹ÓÃ
{  
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0
};
unsigned int g_storageSysVariableCellOut[36]= //¶Á³ö200¸öµ¥ÌåµçÑ¹ÓÃ
{  
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0
};

unsigned int g_storageSysVariable[120];
//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
//******************************************************************************
//* Function name:   ReadErrorIndex
//* Description:     ¶Á³öÀúÊ·Êý¾ÝË÷ÒýºÅ
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
unsigned int ReadErrorIndex(void) 
{
    unsigned int counter=0;   
    unsigned int cc[1];
    
    Read24c64_Byte(ERROR_COUNT_ADDR,(unsigned char* )cc,2); //»ñÈ¡µ±Ç°ÀúÊ·¼ÇÂ¼¼ÆÊýÆ÷  
    return ((unsigned int)cc[0]);   
}
//******************************************************************************
//* Function name:   storeErrorIndex
//* Description:     ´æ´¢ÀúÊ·¼ÇÂ¼Ë÷ÒýºÅ
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void storeErrorIndex(unsigned int index) 
{
    unsigned int counter[1];
    
    counter[0]= index;
    Write24c64_Byte(ERROR_COUNT_ADDR,(unsigned char *)&counter,2);//¸üÐÂ¹ÊÕÏ¼ÆÊýÆ 
}
//******************************************************************************
//* Function name:   StoreSysVariable
//* Description:     ´æ´¢ÀúÊ·¼ÇÂ¼ÐÅÏ¢
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void StoreSysVariable(void)  //´æ´¢¹ÊÕÏÐÅÏ¢ºÍSOCÖµ£¬µØÖ·´Óat45db161 µÄ 0x3ff ¿ªÊ¼
{
	unsigned char i=0,j=0; 
	unsigned int buffer1[STORE_NUMBER],buffer2_1[128],buffer2_2[72];//,test_1[128],test_2[72],test1[32]
	unsigned int check=0;   //Ð£ÑéºÍ

	g_errorCounter++;
	if(g_errorCounter>=500){  //±£´æ500Ìõºó£¬Ñ­»·´æ´¢
		g_errorCounter = 0;
	}
	
    storeErrorIndex(g_errorCounter);//¸üÐÂ¹ÊÕÏ¼ÆÊýÆ÷ 
	
    g_storageSysVariable[INDEX]= g_errorCounter;
    g_storageSysVariable[TOTAL_VOLTAGE]= (unsigned int)g_highVoltageV1;   
    g_storageSysVariable[TOTAL_CURRENT]= (unsigned int)((g_systemCurrent+400)*50);
    g_storageSysVariable[PARA_SOC_DISPLAY]= (unsigned int)(g_socValue*100*2.5);
    g_storageSysVariable[SYS_CONTACTORS_STATE]= BmsCtlStat0 & 0xff;//BMS¿ØÖÆ×´Ì¬ 
    
    //¹ÊÕÏÐÅÏ¢ÔÚ¹ÊÕÏ´¦Àí³ÌÐòÀï
    //ÊµÊ±Ê±¼ä
    for(j=SYS_REALTIME_SECOND;j<SYS_REALTIME_YEAR+1;j++){
        g_storageSysVariable[j]= CurrentTime[j-10];
    }

	g_storageSysVariable[CELL_MAX_TEM]			= (unsigned int)((g_bms_msg.CellTempMax-40)+48);
	g_storageSysVariable[CELL_MIN_TEM]			= (unsigned int)((g_bms_msg.CellTempMin-40)+48);
	g_storageSysVariable[CELL_AVERAGE_TEM]		= (unsigned int)((g_averageTemperature-40)+48);
	g_storageSysVariable[CELL_MAX_VOLTAGE]		= (unsigned int)(g_bms_msg.CellVoltageMax);
	g_storageSysVariable[CELL_MIN_VOLTAGE]		= (unsigned int)(g_bms_msg.CellVoltageMin);
	g_storageSysVariable[CELL_AVERAGE_VOLTAGE]	= (unsigned int)(g_averageVoltage*10000); 
	g_storageSysVariable[SYS_INSULATION_P]		= Rp_Vpn_Value;
	g_storageSysVariable[SYS_INSULATION_N]		= Rn_Vpn_Value;
	
    //µ¥ÌåµçÑ¹ÖµÔÚBMUÊý¾Ý´¦ÀíÀï
    //´æÈëAD45DB161
    //ÒÔÏÂ´æ´¢Êý¾ÝÒòÎª³¬¹ý256¸ö£¬ËùÒÔ·Ö³ÉÁ½²¿·ÖÀ´±£´æ¡£ Wrt_Flashº¯ÊýµÄÈë¿Ú²ÎÊýÊÇunsigned charÐÍµÄ¡£¸Ä³Éunsigned intÐÍµÄÓÐÊ±ºò¶Á²»¶Ô
    //ÕâÀï³öÏÖ¿çÒ³´íÎóÎÊÌâ¡£¡£¡£ËùÒÔ£¬Ã¿Ìõ¼ÇÂ¼Õ¼Ò»ÕûÒ³¡£528×Ö½ÚÒ»Ò³¡£      
    for(i=0;i<=35;i++) 
    {    
        buffer2_1[i] = g_storageSysVariableCell[i];//¼ÇÂ¼ËùÓÐµ¥ÌåµçÑ¹¼«Öµ
        check += buffer2_1[i];
    }
    M95_Write_Memory(256*(unsigned long)2*g_errorCounter,(unsigned char* )buffer2_1,36*2);//´ÓµÚ1Ò³¿ªÊ¼£¨µØÖ·´Ó0¿ªÊ¼,0~255,´æ18¸ö×î¸ßµ¥ÌåµçÑ¹ºÍ18¸ö×îµÍµ¥ÌåµçÑ¹, 18*2bytes*2, max and min
    
    //for test
    /*
    DisableInterrupts;
    M95_Read_Memory(256*(unsigned long)2*g_errorCounter,(unsigned char* )test_1,256);//´ÓµÚ1Ò³¿ªÊ¼£¨µØÖ·´Ó0¿ªÊ¼,0~255,´æ128¸öµ¥ÌåµçÑ¹  
    EnableInterrupts; //¿ªÖÐ¶Ï£
    */
    //end of test
    
    for(i=128;i<200;i++)
    {
//		buffer2_2[i-128] = g_storageSysVariableCell[i];//¼ÇÂ¼ËùÓÐµ¥ÌåµçÑ¹
		buffer2_2[i-128] = 0;   //fill 0 for unused area. just check calculate, project name S278.

		check += buffer2_2[i-128];  
    }
      
    M95_Write_Memory(256*(unsigned long)(2*g_errorCounter+1),buffer2_2,72*2);//´ÓµÚ1Ò³¿ªÊ¼£¨µØÖ·´Ó256¿ªÊ¼£¬256~399,´æÁíÍâ72¸öµçÑ¹
    
    //for test
    /*
    DisableInterrupts;
    M95_Read_Memory(256*(unsigned long)(2*g_errorCounter+1),(unsigned char* )test_2,72*2);//´ÓµÚ1Ò³¿ªÊ¼£¨µØÖ·´Ó0¿ªÊ¼,0~255,´æ128¸öµ¥ÌåµçÑ¹  
    EnableInterrupts; //¿ªÖÐ¶Ï
    */
    //end of test  
    
    //ÏÈ´æºó°ëÒ³£¬ÔÙ´æÇ°°ëÒ³£¬ÒòÎªÐ£ÑéºÍÔÚÇ°°ëÒ³Àï
    for(i=0;i<=SYS_INSULATION_N;i++) 
    {
        buffer1[i]= g_storageSysVariable[i];//¼ÇÂ¼64Î»ÆäËû×Ö½Ú 
        check += buffer1[i];
    }
    //***Ôö¼Ó±£´æV1£¬V2£¬V3µÄK,BÖµ¡£¡£¡£ÒòÎªBÖµÐ©ÖµÊÇintÀàÐÍ£¬ËùÒÔÒªÓÃ²¹Âë½øÐÐ±£´æ
   
	buffer1[VOLT_K1] =Vpn_K1;
	check += buffer1[VOLT_K1];
	
	buffer1[VOLT_B1] =(unsigned int)(32767-Vpn_B1);
	check += buffer1[VOLT_B1];
	
	buffer1[VOLT_K2] =Vpn_K2;
	check += buffer1[VOLT_K2];
	
	buffer1[VOLT_B2] =(unsigned int)(32767-Vpn_B2);
	check += buffer1[VOLT_B2];
	
	buffer1[VOLT_K3] =Vpn_K3;
	check += buffer1[VOLT_K3];
	
	buffer1[VOLT_B3] =(unsigned int)(32767-Vpn_B3);
	check += buffer1[VOLT_B3];
           
    buffer1[VERIFICATION] = check;
    
    M95_Write_Memory(256*(unsigned long)(2*g_errorCounter+1)+72*2,(unsigned char*)buffer1,STORE_NUMBER*2);//´ÓµÚ1Ò³¿ªÊ¼£¨µØÖ·´Ó400¿ªÊ¼£¬463´æ´¢64¸ö²ÎÊýÊý¾Ý
    
    //for test
    /*
    DisableInterrupts; //
        M95_Read_Memory(256*(unsigned long)(2*g_errorCounter+1)+72*2,test1,STORE_NUMBER*2);
    EnableInterrupts;
    */
    //for test
}
//******************************************************************************
//* Function name:   ReadOutErrorRecord
//* Description:     ¶Á³öÀúÊ·¼ÇÂ¼ÐÅÏ¢
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
 
unsigned char ReadOutErrorRecord(unsigned int counter) //   1:Ð£Ñé²»Í¨¹ý
{
	unsigned int i=0;
	unsigned int check=0;
	unsigned int verification=0;
	unsigned int buffer1[STORE_NUMBER],buffer2_1[128],buffer2_2[72];

	DisableInterrupts; //
        M95_Read_Memory(256*(unsigned long)2*counter,(unsigned char* )buffer2_1,256);//´ÓµÚ1Ò³¿ªÊ¼£¨µØÖ·´Ó0¿ªÊ¼,0~255,´æ128¸öµ¥ÌåµçÑ¹  
	EnableInterrupts; //¿ªÖÐ¶Ï

	for(i=0;i<128;i++) 
	{      
         check += buffer2_1[i];
    }


    DisableInterrupts; //
        M95_Read_Memory(256*((unsigned long)2*counter+1),(unsigned char* )buffer2_2,72*2);//´ÓµÚ1Ò³¿ªÊ¼£¨µØÖ·´Ó0¿ªÊ¼,0~255,´æ128¸öµ¥ÌåµçÑ¹  
    EnableInterrupts; //¿ªÖÐ¶Ï  
    for(i=0;i<72;i++) 
    {      
         check += buffer2_2[i];
    }
    
    
    DisableInterrupts; //
        M95_Read_Memory((256*(unsigned long)(2*counter+1)+72*2),(unsigned char* )buffer1,STORE_NUMBER*2);
    EnableInterrupts; //¿ªÖÐ¶Ï
    
    for(i=0;i<=VOLT_B3;i++) 
    {      
        check += buffer1[i];
    }
    verification =  buffer1[VERIFICATION];

    if(verification == check)
    {
		for(i=0;i<STORE_NUMBER;i++) 
		    g_storageSysVariableOut[i] = buffer1[i]; //²ÎÊý¸öÊý 32
//		for(i=0;i<128;i++) 
//		    g_storageSysVariableCellOut[i]= buffer2_1[i];  //µ¥ÌåµçÑ¹ 
//		for(i=128;i<200;i++)
//		    g_storageSysVariableCellOut[i]= buffer2_2[i-128];  //µ¥ÌåµçÑ¹     

//		for(i=128;i<200;i++){
//			g_storageSysVariableCellOut[i]= buffer2_2[i-128];  //µ¥ÌåµçÑ¹	  
//		}

		for(i=0;i<36;i++){
			g_storageSysVariableCellOut[i]= buffer2_1[i];  //µ¥ÌåµçÑ¹ 
		}
		return 0;
    }
    else if(counter > g_errorCounter) 
    {
        for(i=0;i<STORE_NUMBER;i++) 
            g_storageSysVariableOut[i] = 0;
//        for(i=0;i<200;i++)
//            g_storageSysVariableCellOut[i]=0;   
        for(i=0;i<36;i++)
            g_storageSysVariableCellOut[i]=0;   
        return 0; 
    }
    return 1;                   
}
//******************************************************************************
//* Function name:   TaskRecordProcess
//* Description:     ÀúÊ·¼ÇÂ¼´¦ÀíÈÎÎñ¹ý³Ì£¬¶ÁÈ¡2000Ìõ
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void TaskRecordProcess(void)
{
	int i,j;

	if(!g_errorRecordRead_flag){ 
		return;
	}
	  
	DisableInterrupts; //ÊÇ·ñ¶ÁÈ¡¹ÊÕÏÐÅÏ¢£¬µ±¶ÁÈ¡¹ÊÕÏÐÅÏ¢Ê±£¬ËùÓÐÖÐ¶ÏÍ£Ö¹
	for(i=499;i>=0;i--) 
	{	    
		_FEED_COP();   //2sÄÚ²»Î¹ÄÚ¹·£¬ÔòÏµÍ³¸´Î»
		//PORTB_PB4 ^=1; //feed the hardware dog
		if(1==ReadOutErrorRecord(i))//Èç¹ûÐ£Ñé²»Í¨¹ý£¬ÔòÖØÐÂ¶ÁÈ¡	 
		{
			ReadOutErrorRecord(i);
		}
		
		delay(1000);
		delay(1000);      
		RecordSystem();
		delay(1000);
		delay(1000);
		RecordFaultTemperture();
		delay(1000);
		delay(1000);
		RecordRealtime();
		delay(1000);
		delay(1000);
		RecordExtremCellVoltage();
		delay(1000);
		delay(1000);
		RecordInsulation();
		delay(1000);
		delay(1000);
		RecordVoltKB();
		delay(1000);
		delay(1000);
		for(j=0;j<50;j++) 
		{	        
			RecordCellVoltage(j);//0~4*49+3=199
			delay(1000);
			delay(1000);   //´Ë´¦±ØÐëÑÓÊ±×ã¹»
			delay(1000);
			delay(1000);
		}
    }
	
	delay(1000);
	delay(1000);
	RecordEndFlag();//end	 

	g_errorRecordRead_flag=0;	
	EnableInterrupts;	
}
//******************************************************************************
//* Function name:   parametersClean
//* Description:     ²ÎÊý±äÁ¿ÇåÁã
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void parametersClean(void)
{
	unsigned int i,k;//,j

	for(i=0;i<BMU_NUMBER;i++){
		for(k=0;k<CELL_NUMBER;k++){
			g_bmu_msg.cell_V[i][k] = 0;
		}
		for(k=0;k<Tem_NUMBER;k++){
			g_bmu_msg.cell_T[i][k] = 0;
		}
	}
	
//	g_highestCellVoltage = 0;
//	g_lowestCellVoltage = 0;
	g_bms_msg.CellVoltageMax = 0;
	g_bms_msg.CellVoltageMin = 0;
	g_averageVoltage = 0; 

	for(i=0;i<STORE_NUMBER;i++){
        g_storageSysVariableOut[i] = 0;
	}

	VCU_ChgControl_2.Bit.rise_Eleband_No_OK = 1;
	VCU_ChgControl.Bit.rise_Eleband_Switch = 0;
	VCU_ChgControl.Bit.downC_OK = 1;
}
//********************************************************************************************
//***********************************the end*************************************************
//********************************************************************************************
//********************************************************************************************

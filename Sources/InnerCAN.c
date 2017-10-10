//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : S133
//* File Name          : InnerCAN.c
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2016.1.12
//* Description        : 该文件负责发送内部CAN的所有报文内容
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "BMS20.h"
unsigned char  C0552_0=0;
unsigned char  C0552_1=0;
unsigned char BmsCtlStat0  = 0;               //继电器状态
STATE_PC552_GROUP1   state_pc552_group1;
STATE_PC552_GROUP2   state_pc552_group2;
FAULT_PC552_GROUP1   fault_pc552_group1;
FAULT_PC552_GROUP2   fault_pc552_group2;
FAULT_PC552_GROUP3   fault_pc552_group3;
FAULT_PC552_GROUP4   fault_pc552_group4;
CAN554BYTE0      Can554Byte0;
CAN554BYTE1      Can554Byte1;
CAN554BYTE2      Can554Byte2;
CAN554BYTE3      Can554Byte3;
BMS_FAN_CONTROL  BMS_Fan_Control;
//PC750_GROUP pc750_group;
float	g_highVoltageV4; // V1B
float	g_highVoltageV5; // V2B
float	g_highVoltageV6; // V3B
unsigned char InsRelayControl = 0;//绝缘控制继电器控制
//*************************************************************************************
//*************************************************************************************
//*****************以下是BMS给PC发消息子程序*****************************************
//*************************************************************************************
//******************************************************************************
//* Function name:   bmsToPcInfo450
//* Description:     发送生命信号、SOC、最大放电功率、温差等
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void bmsToPcInfo450(void)
{
	struct can_msg mg;
	unsigned int buff;
	float rc = 0;
	static unsigned char life=0;
	float g_socValueSet=0;  //实际发送给整车
	char tt=100;
	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	life++;
	mg.data[0] = life;   //生命信号

	buff = (unsigned int)(g_socValue*100*2.5);
	mg.data[1] =(unsigned char)buff;// 电池荷电状态SOC 分辨率0.4,单位%

	rc = -BiggestFeedbackPower;
	buff = (unsigned int)(rc*100);	//最大允许回馈功率
	mg.data[2]= buff>>8;//高字节 
	mg.data[3]= (unsigned char)buff;//低字节 

	rc = BiggestDischargePower;
	buff = (unsigned int)(rc*100);	//最大放电功率
	mg.data[4]= buff>>8;//高字节 
	mg.data[5]= (unsigned char)buff;//低字节 

	mg.data[6] = g_highestTemperature - g_lowestTemperature;//单体电池 温度差
	buff = (unsigned int)(PowerVOL*5);
	mg.data[7] =buff; ;//由电池系统编码：0~3电芯厂编码 4~7 BMS编码改为电源电压

	mg.id= 0x000c0450;
	while((!MSCAN2SendMsg(mg))&&(tt>0))
		tt--;
    //MSCAN2SendMsg(mg);
}
//******************************************************************************
//* Function name:   bmsToPcInfo451
//* Description:     发送系统电流、系统电压、单体最高最低电压
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void bmsToPcInfo451(void)
{
    struct can_msg mg;
    unsigned int buff;
    char tt=100;
    
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    buff = (unsigned int)((g_systemCurrent+400)*50);	
	  mg.data[0]= buff>>8;//电池组当前电流高字节 
  	mg.data[1]= (unsigned char)buff;//电池组当前电流低字节 

	  //buff = (unsigned int)(g_highVoltageV1*100);
	  buff = (unsigned int)(g_highVoltageV1*50);
	  mg.data[2]= buff>>8;//电池组当前电压高字节 
	  mg.data[3]= (unsigned char)buff;//电池组当前电压低字节 
	  
	  buff = (unsigned int)(g_highestCellVoltage*10000);
	  mg.data[4]= buff>>8;//电池单体最高电压高字节 
	  mg.data[5]= (unsigned char)buff;//电池单体最高电压低字节
	  
	  buff = (unsigned int)(g_lowestCellVoltage*10000);
	  mg.data[6]= buff>>8;//电池单体最低电压高字节
	  mg.data[7]= (unsigned char)buff;//电池单体最低电压低字节

	  mg.id= 0x000c0451; 
	  //while(!MSCAN2SendMsg(mg));
	  while((!MSCAN2SendMsg(mg))&&(tt>0))
        tt--;
}
//******************************************************************************
//* Function name:   bmsToPcInfo552
//* Description:     继电器控制请求、继电器状态、单体最高最低温度、故障状态
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void bmsToPcInfo552(void)
{
    struct can_msg mg;
    char tt=100;
    
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    mg.data[0]= C0552_0; //测试模式下A口的检测
    mg.data[1]= BmsCtlStat0 & 0xff;//BMS控制状态
    mg.data[2]= (g_highestTemperature-40)+48;//电池最高温度 
	  mg.data[3]= (g_lowestTemperature-40)+48;//电池最低温度 
	  
    mg.data[4]= g_caution_Flag_1; //故障状态
    mg.data[5]= g_caution_Flag_2;
    mg.data[6]= g_caution_Flag_3;
    mg.data[7]= g_caution_Flag_4;
    
	  mg.id= 0x000c0552; 
	  //while(!MSCAN2SendMsg(mg));
	  while((!MSCAN2SendMsg(mg))&&(tt>0))
        tt--;
}
//******************************************************************************
//* Function name:   bmsToPcInfo553
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void bmsToPcInfo553(void)
{
    struct can_msg mg;
    unsigned int buff;
    unsigned char AH=0;
    char tt=100;
    
	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	AH = (unsigned char) g_realNominalCap;
	mg.data[0] = AH; // gpio

	AH = (unsigned char) Q2;
	mg.data[1]= AH;//

	buff = (unsigned int)(Can_g_socValue*100*2.5);
	mg.data[2] =(unsigned char)buff;// 电池荷电状态SOC 分辨率0.4,单位%

	buff = (unsigned int)(CC2VOL*5);
	mg.data[3] =buff ;// 

	//buff = (unsigned int)(g_highVoltageV2*100);
	buff = (unsigned int)(g_highVoltageV2*50);
	mg.data[4]= buff>>8;//电池组当前电压高字节 
	mg.data[5]= (unsigned char)buff;//电池组当前电压低字节

	//buff = (unsigned int)(g_highVoltageV3*100);
	buff = (unsigned int)(g_highVoltageV3*50);
	mg.data[6]= buff>>8;//电池组当前电压高字节 
	mg.data[7]= (unsigned char)buff;//电池组当前电压低字节


	mg.id= 0x000c0553; 
	//while(!MSCAN2SendMsg(mg));
	while((!MSCAN2SendMsg(mg))&&(tt>0))
		tt--;
	 
}
//******************************************************************************
//* Function name:   bmsToPcInfo554
//* Description:     BMS故障及V2，V3电压
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void bmsToPcInfo554(void)
{
    struct can_msg mg;
    char tt=100;
    
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    mg.data[0]= Can554Byte0.byte; 
    mg.data[1]= Can554Byte1.byte; 
    mg.data[2]= Can554Byte2.byte;
    mg.data[3]= Can554Byte3.byte;
    
    mg.data[4]= (DCTem1+48);
    mg.data[5]= (DCTem2+48);
    
    mg.data[6]= 0;
    mg.data[7]= 0;
    
    mg.id= 0x000c0554; 
	  while((!MSCAN2SendMsg(mg))&&(tt>0))
        tt--;
}
//******************************************************************************
//* Function name:   bmsToSBMS信息
//* Description:     控制SBMS
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void bmsToSBMSMessage1(void)
{
	struct can_msg mg;
	char tt=100;

	mg.id= 0x000c0125;
	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	mg.data[0]= InsRelayControl;//绝缘控制继电器的控制 
	mg.data[1]= St_heatManage; 
	mg.data[2]= 0;
	mg.data[3]= 0;

	mg.data[4]= 0; 
	mg.data[5]= 0; 
	mg.data[6]= 0;
	mg.data[7]= 0;
	while((!MSCAN2SendMsg(mg))&&(tt>0))
		tt--;
}
//******************************************************************************
//* Function name:   bmsToPcInfo750
//* Description:     BMS控制电子锁
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
/*void bmsToPcInfo750(void)
{
    struct can_msg mg;
    unsigned int buff;
    char tt=100;
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    mg.data[0]= pc750_group.byte; 
    mg.data[1]= 0; 
    mg.data[2]= 0;
	  mg.data[3]= 0;
	  
    mg.data[4]= 0; 
    mg.data[5]= 0; 
    mg.data[6]= 0;
	  mg.data[7]= 0;
 
    mg.id= 0x000c0750;
    while((!MSCAN2SendMsg(mg))&&(tt>0))
	      tt--; 
	  //MSCAN2SendMsg(mg);
}  */
//**************************************************************
//**************************************************************
//*********************BMS TO BMU********************************
//**************************************************************
//******************************************************************************
//* Function name:   sendBMSIDtoBMU
//* Description:     报文描述：BMS 标识信息；硬件版本、软件版本、通讯协议版本等；
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void sendBMSIDtoBMU(void)   //
{
    struct can_msg mg;
  	unsigned char i;
  	static unsigned char lifeSign =0;
  	
  	mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    lifeSign++;

  	mg.data[0]= DEVICE_SERIAL_NUMBER;
  	mg.data[1]= HARDWARE_VERSION|(SOFTWARE_VERSION<<4);
  	mg.data[2]= COMMUNICATION_VERSION;
  	mg.data[3]= lifeSign;
  	for(i=4;i<8;i++)
  		mg.data[i]=0;

  	mg.id = 0x98FF0100;
  	MSCAN2SendMsg(mg);

}

//******************************************************************************
//* Function name:   sendBMSSFVersionToPC
//* Description:     给BMU发均衡控制命令
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void sendBMSSFVersionToPC(void)
{
    struct can_msg mg;
	 
  	mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    mg.data[0]= BMS_SW_Version[0]; //BMS
    mg.data[1]= BMS_SW_Version[1];; //
    mg.data[2]= BMS_SW_Version[2];; //项目代号
    mg.data[3]= BMS_SW_Version[3];; //年
    mg.data[4]= BMS_SW_Version[4];; //月
    mg.data[5]= BMS_SW_Version[5];; // 版本
    mg.data[6]= BMS_SW_Version[6];; // 版本号
  	mg.data[7]= BMS_SW_Version[7];; //修改次数
  	
  	mg.id = 0x180b0c5a;
  	MSCAN2SendMsg(mg);
}
//******************************************************************************
//* Function name:   sendRealtimeToBMU
//* Description:     给BMU发送BMS当前实时时间
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void sendRealtimeToBMU(void) //给BMU发送BMS当前实时时间
{
    struct can_msg mg;
  	 
  	mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    mg.data[0]= CurrentTime[6]; //年
    mg.data[1]= CurrentTime[5]; //月
    mg.data[2]= CurrentTime[4]; //日
    mg.data[3]= CurrentTime[2]; //时
    mg.data[4]= CurrentTime[1]; //分
    mg.data[5]= CurrentTime[0]; //秒 
    mg.data[6]= 0;
  	mg.data[7]= 0;
  	
  	mg.id = 0x98FF0200;
  	MSCAN2SendMsg(mg);

}

//**************************************************************
//**************************************************************
//*********************BMS TO PC 历史故障***********************
//**************************************************************
//******************************************************************************
//* Function name:   RecordSystem
//* Description:     系统电压、电流、SOC、BMS控制状态
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void RecordSystem(void)//
{
	struct can_msg mg;
	char tt=100;

	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	mg.data[0]= g_storageSysVariableOut[INDEX]>>8;
	mg.data[1]= g_storageSysVariableOut[INDEX];

	mg.data[2]= g_storageSysVariableOut[TOTAL_VOLTAGE]>>8;//电池组当前电压高字节 
	mg.data[3]= g_storageSysVariableOut[TOTAL_VOLTAGE];//电池组当前电压低字节 

	mg.data[4]= g_storageSysVariableOut[TOTAL_CURRENT]>>8;//电池组当前电流高字节 
	mg.data[5]= g_storageSysVariableOut[TOTAL_CURRENT];//电池组当前电流低字节 

	mg.data[6] = g_storageSysVariableOut[PARA_SOC_DISPLAY];// 电池荷电状态SOC 分辨率0.4,单位%

	mg.data[7]= g_storageSysVariableOut[SYS_CONTACTORS_STATE];//BMS控制状态


	mg.id = 0x18ff6000;
	while((!MSCAN2SendMsg(mg))&&(tt>0))
		tt--;
	  
}
//******************************************************************************
//* Function name:   RecordFaultTemperture
//* Description:     故障状态、最高最低温度、平均温度
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void RecordFaultTemperture(void)//
{
    struct can_msg mg;
    char tt=100;
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    mg.data[0]= 0x00;
    mg.data[1]= g_storageSysVariableOut[CAUTION_FLAG_1];
    mg.data[2]= g_storageSysVariableOut[CAUTION_FLAG_2];
    mg.data[3]= g_storageSysVariableOut[CAUTION_FLAG_3];
    mg.data[4]= g_storageSysVariableOut[CAUTION_FLAG_4];
    mg.data[5]= g_storageSysVariableOut[CELL_MAX_TEM];//电池最高温度 
    mg.data[6]= g_storageSysVariableOut[CELL_MIN_TEM];//电池最低温度 
    mg.data[7]= g_storageSysVariableOut[CELL_AVERAGE_TEM];//电池平均温度
    
    mg.id = 0x18ff6001;
	  //MSCAN2SendMsg(mg);
    while((!MSCAN2SendMsg(mg))&&(tt>0))
	      tt--;
}
//******************************************************************************
//* Function name:   RecordRealtime
//* Description:     系统时间
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void RecordRealtime(void)//
{
    struct can_msg mg;
    char tt=100;
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;

    mg.data[0]= g_storageSysVariableOut[SYS_REALTIME_SECOND];
    mg.data[1]= g_storageSysVariableOut[SYS_REALTIME_MINUTE];
    mg.data[2]= g_storageSysVariableOut[SYS_REALTIME_HOUR];
    mg.data[3]= g_storageSysVariableOut[SYS_REALTIME_WEEK];
    mg.data[4]= g_storageSysVariableOut[SYS_REALTIME_DAY];
    mg.data[5]= g_storageSysVariableOut[SYS_REALTIME_MONTH];// 
    mg.data[6]= g_storageSysVariableOut[SYS_REALTIME_YEAR];//
    mg.data[7]= 0x00;//

    mg.id = 0x18ff6002;
	  //MSCAN2SendMsg(mg);
	  while((!MSCAN2SendMsg(mg))&&(tt>0))
	      tt--;
}
//******************************************************************************
//* Function name:   RecordExtremCellVoltage
//* Description:     单体最高最低电压、平均电压
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void RecordExtremCellVoltage(void)//
{

    struct can_msg mg;
    char tt=100;
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    mg.data[0]= g_storageSysVariableOut[CELL_MAX_VOLTAGE]>>8;
    mg.data[1]= g_storageSysVariableOut[CELL_MAX_VOLTAGE];
    mg.data[2]= g_storageSysVariableOut[CELL_MIN_VOLTAGE]>>8;
    mg.data[3]= g_storageSysVariableOut[CELL_MIN_VOLTAGE];
    mg.data[4]= g_storageSysVariableOut[CELL_AVERAGE_VOLTAGE]>>8;
    mg.data[5]= g_storageSysVariableOut[CELL_AVERAGE_VOLTAGE];
    mg.data[6]= 0x00;
    mg.data[7]= 0xC8;//
    
    mg.id = 0x18ff6003;
	  //MSCAN2SendMsg(mg);
	  while((!MSCAN2SendMsg(mg))&&(tt>0))
	      tt--; 
}
//******************************************************************************
//* Function name:   RecordInsulation
//* Description:     正负绝缘电阻值、1路电压对应的K值B值
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void RecordInsulation(void)//
{

    struct can_msg mg;
    char tt=100;
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    mg.data[0]= g_storageSysVariableOut[SYS_INSULATION_P]>>8;
    mg.data[1]= g_storageSysVariableOut[SYS_INSULATION_P];
    mg.data[2]= g_storageSysVariableOut[SYS_INSULATION_N]>>8;
    mg.data[3]= g_storageSysVariableOut[SYS_INSULATION_N];
    mg.data[4]= g_storageSysVariableOut[VOLT_K1]>>8;
    mg.data[5]= g_storageSysVariableOut[VOLT_K1];
    mg.data[6]= g_storageSysVariableOut[VOLT_B1]>>8;
    mg.data[7]= g_storageSysVariableOut[VOLT_B1];//
    
    mg.id = 0x18ff6004;
    while((!MSCAN2SendMsg(mg))&&(tt>0))
	      tt--;
	  //MSCAN2SendMsg(mg); 
}
//******************************************************************************
//* Function name:   RecordVoltKB
//* Description:     2、3路电压对应的K值B值
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void RecordVoltKB(void) 
{    
    struct can_msg mg;
    char tt=100;
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    mg.data[0]= g_storageSysVariableOut[VOLT_K2]>>8;
    mg.data[1]= g_storageSysVariableOut[VOLT_K2];
    mg.data[2]= g_storageSysVariableOut[VOLT_B2]>>8;
    mg.data[3]= g_storageSysVariableOut[VOLT_B2];
    mg.data[4]= g_storageSysVariableOut[VOLT_K3]>>8;
    mg.data[5]= g_storageSysVariableOut[VOLT_K3];
    mg.data[6]= g_storageSysVariableOut[VOLT_B3]>>8;
    mg.data[7]= g_storageSysVariableOut[VOLT_B3];//
    
    mg.id = 0x18ff6005;
	  //MSCAN2SendMsg(mg); 
    while((!MSCAN2SendMsg(mg))&&(tt>0))
	      tt--;

}
//******************************************************************************
//* Function name:   RecordEndFlag
//* Description:     所有单体电压
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void RecordCellVoltage(unsigned char number)//
{

    struct can_msg mg;
    char tt=100;
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    /*
    mg.data[0]= g_storageSysVariable[CELL_VOLTAGE_0+4*number]>>8;
    mg.data[1]= g_storageSysVariable[CELL_VOLTAGE_0+4*number];
    mg.data[2]= g_storageSysVariable[CELL_VOLTAGE_1+4*number]>>8;
    mg.data[3]= g_storageSysVariable[CELL_VOLTAGE_1+4*number];
    mg.data[4]= g_storageSysVariable[CELL_VOLTAGE_2+4*number]>>8;
    mg.data[5]= g_storageSysVariable[CELL_VOLTAGE_2+4*number];
    mg.data[6]= g_storageSysVariable[CELL_VOLTAGE_3+4*number]>>8;;
    mg.data[7]= g_storageSysVariable[CELL_VOLTAGE_3+4*number];//
    */
    mg.data[0]= g_storageSysVariableCellOut[CELL_VOLTAGE_0+4*number]>>8;
    mg.data[1]= g_storageSysVariableCellOut[CELL_VOLTAGE_0+4*number];
    mg.data[2]= g_storageSysVariableCellOut[CELL_VOLTAGE_1+4*number]>>8;
    mg.data[3]= g_storageSysVariableCellOut[CELL_VOLTAGE_1+4*number];
    mg.data[4]= g_storageSysVariableCellOut[CELL_VOLTAGE_2+4*number]>>8;
    mg.data[5]= g_storageSysVariableCellOut[CELL_VOLTAGE_2+4*number];
    mg.data[6]= g_storageSysVariableCellOut[CELL_VOLTAGE_3+4*number]>>8;;
    mg.data[7]= g_storageSysVariableCellOut[CELL_VOLTAGE_3+4*number];//
    
    mg.id = 0x18ff6100+number;
	  //MSCAN2SendMsg(mg); 
    while((!MSCAN2SendMsg(mg))&&(tt>0))
	      tt--;
}
//******************************************************************************
//* Function name:   RecordEndFlag
//* Description:     历史记录发送完毕报文
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void RecordEndFlag(void)//表示发送完成
{
    struct can_msg mg;
    unsigned char i=0;
    char tt=100;
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;

    for(i=0;i<8;i++)
        mg.data[i]= 0xEE;
    
    mg.id = 0x18ff0000;
	  //MSCAN2SendMsg(mg);
	  while((!MSCAN2SendMsg(mg))&&(tt>0))
	      tt--; 
}
//******************************************************************************
//* Function name:   ReadAHRecord
//* Description:     读取存储安时数(充电与放电)
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void ReadAHRecord(void)//
{

    struct can_msg mg; 
    char i=0,t=100; 
    unsigned long Buffer=0;
    unsigned int  Buffer1=0;
       
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    Buffer=chargeAH;
    //Buffer=0x00123456;
    for(i=2;i>=0;i--)
    {      
        mg.data[i]=Buffer;//[0]~[2]为高到底
        Buffer=Buffer>>8;
    }
    
    Buffer=dischargeAH;
    //Buffer=0x00654321;
    for(i=5;i>=3;i--)
    {      
        mg.data[i]=Buffer;//[3]~[5]为高到底
        Buffer=Buffer>>8;
    }
    
    Buffer1=Charge_Times;
    for(i=7;i>=6;i--)
    {      
        mg.data[i]=Buffer1;//[3]~[5]为高到底
        Buffer1=Buffer1>>8;
    }
        
    mg.id = 0xC0AAA;    
	  while((MSCAN2SendMsg(mg)==FALSE)&&(t>0))
	      t--; 

}
//******************************************************************************
//* Function name:   InTestToPC
//* Description:     向PC返回测试模式
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void InTestToPC(void)//
{

    struct can_msg mg; 
    char i=0,t=100; 
    unsigned long Buffer=0;
       
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    mg.data[0]=0x55;
    mg.data[1]=0xaa;
     
    mg.id = 0xC01EE4F;    
	  while((MSCAN2SendMsg(mg)==FALSE)&&(t>0))
	      t--; 

}
//***********************************************************************
//************************************************************************
//*************************the end*************************************
//************************************************************************

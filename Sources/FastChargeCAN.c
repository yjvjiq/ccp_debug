//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : S178
//* File Name          : FastChargeCAN.c
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2016.1.12
//* Description        : 该文件负责发送直流快充CAN的所有报文内容
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "BMS20.h"
//********************************************************************************
//*******************************************************************************

unsigned char BEMError1=0xf0;
unsigned char BEMError2=0xf0;
unsigned char BEMError3=0xf0;
unsigned char BEMError4=0xf0;

unsigned char PGN[3] = 0;
//**********************************************************************************
//**********************************************************************************
//*******快充消息子程序**********/////////
//*******报文管理**********/////////
//**********************************************************************************
//**********************************************************************************
//******************************************************************************
//* Function name:   cpuToCHMBRM
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBHM(void)
{
	struct can_msg mg;
	char tt=100;
	unsigned int buff;
	mg.RTR= FALSE;  
	mg.len = 2;
	mg.prty = 0;

	buff = HIGHEST_ALLOWED_CHARGE_V*10;

	mg.data[0] = buff;     //最高允许充电电压低字节
	mg.data[1] = buff>>8;  //最高允许充电电压高字节

	mg.id= 0x182756f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
		while((!MSCAN1SendMsg(mg))&&(tt>0))
			tt--;
	else if((g_BmsModeFlag == RECHARGING)) 
		while((!MSCAN0SendMsg(mg))&&(tt>0))
			tt--;         
}
//******************************************************************************
//* Function name:   cpuToCHMBRM
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBRM(void)
{
    struct can_msg mg;
    char tt=100;
    unsigned char Num = 6;
    unsigned char ByteNum = 0x29;
    
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    if(DC_Vesion==2)
    {
        Num = 7;
        ByteNum=0x31;
    }
    
    
	mg.data[0] = 0x10;  //控制字：16
	mg.data[1] = ByteNum;  //整个消息大小,49byte
	mg.data[2] = 0x00;  //整个消息大小
	mg.data[3] = Num;  //全部数据包的数目
	mg.data[4] = 0xff;//保留给SAE设定使用，该字节应设为FF
	mg.data[5] = 0x00;//所装载数据的参数群编号 快充对应的PGN号：0x000200
	mg.data[6] = 0x02;//所装载数据的参数群编号 快充对应的PGN号：0x000200
	mg.data[7] = 0x00;//所装载数据的参数群编号 快充对应的PGN号：0x000200

	mg.id= 0x1cec56f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
		while((!MSCAN1SendMsg(mg))&&(tt>0))
			tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
} 
//******************************************************************************
//* Function name:   cpuToCHMBRMDATA1
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBRMDATA1(void)
{
    struct can_msg mg;
    unsigned int buff;
    char tt=100;
    
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
    mg.data[0] = 0x01;
    mg.data[1] = 0x01;
    mg.data[2] = 0x01;  //BMS通信协议版本号
    mg.data[3] = 0x00;  
    mg.data[4] = CELL_TYPE;//磷酸铁锂 
    
	buff = (unsigned int)(SetCap*10);//动力电池系统额定容量:150Ah
	mg.data[5] = (unsigned char)buff;  
	mg.data[6] = buff>>8;

	buff = SYS_NOMINAL_V*10;//652.8V
	mg.data[7] = (unsigned char)buff;//动力电池系统额定电压

	mg.id= 0x1ceb56f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
		while((!MSCAN1SendMsg(mg))&&(tt>0))
			tt--;
    else if(g_BmsModeFlag == RECHARGING) 
		while((!MSCAN0SendMsg(mg))&&(tt>0))
			tt--; 
} 
//******************************************************************************
//* Function name:   cpuToCHMBRMDATA2
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBRMDATA2(void)
{
	struct can_msg mg;
	unsigned int buff;
	char tt=100;

	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	mg.data[0] = 0x02;

	buff = SYS_NOMINAL_V*10;//动力电池系统额定电压 
	mg.data[1] = buff>>8;
	mg.data[2] = 0xff; 
	mg.data[3] = 0xff; 
	mg.data[4] = 0xff;
	mg.data[5] = 0xff;
	mg.data[6] = 0xff;
	mg.data[7] = 0xff;

	mg.id= 0x1ceb56f4;
	  
	  if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
} 
//******************************************************************************
//* Function name:   cpuToCHMBRMDATA3
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBRMDATA3(void)
{
	struct can_msg mg;
	char tt=100;
	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	mg.data[0] = 0x03;
	mg.data[1] = 0xff;
	mg.data[2] = 0xff; 
	mg.data[3] = 0xff; 
	mg.data[4]= 0xff;
	mg.data[5]= 0xff;
	mg.data[6]= 0xff;
	mg.data[7]= 0xff;

	mg.id= 0x1ceb56f4;
	    
	  if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
} 
//******************************************************************************
//* Function name:   cpuToCHMBRMDATA4
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBRMDATA4(void)
{
	struct can_msg mg;
	char tt=100;
	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	mg.data[0] = 0x04;
	mg.data[1] = 0xff;
	mg.data[2] = 0x01; 
	mg.data[3] = 0xff; 
	mg.data[4]= 0xff;
	mg.data[5]= 0xff;
	mg.data[6]= 0xff;
	mg.data[7]= 0xff;

	mg.id= 0x1ceb56f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
} 
//******************************************************************************
//* Function name:   cpuToCHMBRMDATA5
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBRMDATA5(void)
{
	struct can_msg mg;
	char tt=100;

	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	mg.data[0] = 0x05;
	mg.data[1] = 0xff;
	mg.data[2] = 0xff; 
	mg.data[3] = 0xff; 
	mg.data[4]= 0xff;
	mg.data[5]= 0xff;
	mg.data[6]= 0xff;
	mg.data[7]= 0xff;

	mg.id= 0x1ceb56f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
} 
//******************************************************************************
//* Function name:   cpuToCHMBRMDATA6
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBRMDATA6(void)
{
	struct can_msg mg;
	char tt=100;

	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	mg.data[0] = 0x06;
	mg.data[1] = 0xff;
	mg.data[2] = 0xff; 
	mg.data[3] = 0xff; 
	mg.data[4]= 0xff;
	mg.data[5]= 0xff;
	mg.data[6]= 0xff;
	mg.data[7]= 0xff;

	mg.id= 0x1ceb56f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)){
		while((!MSCAN1SendMsg(mg))&&(tt>0)){
			tt--;
		}
	}
	else if(g_BmsModeFlag == RECHARGING){
		while((!MSCAN0SendMsg(mg))&&(tt>0)){
			tt--;
		}
	}
}
//******************************************************************************
//* Function name:   cpuToCHMBRMDATA7
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBRMDATA7(void)
{
    struct can_msg mg;
    char tt=100;
    
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
	mg.data[0] = 0x07;
	mg.data[1] = 0xff;
	mg.data[2] = 0xff; 
	mg.data[3] = 0xff; 
	mg.data[4] = 0xff;
	mg.data[5] = 0xff;
	mg.data[6] = 0xff;
	mg.data[7] = 0xff;

	mg.id= 0x1ceb56f4;
	  
	  if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
}  
//******************************************************************************
//* Function name:   cpuToCHMBCP
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBCP(void)
{
	struct can_msg mg;
	char tt=100;

	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	mg.data[0] = 0x10;//CW
	mg.data[1]=  0x0d;//ByteL
	mg.data[2]=  0x00;//ByteH
	mg.data[3]=  0x02;//Pack
	mg.data[4]=  0xff;//Void
	mg.data[5]=  0x00;//PGN 
	mg.data[6]=  0x06;//PGN
	mg.data[7]=  0x00;//PGN 

	mg.id= 0x1cec56f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
 }
 //******************************************************************************
//* Function name:   cpuToCHMBCPDATA1
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
 void cpuToCHMBCPDATA1(void)
{
	struct can_msg mg;
	unsigned int buff;
	char tt=100;

	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	mg.data[0] = 0x01;
	
	buff = (unsigned int)(HIGHEST_ALLOWED_CHARGE_CV*100);
	mg.data[1]= (unsigned char)buff;//单体最高允许充电电压
	mg.data[2]= buff>>8;//单体最高允许充电电压

	if(g_BmsModeFlag == FASTRECHARGING){
		buff = (unsigned int)((400 - FastChg_Max_Current)*10);//已经乘以0.75了
	}
	else if(g_BmsModeFlag == RECHARGING){
		buff = (unsigned int)((400 - EleBand_Max_Current)*10);//已经乘以0.75了
	}
	mg.data[3]= (unsigned char)buff;//动力最大允许电流低字节
	mg.data[4]= buff>>8;//动力电池最大允许电流高字节

	buff = SYS_KWH*10;
	mg.data[5]= (unsigned char)buff;//动力电池系统额定能量 
	mg.data[6]= buff>>8;//动力电池系统额定能量

	buff = (unsigned int)(HIGHEST_ALLOWED_CHARGE_V * 10);
	mg.data[7]= (unsigned char)buff;//最高允许动力电池系统 总电压低字节

	mg.id= 0x1ceb56f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
 }
 //******************************************************************************
//* Function name:   cpuToCHMBCPDATA2
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
 void cpuToCHMBCPDATA2(void)
{
	struct can_msg mg;
	unsigned int buff;
	char tt=100;

	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;

	mg.data[0] = 0x02;

	buff = (unsigned int)(HIGHEST_ALLOWED_CHARGE_V*10);
	mg.data[1]= buff>>8;//最高允许动力电池系统 总电压高字节
	mg.data[2] = HIGHEST_ALLOWED_CHARGE_T + 50;// the allowed highest temperature = 105-50=55 C

	buff = (unsigned int)(Can_g_socValue*1000); 
	mg.data[3]= (unsigned char)buff;//SOC
	mg.data[4]= buff>>8;

	buff = (unsigned int)(g_systemVoltage*10);
	mg.data[5]= (unsigned char)buff;//系统总电压低字节
	mg.data[6]= buff>>8; //系统总电压高字节
	mg.data[7]= 0xff;

	mg.id= 0x1ceb56f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
		while((!MSCAN1SendMsg(mg))&&(tt>0))
			tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
 }
//******************************************************************************
//* Function name:   cpuToCHMBRO
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBRO(void)
{
	struct can_msg mg;
	char tt=100;

	mg.RTR= FALSE;  
	mg.len = 1;
	mg.prty = 0;
    
     if(((BROErrorAA==0) && ((Relay_State >> 2) & 0x01 == 0x01) && (g_BmsModeFlag == FASTRECHARGING)) // KFastChg_P_Switch(ON) then send 0xAA.
		|| ((BROErrorAA==0) && (status_group2.Bit.St_Ele_Relay == 2) && (g_BmsModeFlag == RECHARGING)) // KFastChg_P_Switch(ON) then send 0xAA.
	){
        mg.data[0] = 0xaa;
    }
    else if(BROErrorAA==1){
        mg.data[0] = 0x00;
    }
    
	mg.id= 0x100956f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--;  
}
//******************************************************************************
//* Function name:   cpuToCHMBCL
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBCL(void)
{
	struct can_msg mg;
	unsigned int buff;
	char tt=100;

	mg.RTR= FALSE;  
	mg.len = 5;
	mg.prty = 0;


	buff = (unsigned int)(m_askvoltage*10);
	mg.data[0]= (unsigned char)buff;//电压需求
	mg.data[1]= buff>>8;

	buff = (unsigned int)((400 - m_askcurrent)*10);
	mg.data[2]= (unsigned char)buff;//电流需求
	mg.data[3]=  buff>>8;
	mg.data[4] = m_chmmode;//恒流控制

	mg.id= 0x181056f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)){ 
		while((!MSCAN1SendMsg(mg))&&(tt>0)){
			tt--;
		}
	}
	else if(g_BmsModeFlag == RECHARGING){ 
		while((!MSCAN0SendMsg(mg))&&(tt>0)){
			tt--;   
		}
	}
}
//******************************************************************************
//* Function name:   cpuToCHMBCS
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBCS(void)
{
    struct can_msg mg;
    char tt=100;
    
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
	  mg.data[0]= 0x10;//
	  mg.data[1]= 0x09;	
	  mg.data[2]= 0x00;//
  	mg.data[3]= 0x02;//  
	  mg.data[4]= 0xff;// 
	  mg.data[5]= 0x00;//
	  mg.data[6]= 0x11;	  
    mg.data[7]= 0x00;
    
    mg.id= 0x1cec56f4;
    
   	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--;   
} 
//******************************************************************************
//* Function name:   cpuToCHMBCSDATA1
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBCSDATA1(void)
{
	struct can_msg mg;
	unsigned int buff;
	char tt=100;

	mg.RTR= FALSE;  
	mg.len = 8;
	mg.prty = 0;


	mg.data[0]= 0x01;
	buff = (unsigned int)(g_systemVoltage*10);//电池组当前电压高字节 
	mg.data[1]= (unsigned char)buff;         //电池组当前电压di字节 
	mg.data[2]= buff>>8;//电池组当前电流高字节 

	buff = (unsigned int)((g_systemCurrent+400)*10);
	mg.data[3]= (unsigned char)buff;//电池组当前电流低字节 
	mg.data[4]= buff>>8;//电池组当前电流高字节 

	buff = (unsigned int)(g_highestCellVoltage*100);	   
	mg.data[5]= (unsigned char)buff;//电池单体最高电压低字节
	mg.data[6]= buff>>8;//电池单体最高电压高字节

	buff = (unsigned int)(Can_g_socValue*100); 
	mg.data[7]= (unsigned char)buff;//SOC at present

	mg.id= 0x1ceb56f4;
    
    if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
            
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--;  
}
//******************************************************************************
//* Function name:   cpuToCHMBCSDATA2
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBCSDATA2(void)
{
    struct can_msg mg;
    char tt=100;
    
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    if((g_systemCurrent<=-5)&&(Can_g_socValue<0.992))
        DCLeftTime=(unsigned int)((Q2*(1-Can_g_socValue)*60)/(-g_systemCurrent));
    else if(Can_g_socValue>=0.992)
        chargeRemainderTime=2;
    chargeRemainderTime=DCLeftTime*60;
	
	mg.data[0]= 0x2;//
	mg.data[1]=(unsigned char)DCLeftTime;//	
	mg.data[2]= DCLeftTime>>8;//
	mg.data[3]= 0xff;//
	mg.data[4]= 0xff;// 
	mg.data[5]= 0xff;// 
	mg.data[6]= 0xff;// 	  
	mg.data[7]= 0xff;//
    
    mg.id= 0x1ceb56f4;
    
    if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
} 
//******************************************************************************
//* Function name:   cpuToCHMBSM
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBSM(void)
{
    struct can_msg mg;
    char tt=100;
    
	mg.RTR= FALSE;
	mg.len = 7;
	mg.prty = 0;

	mg.data[0]= g_bms_msg.CellVoltageMaxPackNum - 1;
	mg.data[1]= g_bms_msg.CellTempMax + 10; // offset: -40+50
	mg.data[2]= g_bms_msg.CellTempMaxPackNum - 1;
	mg.data[3]= g_bms_msg.CellTempMin + 10; // offset: -40+50
	mg.data[4]= g_bms_msg.CellTempMinPackNum - 1;
	mg.data[5]= fasterror11;
	mg.data[6]= fasterror12;

	mg.id= 0x181356f4;
    
    if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278))
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
}
//******************************************************************************
//* Function name:   cpuToCHMBST
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
//void cpuToCHMBMV(void); //可选项，单体电压
//void cpuToCHMBMT(void); //可选项，单体温度
//void cpuToCHMBSP(void); //可选项，温度
void cpuToCHMBST(void)  
{    
	struct can_msg mg;
	char tt=100;

	mg.RTR= FALSE;  
	mg.len = 4;
	mg.prty = 0;

	mg.data[0]= fastend1;
	mg.data[1]= fastend2;
	mg.data[2]= fastend3;
	mg.data[3]= fastend4;

	mg.id= 0x101956f4;

	if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
		while((!MSCAN1SendMsg(mg))&&(tt>0))
			tt--;
    else if(g_BmsModeFlag == RECHARGING) 
		while((!MSCAN0SendMsg(mg))&&(tt>0))
			tt--; 
} 
//******************************************************************************
//* Function name:   cpuToCHMBSD
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBSD(void)
{
    struct can_msg mg;
    unsigned int buff;
    char tt=100;
    
    mg.RTR= FALSE;  
    mg.len = 7;
    mg.prty = 0;
    
	  mg.data[0]= (unsigned char)(Can_g_socValue*100);//soc

    buff = (unsigned int)(g_lowestCellVoltage*100);	   
	  mg.data[1]= (unsigned char)buff;//电池单体最高电压低字节
	  mg.data[2]= buff>>8;//电池单体最高电压高字节
	  
	  buff = (unsigned int)(g_highestCellVoltage*100);	   
	  mg.data[3]= (unsigned char)buff;//电池单体最高电压低字节
	  mg.data[4]= buff>>8;//电池单体最高电压高字节
	  
	  mg.data[5]= g_lowestTemperature+10;//电池最低温度-40+50	  
	  mg.data[6]= g_highestTemperature+10;//电池最高温度 
	  
    mg.id= 0x181c56f4;
    
    if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
} 
//******************************************************************************
//* Function name:   cpuToCHMBEM
//* Description:     
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void cpuToCHMBEM(void)
{
    struct can_msg mg;
    char tt=100;
    
    mg.RTR= FALSE;  
    mg.len = 4;
    mg.prty = 0;
    
	  mg.data[0]=BEMError1;   
	  mg.data[1]=BEMError2; 
	  mg.data[2]=BEMError3;
	  mg.data[3]=BEMError4;
	  
    mg.id= 0x081e56f4;
    
    if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
}
//******************************************************************************
//* Function name:   J1939_TP_CM_Abort
//* Description:     放弃连接
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void J1939_TP_CM_Abort(void)
{
    struct can_msg mg;
    char tt=100;
    
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    
	  mg.data[0]=0xff;   
	  mg.data[1]=0xff; 
	  mg.data[2]=0xff;
	  mg.data[3]=0xff;
	  mg.data[4]=0xff;   
	  mg.data[5]=PGN[0]; 
	  mg.data[6]=PGN[1];
	  mg.data[7]=PGN[2];
	  
    mg.id= 0x1cec56f4;
    
    if((g_BmsModeFlag == FASTRECHARGING)||(PROJECT_NAME==278)) 
	      while((!MSCAN1SendMsg(mg))&&(tt>0))
            tt--;
    else if(g_BmsModeFlag == RECHARGING) 
	      while((!MSCAN0SendMsg(mg))&&(tt>0))
            tt--; 
}  
//***********************************************************************
//************************************************************************
//*************************the end*************************************
//************************************************************************

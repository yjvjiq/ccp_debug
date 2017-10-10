//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : InitBMS.c
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2014.5.7
//* Description        : 该文件用于整个项目系统初始化，包括SOC初始化、参数初始化、还有中断优先级设置
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "BMS20.h" 
//
float g_defaultSysParameters[ParamNUMBER] =
{
    0.7,//SOC 实际值
    0,//主正继电器粘连
    37.0,//单体电池容量AH SINGLE_CAPACITY
    37.0, //电池组总容量  WHOLE_CAPACITY
    2.0,//BMU数量BMU_NUMBER

    0.1,//单体电压均衡值DIFFERENCE_SINGLE_V
    15.0,//电池温度均衡值DIFFERENCE_SINGLE_T
    3.2,//均衡开启电压
    4.3,//均衡关闭电压
    0.95, //soc 高

    0.98, //soc 过高
    0.15, //soc 低
    0.10,//SOC 过低
    346.0,//总电压值WHOLE_VOLTAGE
    355.0,//总电压极高

    259.0,   //总电压低
    235.0,//总电压极低
    3.65,//单体过压值O_VOLTAGE
    3.7,//单体电压极高
    2.75,//单体电压值低L_VOLTAGE

    2.45, //单体电压极低
    50.0,//过温值O_TEMPERATURE
    55.0, //温度极高
    0.0,//温度过低值L_TEMPERATURE
    -25,  //温度极低

    0.25,  //电压一致性差
    0.5, //电压一致性极差
    20.0,  //温度一致性差
    25.0,//温度一致性极差
    320.0,//电流值过流

    403,  //最大允许充电端电压
    120.0,//最大允许充电电流
    1000.0,//最大充电电流允许时间  单位min
    120.0,//最大允许放电电流
    1000.0, //最大放电电流允许时间  单位min

    40.0, //绝缘电阻过低值 单位M欧
    200.0,// 绝缘电阻低值 单位M欧

    96.0// 不能超过100
};

unsigned int g_oldTime[7];
unsigned char g_BmsModeFlag; //3:快充充电2:慢充充电 1:放电
unsigned char OCVState = 0;//0:OCV没有发生,1：OCV已经发送
//******************************************************************************
//* Function name:   delay
//* Description:     延时子程序              
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void delay(unsigned int t) 
{ 
    while(t--); 
}
//******************************************************************************
//* Function name:   InitialBMS
//* Description:     BMS系统上电参数初始化             
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void InitialBMS(void)
{
    unsigned char SetTime[7];
    	
    TurnOff_ALL();// Turn off all relays. then check their state.
    
    status_group1.Bit.St_BMS = 3;           //高压断开  上电发无效值
    status_group2.Bit.St_Ele_Relay = 1;     //受电弓继电器未连接
    status_group2.Bit.St_CHG_Connect = 1;   //充电连接状态未连接
    status_group3.Bit.St_Charge = 3;        //充电状态设置为无效
    
    //TurnOn_CC2();//12V系统 屏蔽就是24V
    g_sysPara[PARA_BMU_NUMBER]=BMU_NUMBER;
		
	if(ENDFLAG != ReadEndFlag())   //ENDFLAG=98 //是否要下载出厂参数？
	{
		InitDefaultParam();
		//设置时钟
		SetTime[0]=1;//秒
		SetTime[1]=21;//分
		SetTime[2]=14;//时

		SetTime[3]=3;//星期
		SetTime[4]=18;//日
		SetTime[5]=6;//月
		SetTime[6]=12;//年
		I2CWriteDate(SetTime);  //设置初始时间
	}
     
	LoadParamter();   //系统参数初始化
	StoreParameter();

	KB_DATA_RECALL();//调用绝缘检测的系数，为绝缘做准备。

	g_errorCounter=ReadErrorIndex(); //读出当前故障记录条数
	//g_errorCounter=0;

	parametersClean();  //一些全局变量清零

	I2CReadDate();  //读取系统时间
	g_oldTime[0] = CurrentTime[0];  //秒
	g_oldTime[1] = CurrentTime[1];  //分

	if(StoreAHState==1)
		ReadChargeDischargeAH();//读出累积充放电的AH容量
    //state_group3.Bit.St_BMS_Operation = 1;//初始化状态
}
//******************************************************************************
//* Function name:   InitialSoc
//* Description:     SOC上电初始化：读取保存在24c64中的SOC值，计算剩余容量        
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void InitialSoc(void)
{
    //if(OCVState == 0)//如果没有进行OCV修正,则调用上一次的值
    {
        g_socValue = ReadOutSocStoreValue(); //SOC实际值，但不是显示值    
        g_realNominalCap = ReadOutQ1StoreValue();//读取Q1值
    }
    //当OCVState==1,Q1:g_realNominalCap与g_socValue在OCV函数中赋值
    Can_g_socValue = ReadOutCanSocStoreValue();//SOC显示值
    First_g_socValue = g_socValue;
    StoreAHSOC = g_socValue;
    Can_g_socValue_Start = Can_g_socValue;
	
	if(g_socValue < 0)
	{
		g_socValue = 0.22;
	}
	if(Can_g_socValue < 0)
	{
		Can_g_socValue = 0.44;
	}
	
	g_originalCapacity = SYS_NOMINAL_AH;
	if(g_realNominalCap >= g_originalCapacity)
	{
		g_realNominalCap = g_originalCapacity;
	}
	
	Q2 = Q2nominalCalculate(g_realNominalCap); //计算出额定容量
	if(Q2 >= g_realNominalCap)
	{
		Q2=g_realNominalCap;
	}
	
	g_leftEnergy = g_socValue*(g_realNominalCap*3600);  //剩余容量(上电时的容量	  
	g_energyOfUsed = 0;      
}
//******************************************************************************
//* Function name:   ReadEndFlag
//* Description:     第一次上电标志位读取函数     
//* EntryParameter : None
//* ReturnValue    : 返回0xffff表示第一次， !=0xffff,表示非第一次
//******************************************************************************
float ReadEndFlag(void)
{
		//float flag[1];
  	unsigned int	Endflag[2];
  	
    Read24c64_Byte(ENDFLAG_ADDR,(unsigned char* )Endflag,4); 
  	
  	if((Endflag[0]==0xffff)&&(Endflag[1]!=0xffff))
  	    Endflag[0] = Endflag[1];

  	return (Endflag[0]);
}
//******************************************************************************
//* Function name:   InitDefaultParam
//* Description:     将出厂默认参数写入24c65  
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void InitDefaultParam(void)
{	
    DataBuffer[0] = ENDFLAG;
    DataBuffer[1] = ENDFLAG;
    Write24c64_Byte(ENDFLAG_ADDR,(unsigned char* )DataBuffer,4);//write the endflag into 24c64 at 0x0100 
  	g_defaultSysParameters[PARA_ENDFLAG]= ENDFLAG;	
  	Write24c64_Byte(ParaBaseAddr,(unsigned char* )g_defaultSysParameters,ParamNUMBER*4);//写入初始参数到空间24c64 0x0000
}

//******************************************************************************
//* Function name:   Interrupt_Priority_Set
//* Description:     中断优先级设置函数
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void Interrupt_Priority_Set(void)
{     
    
    INT_CFADDR=0xA0;     
    INT_CFDATA5=0x03;     //CAN1
    
    INT_CFADDR=0xB0;     
    INT_CFDATA1=0x04;     //CAN0
    
    INT_CFADDR=0x70;     
    INT_CFDATA5=0x05;     //pit 
    
    INT_CFADDR=0xF0;     //RIT
    INT_CFDATA0=0x06;
         
    INT_CFADDR=0xD0;      //ad0
    INT_CFDATA1=0x07;
    
    
}

//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
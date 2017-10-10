//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : bmn.C
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,05,26
//* Description        : 本程序用于计算总电压v1,v2,v3和绝缘阻值Rp,Rn
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

#include "derivative.h"  /* include peripheral declarations */
#include "BMS20.h"               

/////////////////////////////////////////////////////////////////////////////////////////
// Defines
#define Filter_N                10         //滤波采样点数目,6s采一个点
/////////////////////////////////////////////////////////////////////////////////////////

Bool BMN_CAN4_Enable = FALSE;             //标定CAN    500kbsp
Bool BMN_WATCHDOG_Enable = FALSE;          //看门狗标志
//
//BMN参数变量
BMNVPNFLAG   BMNVPNflag;///
unsigned int Vpn1_Voltage_AD_Value=0;        //电池总电压1采样值     0.01V  100~500V   100.00~500.00
//unsigned int Vpn1_Voltage_CAL_Value=0;       //电池总电压1计算值     0.01V  100~500V   100.00~500.00
long Vpn1_Voltage_CAL_Value=0;       //电池总电压1计算值     0.01V  100~500V   100.00~500.00
unsigned int Vpn2_Voltage_AD_Value=0;        //电池总电压2采样值     0.01V  100~500V   100.00~500.00
//unsigned int Vpn2_Voltage_CAL_Value=0;       //电池总电压2计算值     0.01V  100~500V   100.00~500.00
long Vpn2_Voltage_CAL_Value=0;       //电池总电压2计算值     0.01V  100~500V   100.00~500.00
unsigned int Vpn3_Voltage_AD_Value=0;        //电池总电压3采样值     0.01V  100~500V   100.00~500.00
//unsigned int Vpn3_Voltage_CAL_Value=0;       //电池总电压3计算值     0.01V  100~500V   100.00~500.00
long Vpn3_Voltage_CAL_Value=0;       //电池总电压3计算值     0.01V  100~500V   100.00~500.00

float V51_Voltage_CAL_Value=0;                 //V5两端电压值（开关1闭合，开关2断开）
float V52_Voltage_CAL_Value=0;                  //V5两端电压值（开关1断开，开关2闭合）
float voltage_buffer2;

unsigned int   V51_Voltage_AD_Value; 
unsigned int  V52_Voltage_AD_Value;

float g_highVoltageV1; //V1A   电池电压 
float g_highVoltageV2; //V2A   预充电继电器与预充电阻之间的电压
float g_highVoltageV3; //V3A   预充电继电器另一边的电压
 
unsigned long RR_Vp_GND_Value;           //总正对地绝缘电阻 0.01M 0.01M~50M  1~5000 
unsigned long RR_Vn_GND_Value;           //总负对地绝缘电阻 0.01M 0.01M~50M  1~5000 

float Rp_Vpn_Value=2000;              //总正对地绝缘电阻等级 10欧/V 1~500  1~5000 
float Rn_Vpn_Value=2000;              //总负对地绝缘电阻等级 10欧/V 1~500  1~5000

unsigned int Vpn_K1;
int Vpn_B1;
unsigned int Vpn_K2;
int Vpn_B2;
unsigned int Vpn_K3;
int Vpn_B3;

unsigned char flagV51;
unsigned char flagV52;
unsigned char ads1110Worked=0;

unsigned int R_Vp_GND_Value[Filter_N];         //总正对地绝缘电阻数组 0.01M 0.01M~50M  1~5000 
unsigned int R_Vn_GND_Value[Filter_N];         //总负对地绝缘电阻数组 0.01M 0.01M~50M  1~5000 
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//**********************************************************************
//* Function name:   Delay_ms
//* Description:     延时//总线时钟 16MHz
//* EntryParameter : ms
//* ReturnValue    : None
//**********************************************************************
void Delay_ms(byte ms)     //总线时钟 16MHz
{ 
  uint i=0;
  for(i=ms*2000;i>0;i--);
}
//**********************************************************************
//* Function name:   Task02_BMN_GlobalVariables_Init
//* Description:     全局变量初始化
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Task02_BMN_GlobalVariables_Init(void)
{

   //V02B  250 350    2012.09.03
    Vpn_K1=198;       //Vpn_K扩大1000倍，精确到小数点后3位 922
    Vpn_B1=4000;      //Vpn_B扩大1000倍，精确到小数点后3位  58 000
    Vpn_K2=198;       //Vpn_K扩大1000倍，精确到小数点后3位 922
    Vpn_B2=4000;      //Vpn_B扩大1000倍，精确到小数点后3位  58 000
    Vpn_K3=198;       //Vpn_K扩大1000倍，精确到小数点后3位 922
    Vpn_B3=4000;      //Vpn_B扩大1000倍，精确到小数点后3位  58 000
                      
    Vpn1_Voltage_AD_Value=0;        //电池总电压AD值1
    Vpn1_Voltage_CAL_Value=0;       //电池总电压值1
    Vpn2_Voltage_AD_Value=0;        //电池总电压AD值2
    Vpn2_Voltage_CAL_Value=0;       //电池总电压值2
    Vpn3_Voltage_AD_Value=0;        //电池总电压AD值3
    Vpn3_Voltage_CAL_Value=0;       //电池总电压值3

}

//**********************************************************************
//* Function name:   Task04_BMN_FEED_COP
//* Description:     看门狗任务
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Task04_BMN_FEED_COP(void)
{
    if(BMN_WATCHDOG_Enable) 
        _FEED_COP();      //feeds the dog
}

//**********************************************************************
//* Function name:   Task08_BMN_ReInit
//* Description:     BMN重新初始化
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Task08_BMN_ReInit(void)
{

}
//**********************************************************************
//* Function name:   Task09_BMN_GlobalVariables_Clear
//* Description:     全局变量清零
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Task09_BMN_GlobalVariables_Clear(void)
{

}
//**********************************************************************
//* Function name:   Task11_Vpn_StartAD_Polling
//* Description:     获取3路电压的AD值
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Task11_Vpn_StartAD_Polling(void)
{
    CRGINT = 0x00; // disable RTI interrupt
    PITINTE  &=0xfe; ///disable the PIT Ch0 interrupt 
    Vpn1_Voltage_AD_Value=GetU1adValue();
    Vpn2_Voltage_AD_Value=GetU2adValue();
    Vpn3_Voltage_AD_Value=GetU3adValue();  
    CRGINT = 0x80; // enable RTI interrupt
    PITINTE  |=0x01; ///Enable the PIT Ch0 interrupt 
}

//**********************************************************************
//* Function name:   Task13_Vpn_Value_Calibrate
//* Description:     3路电压标定
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Task13_Vpn_Value_Calibrate(void)
{
    slong buffer1=0;
    static unsigned int Vpn1_V1;               
    static unsigned int Vpn1_V2;              
    static unsigned int Vpn2_V1;               
    static unsigned int Vpn2_V2; 
    static unsigned int Vpn3_V1;               
    static unsigned int Vpn3_V2;                          

    if(BMNVPNflag.Bit.flag4) 
    {
        BMNVPNflag.Bit.flag4=0;
        Vpn1_V1=GetU1adValue();  //250V对应的AD值;350
        Vpn2_V1=GetU2adValue(); 
        Vpn3_V1=GetU3adValue();   
        BMNVPNflag.Bit.flag5=1;
    }

    if(BMNVPNflag.Bit.flag6) 
    {
        BMNVPNflag.Bit.flag6=0; 
        Vpn1_V2=GetU1adValue();  //350V对应的AD值;550
        Vpn2_V2=GetU2adValue(); 
        Vpn3_V2=GetU3adValue(); 
        BMNVPNflag.Bit.flag7=1;
    }

    if((BMNVPNflag.Bit.flag5)&&(BMNVPNflag.Bit.flag7)) 
    {
        BMNVPNflag.Bit.flag5=0;
        BMNVPNflag.Bit.flag7=0;
         
        Vpn_K1=(uint)(((unsigned long)(HIGHVOL_23-HIGHVOL_19)*(unsigned long)1000)/(Vpn1_V2-Vpn1_V1));      
        Vpn_B1=HIGHVOL_23*1000-Vpn_K1*Vpn1_V2;
        Vpn_K2=(uint)((unsigned long)(HIGHVOL_23-HIGHVOL_19)*(unsigned long)1000/(Vpn2_V2-Vpn2_V1));      
        Vpn_B2=HIGHVOL_23*1000-Vpn_K2*Vpn2_V2;
        Vpn_K3=(uint)((unsigned long)(HIGHVOL_23-HIGHVOL_19)*(unsigned long)1000/(Vpn3_V2-Vpn3_V1));      
        Vpn_B3=HIGHVOL_23*1000-Vpn_K3*Vpn3_V2;
                       
        KB_DATA_SAVE();
    }

}
//**********************************************************************
//* Function name:   TaskVoltage
//* Description:     根据AD值计算出3路电压值
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void TaskVoltage(void)
{
    long voltage_buffer2;
    
    Task11_Vpn_StartAD_Polling();
    
    
    if(Vpn1_Voltage_AD_Value>=8192)   //防止出现负压
    {
        //Can08f0Byte1.Bit.voltageSensor=1; //to vcu
        Vpn1_Voltage_AD_Value = 0;
    }
    if(Vpn2_Voltage_AD_Value>=8192)  //
    {
        Vpn2_Voltage_AD_Value = 0;
        //Can08f0Byte1.Bit.voltageSensor=1; //to vcu
    }
    if(Vpn3_Voltage_AD_Value>=8192)//
    {
        Vpn3_Voltage_AD_Value = 0;
        //Can08f0Byte1.Bit.voltageSensor=1; //to vcu
    }
    
    voltage_buffer2 = (unsigned long)Vpn1_Voltage_AD_Value * Vpn_K1;    //y=kx+b;
    voltage_buffer2 = voltage_buffer2 + Vpn_B1; 
    if(voltage_buffer2<0)
        voltage_buffer2=0;
    Vpn1_Voltage_CAL_Value =voltage_buffer2/10;
    g_highVoltageV1 = (float)(Vpn1_Voltage_CAL_Value/100.0); // 内部电压 v1
    /////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////
    voltage_buffer2 = (unsigned long)Vpn2_Voltage_AD_Value * Vpn_K2;    //y=kx+b;
    voltage_buffer2 = voltage_buffer2 + Vpn_B2; 
    if(voltage_buffer2<0)//f防止溢出  
        voltage_buffer2=0;
    Vpn2_Voltage_CAL_Value =voltage_buffer2/10;
    g_highVoltageV2 = (float)(Vpn2_Voltage_CAL_Value/100.0);//外部电压 v2    
    
    /////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////
    voltage_buffer2 = (unsigned long)Vpn3_Voltage_AD_Value*Vpn_K3;    //y=kx+b;
    voltage_buffer2 = voltage_buffer2+Vpn_B3;  
    if(voltage_buffer2<0)
        voltage_buffer2=0;
    Vpn3_Voltage_CAL_Value =voltage_buffer2/10;
    g_highVoltageV3 = (float)(Vpn3_Voltage_CAL_Value/100.0);//外部电压 v3
    
    Task21_CAN_SendGouup1(); //给上位机发送报文
    ads1110Worked =1;
}
//**********************************************************************
//* Function name:   Task14_R_Vp_GND_Value_Polling
//* Description:     获取当DO1 吸合，DO2 断开时对应的电压值
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Task14_R_Vp_GND_Value_Polling(void)
{
    float voltage_buffer2;
    float k=0;
    static U16 isoCounter1 = 0;
  
    flagV51 = 0;
    turnOffDO2();   //DO2 断开
    turnOnDO1();   //DO1 吸合
    isoCounter1++;
   
    if(isoCounter1 == 2) //2*2100ms 
    { 
        isoCounter1 =0;

        CRGINT = 0x00; // disable rti interrupt
        PITINTE  &= 0xfe; ///disable the PIT Ch0 interrupt
        
        V51_Voltage_AD_Value = GetInsulateVoltAd();
        
        CRGINT = 0x80; // enable rti interrupt
        PITINTE  |=0x01; ///Enable the PIT Ch0 interrupt
        
        turnOffDO1();  //DO1 断开

        voltage_buffer2 = (float)V51_Voltage_AD_Value/32768*2048; 
            
        if((voltage_buffer2>=8.62)&&(voltage_buffer2<=37.034))
            k= 5.9992+0.06557*voltage_buffer2-0.000558*voltage_buffer2*voltage_buffer2;
        else if((voltage_buffer2>37.034)&&(voltage_buffer2<=133.55))
            k=7.407 + 0.00768*voltage_buffer2 + 0.00002885*voltage_buffer2*voltage_buffer2;
        else if((voltage_buffer2>133.55)&&(voltage_buffer2<=2446.8))
            k=8.027; 
        else
            k=8.0;
		
        V51_Voltage_CAL_Value = voltage_buffer2/k;
       
        //V51_Voltage_CAL_Value =voltage_buffer2/8;  
        if(V51_Voltage_AD_Value >= 32768)
        {
            V51_Voltage_CAL_Value = 1;
            //error21|=0x20;           //绝缘检测电路故障
        }
        if(V51_Voltage_CAL_Value < 1)
            V51_Voltage_CAL_Value = 1;
        flagV51 = 1;
    }
    
}
//**********************************************************************
//* Function name:   Task15_R_Vn_GND_Value_Polling
//* Description:     获取当DO2 吸合，DO1 断开时对应的电压值
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Task15_R_Vn_GND_Value_Polling(void)
{   
    float voltage_buffer2; 
    float k=0;
    static U16 isoCounter2=0;

    flagV52 = 0; 
    turnOffDO1();  //DO1 断开
    turnOnDO2();//DO2 吸合 
    
    isoCounter2++; 
    
    if(isoCounter2 == 2) //2100ms*2 = 4200ms
    { 
        isoCounter2 = 0;

        CRGINT = 0x00; // disable rti interrupt
        PITINTE  &=0xfe; ///disable the PIT Ch0 interrupt 
        V52_Voltage_AD_Value  =GetInsulateVoltAd();
		
        CRGINT = 0x80; // enable rti interrupt
        PITINTE  |=0x01; ///Enable the PIT Ch0 interrupt 
        
        turnOffDO2();             //DO2 断开 
        
        voltage_buffer2 = -1 * (float)(65536 - V52_Voltage_AD_Value) / 32768 * 2048; 
          
        if((voltage_buffer2>=-33.508)&&(voltage_buffer2<=-11.456))
            k= 11.78234+0.20316*voltage_buffer2+0.00337*voltage_buffer2*voltage_buffer2;
            
        else if((voltage_buffer2>-383.15)&&(voltage_buffer2<=-33.508))
            k=8.40372+0.00185*voltage_buffer2+0.00000295*voltage_buffer2*voltage_buffer2;
        
        else if((voltage_buffer2>-2537.4)&&(voltage_buffer2<=-383.15))
            k=8.073;
        else
            k=8.0;
		
        V52_Voltage_CAL_Value = voltage_buffer2/k;
        
        //V52_Voltage_CAL_Value =voltage_buffer2/8; 
        if(V52_Voltage_AD_Value<=32768)
        {
           V52_Voltage_CAL_Value =-1;
           //error21|=0x20;  //绝缘检测电路故障
        }
        if(V52_Voltage_CAL_Value>-1)
           V52_Voltage_CAL_Value =-1;
        flagV52 = 1;
    } 
                                 
}

//**********************************************************************
//* Function name:   TaskInsulation
//* Description:     根据所得的桥路电压值和对应的电阻，算出对应的绝缘阻值
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void TaskInsulation(void)//调用函数TaskInsulation(void)需要400ms;
{
	float buff1=0;
	static unsigned char isoCounter=0;
	
	if((!InsRelayState)||(stateCode!=170))//只有在快充和绝缘控制继电器闭合时才检绝缘
		return;
   
    if((flagV51==0)&&(isoCounter==0)){
        Task14_R_Vp_GND_Value_Polling();//计算完成需要400*20=8s       
    }
	
    if(flagV51)//8s后，到这 
    {
        isoCounter++;
        if(isoCounter==1) 
        {
            isoCounter =0;
            
            Task15_R_Vn_GND_Value_Polling();// 计算完成需要400*20=8s 
        }
    }
    
    if(flagV52)  //等待检测完V5两个方向的电压，然后再计算绝缘阻值
    {
        turnOffDO1();              //DO1 断开  
        turnOffDO2();             //DO2 断开 
        
        buff1 =(RESVALUE+1000)*((float)V51_Voltage_CAL_Value-(float)V52_Voltage_CAL_Value)-RESVALUE*10*(float)Vpn1_Voltage_CAL_Value;
        Rp_Vpn_Value = buff1/(float)V52_Voltage_CAL_Value;
        
        buff1 =0;
        buff1 =(RESVALUE+1000)*((float)V52_Voltage_CAL_Value-(float)V51_Voltage_CAL_Value)+RESVALUE*10*(float)Vpn1_Voltage_CAL_Value; 
        Rn_Vpn_Value = buff1/(float)V51_Voltage_CAL_Value;

		if(Rn_Vpn_Value < 0){
			Rn_Vpn_Value = 2000;
		}
		else if(Rn_Vpn_Value < 10){
			Rn_Vpn_Value = 10;
		}

		if(Rp_Vpn_Value < 0){
			Rp_Vpn_Value = 2000;
		}
		else if(Rp_Vpn_Value < 10){
		     Rp_Vpn_Value = 10;
		}
        
        if(Rp_Vpn_Value>10000)
            Rp_Vpn_Value=10000;
        if(Rn_Vpn_Value>10000)
            Rn_Vpn_Value=10000;
        
		
        flagV52=0;
        isoCounter=0;
        flagV51=0;
        
        if((Rp_Vpn_Value>0)&&(Rn_Vpn_Value>0)) //如果出现负值，则不发送
            Task22_CAN_SendGouup2();
        
    } 
 
}
//**********************************************************************
//* Function name:   fastInsulationProcess
//* Description:     快速绝缘电压检测  //通过对桥路电压的快速检测，简单判断绝缘是否合格
//* EntryParameter : None
//* ReturnValue    : 电压是否合格
//**********************************************************************
Bool fastInsulationProcess(void) 
{
    unsigned char flagP=0,flagN=0;
    float voltage_buffer2; 
     
    turnOffDO2();   //DO2 断开 
    turnOnDO1();   //DO1 吸合
    Delay_ms(85); 
    V51_Voltage_AD_Value =GetInsulateVoltAd();
    voltage_buffer2 = (float)V51_Voltage_AD_Value/32768*2.048;   
    V51_Voltage_CAL_Value = voltage_buffer2*1000/8;
    if(V51_Voltage_CAL_Value >= 1521 )
        flagP=1;
      
    turnOffDO1();  //DO1 断开
    turnOnDO2();//DO2 吸合
    Delay_ms(85);
    V52_Voltage_AD_Value  =GetInsulateVoltAd();
    voltage_buffer2 =-1* (float)(65536-V52_Voltage_AD_Value)/32768*2.048; 
    V52_Voltage_CAL_Value =voltage_buffer2*1000/8; 
    if(V52_Voltage_CAL_Value <= -1.521 )
        flagN=1;  
    return (flagP+flagN);
}

//**********************************************************************
//* Function name:   Task17_Rp_Rn_Value_Calculate_Filter
//* Description:     对计算出的绝缘值进行滤波
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Task17_Rp_Rn_Value_Calculate_Filter(void)
{
    byte count,i,j;
    unsigned int temp1,temp2;
    unsigned long sum1=0;
    unsigned long sum2=0; 
    //数值排序，从小到大
   
    for (j=0;j<Filter_N-1;j++)
    {
        for (i=0;i<Filter_N-j-1;i++)
        {
            if ( R_Vp_GND_Value[i]>R_Vp_GND_Value[i+1] )
            {
                temp1 = R_Vp_GND_Value[i];
                R_Vp_GND_Value[i] = R_Vp_GND_Value[i+1]; 
                R_Vp_GND_Value[i+1] = temp1;
            }
            if ( R_Vn_GND_Value[i]>R_Vn_GND_Value[i+1] )
            {
                temp2 = R_Vn_GND_Value[i];
                R_Vn_GND_Value[i] = R_Vn_GND_Value[i+1]; 
                R_Vn_GND_Value[i+1] = temp2;
            } 
        }
    }

    for(count=2;count<Filter_N-2;count++) 
    {
        sum1 += R_Vp_GND_Value[count];
        sum2 += R_Vn_GND_Value[count];
    }
    
    RR_Vp_GND_Value=(unsigned int)(sum1/(Filter_N-4));
    RR_Vn_GND_Value=(unsigned int)(sum2/(Filter_N-4));
  
}
//**********************************************************************
//* Function name:   Task21_CAN_SendGouup1
//* Description:     将3路电压值通过 inner CAN 发送出去
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Task21_CAN_SendGouup1(void)
{
    struct can_msg mg;
    
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
   
    // VPN
    mg.id = CANID_BMNVPN;
    
    mg.data[0]=(unsigned char)(Vpn1_Voltage_CAL_Value>>8);
    mg.data[1]=(unsigned char)Vpn1_Voltage_CAL_Value;
    mg.data[2]=(unsigned char)(Vpn2_Voltage_CAL_Value>>8); 
    mg.data[3]=(unsigned char)Vpn2_Voltage_CAL_Value;  
    mg.data[4]=(unsigned char)(Vpn3_Voltage_CAL_Value>>8); 
    mg.data[5]=(unsigned char)Vpn3_Voltage_CAL_Value;
    mg.data[6]=(unsigned char)(Vpn1_Voltage_AD_Value>>8);  
    mg.data[7]=Vpn1_Voltage_AD_Value; 
   // Sends a data frame message
    MSCAN2SendMsg(mg);
   
}
//**********************************************************************
//* Function name:   Task22_CAN_SendGouup2
//* Description:     将正负端对地的绝缘阻值通过inner CAN 发送出去
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void Task22_CAN_SendGouup2(void)
{
    struct can_msg mg;
    unsigned int buff1 = 0;
    unsigned int buff2 = 0;
    mg.RTR= FALSE;  
    mg.len = 8;
    mg.prty = 0;
    // RP Rn To Gnd
    
    buff1 = Rp_Vpn_Value;
    buff2 = Rn_Vpn_Value;
     
    mg.id = CANID_RPNTOGND;
	
    mg.data[0]=(unsigned char)((buff1/10)>>8);
    mg.data[1]=(unsigned char)(buff1/10);
    mg.data[2]=(unsigned char)((buff2/10)>>8);
    mg.data[3]=(unsigned char)(buff2/10);
    mg.data[4]=0;
    mg.data[5]=0;
    mg.data[6]=0;
    mg.data[7]=0;
    mg.len = 8;
    mg.RTR = FALSE;
    mg.prty = 0;
    // Sends a data frame message
    MSCAN2SendMsg(mg);
}
//**********************************************************************
//* Function name:   TurnOffInsulation
//* Description:     将正负端对地的绝缘阻值通过inner CAN 发送出去
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************    
void TurnOffInsulation(void)
{      
    turnOffDO2();   //DO2 断开
    turnOffDO1();   //DO1 断开 
}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

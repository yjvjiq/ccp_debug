/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////
#include <hidef.h>       /* for EnableInterrupts macro */
#include "derivative.h"  /* include peripheral declarations */
#include <stdtypes.h>

#include "mscan.h"
#include "bmn.h"                     

/////////////////////////////////////////////////////////////////////////////////////////
// Defines
#define Filter_N                10         //滤波采样点数目,6s采一个点
/////////////////////////////////////////////////////////////////////////////////////////
typedef union{
	unsigned char byte;
	struct {
		byte flag0:1;       //CANRx标定判断
		byte flag1:1;       //60s 滤波标志 60s= Filter_N*6
		byte flag2:1;       //未用
		byte flag3:1;       //100V 以上标定
		byte flag4:1;       //200V 标定
		byte flag5:1;       //200V 标定
		byte flag6:1;       //400V 标定
		byte flag7:1;       //400V 标定
	}Bit;
}BMNVPNFLAG ;    //BMN VPN标定任务标志   
BMNVPNFLAG      BMNVPNflag;

Bool BMN_CAN4_Enable = FALSE;             //标定CAN    500kbsp
Bool BMN_WATCHDOG_Enable = FALSE;          //看门狗标志
//
unsigned char I_Vp_GND_DIR;             //总正对地漏电流方向                                  
unsigned char I_Vn_GND_DIR;             //总负对地漏电流方向

//BMN参数变量
unsigned int Vpn1_Voltage_AD_Value=0;        //电池总电压1采样值     0.01V  100~500V   100.00~500.00
unsigned int Vpn1_Voltage_CAL_Value=0;       //电池总电压1计算值     0.01V  100~500V   100.00~500.00
unsigned int Vpn2_Voltage_AD_Value=0;        //电池总电压2采样值     0.01V  100~500V   100.00~500.00
unsigned int Vpn2_Voltage_CAL_Value=0;       //电池总电压2计算值     0.01V  100~500V   100.00~500.00
unsigned int Vpn2_Voltage_buff;

unsigned long RR_Vp_GND_Value;           //总正对地绝缘电阻 0.01M 0.01M~50M  1~5000 
unsigned long RR_Vn_GND_Value;           //总负对地绝缘电阻 0.01M 0.01M~50M  1~5000 
unsigned char R_Vp_Vn_GND_Num;          //总正、负对地绝缘电阻测量次数  1~5 

unsigned int Rp_Vpn_Value;              //总正对地绝缘电阻等级 10欧/V 1~500  1~5000 
unsigned int Rn_Vpn_Value;              //总负对地绝缘电阻等级 10欧/V 1~500  1~5000

unsigned int Vpn1_V1;               //200,250,300,350,400
unsigned int Vpn1_V2;               //200,250,300,350,400
unsigned int Vpn2_V1;               //200,250,300,350,400
unsigned int Vpn2_V2;               //200,250,300,350,400

unsigned int Vpn_K1;              //
int Vpn_B1;                       //
unsigned int Vpn_K2;              //
int Vpn_B2;                       //

unsigned int     DataBuffer[4];//={0xaaaa,0x5678,0x9abc,0xdef0};//数据缓存区，只能一次写入四个数据
unsigned int R_Vp_GND_Value[Filter_N];         //总正对地绝缘电阻数组 0.01M 0.01M~50M  1~5000 
unsigned int R_Vn_GND_Value[Filter_N];         //总负对地绝缘电阻数组 0.01M 0.01M~50M  1~5000 
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
static void Delay_ms(byte ms)     //总线时钟 8MHz
{ 
  uint i=0;
  for(i=ms*2000;i>0;i--) ;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Task01_BMN_Init
// --------------------------------------------------------------------------------------
// 执行时刻：1ms 
/////////////////////////////////////////////////////////////////////////////////////////
void Task01_BMN_Init(void)
{
    //BMN_CAN_Address = BMN_CAN_ADDRESS;    //BMN的CAN地址设置  
}

/////////////////////////////////////////////////////////////////////////////////////////
// Task02_BMN_GlobalVariables_Init()
// --------------------------------------------------------------------------------------
// 全局变量初始化
/////////////////////////////////////////////////////////////////////////////////////////
void Task02_BMN_GlobalVariables_Init(void)
{
    //Taskflag.byte=0;
    //CANsendflag.byte=0; 
    //CANREQflag.byte=0;
    //EEEflag.word=0;
    //BMNVPNflag.byte=0;
    //BMNCAN_LIFE_SIGNAL_Num=0;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//V02B  250 350    2012.09.03
    Vpn_K1=198;       //Vpn_K扩大1000倍，精确到小数点后3位 922
    Vpn_B1=4000;      //Vpn_B扩大1000倍，精确到小数点后3位  58 000
    Vpn_K2=198;       //Vpn_K扩大1000倍，精确到小数点后3位 922
    Vpn_B2=4000;      //Vpn_B扩大1000倍，精确到小数点后3位  58 000
                      
    Vpn1_Voltage_AD_Value=0;        //电池总电压AD值1
    Vpn1_Voltage_CAL_Value=0;       //电池总电压值1
    Vpn2_Voltage_AD_Value=0;        //电池总电压AD值2
    Vpn2_Voltage_CAL_Value=0;       //电池总电压值2

    R_Vp_Vn_GND_Num=0;          //总正、负对地绝缘电阻测量次数  1~5 

    RR_Vp_GND_Value=0;           //总正对地绝缘电阻
    RR_Vn_GND_Value=0;           //总负对地绝缘电阻
 
    Rp_Vpn_Value=0;            //总正对地绝缘电阻等级 10欧/V 1~500  1~5000 
    Rn_Vpn_Value=0;            //总负对地绝缘电阻等级 10欧/V 1~500  1~5000

}

/////////////////////////////////////////////////////////////////////////////////////////
// Task03_BMN_MCU_Init
// --------------------------------------------------------------------------------------
// Initializes various registers and peripherals
/////////////////////////////////////////////////////////////////////////////////////////
void Task03_BMN_MCU_Init(void)
{
    DisableInterrupts;
    IVBR=0x7f;                //向量表要重新定位
    MCU_BusClock_Init();
    BMN_DIO_Init();
    RTC_Init();
//    PIT0_Init();
    CAN0_Init();
    
    //Fee_Init();
    //FCLKDIV = 0x03;//为了fee时钟分频
    DFlash_Init();
    
    BMN_ADC_Init();       //两路AD
    CS5460A_Init();       //BMN专用
   // if(BMN_WATCHDOG_Enable) COP_Init();

    EnableInterrupts;
 
}

/////////////////////////////////////////////////////////////////////////////////////////
// Task04_BMN_FEED_COP()
// --------------------------------------------------------------------------------------
// Feeds the dog
/////////////////////////////////////////////////////////////////////////////////////////
void Task04_BMN_FEED_COP(void)
{
    if(BMN_WATCHDOG_Enable) 
        _FEED_COP();      //feeds the dog
}

/////////////////////////////////////////////////////////////////////////////////////////
// Task06_BMN_DATA_RECALL
// --------------------------------------------------------------------------------------
// 执行时刻：1ms 
/////////////////////////////////////////////////////////////////////////////////////////
void Task06_BMN_DATA_RECALL(void)
{
    DisableInterrupts;
    Vpn_K1 = FSL_ReadDFlash(0x0300);  //
    Vpn_B1 = FSL_ReadDFlash(0x0302);
    Vpn_K2 = FSL_ReadDFlash(0x0304);
    Vpn_B2 = FSL_ReadDFlash(0x0306);
    EnableInterrupts;

}


/////////////////////////////////////////////////////////////////////////////////////////
// Task07_BMN_DATA_SAVE
// --------------------------------------------------------------------------------------
// 执行时刻：1ms 
/////////////////////////////////////////////////////////////////////////////////////////
void Task07_BMN_DATA_SAVE(void)
{
    DisableInterrupts; 
    //if(EEEflag.Bit.flag8) 
    {    
        DFlash_Erase_Sector(0x0300); //必须先擦除 the second sector;每扇区256个字节
        DataBuffer[0] = Vpn_K1;
        DataBuffer[1] = Vpn_B1;
        DataBuffer[2] = Vpn_K2;
        DataBuffer[3] = Vpn_B2;
        DFlash_Write_Word(0x0300); 
        
        //EEEflag.Bit.flag8=0;
      } 
    EnableInterrupts;
}


/////////////////////////////////////////////////////////////////////////////////////////
// Task08_BMN_ReInit
// --------------------------------------------------------------------------------------
// 执行时刻：1ms 
/////////////////////////////////////////////////////////////////////////////////////////
void Task08_BMN_ReInit(void)
{

}
/////////////////////////////////////////////////////////////////////////////////////////
// Task09_BMN_GlobalVariables_Clear
// --------------------------------------------------------------------------------------
// 执行时刻：170ms 
/////////////////////////////////////////////////////////////////////////////////////////
void Task09_BMN_GlobalVariables_Clear(void)
{

}
/////////////////////////////////////////////////////////////////////////////////////////
// Task11_Vpn_StartAD_Polling  //查询模式
// --------------------------------------------------------------------------------------
// 耗时10ms 
/////////////////////////////////////////////////////////////////////////////////////////
void Task11_Vpn_StartAD_Polling(void)
{
    Vpn1_Voltage_AD_Value =GetU1adValue();
    Vpn2_Voltage_AD_Value =GetU2adValue();
  
}

/////////////////////////////////////////////////////////////////////////////////////////
// Task12_Vpn_Value_Calculate  
// --------------------------------------------------------------------------------------
// 耗时10ms 
/////////////////////////////////////////////////////////////////////////////////////////
void Task12_Vpn_Value_Calculate(void)
{
    ulong voltage_buffer2;
   
    Vpn1_Voltage_CAL_Value = 0;
    Vpn2_Voltage_CAL_Value =0;
    voltage_buffer2 = (unsigned long)Vpn1_Voltage_AD_Value*Vpn_K1;    //y=kx+b;
    voltage_buffer2 = voltage_buffer2+Vpn_B1;  
    Vpn1_Voltage_CAL_Value =(unsigned int)(voltage_buffer2/100);
   
    voltage_buffer2 = (unsigned long)Vpn2_Voltage_AD_Value*Vpn_K2;    //y=kx+b;
    voltage_buffer2 = voltage_buffer2+Vpn_B2;  
    Vpn2_Voltage_CAL_Value =(unsigned int)(voltage_buffer2/100);
}
/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////6次测量，并滤波/////////////////////////////////////////////////
float VisolationCalculate(void) 
{
    unsigned char i;
    unsigned int ADvalue;
    float VisolationDetectValue[6];
    float max, min,sum;
     
    for(i=0;i<6;i++) 
    {
        ADvalue  = GetInsulateVoltAd();
        if(ADvalue<0x7ff)
            VisolationDetectValue[i] = 2.048*ADvalue/(2048*1);
        else
            VisolationDetectValue[i] = -2.048*(0xffff-ADvalue)/(2048*1);  //负压                
    }
    
    max = VisolationDetectValue[0];
    min = max;
    for(i=0;i<6;i++) 
    {
         if(max>VisolationDetectValue[i])
             max = VisolationDetectValue[i];
         if(min<VisolationDetectValue[i])
             min = VisolationDetectValue[i];  
         sum += VisolationDetectValue[i];
    }
    sum = sum - max - min;
    return (sum/4);
}
/////////////////////////////////////////////////////////////////////////////////////////
// Task13_Vpn_Value_Calibrate  
// --------------------------------------------------------------------------------------
// 耗时10ms 
/////////////////////////////////////////////////////////////////////////////////////////
void Task13_Vpn_Value_Calibrate(void)
{
    slong buffer1=0;

    if(BMNVPNflag.Bit.flag4) 
    {
        BMNVPNflag.Bit.flag4=0;
        Vpn1_V1=GetU1adValue();  //250V对应的AD值
        Vpn2_V1=GetU2adValue();   
        BMNVPNflag.Bit.flag5=1;
    }

    if(BMNVPNflag.Bit.flag6) 
    {
        BMNVPNflag.Bit.flag6=0; 
        Vpn1_V2=GetU1adValue();  //350V对应的AD值
        Vpn2_V2=GetU2adValue(); 
        BMNVPNflag.Bit.flag7=1;
    }

    if((BMNVPNflag.Bit.flag5)&&(BMNVPNflag.Bit.flag7)) 
    {
        BMNVPNflag.Bit.flag5=0;
        BMNVPNflag.Bit.flag7=0;
       
        Vpn_K1=(uint)(((unsigned long)100*(unsigned long)10000)/(Vpn1_V2-Vpn1_V1));      
        Vpn_B1=350*10000-Vpn_K1*Vpn1_V2;
        Vpn_K2=(uint)((unsigned long)100*(unsigned long)10000/(Vpn2_V2-Vpn2_V1));      
        Vpn_B2=350*10000-Vpn_K2*Vpn2_V2;

        //EEEflag.Bit.flag8=1; //Vpn的K和B值存储标志
        Task07_BMN_DATA_SAVE();
    }

}

/////////////////////////////////////////////////////////////////////////////////////////
// Task14_R_Vp_GND_Value_Polling  //查询模式
// --------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////
void Task14_R_Vp_GND_Value_Polling(void)
{
    turnOffDO2();             //DO2 断开
    Delay_ms(500);    
    turnOnDO1();                //DO1 吸合
    Delay_ms(500);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Task15_R_Vn_GND_Value_Polling  //查询模式
// --------------------------------------------------------------------------------------
// 耗时10ms 
/////////////////////////////////////////////////////////////////////////////////////////
void Task15_R_Vn_GND_Value_Polling(void)
{   
    turnOffDO1();                 //DO1 断开
    Delay_ms(500);
    turnOnDO2();                  //DO2 吸合 
    Delay_ms(500);                  
}

/////////////////////////////////////////////////////////////////////////////////////////
// Task16_Rp_Rn_Value_Calculate
// --------------------------------------------------------------------------------------
// 耗时10ms 
/////////////////////////////////////////////////////////////////////////////////////////
//void Task16_Rp_Rn_Value_Calculate(byte number)
void Task16_Rp_Rn_Value_Calculate()
{
    turnOffDO1();              //DO1 断开  
    Delay_ms(500);
    turnOffDO2();             //DO2 断开 
    Delay_ms(500); 
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
Bool fastInsulationProcess(void) 
{
    unsigned char flagP,flagN;
    float temp;
     
    Task14_R_Vp_GND_Value_Polling(); //DO1 吸合; DO2 断开
    temp = VisolationCalculate();
    if(temp >= 1.521 )
        flagP=1;
     
    Task15_R_Vn_GND_Value_Polling();  //DO1 断开  //DO2 吸合 
    temp = VisolationCalculate();
    if(temp <= -1.521 )
        flagN=1;
     
    return (flagP+flagN);

}
/////////////////////////////////////////////////////////////////////////////////////////
// void Task17_Rp_Rn_Value_Calculate_Filter(void)
// --------------------------------------------------------------------------------------
// 软件滤波函数
/////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

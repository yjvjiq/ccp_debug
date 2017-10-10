//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : PHEV.DJ
//* File Name          : Q1Q2calculate.c
//* Author             : Kxy
//* Version            : V1.0.0
//* Start Date         : 2016.7.12
//* Description        : 该文件用于项目的策略处理包括：系统高压上下电、SOF、回馈电流、SOC修正、电流计算等等
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "BMS20.h" 
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

//******************************************************************************
//* Function name:   Q2nominalCalculate
//* Description:     额定容量计算 Q2_额定=Q_NEDC×k_温度×SOH×K_均衡,上电时候用,用于修正Q2
//* EntryParameter : ValueQ1
//* ReturnValue    : 额定容量
//******************************************************************************
float Q2nominalCalculate(float ValueQ1)
{
    unsigned int t=0;
    unsigned char m=0,i=0;
    float q=0;
    float kt=1;
    float soh=1;
    float kj=1;
    //float Ktem[8]={76.155,85.26,93.73,101.37,108.79,114.29,118.64,120};
               //-20     -15   -10    -5     0      5      10    15
    
    /*if(g_lowestTemperature<=20)//如果小于等于-20
        kt=Ktem[0]/120.0;
    else if(g_lowestTemperature>=(15+40))//如果大于15
        kt=Ktem[7]/120.0;
    else//-20~15,(-20,15]
    {
        m=(g_lowestTemperature-40)+20;
        if(m%5==0)
            i=m/5-1;
        else
            i=m/5;
        kt=Ktem[i]/120.0;
    }
    
     
    */    
    
    YoungMan_LT_PowerOnSOCAjust();
    kt=PowerOnSOCAjustFactor;
    
    FactorA=kt;
    if(g_BmsModeFlag == DISCHARGING)
    {   
        if((Can_g_socValue==0)||(g_socValue==0))
            q = ValueQ1*kt*soh*kj;
        else
            q = ValueQ1*kt*soh*kj*g_socValue/Can_g_socValue;
    } 
    else if((g_BmsModeFlag == FASTRECHARGING)||(g_BmsModeFlag == RECHARGING))
    {   
        if((Can_g_socValue==1)||(g_socValue==1))
            q = ValueQ1*kt*soh*kj;
        else
            q = ValueQ1*kt*soh*kj*(1-g_socValue)/(1-Can_g_socValue);
    }
    return q; 
}
//******************************************************************************
//* Function name:   CapacityCalculate
//* Description:     根据单体电压和OCV曲线，算出SOC，然后算出SOC对应的容量
//* EntryParameter : 单体电压值
//* ReturnValue    : 容量系数
//******************************************************************************
float CapacityCalculate(float vocv) //青年项目没有用 
{
    unsigned char i;
    float y2=0;
    float factor[2];
    float socvalue[21]={1,0.95,0.9,0.85,0.8,0.75,0.7,0.65,0.6,0.55,0.5,0.45,0.4,0.35,0.3,0.25,0.2,0.15,0.1,0.05,0};
    float cell[21]={4.132,4.070,4.014,3.962,3.914,3.866,3.821,3.778,3.74,3.7,3.667,3.648,3.634,3.622,3.609,3.595,3.569,3.541,3.509,3.473,3.424};
    g_originalCapacity = SYS_NOMINAL_AH;
    if(vocv>=4.1316)
    {
        return g_originalCapacity;
    }
    if(vocv<=3.4235)
    {
        return 0;    
    }
    
    for(i=0;i<=20;i++)
        if(cell[i]<=vocv) break;//当前的i与i-1是区间
    factor[1]=socvalue[i];//i=8,0.2
    factor[0]=socvalue[i-1];//0.3    
    y2=(vocv-cell[i-1])*(factor[1]-factor[0])/(cell[i]-cell[i-1])+factor[0];//斜率相等
    if(y2>=1) y2=1;
    if(y2<=0) y2=0;
    y2=y2*g_originalCapacity;
     
    return y2;
}

//******************************************************************************
//* Function name:   Temfactor
//* Description:     根据当前温度，计算出系数
//* EntryParameter : 当前温度值
//* ReturnValue    : 容量
//******************************************************************************
//float Temfactor(char Tem)//青年项目目前没有用  

//******************************************************************************
//* Function name:   ChargeEndadjustQ1
//* Description:     根据单体电压、温度计算出充电末端的Qmax与Qmin
//* EntryParameter : 单体最低,温度值
//* ReturnValue    : 容量
//******************************************************************************
/*float ChargeEndadjustQ1(float LowestCell,char Tem)//采用模型  
{
    float VolCell[8]={3.389,3.399,3.405,3.422,3.44,3.475,3.63,3.65};
    float Kah=1;
    float y2=0;
    float Cell1;
    float Cell2;
    float T1;
    float T2;
    float A1,A2,A3,A4;
    float x1,x2;
    unsigned char TemVal[8]={0,5,10,15,20,25,35,45};
    unsigned char i,j;
    float AH[8][8]={ 
                      {69.89 ,74.29 ,77.18 ,93.5  ,105.41,113.6 ,118.78,119   }, //0
                      {75.96 ,80.3  ,86.92 ,104.37,111.78,116.75,120   ,120   }, //5
                      {81.79 ,98.78 ,105.57,114.46,117.86,120   ,120   ,120   }, //10
                      {99.32 ,111   ,113.6 ,118.12,120   ,120   ,120   ,120   }, //15
                      {107.84,115.27,117.28,120   ,120   ,120   ,120   ,120   }, //20
                      {114.58,118.84,120   ,120   ,120   ,120   ,120   ,120   }, //25
                      {119.19,120   ,120   ,120   ,120   ,120   ,120   ,120   }, //35
                      {120   ,120   ,120   ,120   ,120   ,120   ,120   ,120   }  //45
                    //3.389  ,3.399 ,3.403 ,3.442 ,3.44  ,3.475 ,3.63  ,3.65
                    };

    if(LowestCell<=VolCell[0])
        i=1;
    else if(LowestCell>=VolCell[7])
        i=7;
    else
    {    
        for(i=0;i<8;i++)
        {
            if(LowestCell<=VolCell[i])
                break;
        }
    }
    Cell2=VolCell[i];
    Cell1=VolCell[i-1];
    
    if(Tem<=0)
        j=1;
    else if(Tem>=45)
        j=7;
    else
    {          
        for(j=0;j<8;j++)
        {
            if(Tem<=TemVal[j])
                break;
        }
    }
    T2=TemVal[j];
    T1=TemVal[j-1];
    
    A1=AH[j-1][i-1];
    A2=AH[j-1][i];
    A3=AH[j][i-1];
    A4=AH[j][i];
    x1=(LowestCell-Cell1)*(A2-A1)/(Cell2-Cell1)+A1;
    x2=(LowestCell-Cell1)*(A4-A3)/(Cell2-Cell1)+A3;
    y2=(Tem-T1)*(x2-x1)/(T2-T1)+x1;
    Kah=y2/120.0;
    return Kah;
} */
//******************************************************************************
//* Function name:   AdjustQ1Value
//* Description:     充电末端的Qmax与Qmin
//* EntryParameter : void
//* ReturnValue    : Void
//******************************************************************************
void AdjustQ1Value(void)
{
    float y=0;
    YoungMan_LT_ChargeEndSOCAjust();
    //y=ChargeEndadjustQ1(g_lowestCellVoltage,(Tavg-40));
    y=ChargeEndSOCAjustFactor;
    //g_realNominalCap=y*SetCap;
    g_realNominalCap=y;
    StoreQ1value();
}
//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
/*-------------------------------------------------------
---------------------------------------------------------*/






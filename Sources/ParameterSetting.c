
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : 恩驰
//* File Name          : SocAdjust.c
//* Author             : judy
//* Version            : V1.0.0
//* Start Date         : 2016.2.14
//* Description        : 该文件用于调整在不同情况下SOC值
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

#include "BMS20.h"
float g_sysPara[ParamNUMBER];
unsigned char g_bmubalance = 0; //0:充电 1:放电
unsigned long g_BMU_CIRCLE_FLAG =0; //用于配置BMU个数
//******************************************************************************
//* Function name:   ParameterSetting
//* Description:     通过上位机设置系统各个参数或修改某个值
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void ParameterSetting(void)//
{      
    unsigned char i=0;
    unsigned char SetTime[7];  
    float CanSOC=0; 
    switch(g_mboxID)//
    {            
        case 0x0c14ee00:
            sendRealtimeToBMU();
            break;
        case 0xC01ee18:
            sendBMSSFVersionToPC();
            break;
        case 0xc01ee14:         //标定系统时间
            //设置时钟
		        for(i=0;i<7;i++)
		            SetTime[i]=*((&CAN2RXDSR0)+i);//秒//分//时//星期//日//月//年
		        I2CWriteDate(SetTime);  //设置初始时间
            break;
        case 0xC01ee15:
            g_sysPara[PARA_SOC_VALUE]= (float)(*((&CAN2RXDSR0)+2))/100;    // RSOC
            g_socValue = g_sysPara[PARA_SOC_VALUE];
            First_g_socValue = g_socValue;
            
            g_leftEnergy = g_socValue*(g_realNominalCap*3600);  //剩余容量
	          g_energyOfUsed = 0;                          //本次开机已用容量       
	          StoreParameter();               
	          StoreSocRealvalue();
            break;
         case 0xC01ef15:
                         
	          CanSOC =  (float)(*((&CAN2RXDSR0)+2))/100;
	          Can_g_socValue_Start=CanSOC;
	          CanSocIntegral();
	          StoreSocRealvalue();
            
            break;
        case 0xC01ee16:
            g_sysPara[PARA_WHOLE_CAPACITY]= *((&CAN2RXDSR0)+2);
	          g_realNominalCap =  g_sysPara[PARA_WHOLE_CAPACITY];//可用容量初始化
	          StoreParameter();
	          StoreQ1value();
            break;
        case 0xc01ee17:     //配置BMU个数
            g_sysPara[PARA_BMU_NUMBER]= *((&CAN2RXDSR0)+2);
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
                  	break;  
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
            StoreParameter();
            //paraChangedFlag = 1;
            break;
        case 0xC01EE26://读取系统内部参数
            if(*((&CAN0RXDSR0)+0)==0x66)
                //paraReadFlag=1;
            break;            
        case 0xC01EE28:         //接收系统参数修正信息from 上位机
            g_sysPara[PARA_O_WHOLE_VOLTAGE]=  (*((&CAN2RXDSR0)+0)&0x00ff)<<8 | (*((&CAN2RXDSR0)+1)&0x00ff);//总电压过高阈值
            g_sysPara[PARA_L_WHOLE_VOLTAGE]=  (*((&CAN2RXDSR0)+2)&0x00ff)<<8 | (*((&CAN2RXDSR0)+3)&0x00ff);//总电压过低阈值
            g_sysPara[PARA_O_CELL_VOLTAGE] = *((&CAN2RXDSR0)+4)*0.01-1.75;//过压值
            g_sysPara[PARA_L_CELL_VOLTAGE] = *((&CAN2RXDSR0)+5)*0.01-1.75;//欠压值
            g_sysPara[PARA_O_TEMPERATURE] =  *((&CAN2RXDSR0)+6)-40; //过温值
            g_sysPara[PARA_L_TEMPERATURE] =  *((&CAN2RXDSR0)+7)-40; //温度过低值                    
            StoreParameter();
            //paraChangedFlag = 1;
            break;
        case 0xC01EE29:         //接收系统参数修正信息from 上位机
            g_sysPara[PARA_HIGHEST_RECHARGE_CURRENT] =  *((&CAN2RXDSR0)+0);//最大允许充电电流值  
            g_sysPara[PARA_O_SOC_VALUE] =  *((&CAN2RXDSR0)+4); //SOC过高
            g_sysPara[PARA_L_SOC_VALUE] =  *((&CAN2RXDSR0)+5); //SOC过低  
            g_sysPara[PARA_L_ISOLATION_RESISTANCE] =  *((&CAN2RXDSR0)+6); //绝缘电阻过低值
            g_sysPara[PARA_O_CONSISTENCY_V] =  *((&CAN2RXDSR0)+7);//电压一致性差 
            StoreParameter();
            //paraChangedFlag = 1;
            break;
        case 0xC01EE2a:         //接收系统参数修正信息from 上位机
            g_sysPara[PARA_BALANCE_ON_VOLTAGE] = *((&CAN2RXDSR0)+0)*0.01-1.75;//均衡开启电压
            g_sysPara[PARA_BALANCE_OFF_VOLTAGE] = *((&CAN2RXDSR0)+1)*0.01-1.75;//均衡截止电压
            g_sysPara[PARA_DIFFERENCE_SINGLE_V] =  *((&CAN2RXDSR0)+2);//均衡压差
            StoreParameter();
            //paraChangedFlag = 1;
            break;
        case 0xC01EE2b:         //接收系统参数修正信息from 上位机
            break;                      
        default:
            break;                  
      }//end of switch      

}

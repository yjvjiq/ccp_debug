//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : ProcessBMU.c
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2014.5.7
//* Description        : 该文件专门用于处理接收到的BMU数据，从而得出单体极值和单体值
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "derivative.h" /* include peripheral declarations */
#include "BMS20.h" 

#pragma DATA_SEG __GPAGE_SEG PAGED_RAM  
	BMU_CELL_MSG g_bmu_msg;
	BMS_CELL_MSG g_bms_msg;
#pragma DATA_SEG DEFAULT 

U8 g_group;  //BMU1 组号， 从0~18

float g_highestCellVoltage=0; //单体最高电压
float g_lowestCellVoltage=0;  //单体最低电压
U8 g_highestCellVoltage_Num=0; //单体最高电压编号
U8 g_lowestCellVoltage_Num=0;  //单体最低电压编号

U8 g_highestTemperature=0; //单体最高温度
U8 g_lowestTemperature=0;  //单体最低温度
U8 g_highestTemperature_Num=0; //单体最高温度编号
U8 g_lowestTemperature_Num=0;  //单体最低温度编号

float g_averageVoltage;       //平均单体电压
float g_systemVoltage;      //系统电压=单体电压累加总电压

U8 g_averageTemperature; //单体平均温度
U8 Tavg; //电芯平均温度

U8 g_bmu2_number_v[BMU_NUMBER];
U8 g_cell_number_v[BMU_NUMBER][5];

U8 g_bmu2_number_t[BMU_NUMBER];
U8 g_cell_number_t[BMU_NUMBER][5];

U8 recogBMStoBMUflag = 0;//BMS与BMU辨识成功标志
	
//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
U32 g_circleFlag = 0; //一个循环完成的标志
U32 g_configFlag = 0;//收到配置信息标志，用于判断BMU个数，6805组数和单体个数 

//******************************************************************************
//* Function name:   BMU_initial
//* Description:     上电接收BMU所有数据，确保单体温度和电压都没问题
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void BMU_initial(void) 
{
    U16 t=0;
    
    //***********BMU自检*******************************************       
    while((!bmuProcess2())&&(t<65000))    	        
    {
        t++;      
        if(t >= 60000) //超时故障报告
        {
			//t= 60000;
			//Can08f0Byte5.Bit.F3_innerComm=1;  //t0 vcu
			g_caution_Flag_3 |=0x01;    //to pc
        }//end of BMU通信判断  
        else 
        {            
            //Can08f0Byte5.Bit.F3_innerComm=0; //to vcu 
            g_caution_Flag_3 &=0xfe;  //不上报内部通讯故障   to pc 
        }  
        _FEED_COP();   //2s内不喂内狗，则系统复位 
    }
}
//******************************************************************************
//* Function name:   BMU_Processure
//* Description:     interpreting the BMU frame msg.
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void BMU_Processure(void)
{
    U32 framID;
    U16 i,boxNumber=0;
	   
    if((Int_Flag & 0x08) == 0x08) //if received a frame message, then deal with it.
    {
        Int_Flag &= 0xf7;//clear the interrupt flag.
        g_group = 0;  		
		
        framID = g_mboxID;
        g_group = framID & 0x000000ff; //use the lower 8 bits as the group number.
		g_group--;
		
        framID = ((framID >> 8) & 0x003fffff);//use the last high 15 bits as the judge parameter.

		switch(framID)  //interpreting data.
		{
            case 0x018FF11://BMU recognise msg: HW version, SW version, commmunication prorocal version etc, 0x18ff110x
                //if(recogBMUtoBMSmessage != bufL)
                //	recogBMStoBMUflag = 0; //recognise error.
                //else
				BMU_OverTime[g_group] = 0;
				recogBMStoBMUflag = 1; //recognise ok.
                break;
            case 0x018FF13://cell config msg1(CC1):the number of 6802, the number of cell_v and cell_T channals;
				BMU_OverTime[g_group] = 0;
				switch(g_group) 
                {
                    case 0:
                      g_configFlag |= 0x00000001;
                      break;
                    case 1:
                      g_configFlag |= 0x00000002;
                      break;
                    case 2:
                      g_configFlag |= 0x00000004;
                      break;
                    case 3:
                      g_configFlag |= 0x00000008;
                      break;
                    case 4:
                      g_configFlag |= 0x00000010;
                      break;
                    case 5:
                      g_configFlag |= 0x00000020;
                      break;
                    case 6:
                      g_configFlag |= 0x00000040;
                      break;
                    case 7:
                      g_configFlag |= 0x00000080;
                      break;
                    case 8:
                      g_configFlag |= 0x00000100;
                      break;
                    case 9:
                      g_configFlag |= 0x00000200;
                      break;
                    case 10:
                      g_configFlag |= 0x00000400;
                      break;
                    case 11:
                      g_configFlag |= 0x00000800;
                      break;
                    case 12:
                      g_configFlag |= 0x00001000;
                      break;
                    case 13:
                      g_configFlag |= 0x00002000;
                      break;
                    case 14:
                      g_configFlag |= 0x00004000;
                      break;
                    case 15:
                      g_configFlag |= 0x00008000;
                      break;
                    case 16:
                      g_configFlag |= 0x00010000;
                      break;
                    case 17:
                      g_configFlag |= 0x00020000;
                      break;
					default:
						break;
                }
			      
			    g_bmu2_number_v[g_group] = g_mboxData[boxNumber][0]&0x07;		//the number of 6802 in BMU1.
				g_bmu2_number_t[g_group] = (g_mboxData[boxNumber][0]&0x70)>>4;	//&0x07;
        
				g_cell_number_v[g_group][0]=g_mboxData[boxNumber][1]&0x0f;
				g_cell_number_t[g_group][0]=(g_mboxData[boxNumber][1]&0xf0)>>4;

				g_cell_number_v[g_group][1]=g_mboxData[boxNumber][2]&0x0f;
				g_cell_number_t[g_group][1]=(g_mboxData[boxNumber][2]&0xf0)>>4;

				g_cell_number_v[g_group][2]=g_mboxData[boxNumber][3]&0x0f;
				g_cell_number_t[g_group][2]=(g_mboxData[boxNumber][3]&0xf0)>>4;

				g_cell_number_v[g_group][3]=g_mboxData[boxNumber][4]&0x0f;
				g_cell_number_t[g_group][3]=(g_mboxData[boxNumber][4]&0xf0)>>4;

				g_cell_number_v[g_group][4]=g_mboxData[boxNumber][5]&0x0f;	
				g_cell_number_t[g_group][4]=(g_mboxData[boxNumber][5]&0xf0)>>4;	
																	
			    break;
            case 0x018FF14:	//battery config msg3:the number of 6802, the number of cell and temperature channals;CC3
				BMU_OverTime[g_group] = 0;
				break;
		    case 0x018FF16:	//judge the life cycle, whether has received all datas.
			    BMU_OverTime[g_group] = 0;
                switch(g_group) 
                {
					case 0:
						g_circleFlag |= 0x00000001;
						break;
                    case 1:
						g_circleFlag |= 0x00000002;
						break;
                    case 2:
						g_circleFlag |= 0x00000004;
						break;
                    case 3:
						g_circleFlag |= 0x00000008;
						break;
                    case 4:
						g_circleFlag |= 0x00000010;
						break;
                    case 5:
						g_circleFlag |= 0x00000020;
						break;
                    case 6:
						g_circleFlag |= 0x00000040;
						break;
                    case 7:
						g_circleFlag |= 0x00000080;
						break;
                    case 8:
						g_circleFlag |= 0x00000100;
						break;
                    case 9:
						g_circleFlag |= 0x00000200;
						break;
                    case 10:
						g_circleFlag |= 0x00000400;
						break;
                    case 11:
						g_circleFlag |= 0x00000800;
						break;
                    case 12:
						g_circleFlag |= 0x00001000;
						break;
                    case 13:
						g_circleFlag |= 0x00002000;
						break;
                    case 14:
						g_circleFlag |= 0x00004000;
						break;
                    case 15:
						g_circleFlag |= 0x00008000;
						break;
                    case 16:
						g_circleFlag |= 0x00010000;
						break;
                    case 17:
						g_circleFlag |= 0x00020000;
						break;
					default:
						break;
                }
                //State_Box_Online=g_circleFlag;
                break;
				
            //******group, cell voltages*******
            //*********************************
            case 0x0018FF21://BMU number = group; #1 frame, 4 cells each frame.
	            BMU_OverTime[g_group] = 0;
                for(i=0;i<4;i++)
                {
					g_bmu_msg.cell_V[g_group][i] =  (U16)g_mboxData[boxNumber][2*i+1]|(U16)g_mboxData[boxNumber][2*i]<<8;
                }
                break;
            case 0x0018FF22://BMU number = group; #2 frame, 4 cells each frame.
				BMU_OverTime[g_group] = 0;
				for(i=0;i<4;i++)
                {
                    g_bmu_msg.cell_V[g_group][4+i] = (U16)g_mboxData[boxNumber][2*i+1]|(U16)g_mboxData[boxNumber][2*i]<<8;
                }
                break;
            case 0x0018FF23://BMU number = group; #3 frame, 4 cells each frame.		  
				BMU_OverTime[g_group] = 0;
				for(i=0;i<4;i++)
                {
                    g_bmu_msg.cell_V[g_group][8+i] = (U16)g_mboxData[boxNumber][2*i+1]|(U16)g_mboxData[boxNumber][2*i]<<8;
                }
                break;
			case 0x0018FF24://BMU number = group; #4 frame, 4 cells each frame.
				BMU_OverTime[g_group] = 0;
				for(i=0;i<4;i++)
				{
					g_bmu_msg.cell_V[g_group][12+i] = (U16)g_mboxData[boxNumber][2*i+1]|(U16)g_mboxData[boxNumber][2*i]<<8;
				}
				break;
			case 0x0018FF25://BMU number = group; #5 frame, 4 cells each frame.
				BMU_OverTime[g_group] = 0;
				for(i=0;i<4;i++)
				{
					g_bmu_msg.cell_V[g_group][16+i] = (U16)g_mboxData[boxNumber][2*i+1]|(U16)g_mboxData[boxNumber][2*i]<<8;
				}
				break;
			case 0x0018FF26://BMU number = group; #6 frame, 4 cells each frame.
				BMU_OverTime[g_group] = 0;
				for(i=0;i<4;i++)
				{
					g_bmu_msg.cell_V[g_group][20+i] = (U16)g_mboxData[boxNumber][2*i+1]|(U16)g_mboxData[boxNumber][2*i]<<8;
				}
				break;						
			case 0x0018FF27://BMU number = group; #7 frame, 4 cells each frame.
				BMU_OverTime[g_group] = 0;
				if(g_group == 1 || g_group == 7 || g_group == 13){
    				for(i=0;i<4;i++)
    				{
    					g_bmu_msg.cell_V[g_group][24+i] = 0;
    				}
				}
				else{
    				for(i=0;i<4;i++)
    				{
    					g_bmu_msg.cell_V[g_group][24+i] = (U16)g_mboxData[boxNumber][2*i+1]|(U16)g_mboxData[boxNumber][2*i]<<8;
    				}
				}
				break;
			case 0x0018FF28://BMU number = group; #8 frame, 4 cells each frame.
				BMU_OverTime[g_group] = 0;
				if(g_group == 1 || g_group == 7 || g_group == 13){
    				for(i=0;i<4;i++)
    				{
    					g_bmu_msg.cell_V[g_group][28+i] = 0;
    				}
				}
				else{
    				for(i=0;i<4;i++)
    				{
    					g_bmu_msg.cell_V[g_group][28+i] = (U16)g_mboxData[boxNumber][2*i+1]|(U16)g_mboxData[boxNumber][2*i]<<8;
    				}
				}
				break;
			case 0x0018FF29://BMU number = group; #9 frame, 4 cells each frame.
				BMU_OverTime[g_group] = 0;
				if(g_group == 1 || g_group == 7 || g_group == 13){
    				for(i=0;i<4;i++)
    				{
    					g_bmu_msg.cell_V[g_group][32+i] = 0;
    				}
				}
				else{
    				for(i=0;i<4;i++)
    				{
    					g_bmu_msg.cell_V[g_group][32+i] = (U16)g_mboxData[boxNumber][2*i+1]|(U16)g_mboxData[boxNumber][2*i]<<8;
    				}
				}
				break;
			case 0x0018FF41://BMU number = group; #1 frame, 1 temperature each frame.
				BMU_OverTime[g_group] = 0;
				for(i=0;i<1;i++){
					g_bmu_msg.cell_T[g_group][i]= g_mboxData[boxNumber][i];
				}
				break;	
			case 0x0018FF42://BMU number = group; #2 frame, 1 temperature each frame.	 
				BMU_OverTime[g_group] = 0;
				for(i=0;i<1;i++){
					g_bmu_msg.cell_T[g_group][i+1]= g_mboxData[boxNumber][i];
				}
				break;
             case 0x0018FF43://BMU number = group; #3 frame, 1 temperature each frame.
				BMU_OverTime[g_group] = 0;
				if(g_group == 1 || g_group == 7 || g_group == 13){
	                for(i=0;i<1;i++){
	                    g_bmu_msg.cell_T[g_group][i+2]= 0;
	                }
             	}
				else{
	                for(i=0;i<1;i++){
	                    g_bmu_msg.cell_T[g_group][i+2]= g_mboxData[boxNumber][i];
	                }
				}
                break;  	
			/* new add, the max and min voltage/temperature in erery pack */
		    case 0x0018FF36://组号＃1，电压最值   3601 表示BMU1的所有口的电压最值
				BMU_OverTime[g_group] = 0;
				g_bmu_msg.cell_V_max[g_group]= g_mboxData[boxNumber][3]|(unsigned int)g_mboxData[boxNumber][2]<<8;
				g_bmu_msg.cell_V_min[g_group]= g_mboxData[boxNumber][5]|(unsigned int)g_mboxData[boxNumber][4]<<8;
				g_bmu_msg.cell_V_max_group_num[g_group] = (g_mboxData[boxNumber][6] & 0xF0) >> 4;
				g_bmu_msg.cell_V_max_num[g_group]= g_mboxData[boxNumber][6] & 0x0F;
				g_bmu_msg.cell_V_min_group_num[g_group] = (g_mboxData[boxNumber][7] & 0xF0) >> 4;
				g_bmu_msg.cell_V_min_num[g_group]= g_mboxData[boxNumber][7] & 0x0F;
                break;
            case 0x0018FF4B://组号＃1，温度最值       
				BMU_OverTime[g_group] = 0;
				g_bmu_msg.cell_T_max[g_group]= g_mboxData[boxNumber][0];
				g_bmu_msg.cell_T_min[g_group]= g_mboxData[boxNumber][1];
				g_bmu_msg.cell_T_max_group_num[g_group]= (g_mboxData[boxNumber][2] & 0xF0) >> 4;
				g_bmu_msg.cell_T_max_num[g_group]= g_mboxData[boxNumber][2] & 0x0F;
				g_bmu_msg.cell_T_min_group_num[g_group]= (g_mboxData[boxNumber][3] & 0xF0) >> 4;
				g_bmu_msg.cell_T_min_num[g_group]= g_mboxData[boxNumber][3] & 0x0F;
                break;
            default:
                break;
		} // end switch(framID)  //解析数据
    }
}
//******************************************************************************
//* Function name:   HighGroup
//* Description:     最值模组位置确定
//* EntryParameter : None
//* ReturnValue    : 1，收到所有信息；0：未收到所有信息
//******************************************************************************
unsigned char ModelLocation(unsigned char Addr) 
{
    if((Addr==0)||(Addr==1))
        return 1;
    else
        return 2;
}
//******************************************************************************
//* Function name:   bmuProcess2
//* Description:     收到所有单体信息后，算出单体极值
//* EntryParameter : None
//* ReturnValue    : 1，收到所有信息；0：未收到所有信息
//******************************************************************************
unsigned char bmuProcess2(void)//
{
    U16         buf=0,Cell_V_Max=0,Cell_V_Min=0;
    U8          Cell_V_Max_Num=0,Cell_V_Min_Num=0;
    U8			Cell_V_Max_Pack_Num, Cell_V_Min_Pack_Num;
	
    U8          Cell_T_Max=0,Cell_T_Min=0;
    U8          Cell_T_Max_Num=0,Cell_T_Min_Num=0;  
    U8			Cell_T_Max_Pack_Num, Cell_T_Min_Pack_Num;
     
    U16         i,j;
    U32         sum=0;
//	U16			j,boxNumber=0,count=0;
//	U8          ti=0,ci=0;
//	U8          HighBMUAddr=0,HighBMUGroupNum=0,HighBMUNum=0;
//	U8          LowBMUAddr=0,LowBMUGroupNum=0,LowBMUNum=0;
//	static U8   ErrorBMUAddr=0;
//	static U8   ErrorBMUGroup=0;
//	static U8   ErrorBMULocation=0;
//	static U8	TemLossTime=0;
	static U8   TemLossState=0;
	
    U8          cnt = 0;
    U8          pack_cnt = 0;
    U8          cell_cnt = 0;
    
    //if((g_circleFlag==G_BMU_CIRCLE_FLAG)&&(g_configFlag==G_BMU_CIRCLE_FLAG))//如果收到所有的报文，则处理    
    {
        g_circleFlag=0; //配置信息1分钟才发一次，所以不能在这里把它的标志位清掉。 		  
		
        //计算电池单体最高和最低电压,温度                                          
        //***单体电压极值处理***********************************************************************************		      			
		//the init value for the local variables.
		pack_cnt = 0;
		for(cnt=0;cnt<BMU_NUMBER;cnt++){
			if(g_bmu_msg.cell_V_max_group_num[cnt] != 0){
				Cell_V_Max = g_bmu_msg.cell_V_max[cnt];
				Cell_V_Min = g_bmu_msg.cell_V_min[cnt];
				Cell_V_Max_Num = (g_bmu_msg.cell_V_max_group_num[cnt] - 1) + g_bmu_msg.cell_V_max_num[cnt];
				Cell_V_Min_Num = (g_bmu_msg.cell_V_min_group_num[cnt] - 1) + g_bmu_msg.cell_V_min_num[cnt];
				break;
			}
			else{
				pack_cnt++;
			}
		}
		if(pack_cnt == BMU_NUMBER){
			pack_cnt = 0;
			Cell_V_Max = 0XFFFF;
			Cell_V_Min = 0;
			Cell_V_Max_Num = 1;
			Cell_V_Min_Num = 1;
		}
        
        for(cnt=0;cnt<BMU_NUMBER;cnt++)
        {
            if(g_bmu_msg.cell_V_max[cnt] >= Cell_V_Max)
            {
                Cell_V_Max = g_bmu_msg.cell_V_max[cnt];
                Cell_V_Max_Num = (g_bmu_msg.cell_V_max_group_num[cnt] - 1) * 12
								 + g_bmu_msg.cell_V_max_num[cnt];
				Cell_V_Max_Pack_Num = cnt + 1;
            }
			
			if(g_bmu_msg.cell_V_min[cnt] != 0){
	            if(g_bmu_msg.cell_V_min[cnt] <= Cell_V_Min)
	            {
	                Cell_V_Min = g_bmu_msg.cell_V_min[cnt];
	                Cell_V_Min_Num = (g_bmu_msg.cell_V_min_group_num[cnt] - 1) * 12
									 + g_bmu_msg.cell_V_min_num[cnt];
					Cell_V_Min_Pack_Num = cnt + 1;
	            }
			}
            
            /* the max and min cell voltage store array */
            g_storageSysVariableCell[cnt*2]       = g_bmu_msg.cell_V_max[cnt];
            g_storageSysVariableCell[cnt*2 + 1]   = g_bmu_msg.cell_V_min[cnt];
        }

		if(Cell_V_Max == 0xffff){
			g_highestCellVoltage		= 0;
			g_highestCellVoltage_Num	= 1;

			g_bms_msg.CellVoltageMax = 0;
			g_bms_msg.CellVoltageMaxNum = 1;
			g_bms_msg.CellVoltageMaxPackNum = 1;
		}
		else{
			g_highestCellVoltage		= (float)Cell_V_Max / 10000;
			g_highestCellVoltage_Num	= Cell_V_Max_Num;
			
			g_bms_msg.CellVoltageMax = Cell_V_Max;
			g_bms_msg.CellVoltageMaxNum = Cell_V_Max_Num;
			g_bms_msg.CellVoltageMaxPackNum = Cell_V_Max_Pack_Num;
		}

		if(Cell_V_Min == 0){
			g_lowestCellVoltage 		= 0;
			g_lowestCellVoltage_Num 	= 1;
			
			g_bms_msg.CellVoltageMin = 0;
			g_bms_msg.CellVoltageMinNum = 1;
			g_bms_msg.CellVoltageMinPackNum = 1;
		}
		else{
			g_lowestCellVoltage 		= (float)Cell_V_Min / 10000; 
			g_lowestCellVoltage_Num 	= Cell_V_Min_Num;	  
			
			g_bms_msg.CellVoltageMin = Cell_V_Min;
			g_bms_msg.CellVoltageMinNum = Cell_V_Min_Num;
			g_bms_msg.CellVoltageMinPackNum = Cell_V_Min_Pack_Num;
		}
		
        //***单体温度极值处理***********************************************************************************		      			
//        Cell_T_Max = g_bmu_msg.cell_T_max[0];
//        Cell_T_Min = g_bmu_msg.cell_T_min[0];
//        Cell_T_Max_Num = (g_bmu_msg.cell_T_max_group_num[0] - 1) + g_bmu_msg.cell_T_max_num[0];
//        Cell_T_Min_Num = (g_bmu_msg.cell_T_min_group_num[0] - 1) + g_bmu_msg.cell_T_min_num[0];
		
		//the init value for the local variables.
		pack_cnt = 0;
		for(cnt=0;cnt<BMU_NUMBER;cnt++){
			if(g_bmu_msg.cell_T_max_group_num[cnt] != 0){
				Cell_T_Max = g_bmu_msg.cell_T_max[cnt];
				Cell_T_Min = g_bmu_msg.cell_T_min[cnt];
				Cell_T_Max_Num = (g_bmu_msg.cell_T_max_group_num[cnt] - 1) + g_bmu_msg.cell_T_max_num[cnt];
				Cell_T_Min_Num = (g_bmu_msg.cell_T_min_group_num[cnt] - 1) + g_bmu_msg.cell_T_min_num[cnt];
				break;
			}
			else{
				pack_cnt++;
			}
		}
		if(pack_cnt == BMU_NUMBER){
			pack_cnt = 0;
			Cell_T_Max = 0xff;
			Cell_T_Min = 0;
			Cell_T_Max_Num = 1;
			Cell_T_Min_Num = 1;
		}

		
        for(cnt=0;cnt<BMU_NUMBER;cnt++)
        {    						
            if(g_bmu_msg.cell_T_max[cnt] >= Cell_T_Max)
            {
                Cell_T_Max = g_bmu_msg.cell_T_max[cnt];
                Cell_T_Max_Num = (g_bmu_msg.cell_T_max_group_num[cnt] - 1) * 1 + g_bmu_msg.cell_T_max_num[cnt];
				Cell_T_Max_Pack_Num = cnt + 1;
            }

			if(g_bmu_msg.cell_T_min[cnt] != 0){
	            if(g_bmu_msg.cell_T_min[cnt] <= Cell_T_Min)
	            {
	                Cell_T_Min = g_bmu_msg.cell_T_min[cnt];
	                Cell_T_Min_Num = (g_bmu_msg.cell_T_min_group_num[cnt] * 1 - 1) + g_bmu_msg.cell_T_min_num[cnt];
					Cell_T_Min_Pack_Num = cnt + 1;
	            }
			}
            
            sum += (U32)(g_bmu_msg.cell_T_max[cnt] + g_bmu_msg.cell_T_min[cnt]);
            
            /* the max and min cell temperature store array */
            g_storageSysVariableT[cnt*2]     = g_bmu_msg.cell_T_max[cnt];
            g_storageSysVariableT[cnt*2 + 1] = g_bmu_msg.cell_T_min[cnt];
        } 			

		if(Cell_T_Max == 0xff){
			g_highestTemperature = 0;			//the temperature offset is 40 here.
			g_highestTemperature_Num = 1;
			
			g_bms_msg.CellTempMax = 0;
			g_bms_msg.CellTempMaxNum = 1;
			g_bms_msg.CellTempMaxPackNum = 1;
		}
		else{
			g_highestTemperature = Cell_T_Max;			//the temperature offset is 40 here.
			g_highestTemperature_Num = Cell_T_Max_Num;	//1~N
			
			g_bms_msg.CellTempMax = Cell_T_Max;
			g_bms_msg.CellTempMaxNum = Cell_T_Max_Num;
			g_bms_msg.CellTempMaxPackNum = Cell_T_Max_Pack_Num;
		}

		if(Cell_T_Min == 0){
			g_lowestTemperature = 0;		//the temperature offset is 40 here.
			g_lowestTemperature_Num = 1;	//1~N
			
			g_bms_msg.CellTempMin = 0;
			g_bms_msg.CellTempMinNum = 1;
			g_bms_msg.CellTempMinPackNum = 1;
		}
		else{
			g_lowestTemperature = Cell_T_Min;			//the temperature offset is 40 here.
	        g_lowestTemperature_Num = Cell_T_Min_Num;	//1~N
	        
			g_bms_msg.CellTempMin = Cell_T_Min;
			g_bms_msg.CellTempMinNum = Cell_T_Min_Num;
			g_bms_msg.CellTempMinPackNum = Cell_T_Min_Pack_Num;
		}

//		sum = sum - g_highestTemperature - g_lowestTemperature;
        sum = sum - g_bms_msg.CellTempMax - g_bms_msg.CellTempMin;
        g_averageTemperature = (U8)(sum / ((U32)BMU_NUMBER*2 - 2));

		sum = 0;
		for(pack_cnt = 0; pack_cnt < BMU_NUMBER; pack_cnt++){
			for(cell_cnt = 0; cell_cnt < CELL_NUMBER; cell_cnt++){
				sum += g_bmu_msg.cell_V[pack_cnt][cell_cnt];
			}
		}
		g_systemVoltage = (float)sum/30000;
		
        //************************************************************************************************
        for(i=0;i<1;i++)  //clear the receive buff.
        {
            g_mboxID=0;
            for(j=0;j<8;j++){
                g_mboxData[0][j] = 0;
            }
        }
        
        if((g_lowestCellVoltage==0)||(g_lowestTemperature==0)||(TemLossState==1)){              
            return 0;
        }
        else{ 
            return 1;	//all data processing is complete.
        }
  	} // end of circleflag	
}

//**********************************************************************
//**********************************************************************

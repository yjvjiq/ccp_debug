//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : S133
//* File Name          : MachineControl.c
//* Author             : judy
//* Version            : V1.0.0
//* Start Date         : 2016.2.14
//* Description        : 该文件用于状态转移判断
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "BMS20.h" 
unsigned char HighVolPowerOff = 0;//行车模式断高压请求
unsigned char OffState=0;//快充模式断高压请求
unsigned char PantographOff=0;//受电弓模式断高压请求

unsigned char ChangerINError = 2; //充电机ChanerIN信号突然没有:0:有ChanerIN信号;1:无ChangerIN信号;2：不确定
unsigned char State177End=0;//不停在177状态,
unsigned char PowerOffError=0;//行车模式下电故障

unsigned int Error10S=0; //行车和受电弓故障下电10S延时
unsigned int Error5S=0;  //快充下电5S延时
unsigned char E10SOverFlag=0; //10S延时完成标志位
unsigned int Error20S=0; //行车和受电弓故障下电10S延时后的20S延时
unsigned int Error_30s_delay_cnt = 0;
unsigned char TurnOffNRelay=0;//断负继电器完成标志位

//******************************************************************************
//* Function name:   stateCodeTransfer
//* Description:     在系统工作期间时刻检测当前信号，若没信号了，需要下电
//* EntryParameter : None
//* ReturnValue    : None
//******************************************************************************
void stateCodeTransfer(void) 
{
    static unsigned int Delay30=0;
    static unsigned int CDelay30=0;
    static unsigned int DCDelay30=0;
    static unsigned int DisChangerDelay=0;
    static unsigned int Delay110=0;
    static unsigned int Delay170=0;
    static unsigned int Delay126=0;
    static unsigned int Delay186=0;
    static unsigned int Delay30_81=0;
	static U16 DelayfPowerOffCnt = 0;
    static U16 charge_disable_cnt_t = 0;
	static U16 fast_charge_end_cnt_t = 0;
	        
    if(State177End==1)//在177状态下将变量State177End置1
    {
        stateCode=179;//调试模式
        return;
    }
    else if(TestState==1)
    {
        stateCode=177;//关闭继电器状态
        return;
    }
    /////////////////行车//////////////////////
    if(g_BmsModeFlag == DISCHARGING)
    {
		Error_Group1.Bit.St_CHG_Allow = 1;	// charge not allowed.
        if(stateCode == 11)
        {   
            stateCode = 12;
        }
        else if(stateCode == 12)
        {
            if((MSDError)||(N_RelayConnetError)||(HighVolPowerOff)||(acc_Connect == 0)
            ||(VCU_Request.Bit.Finish_PreChg)
            ||(g_bms_fault_msg.fault.HLVol_Lock_Alram == 1)
            ||(VCU_ChgControl.Bit.rise_Eleband_Switch)
//            ||(VCU_ChgControl.Bit.downC_OK == 0)
            ||(VCU_ChgControl_2.Bit.rise_Eleband_No_OK == 0)
            ){
                stateCode = 46;//MSD断路||负极粘连||需要下电的故障||ON=0||整车预充已完成
            }
            else if((VCU_Control.Bit.PowerOnOffReq == 1)&&(bmsSelfcheckCounter==1)){
                stateCode = 14;
            }
        }
        else if(stateCode == 14)
        {
            if((acc_Connect == 0)||(PowerOffError == 1)||(VCU_Request.Bit.Finish_PreChg == 1))
                stateCode = 44;//||整车预充已完成
            else if(status_group3.Bit.St_N_Relay == 1)
                stateCode = 17;
        }
        else if(stateCode == 17)
        {
          
           if((N_RelayDisConError)||(P_RelayConError)||(acc_Connect==0)
           ||(HighVolPowerOff==1)||(VCU_Request.Bit.Finish_PreChg))
                stateCode = 44; //负极继电器断路||正极粘连||需要下电的故障||ON=0||整车预充已完成
           else if(bmsSelfcheckCounter==2)
                stateCode = 20;
        }
        else if(stateCode == 20)
        {
            if((P_RelayDisConError==1)||(HighVolPowerOff == 1)||(acc_Connect == 0)||(VCU_Control.Bit.PowerOnOffReq == 2))
            {
				if(VCU_Control.Bit.PowerOnOffReq == 2){ // power off command exist 2s, then turn off the contactor.
					DelayfPowerOffCnt++;
					if(DelayfPowerOffCnt >= 50){ // delay 2s
						stateCode =40;
						DelayfPowerOffCnt = 0;
					}
				}
				else{
					stateCode = 40;//正极断路||需要下电的故障||ON=0
					DelayfPowerOffCnt = 0;
				}
            }
            else if((bmsSelfcheckCounter==3)&&(status_group3.Bit.St_P_Relay)&&(VCU_Request.Bit.Finish_PreChg))
                stateCode = 30;//自检计数器=3&&正极继电器闭合&&整车预充电完成
        } 
        else if(stateCode == 30)
        {
            if(((VCU_Control.Bit.PowerOnOffReq != 2)&&(E10SOverFlag == 1)&&(Error_30s_delay_cnt >= 30000))
				||((VCU_Control.Bit.PowerOnOffReq == 2)&&(E10SOverFlag == 1))//fault occured, and has delay 10s already, then received the power off command.
				||(Delay30 >= 400)
            )
            {
                 stateCode = 40;
                 Delay30 = 0;
            }
            else if((acc_Connect==0)||(VCU_Control.Bit.PowerOnOffReq == 2))//ACC disappear, 5ms*400=2S
            {
                Delay30++;
            }
            else 
            {
				//do nothing here, keep previous status.
            } 
              
        } 
        else if(stateCode == 40)//断开正极继电器
        {
            if(bmsSelfcheckCounter == 2)
                stateCode = 44; //自检计数器==2&&正极继电器已断开
        } 
        else if(stateCode == 44)
        { 
            if(TurnOffNRelay)
                stateCode = 46;
        }
        else if((stateCode == 46))
        {
            /////////////////////46 start/////////////////////////
            if((HighVolPowerOff) || (acc_Connect==0) || (RelayErrorPowerOff))
            {
                if(bmsSelfcheckCounter==1)//无故障
                    stateCode = 47;
            }
            else if(((VCU_ChgControl.Bit.rise_Eleband_Switch)
//				||(VCU_ChgControl.Bit.downC_OK == 0)
				||(VCU_ChgControl_2.Bit.rise_Eleband_No_OK == 0))
				&&(bmsSelfcheckCounter==1))
            {
                //降弓开关&&降弓到位&&自检计数器==1
                InitialSoc();
				g_BmsModeFlag = RECHARGING;//进入受电弓充电模式
				status_group4.Bit.Mode_BMS_Work = 2;//BMS当前工作状态=充电
				status_group3.Bit.St_CHG_Mode=2;//充电模式等于AC充电
				status_group3.Bit.St_Charge = 1;//正在充电 
                stateCode = 81;
                bmsSelfcheckCounter = 0;            
            }
        }
    }
    ///////////////受电弓充电 //////////////////
    else if(g_BmsModeFlag == RECHARGING)
    {
		Error_Group1.Bit.St_DisCHG_Allow = 1;	// discharge not allowed.
        if(stateCode == 81)
        {   
            if((VCU_ChgControl.Bit.rise_Eleband_Switch)
//				&&(VCU_ChgControl.Bit.downC_OK == 0)
				&&(VCU_ChgControl_2.Bit.rise_Eleband_No_OK == 0)
				&&(VCU_ParkBrake.Bit.Parking_Brake)){
                stateCode = 82;
				}
        }
        else if(stateCode == 82)
        {
			if(g_bms_msg.CellVoltageMax >= (U16)(HIGHEST_ALLOWED_CHARGE_CV * 10000)
				|| g_bms_msg.CellTempMax >= (U16)(HIGHEST_ALLOWED_CHARGE_T + 40)
				|| g_bms_msg.CellTempMin <= (LOWEST_ALLOWED_WORK_T + 40)
				||(g_bms_fault_msg.fault.HLVol_Lock_Alram == 1)){
				stateCode = 126;
			}
            else if((MSDError==1)||(CCHG_RelayConError == 1)||(PantographOff)
            ||(VCU_ChgControl.Bit.rise_Eleband_Switch == 0)
            ||(VCU_ChgControl.Bit.downC_OK == 1)
            ||(VCU_ChgControl_2.Bit.rise_Eleband_No_OK == 1)
            ||(VCU_ParkBrake.Bit.Parking_Brake==0))
                stateCode=126; //MSD断路||充电负粘连||需要下电故障||||降弓开关==0||降弓到位==0||驻车信号==0
            else if((bmsSelfcheckCounter==1) && (DC_Start == 1))
                stateCode=84; //自检计数器==1&&降弓到位&&降弓开关==1&&驻车信号==1
        }
        else if(stateCode == 84)
        {
            if((VCU_ChgControl.Bit.rise_Eleband_Switch == 0)
				||(VCU_ChgControl.Bit.downC_OK == 1)
				||(VCU_ChgControl_2.Bit.rise_Eleband_No_OK == 1)
				||(VCU_ParkBrake.Bit.Parking_Brake==0)||(PantographOff)){
                stateCode = 124;//降弓开关==0||降弓到位==0||驻车信号==0||需要下电故障
				}
            else{// if((BmsCtlStat0&0x08)!=0)//降弓到位&&降弓开关
                stateCode = 87;//充电负已闭合
            }
        }
        else if(stateCode == 87)
        {
            if((CHG_N_RelayDisConError)||(CCHG_RelayConError)||(PantographOff)
             ||(VCU_ChgControl.Bit.rise_Eleband_Switch == 0)
             ||(VCU_ChgControl.Bit.downC_OK == 1)
             ||(VCU_ChgControl_2.Bit.rise_Eleband_No_OK == 1)
             ||(VCU_ParkBrake.Bit.Parking_Brake==0)){
                stateCode = 124;//高压检测2有故障||需下电的故障||降弓开关==0||降弓到位==0（车载WIFI)||驻车信号
			}
            else if(bmsSelfcheckCounter==2) {
                stateCode = 90;//自检计数器==2&&降弓开关==1&&降弓到位==1（车载WIFI)
            }
        }
        else if(stateCode == 90)
        {
            if((VCU_ChgControl.Bit.rise_Eleband_Switch == 0)
				||(VCU_ChgControl.Bit.downC_OK == 1)
				||(VCU_ChgControl_2.Bit.rise_Eleband_No_OK == 1)
				||(VCU_ParkBrake.Bit.Parking_Brake==0)
            	||(PantographOff)||(CCHG_RelayDisConError)){
                stateCode = 120; //高压检测3有故障||需下电的故障||降弓开关==0||降弓到位==0（车载WIFI)||驻车信号 
            }
            else if(bmsSelfcheckCounter==3){
                stateCode = 110;//自检计数器==3&&降弓开关==1&&降弓到位==1&&充电开关==1
            }
        }
        else if(stateCode == 110)
        {
            if((slowRechargeFinished == 1)
			||((PantographOff == 1)&&(E10SOverFlag == 1)&&(g_systemCurrent > -5))//延时10S下电
			||((PantographOff == 1)&&(E10SOverFlag == 1)&&(Error20S>=20000)&&(g_systemCurrent <= -5))//故障延时10S&&电流大于5A，再持续20S
            ){
                stateCode = 120;//充电已完成或者需下电的故障或者检测降弓开关==0||降弓到位==0||充电开关==0    
            }
            else if((VCU_ChgControl.Bit.rise_Eleband_Switch == 0)
            ||(VCU_ChgControl.Bit.downC_OK == 1)
            ||(VCU_ChgControl_2.Bit.rise_Eleband_No_OK == 1)
            ||(VCU_ParkBrake.Bit.Parking_Brake==0) 
			||((fastendflag == 1) && (PantographOff != 1)) // charge finished and no fault.
			)
            {
                CDelay30++;
				if(CDelay30 >= 400){	//充电信号无     5ms * 400 = 2.0S
					CDelay30 = 0;
					stateCode = 120;
				}
            }
        } 
        else if(stateCode == 120)//断开受电弓继电器
        {
            if(bmsSelfcheckCounter == 2)//自检计数器=2
                stateCode = 124;
        } 
        else if(stateCode == 124)
        { 
            if(TurnOffNRelay)//确保充电负继电器已断开
                stateCode = 126;
        } 
        else if((stateCode == 126))
        {
            if(((bmsSelfcheckCounter==1)&&(g_highVoltageV3<200))||(acc_Connect==0)||(OffState)||(PantographOff))//无故障
			{
                stateCode = 127;
			}
		} 
    }
    ///////////////////////////快充/////////////////////////////////
    else if(g_BmsModeFlag == FASTRECHARGING)
    {
		Error_Group1.Bit.St_DisCHG_Allow = 1;	// discharge not allowed.
        if(stateCode == 141)
        {
            InsRelayControl = 1;//快充时采绝缘控制给SBMS
            if((status_group3.Bit.St_N_Relay == 0)&&(status_group3.Bit.St_P_Relay == 0)
            &&(CC2VOL<=CC2VOLHIGH)&&(CC2VOL>=CC2VOLLOW)) //CC2电压在范围内
                stateCode = 142;
        }
        else if(stateCode == 142)
        {
			if(g_bms_msg.CellVoltageMax >= (U16)(HIGHEST_ALLOWED_CHARGE_CV * 10000)
				|| g_bms_msg.CellTempMax >= (U16)(HIGHEST_ALLOWED_CHARGE_T + 40)
				|| g_bms_msg.CellTempMin <= (LOWEST_ALLOWED_WORK_T + 40)
				||(g_bms_fault_msg.fault.HLVol_Lock_Alram == 1)
				||(DCTem1 >= Chg_Socet_Max_Temperatue_lv1)
				||(DCTem2 >= Chg_Socet_Max_Temperatue_lv1)
				){
				stateCode = 186;
				
				if((DCTem1 >= Chg_Socet_Max_Temperatue_lv2)
				||(DCTem2 >= Chg_Socet_Max_Temperatue_lv2)){
					fastendflag = 1;
					fastend2 |= 0x40;//连接器温度过大
					OffState = 1;//请求下电
					Error_Group0.Bit.F2_Ele_Relay_Con = 3;//整车CAN赋值     
				}
				else if((DCTem1 >= Chg_Socet_Max_Temperatue_lv1)
				||(DCTem2 >= Chg_Socet_Max_Temperatue_lv1)){
					fastendflag = 1;
					fastend2 |= 0x40;//连接器温度过大
					OffState = 1;//请求下电
					Error_Group0.Bit.F2_Ele_Relay_Con = 2;//整车CAN赋值     
				}
				
			}
            else if((MSDError)||(DCCHG_RelayConError == 1)||(plug_DC_Connect == 0)||(OffState))
                stateCode = 186;//高压检测1有故障||需下电的故障||CC2==0 ||ChargeIN==0
            else if((plug_DC_Connect == 1)&&(bmsSelfcheckCounter==1) && (DC_Start == 1))
                stateCode = 144;
        }
        else if(stateCode == 144)
        {
            if((plug_DC_Connect == 0)||(OffState == 1))
                stateCode = 184; //需下电的故障||CC2==0 ||ChargeIN==0
            else if(plug_DC_Connect == 1)//&&((BmsCtlStat0&0x08)!=0)
                stateCode = 147;//负极继电器已经闭合&&CC2==1&&ChargeIN==1
        }
        else if(stateCode == 147)
        {
           if((CHG_N_RelayDisConError==1)||(DCCHG_RelayConError==1)||(plug_DC_Connect == 0)||(OffState))
                stateCode = 184;//高压检测2有故障||需下电的故障||CC2==0 ||ChargeIN==0
           else if((plug_DC_Connect == 1)&&(bmsSelfcheckCounter==2))
                stateCode = 150;//自检计数器==2&&CC2==1&&ChargeIN==1
        }
        else if (stateCode == 150)
        {                                      
            if((plug_DC_Connect == 0)||(DCCHG_RelayDisConError==1)||(OffState))
                stateCode = 180;//高压检测3有故障||需下电的故障||CC2==0 ||ChargeIN==0
            else if((bmsSelfcheckCounter==3)&&(plug_DC_Connect == 1)&&(status_group2.Bit.St_CHG_Connect == 2))
                stateCode = 170;
        }
        else if(stateCode == 170)
        {
            if(((OffState)&&(Error5S >= 5000))
				||(DCDelay30 >= 400))
            { 
                 stateCode = 180;
                 DCDelay30 = 0; 
            }  
            else if(plug_DC_Connect == 0)//CC2无    5ms*300=2.5S
            {                
                DCDelay30++; 
            }
			else if(fastendflag == 1){
				fast_charge_end_cnt_t++;
				if(fast_charge_end_cnt_t >= 1000){
					fast_charge_end_cnt_t = 0;
					stateCode = 180;
				}
			}
        } 
        else if(stateCode == 180)//断开快充继电器
        {
            if(bmsSelfcheckCounter == 2)
                stateCode = 184;
        } 
        else if(stateCode == 184)
        { 
            if(TurnOffNRelay)//确保负断开
                stateCode = 186;
        } 
        else if((stateCode == 186))
        {
			if(bmsSelfcheckCounter == 1){
                stateCode = 187;
			}
        } 
    } 
}
//*************************************************************************
//**************************the end *********************************************
//************************************************************************************
//******************************************************************************************

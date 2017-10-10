//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : 黄海10.5m
//* File Name          : Heat.c
//* Author             : 孙丽雪
//* Version            : V1.0.0
//* Start Date         : 2016.9.6
//* Description        : 该文件用于加热管理
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include  "BMS20.h"
unsigned char st_heating;//动力电池加热状态：0未加热；1预加热中；2边充电边加热中
float HeatCurt;
unsigned char heatingStart=0;//预加热停止标志位
unsigned char BeforeTempFlag1=0;//上电前温度判断<0
unsigned char BeforeTempFlag2=0;//上电前温度判断 <10
//unsigned char BeforeTempFlag3=0;//上电前温度判断 >10

typedef enum{
	T_CMD_POWER_OFF = 0,
	T_CMD_COOL,
	T_CMD_HEAT,
	T_CMD_SELF_LOOP
} T_CMD;

typedef enum{
	T_CTRL_HV_ON_REQ = 0,
	T_CTRL_HV_OFF_REQ
}T_CTRL_HV_REQ;
	
//***********************************************************************
//* Function name:   HeatManage
//* Description:     状态机为100，110，170的时候进行热管理
//* EntryParameter : None
//* ReturnValue    : None
//************************************************************************
void HeatManage(void)
{
    static unsigned int tt=0;
    
    if(Tavg==0)
    {
        st_heating==0;  
        return;
    }
    if(g_highestCellVoltage>HIGHEST_ALLOWED_CHARGE_CV)
        return;
    //************未加热阶段,温度区间是大于等于10度st_heating都为0
    if(st_heating==0)
    {
        //if(Tavg<40)//0+40,小于0度，进入预加热阶段
        if(Tavg<=(START_ALLOWED_PreHEAT_CHARGE_TEM+40))//小于0度，进入预加热阶段 只加热不充电
        {
            st_heating=1;
            HeatCurt = HIGHEST_ALLOWED_HEAT_CHARGE_C;
            BeforeTempFlag1=1;
            heatingStart=1;
   
        } 
        else if(Tavg<=(START_ALLOWED_HEAT_CHARGE_TEM+40))//10，进入边加热边充电阶段
        {
            st_heating=2;
            HeatCurt=HIGHEST_ALLOWED_HEAT_CHARGE_C;
            BeforeTempFlag2=1;
  
        }
    }
    //*************在预加热阶段，只加热，请求电流只请求加热电流，不请求充电电流
    if(st_heating==1)
    {
        if(Tavg>(STOP_ALLOWED_PreHEAT_CHARGE_TEM+40)) //大于等于5度°，预加热结束
        {
            st_heating=2;
            HeatCurt=HIGHEST_ALLOWED_HEAT_CHARGE_C;
            heatingStart=0;
        }
    }
    //*************在边加热边充电阶段   
    if(st_heating==2)
    {
        if(Tavg>(STOP_ALLOWED_HEAT_CHARGE_TEM+40)) //大于等于15°，加热边充电阶段结束
        {
            st_heating=0;
            HeatCurt=0;
            BeforeTempFlag1=0;
            BeforeTempFlag2=0;
        }
        if(Tavg<(BACK_HEAT_TEM+40))  //小于-1度，跳回只加热阶段
        {
            st_heating=1;
            HeatCurt = HIGHEST_ALLOWED_HEAT_CHARGE_C;
        }
    }
}
//******************************************************************************
//* Function name:   HeatAndChargeControl
//* Description:     边充电边加热加热继电器控制
//* EntryParameter : void
//* ReturnValue    : void
//******************************************************************************
void HeatAndChargeControl(void)
{
   
    static unsigned int time;
    /*if(st_heating==0) //
    {
        TurnOff_INHK();//断开加热继电器
    } 
    else if(st_heating==1)  //进行预加热
    {
        TurnOn_INHK(); //闭合加热继电器 
    }*/
    if(HeatFlag==0) //
    {
        TurnOff_INHK();//断开加热继电器
    } 
    else if(HeatFlag==1)  //进行预加热
    {
        TurnOn_INHK(); //闭合加热继电器 
    }
    else if(HeatFlag==3)  //断开加热
    {
        TurnOff_INHK(); //断开加热
    }   
    else
    {
        if(Tavg>(STOP_ALLOWED_HEAT_CHARGE_TEM+40)) //如果温度大于40+15度，则断开加热继电器
        {
            TurnOff_INHK();  
        }
        else if(Tavg<=(START_ALLOWED_HEAT_CHARGE_TEM+40))//如果温度小于40+10度，则闭合加热继电器
        { 
            TurnOn_INHK();
        }
        if((g_systemCurrent>=2)&&(g_lowestCellVoltage<2.8))//防止用电池进行加热
        {      
            time++;
            if(time>100)//250ms*100=25S
                TurnOff_INHK();        
        } 
        else
            time=0;
    }
}


//******************************************************************************
//* Function name:   T_Control_Process
//* Description:     used for water cool system, control the temperature by Tmax.
//* EntryParameter : void
//* ReturnValue    : void
//******************************************************************************
void T_Ctrl_Process(void){
	U16 buff = 0;
	static U8 T_ctrl_state = 0;
	static U8 T_power_on_flag = 0;
	static U16 cnt = 0;
	static U16 cnt_2 = 0;
	
  	if(stateCode != 30 && stateCode != 110 && stateCode != 170){
		g_BMS_TMS_msg.msg.HV_on_request = T_CTRL_HV_OFF_REQ;
		return;
	}

	if((g_bms_msg.CellTempMax <= (25 + 40)) && (g_bms_msg.CellTempMax != 0xff)){
		if(T_ctrl_state == 3){
			T_ctrl_state = 4;
		}
		else if(T_ctrl_state == 4){
			T_ctrl_state = 4;
		}
		else{
			T_ctrl_state = 1;
		}
	}
	else if((g_bms_msg.CellTempMax >= (25 + 40))
		&&(g_bms_msg.CellTempMax < (32 + 40))
		&& (g_bms_msg.CellTempMax != 0xff)) {
		if(T_ctrl_state == 4){
			T_ctrl_state = 4;
		}
		else if(T_ctrl_state == 3){
			T_ctrl_state = 3;
		}
		else{
			T_ctrl_state = 2;
		}
	}
	else if((g_bms_msg.CellTempMax >= (32 + 40))
		&& (g_bms_msg.CellTempMax != 0xff)){
		T_ctrl_state = 3;
	}

	if(g_TMS_BMS_msg.msg.fault_level == 1){
		T_ctrl_state = 1;
	}
	else if(g_TMS_BMS_msg.msg.fault_level == 2){
		T_ctrl_state = 4;
	}
	else if(g_TMS_BMS_msg.msg.fault_level == 3){
		// do nothing, ignore the fault level.
	}
	

	switch(T_ctrl_state){
		case 1:
			g_BMS_TMS_msg.msg.mode_cmd = T_CMD_POWER_OFF;
			KHeat_Switch(OFF);
			g_BMS_TMS_msg.msg.HV_relay_status = St_heatManage;
			T_power_on_flag = 0;
			g_BMS_TMS_msg.msg.HV_on_request = T_CTRL_HV_OFF_REQ; // 0 = power on request, 1 = power off request
			break;
		case 2:
			if(g_TMS_BMS_msg.msg.TMS_HV_status == 1 && T_power_on_flag == 0 && (St_heatManage == 0)){
				g_BMS_TMS_msg.msg.HV_on_request = T_CTRL_HV_OFF_REQ;
				KHeat_Switch(OFF);
				cnt++;
				if(cnt >= 400){ //400*5ms = 2000ms = 2s
					T_power_on_flag = 1;
					cnt = 0;
				}
			}
			else{
				T_power_on_flag = 1;
				cnt = 0;
				KHeat_Switch(ON);
				g_BMS_TMS_msg.msg.mode_cmd = T_CMD_SELF_LOOP;
				g_BMS_TMS_msg.msg.HV_on_request = T_CTRL_HV_ON_REQ; // 0 = power on request, 1 = power off request
			}
			
			g_BMS_TMS_msg.msg.HV_relay_status = St_heatManage;
			break;
		case 3:
			if((g_TMS_BMS_msg.msg.TMS_HV_status == 1) && (T_power_on_flag == 0) && (St_heatManage == 0)){
				g_BMS_TMS_msg.msg.HV_on_request = T_CTRL_HV_OFF_REQ;
				KHeat_Switch(OFF);
				cnt_2++;
				if(cnt_2 >= 400){ //400*5ms = 2000ms = 2s
					T_power_on_flag = 1;
					cnt_2 = 0;
				}
			}
			else{
				T_power_on_flag = 1;
				cnt_2 = 0;
				g_BMS_TMS_msg.msg.mode_cmd = T_CMD_COOL;
				KHeat_Switch(ON);
				g_BMS_TMS_msg.msg.HV_on_request = T_CTRL_HV_ON_REQ; // 0 = power on request, 1 = power off request
			}
			
			g_BMS_TMS_msg.msg.HV_relay_status = St_heatManage;
			break;
		case 4:
			g_BMS_TMS_msg.msg.mode_cmd = T_CMD_POWER_OFF;
			g_BMS_TMS_msg.msg.HV_on_request = T_CTRL_HV_OFF_REQ; // 0 = power on request, 1 = power off request
			if(g_TMS_BMS_msg.msg.TMS_HV_status == 0){
				KHeat_Switch(OFF);
				g_BMS_TMS_msg.msg.HV_relay_status = St_heatManage;
				T_ctrl_state = 0;
			}
			
			break;
		default:
			break;
	}

	g_BMS_TMS_msg.msg.CellTempMax	= g_bms_msg.CellTempMax;
	g_BMS_TMS_msg.msg.CellTempMin	= g_bms_msg.CellTempMin;
	g_BMS_TMS_msg.msg.pack_volt		= (U16)g_systemVoltage;
	g_BMS_TMS_msg.msg.T_goal		= 13 + 40;
	
	if(g_BmsModeFlag == RECHARGING || g_BmsModeFlag == FASTRECHARGING){
		g_BMS_TMS_msg.msg.chg_mode = 1;
	}
	else{
		g_BMS_TMS_msg.msg.chg_mode = 0;
	}
}




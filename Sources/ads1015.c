//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : FOTTON-2T-5T
//* File Name          : ads1015.c
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2015.7.4
//* Description        : 该程序针对AD芯片ads1015进行读写,在BMS中测量2个差分通道的温度
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "derivative.h" /* include peripheral declarations */
#include "ads1015.h"
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

#define i2c_Delay 50       //I2C延时时间
#define ADS_RE_COUNT 10   //如果从ADS1015返回的响应失败，重复次数

#define SCL_ADS1015_DIR  DDR0AD0_DDR0AD05  //1--output  0---input      PAD13
#define SCL_ADS1015      PT0AD0_PT0AD05
#define SDA_ADS1015_DIR  DDR1AD0_DDR1AD05  //1--output  0---input        PAD05
#define SDA_ADS1015      PT1AD0_PT1AD05

static unsigned int m_i2cAddress;  
static unsigned int m_conversionDelay;  
static unsigned int m_bitShift;  
static int m_gain;  
static unsigned int m_chn;                           
//**********************************************************************
//* Function name:   IIC_Delay
//* Description:     延时
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void IIC_Delay(unsigned int value)
{
    while(value--);
}
//**********************************************************************
//* Function name:   StartRom
//* Description:     提供i2c总线工作时序中的起始位(SCL为高时SDA的一个下降沿,而后两线都为低)
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void StartRom(void)
{
	  SDA_ADS1015_DIR=1;
	  SCL_ADS1015_DIR=1;
	  asm("nop");
  	SDA_ADS1015=1;
    SCL_ADS1015=1;             //SCL and SDA set to inputs, signals go high due to pull-up resistors
    IIC_Delay(i2c_Delay);
    SDA_ADS1015=0;             //Set to output, data low so SDA = 0
    IIC_Delay(i2c_Delay);
    SCL_ADS1015=0;             //Set to output, data low so SCL = 0
    IIC_Delay(i2c_Delay);
}
//**********************************************************************
//* Function name:   StopRom
//* Description:     提供i2c总线工作时序中的停止位
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void StopRom(void)
{
	  SDA_ADS1015_DIR=1;
	  asm("nop");
	  SDA_ADS1015=0;                        //Set to output, data low so SDA = 0
    IIC_Delay(i2c_Delay);
    SCL_ADS1015=1;                        //Set to input, SCL = 1 due to pull-up
    IIC_Delay(i2c_Delay);
    SDA_ADS1015=1;                       //Set to input, SDA = 1 due to pull-up
    IIC_Delay(i2c_Delay);
}
//**********************************************************************
//* Function name:   ClockADS1015
//* Description:     时钟
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void ClockADS1015(void)
{
  	SCL_ADS1015=1;                              //Set to input, SCL = 1 due to pull-up
  	IIC_Delay(i2c_Delay);
  	SCL_ADS1015=0;                                //Set to output, data low so SCL = 0
  	IIC_Delay(i2c_Delay);

}
//**********************************************************************
//* Function name:   nmack
//* Description:    空响应 
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
void nmack(void)
{
 	  SDA_ADS1015_DIR=1;
	  asm("nop");
 	  SDA_ADS1015=1;                          //Set to input, SDA = 1 due to pull-up
  	ClockADS1015();
    SDA_ADS1015_DIR=1;
    asm("nop");
  	SDA_ADS1015=1;                               //Set to input, SDA = 1 due to pull-up
}
//**********************************************************************
//* Function name:   e2ack
//* Description:     ack from ads1015 to MCU
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************
unsigned int e2ack(void)   //ack from ads1015 to MCU
{
	  unsigned int m=0;
	  
	  SDA_ADS1015_DIR=0;
	  asm("nop");
	  if(SDA_ADS1015)                 //"高电平
  	{
	      m=0;
  	}
	  else
	  {
	      m=0x55;
	  }
    ClockADS1015();
    
    return m;

}

//**********************************************************************
//* Function name:   mack
//* Description:     ack from MCU TO ads1015
//* EntryParameter : None
//* ReturnValue    : None
//**********************************************************************

void mack()   //ack from MCU TO ads1015
{
    SDA_ADS1015_DIR=1;
    SDA_ADS1015=0;                        //Set to output, data low so SDA = 0
    ClockADS1015();

}

//**********************************************************************
//* Function name:   SendToRom
//* Description:     向24c64写入一个字节
//* EntryParameter : 一个字节
//* ReturnValue    : None
//**********************************************************************
unsigned int SendToRom(unsigned int d)
{
	  unsigned char i;
	  unsigned char dd;
	  unsigned int m=0;
	  
	  dd =(unsigned char)d;
	  
	  SDA_ADS1015_DIR=1;
    asm("nop");
	  for(i=8;i>0;i--)
	  {
		    
		    if(dd & 0x80)
	    	{
			      SDA_ADS1015=1;        //Set to input, SDA = 1 due to pull-up
		    }
	    	else
		    {
			      SDA_ADS1015=0;           //Set to output, data low so SDA = 0
		    }
		    dd <<= 1;
		    ClockADS1015();
	  }
    m= e2ack();
    return m; 
    
}
//**********************************************************************
//* Function name:   ReceiveFromRom
//* Description:     从24c64读出一个字节
//* EntryParameter : None
//* ReturnValue    : 一个字节
//**********************************************************************
unsigned char ReceiveFromRom(void)
{
	  unsigned char i,dd;
	  
	  dd=0;
	  
	  SDA_ADS1015_DIR=0;
	  asm("nop");
	  asm("nop");
	  asm("nop");
	  asm("nop");  //此处需要一点延时
	  for(i=8;i>0;i--)
	  {    		

    	  dd <<= 1;
    		if(SDA_ADS1015)           //读 1
        { 
            dd=dd|0x01;    
        }
        else                     //读 0
        {
            dd=dd&0xfe;
        }
        ClockADS1015();		
  	}
	  return dd;
}
//**********************************************************************
//* Function name:   writeRegister
//* Description:     写寄存器
//* EntryParameter : 芯片地址，寄存器地址，寄存器配置
//* ReturnValue    : none
//**********************************************************************
void writeRegister(unsigned int i2cAddress, unsigned int reg, unsigned int value)   
{  
    unsigned int i;  
  
 
    for(i = 0; i < ADS_RE_COUNT; i++)  
    {                 
        StopRom();  
        IIC_Delay(i2c_Delay);  
        StartRom(); 
        
        if(SendToRom(i2cAddress) == 1)  
            continue;  
        if(SendToRom(reg&0xFF) == 1)  
            continue;  
        if(SendToRom(value>>8) == 1)  
            continue;  
        if(SendToRom(value&0xFF) == 1)  
            continue;  
         
        break;  
 
    }      
    StopRom();   
    IIC_Delay(i2c_Delay);      
 
}  
//**********************************************************************
//* Function name:   readRegister
//* Description:     写寄存器
//* EntryParameter : 芯片地址，寄存器地址
//* ReturnValue    : 一个unsigned int寄存器里的值
//**********************************************************************  
unsigned int readRegister(unsigned int i2cAddress, unsigned int reg)   
{  
    unsigned int i, ret;  
  
     
    for(i = 0; i < ADS_RE_COUNT; i++)  
    {                 
        StopRom();  
        IIC_Delay(i2c_Delay);  
        StartRom();  
       
        if(SendToRom(i2cAddress) == 1)  
            continue;  
        if(SendToRom(ADS1015_REG_POINTER_CONVERT) == 1)  
            continue;  
        StopRom();  
        IIC_Delay(i2c_Delay);  
        StartRom();  
        if(SendToRom(i2cAddress|0x0001) == 1)  
            continue;  
       
     
        ret = ReceiveFromRom() << 8;  
        mack();  
  
        ret |= ReceiveFromRom();  
        mack();  
  
        break;          
    }      
    StopRom();   
    IIC_Delay(i2c_Delay);  
    
      
    return ret;    
} 
//**********************************************************************
//* Function name:   ads1015_init
//* Description:     ADS1015芯片初始化
//* EntryParameter : 初始化芯片地址，转换时间，转移位，AD范围，通道号
//* ReturnValue    : 一个unsigned int寄存器里的值
//********************************************************************** 
void ads1015_init(void)  
{  
    m_i2cAddress = ADS1015_ADDRESS;  
    m_conversionDelay = ADS1015_CONVERSIONDELAY;  
    m_bitShift = 4;  
    m_gain = GAIN_ONE; /* +/- 6.144V range (limited to VDD +0.3V max!) */  
    m_chn = 0;  
} 
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

#if 0  
/**************************************************************************/  
/*!  
    @brief  Writes 16-bits to the specified destination register  
*/  
/**************************************************************************/  
static void writeRegister(unsigned int i2cAddress, unsigned int reg, unsigned int value)  
{  
    Wire.beginTransmission(i2cAddress);  
    i2cwrite((unsigned int)reg);  
    i2cwrite((unsigned int)(value >> 8));  
    i2cwrite((unsigned int)(value & 0xFF));  
    Wire.endTransmission();  
}  
  
/**************************************************************************/  
/*!  
    @brief  Writes 16-bits to the specified destination register  
*/  
/**************************************************************************/  
static unsigned int readRegister(unsigned int i2cAddress, unsigned int reg)  
{  
    Wire.beginTransmission(i2cAddress);  
    i2cwrite(ADS1015_REG_POINTER_CONVERT);  
    Wire.endTransmission();  
    Wire.requestFrom(i2cAddress, (unsigned int)2);  
    return ((i2cread() << 8) | i2cread());  
}  
  
/**************************************************************************/  
/*!  
    @brief  Sets the gain and input voltage range  
*/  
/**************************************************************************/  
void setGain(adsGain_t gain)  
{  
    m_gain = gain;  
}  
  
/**************************************************************************/  
/*!  
    @brief  Gets a gain and input voltage range  
*/  
/**************************************************************************/  
adsGain_t getGain()  
{  
    return m_gain;  
}  
 
#endif   
//**********************************************************************
//* Function name:   read_adc_config
//* Description:     写入配置寄存器
//* EntryParameter : none
//* ReturnValue    : none
//**********************************************************************   
void read_adc_config(void)  
{  
    unsigned int  config;  
  
    // Start with default values  
    config = ADS1015_REG_CONFIG_CQUE_NONE    | // Disable the comparator (default val)  
            ADS1015_REG_CONFIG_CLAT_NONLAT  | // Non-latching (default val)  
            ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)  
            ADS1015_REG_CONFIG_CMODE_TRAD   | // Traditional comparator (default val)  
            ADS1015_REG_CONFIG_DR_1600SPS   | // 1600 samples per second (default)  
            ADS1015_REG_CONFIG_MODE_SINGLE;   // Single-shot mode (default)  
  
    // Set PGA/voltage range  
    config |= m_gain;  
  
    // Set single-ended input channel  
    switch (m_chn)  
    {  
    case (0):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;  
        break;  
    case (1):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;  
        break;  
    case (2):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;  
        break;  
    case (3):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;  
        break;  
    }  
  
    // Set 'start single-conversion' bit  
    config |= ADS1015_REG_CONFIG_OS_SINGLE;  
  
    // Write config register to the ADC  
    writeRegister(m_i2cAddress, ADS1015_REG_POINTER_CONFIG, config);  
      
}  
#if 0
//**********************************************************************
//* Function name:   read_adc_reg
//* Description:     读取ADC寄存器里的AD值
//* EntryParameter : 通道1的ADC寄存器，通道0的ADC寄存器
//* ReturnValue    : none
//**********************************************************************  
void read_adc_reg(volatile unsigned int *res0, volatile unsigned int *res1)  
{  
    if(m_chn)  
    {  
        *res1 = readRegister(m_i2cAddress, ADS1015_REG_POINTER_CONVERT) >> m_bitShift;  
        m_chn = 0;  
    }  
    else  
    {  
        *res0 = readRegister(m_i2cAddress, ADS1015_REG_POINTER_CONVERT) >> m_bitShift;  
        m_chn = 1;  
    }  
} 
//**********************************************************************
//* Function name:   get_adc
//* Description:     配置寄存器后，读取ADC寄存器的值
//* EntryParameter : 通道1的ADC寄存器，通道0的ADC寄存器
//* ReturnValue    : none
//**********************************************************************  
void get_adc(volatile unsigned int *res0, volatile unsigned int *res1)  
{  
    #define PER_CNT 6  
    static volatile unsigned int i = 0;  
  
    if(i == 0)  
    {  
        read_adc_config();  
    }  
  
    if(i == PER_CNT)  
    {  
        read_adc_reg(res0, res1);  
    }  
    if(i++ > PER_CNT) i = 0;  
}  
#endif 

//**********************************************************************
//* Function name:   readADC_Differential_0_1
//* Description:     Reads the conversion results, measuring the voltage  
//*                  difference between the P (AIN0) and N (AIN1) input.  Generates  
//*                  a signed value since the difference can be either  
//*                  positive or negative. 
//* EntryParameter : void
//* ReturnValue    : unsigned int 的AD值
//********************************************************************** 
unsigned int readADC_Differential_0_1(void)  
{  
    unsigned int res, config;  
    // Start with default values  
    config = ADS1015_REG_CONFIG_CQUE_NONE    | // Disable the comparator (default val)  
             ADS1015_REG_CONFIG_CLAT_NONLAT  | // Non-latching (default val)  
             ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)  
             ADS1015_REG_CONFIG_CMODE_TRAD   | // Traditional comparator (default val)  
             ADS1015_REG_CONFIG_DR_1600SPS   | // 1600 samples per second (default)  
             ADS1015_REG_CONFIG_MODE_SINGLE;   // Single-shot mode (default)  
  
    // Set PGA/voltage range  
    config |= m_gain;  
  
    // Set channels  
    config |= ADS1015_REG_CONFIG_MUX_DIFF_0_1;          // AIN0 = P, AIN1 = N  
  
    // Set 'start single-conversion' bit  
    config |= ADS1015_REG_CONFIG_OS_SINGLE;  
  
    // Write config register to the ADC  
    writeRegister(m_i2cAddress, ADS1015_REG_POINTER_CONFIG, config);  
  
    // Wait for the conversion to complete  
    //DELAY_US(m_conversionDelay);  
    IIC_Delay(500);
    // Read the conversion results  
    res = readRegister(m_i2cAddress, ADS1015_REG_POINTER_CONVERT) >> m_bitShift;  
    if (m_bitShift == 0)  
    {  
        return (int)res;  
    }  
    else  
    {  
        // Shift 12-bit results right 4 bits for the ADS1015,  
        // making sure we keep the sign bit intact  
        if (res > 0x07FF)  
        {  
            // negative number - extend the sign to 16th bit  
            res |= 0xF000;  
        }  
        return (int)res;  
    }  
}  
  
/**************************************************************************/  
/*!  
    @brief  Reads the conversion results, measuring the voltage  
            difference between the P (AIN2) and N (AIN3) input.  Generates  
            a signed value since the difference can be either  
            positive or negative.  
*/  
/**************************************************************************/ 
//**********************************************************************
//* Function name:   readADC_Differential_0_1
//* Description:     Reads the conversion results, measuring the voltage  
//*                  difference between the P (AIN2) and N (AIN3) input.  Generates  
//*                  a signed value since the difference can be either  
//*                  positive or negative. 
//* EntryParameter : void
//* ReturnValue    : unsigned int 的AD值
//**********************************************************************  
unsigned int readADC_Differential_2_3(void)  
{  
    unsigned int res, config;  
    // Start with default values  
    config = ADS1015_REG_CONFIG_CQUE_NONE    | // Disable the comparator (default val)  
             ADS1015_REG_CONFIG_CLAT_NONLAT  | // Non-latching (default val)  
             ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)  
             ADS1015_REG_CONFIG_CMODE_TRAD   | // Traditional comparator (default val)  
             ADS1015_REG_CONFIG_DR_1600SPS   | // 1600 samples per second (default)  
             ADS1015_REG_CONFIG_MODE_SINGLE;   // Single-shot mode (default)  
  
    // Set PGA/voltage range  
    config |= m_gain;  
  
    // Set channels  
    config |= ADS1015_REG_CONFIG_MUX_DIFF_2_3;          // AIN2 = P, AIN3 = N  
  
    // Set 'start single-conversion' bit  
    config |= ADS1015_REG_CONFIG_OS_SINGLE;  
  
    // Write config register to the ADC  
    writeRegister(m_i2cAddress, ADS1015_REG_POINTER_CONFIG, config);  
  
    // Wait for the conversion to complete  
    //DELAY_US(m_conversionDelay);  
    IIC_Delay(500);
    // Read the conversion results  
    res = readRegister(m_i2cAddress, ADS1015_REG_POINTER_CONVERT) >> m_bitShift;  
    if (m_bitShift == 0)  
    {  
        return (int)res;  
    }  
    else  
    {  
        // Shift 12-bit results right 4 bits for the ADS1015,  
        // making sure we keep the sign bit intact  
        if (res > 0x07FF)  
        {  
            // negative number - extend the sign to 16th bit  
            res |= 0xF000;  
        }  
        return (int)res;  
    }  
} 
 
 
/**************************************************************************/  
/*!  
    @brief  Gets a single-ended ADC reading from the specified channel  
*/  
/**************************************************************************/  
unsigned int readADC_SingleEnded(unsigned int channel) 
{  
    unsigned int  config;  
    if (channel > 3)  
    {  
        return 0;  
    }  
  
    // Start with default values  
    config = ADS1015_REG_CONFIG_CQUE_NONE    | // Disable the comparator (default val)  
            ADS1015_REG_CONFIG_CLAT_NONLAT  | // Non-latching (default val)  
            ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)  
            ADS1015_REG_CONFIG_CMODE_TRAD   | // Traditional comparator (default val)  
            ADS1015_REG_CONFIG_DR_1600SPS   | // 1600 samples per second (default)  
            ADS1015_REG_CONFIG_MODE_SINGLE;   // Single-shot mode (default)  
  
    // Set PGA/voltage range  
    config |= m_gain;  
  
    // Set single-ended input channel  
    switch (channel)  
    {  
    case (0):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;  
        break;  
    case (1):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;  
        break;  
    case (2):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;  
        break;  
    case (3):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;  
        break;  
    }  
  
    // Set 'start single-conversion' bit  
    config |= ADS1015_REG_CONFIG_OS_SINGLE;  
  
    // Write config register to the ADC  
    writeRegister(m_i2cAddress, ADS1015_REG_POINTER_CONFIG, config);  
  
    // Wait for the conversion to complete  
    //DELAY_US(m_conversionDelay);  
    //DELAY_US(350);  
    IIC_Delay(500);
    // Read the conversion results  
    // Shift 12-bit results right 4 bits for the ADS1015  
    return readRegister(m_i2cAddress, ADS1015_REG_POINTER_CONVERT) >> m_bitShift;  
}
#if 0     
/**************************************************************************/  
/*!  
    @brief  Sets up the comparator to operate in basic mode, causing the  
            ALERT/RDY pin to assert (go from high to low) when the ADC  
            value exceeds the specified threshold.  
  
            This will also set the ADC in continuous conversion mode.  
*/  
/**************************************************************************/  
void startComparator_SingleEnded(unsigned int channel, int16_t threshold)  
{  
    // Start with default values  
    unsigned int config = ADS1015_REG_CONFIG_CQUE_1CONV   | // Comparator enabled and asserts on 1 match  
                    ADS1015_REG_CONFIG_CLAT_LATCH   | // Latching mode  
                    ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)  
                    ADS1015_REG_CONFIG_CMODE_TRAD   | // Traditional comparator (default val)  
                    ADS1015_REG_CONFIG_DR_1600SPS   | // 1600 samples per second (default)  
                    ADS1015_REG_CONFIG_MODE_CONTIN  | // Continuous conversion mode  
                    ADS1015_REG_CONFIG_MODE_CONTIN;   // Continuous conversion mode  
  
    // Set PGA/voltage range  
    config |= m_gain;  
  
    // Set single-ended input channel  
    switch (channel)  
    {  
    case (0):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;  
        break;  
    case (1):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;  
        break;  
    case (2):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;  
        break;  
    case (3):  
        config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;  
        break;  
    }  
  
    // Set the high threshold register  
    // Shift 12-bit results left 4 bits for the ADS1015  
    writeRegister(m_i2cAddress, ADS1015_REG_POINTER_HITHRESH, threshold << m_bitShift);  
  
    // Write config register to the ADC  
    writeRegister(m_i2cAddress, ADS1015_REG_POINTER_CONFIG, config);  
}  
  
/**************************************************************************/  
/*!  
    @brief  In order to clear the comparator, we need to read the  
            conversion results.  This function reads the last conversion  
            results without changing the config value.  
*/  
/**************************************************************************/  
int getLastConversionResults(void)  
{  
    unsigned int res;  
    // Wait for the conversion to complete  
    DELAY_US(m_conversionDelay);  
  
    // Read the conversion results  
    res = readRegister(m_i2cAddress, ADS1015_REG_POINTER_CONVERT) >> m_bitShift;  
    if (m_bitShift == 0)  
    {  
        return (int)res;  
    }  
    else  
    {  
        // Shift 12-bit results right 4 bits for the ADS1015,  
        // making sure we keep the sign bit intact  
        if (res > 0x07FF)  
        {  
            // negative number - extend the sign to 16th bit  
            res |= 0xF000;  
        }  
        return (int)res;  
    }  
}  
#endif  

//=============================================================================================
//=============================================================================================
//=============================================================================================
//===================================the end ====================================================
//=============================================================================================
//=============================================================================================
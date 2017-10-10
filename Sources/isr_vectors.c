//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//---------------------- Pride Power------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//* Project Name       : C50ES_FP
//* File Name          : isr_vectors.C
//* Author             : Judy
//* Version            : V1.0.0
//* Start Date         : 2011,06,02
//* Description        : 该程序针对9s12xep100的中断矢量进行定义，以及使用了哪些中断进行声明
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

extern void near _Startup(void);       /* Startup routine */
extern void near PIT0_ISR(void);  
extern void near RTI_ISR(void);  
extern void near ADC0_ISR(void); 
extern void near CAN0_RECEIVE_ISR(void);
extern void near CAN1_RECEIVE_ISR(void);
extern void near CAN2_RECEIVE_ISR(void);


#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void Unimplemented_ISR(void)
{
   /* Unimplemented ISRs trap.*/
   asm BGND;
}
#pragma CODE_SEG DEFAULT
   
typedef void (*near tIsrFunc)(void);
const tIsrFunc VectorTable[] @0x7F10 = 
{
    Unimplemented_ISR,    // Vector base + 0x10   Spurious interrupt
    Unimplemented_ISR,    // Vector base + 0x12   System Call Interrupt (SYS)
    Unimplemented_ISR,    // Vector base + 0x14   MPU Access Error
    Unimplemented_ISR,    // Vector base + 0x16   XGATE software error interrupt
    Unimplemented_ISR,    // Vector base + 0x18   Reserved
    Unimplemented_ISR,    // Vector base + 0x1A   Reserved
    Unimplemented_ISR,    // Vector base + 0x1C   Reserved
    Unimplemented_ISR,    // Vector base + 0x1E   Reserved
    Unimplemented_ISR,    // Vector base + 0x20   Reserved
    Unimplemented_ISR,    // Vector base + 0x22   Reserved
    Unimplemented_ISR,    // Vector base + 0x24   Reserved
    Unimplemented_ISR,    // Vector base + 0x26   Reserved
    Unimplemented_ISR,    // Vector base + 0x28   Reserved
    Unimplemented_ISR,    // Vector base + 0x2A   Reserved
    Unimplemented_ISR,    // Vector base + 0x2C   Reserved
    Unimplemented_ISR,    // Vector base + 0x2E   Reserved
    Unimplemented_ISR,    // Vector base + 0x30   Reserved
    Unimplemented_ISR,    // Vector base + 0x32   Reserved
    Unimplemented_ISR,    // Vector base + 0x34   Reserved
    Unimplemented_ISR,    // Vector base + 0x36   Reserved
    Unimplemented_ISR,    // Vector base + 0x38   Reserved
    Unimplemented_ISR,    // Vector base + 0x3A   Reserved
    Unimplemented_ISR,    // Vector base + 0x3C   ATD1 Compare Interrupt
    Unimplemented_ISR,    // Vector base + 0x3E   ATD0 Compare Interrupt
    Unimplemented_ISR,    // Vector base + 0x40   TIM Pulse accumulator input edge
    Unimplemented_ISR,    // Vector base + 0x42   TIM Pulse accumulator A overflow
    Unimplemented_ISR,    // Vector base + 0x44   TIM timer overflow
    Unimplemented_ISR,    // Vector base + 0x46   TIM timer channel 7
    Unimplemented_ISR,    // Vector base + 0x48   TIM timer channel 6
    Unimplemented_ISR,    // Vector base + 0x4A   TIM timer channel 5
    Unimplemented_ISR,    // Vector base + 0x4C   TIM timer channel 4
    Unimplemented_ISR,    // Vector base + 0x4E   TIM timer channel 3
    Unimplemented_ISR,    // Vector base + 0x50   TIM timer channel 2
    Unimplemented_ISR,    // Vector base + 0x52   TIM timer channel 1
    Unimplemented_ISR,    // Vector base + 0x54   TIM timer channel 0
    Unimplemented_ISR,    // Vector base + 0x56   SCI7
    Unimplemented_ISR,    // Vector base + 0x58   Periodic interrupt timer channel 7
    Unimplemented_ISR,    // Vector base + 0x5A   Periodic interrupt timer channel 6
    Unimplemented_ISR,    // Vector base + 0x5C   Periodic interrupt timer channel 5
    Unimplemented_ISR,    // Vector base + 0x5E   Periodic interrupt timer channel 4
    Unimplemented_ISR,    // Vector base + 0x60   Reserved
    Unimplemented_ISR,    // Vector base + 0x62   Reserved
    Unimplemented_ISR,    // Vector base + 0x64   XGATE software trigger 7
    Unimplemented_ISR,    // Vector base + 0x66   XGATE software trigger 6
    Unimplemented_ISR,    // Vector base + 0x68   XGATE software trigger 5
    Unimplemented_ISR,    // Vector base + 0x6A   XGATE software trigger 4
    Unimplemented_ISR,    // Vector base + 0x6C   XGATE software trigger 3
    Unimplemented_ISR,    // Vector base + 0x6E   XGATE software trigger 2
    Unimplemented_ISR,    // Vector base + 0x70   XGATE software trigger 1
    Unimplemented_ISR,    // Vector base + 0x72   XGATE software trigger 0
    Unimplemented_ISR,    // Vector base + 0x74   Periodic interrupt timer channel 3
    Unimplemented_ISR,    // Vector base + 0x76   Periodic interrupt timer channel 2
    Unimplemented_ISR,    // Vector base + 0x78   Periodic interrupt timer channel 1
    PIT0_ISR,                // Vector base + 0x7A   Periodic interrupt timer channel 0
    Unimplemented_ISR,    // Vector base + 0x7C   High Temperature Interrupt (HTI)
    Unimplemented_ISR,    // Vector base + 0x7E   Autonomous periodical interrupt (API)
    Unimplemented_ISR,    // Vector base + 0x80   Low-voltage interrupt (LVI)
    Unimplemented_ISR,    // Vector base + 0x82   IIC1 Bus
    Unimplemented_ISR,    // Vector base + 0x84   SCI5
    Unimplemented_ISR,    // Vector base + 0x86   SCI4
    Unimplemented_ISR,    // Vector base + 0x88   SCI3
    Unimplemented_ISR,    // Vector base + 0x8A   SCI2
    Unimplemented_ISR,    // Vector base + 0x8C   PWM emergency shutdown
    Unimplemented_ISR,    // Vector base + 0x8E   Port P Interrupt
    Unimplemented_ISR,    // Vector base + 0x90   CAN4 transmit
    Unimplemented_ISR,    // Vector base + 0x92   CAN4 receive
    Unimplemented_ISR,    // Vector base + 0x94   CAN4 errors
    Unimplemented_ISR,    // Vector base + 0x96   CAN4 wake-up
    Unimplemented_ISR,    // Vector base + 0x98   CAN3 transmit
    Unimplemented_ISR,    // Vector base + 0x9A   CAN3 receive
    Unimplemented_ISR,    // Vector base + 0x9C   CAN3 errors
    Unimplemented_ISR,    // Vector base + 0x9E   CAN3 wake-up
    Unimplemented_ISR,    // Vector base + 0xA0   CAN2 transmit
    CAN2_RECEIVE_ISR,    // Vector base + 0xA2   CAN2 receive
    Unimplemented_ISR,    // Vector base + 0xA4   CAN2 errors
    Unimplemented_ISR,    // Vector base + 0xA6   CAN2 wake-up
    Unimplemented_ISR,    // Vector base + 0xA8   CAN1 transmit
    CAN1_RECEIVE_ISR,    // Vector base + 0xAA   CAN1 receive
    Unimplemented_ISR,    // Vector base + 0xAC   CAN1 errors
    Unimplemented_ISR,    // Vector base + 0xAE   CAN1 wake-up
    Unimplemented_ISR,    // Vector base + 0xB0   CAN0 transmit
    CAN0_RECEIVE_ISR,    // Vector base + 0xB2   CAN0 receive
    Unimplemented_ISR,    // Vector base + 0xB4   CAN0 errors
    Unimplemented_ISR,    // Vector base + 0xB6   CAN0 wake-up
    Unimplemented_ISR,    // Vector base + 0xB8   FLASH
    Unimplemented_ISR,    // Vector base + 0xBA   FLASH Fault Detect
    Unimplemented_ISR,    // Vector base + 0xBC   SPI2
    Unimplemented_ISR,    // Vector base + 0xBE   SPI1
    Unimplemented_ISR,    // Vector base + 0xC0   IIC0 bus
    Unimplemented_ISR,    // Vector base + 0xC2   SCI6
    Unimplemented_ISR,    // Vector base + 0xC4   CRG self-clock mode
    Unimplemented_ISR,    // Vector base + 0xC6   CRG PLL lock
    Unimplemented_ISR,    // Vector base + 0xC8   Pulse accumulator B overflow
    Unimplemented_ISR,    // Vector base + 0xCA   Modulus down counter underflow
    Unimplemented_ISR,    // Vector base + 0xCC   Port H
    Unimplemented_ISR,    // Vector base + 0xCE   Port J
    Unimplemented_ISR,    // Vector base + 0xD0   ATD1
    ADC0_ISR,             // Vector base + 0xD2   ATD0
    Unimplemented_ISR,    // Vector base + 0xD4   SCI1
    Unimplemented_ISR,    // Vector base + 0xD6   SCI0     
    Unimplemented_ISR,    // Vector base + 0xD8   SPI0     
    Unimplemented_ISR,    // Vector base + 0xDA   TIM Pulse accumulator input edge      
    Unimplemented_ISR,    // Vector base + 0xDC   TIM Pulse accumulator A overflow      
    Unimplemented_ISR,    // Vector base + 0xDE   TIM timer overflow      
    Unimplemented_ISR,    // Vector base + 0xE0   TIM timer channel 7      
    Unimplemented_ISR,    // Vector base + 0xE2   TIM timer channel 6      
    Unimplemented_ISR,    // Vector base + 0xE4   TIM timer channel 5      
    Unimplemented_ISR,    // Vector base + 0xE6   TIM timer channel 4      
    Unimplemented_ISR,    // Vector base + 0xE8   TIM timer channel 3      
    Unimplemented_ISR,    // Vector base + 0xEA   TIM timer channel 2      
    Unimplemented_ISR,    // Vector base + 0xEC   TIM timer channel 1      
    Unimplemented_ISR,    // Vector base + 0xEE   TIM timer channel 0      
    RTI_ISR,               // Vector base + 0xF0   Real time interrupt
    Unimplemented_ISR,    // Vector base + 0xF2   IRQ      
    Unimplemented_ISR,    // Vector base + 0xF4   XIRQ      
    Unimplemented_ISR,    // Vector base + 0xF6   SWI      
    Unimplemented_ISR     // Vector base + 0xF8   Unimplemented instruction trap      
};
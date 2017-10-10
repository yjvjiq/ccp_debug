/*
 * File: PackFault.c
 *
 * Code generated for Simulink model 'PackFault'.
 *
 * Model version                  : 1.121
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue Aug 01 17:19:25 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PackFault.h"
#include "PackFault_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define PackFault_IN_Delay30           ((uint8_T)1U)
#define PackFault_IN_Fault3            ((uint8_T)2U)
#define PackFault_IN_NO_ACTIVE_CHILD   ((uint8_T)0U)
#define PackFault_IN_Wait3             ((uint8_T)3U)

/* Block signals (auto storage) */
B_PackFault_T PackFault_B;

/* Block states (auto storage) */
DW_PackFault_T PackFault_DW;

/* Real-time model */
RT_MODEL_PackFault_T PackFault_M_;
RT_MODEL_PackFault_T *const PackFault_M = &PackFault_M_;

/* Model step function */
uint8_T PackFault_custom(real32_T I1, real32_T I2, real32_T I3)
{
  real32_T rtb_Abs1;
  real32_T rtb_Abs2;
  real32_T rtb_Abs3;

  /* specified return value */
  uint8_T F_lev;

  /* Abs: '<Root>/Abs1' incorporates:
   *  Inport: '<Root>/I1'
   */
  rtb_Abs1 = (real32_T)fabs(I1);

  /* Abs: '<Root>/Abs2' incorporates:
   *  Inport: '<Root>/I2'
   */
  rtb_Abs2 = (real32_T)fabs(I2);

  /* Abs: '<Root>/Abs3' incorporates:
   *  Inport: '<Root>/I3'
   */
  rtb_Abs3 = (real32_T)fabs(I3);

  /* Chart: '<Root>/Chart' */
  /* Gateway: Chart */
  if (PackFault_DW.temporalCounter_i1 < 31U) {
    PackFault_DW.temporalCounter_i1++;
  }

  /* During: Chart */
  if (PackFault_DW.is_active_c3_PackFault == 0U) {
    /* Entry: Chart */
    PackFault_DW.is_active_c3_PackFault = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F3': '<S1>:192' */
    /* Transition: '<S1>:191' */
    PackFault_DW.is_F3 = PackFault_IN_Wait3;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F3': '<S1>:192' */
    switch (PackFault_DW.is_F3) {
     case PackFault_IN_Delay30:
      /* During 'Delay30': '<S1>:184' */
      if (!(((rtb_Abs3 > 100.0F) && (rtb_Abs1 < rtb_Abs3 / 3.0F * 0.8)) ||
            ((rtb_Abs3 > 100.0F) && (rtb_Abs1 > rtb_Abs3 / 3.0F * 1.2)) ||
            ((rtb_Abs3 > 100.0F) && (rtb_Abs2 < rtb_Abs3 / 3.0F * 0.8)) ||
            ((rtb_Abs3 > 100.0F) && (rtb_Abs2 > rtb_Abs3 / 3.0F * 1.2)))) {
        /* Transition: '<S1>:187' */
        PackFault_DW.is_F3 = PackFault_IN_Wait3;
      } else {
        if (PackFault_DW.temporalCounter_i1 >= 20) {
          /* Transition: '<S1>:186' */
          PackFault_DW.is_F3 = PackFault_IN_Fault3;

          /* Entry 'Fault3': '<S1>:182' */
          PackFault_B.F_lev_i = 2U;
        }
      }
      break;

     case PackFault_IN_Fault3:
      /* During 'Fault3': '<S1>:182' */
      break;

     default:
      /* During 'Wait3': '<S1>:190' */
      if (((rtb_Abs3 > 100.0F) && (rtb_Abs1 < rtb_Abs3 / 3.0F * 0.8)) ||
          ((rtb_Abs3 > 100.0F) && (rtb_Abs1 > rtb_Abs3 / 3.0F * 1.2)) ||
          ((rtb_Abs3 > 100.0F) && (rtb_Abs2 < rtb_Abs3 / 3.0F * 0.8)) ||
          ((rtb_Abs3 > 100.0F) && (rtb_Abs2 > rtb_Abs3 / 3.0F * 1.2))) {
        /* Transition: '<S1>:188' */
        PackFault_DW.is_F3 = PackFault_IN_Delay30;
        PackFault_DW.temporalCounter_i1 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = PackFault_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void PackFault_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(PackFault_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &PackFault_B), 0,
                sizeof(B_PackFault_T));

  /* states (dwork) */
  (void) memset((void *)&PackFault_DW, 0,
                sizeof(DW_PackFault_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  PackFault_DW.is_F3 = PackFault_IN_NO_ACTIVE_CHILD;
  PackFault_DW.temporalCounter_i1 = 0U;
  PackFault_DW.is_active_c3_PackFault = 0U;
  PackFault_B.F_lev_i = 0U;
}

/* Model terminate function */
void PackFault_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

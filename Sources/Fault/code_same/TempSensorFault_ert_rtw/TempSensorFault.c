/*
 * File: TempSensorFault.c
 *
 * Code generated for Simulink model 'TempSensorFault'.
 *
 * Model version                  : 1.98
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Mon Apr 24 10:50:37 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TempSensorFault.h"
#include "TempSensorFault_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define TempSensorFa_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define TempSensorFault_IN_Delay10     ((uint8_T)1U)
#define TempSensorFault_IN_Fault1      ((uint8_T)2U)
#define TempSensorFault_IN_Wait1       ((uint8_T)3U)

/* Block signals (auto storage) */
B_TempSensorFault_T TempSensorFault_B;

/* Block states (auto storage) */
DW_TempSensorFault_T TempSensorFault_DW;

/* Real-time model */
RT_MODEL_TempSensorFault_T TempSensorFault_M_;
RT_MODEL_TempSensorFault_T *const TempSensorFault_M = &TempSensorFault_M_;

/* Model step function */
uint8_T TempSensorFault_custom(uint8_T tem)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/tem'
   */
  /* Gateway: Chart */
  if (TempSensorFault_DW.temporalCounter_i1 < 15U) {
    TempSensorFault_DW.temporalCounter_i1++;
  }

  /* During: Chart */
  if (TempSensorFault_DW.is_active_c3_TempSensorFault == 0U) {
    /* Entry: Chart */
    TempSensorFault_DW.is_active_c3_TempSensorFault = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F1': '<S1>:102' */
    /* Transition: '<S1>:108' */
    TempSensorFault_DW.is_F1 = TempSensorFault_IN_Wait1;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F1': '<S1>:102' */
    switch (TempSensorFault_DW.is_F1) {
     case TempSensorFault_IN_Delay10:
      /* During 'Delay10': '<S1>:28' */
      if (!((tem == 5) || (tem == 254))) {
        /* Transition: '<S1>:24' */
        TempSensorFault_DW.is_F1 = TempSensorFault_IN_Wait1;
      } else {
        if (TempSensorFault_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:26' */
          TempSensorFault_DW.is_F1 = TempSensorFault_IN_Fault1;

          /* Entry 'Fault1': '<S1>:23' */
          TempSensorFault_B.F_lev_i = 1U;
        }
      }
      break;

     case TempSensorFault_IN_Fault1:
      /* During 'Fault1': '<S1>:23' */
      break;

     default:
      /* During 'Wait1': '<S1>:98' */
      if ((tem == 5) || (tem == 254)) {
        /* Transition: '<S1>:25' */
        TempSensorFault_DW.is_F1 = TempSensorFault_IN_Delay10;
        TempSensorFault_DW.temporalCounter_i1 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = TempSensorFault_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void TempSensorFault_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(TempSensorFault_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &TempSensorFault_B), 0,
                sizeof(B_TempSensorFault_T));

  /* states (dwork) */
  (void) memset((void *)&TempSensorFault_DW, 0,
                sizeof(DW_TempSensorFault_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  TempSensorFault_DW.is_F1 = TempSensorFa_IN_NO_ACTIVE_CHILD;
  TempSensorFault_DW.temporalCounter_i1 = 0U;
  TempSensorFault_DW.is_active_c3_TempSensorFault = 0U;
  TempSensorFault_B.F_lev_i = 0U;
}

/* Model terminate function */
void TempSensorFault_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

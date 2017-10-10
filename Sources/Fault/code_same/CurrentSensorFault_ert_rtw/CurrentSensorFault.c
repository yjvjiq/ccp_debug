/*
 * File: CurrentSensorFault.c
 *
 * Code generated for Simulink model 'CurrentSensorFault'.
 *
 * Model version                  : 1.95
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 16 15:56:46 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CurrentSensorFault.h"
#include "CurrentSensorFault_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define CurrentSenso_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define CurrentSensorFault_IN_Delay10  ((uint8_T)1U)
#define CurrentSensorFault_IN_Fault1   ((uint8_T)2U)
#define CurrentSensorFault_IN_Wait1    ((uint8_T)3U)

/* Block signals (auto storage) */
B_CurrentSensorFault_T CurrentSensorFault_B;

/* Block states (auto storage) */
DW_CurrentSensorFault_T CurrentSensorFault_DW;

/* Real-time model */
RT_MODEL_CurrentSensorFault_T CurrentSensorFault_M_;
RT_MODEL_CurrentSensorFault_T *const CurrentSensorFault_M =
  &CurrentSensorFault_M_;

/* Model step function */
uint8_T CurrentSensorFault_custom(real32_T cur)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/cur'
   */
  /* Gateway: Chart */
  if (CurrentSensorFault_DW.temporalCounter_i1 < 31U) {
    CurrentSensorFault_DW.temporalCounter_i1++;
  }

  /* During: Chart */
  if (CurrentSensorFault_DW.is_active_c3_CurrentSensorFault == 0U) {
    /* Entry: Chart */
    CurrentSensorFault_DW.is_active_c3_CurrentSensorFault = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F1': '<S1>:102' */
    /* Transition: '<S1>:108' */
    CurrentSensorFault_DW.is_F1 = CurrentSensorFault_IN_Wait1;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F1': '<S1>:102' */
    switch (CurrentSensorFault_DW.is_F1) {
     case CurrentSensorFault_IN_Delay10:
      /* During 'Delay10': '<S1>:28' */
      if (!((cur > 500.0F) || (cur < -500.0F))) {
        /* Transition: '<S1>:24' */
        CurrentSensorFault_DW.is_F1 = CurrentSensorFault_IN_Wait1;
      } else {
        if (CurrentSensorFault_DW.temporalCounter_i1 >= 15) {
          /* Transition: '<S1>:26' */
          CurrentSensorFault_DW.is_F1 = CurrentSensorFault_IN_Fault1;

          /* Entry 'Fault1': '<S1>:23' */
          CurrentSensorFault_B.F_lev_i = 1U;
        }
      }
      break;

     case CurrentSensorFault_IN_Fault1:
      /* During 'Fault1': '<S1>:23' */
      break;

     default:
      /* During 'Wait1': '<S1>:98' */
      if ((cur > 500.0F) || (cur < -500.0F)) {
        /* Transition: '<S1>:25' */
        CurrentSensorFault_DW.is_F1 = CurrentSensorFault_IN_Delay10;
        CurrentSensorFault_DW.temporalCounter_i1 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = CurrentSensorFault_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void CurrentSensorFault_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(CurrentSensorFault_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &CurrentSensorFault_B), 0,
                sizeof(B_CurrentSensorFault_T));

  /* states (dwork) */
  (void) memset((void *)&CurrentSensorFault_DW, 0,
                sizeof(DW_CurrentSensorFault_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  CurrentSensorFault_DW.is_F1 = CurrentSenso_IN_NO_ACTIVE_CHILD;
  CurrentSensorFault_DW.temporalCounter_i1 = 0U;
  CurrentSensorFault_DW.is_active_c3_CurrentSensorFault = 0U;
  CurrentSensorFault_B.F_lev_i = 0U;
}

/* Model terminate function */
void CurrentSensorFault_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

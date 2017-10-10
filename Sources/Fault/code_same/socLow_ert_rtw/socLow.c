/*
 * File: socLow.c
 *
 * Code generated for Simulink model 'socLow'.
 *
 * Model version                  : 1.104
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 16 15:55:41 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "socLow.h"
#include "socLow_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define socLow_IN_Delay10              ((uint8_T)1U)
#define socLow_IN_Delay20              ((uint8_T)1U)
#define socLow_IN_Fault1               ((uint8_T)2U)
#define socLow_IN_Fault2               ((uint8_T)2U)
#define socLow_IN_NO_ACTIVE_CHILD      ((uint8_T)0U)
#define socLow_IN_Wait1                ((uint8_T)3U)
#define socLow_IN_Wait2                ((uint8_T)3U)

/* Block signals (auto storage) */
B_socLow_T socLow_B;

/* Block states (auto storage) */
DW_socLow_T socLow_DW;

/* Real-time model */
RT_MODEL_socLow_T socLow_M_;
RT_MODEL_socLow_T *const socLow_M = &socLow_M_;

/* Model step function */
uint8_T socLow_custom(real32_T soc)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/soc'
   */
  /* Gateway: Chart */
  if (socLow_DW.temporalCounter_i1 < 15U) {
    socLow_DW.temporalCounter_i1++;
  }

  if (socLow_DW.temporalCounter_i2 < 15U) {
    socLow_DW.temporalCounter_i2++;
  }

  /* During: Chart */
  if (socLow_DW.is_active_c3_socLow == 0U) {
    /* Entry: Chart */
    socLow_DW.is_active_c3_socLow = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F1': '<S1>:185' */
    /* Transition: '<S1>:184' */
    socLow_DW.is_F1 = socLow_IN_Wait1;

    /* Entry Internal 'F2': '<S1>:101' */
    /* Transition: '<S1>:173' */
    socLow_DW.is_F2 = socLow_IN_Wait2;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F1': '<S1>:185' */
    switch (socLow_DW.is_F1) {
     case socLow_IN_Delay10:
      /* During 'Delay10': '<S1>:181' */
      if (!(soc < 0.1F)) {
        /* Transition: '<S1>:188' */
        socLow_DW.is_F1 = socLow_IN_Wait1;
      } else {
        if (socLow_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:187' */
          socLow_DW.is_F1 = socLow_IN_Fault1;

          /* Entry 'Fault1': '<S1>:183' */
          socLow_B.F_lev_i = 1U;
        }
      }
      break;

     case socLow_IN_Fault1:
      /* During 'Fault1': '<S1>:183' */
      break;

     default:
      /* During 'Wait1': '<S1>:182' */
      if (soc < 0.1F) {
        /* Transition: '<S1>:186' */
        socLow_DW.is_F1 = socLow_IN_Delay10;
        socLow_DW.temporalCounter_i1 = 0U;
      }
      break;
    }

    /* During 'F2': '<S1>:101' */
    switch (socLow_DW.is_F2) {
     case socLow_IN_Delay20:
      /* During 'Delay20': '<S1>:22' */
      if (!(soc < 0.05F)) {
        /* Transition: '<S1>:18' */
        socLow_DW.is_F2 = socLow_IN_Wait2;
      } else {
        if (socLow_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:20' */
          socLow_DW.is_F2 = socLow_IN_Fault2;

          /* Entry 'Fault2': '<S1>:17' */
          socLow_B.F_lev_i = 2U;
        }
      }
      break;

     case socLow_IN_Fault2:
      /* During 'Fault2': '<S1>:17' */
      break;

     default:
      /* During 'Wait2': '<S1>:97' */
      if (soc < 0.05F) {
        /* Transition: '<S1>:19' */
        socLow_DW.is_F2 = socLow_IN_Delay20;
        socLow_DW.temporalCounter_i2 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = socLow_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void socLow_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(socLow_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &socLow_B), 0,
                sizeof(B_socLow_T));

  /* states (dwork) */
  (void) memset((void *)&socLow_DW, 0,
                sizeof(DW_socLow_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  socLow_DW.is_F1 = socLow_IN_NO_ACTIVE_CHILD;
  socLow_DW.temporalCounter_i1 = 0U;
  socLow_DW.is_F2 = socLow_IN_NO_ACTIVE_CHILD;
  socLow_DW.temporalCounter_i2 = 0U;
  socLow_DW.is_active_c3_socLow = 0U;
  socLow_B.F_lev_i = 0U;
}

/* Model terminate function */
void socLow_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

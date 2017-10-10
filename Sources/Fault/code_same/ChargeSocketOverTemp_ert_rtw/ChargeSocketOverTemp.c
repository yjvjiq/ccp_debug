/*
 * File: ChargeSocketOverTemp.c
 *
 * Code generated for Simulink model 'ChargeSocketOverTemp'.
 *
 * Model version                  : 1.106
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 16 15:56:57 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ChargeSocketOverTemp.h"
#include "ChargeSocketOverTemp_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define ChargeSocketOverTemp_IN_Delay20 ((uint8_T)1U)
#define ChargeSocketOverTemp_IN_Delay30 ((uint8_T)1U)
#define ChargeSocketOverTemp_IN_Fault2 ((uint8_T)2U)
#define ChargeSocketOverTemp_IN_Fault3 ((uint8_T)2U)
#define ChargeSocketOverTemp_IN_Wait2  ((uint8_T)3U)
#define ChargeSocketOverTemp_IN_Wait3  ((uint8_T)3U)
#define ChargeSocket_IN_NO_ACTIVE_CHILD ((uint8_T)0U)

/* Block signals (auto storage) */
B_ChargeSocketOverTemp_T ChargeSocketOverTemp_B;

/* Block states (auto storage) */
DW_ChargeSocketOverTemp_T ChargeSocketOverTemp_DW;

/* Real-time model */
RT_MODEL_ChargeSocketOverTemp_T ChargeSocketOverTemp_M_;
RT_MODEL_ChargeSocketOverTemp_T *const ChargeSocketOverTemp_M =
  &ChargeSocketOverTemp_M_;

/* Model step function */
uint8_T ChargeSocketOverTemp_custom(uint8_T Tso)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/Tso'
   */
  /* Gateway: Chart */
  if (ChargeSocketOverTemp_DW.temporalCounter_i1 < 15U) {
    ChargeSocketOverTemp_DW.temporalCounter_i1++;
  }

  if (ChargeSocketOverTemp_DW.temporalCounter_i2 < 15U) {
    ChargeSocketOverTemp_DW.temporalCounter_i2++;
  }

  /* During: Chart */
  if (ChargeSocketOverTemp_DW.is_active_c3_ChargeSocketOverTe == 0U) {
    /* Entry: Chart */
    ChargeSocketOverTemp_DW.is_active_c3_ChargeSocketOverTe = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F2': '<S1>:101' */
    /* Transition: '<S1>:173' */
    ChargeSocketOverTemp_DW.is_F2 = ChargeSocketOverTemp_IN_Wait2;

    /* Entry Internal 'F3': '<S1>:102' */
    /* Transition: '<S1>:108' */
    ChargeSocketOverTemp_DW.is_F3 = ChargeSocketOverTemp_IN_Wait3;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F2': '<S1>:101' */
    switch (ChargeSocketOverTemp_DW.is_F2) {
     case ChargeSocketOverTemp_IN_Delay20:
      /* During 'Delay20': '<S1>:22' */
      if (!(Tso >= 125)) {
        /* Transition: '<S1>:18' */
        ChargeSocketOverTemp_DW.is_F2 = ChargeSocketOverTemp_IN_Wait2;
      } else {
        if (ChargeSocketOverTemp_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:20' */
          ChargeSocketOverTemp_DW.is_F2 = ChargeSocketOverTemp_IN_Fault2;

          /* Entry 'Fault2': '<S1>:17' */
          ChargeSocketOverTemp_B.F_lev_i = 2U;
        }
      }
      break;

     case ChargeSocketOverTemp_IN_Fault2:
      /* During 'Fault2': '<S1>:17' */
      break;

     default:
      /* During 'Wait2': '<S1>:97' */
      if (Tso >= 125) {
        /* Transition: '<S1>:19' */
        ChargeSocketOverTemp_DW.is_F2 = ChargeSocketOverTemp_IN_Delay20;
        ChargeSocketOverTemp_DW.temporalCounter_i1 = 0U;
      }
      break;
    }

    /* During 'F3': '<S1>:102' */
    switch (ChargeSocketOverTemp_DW.is_F3) {
     case ChargeSocketOverTemp_IN_Delay30:
      /* During 'Delay30': '<S1>:28' */
      if (!(Tso >= 160)) {
        /* Transition: '<S1>:24' */
        ChargeSocketOverTemp_DW.is_F3 = ChargeSocketOverTemp_IN_Wait3;
      } else {
        if (ChargeSocketOverTemp_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:26' */
          ChargeSocketOverTemp_DW.is_F3 = ChargeSocketOverTemp_IN_Fault3;

          /* Entry 'Fault3': '<S1>:23' */
          ChargeSocketOverTemp_B.F_lev_i = 3U;
        }
      }
      break;

     case ChargeSocketOverTemp_IN_Fault3:
      /* During 'Fault3': '<S1>:23' */
      ChargeSocketOverTemp_B.F_lev_i = 3U;
      break;

     default:
      /* During 'Wait3': '<S1>:98' */
      if (Tso >= 160) {
        /* Transition: '<S1>:25' */
        ChargeSocketOverTemp_DW.is_F3 = ChargeSocketOverTemp_IN_Delay30;
        ChargeSocketOverTemp_DW.temporalCounter_i2 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = ChargeSocketOverTemp_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void ChargeSocketOverTemp_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(ChargeSocketOverTemp_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &ChargeSocketOverTemp_B), 0,
                sizeof(B_ChargeSocketOverTemp_T));

  /* states (dwork) */
  (void) memset((void *)&ChargeSocketOverTemp_DW, 0,
                sizeof(DW_ChargeSocketOverTemp_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  ChargeSocketOverTemp_DW.is_F2 = ChargeSocket_IN_NO_ACTIVE_CHILD;
  ChargeSocketOverTemp_DW.temporalCounter_i1 = 0U;
  ChargeSocketOverTemp_DW.is_F3 = ChargeSocket_IN_NO_ACTIVE_CHILD;
  ChargeSocketOverTemp_DW.temporalCounter_i2 = 0U;
  ChargeSocketOverTemp_DW.is_active_c3_ChargeSocketOverTe = 0U;
  ChargeSocketOverTemp_B.F_lev_i = 0U;
}

/* Model terminate function */
void ChargeSocketOverTemp_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

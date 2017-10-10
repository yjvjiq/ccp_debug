/*
 * File: ChargeDirectionFault.c
 *
 * Code generated for Simulink model 'ChargeDirectionFault'.
 *
 * Model version                  : 1.119
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Fri May 26 10:01:38 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ChargeDirectionFault.h"
#include "ChargeDirectionFault_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define ChargeDirect_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define ChargeDirectionFault_IN_Delay30 ((uint8_T)1U)
#define ChargeDirectionFault_IN_Fault3 ((uint8_T)2U)
#define ChargeDirectionFault_IN_Wait3  ((uint8_T)3U)

/* Block signals (auto storage) */
B_ChargeDirectionFault_T ChargeDirectionFault_B;

/* Block states (auto storage) */
DW_ChargeDirectionFault_T ChargeDirectionFault_DW;

/* Real-time model */
RT_MODEL_ChargeDirectionFault_T ChargeDirectionFault_M_;
RT_MODEL_ChargeDirectionFault_T *const ChargeDirectionFault_M =
  &ChargeDirectionFault_M_;

/* Model step function */
uint8_T ChargeDirectionFault_custom(real32_T cur, real32_T Vmin)
{
  int16_T tmp;

  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/Vmin'
   *  Inport: '<Root>/cur'
   */
  /* Gateway: Chart */
  /* During: Chart */
  if (ChargeDirectionFault_DW.is_active_c3_ChargeDirectionFau == 0U) {
    /* Entry: Chart */
    ChargeDirectionFault_DW.is_active_c3_ChargeDirectionFau = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F3': '<S1>:185' */
    /* Transition: '<S1>:184' */
    ChargeDirectionFault_DW.is_F3 = ChargeDirectionFault_IN_Wait3;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F3': '<S1>:185' */
    switch (ChargeDirectionFault_DW.is_F3) {
     case ChargeDirectionFault_IN_Delay30:
      /* During 'Delay30': '<S1>:181' */
      if (!((cur >= 2.0F) && (Vmin <= 2.5F))) {
        /* Transition: '<S1>:188' */
        ChargeDirectionFault_DW.is_F3 = ChargeDirectionFault_IN_Wait3;
      } else if (ChargeDirectionFault_DW.n == 100) {
        /* Transition: '<S1>:187' */
        ChargeDirectionFault_DW.is_F3 = ChargeDirectionFault_IN_Fault3;

        /* Entry 'Fault3': '<S1>:183' */
        ChargeDirectionFault_B.F_lev_i = 3U;
      } else {
        tmp = ChargeDirectionFault_DW.n + 1;
        if (tmp > 255) {
          tmp = 255;
        }

        ChargeDirectionFault_DW.n = (uint8_T)tmp;
      }
      break;

     case ChargeDirectionFault_IN_Fault3:
      /* During 'Fault3': '<S1>:183' */
      break;

     default:
      /* During 'Wait3': '<S1>:182' */
      if ((cur >= 2.0F) && (Vmin <= 2.5F)) {
        /* Transition: '<S1>:186' */
        ChargeDirectionFault_DW.is_F3 = ChargeDirectionFault_IN_Delay30;

        /* Entry 'Delay30': '<S1>:181' */
        tmp = ChargeDirectionFault_DW.n + 1;
        if (tmp > 255) {
          tmp = 255;
        }

        ChargeDirectionFault_DW.n = (uint8_T)tmp;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = ChargeDirectionFault_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void ChargeDirectionFault_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(ChargeDirectionFault_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &ChargeDirectionFault_B), 0,
                sizeof(B_ChargeDirectionFault_T));

  /* states (dwork) */
  (void) memset((void *)&ChargeDirectionFault_DW, 0,
                sizeof(DW_ChargeDirectionFault_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  ChargeDirectionFault_DW.is_F3 = ChargeDirect_IN_NO_ACTIVE_CHILD;
  ChargeDirectionFault_DW.is_active_c3_ChargeDirectionFau = 0U;
  ChargeDirectionFault_DW.n = 0U;
  ChargeDirectionFault_B.F_lev_i = 0U;
}

/* Model terminate function */
void ChargeDirectionFault_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

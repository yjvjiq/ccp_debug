/*
 * File: Supply24V.c
 *
 * Code generated for Simulink model 'Supply24V'.
 *
 * Model version                  : 1.122
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 16 15:55:24 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Supply24V.h"
#include "Supply24V_private.h"

/* Named constants for Chart: '<Root>/Logic' */
#define Supply24V_IN_Fault3            ((uint8_T)1U)
#define Supply24V_IN_NO_ACTIVE_CHILD   ((uint8_T)0U)
#define Supply24V_IN_Wait3             ((uint8_T)2U)

/* Block signals (auto storage) */
B_Supply24V_T Supply24V_B;

/* Block states (auto storage) */
DW_Supply24V_T Supply24V_DW;

/* Real-time model */
RT_MODEL_Supply24V_T Supply24V_M_;
RT_MODEL_Supply24V_T *const Supply24V_M = &Supply24V_M_;

/* Model step function */
uint8_T Supply24V_custom(real32_T V)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Logic' incorporates:
   *  Inport: '<Root>/V'
   */
  /* Gateway: Logic */
  /* During: Logic */
  if (Supply24V_DW.is_active_c3_Supply24V == 0U) {
    /* Entry: Logic */
    Supply24V_DW.is_active_c3_Supply24V = 1U;

    /* Entry Internal: Logic */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F3': '<S1>:102' */
    /* Transition: '<S1>:108' */
    Supply24V_DW.is_F3 = Supply24V_IN_Wait3;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F3': '<S1>:102' */
    if ((Supply24V_DW.is_F3 != Supply24V_IN_Fault3) && ((V < 11.0F) || (V >
          32.0F))) {
      /* During 'Wait3': '<S1>:98' */
      /* Transition: '<S1>:25' */
      Supply24V_DW.is_F3 = Supply24V_IN_Fault3;

      /* Entry 'Fault3': '<S1>:23' */
      Supply24V_B.F_lev_i = 1U;
    } else {
      /* During 'Fault3': '<S1>:23' */
    }
  }

  /* End of Chart: '<Root>/Logic' */

  /* Outport: '<Root>/F_lev' */
  F_lev = Supply24V_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void Supply24V_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Supply24V_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Supply24V_B), 0,
                sizeof(B_Supply24V_T));

  /* states (dwork) */
  (void) memset((void *)&Supply24V_DW, 0,
                sizeof(DW_Supply24V_T));

  /* SystemInitialize for Chart: '<Root>/Logic' */
  Supply24V_DW.is_F3 = Supply24V_IN_NO_ACTIVE_CHILD;
  Supply24V_DW.is_active_c3_Supply24V = 0U;
  Supply24V_B.F_lev_i = 0U;
}

/* Model terminate function */
void Supply24V_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

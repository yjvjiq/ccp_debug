/*
 * File: CellVolUnbalance.c
 *
 * Code generated for Simulink model 'CellVolUnbalance'.
 *
 * Model version                  : 1.90
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 16 15:57:32 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CellVolUnbalance.h"
#include "CellVolUnbalance_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define CellVolUnbal_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define CellVolUnbalance_IN_Delay20    ((uint8_T)1U)
#define CellVolUnbalance_IN_Delay21    ((uint8_T)2U)
#define CellVolUnbalance_IN_Fault2     ((uint8_T)3U)
#define CellVolUnbalance_IN_Fault20    ((uint8_T)4U)
#define CellVolUnbalance_IN_Wait2      ((uint8_T)5U)

/* Block signals (auto storage) */
B_CellVolUnbalance_T CellVolUnbalance_B;

/* Block states (auto storage) */
DW_CellVolUnbalance_T CellVolUnbalance_DW;

/* Real-time model */
RT_MODEL_CellVolUnbalance_T CellVolUnbalance_M_;
RT_MODEL_CellVolUnbalance_T *const CellVolUnbalance_M = &CellVolUnbalance_M_;

/* Model step function */
uint8_T CellVolUnbalance_custom(real32_T Vmax, real32_T Vmin)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/Vmax'
   *  Inport: '<Root>/Vmin'
   */
  /* Gateway: Chart */
  if (CellVolUnbalance_DW.temporalCounter_i1 < 15U) {
    CellVolUnbalance_DW.temporalCounter_i1++;
  }

  /* During: Chart */
  if (CellVolUnbalance_DW.is_active_c3_CellVolUnbalance == 0U) {
    /* Entry: Chart */
    CellVolUnbalance_DW.is_active_c3_CellVolUnbalance = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F2': '<S1>:101' */
    /* Transition: '<S1>:173' */
    CellVolUnbalance_DW.is_F2 = CellVolUnbalance_IN_Wait2;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F2': '<S1>:101' */
    switch (CellVolUnbalance_DW.is_F2) {
     case CellVolUnbalance_IN_Delay20:
      /* During 'Delay20': '<S1>:22' */
      if (!(Vmax - Vmin >= 0.8F)) {
        /* Transition: '<S1>:18' */
        CellVolUnbalance_DW.is_F2 = CellVolUnbalance_IN_Wait2;
      } else {
        if (CellVolUnbalance_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:20' */
          CellVolUnbalance_DW.is_F2 = CellVolUnbalance_IN_Fault2;

          /* Entry 'Fault2': '<S1>:17' */
          CellVolUnbalance_B.F_lev_i = 2U;
        }
      }
      break;

     case CellVolUnbalance_IN_Delay21:
      /* During 'Delay21': '<S1>:118' */
      if (!(Vmax - Vmin < 0.45F)) {
        /* Transition: '<S1>:70' */
        CellVolUnbalance_DW.is_F2 = CellVolUnbalance_IN_Fault2;

        /* Entry 'Fault2': '<S1>:17' */
        CellVolUnbalance_B.F_lev_i = 2U;
      } else {
        if (CellVolUnbalance_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:69' */
          CellVolUnbalance_DW.is_F2 = CellVolUnbalance_IN_Fault20;

          /* Entry 'Fault20': '<S1>:153' */
          CellVolUnbalance_B.F_lev_i = 0U;
        }
      }
      break;

     case CellVolUnbalance_IN_Fault2:
      /* During 'Fault2': '<S1>:17' */
      if (Vmax - Vmin < 0.45F) {
        /* Transition: '<S1>:72' */
        CellVolUnbalance_DW.is_F2 = CellVolUnbalance_IN_Delay21;
        CellVolUnbalance_DW.temporalCounter_i1 = 0U;
      }
      break;

     case CellVolUnbalance_IN_Fault20:
      /* During 'Fault20': '<S1>:153' */
      /* Transition: '<S1>:175' */
      CellVolUnbalance_DW.is_F2 = CellVolUnbalance_IN_Wait2;
      break;

     default:
      /* During 'Wait2': '<S1>:97' */
      if (Vmax - Vmin >= 0.8F) {
        /* Transition: '<S1>:19' */
        CellVolUnbalance_DW.is_F2 = CellVolUnbalance_IN_Delay20;
        CellVolUnbalance_DW.temporalCounter_i1 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = CellVolUnbalance_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void CellVolUnbalance_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(CellVolUnbalance_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &CellVolUnbalance_B), 0,
                sizeof(B_CellVolUnbalance_T));

  /* states (dwork) */
  (void) memset((void *)&CellVolUnbalance_DW, 0,
                sizeof(DW_CellVolUnbalance_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  CellVolUnbalance_DW.is_F2 = CellVolUnbal_IN_NO_ACTIVE_CHILD;
  CellVolUnbalance_DW.temporalCounter_i1 = 0U;
  CellVolUnbalance_DW.is_active_c3_CellVolUnbalance = 0U;
  CellVolUnbalance_B.F_lev_i = 0U;
}

/* Model terminate function */
void CellVolUnbalance_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

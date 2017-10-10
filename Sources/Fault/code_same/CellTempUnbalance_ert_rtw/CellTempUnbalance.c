/*
 * File: CellTempUnbalance.c
 *
 * Code generated for Simulink model 'CellTempUnbalance'.
 *
 * Model version                  : 1.117
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 16 15:57:54 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CellTempUnbalance.h"
#include "CellTempUnbalance_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define CellTempUnba_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define CellTempUnbalance_IN_Delay10   ((uint8_T)1U)
#define CellTempUnbalance_IN_Delay11   ((uint8_T)2U)
#define CellTempUnbalance_IN_Delay20   ((uint8_T)1U)
#define CellTempUnbalance_IN_Delay21   ((uint8_T)2U)
#define CellTempUnbalance_IN_Fault1    ((uint8_T)3U)
#define CellTempUnbalance_IN_Fault10   ((uint8_T)4U)
#define CellTempUnbalance_IN_Fault2    ((uint8_T)3U)
#define CellTempUnbalance_IN_Fault20   ((uint8_T)4U)
#define CellTempUnbalance_IN_Wait1     ((uint8_T)5U)
#define CellTempUnbalance_IN_Wait2     ((uint8_T)5U)

/* Block signals (auto storage) */
B_CellTempUnbalance_T CellTempUnbalance_B;

/* Block states (auto storage) */
DW_CellTempUnbalance_T CellTempUnbalance_DW;

/* Real-time model */
RT_MODEL_CellTempUnbalance_T CellTempUnbalance_M_;
RT_MODEL_CellTempUnbalance_T *const CellTempUnbalance_M = &CellTempUnbalance_M_;

/* Model step function */
uint8_T CellTempUnbalance_custom(uint8_T Tmax, uint8_T Tmin)
{
  /* specified return value */
  uint8_T arg_F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/Tmax'
   *  Inport: '<Root>/Tmin'
   */
  /* Gateway: Chart */
  if (CellTempUnbalance_DW.temporalCounter_i1 < 15U) {
    CellTempUnbalance_DW.temporalCounter_i1++;
  }

  if (CellTempUnbalance_DW.temporalCounter_i2 < 15U) {
    CellTempUnbalance_DW.temporalCounter_i2++;
  }

  /* During: Chart */
  if (CellTempUnbalance_DW.is_active_c3_CellTempUnbalance == 0U) {
    /* Entry: Chart */
    CellTempUnbalance_DW.is_active_c3_CellTempUnbalance = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F1': '<S1>:199' */
    /* Transition: '<S1>:193' */
    CellTempUnbalance_DW.is_F1 = CellTempUnbalance_IN_Wait1;

    /* Entry Internal 'F2': '<S1>:101' */
    /* Transition: '<S1>:173' */
    CellTempUnbalance_DW.is_F2 = CellTempUnbalance_IN_Wait2;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F1': '<S1>:199' */
    switch (CellTempUnbalance_DW.is_F1) {
     case CellTempUnbalance_IN_Delay10:
      /* During 'Delay10': '<S1>:190' */
      if (!(Tmax - Tmin >= 18)) {
        /* Transition: '<S1>:191' */
        CellTempUnbalance_DW.is_F1 = CellTempUnbalance_IN_Wait1;
      } else {
        if (CellTempUnbalance_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:202' */
          CellTempUnbalance_DW.is_F1 = CellTempUnbalance_IN_Fault1;

          /* Entry 'Fault1': '<S1>:197' */
          CellTempUnbalance_B.F_lev = 1U;
        }
      }
      break;

     case CellTempUnbalance_IN_Delay11:
      /* During 'Delay11': '<S1>:200' */
      if (!(Tmax - Tmin < 15)) {
        /* Transition: '<S1>:195' */
        CellTempUnbalance_DW.is_F1 = CellTempUnbalance_IN_Fault1;

        /* Entry 'Fault1': '<S1>:197' */
        CellTempUnbalance_B.F_lev = 1U;
      } else {
        if (CellTempUnbalance_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:194' */
          CellTempUnbalance_DW.is_F1 = CellTempUnbalance_IN_Fault10;

          /* Entry 'Fault10': '<S1>:198' */
          CellTempUnbalance_B.F_lev = 0U;
        }
      }
      break;

     case CellTempUnbalance_IN_Fault1:
      /* During 'Fault1': '<S1>:197' */
      if (Tmax - Tmin < 15) {
        /* Transition: '<S1>:201' */
        CellTempUnbalance_DW.is_F1 = CellTempUnbalance_IN_Delay11;
        CellTempUnbalance_DW.temporalCounter_i1 = 0U;
      }
      break;

     case CellTempUnbalance_IN_Fault10:
      /* During 'Fault10': '<S1>:198' */
      /* Transition: '<S1>:189' */
      CellTempUnbalance_DW.is_F1 = CellTempUnbalance_IN_Wait1;
      break;

     default:
      /* During 'Wait1': '<S1>:192' */
      if (Tmax - Tmin >= 18) {
        /* Transition: '<S1>:196' */
        CellTempUnbalance_DW.is_F1 = CellTempUnbalance_IN_Delay10;
        CellTempUnbalance_DW.temporalCounter_i1 = 0U;
      }
      break;
    }

    /* During 'F2': '<S1>:101' */
    switch (CellTempUnbalance_DW.is_F2) {
     case CellTempUnbalance_IN_Delay20:
      /* During 'Delay20': '<S1>:22' */
      if (!(Tmax - Tmin >= 25)) {
        /* Transition: '<S1>:18' */
        CellTempUnbalance_DW.is_F2 = CellTempUnbalance_IN_Wait2;
      } else {
        if (CellTempUnbalance_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:20' */
          CellTempUnbalance_DW.is_F2 = CellTempUnbalance_IN_Fault2;

          /* Entry 'Fault2': '<S1>:17' */
          CellTempUnbalance_B.F_lev = 2U;
        }
      }
      break;

     case CellTempUnbalance_IN_Delay21:
      /* During 'Delay21': '<S1>:118' */
      if (!(Tmax - Tmin < 18)) {
        /* Transition: '<S1>:70' */
        CellTempUnbalance_DW.is_F2 = CellTempUnbalance_IN_Fault2;

        /* Entry 'Fault2': '<S1>:17' */
        CellTempUnbalance_B.F_lev = 2U;
      } else {
        if (CellTempUnbalance_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:69' */
          CellTempUnbalance_DW.is_F2 = CellTempUnbalance_IN_Fault20;

          /* Entry 'Fault20': '<S1>:153' */
          CellTempUnbalance_B.F_lev = 0U;
        }
      }
      break;

     case CellTempUnbalance_IN_Fault2:
      /* During 'Fault2': '<S1>:17' */
      if (Tmax - Tmin < 18) {
        /* Transition: '<S1>:72' */
        CellTempUnbalance_DW.is_F2 = CellTempUnbalance_IN_Delay21;
        CellTempUnbalance_DW.temporalCounter_i2 = 0U;
      }
      break;

     case CellTempUnbalance_IN_Fault20:
      /* During 'Fault20': '<S1>:153' */
      /* Transition: '<S1>:175' */
      CellTempUnbalance_DW.is_F2 = CellTempUnbalance_IN_Wait2;
      break;

     default:
      /* During 'Wait2': '<S1>:97' */
      if (Tmax - Tmin >= 25) {
        /* Transition: '<S1>:19' */
        CellTempUnbalance_DW.is_F2 = CellTempUnbalance_IN_Delay20;
        CellTempUnbalance_DW.temporalCounter_i2 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  arg_F_lev = CellTempUnbalance_B.F_lev;
  return arg_F_lev;
}

/* Model initialize function */
void CellTempUnbalance_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(CellTempUnbalance_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &CellTempUnbalance_B), 0,
                sizeof(B_CellTempUnbalance_T));

  /* states (dwork) */
  (void) memset((void *)&CellTempUnbalance_DW, 0,
                sizeof(DW_CellTempUnbalance_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  CellTempUnbalance_DW.is_F1 = CellTempUnba_IN_NO_ACTIVE_CHILD;
  CellTempUnbalance_DW.temporalCounter_i1 = 0U;
  CellTempUnbalance_DW.is_F2 = CellTempUnba_IN_NO_ACTIVE_CHILD;
  CellTempUnbalance_DW.temporalCounter_i2 = 0U;
  CellTempUnbalance_DW.is_active_c3_CellTempUnbalance = 0U;
  CellTempUnbalance_B.F_lev = 0U;
}

/* Model terminate function */
void CellTempUnbalance_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

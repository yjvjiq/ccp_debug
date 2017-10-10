/*
 * File: CellOverVoltage.c
 *
 * Code generated for Simulink model 'CellOverVoltage'.
 *
 * Model version                  : 1.119
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 16 15:58:04 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CellOverVoltage.h"
#include "CellOverVoltage_private.h"

/* Named constants for Chart: '<Root>/Logic' */
#define CellOverVolt_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define CellOverVoltage_IN_Delay10     ((uint8_T)1U)
#define CellOverVoltage_IN_Delay11     ((uint8_T)2U)
#define CellOverVoltage_IN_Delay20     ((uint8_T)1U)
#define CellOverVoltage_IN_Delay21     ((uint8_T)2U)
#define CellOverVoltage_IN_Delay30     ((uint8_T)1U)
#define CellOverVoltage_IN_Fault1      ((uint8_T)3U)
#define CellOverVoltage_IN_Fault10     ((uint8_T)4U)
#define CellOverVoltage_IN_Fault2      ((uint8_T)3U)
#define CellOverVoltage_IN_Fault20     ((uint8_T)4U)
#define CellOverVoltage_IN_Fault3      ((uint8_T)2U)
#define CellOverVoltage_IN_Wait1       ((uint8_T)5U)
#define CellOverVoltage_IN_Wait2       ((uint8_T)5U)
#define CellOverVoltage_IN_Wait3       ((uint8_T)3U)

/* Block signals (auto storage) */
B_CellOverVoltage_T CellOverVoltage_B;

/* Block states (auto storage) */
DW_CellOverVoltage_T CellOverVoltage_DW;

/* Real-time model */
RT_MODEL_CellOverVoltage_T CellOverVoltage_M_;
RT_MODEL_CellOverVoltage_T *const CellOverVoltage_M = &CellOverVoltage_M_;

/* Model step function */
uint8_T CellOverVoltage_custom(real32_T Vmax, uint8_T Modelflag)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Logic' incorporates:
   *  Inport: '<Root>/Modelflag'
   *  Inport: '<Root>/Vmax'
   */
  /* Gateway: Logic */
  if (CellOverVoltage_DW.temporalCounter_i1 < 15U) {
    CellOverVoltage_DW.temporalCounter_i1++;
  }

  if (CellOverVoltage_DW.temporalCounter_i2 < 15U) {
    CellOverVoltage_DW.temporalCounter_i2++;
  }

  if (CellOverVoltage_DW.temporalCounter_i3 < 15U) {
    CellOverVoltage_DW.temporalCounter_i3++;
  }

  /* During: Logic */
  if (CellOverVoltage_DW.is_active_c3_CellOverVoltage == 0U) {
    /* Entry: Logic */
    CellOverVoltage_DW.is_active_c3_CellOverVoltage = 1U;

    /* Entry Internal: Logic */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F1': '<S1>:184' */
    /* Transition: '<S1>:182' */
    CellOverVoltage_DW.is_F1 = CellOverVoltage_IN_Wait1;

    /* Entry Internal 'F2': '<S1>:202' */
    /* Transition: '<S1>:210' */
    CellOverVoltage_DW.is_F2 = CellOverVoltage_IN_Wait2;

    /* Entry Internal 'F3': '<S1>:102' */
    /* Transition: '<S1>:108' */
    CellOverVoltage_DW.is_F3 = CellOverVoltage_IN_Wait3;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F1': '<S1>:184' */
    switch (CellOverVoltage_DW.is_F1) {
     case CellOverVoltage_IN_Delay10:
      /* During 'Delay10': '<S1>:192' */
      if (!(Vmax > 3.65F)) {
        /* Transition: '<S1>:185' */
        CellOverVoltage_DW.is_F1 = CellOverVoltage_IN_Wait1;
      } else {
        if (CellOverVoltage_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:183' */
          CellOverVoltage_DW.is_F1 = CellOverVoltage_IN_Fault1;

          /* Entry 'Fault1': '<S1>:190' */
          CellOverVoltage_B.F_lev_i = 1U;
        }
      }
      break;

     case CellOverVoltage_IN_Delay11:
      /* During 'Delay11': '<S1>:188' */
      if (!((Vmax <= 3.6F) && (Modelflag == 0))) {
        /* Transition: '<S1>:191' */
        CellOverVoltage_DW.is_F1 = CellOverVoltage_IN_Fault1;

        /* Entry 'Fault1': '<S1>:190' */
        CellOverVoltage_B.F_lev_i = 1U;
      } else {
        if (CellOverVoltage_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:181' */
          CellOverVoltage_DW.is_F1 = CellOverVoltage_IN_Fault10;

          /* Entry 'Fault10': '<S1>:187' */
          CellOverVoltage_B.F_lev_i = 0U;
        }
      }
      break;

     case CellOverVoltage_IN_Fault1:
      /* During 'Fault1': '<S1>:190' */
      if ((Vmax <= 3.6F) && (Modelflag == 0)) {
        /* Transition: '<S1>:189' */
        CellOverVoltage_DW.is_F1 = CellOverVoltage_IN_Delay11;
        CellOverVoltage_DW.temporalCounter_i1 = 0U;
      }
      break;

     case CellOverVoltage_IN_Fault10:
      /* During 'Fault10': '<S1>:187' */
      /* Transition: '<S1>:193' */
      CellOverVoltage_DW.is_F1 = CellOverVoltage_IN_Wait1;
      break;

     default:
      /* During 'Wait1': '<S1>:186' */
      if (Vmax > 3.65F) {
        /* Transition: '<S1>:194' */
        CellOverVoltage_DW.is_F1 = CellOverVoltage_IN_Delay10;
        CellOverVoltage_DW.temporalCounter_i1 = 0U;
      }
      break;
    }

    /* During 'F2': '<S1>:202' */
    switch (CellOverVoltage_DW.is_F2) {
     case CellOverVoltage_IN_Delay20:
      /* During 'Delay20': '<S1>:207' */
      if (!(Vmax > 3.75F)) {
        /* Transition: '<S1>:198' */
        CellOverVoltage_DW.is_F2 = CellOverVoltage_IN_Wait2;
      } else {
        if (CellOverVoltage_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:209' */
          CellOverVoltage_DW.is_F2 = CellOverVoltage_IN_Fault2;

          /* Entry 'Fault2': '<S1>:200' */
          CellOverVoltage_B.F_lev_i = 2U;
        }
      }
      break;

     case CellOverVoltage_IN_Delay21:
      /* During 'Delay21': '<S1>:203' */
      if (!((Vmax <= 3.65F) && (Modelflag == 0))) {
        /* Transition: '<S1>:199' */
        CellOverVoltage_DW.is_F2 = CellOverVoltage_IN_Fault2;

        /* Entry 'Fault2': '<S1>:200' */
        CellOverVoltage_B.F_lev_i = 2U;
      } else {
        if (CellOverVoltage_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:206' */
          CellOverVoltage_DW.is_F2 = CellOverVoltage_IN_Fault20;

          /* Entry 'Fault20': '<S1>:204' */
          CellOverVoltage_B.F_lev_i = 0U;
        }
      }
      break;

     case CellOverVoltage_IN_Fault2:
      /* During 'Fault2': '<S1>:200' */
      if ((Vmax <= 3.65F) && (Modelflag == 0)) {
        /* Transition: '<S1>:205' */
        CellOverVoltage_DW.is_F2 = CellOverVoltage_IN_Delay21;
        CellOverVoltage_DW.temporalCounter_i2 = 0U;
      }
      break;

     case CellOverVoltage_IN_Fault20:
      /* During 'Fault20': '<S1>:204' */
      /* Transition: '<S1>:208' */
      CellOverVoltage_DW.is_F2 = CellOverVoltage_IN_Wait2;
      break;

     default:
      /* During 'Wait2': '<S1>:201' */
      if (Vmax > 3.75F) {
        /* Transition: '<S1>:211' */
        CellOverVoltage_DW.is_F2 = CellOverVoltage_IN_Delay20;
        CellOverVoltage_DW.temporalCounter_i2 = 0U;
      }
      break;
    }

    /* During 'F3': '<S1>:102' */
    switch (CellOverVoltage_DW.is_F3) {
     case CellOverVoltage_IN_Delay30:
      /* During 'Delay30': '<S1>:28' */
      if (!(Vmax > 3.8F)) {
        /* Transition: '<S1>:24' */
        CellOverVoltage_DW.is_F3 = CellOverVoltage_IN_Wait3;
      } else {
        if (CellOverVoltage_DW.temporalCounter_i3 >= 10) {
          /* Transition: '<S1>:26' */
          CellOverVoltage_DW.is_F3 = CellOverVoltage_IN_Fault3;

          /* Entry 'Fault3': '<S1>:23' */
          CellOverVoltage_B.F_lev_i = 3U;
        }
      }
      break;

     case CellOverVoltage_IN_Fault3:
      /* During 'Fault3': '<S1>:23' */
      CellOverVoltage_B.F_lev_i = 3U;
      break;

     default:
      /* During 'Wait3': '<S1>:98' */
      if (Vmax > 3.8F) {
        /* Transition: '<S1>:25' */
        CellOverVoltage_DW.is_F3 = CellOverVoltage_IN_Delay30;
        CellOverVoltage_DW.temporalCounter_i3 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Logic' */

  /* Outport: '<Root>/F_lev' */
  F_lev = CellOverVoltage_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void CellOverVoltage_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(CellOverVoltage_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &CellOverVoltage_B), 0,
                sizeof(B_CellOverVoltage_T));

  /* states (dwork) */
  (void) memset((void *)&CellOverVoltage_DW, 0,
                sizeof(DW_CellOverVoltage_T));

  /* SystemInitialize for Chart: '<Root>/Logic' */
  CellOverVoltage_DW.is_F1 = CellOverVolt_IN_NO_ACTIVE_CHILD;
  CellOverVoltage_DW.temporalCounter_i1 = 0U;
  CellOverVoltage_DW.is_F2 = CellOverVolt_IN_NO_ACTIVE_CHILD;
  CellOverVoltage_DW.temporalCounter_i2 = 0U;
  CellOverVoltage_DW.is_F3 = CellOverVolt_IN_NO_ACTIVE_CHILD;
  CellOverVoltage_DW.temporalCounter_i3 = 0U;
  CellOverVoltage_DW.is_active_c3_CellOverVoltage = 0U;
  CellOverVoltage_B.F_lev_i = 0U;
}

/* Model terminate function */
void CellOverVoltage_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

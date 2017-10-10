/*
 * File: CellUnderVoltage.c
 *
 * Code generated for Simulink model 'CellUnderVoltage'.
 *
 * Model version                  : 1.120
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 16 15:57:43 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CellUnderVoltage.h"
#include "CellUnderVoltage_private.h"

/* Named constants for Chart: '<Root>/Logic' */
#define CellUnderVol_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define CellUnderVoltage_IN_Delay10    ((uint8_T)1U)
#define CellUnderVoltage_IN_Delay11    ((uint8_T)2U)
#define CellUnderVoltage_IN_Delay20    ((uint8_T)1U)
#define CellUnderVoltage_IN_Delay21    ((uint8_T)2U)
#define CellUnderVoltage_IN_Delay30    ((uint8_T)1U)
#define CellUnderVoltage_IN_Fault1     ((uint8_T)3U)
#define CellUnderVoltage_IN_Fault10    ((uint8_T)4U)
#define CellUnderVoltage_IN_Fault2     ((uint8_T)3U)
#define CellUnderVoltage_IN_Fault20    ((uint8_T)4U)
#define CellUnderVoltage_IN_Fault3     ((uint8_T)2U)
#define CellUnderVoltage_IN_Wait1      ((uint8_T)5U)
#define CellUnderVoltage_IN_Wait2      ((uint8_T)5U)
#define CellUnderVoltage_IN_Wait3      ((uint8_T)3U)

/* Block signals (auto storage) */
B_CellUnderVoltage_T CellUnderVoltage_B;

/* Block states (auto storage) */
DW_CellUnderVoltage_T CellUnderVoltage_DW;

/* Real-time model */
RT_MODEL_CellUnderVoltage_T CellUnderVoltage_M_;
RT_MODEL_CellUnderVoltage_T *const CellUnderVoltage_M = &CellUnderVoltage_M_;

/* Model step function */
uint8_T CellUnderVoltage_custom(real32_T Vmin)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Logic' incorporates:
   *  Inport: '<Root>/Vmin'
   */
  /* Gateway: Logic */
  if (CellUnderVoltage_DW.temporalCounter_i1 < 15U) {
    CellUnderVoltage_DW.temporalCounter_i1++;
  }

  if (CellUnderVoltage_DW.temporalCounter_i2 < 15U) {
    CellUnderVoltage_DW.temporalCounter_i2++;
  }

  if (CellUnderVoltage_DW.temporalCounter_i3 < 15U) {
    CellUnderVoltage_DW.temporalCounter_i3++;
  }

  /* During: Logic */
  if (CellUnderVoltage_DW.is_active_c3_CellUnderVoltage == 0U) {
    /* Entry: Logic */
    CellUnderVoltage_DW.is_active_c3_CellUnderVoltage = 1U;

    /* Entry Internal: Logic */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F1': '<S1>:184' */
    /* Transition: '<S1>:182' */
    CellUnderVoltage_DW.is_F1 = CellUnderVoltage_IN_Wait1;

    /* Entry Internal 'F2': '<S1>:202' */
    /* Transition: '<S1>:210' */
    CellUnderVoltage_DW.is_F2 = CellUnderVoltage_IN_Wait2;

    /* Entry Internal 'F3': '<S1>:102' */
    /* Transition: '<S1>:108' */
    CellUnderVoltage_DW.is_F3 = CellUnderVoltage_IN_Wait3;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F1': '<S1>:184' */
    switch (CellUnderVoltage_DW.is_F1) {
     case CellUnderVoltage_IN_Delay10:
      /* During 'Delay10': '<S1>:192' */
      if (!(Vmin < 2.8F)) {
        /* Transition: '<S1>:185' */
        CellUnderVoltage_DW.is_F1 = CellUnderVoltage_IN_Wait1;
      } else {
        if (CellUnderVoltage_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:183' */
          CellUnderVoltage_DW.is_F1 = CellUnderVoltage_IN_Fault1;

          /* Entry 'Fault1': '<S1>:190' */
          CellUnderVoltage_B.F_lev_i = 1U;
        }
      }
      break;

     case CellUnderVoltage_IN_Delay11:
      /* During 'Delay11': '<S1>:188' */
      if (!(Vmin >= 2.9F)) {
        /* Transition: '<S1>:191' */
        CellUnderVoltage_DW.is_F1 = CellUnderVoltage_IN_Fault1;

        /* Entry 'Fault1': '<S1>:190' */
        CellUnderVoltage_B.F_lev_i = 1U;
      } else {
        if (CellUnderVoltage_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:181' */
          CellUnderVoltage_DW.is_F1 = CellUnderVoltage_IN_Fault10;

          /* Entry 'Fault10': '<S1>:187' */
          CellUnderVoltage_B.F_lev_i = 0U;
        }
      }
      break;

     case CellUnderVoltage_IN_Fault1:
      /* During 'Fault1': '<S1>:190' */
      if (Vmin >= 2.9F) {
        /* Transition: '<S1>:189' */
        CellUnderVoltage_DW.is_F1 = CellUnderVoltage_IN_Delay11;
        CellUnderVoltage_DW.temporalCounter_i1 = 0U;
      }
      break;

     case CellUnderVoltage_IN_Fault10:
      /* During 'Fault10': '<S1>:187' */
      /* Transition: '<S1>:193' */
      CellUnderVoltage_DW.is_F1 = CellUnderVoltage_IN_Wait1;
      break;

     default:
      /* During 'Wait1': '<S1>:186' */
      if (Vmin < 2.8F) {
        /* Transition: '<S1>:194' */
        CellUnderVoltage_DW.is_F1 = CellUnderVoltage_IN_Delay10;
        CellUnderVoltage_DW.temporalCounter_i1 = 0U;
      }
      break;
    }

    /* During 'F2': '<S1>:202' */
    switch (CellUnderVoltage_DW.is_F2) {
     case CellUnderVoltage_IN_Delay20:
      /* During 'Delay20': '<S1>:207' */
      if (!(Vmin < 2.7F)) {
        /* Transition: '<S1>:198' */
        CellUnderVoltage_DW.is_F2 = CellUnderVoltage_IN_Wait2;
      } else {
        if (CellUnderVoltage_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:209' */
          CellUnderVoltage_DW.is_F2 = CellUnderVoltage_IN_Fault2;

          /* Entry 'Fault2': '<S1>:200' */
          CellUnderVoltage_B.F_lev_i = 2U;
        }
      }
      break;

     case CellUnderVoltage_IN_Delay21:
      /* During 'Delay21': '<S1>:203' */
      if (!(Vmin >= 2.8F)) {
        /* Transition: '<S1>:199' */
        CellUnderVoltage_DW.is_F2 = CellUnderVoltage_IN_Fault2;

        /* Entry 'Fault2': '<S1>:200' */
        CellUnderVoltage_B.F_lev_i = 2U;
      } else {
        if (CellUnderVoltage_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:206' */
          CellUnderVoltage_DW.is_F2 = CellUnderVoltage_IN_Fault20;

          /* Entry 'Fault20': '<S1>:204' */
          CellUnderVoltage_B.F_lev_i = 0U;
        }
      }
      break;

     case CellUnderVoltage_IN_Fault2:
      /* During 'Fault2': '<S1>:200' */
      if (Vmin >= 2.8F) {
        /* Transition: '<S1>:205' */
        CellUnderVoltage_DW.is_F2 = CellUnderVoltage_IN_Delay21;
        CellUnderVoltage_DW.temporalCounter_i2 = 0U;
      }
      break;

     case CellUnderVoltage_IN_Fault20:
      /* During 'Fault20': '<S1>:204' */
      /* Transition: '<S1>:208' */
      CellUnderVoltage_DW.is_F2 = CellUnderVoltage_IN_Wait2;
      break;

     default:
      /* During 'Wait2': '<S1>:201' */
      if (Vmin < 2.7F) {
        /* Transition: '<S1>:211' */
        CellUnderVoltage_DW.is_F2 = CellUnderVoltage_IN_Delay20;
        CellUnderVoltage_DW.temporalCounter_i2 = 0U;
      }
      break;
    }

    /* During 'F3': '<S1>:102' */
    switch (CellUnderVoltage_DW.is_F3) {
     case CellUnderVoltage_IN_Delay30:
      /* During 'Delay30': '<S1>:28' */
      if (!(Vmin < 2.6F)) {
        /* Transition: '<S1>:24' */
        CellUnderVoltage_DW.is_F3 = CellUnderVoltage_IN_Wait3;
      } else {
        if (CellUnderVoltage_DW.temporalCounter_i3 >= 10) {
          /* Transition: '<S1>:26' */
          CellUnderVoltage_DW.is_F3 = CellUnderVoltage_IN_Fault3;

          /* Entry 'Fault3': '<S1>:23' */
          CellUnderVoltage_B.F_lev_i = 3U;
        }
      }
      break;

     case CellUnderVoltage_IN_Fault3:
      /* During 'Fault3': '<S1>:23' */
      CellUnderVoltage_B.F_lev_i = 3U;
      break;

     default:
      /* During 'Wait3': '<S1>:98' */
      if (Vmin < 2.6F) {
        /* Transition: '<S1>:25' */
        CellUnderVoltage_DW.is_F3 = CellUnderVoltage_IN_Delay30;
        CellUnderVoltage_DW.temporalCounter_i3 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Logic' */

  /* Outport: '<Root>/F_lev' */
  F_lev = CellUnderVoltage_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void CellUnderVoltage_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(CellUnderVoltage_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &CellUnderVoltage_B), 0,
                sizeof(B_CellUnderVoltage_T));

  /* states (dwork) */
  (void) memset((void *)&CellUnderVoltage_DW, 0,
                sizeof(DW_CellUnderVoltage_T));

  /* SystemInitialize for Chart: '<Root>/Logic' */
  CellUnderVoltage_DW.is_F1 = CellUnderVol_IN_NO_ACTIVE_CHILD;
  CellUnderVoltage_DW.temporalCounter_i1 = 0U;
  CellUnderVoltage_DW.is_F2 = CellUnderVol_IN_NO_ACTIVE_CHILD;
  CellUnderVoltage_DW.temporalCounter_i2 = 0U;
  CellUnderVoltage_DW.is_F3 = CellUnderVol_IN_NO_ACTIVE_CHILD;
  CellUnderVoltage_DW.temporalCounter_i3 = 0U;
  CellUnderVoltage_DW.is_active_c3_CellUnderVoltage = 0U;
  CellUnderVoltage_B.F_lev_i = 0U;
}

/* Model terminate function */
void CellUnderVoltage_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

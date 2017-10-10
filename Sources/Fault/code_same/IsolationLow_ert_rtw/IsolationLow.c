/*
 * File: IsolationLow.c
 *
 * Code generated for Simulink model 'IsolationLow'.
 *
 * Model version                  : 1.125
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Mon Jul 24 09:32:30 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "IsolationLow.h"
#include "IsolationLow_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define IsolationLow_IN_Delay10        ((uint8_T)1U)
#define IsolationLow_IN_Delay11        ((uint8_T)2U)
#define IsolationLow_IN_Delay20        ((uint8_T)1U)
#define IsolationLow_IN_Delay21        ((uint8_T)2U)
#define IsolationLow_IN_Delay22        ((uint8_T)3U)
#define IsolationLow_IN_Delay30        ((uint8_T)1U)
#define IsolationLow_IN_Fault1         ((uint8_T)3U)
#define IsolationLow_IN_Fault10        ((uint8_T)4U)
#define IsolationLow_IN_Fault2         ((uint8_T)4U)
#define IsolationLow_IN_Fault21        ((uint8_T)5U)
#define IsolationLow_IN_Fault22        ((uint8_T)6U)
#define IsolationLow_IN_Fault3         ((uint8_T)2U)
#define IsolationLow_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define IsolationLow_IN_Wait1          ((uint8_T)5U)
#define IsolationLow_IN_Wait2          ((uint8_T)7U)
#define IsolationLow_IN_Wait3          ((uint8_T)3U)

/* Block signals (auto storage) */
B_IsolationLow_T IsolationLow_B;

/* Block states (auto storage) */
DW_IsolationLow_T IsolationLow_DW;

/* Real-time model */
RT_MODEL_IsolationLow_T IsolationLow_M_;
RT_MODEL_IsolationLow_T *const IsolationLow_M = &IsolationLow_M_;

/* Model step function */
uint8_T IsolationLow_custom(real32_T Res)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/Res'
   */
  /* Gateway: Chart */
  if (IsolationLow_DW.temporalCounter_i1 < 31U) {
    IsolationLow_DW.temporalCounter_i1++;
  }

  if (IsolationLow_DW.temporalCounter_i2 < 31U) {
    IsolationLow_DW.temporalCounter_i2++;
  }

  if (IsolationLow_DW.temporalCounter_i3 < 31U) {
    IsolationLow_DW.temporalCounter_i3++;
  }

  /* During: Chart */
  if (IsolationLow_DW.is_active_c3_IsolationLow == 0U) {
    /* Entry: Chart */
    IsolationLow_DW.is_active_c3_IsolationLow = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F1': '<S1>:202' */
    /* Transition: '<S1>:197' */
    IsolationLow_DW.is_F1 = IsolationLow_IN_Wait1;

    /* Entry Internal 'F2': '<S1>:101' */
    /* Transition: '<S1>:173' */
    IsolationLow_DW.is_F2 = IsolationLow_IN_Wait2;

    /* Entry Internal 'F3': '<S1>:181' */
    /* Transition: '<S1>:185' */
    IsolationLow_DW.is_F3 = IsolationLow_IN_Wait3;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F1': '<S1>:202' */
    switch (IsolationLow_DW.is_F1) {
     case IsolationLow_IN_Delay10:
      /* During 'Delay10': '<S1>:209' */
      if (!(Res * 1000.0F <= 326400.0F)) {
        /* Transition: '<S1>:208' */
        IsolationLow_DW.is_F1 = IsolationLow_IN_Wait1;
      } else {
        if (IsolationLow_DW.temporalCounter_i1 >= 30) {
          /* Transition: '<S1>:203' */
          IsolationLow_DW.is_F1 = IsolationLow_IN_Fault1;

          /* Entry 'Fault1': '<S1>:200' */
          IsolationLow_B.F_lev_i = 1U;
        }
      }
      break;

     case IsolationLow_IN_Delay11:
      /* During 'Delay11': '<S1>:199' */
      if (!(Res * 1000.0F > 326400.0F)) {
        /* Transition: '<S1>:205' */
        IsolationLow_DW.is_F1 = IsolationLow_IN_Fault1;

        /* Entry 'Fault1': '<S1>:200' */
        IsolationLow_B.F_lev_i = 1U;
      } else {
        if (IsolationLow_DW.temporalCounter_i1 >= 30) {
          /* Transition: '<S1>:207' */
          IsolationLow_DW.is_F1 = IsolationLow_IN_Fault10;

          /* Entry 'Fault10': '<S1>:198' */
          IsolationLow_B.F_lev_i = 0U;
        }
      }
      break;

     case IsolationLow_IN_Fault1:
      /* During 'Fault1': '<S1>:200' */
      if (Res * 1000.0F > 326400.0F) {
        /* Transition: '<S1>:201' */
        IsolationLow_DW.is_F1 = IsolationLow_IN_Delay11;
        IsolationLow_DW.temporalCounter_i1 = 0U;
      }
      break;

     case IsolationLow_IN_Fault10:
      /* During 'Fault10': '<S1>:198' */
      /* Transition: '<S1>:196' */
      IsolationLow_DW.is_F1 = IsolationLow_IN_Wait1;
      break;

     default:
      /* During 'Wait1': '<S1>:204' */
      if (Res * 1000.0F <= 326400.0F) {
        /* Transition: '<S1>:206' */
        IsolationLow_DW.is_F1 = IsolationLow_IN_Delay10;
        IsolationLow_DW.temporalCounter_i1 = 0U;
      }
      break;
    }

    /* During 'F2': '<S1>:101' */
    switch (IsolationLow_DW.is_F2) {
     case IsolationLow_IN_Delay20:
      /* During 'Delay20': '<S1>:22' */
      if (!(Res * 1000.0F <= 65280.0F)) {
        /* Transition: '<S1>:18' */
        IsolationLow_DW.is_F2 = IsolationLow_IN_Wait2;
      } else {
        if (IsolationLow_DW.temporalCounter_i2 >= 30) {
          /* Transition: '<S1>:20' */
          IsolationLow_DW.is_F2 = IsolationLow_IN_Fault2;

          /* Entry 'Fault2': '<S1>:17' */
          IsolationLow_B.F_lev_i = 2U;
        }
      }
      break;

     case IsolationLow_IN_Delay21:
      /* During 'Delay21': '<S1>:118' */
      if (IsolationLow_DW.temporalCounter_i2 >= 30) {
        /* Transition: '<S1>:69' */
        IsolationLow_DW.is_F2 = IsolationLow_IN_Fault22;

        /* Entry 'Fault22': '<S1>:223' */
        IsolationLow_B.F_lev_i = 1U;
      } else {
        if (!(Res * 1000.0F > 65280.0F)) {
          /* Transition: '<S1>:70' */
          IsolationLow_DW.is_F2 = IsolationLow_IN_Fault2;

          /* Entry 'Fault2': '<S1>:17' */
          IsolationLow_B.F_lev_i = 2U;
        }
      }
      break;

     case IsolationLow_IN_Delay22:
      /* During 'Delay22': '<S1>:213' */
      if (!(Res * 1000.0F > 326400.0F)) {
        /* Transition: '<S1>:217' */
        IsolationLow_DW.is_F2 = IsolationLow_IN_Fault2;

        /* Entry 'Fault2': '<S1>:17' */
        IsolationLow_B.F_lev_i = 2U;
      } else {
        if (IsolationLow_DW.temporalCounter_i2 >= 30) {
          /* Transition: '<S1>:215' */
          IsolationLow_DW.is_F2 = IsolationLow_IN_Fault21;

          /* Entry 'Fault21': '<S1>:214' */
          IsolationLow_B.F_lev_i = 0U;
        }
      }
      break;

     case IsolationLow_IN_Fault2:
      /* During 'Fault2': '<S1>:17' */
      if (Res * 1000.0F > 326400.0F) {
        /* Transition: '<S1>:216' */
        IsolationLow_DW.is_F2 = IsolationLow_IN_Delay22;
        IsolationLow_DW.temporalCounter_i2 = 0U;
      } else {
        if (Res * 1000.0F > 65280.0F) {
          /* Transition: '<S1>:72' */
          IsolationLow_DW.is_F2 = IsolationLow_IN_Delay21;
          IsolationLow_DW.temporalCounter_i2 = 0U;
        }
      }
      break;

     case IsolationLow_IN_Fault21:
      /* During 'Fault21': '<S1>:214' */
      /* Transition: '<S1>:220' */
      IsolationLow_DW.is_F2 = IsolationLow_IN_Wait2;
      break;

     case IsolationLow_IN_Fault22:
      /* During 'Fault22': '<S1>:223' */
      /* Transition: '<S1>:224' */
      IsolationLow_DW.is_F2 = IsolationLow_IN_Wait2;
      break;

     default:
      /* During 'Wait2': '<S1>:97' */
      if (Res * 1000.0F <= 65280.0F) {
        /* Transition: '<S1>:19' */
        IsolationLow_DW.is_F2 = IsolationLow_IN_Delay20;
        IsolationLow_DW.temporalCounter_i2 = 0U;
      }
      break;
    }

    /* During 'F3': '<S1>:181' */
    switch (IsolationLow_DW.is_F3) {
     case IsolationLow_IN_Delay30:
      /* During 'Delay30': '<S1>:190' */
      if (!(Res * 1000.0F <= 32640.0F)) {
        /* Transition: '<S1>:184' */
        IsolationLow_DW.is_F3 = IsolationLow_IN_Wait3;
      } else {
        if (IsolationLow_DW.temporalCounter_i3 >= 30) {
          /* Transition: '<S1>:194' */
          IsolationLow_DW.is_F3 = IsolationLow_IN_Fault3;

          /* Entry 'Fault3': '<S1>:188' */
          IsolationLow_B.F_lev_i = 3U;
        }
      }
      break;

     case IsolationLow_IN_Fault3:
      /* During 'Fault3': '<S1>:188' */
      IsolationLow_B.F_lev_i = 3U;
      break;

     default:
      /* During 'Wait3': '<S1>:187' */
      if (Res * 1000.0F <= 32640.0F) {
        /* Transition: '<S1>:186' */
        IsolationLow_DW.is_F3 = IsolationLow_IN_Delay30;
        IsolationLow_DW.temporalCounter_i3 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = IsolationLow_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void IsolationLow_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(IsolationLow_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &IsolationLow_B), 0,
                sizeof(B_IsolationLow_T));

  /* states (dwork) */
  (void) memset((void *)&IsolationLow_DW, 0,
                sizeof(DW_IsolationLow_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  IsolationLow_DW.is_F1 = IsolationLow_IN_NO_ACTIVE_CHILD;
  IsolationLow_DW.temporalCounter_i1 = 0U;
  IsolationLow_DW.is_F2 = IsolationLow_IN_NO_ACTIVE_CHILD;
  IsolationLow_DW.temporalCounter_i2 = 0U;
  IsolationLow_DW.is_F3 = IsolationLow_IN_NO_ACTIVE_CHILD;
  IsolationLow_DW.temporalCounter_i3 = 0U;
  IsolationLow_DW.is_active_c3_IsolationLow = 0U;
  IsolationLow_B.F_lev_i = 0U;
}

/* Model terminate function */
void IsolationLow_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

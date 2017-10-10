/*
 * File: TotalVoltageUnderVoltage.c
 *
 * Code generated for Simulink model 'TotalVoltageUnderVoltage'.
 *
 * Model version                  : 1.97
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 23 11:00:57 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TotalVoltageUnderVoltage.h"
#include "TotalVoltageUnderVoltage_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define TotalVoltageUnderVol_IN_Delay10 ((uint8_T)1U)
#define TotalVoltageUnderVol_IN_Delay11 ((uint8_T)2U)
#define TotalVoltageUnderVol_IN_Delay20 ((uint8_T)1U)
#define TotalVoltageUnderVol_IN_Delay21 ((uint8_T)2U)
#define TotalVoltageUnderVol_IN_Delay30 ((uint8_T)1U)
#define TotalVoltageUnderVol_IN_Fault10 ((uint8_T)4U)
#define TotalVoltageUnderVol_IN_Fault20 ((uint8_T)4U)
#define TotalVoltageUnderVolt_IN_Fault1 ((uint8_T)3U)
#define TotalVoltageUnderVolt_IN_Fault2 ((uint8_T)3U)
#define TotalVoltageUnderVolt_IN_Fault3 ((uint8_T)2U)
#define TotalVoltageUnderVolta_IN_Wait1 ((uint8_T)5U)
#define TotalVoltageUnderVolta_IN_Wait2 ((uint8_T)5U)
#define TotalVoltageUnderVolta_IN_Wait3 ((uint8_T)3U)
#define TotalVoltage_IN_NO_ACTIVE_CHILD ((uint8_T)0U)

/* Block signals (auto storage) */
B_TotalVoltageUnderVoltage_T TotalVoltageUnderVoltage_B;

/* Block states (auto storage) */
DW_TotalVoltageUnderVoltage_T TotalVoltageUnderVoltage_DW;

/* Real-time model */
RT_MODEL_TotalVoltageUnderVol_T TotalVoltageUnderVoltage_M_;
RT_MODEL_TotalVoltageUnderVol_T *const TotalVoltageUnderVoltage_M =
  &TotalVoltageUnderVoltage_M_;

/* Model step function */
uint8_T TotalVoltageUnderVoltage_custom(real32_T V0, real32_T V3)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/V0'
   *  Inport: '<Root>/V3'
   */
  /* Gateway: Chart */
  if (TotalVoltageUnderVoltage_DW.temporalCounter_i1 < 15U) {
    TotalVoltageUnderVoltage_DW.temporalCounter_i1++;
  }

  if (TotalVoltageUnderVoltage_DW.temporalCounter_i2 < 15U) {
    TotalVoltageUnderVoltage_DW.temporalCounter_i2++;
  }

  if (TotalVoltageUnderVoltage_DW.temporalCounter_i3 < 15U) {
    TotalVoltageUnderVoltage_DW.temporalCounter_i3++;
  }

  /* During: Chart */
  if (TotalVoltageUnderVoltage_DW.is_active_c3_TotalVoltageUnderV == 0U) {
    /* Entry: Chart */
    TotalVoltageUnderVoltage_DW.is_active_c3_TotalVoltageUnderV = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F1': '<S1>:192' */
    /* Transition: '<S1>:191' */
    TotalVoltageUnderVoltage_DW.is_F1 = TotalVoltageUnderVolta_IN_Wait1;

    /* Entry Internal 'F2': '<S1>:101' */
    /* Transition: '<S1>:173' */
    TotalVoltageUnderVoltage_DW.is_F2 = TotalVoltageUnderVolta_IN_Wait2;

    /* Entry Internal 'F3': '<S1>:102' */
    /* Transition: '<S1>:108' */
    TotalVoltageUnderVoltage_DW.is_F3 = TotalVoltageUnderVolta_IN_Wait3;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F1': '<S1>:192' */
    switch (TotalVoltageUnderVoltage_DW.is_F1) {
     case TotalVoltageUnderVol_IN_Delay10:
      /* During 'Delay10': '<S1>:184' */
      if (!((V0 < 572.0F) && (V3 < 572.0F))) {
        /* Transition: '<S1>:187' */
        TotalVoltageUnderVoltage_DW.is_F1 = TotalVoltageUnderVolta_IN_Wait1;
      } else {
        if (TotalVoltageUnderVoltage_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:186' */
          TotalVoltageUnderVoltage_DW.is_F1 = TotalVoltageUnderVolt_IN_Fault1;

          /* Entry 'Fault1': '<S1>:182' */
          TotalVoltageUnderVoltage_B.F_lev_i = 1U;
        }
      }
      break;

     case TotalVoltageUnderVol_IN_Delay11:
      /* During 'Delay11': '<S1>:185' */
      if (!((V0 >= 612.0F) && (V3 >= 612.0F))) {
        /* Transition: '<S1>:181' */
        TotalVoltageUnderVoltage_DW.is_F1 = TotalVoltageUnderVolt_IN_Fault1;

        /* Entry 'Fault1': '<S1>:182' */
        TotalVoltageUnderVoltage_B.F_lev_i = 1U;
      } else {
        if (TotalVoltageUnderVoltage_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:183' */
          TotalVoltageUnderVoltage_DW.is_F1 = TotalVoltageUnderVol_IN_Fault10;

          /* Entry 'Fault10': '<S1>:194' */
          TotalVoltageUnderVoltage_B.F_lev_i = 0U;
        }
      }
      break;

     case TotalVoltageUnderVolt_IN_Fault1:
      /* During 'Fault1': '<S1>:182' */
      if ((V0 >= 612.0F) && (V3 >= 612.0F)) {
        /* Transition: '<S1>:193' */
        TotalVoltageUnderVoltage_DW.is_F1 = TotalVoltageUnderVol_IN_Delay11;
        TotalVoltageUnderVoltage_DW.temporalCounter_i1 = 0U;
      }
      break;

     case TotalVoltageUnderVol_IN_Fault10:
      /* During 'Fault10': '<S1>:194' */
      /* Transition: '<S1>:189' */
      TotalVoltageUnderVoltage_DW.is_F1 = TotalVoltageUnderVolta_IN_Wait1;
      break;

     default:
      /* During 'Wait1': '<S1>:190' */
      if ((V0 < 572.0F) && (V3 < 572.0F)) {
        /* Transition: '<S1>:188' */
        TotalVoltageUnderVoltage_DW.is_F1 = TotalVoltageUnderVol_IN_Delay10;
        TotalVoltageUnderVoltage_DW.temporalCounter_i1 = 0U;
      }
      break;
    }

    /* During 'F2': '<S1>:101' */
    switch (TotalVoltageUnderVoltage_DW.is_F2) {
     case TotalVoltageUnderVol_IN_Delay20:
      /* During 'Delay20': '<S1>:22' */
      if (!((V0 < 551.0F) && (V3 < 551.0F))) {
        /* Transition: '<S1>:18' */
        TotalVoltageUnderVoltage_DW.is_F2 = TotalVoltageUnderVolta_IN_Wait2;
      } else {
        if (TotalVoltageUnderVoltage_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:20' */
          TotalVoltageUnderVoltage_DW.is_F2 = TotalVoltageUnderVolt_IN_Fault2;

          /* Entry 'Fault2': '<S1>:17' */
          TotalVoltageUnderVoltage_B.F_lev_i = 2U;
        }
      }
      break;

     case TotalVoltageUnderVol_IN_Delay21:
      /* During 'Delay21': '<S1>:118' */
      if (!((V0 >= 572.0F) && (V3 >= 572.0F))) {
        /* Transition: '<S1>:70' */
        TotalVoltageUnderVoltage_DW.is_F2 = TotalVoltageUnderVolt_IN_Fault2;

        /* Entry 'Fault2': '<S1>:17' */
        TotalVoltageUnderVoltage_B.F_lev_i = 2U;
      } else {
        if (TotalVoltageUnderVoltage_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:69' */
          TotalVoltageUnderVoltage_DW.is_F2 = TotalVoltageUnderVol_IN_Fault20;

          /* Entry 'Fault20': '<S1>:153' */
          TotalVoltageUnderVoltage_B.F_lev_i = 0U;
        }
      }
      break;

     case TotalVoltageUnderVolt_IN_Fault2:
      /* During 'Fault2': '<S1>:17' */
      if ((V0 >= 572.0F) && (V3 >= 572.0F)) {
        /* Transition: '<S1>:72' */
        TotalVoltageUnderVoltage_DW.is_F2 = TotalVoltageUnderVol_IN_Delay21;
        TotalVoltageUnderVoltage_DW.temporalCounter_i2 = 0U;
      }
      break;

     case TotalVoltageUnderVol_IN_Fault20:
      /* During 'Fault20': '<S1>:153' */
      /* Transition: '<S1>:175' */
      TotalVoltageUnderVoltage_DW.is_F2 = TotalVoltageUnderVolta_IN_Wait2;
      break;

     default:
      /* During 'Wait2': '<S1>:97' */
      if ((V0 < 551.0F) && (V3 < 551.0F)) {
        /* Transition: '<S1>:19' */
        TotalVoltageUnderVoltage_DW.is_F2 = TotalVoltageUnderVol_IN_Delay20;
        TotalVoltageUnderVoltage_DW.temporalCounter_i2 = 0U;
      }
      break;
    }

    /* During 'F3': '<S1>:102' */
    switch (TotalVoltageUnderVoltage_DW.is_F3) {
     case TotalVoltageUnderVol_IN_Delay30:
      /* During 'Delay30': '<S1>:28' */
      if (!((V0 < 531.0F) && (V3 < 531.0F))) {
        /* Transition: '<S1>:24' */
        TotalVoltageUnderVoltage_DW.is_F3 = TotalVoltageUnderVolta_IN_Wait3;
      } else {
        if (TotalVoltageUnderVoltage_DW.temporalCounter_i3 >= 10) {
          /* Transition: '<S1>:26' */
          TotalVoltageUnderVoltage_DW.is_F3 = TotalVoltageUnderVolt_IN_Fault3;

          /* Entry 'Fault3': '<S1>:23' */
          TotalVoltageUnderVoltage_B.F_lev_i = 3U;
        }
      }
      break;

     case TotalVoltageUnderVolt_IN_Fault3:
      /* During 'Fault3': '<S1>:23' */
      TotalVoltageUnderVoltage_B.F_lev_i = 3U;
      break;

     default:
      /* During 'Wait3': '<S1>:98' */
      if ((V0 < 531.0F) && (V3 < 531.0F)) {
        /* Transition: '<S1>:25' */
        TotalVoltageUnderVoltage_DW.is_F3 = TotalVoltageUnderVol_IN_Delay30;
        TotalVoltageUnderVoltage_DW.temporalCounter_i3 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = TotalVoltageUnderVoltage_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void TotalVoltageUnderVoltage_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(TotalVoltageUnderVoltage_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &TotalVoltageUnderVoltage_B), 0,
                sizeof(B_TotalVoltageUnderVoltage_T));

  /* states (dwork) */
  (void) memset((void *)&TotalVoltageUnderVoltage_DW, 0,
                sizeof(DW_TotalVoltageUnderVoltage_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  TotalVoltageUnderVoltage_DW.is_F1 = TotalVoltage_IN_NO_ACTIVE_CHILD;
  TotalVoltageUnderVoltage_DW.temporalCounter_i1 = 0U;
  TotalVoltageUnderVoltage_DW.is_F2 = TotalVoltage_IN_NO_ACTIVE_CHILD;
  TotalVoltageUnderVoltage_DW.temporalCounter_i2 = 0U;
  TotalVoltageUnderVoltage_DW.is_F3 = TotalVoltage_IN_NO_ACTIVE_CHILD;
  TotalVoltageUnderVoltage_DW.temporalCounter_i3 = 0U;
  TotalVoltageUnderVoltage_DW.is_active_c3_TotalVoltageUnderV = 0U;
  TotalVoltageUnderVoltage_B.F_lev_i = 0U;
}

/* Model terminate function */
void TotalVoltageUnderVoltage_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

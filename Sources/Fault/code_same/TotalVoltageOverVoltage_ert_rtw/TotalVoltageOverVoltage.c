/*
 * File: TotalVoltageOverVoltage.c
 *
 * Code generated for Simulink model 'TotalVoltageOverVoltage'.
 *
 * Model version                  : 1.113
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue Aug 08 09:52:32 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TotalVoltageOverVoltage.h"
#include "TotalVoltageOverVoltage_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define TotalVoltageOverVolt_IN_Delay10 ((uint8_T)1U)
#define TotalVoltageOverVolt_IN_Delay11 ((uint8_T)2U)
#define TotalVoltageOverVolt_IN_Delay20 ((uint8_T)1U)
#define TotalVoltageOverVolt_IN_Delay21 ((uint8_T)2U)
#define TotalVoltageOverVolt_IN_Delay30 ((uint8_T)1U)
#define TotalVoltageOverVolt_IN_Delay31 ((uint8_T)2U)
#define TotalVoltageOverVolt_IN_Delay32 ((uint8_T)3U)
#define TotalVoltageOverVolt_IN_Fault10 ((uint8_T)4U)
#define TotalVoltageOverVolt_IN_Fault20 ((uint8_T)4U)
#define TotalVoltageOverVolt_IN_Fault30 ((uint8_T)5U)
#define TotalVoltageOverVolta_IN_Fault1 ((uint8_T)3U)
#define TotalVoltageOverVolta_IN_Fault2 ((uint8_T)3U)
#define TotalVoltageOverVolta_IN_Fault3 ((uint8_T)4U)
#define TotalVoltageOverVoltag_IN_Wait1 ((uint8_T)5U)
#define TotalVoltageOverVoltag_IN_Wait2 ((uint8_T)5U)
#define TotalVoltageOverVoltag_IN_Wait3 ((uint8_T)6U)
#define TotalVoltage_IN_NO_ACTIVE_CHILD ((uint8_T)0U)

/* Block signals (auto storage) */
B_TotalVoltageOverVoltage_T TotalVoltageOverVoltage_B;

/* Block states (auto storage) */
DW_TotalVoltageOverVoltage_T TotalVoltageOverVoltage_DW;

/* Real-time model */
RT_MODEL_TotalVoltageOverVolt_T TotalVoltageOverVoltage_M_;
RT_MODEL_TotalVoltageOverVolt_T *const TotalVoltageOverVoltage_M =
  &TotalVoltageOverVoltage_M_;

/* Model step function */
uint8_T TotalVoltageOverVoltage_custom(real32_T V0, real32_T V3, uint8_T
  ModelFlag)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/ModelFlag'
   *  Inport: '<Root>/V0'
   *  Inport: '<Root>/V3'
   */
  /* Gateway: Chart */
  if (TotalVoltageOverVoltage_DW.temporalCounter_i1 < 15U) {
    TotalVoltageOverVoltage_DW.temporalCounter_i1++;
  }

  if (TotalVoltageOverVoltage_DW.temporalCounter_i2 < 15U) {
    TotalVoltageOverVoltage_DW.temporalCounter_i2++;
  }

  if (TotalVoltageOverVoltage_DW.temporalCounter_i3 < 15U) {
    TotalVoltageOverVoltage_DW.temporalCounter_i3++;
  }

  /* During: Chart */
  if (TotalVoltageOverVoltage_DW.is_active_c3_TotalVoltageOverVo == 0U) {
    /* Entry: Chart */
    TotalVoltageOverVoltage_DW.is_active_c3_TotalVoltageOverVo = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F1': '<S1>:192' */
    /* Transition: '<S1>:191' */
    TotalVoltageOverVoltage_DW.is_F1 = TotalVoltageOverVoltag_IN_Wait1;

    /* Entry Internal 'F2': '<S1>:101' */
    /* Transition: '<S1>:173' */
    TotalVoltageOverVoltage_DW.is_F2 = TotalVoltageOverVoltag_IN_Wait2;

    /* Entry Internal 'F3': '<S1>:102' */
    /* Transition: '<S1>:108' */
    TotalVoltageOverVoltage_DW.is_F3 = TotalVoltageOverVoltag_IN_Wait3;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F1': '<S1>:192' */
    switch (TotalVoltageOverVoltage_DW.is_F1) {
     case TotalVoltageOverVolt_IN_Delay10:
      /* During 'Delay10': '<S1>:184' */
      if (!((V0 >= 744.0F) || (V3 >= 744.0F))) {
        /* Transition: '<S1>:187' */
        TotalVoltageOverVoltage_DW.is_F1 = TotalVoltageOverVoltag_IN_Wait1;
      } else {
        if (TotalVoltageOverVoltage_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:186' */
          TotalVoltageOverVoltage_DW.is_F1 = TotalVoltageOverVolta_IN_Fault1;

          /* Entry 'Fault1': '<S1>:182' */
          TotalVoltageOverVoltage_B.F_lev_i = 1U;
        }
      }
      break;

     case TotalVoltageOverVolt_IN_Delay11:
      /* During 'Delay11': '<S1>:185' */
      if (!((V0 < 734.0F) && (V3 < 734.0F) && (ModelFlag == 0))) {
        /* Transition: '<S1>:181' */
        TotalVoltageOverVoltage_DW.is_F1 = TotalVoltageOverVolta_IN_Fault1;

        /* Entry 'Fault1': '<S1>:182' */
        TotalVoltageOverVoltage_B.F_lev_i = 1U;
      } else {
        if (TotalVoltageOverVoltage_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:183' */
          TotalVoltageOverVoltage_DW.is_F1 = TotalVoltageOverVolt_IN_Fault10;

          /* Entry 'Fault10': '<S1>:194' */
          TotalVoltageOverVoltage_B.F_lev_i = 0U;
        }
      }
      break;

     case TotalVoltageOverVolta_IN_Fault1:
      /* During 'Fault1': '<S1>:182' */
      if ((V0 < 734.0F) && (V3 < 734.0F) && (ModelFlag == 0)) {
        /* Transition: '<S1>:193' */
        TotalVoltageOverVoltage_DW.is_F1 = TotalVoltageOverVolt_IN_Delay11;
        TotalVoltageOverVoltage_DW.temporalCounter_i1 = 0U;
      }
      break;

     case TotalVoltageOverVolt_IN_Fault10:
      /* During 'Fault10': '<S1>:194' */
      /* Transition: '<S1>:189' */
      TotalVoltageOverVoltage_DW.is_F1 = TotalVoltageOverVoltag_IN_Wait1;
      break;

     default:
      /* During 'Wait1': '<S1>:190' */
      if ((V0 >= 744.0F) || (V3 >= 744.0F)) {
        /* Transition: '<S1>:188' */
        TotalVoltageOverVoltage_DW.is_F1 = TotalVoltageOverVolt_IN_Delay10;
        TotalVoltageOverVoltage_DW.temporalCounter_i1 = 0U;
      }
      break;
    }

    /* During 'F2': '<S1>:101' */
    switch (TotalVoltageOverVoltage_DW.is_F2) {
     case TotalVoltageOverVolt_IN_Delay20:
      /* During 'Delay20': '<S1>:22' */
      if (!((V0 >= 754.0F) || (V3 >= 754.0F))) {
        /* Transition: '<S1>:18' */
        TotalVoltageOverVoltage_DW.is_F2 = TotalVoltageOverVoltag_IN_Wait2;
      } else {
        if (TotalVoltageOverVoltage_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:20' */
          TotalVoltageOverVoltage_DW.is_F2 = TotalVoltageOverVolta_IN_Fault2;

          /* Entry 'Fault2': '<S1>:17' */
          TotalVoltageOverVoltage_B.F_lev_i = 2U;
        }
      }
      break;

     case TotalVoltageOverVolt_IN_Delay21:
      /* During 'Delay21': '<S1>:118' */
      if (!((V0 < 744.0F) && (V3 < 744.0F) && (ModelFlag == 0))) {
        /* Transition: '<S1>:70' */
        TotalVoltageOverVoltage_DW.is_F2 = TotalVoltageOverVolta_IN_Fault2;

        /* Entry 'Fault2': '<S1>:17' */
        TotalVoltageOverVoltage_B.F_lev_i = 2U;
      } else {
        if (TotalVoltageOverVoltage_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:69' */
          TotalVoltageOverVoltage_DW.is_F2 = TotalVoltageOverVolt_IN_Fault20;

          /* Entry 'Fault20': '<S1>:153' */
          TotalVoltageOverVoltage_B.F_lev_i = 0U;
        }
      }
      break;

     case TotalVoltageOverVolta_IN_Fault2:
      /* During 'Fault2': '<S1>:17' */
      if ((V0 < 744.0F) && (V3 < 744.0F) && (ModelFlag == 0)) {
        /* Transition: '<S1>:72' */
        TotalVoltageOverVoltage_DW.is_F2 = TotalVoltageOverVolt_IN_Delay21;
        TotalVoltageOverVoltage_DW.temporalCounter_i2 = 0U;
      }
      break;

     case TotalVoltageOverVolt_IN_Fault20:
      /* During 'Fault20': '<S1>:153' */
      /* Transition: '<S1>:175' */
      TotalVoltageOverVoltage_DW.is_F2 = TotalVoltageOverVoltag_IN_Wait2;
      break;

     default:
      /* During 'Wait2': '<S1>:97' */
      if ((V0 >= 754.0F) || (V3 >= 754.0F)) {
        /* Transition: '<S1>:19' */
        TotalVoltageOverVoltage_DW.is_F2 = TotalVoltageOverVolt_IN_Delay20;
        TotalVoltageOverVoltage_DW.temporalCounter_i2 = 0U;
      }
      break;
    }

    /* During 'F3': '<S1>:102' */
    switch (TotalVoltageOverVoltage_DW.is_F3) {
     case TotalVoltageOverVolt_IN_Delay30:
      /* During 'Delay30': '<S1>:28' */
      if (!((V0 >= 765.0F) || (V3 >= 765.0F))) {
        /* Transition: '<S1>:24' */
        TotalVoltageOverVoltage_DW.is_F3 = TotalVoltageOverVoltag_IN_Wait3;
      } else {
        if (TotalVoltageOverVoltage_DW.temporalCounter_i3 >= 10) {
          /* Transition: '<S1>:26' */
          TotalVoltageOverVoltage_DW.is_F3 = TotalVoltageOverVolta_IN_Fault3;

          /* Entry 'Fault3': '<S1>:23' */
          TotalVoltageOverVoltage_B.F_lev_i = 3U;
        }
      }
      break;

     case TotalVoltageOverVolt_IN_Delay31:
      /* During 'Delay31': '<S1>:197' */
      if (!((V0 < 744.0F) && (V3 < 744.0F) && (ModelFlag == 0))) {
        /* Transition: '<S1>:195' */
        TotalVoltageOverVoltage_DW.is_F3 = TotalVoltageOverVolta_IN_Fault3;

        /* Entry 'Fault3': '<S1>:23' */
        TotalVoltageOverVoltage_B.F_lev_i = 3U;
      } else {
        if (TotalVoltageOverVoltage_DW.temporalCounter_i3 >= 10) {
          /* Transition: '<S1>:196' */
          TotalVoltageOverVoltage_DW.is_F3 = TotalVoltageOverVolt_IN_Fault30;

          /* Entry 'Fault30': '<S1>:200' */
          TotalVoltageOverVoltage_B.F_lev_i = 0U;
        }
      }
      break;

     case TotalVoltageOverVolt_IN_Delay32:
      /* During 'Delay32': '<S1>:205' */
      if (!((V0 < 754.0F) && (V3 < 754.0F) && (ModelFlag == 0))) {
        /* Transition: '<S1>:208' */
        TotalVoltageOverVoltage_DW.is_F3 = TotalVoltageOverVolta_IN_Fault3;

        /* Entry 'Fault3': '<S1>:23' */
        TotalVoltageOverVoltage_B.F_lev_i = 3U;
      } else {
        if (TotalVoltageOverVoltage_DW.temporalCounter_i3 >= 10) {
          /* Transition: '<S1>:210' */
          /* Exit Internal 'F': '<S1>:103' */
          /* Exit Internal 'F3': '<S1>:102' */
          /* Exit Internal 'F2': '<S1>:101' */
          /* Exit Internal 'F1': '<S1>:192' */
          TotalVoltageOverVoltage_DW.is_F1 = TotalVoltageOverVolta_IN_Fault1;

          /* Entry 'Fault1': '<S1>:182' */
          TotalVoltageOverVoltage_B.F_lev_i = 1U;

          /* Entry Internal 'F2': '<S1>:101' */
          /* Transition: '<S1>:173' */
          TotalVoltageOverVoltage_DW.is_F2 = TotalVoltageOverVoltag_IN_Wait2;

          /* Entry Internal 'F3': '<S1>:102' */
          /* Transition: '<S1>:108' */
          TotalVoltageOverVoltage_DW.is_F3 = TotalVoltageOverVoltag_IN_Wait3;
        }
      }
      break;

     case TotalVoltageOverVolta_IN_Fault3:
      /* During 'Fault3': '<S1>:23' */
      if ((V0 < 744.0F) && (V3 < 744.0F) && (ModelFlag == 0)) {
        /* Transition: '<S1>:199' */
        TotalVoltageOverVoltage_DW.is_F3 = TotalVoltageOverVolt_IN_Delay31;
        TotalVoltageOverVoltage_DW.temporalCounter_i3 = 0U;
      } else if ((V0 < 754.0F) && (V3 < 754.0F) && (ModelFlag == 0)) {
        /* Transition: '<S1>:209' */
        TotalVoltageOverVoltage_DW.is_F3 = TotalVoltageOverVolt_IN_Delay32;
        TotalVoltageOverVoltage_DW.temporalCounter_i3 = 0U;
      } else {
        TotalVoltageOverVoltage_B.F_lev_i = 3U;
      }
      break;

     case TotalVoltageOverVolt_IN_Fault30:
      /* During 'Fault30': '<S1>:200' */
      /* Transition: '<S1>:198' */
      TotalVoltageOverVoltage_DW.is_F3 = TotalVoltageOverVoltag_IN_Wait3;
      break;

     default:
      /* During 'Wait3': '<S1>:98' */
      if ((V0 >= 765.0F) || (V3 >= 765.0F)) {
        /* Transition: '<S1>:25' */
        TotalVoltageOverVoltage_DW.is_F3 = TotalVoltageOverVolt_IN_Delay30;
        TotalVoltageOverVoltage_DW.temporalCounter_i3 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = TotalVoltageOverVoltage_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void TotalVoltageOverVoltage_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(TotalVoltageOverVoltage_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &TotalVoltageOverVoltage_B), 0,
                sizeof(B_TotalVoltageOverVoltage_T));

  /* states (dwork) */
  (void) memset((void *)&TotalVoltageOverVoltage_DW, 0,
                sizeof(DW_TotalVoltageOverVoltage_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  TotalVoltageOverVoltage_DW.is_F1 = TotalVoltage_IN_NO_ACTIVE_CHILD;
  TotalVoltageOverVoltage_DW.temporalCounter_i1 = 0U;
  TotalVoltageOverVoltage_DW.is_F2 = TotalVoltage_IN_NO_ACTIVE_CHILD;
  TotalVoltageOverVoltage_DW.temporalCounter_i2 = 0U;
  TotalVoltageOverVoltage_DW.is_F3 = TotalVoltage_IN_NO_ACTIVE_CHILD;
  TotalVoltageOverVoltage_DW.temporalCounter_i3 = 0U;
  TotalVoltageOverVoltage_DW.is_active_c3_TotalVoltageOverVo = 0U;
  TotalVoltageOverVoltage_B.F_lev_i = 0U;
}

/* Model terminate function */
void TotalVoltageOverVoltage_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

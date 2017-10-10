/*
 * File: BatteryTemperatureLow.c
 *
 * Code generated for Simulink model 'BatteryTemperatureLow'.
 *
 * Model version                  : 1.112
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 16 15:58:15 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "BatteryTemperatureLow.h"
#include "BatteryTemperatureLow_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define BatteryTempe_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define BatteryTemperatureLo_IN_Delay10 ((uint8_T)1U)
#define BatteryTemperatureLo_IN_Delay11 ((uint8_T)2U)
#define BatteryTemperatureLo_IN_Delay20 ((uint8_T)1U)
#define BatteryTemperatureLo_IN_Delay21 ((uint8_T)2U)
#define BatteryTemperatureLo_IN_Delay30 ((uint8_T)1U)
#define BatteryTemperatureLo_IN_Fault10 ((uint8_T)4U)
#define BatteryTemperatureLo_IN_Fault20 ((uint8_T)4U)
#define BatteryTemperatureLow_IN_Fault1 ((uint8_T)3U)
#define BatteryTemperatureLow_IN_Fault2 ((uint8_T)3U)
#define BatteryTemperatureLow_IN_Fault3 ((uint8_T)2U)
#define BatteryTemperatureLow_IN_Wait1 ((uint8_T)5U)
#define BatteryTemperatureLow_IN_Wait2 ((uint8_T)5U)
#define BatteryTemperatureLow_IN_Wait3 ((uint8_T)3U)

/* Block signals (auto storage) */
B_BatteryTemperatureLow_T BatteryTemperatureLow_B;

/* Block states (auto storage) */
DW_BatteryTemperatureLow_T BatteryTemperatureLow_DW;

/* Real-time model */
RT_MODEL_BatteryTemperatureLo_T BatteryTemperatureLow_M_;
RT_MODEL_BatteryTemperatureLo_T *const BatteryTemperatureLow_M =
  &BatteryTemperatureLow_M_;

/* Model step function */
uint8_T BatteryTemperatureLow_custom(uint8_T Tmin)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/Tmin'
   */
  /* Gateway: Chart */
  if (BatteryTemperatureLow_DW.temporalCounter_i1 < 15U) {
    BatteryTemperatureLow_DW.temporalCounter_i1++;
  }

  if (BatteryTemperatureLow_DW.temporalCounter_i2 < 15U) {
    BatteryTemperatureLow_DW.temporalCounter_i2++;
  }

  if (BatteryTemperatureLow_DW.temporalCounter_i3 < 15U) {
    BatteryTemperatureLow_DW.temporalCounter_i3++;
  }

  /* During: Chart */
  if (BatteryTemperatureLow_DW.is_active_c3_BatteryTemperature == 0U) {
    /* Entry: Chart */
    BatteryTemperatureLow_DW.is_active_c3_BatteryTemperature = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F1': '<S1>:189' */
    /* Transition: '<S1>:190' */
    BatteryTemperatureLow_DW.is_F1 = BatteryTemperatureLow_IN_Wait1;

    /* Entry Internal 'F2': '<S1>:101' */
    /* Transition: '<S1>:173' */
    BatteryTemperatureLow_DW.is_F2 = BatteryTemperatureLow_IN_Wait2;

    /* Entry Internal 'F3': '<S1>:102' */
    /* Transition: '<S1>:108' */
    BatteryTemperatureLow_DW.is_F3 = BatteryTemperatureLow_IN_Wait3;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F1': '<S1>:189' */
    switch (BatteryTemperatureLow_DW.is_F1) {
     case BatteryTemperatureLo_IN_Delay10:
      /* During 'Delay10': '<S1>:188' */
      if (!(Tmin < 15)) {
        /* Transition: '<S1>:193' */
        BatteryTemperatureLow_DW.is_F1 = BatteryTemperatureLow_IN_Wait1;
      } else {
        if (BatteryTemperatureLow_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:194' */
          BatteryTemperatureLow_DW.is_F1 = BatteryTemperatureLow_IN_Fault1;

          /* Entry 'Fault1': '<S1>:185' */
          BatteryTemperatureLow_B.F_lev_i = 1U;
        }
      }
      break;

     case BatteryTemperatureLo_IN_Delay11:
      /* During 'Delay11': '<S1>:187' */
      if (!(Tmin >= 17)) {
        /* Transition: '<S1>:182' */
        BatteryTemperatureLow_DW.is_F1 = BatteryTemperatureLow_IN_Fault1;

        /* Entry 'Fault1': '<S1>:185' */
        BatteryTemperatureLow_B.F_lev_i = 1U;
      } else {
        if (BatteryTemperatureLow_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:183' */
          BatteryTemperatureLow_DW.is_F1 = BatteryTemperatureLo_IN_Fault10;

          /* Entry 'Fault10': '<S1>:184' */
          BatteryTemperatureLow_B.F_lev_i = 0U;
        }
      }
      break;

     case BatteryTemperatureLow_IN_Fault1:
      /* During 'Fault1': '<S1>:185' */
      if (Tmin >= 17) {
        /* Transition: '<S1>:191' */
        BatteryTemperatureLow_DW.is_F1 = BatteryTemperatureLo_IN_Delay11;
        BatteryTemperatureLow_DW.temporalCounter_i1 = 0U;
      }
      break;

     case BatteryTemperatureLo_IN_Fault10:
      /* During 'Fault10': '<S1>:184' */
      /* Transition: '<S1>:192' */
      BatteryTemperatureLow_DW.is_F1 = BatteryTemperatureLow_IN_Wait1;
      break;

     default:
      /* During 'Wait1': '<S1>:195' */
      if (Tmin < 15) {
        /* Transition: '<S1>:186' */
        BatteryTemperatureLow_DW.is_F1 = BatteryTemperatureLo_IN_Delay10;
        BatteryTemperatureLow_DW.temporalCounter_i1 = 0U;
      }
      break;
    }

    /* During 'F2': '<S1>:101' */
    switch (BatteryTemperatureLow_DW.is_F2) {
     case BatteryTemperatureLo_IN_Delay20:
      /* During 'Delay20': '<S1>:22' */
      if (!(Tmin < 12)) {
        /* Transition: '<S1>:18' */
        BatteryTemperatureLow_DW.is_F2 = BatteryTemperatureLow_IN_Wait2;
      } else {
        if (BatteryTemperatureLow_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:20' */
          BatteryTemperatureLow_DW.is_F2 = BatteryTemperatureLow_IN_Fault2;

          /* Entry 'Fault2': '<S1>:17' */
          BatteryTemperatureLow_B.F_lev_i = 2U;
        }
      }
      break;

     case BatteryTemperatureLo_IN_Delay21:
      /* During 'Delay21': '<S1>:118' */
      if (!(Tmin >= 15)) {
        /* Transition: '<S1>:70' */
        BatteryTemperatureLow_DW.is_F2 = BatteryTemperatureLow_IN_Fault2;

        /* Entry 'Fault2': '<S1>:17' */
        BatteryTemperatureLow_B.F_lev_i = 2U;
      } else {
        if (BatteryTemperatureLow_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:69' */
          BatteryTemperatureLow_DW.is_F2 = BatteryTemperatureLo_IN_Fault20;

          /* Entry 'Fault20': '<S1>:153' */
          BatteryTemperatureLow_B.F_lev_i = 0U;
        }
      }
      break;

     case BatteryTemperatureLow_IN_Fault2:
      /* During 'Fault2': '<S1>:17' */
      if (Tmin >= 15) {
        /* Transition: '<S1>:72' */
        BatteryTemperatureLow_DW.is_F2 = BatteryTemperatureLo_IN_Delay21;
        BatteryTemperatureLow_DW.temporalCounter_i2 = 0U;
      }
      break;

     case BatteryTemperatureLo_IN_Fault20:
      /* During 'Fault20': '<S1>:153' */
      /* Transition: '<S1>:175' */
      BatteryTemperatureLow_DW.is_F2 = BatteryTemperatureLow_IN_Wait2;
      break;

     default:
      /* During 'Wait2': '<S1>:97' */
      if (Tmin < 12) {
        /* Transition: '<S1>:19' */
        BatteryTemperatureLow_DW.is_F2 = BatteryTemperatureLo_IN_Delay20;
        BatteryTemperatureLow_DW.temporalCounter_i2 = 0U;
      }
      break;
    }

    /* During 'F3': '<S1>:102' */
    switch (BatteryTemperatureLow_DW.is_F3) {
     case BatteryTemperatureLo_IN_Delay30:
      /* During 'Delay30': '<S1>:28' */
      if (!(Tmin < 10)) {
        /* Transition: '<S1>:24' */
        BatteryTemperatureLow_DW.is_F3 = BatteryTemperatureLow_IN_Wait3;
      } else {
        if (BatteryTemperatureLow_DW.temporalCounter_i3 >= 10) {
          /* Transition: '<S1>:26' */
          BatteryTemperatureLow_DW.is_F3 = BatteryTemperatureLow_IN_Fault3;

          /* Entry 'Fault3': '<S1>:23' */
          BatteryTemperatureLow_B.F_lev_i = 3U;
        }
      }
      break;

     case BatteryTemperatureLow_IN_Fault3:
      /* During 'Fault3': '<S1>:23' */
      BatteryTemperatureLow_B.F_lev_i = 3U;
      break;

     default:
      /* During 'Wait3': '<S1>:98' */
      if (Tmin < 10) {
        /* Transition: '<S1>:25' */
        BatteryTemperatureLow_DW.is_F3 = BatteryTemperatureLo_IN_Delay30;
        BatteryTemperatureLow_DW.temporalCounter_i3 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = BatteryTemperatureLow_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void BatteryTemperatureLow_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(BatteryTemperatureLow_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &BatteryTemperatureLow_B), 0,
                sizeof(B_BatteryTemperatureLow_T));

  /* states (dwork) */
  (void) memset((void *)&BatteryTemperatureLow_DW, 0,
                sizeof(DW_BatteryTemperatureLow_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  BatteryTemperatureLow_DW.is_F1 = BatteryTempe_IN_NO_ACTIVE_CHILD;
  BatteryTemperatureLow_DW.temporalCounter_i1 = 0U;
  BatteryTemperatureLow_DW.is_F2 = BatteryTempe_IN_NO_ACTIVE_CHILD;
  BatteryTemperatureLow_DW.temporalCounter_i2 = 0U;
  BatteryTemperatureLow_DW.is_F3 = BatteryTempe_IN_NO_ACTIVE_CHILD;
  BatteryTemperatureLow_DW.temporalCounter_i3 = 0U;
  BatteryTemperatureLow_DW.is_active_c3_BatteryTemperature = 0U;
  BatteryTemperatureLow_B.F_lev_i = 0U;
}

/* Model terminate function */
void BatteryTemperatureLow_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: BatteryTemperatureHigh.c
 *
 * Code generated for Simulink model 'BatteryTemperatureHigh'.
 *
 * Model version                  : 1.106
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 16 15:58:26 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "BatteryTemperatureHigh.h"
#include "BatteryTemperatureHigh_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define BatteryTempe_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define BatteryTemperatureHi_IN_Delay10 ((uint8_T)1U)
#define BatteryTemperatureHi_IN_Delay11 ((uint8_T)2U)
#define BatteryTemperatureHi_IN_Delay20 ((uint8_T)1U)
#define BatteryTemperatureHi_IN_Delay21 ((uint8_T)2U)
#define BatteryTemperatureHi_IN_Delay30 ((uint8_T)1U)
#define BatteryTemperatureHi_IN_Fault10 ((uint8_T)4U)
#define BatteryTemperatureHi_IN_Fault20 ((uint8_T)4U)
#define BatteryTemperatureHig_IN_Fault1 ((uint8_T)3U)
#define BatteryTemperatureHig_IN_Fault2 ((uint8_T)3U)
#define BatteryTemperatureHig_IN_Fault3 ((uint8_T)2U)
#define BatteryTemperatureHigh_IN_Wait1 ((uint8_T)5U)
#define BatteryTemperatureHigh_IN_Wait2 ((uint8_T)5U)
#define BatteryTemperatureHigh_IN_Wait3 ((uint8_T)3U)

/* Block signals (auto storage) */
B_BatteryTemperatureHigh_T BatteryTemperatureHigh_B;

/* Block states (auto storage) */
DW_BatteryTemperatureHigh_T BatteryTemperatureHigh_DW;

/* Real-time model */
RT_MODEL_BatteryTemperatureHi_T BatteryTemperatureHigh_M_;
RT_MODEL_BatteryTemperatureHi_T *const BatteryTemperatureHigh_M =
  &BatteryTemperatureHigh_M_;

/* Model step function */
uint8_T BatteryTemperatureHigh_custom(uint8_T Tmax)
{
  /* specified return value */
  uint8_T F_lev;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/Tmax'
   */
  /* Gateway: Chart */
  if (BatteryTemperatureHigh_DW.temporalCounter_i1 < 15U) {
    BatteryTemperatureHigh_DW.temporalCounter_i1++;
  }

  if (BatteryTemperatureHigh_DW.temporalCounter_i2 < 15U) {
    BatteryTemperatureHigh_DW.temporalCounter_i2++;
  }

  if (BatteryTemperatureHigh_DW.temporalCounter_i3 < 15U) {
    BatteryTemperatureHigh_DW.temporalCounter_i3++;
  }

  /* During: Chart */
  if (BatteryTemperatureHigh_DW.is_active_c3_BatteryTemperature == 0U) {
    /* Entry: Chart */
    BatteryTemperatureHigh_DW.is_active_c3_BatteryTemperature = 1U;

    /* Entry Internal: Chart */
    /* Transition: '<S1>:104' */
    /* Entry Internal 'F': '<S1>:103' */
    /* Entry Internal 'F1': '<S1>:181' */
    /* Transition: '<S1>:183' */
    BatteryTemperatureHigh_DW.is_F1 = BatteryTemperatureHigh_IN_Wait1;

    /* Entry Internal 'F2': '<S1>:101' */
    /* Transition: '<S1>:173' */
    BatteryTemperatureHigh_DW.is_F2 = BatteryTemperatureHigh_IN_Wait2;

    /* Entry Internal 'F3': '<S1>:102' */
    /* Transition: '<S1>:108' */
    BatteryTemperatureHigh_DW.is_F3 = BatteryTemperatureHigh_IN_Wait3;
  } else {
    /* During 'F': '<S1>:103' */
    /* During 'F1': '<S1>:181' */
    switch (BatteryTemperatureHigh_DW.is_F1) {
     case BatteryTemperatureHi_IN_Delay10:
      /* During 'Delay10': '<S1>:184' */
      if (!(Tmax >= 92)) {
        /* Transition: '<S1>:194' */
        BatteryTemperatureHigh_DW.is_F1 = BatteryTemperatureHigh_IN_Wait1;
      } else {
        if (BatteryTemperatureHigh_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:182' */
          BatteryTemperatureHigh_DW.is_F1 = BatteryTemperatureHig_IN_Fault1;

          /* Entry 'Fault1': '<S1>:189' */
          BatteryTemperatureHigh_B.F_lev_i = 1U;
        }
      }
      break;

     case BatteryTemperatureHi_IN_Delay11:
      /* During 'Delay11': '<S1>:187' */
      if (!(Tmax < 88)) {
        /* Transition: '<S1>:188' */
        BatteryTemperatureHigh_DW.is_F1 = BatteryTemperatureHig_IN_Fault1;

        /* Entry 'Fault1': '<S1>:189' */
        BatteryTemperatureHigh_B.F_lev_i = 1U;
      } else {
        if (BatteryTemperatureHigh_DW.temporalCounter_i1 >= 10) {
          /* Transition: '<S1>:190' */
          BatteryTemperatureHigh_DW.is_F1 = BatteryTemperatureHi_IN_Fault10;

          /* Entry 'Fault10': '<S1>:191' */
          BatteryTemperatureHigh_B.F_lev_i = 0U;
        }
      }
      break;

     case BatteryTemperatureHig_IN_Fault1:
      /* During 'Fault1': '<S1>:189' */
      if (Tmax < 88) {
        /* Transition: '<S1>:192' */
        BatteryTemperatureHigh_DW.is_F1 = BatteryTemperatureHi_IN_Delay11;
        BatteryTemperatureHigh_DW.temporalCounter_i1 = 0U;
      }
      break;

     case BatteryTemperatureHi_IN_Fault10:
      /* During 'Fault10': '<S1>:191' */
      /* Transition: '<S1>:193' */
      BatteryTemperatureHigh_DW.is_F1 = BatteryTemperatureHigh_IN_Wait1;
      break;

     default:
      /* During 'Wait1': '<S1>:185' */
      if (Tmax >= 92) {
        /* Transition: '<S1>:186' */
        BatteryTemperatureHigh_DW.is_F1 = BatteryTemperatureHi_IN_Delay10;
        BatteryTemperatureHigh_DW.temporalCounter_i1 = 0U;
      }
      break;
    }

    /* During 'F2': '<S1>:101' */
    switch (BatteryTemperatureHigh_DW.is_F2) {
     case BatteryTemperatureHi_IN_Delay20:
      /* During 'Delay20': '<S1>:22' */
      if (!(Tmax >= 95)) {
        /* Transition: '<S1>:18' */
        BatteryTemperatureHigh_DW.is_F2 = BatteryTemperatureHigh_IN_Wait2;
      } else {
        if (BatteryTemperatureHigh_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:20' */
          BatteryTemperatureHigh_DW.is_F2 = BatteryTemperatureHig_IN_Fault2;

          /* Entry 'Fault2': '<S1>:17' */
          BatteryTemperatureHigh_B.F_lev_i = 2U;
        }
      }
      break;

     case BatteryTemperatureHi_IN_Delay21:
      /* During 'Delay21': '<S1>:118' */
      if (!(Tmax < 92)) {
        /* Transition: '<S1>:70' */
        BatteryTemperatureHigh_DW.is_F2 = BatteryTemperatureHig_IN_Fault2;

        /* Entry 'Fault2': '<S1>:17' */
        BatteryTemperatureHigh_B.F_lev_i = 2U;
      } else {
        if (BatteryTemperatureHigh_DW.temporalCounter_i2 >= 10) {
          /* Transition: '<S1>:69' */
          BatteryTemperatureHigh_DW.is_F2 = BatteryTemperatureHi_IN_Fault20;

          /* Entry 'Fault20': '<S1>:153' */
          BatteryTemperatureHigh_B.F_lev_i = 0U;
        }
      }
      break;

     case BatteryTemperatureHig_IN_Fault2:
      /* During 'Fault2': '<S1>:17' */
      if (Tmax < 92) {
        /* Transition: '<S1>:72' */
        BatteryTemperatureHigh_DW.is_F2 = BatteryTemperatureHi_IN_Delay21;
        BatteryTemperatureHigh_DW.temporalCounter_i2 = 0U;
      }
      break;

     case BatteryTemperatureHi_IN_Fault20:
      /* During 'Fault20': '<S1>:153' */
      /* Transition: '<S1>:175' */
      BatteryTemperatureHigh_DW.is_F2 = BatteryTemperatureHigh_IN_Wait2;
      break;

     default:
      /* During 'Wait2': '<S1>:97' */
      if (Tmax >= 95) {
        /* Transition: '<S1>:19' */
        BatteryTemperatureHigh_DW.is_F2 = BatteryTemperatureHi_IN_Delay20;
        BatteryTemperatureHigh_DW.temporalCounter_i2 = 0U;
      }
      break;
    }

    /* During 'F3': '<S1>:102' */
    switch (BatteryTemperatureHigh_DW.is_F3) {
     case BatteryTemperatureHi_IN_Delay30:
      /* During 'Delay30': '<S1>:28' */
      if (!(Tmax >= 97)) {
        /* Transition: '<S1>:24' */
        BatteryTemperatureHigh_DW.is_F3 = BatteryTemperatureHigh_IN_Wait3;
      } else {
        if (BatteryTemperatureHigh_DW.temporalCounter_i3 >= 10) {
          /* Transition: '<S1>:26' */
          BatteryTemperatureHigh_DW.is_F3 = BatteryTemperatureHig_IN_Fault3;

          /* Entry 'Fault3': '<S1>:23' */
          BatteryTemperatureHigh_B.F_lev_i = 3U;
        }
      }
      break;

     case BatteryTemperatureHig_IN_Fault3:
      /* During 'Fault3': '<S1>:23' */
      BatteryTemperatureHigh_B.F_lev_i = 3U;
      break;

     default:
      /* During 'Wait3': '<S1>:98' */
      if (Tmax >= 97) {
        /* Transition: '<S1>:25' */
        BatteryTemperatureHigh_DW.is_F3 = BatteryTemperatureHi_IN_Delay30;
        BatteryTemperatureHigh_DW.temporalCounter_i3 = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/F_lev' */
  F_lev = BatteryTemperatureHigh_B.F_lev_i;
  return F_lev;
}

/* Model initialize function */
void BatteryTemperatureHigh_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(BatteryTemperatureHigh_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &BatteryTemperatureHigh_B), 0,
                sizeof(B_BatteryTemperatureHigh_T));

  /* states (dwork) */
  (void) memset((void *)&BatteryTemperatureHigh_DW, 0,
                sizeof(DW_BatteryTemperatureHigh_T));

  /* SystemInitialize for Chart: '<Root>/Chart' */
  BatteryTemperatureHigh_DW.is_F1 = BatteryTempe_IN_NO_ACTIVE_CHILD;
  BatteryTemperatureHigh_DW.temporalCounter_i1 = 0U;
  BatteryTemperatureHigh_DW.is_F2 = BatteryTempe_IN_NO_ACTIVE_CHILD;
  BatteryTemperatureHigh_DW.temporalCounter_i2 = 0U;
  BatteryTemperatureHigh_DW.is_F3 = BatteryTempe_IN_NO_ACTIVE_CHILD;
  BatteryTemperatureHigh_DW.temporalCounter_i3 = 0U;
  BatteryTemperatureHigh_DW.is_active_c3_BatteryTemperature = 0U;
  BatteryTemperatureHigh_B.F_lev_i = 0U;
}

/* Model terminate function */
void BatteryTemperatureHigh_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

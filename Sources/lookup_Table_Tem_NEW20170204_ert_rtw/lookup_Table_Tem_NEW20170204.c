/*
 * File: lookup_Table_Tem_NEW20170204.c
 *
 * Code generated for Simulink model 'lookup_Table_Tem_NEW20170204'.
 *
 * Model version                  : 1.71
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Sat Feb 04 09:40:35 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "lookup_Table_Tem_NEW20170204.h"
#include "lookup_Table_Tem_NEW20170204_private.h"

/* Block signals (auto storage) */
B_lookup_Table_Tem_NEW2017020_T lookup_Table_Tem_NEW20170204_B;

/* Real-time model */
RT_MODEL_lookup_Table_Tem_NEW_T lookup_Table_Tem_NEW20170204_M_;
RT_MODEL_lookup_Table_Tem_NEW_T *const lookup_Table_Tem_NEW20170204_M =
  &lookup_Table_Tem_NEW20170204_M_;
real32_T look1T_iflf_binlxpw(real32_T u0, const real32_T bp0[], const real32_T
  table[], uint32_T maxIndex)
{
  real32_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0UL]) {
    iLeft = 0UL;
    frac = (u0 - bp0[0UL]) / (bp0[1UL] - bp0[0UL]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1UL;
    iLeft = 0UL;
    iRght = maxIndex;
    while (iRght - iLeft > 1UL) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1UL;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1UL] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1UL;
    frac = (u0 - bp0[maxIndex - 1UL]) / (bp0[maxIndex] - bp0[maxIndex - 1UL]);
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1UL] - table[iLeft]) * frac + table[iLeft];
}

/* Model step function */
real32_T lookup_Table_Tem_NEW20170204_custom(real32_T soc)
{
  real32_T rtb_DLookupTable;

  /* specified return value */
  real32_T feedbackvalue;

  /* Lookup_n-D: '<Root>/1-D Lookup Table' incorporates:
   *  Inport: '<Root>/In1'
   */
  rtb_DLookupTable = look1T_iflf_binlxpw(soc,
    lookup_Table_Tem_NEW20170204_P.lookup_table_voltage_NEW20170204,
    lookup_Table_Tem_NEW20170204_P.lookup_table_tem_NEW20170204, 238UL);

  /* Gain: '<Root>/Gain1' */
  rtb_DLookupTable *= lookup_Table_Tem_NEW20170204_P.Gain1_Gain;

  /* Chart: '<Root>/Chart' */
  /* Gateway: Chart */
  /* During: Chart */
  /* Entry Internal: Chart */
  /* Transition: '<S1>:3' */
  if (rtb_DLookupTable > 198.0F) {
    /* Transition: '<S1>:6' */
    /* Transition: '<S1>:10' */
    lookup_Table_Tem_NEW20170204_B.out_temp = 198.0F;

    /* Transition: '<S1>:16' */
  } else {
    /* Transition: '<S1>:8' */
    if (rtb_DLookupTable < -40.0F) {
      /* Transition: '<S1>:12' */
      /* Transition: '<S1>:14' */
      lookup_Table_Tem_NEW20170204_B.out_temp = -40.0F;

      /* Transition: '<S1>:17' */
    } else {
      /* Transition: '<S1>:22' */
      if ((rtb_DLookupTable <= 198.0F) && (rtb_DLookupTable >= -40.0F)) {
        /* Transition: '<S1>:21' */
        /* Transition: '<S1>:24' */
        lookup_Table_Tem_NEW20170204_B.out_temp = rtb_DLookupTable;

        /* Transition: '<S1>:25' */
      }
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/Out1' */
  feedbackvalue = lookup_Table_Tem_NEW20170204_B.out_temp;
  return feedbackvalue;
}

/* Model initialize function */
void lookup_Table_Tem_NEW20170204_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(lookup_Table_Tem_NEW20170204_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &lookup_Table_Tem_NEW20170204_B), 0,
                sizeof(B_lookup_Table_Tem_NEW2017020_T));
}

/* Model terminate function */
void lookup_Table_Tem_NEW20170204_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

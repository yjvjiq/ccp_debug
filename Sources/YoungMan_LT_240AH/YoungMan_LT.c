/*
 * File: YoungMan_LT.c
 *
 * Code generated for Simulink model 'YoungMan_LT'.
 *
 * Model version                  : 1.1160
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Wed Jun 28 16:07:12 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "YoungMan_LT.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFU) ) || ( INT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFUL) ) || ( LONG_MAX != (0x7FFFFFFFL) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Exported block signals */
real32_T BiggestFeedbackCurt_Model;    /* '<S5>/Gain'
                                        * Output
                                        */
real32_T PowerOnSOCAjustFactor;        /* '<S4>/1-D Lookup Table'
                                        * Input
                                        */
real32_T m_askcurrent_Model;           /* '<S3>/Gain'
                                        * Output
                                        */
real32_T ChargeEndSOCAjustFactor;      /* '<S2>/2-D Lookup Table3'
                                        * Input
                                        */
real32_T BiggestDischargeCurt_Model;   /* '<S1>/Gain'
                                        * Output
                                        */

/* Exported data definition */

/* Definition for custom storage class: Default */
real32_T CAP_CONST_CAL = 150.0F;
real32_T DisChargeCurrentTable[204] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
  0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.1F, 0.21F, 0.32F, 0.42F, 0.42F, 0.42F,
  0.42F, 0.42F, 0.42F, 0.42F, 0.42F, 0.0F, 0.21F, 0.42F, 0.48F, 0.84F, 0.84F,
  0.84F, 0.84F, 0.84F, 0.84F, 0.84F, 0.84F, 0.0F, 0.21F, 0.42F, 0.63F, 0.84F,
  0.84F, 0.84F, 0.84F, 0.84F, 0.84F, 0.84F, 0.84F, 0.0F, 0.21F, 0.42F, 0.69F,
  0.84F, 0.84F, 0.84F, 0.84F, 0.84F, 0.84F, 0.84F, 0.84F, 0.0F, 0.37F, 0.82F,
  0.82F, 1.68F, 1.68F, 1.68F, 1.87F, 1.87F, 1.87F, 1.87F, 1.87F, 0.0F, 0.41F,
  0.89F, 0.89F, 1.83F, 1.83F, 1.83F, 2.03F, 2.03F, 2.03F, 2.03F, 2.03F, 0.0F,
  0.74F, 1.28F, 1.28F, 2.02F, 2.02F, 2.02F, 2.35F, 2.35F, 2.35F, 2.35F, 2.35F,
  0.0F, 0.87F, 1.39F, 1.39F, 2.1F, 2.1F, 2.1F, 2.6F, 2.6F, 2.6F, 2.6F, 2.6F,
  0.0F, 1.01F, 1.51F, 1.51F, 2.18F, 2.18F, 2.18F, 2.67F, 2.67F, 2.67F, 2.67F,
  2.67F, 0.0F, 1.21F, 2.21F, 2.21F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F,
  2.67F, 2.67F, 0.0F, 1.26F, 2.51F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F,
  2.67F, 2.67F, 2.67F, 0.0F, 1.26F, 2.51F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F,
  2.67F, 2.67F, 2.67F, 2.67F, 0.0F, 1.26F, 1.68F, 1.68F, 2.4F, 2.4F, 2.4F, 2.4F,
  2.4F, 2.4F, 2.4F, 2.4F, 0.0F, 0.63F, 0.84F, 0.84F, 1.2F, 1.2F, 1.2F, 1.2F,
  1.2F, 1.2F, 1.2F, 1.2F, 0.0F, 0.36F, 0.5F, 0.5F, 0.72F, 0.72F, 0.72F, 0.72F,
  0.72F, 0.72F, 0.72F, 0.72F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
  0.0F, 0.0F, 0.0F, 0.0F } ;           /* maximum discharge current, row: SOC, collumn: T  */

uint16_T Factor_ChargeEndSOCAjust[64] = { 22365U, 23773U, 24698U, 29920U, 33731U,
  36352U, 38010U, 38080U, 24307U, 25696U, 27814U, 33398U, 35770U, 37360U, 38400U,
  38400U, 26173U, 31610U, 33782U, 36627U, 37715U, 38400U, 38400U, 38400U, 31782U,
  35520U, 36352U, 37798U, 38400U, 38400U, 38400U, 38400U, 34509U, 36886U, 37530U,
  38400U, 38400U, 38400U, 38400U, 38400U, 36666U, 38029U, 38400U, 38400U, 38400U,
  38400U, 38400U, 38400U, 38141U, 38400U, 38400U, 38400U, 38400U, 38400U, 38400U,
  38400U, 38400U, 38400U, 38400U, 38400U, 38400U, 38400U, 38400U, 38400U } ;

real32_T Factor_PowerOnSOCAjust[8] = { 0.6346F, 0.7105F, 0.7811F, 0.8448F,
  0.9066F, 0.9523F, 0.9887F, 1.0F } ;

real32_T FastChargeCurrentTable[176] = { 0.0F, 0.2F, 0.4F, 0.6F, 1.0F, 1.5F,
  1.5F, 1.5F, 5.2F, 5.2F, 5.2F, 5.2F, 1.0F, 0.5F, 0.3F, 0.0F, 0.0F, 0.2F, 0.4F,
  0.6F, 1.0F, 1.5F, 1.5F, 1.5F, 5.2F, 5.2F, 5.2F, 5.2F, 1.0F, 0.5F, 0.3F, 0.0F,
  0.0F, 0.2F, 0.4F, 0.6F, 1.0F, 1.5F, 1.5F, 1.5F, 5.2F, 5.2F, 5.2F, 5.2F, 1.0F,
  0.5F, 0.3F, 0.0F, 0.0F, 0.2F, 0.4F, 0.6F, 1.0F, 1.5F, 1.5F, 1.5F, 5.2F, 5.2F,
  5.2F, 5.2F, 1.0F, 0.5F, 0.3F, 0.0F, 0.0F, 0.2F, 0.4F, 0.6F, 1.0F, 1.5F, 1.5F,
  1.5F, 5.2F, 5.2F, 5.2F, 5.2F, 1.0F, 0.5F, 0.3F, 0.0F, 0.0F, 0.2F, 0.4F, 0.6F,
  1.0F, 1.5F, 1.5F, 1.5F, 5.2F, 5.2F, 5.2F, 5.2F, 1.0F, 0.5F, 0.3F, 0.0F, 0.0F,
  0.2F, 0.4F, 0.6F, 1.0F, 1.5F, 1.5F, 1.5F, 5.2F, 5.2F, 5.2F, 5.2F, 1.0F, 0.5F,
  0.3F, 0.0F, 0.0F, 0.2F, 0.4F, 0.6F, 1.0F, 1.5F, 1.5F, 1.5F, 5.2F, 5.2F, 5.2F,
  5.2F, 1.0F, 0.5F, 0.3F, 0.0F, 0.0F, 0.1F, 0.2F, 0.3F, 0.5F, 1.0F, 1.5F, 1.5F,
  5.2F, 5.2F, 5.2F, 5.2F, 1.0F, 0.5F, 0.3F, 0.0F, 0.0F, 0.1F, 0.2F, 0.3F, 0.5F,
  1.0F, 1.0F, 1.0F, 3.0F, 3.0F, 1.0F, 1.0F, 0.5F, 0.2F, 0.12F, 0.0F, 0.0F, 0.1F,
  0.1F, 0.15F, 0.3F, 0.5F, 0.5F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 0.5F, 0.2F, 0.12F,
  0.0F } ;

real32_T FeedBackCurrentTable[208] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
  0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.1F, 0.1F, 0.1F, 0.1F, 0.1F, 0.1F, 0.1F,
  0.1F, 0.05F, 0.05F, 0.0F, 0.0F, 0.0F, 0.2F, 0.2F, 0.2F, 0.2F, 0.2F, 0.2F, 0.2F,
  0.2F, 0.1F, 0.1F, 0.1F, 0.0F, 0.0F, 0.2F, 0.2F, 0.2F, 0.2F, 0.2F, 0.2F, 0.2F,
  0.2F, 0.1F, 0.1F, 0.1F, 0.0F, 0.0F, 0.4F, 0.4F, 0.4F, 0.4F, 0.4F, 0.4F, 0.4F,
  0.4F, 0.4F, 0.2F, 0.2F, 0.0F, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
  1.0F, 1.0F, 0.5F, 0.5F, 0.0F, 0.0F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F, 1.5F,
  1.5F, 1.5F, 1.5F, 1.0F, 0.0F, 0.0F, 2.5F, 2.5F, 2.5F, 2.5F, 2.5F, 2.5F, 2.5F,
  2.5F, 2.5F, 2.0F, 2.0F, 0.0F, 0.0F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F,
  2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 0.0F, 0.0F, 2.67F, 2.67F, 2.67F, 2.67F,
  2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 0.0F, 0.0F, 2.67F, 2.67F,
  2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 1.0F, 0.0F, 0.0F,
  2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 2.67F, 1.0F,
  0.0F, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 0.5F,
  0.0F, 0.0F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.2F,
  0.0F, 0.0F, 0.3F, 0.3F, 0.3F, 0.3F, 0.3F, 0.3F, 0.3F, 0.3F, 0.3F, 0.3F, 0.12F,
  0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
  0.0F, 0.0F } ;                       /* maximum discharge current, row: SOC, collumn: T  */

real32_T SOC_Discharge[12] = { 0.0F, 0.1F, 0.2F, 0.3F, 0.4F, 0.5F, 0.6F, 0.7F,
  0.8F, 0.9F, 0.95F, 1.0F } ;

real32_T SOC_FastCharge[11] = { 0.0F, 0.1F, 0.2F, 0.3F, 0.4F, 0.5F, 0.6F, 0.7F,
  0.8F, 0.9F, 1.0F } ;

real32_T SOC_Feedback[13] = { 0.0F, 0.1F, 0.2F, 0.3F, 0.4F, 0.5F, 0.6F, 0.65F,
  0.7F, 0.8F, 0.9F, 0.95F, 1.0F } ;    /* row for max dicharge current table */

real32_T T_ChargeEndSOCAjust[8] = { 0.0F, 5.0F, 10.0F, 15.0F, 20.0F, 25.0F,
  35.0F, 45.0F } ;

real32_T T_Discharge[17] = { -30.0F, -25.0F, -20.0F, -18.0F, -15.0F, -10.0F,
  -5.0F, 0.0F, 5.0F, 10.0F, 20.0F, 25.0F, 40.0F, 45.0F, 50.0F, 52.0F, 57.0F } ;/* collumn for max discharge current table */

real32_T T_Facdback[16] = { -15.0F, -10.0F, -5.0F, 0.0F, 5.0F, 10.0F, 15.0F,
  20.0F, 25.0F, 35.0F, 40.0F, 45.0F, 47.0F, 50.0F, 52.0F, 57.0F } ;

real32_T T_FastCharge[16] = { 0.0F, 2.0F, 5.0F, 7.0F, 10.0F, 12.0F, 15.0F, 20.0F,
  23.0F, 35.0F, 40.0F, 45.0F, 47.0F, 50.0F, 52.0F, 57.0F } ;

real32_T T_PowerOnSOCAjust[8] = { -20.0F, -15.0F, -10.0F, -5.0F, 0.0F, 5.0F,
  10.0F, 15.0F } ;

real32_T V_CellLowest[8] = { 3.389F, 3.399F, 3.405F, 3.422F, 3.44F, 3.475F,
  3.63F, 3.65F } ;

/* Constant parameters (auto storage) */
const ConstP_YoungMan_LT_T YoungMan_LT_ConstP = {
  /* Computed Parameter: linearizationSOF_maxIndex
   * Referenced by: '<S6>/linearizationSOF'
   */
  { 11U, 16U },

  /* Computed Parameter: uDLookupTable3_maxIndex
   * Referenced by: '<S2>/2-D Lookup Table3'
   */
  { 7U, 7U },

  /* Computed Parameter: uDLookupTable3_maxIndex_g
   * Referenced by: '<S3>/2-D Lookup Table3'
   */
  { 15U, 10U },

  /* Computed Parameter: linearizationSOF_maxIndex_f
   * Referenced by: '<S9>/linearizationSOF'
   */
  { 12U, 15U }
};

/* Real-time model */
RT_MODEL_YoungMan_LT_T YoungMan_LT_M_;
RT_MODEL_YoungMan_LT_T *const YoungMan_LT_M = &YoungMan_LT_M_;
real32_T look2_iflf_binlcpw(real32_T u0, real32_T u1, const real32_T bp0[],
  const real32_T bp1[], const real32_T table[], const uint32_T maxIndex[],
  uint32_T stride);
real32_T look2_ifs16bfflftu16n8_PYqzO3tA(real32_T u0, int16_T u1, const real32_T
  bp0[], const real32_T bp1[], const uint16_T table[], const uint32_T maxIndex[],
  uint32_T stride);
real32_T look2_iflf_linlcpw(real32_T u0, real32_T u1, const real32_T bp0[],
  const real32_T bp1[], const real32_T table[], const uint32_T maxIndex[],
  uint32_T stride);
real32_T look1_iflf_binlcpw(real32_T u0, const real32_T bp0[], const real32_T
  table[], uint32_T maxIndex);
extern void YoungMa_BigDischargePowerAdjust(void);
extern void YoungMan_LT_ChargeEndSOCAjust(void);
extern void YoungMan_LT_FastChrgPowerAjust(void);
extern void YoungMan_LT_PowerOnSOCAjust(void);
extern void YoungM_PulseRechargePowerAdjust(void);
real32_T look2_iflf_binlcpw(real32_T u0, real32_T u1, const real32_T bp0[],
  const real32_T bp1[], const real32_T table[], const uint32_T maxIndex[],
  uint32_T stride)
{
  real32_T frac;
  uint32_T bpIndices[2];
  real32_T fractions[2];
  real32_T yL_1d;
  uint32_T iRght;
  uint32_T bpIdx;
  uint32_T iLeft;

  /* Lookup 2-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0UL]) {
    iLeft = 0UL;
    frac = 0.0F;
  } else if (u0 < bp0[maxIndex[0UL]]) {
    /* Binary Search */
    bpIdx = maxIndex[0UL] >> 1UL;
    iLeft = 0UL;
    iRght = maxIndex[0UL];
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
    iLeft = maxIndex[0UL] - 1UL;
    frac = 1.0F;
  }

  fractions[0UL] = frac;
  bpIndices[0UL] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0UL]) {
    iLeft = 0UL;
    frac = 0.0F;
  } else if (u1 < bp1[maxIndex[1UL]]) {
    /* Binary Search */
    bpIdx = maxIndex[1UL] >> 1UL;
    iLeft = 0UL;
    iRght = maxIndex[1UL];
    while (iRght - iLeft > 1UL) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1UL;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1UL] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1UL] - 1UL;
    frac = 1.0F;
  }

  /* Interpolation 2-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0UL];
  yL_1d = (table[bpIdx + 1UL] - table[bpIdx]) * fractions[0UL] + table[bpIdx];
  bpIdx += stride;
  return (((table[bpIdx + 1UL] - table[bpIdx]) * fractions[0UL] + table[bpIdx])
          - yL_1d) * frac + yL_1d;
}

real32_T look2_ifs16bfflftu16n8_PYqzO3tA(real32_T u0, int16_T u1, const real32_T
  bp0[], const real32_T bp1[], const uint16_T table[], const uint32_T maxIndex[],
  uint32_T stride)
{
  real32_T frac;
  uint32_T bpIndices[2];
  real32_T fractions[2];
  real32_T yL_1d;
  uint32_T bpIdx;

  /* Lookup 2-D
     Canonical function name: look2_ifs16bfflftu16n8DfIf_linlcspw
     Search method: 'linear'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
     Rounding mode: 'simplest'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0UL]) {
    bpIdx = 0UL;
    frac = 0.0F;
  } else if (u0 < bp0[maxIndex[0UL]]) {
    /* Linear Search */
    for (bpIdx = maxIndex[0UL] >> 1UL; u0 < bp0[bpIdx]; bpIdx--) {
    }

    while (u0 >= bp0[bpIdx + 1UL]) {
      bpIdx++;
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1UL] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex[0UL] - 1UL;
    frac = 1.0F;
  }

  fractions[0UL] = frac;
  bpIndices[0UL] = bpIdx;

  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 < bp1[0UL]) {
    bpIdx = 0UL;
    frac = 0.0F;
  } else if (u1 < bp1[maxIndex[1UL]]) {
    /* Linear Search */
    for (bpIdx = maxIndex[1UL] >> 1UL; u1 < bp1[bpIdx]; bpIdx--) {
    }

    while (u1 >= bp1[bpIdx + 1UL]) {
      bpIdx++;
    }

    frac = ((real32_T)u1 - bp1[bpIdx]) / (bp1[bpIdx + 1UL] - bp1[bpIdx]);
  } else {
    bpIdx = maxIndex[1UL] - 1UL;
    frac = 1.0F;
  }

  /* Interpolation 2-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Rounding mode: 'simplest'
     Overflow mode: 'portable wrapping'
   */
  bpIdx = bpIdx * stride + bpIndices[0UL];
  yL_1d = ((real32_T)table[bpIdx + 1UL] * 0.00390625F - (real32_T)table[bpIdx] *
           0.00390625F) * fractions[0UL] + (real32_T)table[bpIdx] * 0.00390625F;
  bpIdx += stride;
  return ((((real32_T)table[bpIdx + 1UL] * 0.00390625F - (real32_T)table[bpIdx] *
            0.00390625F) * fractions[0UL] + (real32_T)table[bpIdx] * 0.00390625F)
          - yL_1d) * frac + yL_1d;
}

real32_T look2_iflf_linlcpw(real32_T u0, real32_T u1, const real32_T bp0[],
  const real32_T bp1[], const real32_T table[], const uint32_T maxIndex[],
  uint32_T stride)
{
  real32_T frac;
  uint32_T bpIndices[2];
  real32_T fractions[2];
  real32_T yL_1d;
  uint32_T bpIdx;

  /* Lookup 2-D
     Search method: 'linear'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0UL]) {
    bpIdx = 0UL;
    frac = 0.0F;
  } else if (u0 < bp0[maxIndex[0UL]]) {
    /* Linear Search */
    for (bpIdx = maxIndex[0UL] >> 1UL; u0 < bp0[bpIdx]; bpIdx--) {
    }

    while (u0 >= bp0[bpIdx + 1UL]) {
      bpIdx++;
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1UL] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex[0UL] - 1UL;
    frac = 1.0F;
  }

  fractions[0UL] = frac;
  bpIndices[0UL] = bpIdx;

  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0UL]) {
    bpIdx = 0UL;
    frac = 0.0F;
  } else if (u1 < bp1[maxIndex[1UL]]) {
    /* Linear Search */
    for (bpIdx = maxIndex[1UL] >> 1UL; u1 < bp1[bpIdx]; bpIdx--) {
    }

    while (u1 >= bp1[bpIdx + 1UL]) {
      bpIdx++;
    }

    frac = (u1 - bp1[bpIdx]) / (bp1[bpIdx + 1UL] - bp1[bpIdx]);
  } else {
    bpIdx = maxIndex[1UL] - 1UL;
    frac = 1.0F;
  }

  /* Interpolation 2-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  bpIdx = bpIdx * stride + bpIndices[0UL];
  yL_1d = (table[bpIdx + 1UL] - table[bpIdx]) * fractions[0UL] + table[bpIdx];
  bpIdx += stride;
  return (((table[bpIdx + 1UL] - table[bpIdx]) * fractions[0UL] + table[bpIdx])
          - yL_1d) * frac + yL_1d;
}

real32_T look1_iflf_binlcpw(real32_T u0, const real32_T bp0[], const real32_T
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
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0UL]) {
    iLeft = 0UL;
    frac = 0.0F;
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
    frac = 1.0F;
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1UL] - table[iLeft]) * frac + table[iLeft];
}

/* Output and update for atomic system: '<Root>/BigDischargePowerAdjust' */
void YoungMa_BigDischargePowerAdjust(void)
{
  real32_T rtb_Add;

  /* Switch: '<S6>/Switch' incorporates:
   *  Constant: '<S1>/Constant4'
   *  Constant: '<S6>/zero'
   *  Constant: '<S7>/Constant'
   *  Constant: '<S8>/Constant'
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  Inport: '<Root>/Tavg'
   *  Logic: '<S6>/and'
   *  RelationalOperator: '<S7>/Compare'
   *  RelationalOperator: '<S8>/Compare'
   *  Sum: '<S1>/Add'
   */
  if (((real32_T)Tavg - 40.0F > -30.0F) && ((real32_T)Tavg - 40.0F < 57.0F)) {
    /* Lookup_n-D: '<S6>/linearizationSOF' incorporates:
     *  Inport: '<Root>/g_socValue'
     */
    rtb_Add = look2_iflf_binlcpw(Can_g_socValue, (real32_T)Tavg - 40.0F,
      (&(SOC_Discharge[0])), (&(T_Discharge[0])), (&(DisChargeCurrentTable[0])),
      YoungMan_LT_ConstP.linearizationSOF_maxIndex, 12UL);
  } else {
    rtb_Add = 0.0F;
  }

  /* End of Switch: '<S6>/Switch' */

  /* Gain: '<S1>/Gain' */
  BiggestDischargeCurt_Model = CAP_CONST_CAL * rtb_Add;
}

/* Output and update for atomic system: '<Root>/ChargeEndSOCAjust' */
void YoungMan_LT_ChargeEndSOCAjust(void)
{
  /* Lookup_n-D: '<S2>/2-D Lookup Table3' incorporates:
   *  Constant: '<S2>/Constant4'
   *  Inport: '<Root>/Tavg'
   *  Inport: '<Root>/g_lowestCellVoltage'
   *  Sum: '<S2>/Add'
   */
  ChargeEndSOCAjustFactor = look2_ifs16bfflftu16n8_PYqzO3tA(g_lowestCellVoltage,
    Tavg - 40, (&(V_CellLowest[0])), (&(T_ChargeEndSOCAjust[0])),
    (&(Factor_ChargeEndSOCAjust[0])), YoungMan_LT_ConstP.uDLookupTable3_maxIndex,
    8UL);
}

/* Output and update for atomic system: '<Root>/FastChrgPowerAjust' */
void YoungMan_LT_FastChrgPowerAjust(void)
{
  real32_T rtb_uDLookupTable3;

  /* Lookup_n-D: '<S3>/2-D Lookup Table3' incorporates:
   *  Constant: '<S3>/Constant4'
   *  DataTypeConversion: '<S3>/Data Type Conversion1'
   *  Inport: '<Root>/Tavg'
   *  Inport: '<Root>/g_socValue'
   *  Sum: '<S3>/Add'
   */
  rtb_uDLookupTable3 = look2_iflf_linlcpw((real32_T)Tavg - 40.0F, Can_g_socValue,
    (&(T_FastCharge[0])), (&(SOC_FastCharge[0])), (&(FastChargeCurrentTable[0])),
    YoungMan_LT_ConstP.uDLookupTable3_maxIndex_g, 16UL);

  /* Gain: '<S3>/Gain' */
  m_askcurrent_Model = CAP_CONST_CAL * rtb_uDLookupTable3;
}

/* Output and update for atomic system: '<Root>/PowerOnSOCAjust' */
void YoungMan_LT_PowerOnSOCAjust(void)
{
  /* Lookup_n-D: '<S4>/1-D Lookup Table' incorporates:
   *  Constant: '<S4>/Constant4'
   *  Inport: '<Root>/g_lowestTemperature'
   *  Sum: '<S4>/Add'
   */
  PowerOnSOCAjustFactor = look1_iflf_binlcpw((real32_T)g_lowestTemperature -
    40.0F, (&(T_PowerOnSOCAjust[0])), (&(Factor_PowerOnSOCAjust[0])), 7UL);
}

/* Output and update for atomic system: '<Root>/PulseRechargePowerAdjust' */
void YoungM_PulseRechargePowerAdjust(void)
{
  real32_T rtb_Add;

  /* Switch: '<S9>/Switch' incorporates:
   *  Constant: '<S10>/Constant'
   *  Constant: '<S11>/Constant'
   *  Constant: '<S5>/Constant4'
   *  Constant: '<S9>/zero'
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  Inport: '<Root>/Tavg'
   *  Logic: '<S9>/and'
   *  RelationalOperator: '<S10>/Compare'
   *  RelationalOperator: '<S11>/Compare'
   *  Sum: '<S5>/Add'
   */
  if (((real32_T)Tavg - 40.0F > -15.0F) && ((real32_T)Tavg - 40.0F < 57.0F)) {
    /* Lookup_n-D: '<S9>/linearizationSOF' incorporates:
     *  Inport: '<Root>/g_socValue'
     */
    rtb_Add = look2_iflf_binlcpw(Can_g_socValue, (real32_T)Tavg - 40.0F,
      (&(SOC_Feedback[0])), (&(T_Facdback[0])), (&(FeedBackCurrentTable[0])),
      YoungMan_LT_ConstP.linearizationSOF_maxIndex_f, 13UL);
  } else {
    rtb_Add = 0.0F;
  }

  /* End of Switch: '<S9>/Switch' */

  /* Gain: '<S5>/Gain' */
  BiggestFeedbackCurt_Model = CAP_CONST_CAL * rtb_Add;
}

/* Model step function */
void YoungMan_LT_step(void)
{
  /* Outputs for Atomic SubSystem: '<Root>/BigDischargePowerAdjust' */
  YoungMa_BigDischargePowerAdjust();

  /* End of Outputs for SubSystem: '<Root>/BigDischargePowerAdjust' */

  /* Outputs for Atomic SubSystem: '<Root>/PulseRechargePowerAdjust' */
  YoungM_PulseRechargePowerAdjust();

  /* End of Outputs for SubSystem: '<Root>/PulseRechargePowerAdjust' */

  /* Outputs for Atomic SubSystem: '<Root>/FastChrgPowerAjust' */
  YoungMan_LT_FastChrgPowerAjust();

  /* End of Outputs for SubSystem: '<Root>/FastChrgPowerAjust' */

  /* Outputs for Atomic SubSystem: '<Root>/ChargeEndSOCAjust' */
  YoungMan_LT_ChargeEndSOCAjust();

  /* End of Outputs for SubSystem: '<Root>/ChargeEndSOCAjust' */

  /* Outputs for Atomic SubSystem: '<Root>/PowerOnSOCAjust' */
  YoungMan_LT_PowerOnSOCAjust();

  /* End of Outputs for SubSystem: '<Root>/PowerOnSOCAjust' */
}

/* Model initialize function */
void YoungMan_LT_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(YoungMan_LT_M, (NULL));

  /* block I/O */

  /* exported global signals */
  BiggestFeedbackCurt_Model = 0.0F;
  PowerOnSOCAjustFactor = 0.0F;
  m_askcurrent_Model = 0.0F;
  ChargeEndSOCAjustFactor = 0.0F;
  BiggestDischargeCurt_Model = 0.0F;
}

/* Model terminate function */
void YoungMan_LT_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

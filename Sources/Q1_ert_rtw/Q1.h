/*
 * File: Q1.h
 *
 * Code generated for Simulink model 'Q1'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Sat Oct 22 16:08:04 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Q1_h_
#define RTW_HEADER_Q1_h_
#include <stddef.h>
#ifndef Q1_COMMON_INCLUDES_
# define Q1_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Q1_COMMON_INCLUDES_ */

#include "Q1_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Parameters (auto storage) */
struct P_Q1_T_ {
  real32_T Capacity[45];               /* Variable: Capacity
                                        * Referenced by: '<Root>/2-D Lookup Table'
                                        */
  real32_T CellVol[5];                 /* Variable: CellVol
                                        * Referenced by: '<Root>/2-D Lookup Table'
                                        */
  real32_T Tem[9];                     /* Variable: Tem
                                        * Referenced by: '<Root>/2-D Lookup Table'
                                        */
  uint32_T DLookupTable_maxIndex[2];   /* Computed Parameter: DLookupTable_maxIndex
                                        * Referenced by: '<Root>/2-D Lookup Table'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Q1_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern P_Q1_T Q1_P;

/* Model entry point functions */
extern void Q1_initialize(void);
extern void Q1_terminate(void);

/* Customized model step function */
extern real32_T Q1_custom(real32_T TemValue, real32_T CellVol);

/* Real-time Model object */
extern RT_MODEL_Q1_T *const Q1_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Q1'
 */
#endif                                 /* RTW_HEADER_Q1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

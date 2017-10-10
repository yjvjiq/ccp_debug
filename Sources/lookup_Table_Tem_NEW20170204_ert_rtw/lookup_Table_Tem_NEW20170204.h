/*
 * File: lookup_Table_Tem_NEW20170204.h
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

#ifndef RTW_HEADER_lookup_Table_Tem_NEW20170204_h_
#define RTW_HEADER_lookup_Table_Tem_NEW20170204_h_
#include <stddef.h>
#include <string.h>
#ifndef lookup_Table_Tem_NEW20170204_COMMON_INCLUDES_
# define lookup_Table_Tem_NEW20170204_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* lookup_Table_Tem_NEW20170204_COMMON_INCLUDES_ */

#include "lookup_Table_Tem_NEW20170204_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  real32_T out_temp;                   /* '<Root>/Chart' */
} B_lookup_Table_Tem_NEW2017020_T;

/* Parameters (auto storage) */
struct P_lookup_Table_Tem_NEW2017020_T_ {
  real32_T lookup_table_tem_NEW20170204[239];/* Variable: lookup_table_tem_NEW20170204
                                              * Referenced by: '<Root>/1-D Lookup Table'
                                              */
  real32_T lookup_table_voltage_NEW20170204[239];/* Variable: lookup_table_voltage_NEW20170204
                                                  * Referenced by: '<Root>/1-D Lookup Table'
                                                  */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<Root>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_lookup_Table_Tem_NEW2_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern P_lookup_Table_Tem_NEW2017020_T lookup_Table_Tem_NEW20170204_P;

/* Block signals (auto storage) */
extern B_lookup_Table_Tem_NEW2017020_T lookup_Table_Tem_NEW20170204_B;

/* Model entry point functions */
extern void lookup_Table_Tem_NEW20170204_initialize(void);
extern void lookup_Table_Tem_NEW20170204_terminate(void);

/* Customized model step function */
extern real32_T lookup_Table_Tem_NEW20170204_custom(real32_T soc);

/* Real-time Model object */
extern RT_MODEL_lookup_Table_Tem_NEW_T *const lookup_Table_Tem_NEW20170204_M;

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
 * '<Root>' : 'lookup_Table_Tem_NEW20170204'
 * '<S1>'   : 'lookup_Table_Tem_NEW20170204/Chart'
 */
#endif                                 /* RTW_HEADER_lookup_Table_Tem_NEW20170204_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

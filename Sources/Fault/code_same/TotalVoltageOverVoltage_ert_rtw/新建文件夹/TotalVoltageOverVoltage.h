/*
 * File: TotalVoltageOverVoltage.h
 *
 * Code generated for Simulink model 'TotalVoltageOverVoltage'.
 *
 * Model version                  : 1.132
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Fri Jun 23 17:06:58 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_TotalVoltageOverVoltage_h_
#define RTW_HEADER_TotalVoltageOverVoltage_h_
#include <stddef.h>
#include <string.h>
#ifndef TotalVoltageOverVoltage_COMMON_INCLUDES_
# define TotalVoltageOverVoltage_COMMON_INCLUDES_
#include <string.h>
#include "rtwtypes.h"
#endif                                 /* TotalVoltageOverVoltage_COMMON_INCLUDES_ */

#include "TotalVoltageOverVoltage_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T F_lev_m;
  uint8_T is_active_c1_TotalVoltageOverVo;/* '<Root>/Chart1' */
  uint8_T t1;                          /* '<Root>/Chart1' */
  uint8_T t2;                          /* '<Root>/Chart1' */
  uint8_T t3;                          /* '<Root>/Chart1' */
  uint8_T t22;                         /* '<Root>/Chart1' */
  uint8_T t33;                         /* '<Root>/Chart1' */
  uint8_T t11;                         /* '<Root>/Chart1' */
  boolean_T F_1;                       /* '<Root>/Chart1' */
  boolean_T F_2;                       /* '<Root>/Chart1' */
  boolean_T F_3;                       /* '<Root>/Chart1' */
} DW_TotalVoltageOverVoltage_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real32_T V0_g;                       /* '<Root>/V0' */
  real32_T V3_i;                       /* '<Root>/V3' */
  uint8_T ModelFlag_d;                 /* '<Root>/ModelFlag' */
} ExtU_TotalVoltageOverVoltage_T;

/* Real-time Model Data Structure */
struct tag_RTM_TotalVoltageOverVolta_T {
  const char_T * volatile errorStatus;
};

/* Block states (auto storage) */
extern DW_TotalVoltageOverVoltage_T TotalVoltageOverVoltage_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_TotalVoltageOverVoltage_T TotalVoltageOverVoltage_U;

/* Model entry point functions */
extern void TotalVoltageOverVoltage_initialize(void);
extern void TotalVoltageOverVoltage_terminate(void);

/* Customized model step function */
extern uint8_T TotalVoltageOverVoltage_custom(real32_T V0, real32_T V3, uint8_T
  ModelFlag);

/* Real-time Model object */
extern RT_MODEL_TotalVoltageOverVolt_T *const TotalVoltageOverVoltage_M;

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
 * '<Root>' : 'TotalVoltageOverVoltage'
 * '<S1>'   : 'TotalVoltageOverVoltage/Chart1'
 */
#endif                                 /* RTW_HEADER_TotalVoltageOverVoltage_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: Supply24V.h
 *
 * Code generated for Simulink model 'Supply24V'.
 *
 * Model version                  : 1.122
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 16 15:55:24 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Supply24V_h_
#define RTW_HEADER_Supply24V_h_
#include <stddef.h>
#include <string.h>
#ifndef Supply24V_COMMON_INCLUDES_
# define Supply24V_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Supply24V_COMMON_INCLUDES_ */

#include "Supply24V_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  uint8_T F_lev_i;                     /* '<Root>/Logic' */
} B_Supply24V_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c3_Supply24V;      /* '<Root>/Logic' */
  uint8_T is_F3;                       /* '<Root>/Logic' */
} DW_Supply24V_T;

/* Real-time Model Data Structure */
struct tag_RTM_Supply24V_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_Supply24V_T Supply24V_B;

/* Block states (auto storage) */
extern DW_Supply24V_T Supply24V_DW;

/* Model entry point functions */
extern void Supply24V_initialize(void);
extern void Supply24V_terminate(void);

/* Customized model step function */
extern uint8_T Supply24V_custom(real32_T V);

/* Real-time Model object */
extern RT_MODEL_Supply24V_T *const Supply24V_M;

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
 * '<Root>' : 'Supply24V'
 * '<S1>'   : 'Supply24V/Logic'
 */
#endif                                 /* RTW_HEADER_Supply24V_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

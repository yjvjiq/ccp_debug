/*
 * File: ChargeDirectionFault.h
 *
 * Code generated for Simulink model 'ChargeDirectionFault'.
 *
 * Model version                  : 1.119
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Fri May 26 10:01:38 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ChargeDirectionFault_h_
#define RTW_HEADER_ChargeDirectionFault_h_
#include <stddef.h>
#include <string.h>
#ifndef ChargeDirectionFault_COMMON_INCLUDES_
# define ChargeDirectionFault_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ChargeDirectionFault_COMMON_INCLUDES_ */

#include "ChargeDirectionFault_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  uint8_T F_lev_i;                     /* '<Root>/Chart' */
} B_ChargeDirectionFault_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c3_ChargeDirectionFau;/* '<Root>/Chart' */
  uint8_T is_F3;                       /* '<Root>/Chart' */
  uint8_T n;                           /* '<Root>/Chart' */
} DW_ChargeDirectionFault_T;

/* Real-time Model Data Structure */
struct tag_RTM_ChargeDirectionFault_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_ChargeDirectionFault_T ChargeDirectionFault_B;

/* Block states (auto storage) */
extern DW_ChargeDirectionFault_T ChargeDirectionFault_DW;

/* Model entry point functions */
extern void ChargeDirectionFault_initialize(void);
extern void ChargeDirectionFault_terminate(void);

/* Customized model step function */
extern uint8_T ChargeDirectionFault_custom(real32_T cur, real32_T Vmin);

/* Real-time Model object */
extern RT_MODEL_ChargeDirectionFault_T *const ChargeDirectionFault_M;

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
 * '<Root>' : 'ChargeDirectionFault'
 * '<S1>'   : 'ChargeDirectionFault/Chart'
 */
#endif                                 /* RTW_HEADER_ChargeDirectionFault_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: BatteryTemperatureLow.h
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

#ifndef RTW_HEADER_BatteryTemperatureLow_h_
#define RTW_HEADER_BatteryTemperatureLow_h_
#include <stddef.h>
#include <string.h>
#ifndef BatteryTemperatureLow_COMMON_INCLUDES_
# define BatteryTemperatureLow_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* BatteryTemperatureLow_COMMON_INCLUDES_ */

#include "BatteryTemperatureLow_types.h"

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
} B_BatteryTemperatureLow_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c3_BatteryTemperature;/* '<Root>/Chart' */
  uint8_T is_F1;                       /* '<Root>/Chart' */
  uint8_T is_F2;                       /* '<Root>/Chart' */
  uint8_T is_F3;                       /* '<Root>/Chart' */
  uint8_T temporalCounter_i1;          /* '<Root>/Chart' */
  uint8_T temporalCounter_i2;          /* '<Root>/Chart' */
  uint8_T temporalCounter_i3;          /* '<Root>/Chart' */
} DW_BatteryTemperatureLow_T;

/* Real-time Model Data Structure */
struct tag_RTM_BatteryTemperatureLow_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_BatteryTemperatureLow_T BatteryTemperatureLow_B;

/* Block states (auto storage) */
extern DW_BatteryTemperatureLow_T BatteryTemperatureLow_DW;

/* Model entry point functions */
extern void BatteryTemperatureLow_initialize(void);
extern void BatteryTemperatureLow_terminate(void);

/* Customized model step function */
extern uint8_T BatteryTemperatureLow_custom(uint8_T Tmin);

/* Real-time Model object */
extern RT_MODEL_BatteryTemperatureLo_T *const BatteryTemperatureLow_M;

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
 * '<Root>' : 'BatteryTemperatureLow'
 * '<S1>'   : 'BatteryTemperatureLow/Chart'
 */
#endif                                 /* RTW_HEADER_BatteryTemperatureLow_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

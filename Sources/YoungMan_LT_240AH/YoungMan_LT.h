/*
 * File: YoungMan_LT.h
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

#ifndef RTW_HEADER_YoungMan_LT_h_
#define RTW_HEADER_YoungMan_LT_h_
#include <stddef.h>
#ifndef YoungMan_LT_COMMON_INCLUDES_
# define YoungMan_LT_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* YoungMan_LT_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_YoungMan_LT_T RT_MODEL_YoungMan_LT_T;

/* Constant parameters (auto storage) */
typedef struct {
  /* Computed Parameter: linearizationSOF_maxIndex
   * Referenced by: '<S6>/linearizationSOF'
   */
  uint32_T linearizationSOF_maxIndex[2];

  /* Computed Parameter: uDLookupTable3_maxIndex
   * Referenced by: '<S2>/2-D Lookup Table3'
   */
  uint32_T uDLookupTable3_maxIndex[2];

  /* Computed Parameter: uDLookupTable3_maxIndex_g
   * Referenced by: '<S3>/2-D Lookup Table3'
   */
  uint32_T uDLookupTable3_maxIndex_g[2];

  /* Computed Parameter: linearizationSOF_maxIndex_f
   * Referenced by: '<S9>/linearizationSOF'
   */
  uint32_T linearizationSOF_maxIndex_f[2];
} ConstP_YoungMan_LT_T;

/* Real-time Model Data Structure */
struct tag_RTM_YoungMan_LT_T {
  const char_T *errorStatus;
};

/* Imported (extern) block signals */
extern real32_T Can_g_socValue;        /* '<Root>/g_socValue'
                                        * Input
                                        */
extern uint8_T Tavg;                   /* '<Root>/Tavg'
                                        * Input
                                        */
extern uint8_T g_lowestTemperature;    /* '<Root>/g_lowestTemperature'
                                        * Input
                                        */
extern real32_T g_lowestCellVoltage;   /* '<Root>/g_lowestCellVoltage'
                                        * Input
                                        */

/* Constant parameters (auto storage) */
extern const ConstP_YoungMan_LT_T YoungMan_LT_ConstP;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T BiggestFeedbackCurt_Model;/* '<S5>/Gain'
                                           * Output
                                           */
extern real32_T PowerOnSOCAjustFactor; /* '<S4>/1-D Lookup Table'
                                        * Input
                                        */
extern real32_T m_askcurrent_Model;    /* '<S3>/Gain'
                                        * Output
                                        */
extern real32_T ChargeEndSOCAjustFactor;/* '<S2>/2-D Lookup Table3'
                                         * Input
                                         */
extern real32_T BiggestDischargeCurt_Model;/* '<S1>/Gain'
                                            * Output
                                            */

/* Model entry point functions */
extern void YoungMan_LT_initialize(void);
extern void YoungMan_LT_step(void);
extern void YoungMan_LT_terminate(void);

/* Exported data declaration */

/* Declaration for custom storage class: Default */
extern real32_T CAP_CONST_CAL;
extern real32_T DisChargeCurrentTable[204];/* maximum discharge current, row: SOC, collumn: T  */
extern uint16_T Factor_ChargeEndSOCAjust[64];
extern real32_T Factor_PowerOnSOCAjust[8];
extern real32_T FastChargeCurrentTable[176];
extern real32_T FeedBackCurrentTable[208];/* maximum discharge current, row: SOC, collumn: T  */
extern real32_T SOC_Discharge[12];
extern real32_T SOC_FastCharge[11];
extern real32_T SOC_Feedback[13];      /* row for max dicharge current table */
extern real32_T T_ChargeEndSOCAjust[8];
extern real32_T T_Discharge[17];       /* collumn for max discharge current table */
extern real32_T T_Facdback[16];
extern real32_T T_FastCharge[16];
extern real32_T T_PowerOnSOCAjust[8];
extern real32_T V_CellLowest[8];

/* Real-time Model object */
extern RT_MODEL_YoungMan_LT_T *const YoungMan_LT_M;

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
 * '<Root>' : 'YoungMan_LT'
 * '<S1>'   : 'YoungMan_LT/BigDischargePowerAdjust'
 * '<S2>'   : 'YoungMan_LT/ChargeEndSOCAjust'
 * '<S3>'   : 'YoungMan_LT/FastChrgPowerAjust'
 * '<S4>'   : 'YoungMan_LT/PowerOnSOCAjust'
 * '<S5>'   : 'YoungMan_LT/PulseRechargePowerAdjust'
 * '<S6>'   : 'YoungMan_LT/BigDischargePowerAdjust/linearizationSOF'
 * '<S7>'   : 'YoungMan_LT/BigDischargePowerAdjust/linearizationSOF/greaterEq'
 * '<S8>'   : 'YoungMan_LT/BigDischargePowerAdjust/linearizationSOF/lessEq'
 * '<S9>'   : 'YoungMan_LT/PulseRechargePowerAdjust/linearizationSOF'
 * '<S10>'  : 'YoungMan_LT/PulseRechargePowerAdjust/linearizationSOF/greaterEq'
 * '<S11>'  : 'YoungMan_LT/PulseRechargePowerAdjust/linearizationSOF/lessEq'
 */
#endif                                 /* RTW_HEADER_YoungMan_LT_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

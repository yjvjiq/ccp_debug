/*
 * File: TotalVoltageOverVoltage.c
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

#include "TotalVoltageOverVoltage.h"
#include "TotalVoltageOverVoltage_private.h"

/* Block states (auto storage) */
DW_TotalVoltageOverVoltage_T TotalVoltageOverVoltage_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_TotalVoltageOverVoltage_T TotalVoltageOverVoltage_U;

/* Real-time model */
RT_MODEL_TotalVoltageOverVolt_T TotalVoltageOverVoltage_M_;
RT_MODEL_TotalVoltageOverVolt_T *const TotalVoltageOverVoltage_M =
  &TotalVoltageOverVoltage_M_;

/* Forward declaration for local functions */
static void TotalVoltageOverVoltage_F(uint8_T *F_lev_p);

/* Function for Chart: '<Root>/Chart1' */
static void TotalVoltageOverVoltage_F(uint8_T *F_lev_p)
{
  boolean_T guard9 = false;
  boolean_T guard10 = false;
  int16_T tmp;

  /* During 'F': '<S1>:263' */
  /* During 'F_1': '<S1>:288' */
  /* Transition: '<S1>:506' */
  if (!TotalVoltageOverVoltage_DW.F_1) {
    /* Transition: '<S1>:242' */
    /* Exit Internal 'F_1': '<S1>:288' */
    /* Entry Internal 'F_1_true': '<S1>:204' */
    /* Transition: '<S1>:415' */
    TotalVoltageOverVoltage_DW.F_1 = false;

    /* Inport: '<Root>/V0' incorporates:
     *  Inport: '<Root>/V3'
     */
    if ((TotalVoltageOverVoltage_U.V0_g >= 744.0F) ||
        (TotalVoltageOverVoltage_U.V3_i >= 744.0F)) {
      /* Transition: '<S1>:402' */
      tmp = TotalVoltageOverVoltage_DW.t1 + 1;
      if (tmp > 255) {
        tmp = 255;
      }

      TotalVoltageOverVoltage_DW.t1 = (uint8_T)tmp;
      if (TotalVoltageOverVoltage_DW.t1 > 10) {
        /* Transition: '<S1>:414' */
        /* Transition: '<S1>:413' */
        TotalVoltageOverVoltage_DW.F_1 = true;
        TotalVoltageOverVoltage_DW.t1 = 0U;

        /* Transition: '<S1>:411' */
        /* Transition: '<S1>:412' */
      } else {
        guard9 = true;
      }
    } else {
      guard9 = true;
    }
  } else {
    /* Transition: '<S1>:203' */
    /* Exit Internal 'F_1': '<S1>:288' */
    /* Entry Internal 'F_1_false': '<S1>:246' */
    /* Transition: '<S1>:472' */
    TotalVoltageOverVoltage_DW.F_1 = true;

    /* Inport: '<Root>/V0' incorporates:
     *  Inport: '<Root>/V3'
     */
    if ((TotalVoltageOverVoltage_U.V0_g < 734.0F) &&
        (TotalVoltageOverVoltage_U.V3_i < 734.0F) &&
        TotalVoltageOverVoltage_DW.F_1) {
      /* Transition: '<S1>:471' */
      tmp = TotalVoltageOverVoltage_DW.t11 + 1;
      if (tmp > 255) {
        tmp = 255;
      }

      TotalVoltageOverVoltage_DW.t11 = (uint8_T)tmp;
      if (TotalVoltageOverVoltage_DW.t11 > 10) {
        /* Transition: '<S1>:474' */
        /* Transition: '<S1>:468' */
        TotalVoltageOverVoltage_DW.F_1 = false;
        TotalVoltageOverVoltage_DW.t11 = 0U;

        /* Transition: '<S1>:476' */
        /* Transition: '<S1>:480' */
      } else {
        guard10 = true;
      }
    } else {
      guard10 = true;
    }
  }

  /* Inport: '<Root>/V0' incorporates:
   *  Inport: '<Root>/V3'
   */
  if (guard10 && ((!((TotalVoltageOverVoltage_U.V0_g < 734.0F) &&
                     (TotalVoltageOverVoltage_U.V3_i < 734.0F))) &&
                  TotalVoltageOverVoltage_DW.F_1)) {
    /* Transition: '<S1>:477' */
    /* Transition: '<S1>:478' */
    TotalVoltageOverVoltage_DW.t11 = 0U;

    /* Transition: '<S1>:480' */
  } else {
    /* Transition: '<S1>:473' */
  }

  if (guard9 && ((!((TotalVoltageOverVoltage_U.V0_g >= 744.0F) ||
                    (TotalVoltageOverVoltage_U.V3_i >= 744.0F))) &&
                 (!TotalVoltageOverVoltage_DW.F_1))) {
    /* Transition: '<S1>:408' */
    /* Transition: '<S1>:405' */
    TotalVoltageOverVoltage_DW.t1 = 0U;

    /* Transition: '<S1>:412' */
  } else {
    /* Transition: '<S1>:404' */
  }

  /* During 'F_2': '<S1>:245' */
  /* Transition: '<S1>:508' */
  guard9 = false;
  guard10 = false;
  if (!TotalVoltageOverVoltage_DW.F_2) {
    /* Transition: '<S1>:287' */
    /* Exit Internal 'F_2': '<S1>:245' */
    /* Entry Internal 'F_2_true': '<S1>:289' */
    /* Transition: '<S1>:376' */
    TotalVoltageOverVoltage_DW.F_2 = false;

    /* Inport: '<Root>/V0' incorporates:
     *  Inport: '<Root>/V3'
     */
    if ((TotalVoltageOverVoltage_U.V0_g >= 754.0F) ||
        (TotalVoltageOverVoltage_U.V3_i >= 754.0F)) {
      /* Transition: '<S1>:377' */
      tmp = TotalVoltageOverVoltage_DW.t2 + 1;
      if (tmp > 255) {
        tmp = 255;
      }

      TotalVoltageOverVoltage_DW.t2 = (uint8_T)tmp;
      if (TotalVoltageOverVoltage_DW.t2 > 10) {
        /* Transition: '<S1>:380' */
        /* Transition: '<S1>:382' */
        TotalVoltageOverVoltage_DW.F_2 = true;
        TotalVoltageOverVoltage_DW.t2 = 0U;

        /* Transition: '<S1>:384' */
        /* Transition: '<S1>:383' */
      } else {
        guard9 = true;
      }
    } else {
      guard9 = true;
    }
  } else {
    /* Transition: '<S1>:310' */
    /* Exit Internal 'F_2': '<S1>:245' */
    /* Entry Internal 'F_2_false': '<S1>:265' */
    /* Transition: '<S1>:425' */
    TotalVoltageOverVoltage_DW.F_2 = true;

    /* Inport: '<Root>/V0' incorporates:
     *  Inport: '<Root>/ModelFlag'
     *  Inport: '<Root>/V3'
     */
    if ((TotalVoltageOverVoltage_U.V0_g < 744.0F) &&
        (TotalVoltageOverVoltage_U.V3_i < 744.0F) &&
        (TotalVoltageOverVoltage_U.ModelFlag_d == 0) &&
        TotalVoltageOverVoltage_DW.F_2) {
      /* Transition: '<S1>:417' */
      tmp = TotalVoltageOverVoltage_DW.t22 + 1;
      if (tmp > 255) {
        tmp = 255;
      }

      TotalVoltageOverVoltage_DW.t22 = (uint8_T)tmp;
      if (TotalVoltageOverVoltage_DW.t22 > 10) {
        /* Transition: '<S1>:428' */
        /* Transition: '<S1>:420' */
        TotalVoltageOverVoltage_DW.F_2 = false;
        TotalVoltageOverVoltage_DW.t22 = 0U;

        /* Transition: '<S1>:427' */
        /* Transition: '<S1>:426' */
      } else {
        guard10 = true;
      }
    } else {
      guard10 = true;
    }
  }

  /* Inport: '<Root>/V0' incorporates:
   *  Inport: '<Root>/ModelFlag'
   *  Inport: '<Root>/V3'
   */
  if (guard10 && ((!((TotalVoltageOverVoltage_U.V0_g < 744.0F) &&
                     (TotalVoltageOverVoltage_U.V3_i < 744.0F) &&
                     (TotalVoltageOverVoltage_U.ModelFlag_d == 0))) &&
                  TotalVoltageOverVoltage_DW.F_2)) {
    /* Transition: '<S1>:430' */
    /* Transition: '<S1>:422' */
    TotalVoltageOverVoltage_DW.t22 = 0U;
    TotalVoltageOverVoltage_DW.t1 = 0U;

    /* Transition: '<S1>:426' */
  } else {
    /* Transition: '<S1>:419' */
  }

  if (guard9 && ((!((TotalVoltageOverVoltage_U.V0_g >= 754.0F) ||
                    (TotalVoltageOverVoltage_U.V3_i >= 754.0F))) &&
                 (!TotalVoltageOverVoltage_DW.F_2))) {
    /* Transition: '<S1>:378' */
    /* Transition: '<S1>:381' */
    TotalVoltageOverVoltage_DW.t2 = 0U;

    /* Transition: '<S1>:383' */
  } else {
    /* Transition: '<S1>:379' */
  }

  /* During 'F_3': '<S1>:286' */
  /* Transition: '<S1>:507' */
  guard9 = false;
  guard10 = false;
  if (!TotalVoltageOverVoltage_DW.F_3) {
    /* Transition: '<S1>:244' */
    /* Exit Internal 'F_3': '<S1>:286' */
    /* Entry Internal 'F_3_true': '<S1>:332' */
    /* Transition: '<S1>:392' */
    TotalVoltageOverVoltage_DW.F_3 = false;

    /* Inport: '<Root>/V0' incorporates:
     *  Inport: '<Root>/V3'
     */
    if ((TotalVoltageOverVoltage_U.V0_g >= 765.0F) ||
        (TotalVoltageOverVoltage_U.V3_i >= 765.0F)) {
      /* Transition: '<S1>:393' */
      tmp = TotalVoltageOverVoltage_DW.t3 + 1;
      if (tmp > 255) {
        tmp = 255;
      }

      TotalVoltageOverVoltage_DW.t3 = (uint8_T)tmp;
      if (TotalVoltageOverVoltage_DW.t3 > 10) {
        /* Transition: '<S1>:396' */
        /* Transition: '<S1>:398' */
        TotalVoltageOverVoltage_DW.F_3 = true;
        TotalVoltageOverVoltage_DW.t3 = 0U;

        /* Transition: '<S1>:400' */
        /* Transition: '<S1>:399' */
      } else {
        guard9 = true;
      }
    } else {
      guard9 = true;
    }
  } else {
    /* Transition: '<S1>:243' */
    /* Exit Internal 'F_3': '<S1>:286' */
    /* Entry Internal 'F_3_false': '<S1>:311' */
    /* Transition: '<S1>:439' */
    TotalVoltageOverVoltage_DW.F_3 = true;

    /* Inport: '<Root>/V0' incorporates:
     *  Inport: '<Root>/ModelFlag'
     *  Inport: '<Root>/V3'
     */
    if ((TotalVoltageOverVoltage_U.V0_g < 754.0F) &&
        (TotalVoltageOverVoltage_U.V3_i < 754.0F) &&
        (TotalVoltageOverVoltage_U.ModelFlag_d == 0) &&
        TotalVoltageOverVoltage_DW.F_3) {
      /* Transition: '<S1>:437' */
      tmp = TotalVoltageOverVoltage_DW.t33 + 1;
      if (tmp > 255) {
        tmp = 255;
      }

      TotalVoltageOverVoltage_DW.t33 = (uint8_T)tmp;
      if (TotalVoltageOverVoltage_DW.t33 > 10) {
        /* Transition: '<S1>:440' */
        /* Transition: '<S1>:446' */
        TotalVoltageOverVoltage_DW.F_3 = false;
        TotalVoltageOverVoltage_DW.t33 = 0U;

        /* Transition: '<S1>:444' */
        /* Transition: '<S1>:445' */
      } else {
        guard10 = true;
      }
    } else {
      guard10 = true;
    }
  }

  /* Inport: '<Root>/V0' incorporates:
   *  Inport: '<Root>/ModelFlag'
   *  Inport: '<Root>/V3'
   */
  if (guard10 && ((!((TotalVoltageOverVoltage_U.V0_g < 754.0F) &&
                     (TotalVoltageOverVoltage_U.V3_i < 754.0F) &&
                     (TotalVoltageOverVoltage_U.ModelFlag_d == 0))) &&
                  TotalVoltageOverVoltage_DW.F_3)) {
    /* Transition: '<S1>:435' */
    /* Transition: '<S1>:447' */
    TotalVoltageOverVoltage_DW.t33 = 0U;
    TotalVoltageOverVoltage_DW.t1 = 0U;
    TotalVoltageOverVoltage_DW.t2 = 0U;

    /* Transition: '<S1>:445' */
  } else {
    /* Transition: '<S1>:434' */
  }

  if (guard9 && ((!((TotalVoltageOverVoltage_U.V0_g >= 765.0F) ||
                    (TotalVoltageOverVoltage_U.V3_i >= 765.0F))) &&
                 (!TotalVoltageOverVoltage_DW.F_3))) {
    /* Transition: '<S1>:394' */
    /* Transition: '<S1>:397' */
    TotalVoltageOverVoltage_DW.t3 = 0U;

    /* Transition: '<S1>:399' */
  } else {
    /* Transition: '<S1>:395' */
  }

  /* During 'F_0': '<S1>:518' */
  /* Transition: '<S1>:517' */
  /* Exit Internal 'F_0': '<S1>:518' */
  /* Entry Internal 'F_0_true': '<S1>:519' */
  /* Transition: '<S1>:530' */
  if (TotalVoltageOverVoltage_DW.F_3) {
    /* Transition: '<S1>:532' */
    /* Transition: '<S1>:537' */
    TotalVoltageOverVoltage_DW.F_1 = false;
    TotalVoltageOverVoltage_DW.F_2 = false;
    *F_lev_p = 3U;

    /* Transition: '<S1>:544' */
    /* Transition: '<S1>:543' */
    /* Transition: '<S1>:542' */
    /* Transition: '<S1>:541' */
  } else if (TotalVoltageOverVoltage_DW.F_2) {
    /* Transition: '<S1>:533' */
    /* Transition: '<S1>:538' */
    TotalVoltageOverVoltage_DW.F_1 = false;
    *F_lev_p = 2U;

    /* Transition: '<S1>:543' */
    /* Transition: '<S1>:542' */
    /* Transition: '<S1>:541' */
  } else if (TotalVoltageOverVoltage_DW.F_1) {
    /* Transition: '<S1>:534' */
    /* Transition: '<S1>:539' */
    *F_lev_p = 1U;

    /* Transition: '<S1>:542' */
    /* Transition: '<S1>:541' */
  } else {
    /* Transition: '<S1>:536' */
    *F_lev_p = 0U;
  }
}

/* Model step function */
uint8_T TotalVoltageOverVoltage_custom(real32_T V0, real32_T V3, uint8_T
  ModelFlag)
{
  boolean_T guard5 = false;
  boolean_T guard6 = false;
  uint8_T F_lev_p;
  int16_T tmp;

  /* specified return value */
  uint8_T F_lev;

  /* Copy value for root inport '<Root>/V0' since it is accessed globally */
  TotalVoltageOverVoltage_U.V0_g = V0;

  /* Copy value for root inport '<Root>/V3' since it is accessed globally */
  TotalVoltageOverVoltage_U.V3_i = V3;

  /* Copy value for root inport '<Root>/ModelFlag' since it is accessed globally */
  TotalVoltageOverVoltage_U.ModelFlag_d = ModelFlag;

  /* Chart: '<Root>/Chart1' incorporates:
   *  Inport: '<Root>/ModelFlag'
   *  Inport: '<Root>/V0'
   *  Inport: '<Root>/V3'
   */
  /* Gateway: Chart1 */
  /* During: Chart1 */
  if (TotalVoltageOverVoltage_DW.is_active_c1_TotalVoltageOverVo == 0U) {
    /* Entry: Chart1 */
    TotalVoltageOverVoltage_DW.is_active_c1_TotalVoltageOverVo = 1U;

    /* Entry Internal: Chart1 */
    /* Transition: '<S1>:202' */
    /* Entry Internal 'F': '<S1>:263' */
    /* Entry Internal 'F_1': '<S1>:288' */
    /* Transition: '<S1>:505' */
    if (!TotalVoltageOverVoltage_DW.F_1) {
      /* Transition: '<S1>:242' */
      /* Entry Internal 'F_1_true': '<S1>:204' */
      /* Transition: '<S1>:415' */
      TotalVoltageOverVoltage_DW.F_1 = false;
      if ((TotalVoltageOverVoltage_U.V0_g >= 744.0F) ||
          (TotalVoltageOverVoltage_U.V3_i >= 744.0F)) {
        /* Transition: '<S1>:402' */
        tmp = TotalVoltageOverVoltage_DW.t1 + 1;
        if (tmp > 255) {
          tmp = 255;
        }

        TotalVoltageOverVoltage_DW.t1 = (uint8_T)tmp;
        if (TotalVoltageOverVoltage_DW.t1 > 10) {
          /* Transition: '<S1>:414' */
          /* Transition: '<S1>:413' */
          TotalVoltageOverVoltage_DW.F_1 = true;
          TotalVoltageOverVoltage_DW.t1 = 0U;

          /* Transition: '<S1>:411' */
          /* Transition: '<S1>:412' */
        } else {
          guard5 = true;
        }
      } else {
        guard5 = true;
      }
    } else {
      /* Transition: '<S1>:203' */
      /* Entry Internal 'F_1_false': '<S1>:246' */
      /* Transition: '<S1>:472' */
      TotalVoltageOverVoltage_DW.F_1 = true;
      if ((TotalVoltageOverVoltage_U.V0_g < 734.0F) &&
          (TotalVoltageOverVoltage_U.V3_i < 734.0F) &&
          TotalVoltageOverVoltage_DW.F_1) {
        /* Transition: '<S1>:471' */
        tmp = TotalVoltageOverVoltage_DW.t11 + 1;
        if (tmp > 255) {
          tmp = 255;
        }

        TotalVoltageOverVoltage_DW.t11 = (uint8_T)tmp;
        if (TotalVoltageOverVoltage_DW.t11 > 10) {
          /* Transition: '<S1>:474' */
          /* Transition: '<S1>:468' */
          TotalVoltageOverVoltage_DW.F_1 = false;
          TotalVoltageOverVoltage_DW.t11 = 0U;

          /* Transition: '<S1>:476' */
          /* Transition: '<S1>:480' */
        } else {
          guard6 = true;
        }
      } else {
        guard6 = true;
      }
    }

    if (guard6 && ((!((TotalVoltageOverVoltage_U.V0_g < 734.0F) &&
                      (TotalVoltageOverVoltage_U.V3_i < 734.0F))) &&
                   TotalVoltageOverVoltage_DW.F_1)) {
      /* Transition: '<S1>:477' */
      /* Transition: '<S1>:478' */
      TotalVoltageOverVoltage_DW.t11 = 0U;

      /* Transition: '<S1>:480' */
    } else {
      /* Transition: '<S1>:473' */
    }

    if (guard5 && ((!((TotalVoltageOverVoltage_U.V0_g >= 744.0F) ||
                      (TotalVoltageOverVoltage_U.V3_i >= 744.0F))) &&
                   (!TotalVoltageOverVoltage_DW.F_1))) {
      /* Transition: '<S1>:408' */
      /* Transition: '<S1>:405' */
      TotalVoltageOverVoltage_DW.t1 = 0U;

      /* Transition: '<S1>:412' */
    } else {
      /* Transition: '<S1>:404' */
    }

    /* Entry Internal 'F_2': '<S1>:245' */
    /* Transition: '<S1>:503' */
    guard5 = false;
    guard6 = false;
    if (!TotalVoltageOverVoltage_DW.F_2) {
      /* Transition: '<S1>:287' */
      /* Entry Internal 'F_2_true': '<S1>:289' */
      /* Transition: '<S1>:376' */
      TotalVoltageOverVoltage_DW.F_2 = false;
      if ((TotalVoltageOverVoltage_U.V0_g >= 754.0F) ||
          (TotalVoltageOverVoltage_U.V3_i >= 754.0F)) {
        /* Transition: '<S1>:377' */
        tmp = TotalVoltageOverVoltage_DW.t2 + 1;
        if (tmp > 255) {
          tmp = 255;
        }

        TotalVoltageOverVoltage_DW.t2 = (uint8_T)tmp;
        if (TotalVoltageOverVoltage_DW.t2 > 10) {
          /* Transition: '<S1>:380' */
          /* Transition: '<S1>:382' */
          TotalVoltageOverVoltage_DW.F_2 = true;
          TotalVoltageOverVoltage_DW.t2 = 0U;

          /* Transition: '<S1>:384' */
          /* Transition: '<S1>:383' */
        } else {
          guard5 = true;
        }
      } else {
        guard5 = true;
      }
    } else {
      /* Transition: '<S1>:310' */
      /* Entry Internal 'F_2_false': '<S1>:265' */
      /* Transition: '<S1>:425' */
      TotalVoltageOverVoltage_DW.F_2 = true;
      if ((TotalVoltageOverVoltage_U.V0_g < 744.0F) &&
          (TotalVoltageOverVoltage_U.V3_i < 744.0F) &&
          (TotalVoltageOverVoltage_U.ModelFlag_d == 0) &&
          TotalVoltageOverVoltage_DW.F_2) {
        /* Transition: '<S1>:417' */
        tmp = TotalVoltageOverVoltage_DW.t22 + 1;
        if (tmp > 255) {
          tmp = 255;
        }

        TotalVoltageOverVoltage_DW.t22 = (uint8_T)tmp;
        if (TotalVoltageOverVoltage_DW.t22 > 10) {
          /* Transition: '<S1>:428' */
          /* Transition: '<S1>:420' */
          TotalVoltageOverVoltage_DW.F_2 = false;
          TotalVoltageOverVoltage_DW.t22 = 0U;

          /* Transition: '<S1>:427' */
          /* Transition: '<S1>:426' */
        } else {
          guard6 = true;
        }
      } else {
        guard6 = true;
      }
    }

    if (guard6 && ((!((TotalVoltageOverVoltage_U.V0_g < 744.0F) &&
                      (TotalVoltageOverVoltage_U.V3_i < 744.0F) &&
                      (TotalVoltageOverVoltage_U.ModelFlag_d == 0))) &&
                   TotalVoltageOverVoltage_DW.F_2)) {
      /* Transition: '<S1>:430' */
      /* Transition: '<S1>:422' */
      TotalVoltageOverVoltage_DW.t22 = 0U;
      TotalVoltageOverVoltage_DW.t1 = 0U;

      /* Transition: '<S1>:426' */
    } else {
      /* Transition: '<S1>:419' */
    }

    if (guard5 && ((!((TotalVoltageOverVoltage_U.V0_g >= 754.0F) ||
                      (TotalVoltageOverVoltage_U.V3_i >= 754.0F))) &&
                   (!TotalVoltageOverVoltage_DW.F_2))) {
      /* Transition: '<S1>:378' */
      /* Transition: '<S1>:381' */
      TotalVoltageOverVoltage_DW.t2 = 0U;

      /* Transition: '<S1>:383' */
    } else {
      /* Transition: '<S1>:379' */
    }

    /* Entry Internal 'F_3': '<S1>:286' */
    /* Transition: '<S1>:504' */
    guard5 = false;
    guard6 = false;
    if (!TotalVoltageOverVoltage_DW.F_3) {
      /* Transition: '<S1>:244' */
      /* Entry Internal 'F_3_true': '<S1>:332' */
      /* Transition: '<S1>:392' */
      TotalVoltageOverVoltage_DW.F_3 = false;
      if ((TotalVoltageOverVoltage_U.V0_g >= 765.0F) ||
          (TotalVoltageOverVoltage_U.V3_i >= 765.0F)) {
        /* Transition: '<S1>:393' */
        tmp = TotalVoltageOverVoltage_DW.t3 + 1;
        if (tmp > 255) {
          tmp = 255;
        }

        TotalVoltageOverVoltage_DW.t3 = (uint8_T)tmp;
        if (TotalVoltageOverVoltage_DW.t3 > 10) {
          /* Transition: '<S1>:396' */
          /* Transition: '<S1>:398' */
          TotalVoltageOverVoltage_DW.F_3 = true;
          TotalVoltageOverVoltage_DW.t3 = 0U;

          /* Transition: '<S1>:400' */
          /* Transition: '<S1>:399' */
        } else {
          guard5 = true;
        }
      } else {
        guard5 = true;
      }
    } else {
      /* Transition: '<S1>:243' */
      /* Entry Internal 'F_3_false': '<S1>:311' */
      /* Transition: '<S1>:439' */
      TotalVoltageOverVoltage_DW.F_3 = true;
      if ((TotalVoltageOverVoltage_U.V0_g < 754.0F) &&
          (TotalVoltageOverVoltage_U.V3_i < 754.0F) &&
          (TotalVoltageOverVoltage_U.ModelFlag_d == 0) &&
          TotalVoltageOverVoltage_DW.F_3) {
        /* Transition: '<S1>:437' */
        tmp = TotalVoltageOverVoltage_DW.t33 + 1;
        if (tmp > 255) {
          tmp = 255;
        }

        TotalVoltageOverVoltage_DW.t33 = (uint8_T)tmp;
        if (TotalVoltageOverVoltage_DW.t33 > 10) {
          /* Transition: '<S1>:440' */
          /* Transition: '<S1>:446' */
          TotalVoltageOverVoltage_DW.F_3 = false;
          TotalVoltageOverVoltage_DW.t33 = 0U;

          /* Transition: '<S1>:444' */
          /* Transition: '<S1>:445' */
        } else {
          guard6 = true;
        }
      } else {
        guard6 = true;
      }
    }

    if (guard6 && ((!((TotalVoltageOverVoltage_U.V0_g < 754.0F) &&
                      (TotalVoltageOverVoltage_U.V3_i < 754.0F) &&
                      (TotalVoltageOverVoltage_U.ModelFlag_d == 0))) &&
                   TotalVoltageOverVoltage_DW.F_3)) {
      /* Transition: '<S1>:435' */
      /* Transition: '<S1>:447' */
      TotalVoltageOverVoltage_DW.t33 = 0U;
      TotalVoltageOverVoltage_DW.t1 = 0U;
      TotalVoltageOverVoltage_DW.t2 = 0U;

      /* Transition: '<S1>:445' */
    } else {
      /* Transition: '<S1>:434' */
    }

    if (guard5 && ((!((TotalVoltageOverVoltage_U.V0_g >= 765.0F) ||
                      (TotalVoltageOverVoltage_U.V3_i >= 765.0F))) &&
                   (!TotalVoltageOverVoltage_DW.F_3))) {
      /* Transition: '<S1>:394' */
      /* Transition: '<S1>:397' */
      TotalVoltageOverVoltage_DW.t3 = 0U;

      /* Transition: '<S1>:399' */
    } else {
      /* Transition: '<S1>:395' */
    }

    /* Entry Internal 'F_0': '<S1>:518' */
    /* Entry Internal 'F_0_true': '<S1>:519' */
    /* Transition: '<S1>:530' */
    if (TotalVoltageOverVoltage_DW.F_3) {
      /* Transition: '<S1>:532' */
      /* Transition: '<S1>:537' */
      TotalVoltageOverVoltage_DW.F_1 = false;
      TotalVoltageOverVoltage_DW.F_2 = false;
      F_lev_p = 3U;

      /* Transition: '<S1>:544' */
      /* Transition: '<S1>:543' */
      /* Transition: '<S1>:542' */
      /* Transition: '<S1>:541' */
    } else if (TotalVoltageOverVoltage_DW.F_2) {
      /* Transition: '<S1>:533' */
      /* Transition: '<S1>:538' */
      TotalVoltageOverVoltage_DW.F_1 = false;
      F_lev_p = 2U;

      /* Transition: '<S1>:543' */
      /* Transition: '<S1>:542' */
      /* Transition: '<S1>:541' */
    } else if (TotalVoltageOverVoltage_DW.F_1) {
      /* Transition: '<S1>:534' */
      /* Transition: '<S1>:539' */
      F_lev_p = 1U;

      /* Transition: '<S1>:542' */
      /* Transition: '<S1>:541' */
    } else {
      /* Transition: '<S1>:536' */
      F_lev_p = 0U;
    }
  } else {
    TotalVoltageOverVoltage_F(&F_lev_p);
  }

  /* End of Chart: '<Root>/Chart1' */

  /* Outport: '<Root>/F_Level_BOV' */
  F_lev = F_lev_p;
  return F_lev;
}

/* Model initialize function */
void TotalVoltageOverVoltage_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(TotalVoltageOverVoltage_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&TotalVoltageOverVoltage_DW, 0,
                sizeof(DW_TotalVoltageOverVoltage_T));

  /* external inputs */
  (void) memset((void *)&TotalVoltageOverVoltage_U, 0,
                sizeof(ExtU_TotalVoltageOverVoltage_T));

  /* Machine initializer */
  TotalVoltageOverVoltage_DW.F_lev_m = 0.0;

  /* SystemInitialize for Chart: '<Root>/Chart1' */
  TotalVoltageOverVoltage_DW.is_active_c1_TotalVoltageOverVo = 0U;
  TotalVoltageOverVoltage_DW.t1 = 0U;
  TotalVoltageOverVoltage_DW.t2 = 0U;
  TotalVoltageOverVoltage_DW.t3 = 0U;
  TotalVoltageOverVoltage_DW.t22 = 0U;
  TotalVoltageOverVoltage_DW.t33 = 0U;
  TotalVoltageOverVoltage_DW.t11 = 0U;
  TotalVoltageOverVoltage_DW.F_1 = false;
  TotalVoltageOverVoltage_DW.F_2 = false;
  TotalVoltageOverVoltage_DW.F_3 = false;
}

/* Model terminate function */
void TotalVoltageOverVoltage_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

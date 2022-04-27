/*
 * rosTxTest_mod.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "rosTxTest_mod".
 *
 * Model version              : 1.4
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C++ source code generated on : Sun Apr 24 16:36:28 2022
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "rosTxTest_mod.h"
#include "rtwtypes.h"
#include <cmath>
#include "rosTxTest_mod_types.h"
#include "rosTxTest_mod_private.h"
#include "rosTxTest_mod_dt.h"

/* Block signals (default storage) */
B_rosTxTest_mod_T rosTxTest_mod_B;

/* Block states (default storage) */
DW_rosTxTest_mod_T rosTxTest_mod_DW;

/* Real-time model */
RT_MODEL_rosTxTest_mod_T rosTxTest_mod_M_{ };

RT_MODEL_rosTxTest_mod_T *const rosTxTest_mod_M{ &rosTxTest_mod_M_ };

/* Model step function */
void rosTxTest_mod_step(void)
{
  SL_Bus_rosTxTest_mod_std_msgs_Float64 rtb_BusAssignment;
  real_T lastSin_tmp;

  /* Sin: '<Root>/Sine Wave' */
  if (rosTxTest_mod_DW.systemEnable != 0) {
    lastSin_tmp = rosTxTest_mod_P.SineWave_Freq *
      rosTxTest_mod_M->Timing.taskTime0;
    rosTxTest_mod_DW.lastSin = std::sin(lastSin_tmp);
    rosTxTest_mod_DW.lastCos = std::cos(lastSin_tmp);
    rosTxTest_mod_DW.systemEnable = 0;
  }

  /* Sin: '<Root>/Sine Wave' */
  rosTxTest_mod_B.SineWave = ((rosTxTest_mod_DW.lastSin *
    rosTxTest_mod_P.SineWave_PCos + rosTxTest_mod_DW.lastCos *
    rosTxTest_mod_P.SineWave_PSin) * rosTxTest_mod_P.SineWave_HCos +
    (rosTxTest_mod_DW.lastCos * rosTxTest_mod_P.SineWave_PCos -
     rosTxTest_mod_DW.lastSin * rosTxTest_mod_P.SineWave_PSin) *
    rosTxTest_mod_P.SineWave_Hsin) * rosTxTest_mod_P.SineWave_Amp +
    rosTxTest_mod_P.SineWave_Bias;

  /* BusAssignment: '<Root>/Bus Assignment' */
  rtb_BusAssignment.Data = rosTxTest_mod_B.SineWave;

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_rosTxTest_mod_3.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */

  /* Update for Sin: '<Root>/Sine Wave' */
  lastSin_tmp = rosTxTest_mod_DW.lastSin;
  rosTxTest_mod_DW.lastSin = rosTxTest_mod_DW.lastSin *
    rosTxTest_mod_P.SineWave_HCos + rosTxTest_mod_DW.lastCos *
    rosTxTest_mod_P.SineWave_Hsin;
  rosTxTest_mod_DW.lastCos = rosTxTest_mod_DW.lastCos *
    rosTxTest_mod_P.SineWave_HCos - lastSin_tmp * rosTxTest_mod_P.SineWave_Hsin;

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.01s, 0.0s] */
    rtExtModeUpload(0, (real_T)rosTxTest_mod_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.01s, 0.0s] */
    if ((rtmGetTFinal(rosTxTest_mod_M)!=-1) &&
        !((rtmGetTFinal(rosTxTest_mod_M)-rosTxTest_mod_M->Timing.taskTime0) >
          rosTxTest_mod_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(rosTxTest_mod_M, "Simulation finished");
    }

    if (rtmGetStopRequested(rosTxTest_mod_M)) {
      rtmSetErrorStatus(rosTxTest_mod_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++rosTxTest_mod_M->Timing.clockTick0)) {
    ++rosTxTest_mod_M->Timing.clockTickH0;
  }

  rosTxTest_mod_M->Timing.taskTime0 = rosTxTest_mod_M->Timing.clockTick0 *
    rosTxTest_mod_M->Timing.stepSize0 + rosTxTest_mod_M->Timing.clockTickH0 *
    rosTxTest_mod_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void rosTxTest_mod_initialize(void)
{
  /* Registration code */
  rtmSetTFinal(rosTxTest_mod_M, -1);
  rosTxTest_mod_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  rosTxTest_mod_M->Sizes.checksums[0] = (1779167363U);
  rosTxTest_mod_M->Sizes.checksums[1] = (3471057675U);
  rosTxTest_mod_M->Sizes.checksums[2] = (1760505759U);
  rosTxTest_mod_M->Sizes.checksums[3] = (2245105599U);

  {
    static const sysRanDType rtAlwaysEnabled{ SUBSYS_RAN_BC_ENABLE };

    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    rosTxTest_mod_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(rosTxTest_mod_M->extModeInfo,
      &rosTxTest_mod_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(rosTxTest_mod_M->extModeInfo,
                        rosTxTest_mod_M->Sizes.checksums);
    rteiSetTPtr(rosTxTest_mod_M->extModeInfo, rtmGetTPtr(rosTxTest_mod_M));
  }

  /* block I/O */
  (void) std::memset((static_cast<void *>(&rosTxTest_mod_B)), 0,
                     sizeof(B_rosTxTest_mod_T));

  /* states (dwork) */
  (void) std::memset(static_cast<void *>(&rosTxTest_mod_DW), 0,
                     sizeof(DW_rosTxTest_mod_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    rosTxTest_mod_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 24;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    static const char_T tmp[9]{ '/', 'm', 'a', 't', 'l', 'a', 'b', 'T', 'x' };

    char_T b_zeroDelimTopic[10];

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    rosTxTest_mod_DW.obj.matlabCodegenIsDeleted = false;
    rosTxTest_mod_DW.objisempty = true;
    rosTxTest_mod_DW.obj.isInitialized = 1;
    for (int32_T i{0}; i < 9; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[9] = '\x00';
    Pub_rosTxTest_mod_3.createPublisher(&b_zeroDelimTopic[0], 1);
    rosTxTest_mod_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */
  }

  /* Enable for Sin: '<Root>/Sine Wave' */
  rosTxTest_mod_DW.systemEnable = 1;
}

/* Model terminate function */
void rosTxTest_mod_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  if (!rosTxTest_mod_DW.obj.matlabCodegenIsDeleted) {
    rosTxTest_mod_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S2>/SinkBlock' */
  /* End of Terminate for SubSystem: '<Root>/Publish' */
}

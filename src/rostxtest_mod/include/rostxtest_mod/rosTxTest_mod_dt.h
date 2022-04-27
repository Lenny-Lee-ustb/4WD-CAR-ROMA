/*
 * rosTxTest_mod_dt.h
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

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[]{
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(int32_T),
  sizeof(int64_T),
  sizeof(uint64_T),
  sizeof(SL_Bus_rosTxTest_mod_std_msgs_Float64),
  sizeof(ros_slroscpp_internal_block_P_T),
  sizeof(uint64_T),
  sizeof(int64_T),
  sizeof(char_T),
  sizeof(uchar_T),
  sizeof(time_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[]{
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "physical_connection",
  "int64_T",
  "uint64_T",
  "SL_Bus_rosTxTest_mod_std_msgs_Float64",
  "ros_slroscpp_internal_block_P_T",
  "uint64_T",
  "int64_T",
  "char_T",
  "uchar_T",
  "time_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[]{
  { (char_T *)(&rosTxTest_mod_B.SineWave), 0, 0, 1 }
  ,

  { (char_T *)(&rosTxTest_mod_DW.obj), 18, 0, 1 },

  { (char_T *)(&rosTxTest_mod_DW.lastSin), 0, 0, 2 },

  { (char_T *)(&rosTxTest_mod_DW.systemEnable), 6, 0, 1 },

  { (char_T *)(&rosTxTest_mod_DW.objisempty), 8, 0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable{
  5U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[]{
  { (char_T *)(&rosTxTest_mod_P.Constant_Value), 17, 0, 1 },

  { (char_T *)(&rosTxTest_mod_P.SineWave_Amp), 0, 0, 7 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable{
  2U,
  rtPTransitions
};

/* [EOF] rosTxTest_mod_dt.h */

/*
 * pro_upper_controller_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "pro_upper_controller".
 *
 * Model version              : 1.10
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C++ source code generated on : Wed Apr 27 12:54:17 2022
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
  sizeof(SL_Bus_pro_upper_controller_geometry_msgs_Vector3),
  sizeof(SL_Bus_pro_upper_controller_geometry_msgs_Twist),
  sizeof(SL_Bus_pro_upper_controller_ros_time_Time),
  sizeof(SL_Bus_ROSVariableLengthArrayInfo),
  sizeof(SL_Bus_pro_upper_controller_std_msgs_Header),
  sizeof(SL_Bus_pro_upper_controller_geometry_msgs_Point),
  sizeof(SL_Bus_pro_upper_controller_geometry_msgs_Quaternion),
  sizeof(SL_Bus_pro_upper_controller_geometry_msgs_Pose),
  sizeof(SL_Bus_pro_upper_controller_PoseWithCovariance_mdq9bn),
  sizeof(SL_Bus_pro_upper_controller_TwistWithCovariance_j1foob),
  sizeof(SL_Bus_pro_upper_controller_nav_msgs_Odometry),
  sizeof(SL_Bus_pro_upper_controller_geometry_msgs_PoseStamped),
  sizeof(SL_Bus_pro_upper_controller_nav_msgs_Path),
  sizeof(ros_slroscpp_internal_block_P_T),
  sizeof(ros_slroscpp_internal_block_S_T),
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
  "SL_Bus_pro_upper_controller_geometry_msgs_Vector3",
  "SL_Bus_pro_upper_controller_geometry_msgs_Twist",
  "SL_Bus_pro_upper_controller_ros_time_Time",
  "SL_Bus_ROSVariableLengthArrayInfo",
  "SL_Bus_pro_upper_controller_std_msgs_Header",
  "SL_Bus_pro_upper_controller_geometry_msgs_Point",
  "SL_Bus_pro_upper_controller_geometry_msgs_Quaternion",
  "SL_Bus_pro_upper_controller_geometry_msgs_Pose",
  "SL_Bus_pro_upper_controller_PoseWithCovariance_mdq9bn",
  "SL_Bus_pro_upper_controller_TwistWithCovariance_j1foob",
  "SL_Bus_pro_upper_controller_nav_msgs_Odometry",
  "SL_Bus_pro_upper_controller_geometry_msgs_PoseStamped",
  "SL_Bus_pro_upper_controller_nav_msgs_Path",
  "ros_slroscpp_internal_block_P_T",
  "ros_slroscpp_internal_block_S_T",
  "uint64_T",
  "int64_T",
  "char_T",
  "uchar_T",
  "time_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[]{
  { (char_T *)(&pro_upper_controller_B.In1), 27, 0, 1 },

  { (char_T *)(&pro_upper_controller_B.Multiply), 0, 0, 2 }
  ,

  { (char_T *)(&pro_upper_controller_DW.obj), 30, 0, 1 },

  { (char_T *)(&pro_upper_controller_DW.obj_d), 31, 0, 2 },

  { (char_T *)(&pro_upper_controller_DW.FromWorkspace4_PWORK.TimePtr), 11, 0, 10
  },

  { (char_T *)(&pro_upper_controller_DW.FromWorkspace4_IWORK.PrevIndex), 10, 0,
    8 },

  { (char_T *)(&pro_upper_controller_DW.EnabledSubsystem_SubsysRanBC), 2, 0, 5 },

  { (char_T *)(&pro_upper_controller_DW.objisempty), 8, 0, 3 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable{
  8U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[]{
  { (char_T *)(&pro_upper_controller_P.a), 0, 0, 4 },

  { (char_T *)(&pro_upper_controller_P.Out1_Y0), 29, 0, 1 },

  { (char_T *)(&pro_upper_controller_P.Constant_Value), 29, 0, 1 },

  { (char_T *)(&pro_upper_controller_P.Out1_Y0_e), 27, 0, 1 },

  { (char_T *)(&pro_upper_controller_P.Constant_Value_f), 27, 0, 1 },

  { (char_T *)(&pro_upper_controller_P.Constant_Value_h), 18, 0, 1 },

  { (char_T *)(&pro_upper_controller_P.Constant_Value_fm), 0, 0, 5 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable{
  7U,
  rtPTransitions
};

/* [EOF] pro_upper_controller_dt.h */

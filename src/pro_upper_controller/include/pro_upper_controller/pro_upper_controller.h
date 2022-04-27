/*
 * pro_upper_controller.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "pro_upper_controller".
 *
 * Model version              : 1.9
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C++ source code generated on : Tue Apr 26 17:16:28 2022
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#ifndef RTW_HEADER_pro_upper_controller_h_
#define RTW_HEADER_pro_upper_controller_h_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "dt_info.h"
#include "ext_work.h"
#include "slros_initialize.h"
#include "pro_upper_controller_types.h"
#include <cmath>
#include <cfloat>
#include <cstring>

extern "C" {

#include "rtGetInf.h"

}
  extern "C"
{

#include "rt_nonfinite.h"

}

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Block signals (default storage) */
struct B_pro_upper_controller_T {
  real_T FromWorkspace7[4999];         /* '<S2>/From Workspace7' */
  real_T FromWorkspace6[4999];         /* '<S2>/From Workspace6' */
  real_T FromWorkspace5[4999];         /* '<S2>/From Workspace5' */
  real_T FromWorkspace4[4999];         /* '<S2>/From Workspace4' */
  real_T FromWorkspace3[2999];         /* '<S3>/From Workspace3' */
  real_T FromWorkspace2[2999];         /* '<S3>/From Workspace2' */
  real_T FromWorkspace1[2999];         /* '<S3>/From Workspace1' */
  real_T FromWorkspace[2999];          /* '<S3>/From Workspace' */
  SL_Bus_pro_upper_controller_nav_msgs_Path b_varargout_2;
  SL_Bus_pro_upper_controller_nav_msgs_Odometry In1;/* '<S17>/In1' */
  SL_Bus_pro_upper_controller_nav_msgs_Odometry b_varargout_2_m;
  SL_Bus_pro_upper_controller_geometry_msgs_Twist BusAssignment1;/* '<S1>/Bus Assignment1' */
  real_T Multiply;                     /* '<S1>/Multiply' */
  real_T forword_angle;                /* '<S2>/forword_control' */
  real_T b_index;
  real_T Product3;                     /* '<S10>/Product3' */
  real_T Product2;                     /* '<S10>/Product2' */
  real_T Product1;                     /* '<S10>/Product1' */
  real_T fcn5;                         /* '<S6>/fcn5' */
  real_T fcn3;                         /* '<S6>/fcn3' */
  real_T ed_tmp;
};

/* Block states (default storage) for system '<Root>' */
struct DW_pro_upper_controller_T {
  ros_slroscpp_internal_block_P_T obj; /* '<S5>/SinkBlock' */
  ros_slroscpp_internal_block_S_T obj_d;/* '<S8>/SourceBlock' */
  ros_slroscpp_internal_block_S_T obj_l;/* '<S7>/SourceBlock' */
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace4_PWORK;              /* '<S2>/From Workspace4' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace5_PWORK;              /* '<S2>/From Workspace5' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace6_PWORK;              /* '<S2>/From Workspace6' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace7_PWORK;              /* '<S2>/From Workspace7' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace_PWORK;               /* '<S3>/From Workspace' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace1_PWORK;              /* '<S3>/From Workspace1' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace2_PWORK;              /* '<S3>/From Workspace2' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace3_PWORK;              /* '<S3>/From Workspace3' */

  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<S2>/Scope' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<S1>/Scope1' */

  struct {
    int_T PrevIndex;
  } FromWorkspace4_IWORK;              /* '<S2>/From Workspace4' */

  struct {
    int_T PrevIndex;
  } FromWorkspace5_IWORK;              /* '<S2>/From Workspace5' */

  struct {
    int_T PrevIndex;
  } FromWorkspace6_IWORK;              /* '<S2>/From Workspace6' */

  struct {
    int_T PrevIndex;
  } FromWorkspace7_IWORK;              /* '<S2>/From Workspace7' */

  struct {
    int_T PrevIndex;
  } FromWorkspace_IWORK;               /* '<S3>/From Workspace' */

  struct {
    int_T PrevIndex;
  } FromWorkspace1_IWORK;              /* '<S3>/From Workspace1' */

  struct {
    int_T PrevIndex;
  } FromWorkspace2_IWORK;              /* '<S3>/From Workspace2' */

  struct {
    int_T PrevIndex;
  } FromWorkspace3_IWORK;              /* '<S3>/From Workspace3' */

  int8_T EnabledSubsystem_SubsysRanBC; /* '<S8>/Enabled Subsystem' */
  int8_T EnabledSubsystem_SubsysRanBC_p;/* '<S7>/Enabled Subsystem' */
  int8_T IfActionSubsystem2_SubsysRanBC;/* '<S11>/If Action Subsystem2' */
  int8_T IfActionSubsystem1_SubsysRanBC;/* '<S11>/If Action Subsystem1' */
  int8_T IfActionSubsystem_SubsysRanBC;/* '<S11>/If Action Subsystem' */
  boolean_T objisempty;                /* '<S8>/SourceBlock' */
  boolean_T objisempty_f;              /* '<S7>/SourceBlock' */
  boolean_T objisempty_l;              /* '<S5>/SinkBlock' */
};

/* Parameters (default storage) */
struct P_pro_upper_controller_T_ {
  real_T a;                            /* Variable: a
                                        * Referenced by: '<S2>/Constant1'
                                        */
  real_T b;                            /* Variable: b
                                        * Referenced by: '<S2>/Constant2'
                                        */
  real_T cf;                           /* Variable: cf
                                        * Referenced by: '<S2>/Constant4'
                                        */
  real_T m;                            /* Variable: m
                                        * Referenced by: '<S2>/Constant3'
                                        */
  SL_Bus_pro_upper_controller_nav_msgs_Path Out1_Y0;/* Computed Parameter: Out1_Y0
                                                     * Referenced by: '<S18>/Out1'
                                                     */
  SL_Bus_pro_upper_controller_nav_msgs_Path Constant_Value;/* Computed Parameter: Constant_Value
                                                            * Referenced by: '<S8>/Constant'
                                                            */
  SL_Bus_pro_upper_controller_nav_msgs_Odometry Out1_Y0_e;/* Computed Parameter: Out1_Y0_e
                                                           * Referenced by: '<S17>/Out1'
                                                           */
  SL_Bus_pro_upper_controller_nav_msgs_Odometry Constant_Value_f;/* Computed Parameter: Constant_Value_f
                                                                  * Referenced by: '<S7>/Constant'
                                                                  */
  SL_Bus_pro_upper_controller_geometry_msgs_Twist Constant_Value_h;/* Computed Parameter: Constant_Value_h
                                                                    * Referenced by: '<S4>/Constant'
                                                                    */
  real_T Constant_Value_fm;            /* Expression: 1
                                        * Referenced by: '<S12>/Constant'
                                        */
  real_T Constant_Value_d;             /* Expression: 1
                                        * Referenced by: '<S13>/Constant'
                                        */
  real_T Constant_Value_l;             /* Expression: 0
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Constant5_Value;              /* Expression: 0.5
                                        * Referenced by: '<S2>/Constant5'
                                        */
  real_T Multiply_Gain;                /* Expression: 180/pi
                                        * Referenced by: '<S1>/Multiply'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_pro_upper_controller_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_pro_upper_controller_T pro_upper_controller_P;

#ifdef __cplusplus

}
#endif

/* Block signals (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern struct B_pro_upper_controller_T pro_upper_controller_B;

#ifdef __cplusplus

}
#endif

/* Block states (default storage) */
extern struct DW_pro_upper_controller_T pro_upper_controller_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void pro_upper_controller_initialize(void);
  extern void pro_upper_controller_step(void);
  extern void pro_upper_controller_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_pro_upper_controller_T *const pro_upper_controller_M;

#ifdef __cplusplus

}
#endif

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
 * '<Root>' : 'pro_upper_controller'
 * '<S1>'   : 'pro_upper_controller/Platform'
 * '<S2>'   : 'pro_upper_controller/controller'
 * '<S3>'   : 'pro_upper_controller/ref-path-FIXED'
 * '<S4>'   : 'pro_upper_controller/Platform/Blank Message1'
 * '<S5>'   : 'pro_upper_controller/Platform/Publish1'
 * '<S6>'   : 'pro_upper_controller/Platform/Quaternions to Rotation Angles'
 * '<S7>'   : 'pro_upper_controller/Platform/Subscribe'
 * '<S8>'   : 'pro_upper_controller/Platform/Subscribe1'
 * '<S9>'   : 'pro_upper_controller/Platform/Quaternions to Rotation Angles/Angle Calculation'
 * '<S10>'  : 'pro_upper_controller/Platform/Quaternions to Rotation Angles/Quaternion Normalize'
 * '<S11>'  : 'pro_upper_controller/Platform/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input'
 * '<S12>'  : 'pro_upper_controller/Platform/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem'
 * '<S13>'  : 'pro_upper_controller/Platform/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem1'
 * '<S14>'  : 'pro_upper_controller/Platform/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem2'
 * '<S15>'  : 'pro_upper_controller/Platform/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus'
 * '<S16>'  : 'pro_upper_controller/Platform/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S17>'  : 'pro_upper_controller/Platform/Subscribe/Enabled Subsystem'
 * '<S18>'  : 'pro_upper_controller/Platform/Subscribe1/Enabled Subsystem'
 * '<S19>'  : 'pro_upper_controller/controller/err_kappa_calculate_module'
 * '<S20>'  : 'pro_upper_controller/controller/forword_control'
 * '<S21>'  : 'pro_upper_controller/controller/last_angle'
 * '<S22>'  : 'pro_upper_controller/controller/lqr_offline'
 * '<S23>'  : 'pro_upper_controller/controller/predict_module'
 */
#endif                                 /* RTW_HEADER_pro_upper_controller_h_ */

/*
 * pro_upper_controller_types.h
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

#ifndef RTW_HEADER_pro_upper_controller_types_h_
#define RTW_HEADER_pro_upper_controller_types_h_
#include "rtwtypes.h"

/* Model Code Variants */
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_Vector3_

struct SL_Bus_pro_upper_controller_geometry_msgs_Vector3
{
  real_T X;
  real_T Y;
  real_T Z;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_Twist_

struct SL_Bus_pro_upper_controller_geometry_msgs_Twist
{
  SL_Bus_pro_upper_controller_geometry_msgs_Vector3 Linear;
  SL_Bus_pro_upper_controller_geometry_msgs_Vector3 Angular;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_ros_time_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_ros_time_Time_

struct SL_Bus_pro_upper_controller_ros_time_Time
{
  real_T Sec;
  real_T Nsec;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

struct SL_Bus_ROSVariableLengthArrayInfo
{
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_std_msgs_Header_

struct SL_Bus_pro_upper_controller_std_msgs_Header
{
  uint32_T Seq;
  SL_Bus_pro_upper_controller_ros_time_Time Stamp;
  uint8_T FrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo FrameId_SL_Info;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_Point_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_Point_

struct SL_Bus_pro_upper_controller_geometry_msgs_Point
{
  real_T X;
  real_T Y;
  real_T Z;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_Quaternion_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_Quaternion_

struct SL_Bus_pro_upper_controller_geometry_msgs_Quaternion
{
  real_T X;
  real_T Y;
  real_T Z;
  real_T W;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_Pose_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_Pose_

struct SL_Bus_pro_upper_controller_geometry_msgs_Pose
{
  SL_Bus_pro_upper_controller_geometry_msgs_Point Position;
  SL_Bus_pro_upper_controller_geometry_msgs_Quaternion Orientation;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_PoseWithCovariance_mdq9bn_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_PoseWithCovariance_mdq9bn_

struct SL_Bus_pro_upper_controller_PoseWithCovariance_mdq9bn
{
  SL_Bus_pro_upper_controller_geometry_msgs_Pose Pose;
  real_T Covariance[36];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_TwistWithCovariance_j1foob_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_TwistWithCovariance_j1foob_

struct SL_Bus_pro_upper_controller_TwistWithCovariance_j1foob
{
  SL_Bus_pro_upper_controller_geometry_msgs_Twist Twist;
  real_T Covariance[36];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_nav_msgs_Odometry_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_nav_msgs_Odometry_

struct SL_Bus_pro_upper_controller_nav_msgs_Odometry
{
  SL_Bus_pro_upper_controller_std_msgs_Header Header;
  uint8_T ChildFrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo ChildFrameId_SL_Info;
  SL_Bus_pro_upper_controller_PoseWithCovariance_mdq9bn Pose;
  SL_Bus_pro_upper_controller_TwistWithCovariance_j1foob Twist;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_PoseStamped_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_geometry_msgs_PoseStamped_

struct SL_Bus_pro_upper_controller_geometry_msgs_PoseStamped
{
  SL_Bus_pro_upper_controller_std_msgs_Header Header;
  SL_Bus_pro_upper_controller_geometry_msgs_Pose Pose;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_nav_msgs_Path_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pro_upper_controller_nav_msgs_Path_

struct SL_Bus_pro_upper_controller_nav_msgs_Path
{
  SL_Bus_pro_upper_controller_std_msgs_Header Header;
  SL_Bus_pro_upper_controller_geometry_msgs_PoseStamped Poses[16];
  SL_Bus_ROSVariableLengthArrayInfo Poses_SL_Info;
};

#endif

#ifndef struct_ros_slroscpp_internal_block_P_T
#define struct_ros_slroscpp_internal_block_P_T

struct ros_slroscpp_internal_block_P_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                              /* struct_ros_slroscpp_internal_block_P_T */

#ifndef struct_ros_slroscpp_internal_block_S_T
#define struct_ros_slroscpp_internal_block_S_T

struct ros_slroscpp_internal_block_S_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                              /* struct_ros_slroscpp_internal_block_S_T */

/* Parameters (default storage) */
typedef struct P_pro_upper_controller_T_ P_pro_upper_controller_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_pro_upper_controller_T RT_MODEL_pro_upper_controller_T;

#endif                            /* RTW_HEADER_pro_upper_controller_types_h_ */

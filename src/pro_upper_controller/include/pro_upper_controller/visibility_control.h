#ifndef PRO_UPPER_CONTROLLER__VISIBILITY_CONTROL_H_
#define PRO_UPPER_CONTROLLER__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define PRO_UPPER_CONTROLLER_EXPORT __attribute__ ((dllexport))
    #define PRO_UPPER_CONTROLLER_IMPORT __attribute__ ((dllimport))
  #else
    #define PRO_UPPER_CONTROLLER_EXPORT __declspec(dllexport)
    #define PRO_UPPER_CONTROLLER_IMPORT __declspec(dllimport)
  #endif
  #ifdef PRO_UPPER_CONTROLLER_BUILDING_LIBRARY
    #define PRO_UPPER_CONTROLLER_PUBLIC PRO_UPPER_CONTROLLER_EXPORT
  #else
    #define PRO_UPPER_CONTROLLER_PUBLIC PRO_UPPER_CONTROLLER_IMPORT
  #endif
  #define PRO_UPPER_CONTROLLER_PUBLIC_TYPE PRO_UPPER_CONTROLLER_PUBLIC
  #define PRO_UPPER_CONTROLLER_LOCAL
#else
  #define PRO_UPPER_CONTROLLER_EXPORT __attribute__ ((visibility("default")))
  #define PRO_UPPER_CONTROLLER_IMPORT
  #if __GNUC__ >= 4
    #define PRO_UPPER_CONTROLLER_PUBLIC __attribute__ ((visibility("default")))
    #define PRO_UPPER_CONTROLLER_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define PRO_UPPER_CONTROLLER_PUBLIC
    #define PRO_UPPER_CONTROLLER_LOCAL
  #endif
  #define PRO_UPPER_CONTROLLER_PUBLIC_TYPE
#endif
#endif  // PRO_UPPER_CONTROLLER__VISIBILITY_CONTROL_H_
// Generated 06-May-2022 15:53:29
// Copyright 2019-2020 The MathWorks, Inc.

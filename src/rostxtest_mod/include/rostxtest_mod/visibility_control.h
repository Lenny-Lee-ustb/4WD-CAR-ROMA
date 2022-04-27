#ifndef ROSTXTEST_MOD__VISIBILITY_CONTROL_H_
#define ROSTXTEST_MOD__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSTXTEST_MOD_EXPORT __attribute__ ((dllexport))
    #define ROSTXTEST_MOD_IMPORT __attribute__ ((dllimport))
  #else
    #define ROSTXTEST_MOD_EXPORT __declspec(dllexport)
    #define ROSTXTEST_MOD_IMPORT __declspec(dllimport)
  #endif
  #ifdef ROSTXTEST_MOD_BUILDING_LIBRARY
    #define ROSTXTEST_MOD_PUBLIC ROSTXTEST_MOD_EXPORT
  #else
    #define ROSTXTEST_MOD_PUBLIC ROSTXTEST_MOD_IMPORT
  #endif
  #define ROSTXTEST_MOD_PUBLIC_TYPE ROSTXTEST_MOD_PUBLIC
  #define ROSTXTEST_MOD_LOCAL
#else
  #define ROSTXTEST_MOD_EXPORT __attribute__ ((visibility("default")))
  #define ROSTXTEST_MOD_IMPORT
  #if __GNUC__ >= 4
    #define ROSTXTEST_MOD_PUBLIC __attribute__ ((visibility("default")))
    #define ROSTXTEST_MOD_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define ROSTXTEST_MOD_PUBLIC
    #define ROSTXTEST_MOD_LOCAL
  #endif
  #define ROSTXTEST_MOD_PUBLIC_TYPE
#endif
#endif  // ROSTXTEST_MOD__VISIBILITY_CONTROL_H_
// Generated 24-Apr-2022 16:36:43
// Copyright 2019-2020 The MathWorks, Inc.

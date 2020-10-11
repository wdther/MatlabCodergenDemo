//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: coder_foo_types.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 04-Aug-2020 10:16:15
//
#ifndef CODER_FOO_TYPES_H
#define CODER_FOO_TYPES_H

// Include Files
#include "rtwtypes.h"
#ifdef CODER_FOO_XIL_BUILD
#if defined(_MSC_VER) || defined(__LCC__)
#define CODER_FOO_DLL_EXPORT           __declspec(dllimport)
#else
#define CODER_FOO_DLL_EXPORT
#endif

#elif defined(BUILDING_CODER_FOO)
#if defined(_MSC_VER) || defined(__LCC__)
#define CODER_FOO_DLL_EXPORT           __declspec(dllexport)
#else
#define CODER_FOO_DLL_EXPORT           __attribute__ ((visibility("default")))
#endif

#else
#define CODER_FOO_DLL_EXPORT
#endif
#endif

//
// File trailer for coder_foo_types.h
//
// [EOF]
//

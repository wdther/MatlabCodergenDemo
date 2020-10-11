//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: polyfit_types.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 04-Aug-2020 12:18:06
//
#ifndef POLYFIT_TYPES_H
#define POLYFIT_TYPES_H

// Include Files
#include "rtwtypes.h"
#ifdef POLYFIT_XIL_BUILD
#if defined(_MSC_VER) || defined(__LCC__)
#define POLYFIT_DLL_EXPORT             __declspec(dllimport)
#else
#define POLYFIT_DLL_EXPORT
#endif

#elif defined(BUILDING_POLYFIT)
#if defined(_MSC_VER) || defined(__LCC__)
#define POLYFIT_DLL_EXPORT             __declspec(dllexport)
#else
#define POLYFIT_DLL_EXPORT             __attribute__ ((visibility("default")))
#endif

#else
#define POLYFIT_DLL_EXPORT
#endif

// Type Definitions
struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct struct0_T
{
  emxArray_real_T *R;
  double df;
  double normr;
};

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif

//
// File trailer for polyfit_types.h
//
// [EOF]
//

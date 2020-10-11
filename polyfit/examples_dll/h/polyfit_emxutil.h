//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: polyfit_emxutil.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 04-Aug-2020 12:18:06
//
#ifndef POLYFIT_EMXUTIL_H
#define POLYFIT_EMXUTIL_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "polyfit_types.h"

// Function Declarations
POLYFIT_DLL_EXPORT extern void emxEnsureCapacity_int32_T(emxArray_int32_T
  *emxArray, int oldNumel);
POLYFIT_DLL_EXPORT extern void emxEnsureCapacity_real_T(emxArray_real_T
  *emxArray, int oldNumel);
POLYFIT_DLL_EXPORT extern void emxFreeStruct_struct0_T(struct0_T *pStruct);
POLYFIT_DLL_EXPORT extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
POLYFIT_DLL_EXPORT extern void emxFree_real_T(emxArray_real_T **pEmxArray);
POLYFIT_DLL_EXPORT extern void emxInitStruct_struct0_T(struct0_T *pStruct);
POLYFIT_DLL_EXPORT extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int
  numDimensions);
POLYFIT_DLL_EXPORT extern void emxInit_real_T(emxArray_real_T **pEmxArray, int
  numDimensions);

#endif

//
// File trailer for polyfit_emxutil.h
//
// [EOF]
//

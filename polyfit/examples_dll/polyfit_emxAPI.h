//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: polyfit_emxAPI.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 04-Aug-2020 12:18:06
//
#ifndef POLYFIT_EMXAPI_H
#define POLYFIT_EMXAPI_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "polyfit_types.h"

// Function Declarations
POLYFIT_DLL_EXPORT extern emxArray_real_T *emxCreateND_real_T(int numDimensions,
  const int *size);
POLYFIT_DLL_EXPORT extern emxArray_real_T *emxCreateWrapperND_real_T(double
  *data, int numDimensions, const int *size);
POLYFIT_DLL_EXPORT extern emxArray_real_T *emxCreateWrapper_real_T(double *data,
  int rows, int cols);
POLYFIT_DLL_EXPORT extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
POLYFIT_DLL_EXPORT extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
POLYFIT_DLL_EXPORT extern void emxDestroy_struct0_T(struct0_T emxArray);
POLYFIT_DLL_EXPORT extern void emxInitArray_real_T(emxArray_real_T **pEmxArray,
  int numDimensions);
POLYFIT_DLL_EXPORT extern void emxInit_struct0_T(struct0_T *pStruct);

#endif

//
// File trailer for polyfit_emxAPI.h
//
// [EOF]
//

//
// File: xzlarf.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 03-Aug-2020 22:26:41
//

// Include Files
#include "rt_nonfinite.h"
#include "polyfit.h"
#include "xzlarf.h"

// Function Definitions

//
// Arguments    : int m
//                int n
//                int iv0
//                double tau
//                emxArray_real_T *C
//                int ic0
//                int ldc
//                emxArray_real_T *work
// Return Type  : void
//
void xzlarf(int m, int n, int iv0, double tau, emxArray_real_T *C, int ic0, int
            ldc, emxArray_real_T *work)
{
  int lastv;
  int lastc;
  int i;
  boolean_T exitg2;
  int jy;
  int j;
  int i5;
  int ia;
  int exitg1;
  double c;
  int ix;
  if (tau != 0.0) {
    lastv = m;
    i = iv0 + m;
    while ((lastv > 0) && (C->data[i - 2] == 0.0)) {
      lastv--;
      i--;
    }

    lastc = n;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      i = ic0 + (lastc - 1) * ldc;
      ia = i;
      do {
        exitg1 = 0;
        if (ia <= (i + lastv) - 1) {
          if (C->data[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      for (i = 1; i <= lastc; i++) {
        work->data[i - 1] = 0.0;
      }

      i = 0;
      i5 = ic0 + ldc * (lastc - 1);
      jy = ic0;
      while ((ldc > 0) && (jy <= i5)) {
        ix = iv0;
        c = 0.0;
        j = (jy + lastv) - 1;
        for (ia = jy; ia <= j; ia++) {
          c += C->data[ia - 1] * C->data[ix - 1];
          ix++;
        }

        work->data[i] += c;
        i++;
        jy += ldc;
      }
    }

    if (!(-tau == 0.0)) {
      i = ic0 - 1;
      jy = 0;
      for (j = 1; j <= lastc; j++) {
        if (work->data[jy] != 0.0) {
          c = work->data[jy] * -tau;
          ix = iv0;
          i5 = lastv + i;
          for (ia = i; ia + 1 <= i5; ia++) {
            C->data[ia] += C->data[ix - 1] * c;
            ix++;
          }
        }

        jy++;
        i += ldc;
      }
    }
  }
}

//
// File trailer for xzlarf.cpp
//
// [EOF]
//

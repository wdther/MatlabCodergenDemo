/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: qrsolve.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 04-Aug-2020 12:54:05
 */

/* Include Files */
#include "qrsolve.h"
#include "polyfit.h"
#include "polyfit_emxutil.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include <math.h>

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                emxArray_real_T *Y
 * Return Type  : void
 */
void qrsolve(const emxArray_real_T *A, const emxArray_real_T *B, emxArray_real_T
             *Y)
{
  emxArray_real_T *b_A;
  int u0;
  int minmana;
  emxArray_real_T *tau;
  int m;
  int n;
  emxArray_int32_T *jpvt;
  emxArray_real_T *work;
  emxArray_real_T *vn1;
  emxArray_real_T *vn2;
  boolean_T guard1 = false;
  int ix;
  int minmn;
  int pvt;
  double smax;
  int ma;
  int i;
  double d;
  int ip1;
  int iy;
  int ii;
  int nmi;
  int mmi;
  double s;
  emxInit_real_T(&b_A, 2);
  u0 = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = A->size[1];
  emxEnsureCapacity_real_T(b_A, u0);
  minmana = A->size[0] * A->size[1];
  for (u0 = 0; u0 < minmana; u0++) {
    b_A->data[u0] = A->data[u0];
  }

  emxInit_real_T(&tau, 1);
  m = A->size[0];
  n = A->size[1];
  u0 = A->size[0];
  minmana = A->size[1];
  if (u0 < minmana) {
    minmana = u0;
  }

  u0 = tau->size[0];
  tau->size[0] = minmana;
  emxEnsureCapacity_real_T(tau, u0);
  for (u0 = 0; u0 < minmana; u0++) {
    tau->data[u0] = 0.0;
  }

  emxInit_int32_T(&jpvt, 2);
  emxInit_real_T(&work, 1);
  emxInit_real_T(&vn1, 1);
  emxInit_real_T(&vn2, 1);
  guard1 = false;
  if ((A->size[0] == 0) || (A->size[1] == 0)) {
    guard1 = true;
  } else {
    u0 = A->size[0];
    minmana = A->size[1];
    if (u0 < minmana) {
      minmana = u0;
    }

    if (minmana < 1) {
      guard1 = true;
    } else {
      u0 = jpvt->size[0] * jpvt->size[1];
      jpvt->size[0] = 1;
      jpvt->size[1] = A->size[1];
      emxEnsureCapacity_int32_T(jpvt, u0);
      minmana = A->size[1];
      for (u0 = 0; u0 < minmana; u0++) {
        jpvt->data[u0] = 0;
      }

      for (u0 = 0; u0 < n; u0++) {
        jpvt->data[u0] = u0 + 1;
      }

      ma = A->size[0];
      u0 = A->size[0];
      minmn = A->size[1];
      if (u0 < minmn) {
        minmn = u0;
      }

      u0 = work->size[0];
      work->size[0] = A->size[1];
      emxEnsureCapacity_real_T(work, u0);
      minmana = A->size[1];
      for (u0 = 0; u0 < minmana; u0++) {
        work->data[u0] = 0.0;
      }

      u0 = vn1->size[0];
      vn1->size[0] = A->size[1];
      emxEnsureCapacity_real_T(vn1, u0);
      minmana = A->size[1];
      for (u0 = 0; u0 < minmana; u0++) {
        vn1->data[u0] = 0.0;
      }

      u0 = vn2->size[0];
      vn2->size[0] = A->size[1];
      emxEnsureCapacity_real_T(vn2, u0);
      minmana = A->size[1];
      for (u0 = 0; u0 < minmana; u0++) {
        vn2->data[u0] = 0.0;
      }

      for (pvt = 0; pvt < n; pvt++) {
        d = xnrm2(m, A, pvt * ma + 1);
        vn1->data[pvt] = d;
        vn2->data[pvt] = d;
      }

      for (i = 0; i < minmn; i++) {
        ip1 = i + 2;
        iy = i * ma;
        ii = iy + i;
        nmi = n - i;
        mmi = m - i;
        if (nmi < 1) {
          minmana = -1;
        } else {
          minmana = 0;
          if (nmi > 1) {
            ix = i;
            smax = fabs(vn1->data[i]);
            for (u0 = 2; u0 <= nmi; u0++) {
              ix++;
              s = fabs(vn1->data[ix]);
              if (s > smax) {
                minmana = u0 - 1;
                smax = s;
              }
            }
          }
        }

        pvt = i + minmana;
        if (pvt + 1 != i + 1) {
          ix = pvt * ma;
          for (u0 = 0; u0 < m; u0++) {
            smax = b_A->data[ix];
            b_A->data[ix] = b_A->data[iy];
            b_A->data[iy] = smax;
            ix++;
            iy++;
          }

          minmana = jpvt->data[pvt];
          jpvt->data[pvt] = jpvt->data[i];
          jpvt->data[i] = minmana;
          vn1->data[pvt] = vn1->data[i];
          vn2->data[pvt] = vn2->data[i];
        }

        if (i + 1 < m) {
          smax = b_A->data[ii];
          d = xzlarfg(mmi, &smax, b_A, ii + 2);
          tau->data[i] = d;
          b_A->data[ii] = smax;
        } else {
          d = 0.0;
          tau->data[i] = 0.0;
        }

        if (i + 1 < n) {
          smax = b_A->data[ii];
          b_A->data[ii] = 1.0;
          xzlarf(mmi, nmi - 1, ii + 1, d, b_A, (ii + ma) + 1, ma, work);
          b_A->data[ii] = smax;
        }

        for (pvt = ip1; pvt <= n; pvt++) {
          minmana = i + (pvt - 1) * ma;
          d = vn1->data[pvt - 1];
          if (d != 0.0) {
            smax = fabs(b_A->data[minmana]) / d;
            smax = 1.0 - smax * smax;
            if (smax < 0.0) {
              smax = 0.0;
            }

            s = d / vn2->data[pvt - 1];
            s = smax * (s * s);
            if (s <= 1.4901161193847656E-8) {
              if (i + 1 < m) {
                d = xnrm2(mmi - 1, b_A, minmana + 2);
                vn1->data[pvt - 1] = d;
                vn2->data[pvt - 1] = d;
              } else {
                vn1->data[pvt - 1] = 0.0;
                vn2->data[pvt - 1] = 0.0;
              }
            } else {
              vn1->data[pvt - 1] = d * sqrt(smax);
            }
          }
        }
      }
    }
  }

  if (guard1) {
    u0 = jpvt->size[0] * jpvt->size[1];
    jpvt->size[0] = 1;
    jpvt->size[1] = A->size[1];
    emxEnsureCapacity_int32_T(jpvt, u0);
    minmana = A->size[1];
    for (u0 = 0; u0 < minmana; u0++) {
      jpvt->data[u0] = 0;
    }

    for (pvt = 0; pvt < n; pvt++) {
      jpvt->data[pvt] = pvt + 1;
    }
  }

  emxFree_real_T(&vn2);
  emxFree_real_T(&vn1);
  ix = 0;
  if (b_A->size[0] < b_A->size[1]) {
    minmn = b_A->size[0];
    minmana = b_A->size[1];
  } else {
    minmn = b_A->size[1];
    minmana = b_A->size[0];
  }

  if (minmn > 0) {
    smax = fmin(1.4901161193847656E-8, 2.2204460492503131E-15 * (double)minmana)
      * fabs(b_A->data[0]);
    while ((ix < minmn) && (!(fabs(b_A->data[ix + b_A->size[0] * ix]) <= smax)))
    {
      ix++;
    }
  }

  u0 = work->size[0];
  work->size[0] = B->size[0];
  emxEnsureCapacity_real_T(work, u0);
  minmana = B->size[0];
  for (u0 = 0; u0 < minmana; u0++) {
    work->data[u0] = B->data[u0];
  }

  u0 = Y->size[0];
  Y->size[0] = b_A->size[1];
  emxEnsureCapacity_real_T(Y, u0);
  minmana = b_A->size[1];
  for (u0 = 0; u0 < minmana; u0++) {
    Y->data[u0] = 0.0;
  }

  m = b_A->size[0];
  u0 = b_A->size[0];
  minmana = b_A->size[1];
  if (u0 < minmana) {
    minmana = u0;
  }

  for (pvt = 0; pvt < minmana; pvt++) {
    if (tau->data[pvt] != 0.0) {
      smax = work->data[pvt];
      u0 = pvt + 2;
      for (i = u0; i <= m; i++) {
        smax += b_A->data[(i + b_A->size[0] * pvt) - 1] * work->data[i - 1];
      }

      smax *= tau->data[pvt];
      if (smax != 0.0) {
        work->data[pvt] -= smax;
        u0 = pvt + 2;
        for (i = u0; i <= m; i++) {
          work->data[i - 1] -= b_A->data[(i + b_A->size[0] * pvt) - 1] * smax;
        }
      }
    }
  }

  emxFree_real_T(&tau);
  for (i = 0; i < ix; i++) {
    Y->data[jpvt->data[i] - 1] = work->data[i];
  }

  emxFree_real_T(&work);
  for (pvt = ix; pvt >= 1; pvt--) {
    u0 = jpvt->data[pvt - 1];
    Y->data[u0 - 1] /= b_A->data[(pvt + b_A->size[0] * (pvt - 1)) - 1];
    for (i = 0; i <= pvt - 2; i++) {
      Y->data[jpvt->data[i] - 1] -= Y->data[jpvt->data[pvt - 1] - 1] * b_A->
        data[i + b_A->size[0] * (pvt - 1)];
    }
  }

  emxFree_int32_T(&jpvt);
  emxFree_real_T(&b_A);
}

/*
 * File trailer for qrsolve.c
 *
 * [EOF]
 */

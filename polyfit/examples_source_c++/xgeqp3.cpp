//
// File: xgeqp3.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 03-Aug-2020 22:26:41
//

// Include Files
#include "rt_nonfinite.h"
#include "polyfit.h"
#include "xgeqp3.h"
#include "xnrm2.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include "polyfit_emxutil.h"
#include "colon.h"

// Function Definitions

//
// Arguments    : emxArray_real_T *A
//                emxArray_real_T *tau
//                emxArray_int32_T *jpvt
// Return Type  : void
//
void xgeqp3(emxArray_real_T *A, emxArray_real_T *tau, emxArray_int32_T *jpvt)
{
  int m;
  int n;
  int mn;
  int iy;
  emxArray_real_T *work;
  int k;
  emxArray_real_T *vn1;
  emxArray_real_T *vn2;
  int ix;
  int i;
  int i_i;
  int nmi;
  int mmi;
  int pvt;
  double smax;
  double s;
  double absxk;
  double t;
  m = A->size[0];
  n = A->size[1];
  if (A->size[0] <= A->size[1]) {
    mn = A->size[0];
  } else {
    mn = A->size[1];
  }

  iy = tau->size[0];
  tau->size[0] = mn;
  emxEnsureCapacity((emxArray__common *)tau, iy, (int)sizeof(double));
  eml_signed_integer_colon(A->size[1], jpvt);
  if (!((A->size[0] == 0) || (A->size[1] == 0))) {
    emxInit_real_T1(&work, 1);
    k = A->size[1];
    iy = work->size[0];
    work->size[0] = k;
    emxEnsureCapacity((emxArray__common *)work, iy, (int)sizeof(double));
    for (iy = 0; iy < k; iy++) {
      work->data[iy] = 0.0;
    }

    emxInit_real_T1(&vn1, 1);
    emxInit_real_T1(&vn2, 1);
    k = A->size[1];
    iy = vn1->size[0];
    vn1->size[0] = k;
    emxEnsureCapacity((emxArray__common *)vn1, iy, (int)sizeof(double));
    iy = vn2->size[0];
    vn2->size[0] = vn1->size[0];
    emxEnsureCapacity((emxArray__common *)vn2, iy, (int)sizeof(double));
    k = 1;
    for (ix = 0; ix + 1 <= n; ix++) {
      vn1->data[ix] = xnrm2(m, A, k);
      vn2->data[ix] = vn1->data[ix];
      k += m;
    }

    for (i = 0; i + 1 <= mn; i++) {
      i_i = i + i * m;
      nmi = n - i;
      mmi = m - i;
      if (nmi < 1) {
        iy = 0;
      } else {
        iy = 1;
        if (nmi > 1) {
          ix = i;
          smax = std::abs(vn1->data[i]);
          for (k = 2; k <= nmi; k++) {
            ix++;
            s = std::abs(vn1->data[ix]);
            if (s > smax) {
              iy = k;
              smax = s;
            }
          }
        }
      }

      pvt = (i + iy) - 1;
      if (pvt + 1 != i + 1) {
        ix = m * pvt;
        iy = m * i;
        for (k = 1; k <= m; k++) {
          smax = A->data[ix];
          A->data[ix] = A->data[iy];
          A->data[iy] = smax;
          ix++;
          iy++;
        }

        k = jpvt->data[pvt];
        jpvt->data[pvt] = jpvt->data[i];
        jpvt->data[i] = k;
        vn1->data[pvt] = vn1->data[i];
        vn2->data[pvt] = vn2->data[i];
      }

      if (i + 1 < m) {
        smax = A->data[i_i];
        tau->data[i] = xzlarfg(mmi, &smax, A, i_i + 2);
        A->data[i_i] = smax;
      } else {
        tau->data[i] = 0.0;
      }

      if (i + 1 < n) {
        smax = A->data[i_i];
        A->data[i_i] = 1.0;
        xzlarf(mmi, nmi - 1, i_i + 1, tau->data[i], A, (i + (i + 1) * m) + 1, m,
               work);
        A->data[i_i] = smax;
      }

      for (ix = i + 1; ix + 1 <= n; ix++) {
        k = (i + m * ix) + 1;
        if (vn1->data[ix] != 0.0) {
          smax = std::abs(A->data[i + A->size[0] * ix]) / vn1->data[ix];
          smax = 1.0 - smax * smax;
          if (smax < 0.0) {
            smax = 0.0;
          }

          s = vn1->data[ix] / vn2->data[ix];
          s = smax * (s * s);
          if (s <= 1.4901161193847656E-8) {
            if (i + 1 < m) {
              smax = 0.0;
              if (!(mmi - 1 < 1)) {
                if (mmi - 1 == 1) {
                  smax = std::abs(A->data[k]);
                } else {
                  s = 2.2250738585072014E-308;
                  iy = (k + mmi) - 1;
                  while (k + 1 <= iy) {
                    absxk = std::abs(A->data[k]);
                    if (absxk > s) {
                      t = s / absxk;
                      smax = 1.0 + smax * t * t;
                      s = absxk;
                    } else {
                      t = absxk / s;
                      smax += t * t;
                    }

                    k++;
                  }

                  smax = s * std::sqrt(smax);
                }
              }

              vn1->data[ix] = smax;
              vn2->data[ix] = vn1->data[ix];
            } else {
              vn1->data[ix] = 0.0;
              vn2->data[ix] = 0.0;
            }
          } else {
            vn1->data[ix] *= std::sqrt(smax);
          }
        }
      }
    }

    emxFree_real_T(&vn2);
    emxFree_real_T(&vn1);
    emxFree_real_T(&work);
  }
}

//
// File trailer for xgeqp3.cpp
//
// [EOF]
//

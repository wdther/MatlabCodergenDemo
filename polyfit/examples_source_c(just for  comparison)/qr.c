/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: qr.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 04-Aug-2020 12:54:05
 */

/* Include Files */
#include "qr.h"
#include "polyfit.h"
#include "polyfit_emxutil.h"
#include "rt_nonfinite.h"
#include "xgerc.h"
#include "xzlarf.h"
#include "xzlarfg.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                emxArray_real_T *Q
 *                emxArray_real_T *R
 * Return Type  : void
 */
void qr(const emxArray_real_T *A, emxArray_real_T *Q, emxArray_real_T *R)
{
  emxArray_real_T *b_A;
  int i;
  int mmi;
  emxArray_real_T *tau;
  int m;
  int n;
  int minmana;
  int minmn;
  emxArray_real_T *work;
  int lda;
  int b_i;
  double c;
  double atmp;
  int itau;
  int ia;
  int i1;
  int iaii;
  int lastv;
  int lastc;
  boolean_T exitg2;
  int exitg1;
  emxInit_real_T(&b_A, 2);
  i = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = A->size[1];
  emxEnsureCapacity_real_T(b_A, i);
  mmi = A->size[0] * A->size[1];
  for (i = 0; i < mmi; i++) {
    b_A->data[i] = A->data[i];
  }

  emxInit_real_T(&tau, 1);
  m = A->size[0];
  n = A->size[1];
  mmi = A->size[0];
  minmana = A->size[1];
  if (mmi < minmana) {
    minmana = mmi;
  }

  mmi = A->size[0];
  minmn = A->size[1];
  if (mmi < minmn) {
    minmn = mmi;
  }

  i = tau->size[0];
  tau->size[0] = minmana;
  emxEnsureCapacity_real_T(tau, i);
  for (i = 0; i < minmana; i++) {
    tau->data[i] = 0.0;
  }

  emxInit_real_T(&work, 1);
  if ((A->size[0] != 0) && (A->size[1] != 0) && (minmn >= 1)) {
    lda = A->size[0];
    i = work->size[0];
    work->size[0] = A->size[1];
    emxEnsureCapacity_real_T(work, i);
    mmi = A->size[1];
    for (i = 0; i < mmi; i++) {
      work->data[i] = 0.0;
    }

    for (b_i = 0; b_i < minmn; b_i++) {
      minmana = b_i * lda + b_i;
      mmi = m - b_i;
      if (b_i + 1 < m) {
        atmp = b_A->data[minmana];
        c = xzlarfg(mmi, &atmp, b_A, minmana + 2);
        tau->data[b_i] = c;
        b_A->data[minmana] = atmp;
      } else {
        c = 0.0;
        tau->data[b_i] = 0.0;
      }

      if (b_i + 1 < n) {
        atmp = b_A->data[minmana];
        b_A->data[minmana] = 1.0;
        xzlarf(mmi, (n - b_i) - 1, minmana + 1, c, b_A, (minmana + lda) + 1, lda,
               work);
        b_A->data[minmana] = atmp;
      }
    }
  }

  m = b_A->size[0];
  n = b_A->size[1];
  if (b_A->size[0] > b_A->size[1]) {
    i = R->size[0] * R->size[1];
    R->size[0] = b_A->size[1];
    R->size[1] = b_A->size[1];
    emxEnsureCapacity_real_T(R, i);
    for (minmana = 0; minmana < n; minmana++) {
      for (b_i = 0; b_i <= minmana; b_i++) {
        R->data[b_i + R->size[0] * minmana] = b_A->data[b_i + b_A->size[0] *
          minmana];
      }

      i = minmana + 2;
      for (b_i = i; b_i <= n; b_i++) {
        R->data[(b_i + R->size[0] * minmana) - 1] = 0.0;
      }
    }

    if (b_A->size[1] >= 1) {
      i = b_A->size[1] - 1;
      for (minmana = n; minmana <= i; minmana++) {
        ia = minmana * m;
        i1 = m - 1;
        for (b_i = 0; b_i <= i1; b_i++) {
          b_A->data[ia + b_i] = 0.0;
        }

        b_A->data[ia + minmana] = 1.0;
      }

      itau = n - 1;
      i = work->size[0];
      work->size[0] = b_A->size[1];
      emxEnsureCapacity_real_T(work, i);
      mmi = b_A->size[1];
      for (i = 0; i < mmi; i++) {
        work->data[i] = 0.0;
      }

      for (b_i = n; b_i >= 1; b_i--) {
        iaii = b_i + (b_i - 1) * m;
        if (b_i < n) {
          b_A->data[iaii - 1] = 1.0;
          mmi = iaii + m;
          if (tau->data[itau] != 0.0) {
            lastv = (m - b_i) + 1;
            minmana = (iaii + m) - b_i;
            while ((lastv > 0) && (b_A->data[minmana - 1] == 0.0)) {
              lastv--;
              minmana--;
            }

            lastc = n - b_i;
            exitg2 = false;
            while ((!exitg2) && (lastc > 0)) {
              minmana = mmi + (lastc - 1) * m;
              ia = minmana;
              do {
                exitg1 = 0;
                if (ia <= (minmana + lastv) - 1) {
                  if (b_A->data[ia - 1] != 0.0) {
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
              for (minmana = 0; minmana < lastc; minmana++) {
                work->data[minmana] = 0.0;
              }

              minmana = 0;
              i = mmi + m * (lastc - 1);
              for (lda = mmi; m < 0 ? lda >= i : lda <= i; lda += m) {
                minmn = iaii;
                c = 0.0;
                i1 = (lda + lastv) - 1;
                for (ia = lda; ia <= i1; ia++) {
                  c += b_A->data[ia - 1] * b_A->data[minmn - 1];
                  minmn++;
                }

                work->data[minmana] += c;
                minmana++;
              }
            }

            xgerc(lastv, lastc, -tau->data[itau], iaii, work, b_A, mmi, m);
          }
        }

        if (b_i < m) {
          minmana = iaii + 1;
          i = (iaii + m) - b_i;
          for (mmi = minmana; mmi <= i; mmi++) {
            b_A->data[mmi - 1] *= -tau->data[itau];
          }
        }

        b_A->data[iaii - 1] = 1.0 - tau->data[itau];
        for (minmana = 0; minmana <= b_i - 2; minmana++) {
          b_A->data[(iaii - minmana) - 2] = 0.0;
        }

        itau--;
      }
    }

    i = Q->size[0] * Q->size[1];
    Q->size[0] = b_A->size[0];
    Q->size[1] = b_A->size[1];
    emxEnsureCapacity_real_T(Q, i);
    mmi = b_A->size[0] * b_A->size[1];
    for (i = 0; i < mmi; i++) {
      Q->data[i] = b_A->data[i];
    }
  } else {
    i = R->size[0] * R->size[1];
    R->size[0] = b_A->size[0];
    R->size[1] = b_A->size[1];
    emxEnsureCapacity_real_T(R, i);
    for (minmana = 0; minmana < m; minmana++) {
      for (b_i = 0; b_i <= minmana; b_i++) {
        R->data[b_i + R->size[0] * minmana] = b_A->data[b_i + b_A->size[0] *
          minmana];
      }

      i = minmana + 2;
      for (b_i = i; b_i <= m; b_i++) {
        R->data[(b_i + R->size[0] * minmana) - 1] = 0.0;
      }
    }

    i = b_A->size[0] + 1;
    for (minmana = i; minmana <= n; minmana++) {
      for (b_i = 0; b_i < m; b_i++) {
        R->data[b_i + R->size[0] * (minmana - 1)] = b_A->data[b_i + b_A->size[0]
          * (minmana - 1)];
      }
    }

    if (b_A->size[0] >= 1) {
      i = b_A->size[0] - 1;
      for (minmana = m; minmana <= i; minmana++) {
        ia = minmana * m;
        i1 = m - 1;
        for (b_i = 0; b_i <= i1; b_i++) {
          b_A->data[ia + b_i] = 0.0;
        }

        b_A->data[ia + minmana] = 1.0;
      }

      itau = m - 1;
      i = work->size[0];
      work->size[0] = b_A->size[1];
      emxEnsureCapacity_real_T(work, i);
      mmi = b_A->size[1];
      for (i = 0; i < mmi; i++) {
        work->data[i] = 0.0;
      }

      for (b_i = m; b_i >= 1; b_i--) {
        iaii = b_i + (b_i - 1) * m;
        if (b_i < m) {
          b_A->data[iaii - 1] = 1.0;
          mmi = iaii + m;
          if (tau->data[itau] != 0.0) {
            lastc = m - b_i;
            lastv = lastc + 1;
            minmana = mmi - b_i;
            while ((lastv > 0) && (b_A->data[minmana - 1] == 0.0)) {
              lastv--;
              minmana--;
            }

            exitg2 = false;
            while ((!exitg2) && (lastc > 0)) {
              minmana = mmi + (lastc - 1) * m;
              ia = minmana;
              do {
                exitg1 = 0;
                if (ia <= (minmana + lastv) - 1) {
                  if (b_A->data[ia - 1] != 0.0) {
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
              for (minmana = 0; minmana < lastc; minmana++) {
                work->data[minmana] = 0.0;
              }

              minmana = 0;
              i = mmi + m * (lastc - 1);
              for (lda = mmi; m < 0 ? lda >= i : lda <= i; lda += m) {
                minmn = iaii;
                c = 0.0;
                i1 = (lda + lastv) - 1;
                for (ia = lda; ia <= i1; ia++) {
                  c += b_A->data[ia - 1] * b_A->data[minmn - 1];
                  minmn++;
                }

                work->data[minmana] += c;
                minmana++;
              }
            }

            xgerc(lastv, lastc, -tau->data[itau], iaii, work, b_A, mmi, m);
          }

          minmana = iaii + 1;
          i = (iaii + m) - b_i;
          for (mmi = minmana; mmi <= i; mmi++) {
            b_A->data[mmi - 1] *= -tau->data[itau];
          }
        }

        b_A->data[iaii - 1] = 1.0 - tau->data[itau];
        for (minmana = 0; minmana <= b_i - 2; minmana++) {
          b_A->data[(iaii - minmana) - 2] = 0.0;
        }

        itau--;
      }
    }

    i = Q->size[0] * Q->size[1];
    Q->size[0] = m;
    Q->size[1] = m;
    emxEnsureCapacity_real_T(Q, i);
    for (minmana = 0; minmana < m; minmana++) {
      for (b_i = 0; b_i < m; b_i++) {
        Q->data[b_i + Q->size[0] * minmana] = b_A->data[b_i + b_A->size[0] *
          minmana];
      }
    }
  }

  emxFree_real_T(&work);
  emxFree_real_T(&tau);
  emxFree_real_T(&b_A);
}

/*
 * File trailer for qr.c
 *
 * [EOF]
 */

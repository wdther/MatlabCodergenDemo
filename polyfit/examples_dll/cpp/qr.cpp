//
// File: qr.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 03-Aug-2020 22:26:41
//

// Include Files
#include "rt_nonfinite.h"
#include "polyfit.h"
#include "qr.h"
#include "xscal.h"
#include "polyfit_emxutil.h"
#include "xgeqrf.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *A
//                emxArray_real_T *Q
//                emxArray_real_T *R
// Return Type  : void
//
void qr(const emxArray_real_T *A, emxArray_real_T *Q, emxArray_real_T *R)
{
  emxArray_real_T *b_A;
  int i1;
  int i;
  emxArray_real_T *tau;
  int m;
  int n;
  emxArray_real_T *c_A;
  emxArray_real_T *work;
  int jy;
  int j;
  int ijA;
  int b_i;
  int itau;
  unsigned int unnamed_idx_0;
  int iaii;
  int c;
  int lastv;
  int lastc;
  boolean_T exitg2;
  boolean_T exitg4;
  int exitg1;
  int exitg3;
  double b_c;
  int ix;
  emxInit_real_T(&b_A, 2);
  i1 = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = A->size[1];
  emxEnsureCapacity((emxArray__common *)b_A, i1, (int)sizeof(double));
  i = A->size[0] * A->size[1];
  for (i1 = 0; i1 < i; i1++) {
    b_A->data[i1] = A->data[i1];
  }

  emxInit_real_T1(&tau, 1);
  xgeqrf(b_A, tau);
  m = b_A->size[0];
  n = b_A->size[1];
  emxInit_real_T(&c_A, 2);
  emxInit_real_T1(&work, 1);
  if (b_A->size[0] > b_A->size[1]) {
    i = b_A->size[1];
    jy = b_A->size[1];
    i1 = R->size[0] * R->size[1];
    R->size[0] = i;
    R->size[1] = jy;
    emxEnsureCapacity((emxArray__common *)R, i1, (int)sizeof(double));
    for (j = 0; j + 1 <= n; j++) {
      for (b_i = 0; b_i + 1 <= j + 1; b_i++) {
        R->data[b_i + R->size[0] * j] = b_A->data[b_i + b_A->size[0] * j];
      }

      for (b_i = j + 1; b_i + 1 <= n; b_i++) {
        R->data[b_i + R->size[0] * j] = 0.0;
      }
    }

    i1 = c_A->size[0] * c_A->size[1];
    c_A->size[0] = b_A->size[0];
    c_A->size[1] = b_A->size[1];
    emxEnsureCapacity((emxArray__common *)c_A, i1, (int)sizeof(double));
    i = b_A->size[0] * b_A->size[1];
    for (i1 = 0; i1 < i; i1++) {
      c_A->data[i1] = b_A->data[i1];
    }

    if (!(b_A->size[1] < 1)) {
      for (j = b_A->size[1]; j < n; j++) {
        jy = j * m;
        for (b_i = 0; b_i < m; b_i++) {
          c_A->data[jy + b_i] = 0.0;
        }

        c_A->data[jy + j] = 1.0;
      }

      itau = b_A->size[1] - 1;
      unnamed_idx_0 = (unsigned int)c_A->size[1];
      i1 = work->size[0];
      work->size[0] = (int)unnamed_idx_0;
      emxEnsureCapacity((emxArray__common *)work, i1, (int)sizeof(double));
      i = (int)unnamed_idx_0;
      for (i1 = 0; i1 < i; i1++) {
        work->data[i1] = 0.0;
      }

      for (b_i = b_A->size[1]; b_i >= 1; b_i--) {
        iaii = (b_i + (b_i - 1) * m) - 1;
        if (b_i < n) {
          c_A->data[iaii] = 1.0;
          jy = m - b_i;
          c = (iaii + m) + 1;
          if (tau->data[itau] != 0.0) {
            lastv = jy + 1;
            i = iaii + jy;
            while ((lastv > 0) && (c_A->data[i] == 0.0)) {
              lastv--;
              i--;
            }

            lastc = n - b_i;
            exitg4 = false;
            while ((!exitg4) && (lastc > 0)) {
              i = c + (lastc - 1) * m;
              j = i;
              do {
                exitg3 = 0;
                if (j <= (i + lastv) - 1) {
                  if (c_A->data[j - 1] != 0.0) {
                    exitg3 = 1;
                  } else {
                    j++;
                  }
                } else {
                  lastc--;
                  exitg3 = 2;
                }
              } while (exitg3 == 0);

              if (exitg3 == 1) {
                exitg4 = true;
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
              i1 = c + m * (lastc - 1);
              jy = c;
              while ((m > 0) && (jy <= i1)) {
                ix = iaii;
                b_c = 0.0;
                ijA = (jy + lastv) - 1;
                for (j = jy; j <= ijA; j++) {
                  b_c += c_A->data[j - 1] * c_A->data[ix];
                  ix++;
                }

                work->data[i] += b_c;
                i++;
                jy += m;
              }
            }

            if (!(-tau->data[itau] == 0.0)) {
              i = c - 1;
              jy = 0;
              for (j = 1; j <= lastc; j++) {
                if (work->data[jy] != 0.0) {
                  b_c = work->data[jy] * -tau->data[itau];
                  ix = iaii;
                  i1 = lastv + i;
                  for (ijA = i; ijA + 1 <= i1; ijA++) {
                    c_A->data[ijA] += c_A->data[ix] * b_c;
                    ix++;
                  }
                }

                jy++;
                i += m;
              }
            }
          }
        }

        if (b_i < m) {
          xscal(m - b_i, -tau->data[itau], c_A, iaii + 2);
        }

        c_A->data[iaii] = 1.0 - tau->data[itau];
        for (j = 1; j < b_i; j++) {
          c_A->data[iaii - j] = 0.0;
        }

        itau--;
      }
    }

    i1 = Q->size[0] * Q->size[1];
    Q->size[0] = c_A->size[0];
    Q->size[1] = c_A->size[1];
    emxEnsureCapacity((emxArray__common *)Q, i1, (int)sizeof(double));
    i = c_A->size[0] * c_A->size[1];
    for (i1 = 0; i1 < i; i1++) {
      Q->data[i1] = c_A->data[i1];
    }
  } else {
    for (i1 = 0; i1 < 2; i1++) {
      ijA = R->size[0] * R->size[1];
      R->size[i1] = b_A->size[i1];
      emxEnsureCapacity((emxArray__common *)R, ijA, (int)sizeof(double));
    }

    for (j = 0; j + 1 <= m; j++) {
      for (b_i = 0; b_i + 1 <= j + 1; b_i++) {
        R->data[b_i + R->size[0] * j] = b_A->data[b_i + b_A->size[0] * j];
      }

      for (b_i = j + 1; b_i + 1 <= m; b_i++) {
        R->data[b_i + R->size[0] * j] = 0.0;
      }
    }

    for (j = b_A->size[0]; j + 1 <= n; j++) {
      for (b_i = 0; b_i + 1 <= m; b_i++) {
        R->data[b_i + R->size[0] * j] = b_A->data[b_i + b_A->size[0] * j];
      }
    }

    i1 = c_A->size[0] * c_A->size[1];
    c_A->size[0] = b_A->size[0];
    c_A->size[1] = b_A->size[1];
    emxEnsureCapacity((emxArray__common *)c_A, i1, (int)sizeof(double));
    i = b_A->size[0] * b_A->size[1];
    for (i1 = 0; i1 < i; i1++) {
      c_A->data[i1] = b_A->data[i1];
    }

    if (!(b_A->size[0] < 1)) {
      for (j = b_A->size[0]; j < m; j++) {
        jy = j * m;
        for (b_i = 0; b_i < m; b_i++) {
          c_A->data[jy + b_i] = 0.0;
        }

        c_A->data[jy + j] = 1.0;
      }

      itau = b_A->size[0] - 1;
      unnamed_idx_0 = (unsigned int)c_A->size[1];
      i1 = work->size[0];
      work->size[0] = (int)unnamed_idx_0;
      emxEnsureCapacity((emxArray__common *)work, i1, (int)sizeof(double));
      i = (int)unnamed_idx_0;
      for (i1 = 0; i1 < i; i1++) {
        work->data[i1] = 0.0;
      }

      for (b_i = b_A->size[0]; b_i >= 1; b_i--) {
        iaii = (b_i + (b_i - 1) * m) - 1;
        if (b_i < m) {
          c_A->data[iaii] = 1.0;
          jy = m - b_i;
          c = (iaii + m) + 1;
          if (tau->data[itau] != 0.0) {
            lastv = jy + 1;
            i = iaii + jy;
            while ((lastv > 0) && (c_A->data[i] == 0.0)) {
              lastv--;
              i--;
            }

            lastc = m - b_i;
            exitg2 = false;
            while ((!exitg2) && (lastc > 0)) {
              i = c + (lastc - 1) * m;
              j = i;
              do {
                exitg1 = 0;
                if (j <= (i + lastv) - 1) {
                  if (c_A->data[j - 1] != 0.0) {
                    exitg1 = 1;
                  } else {
                    j++;
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
              i1 = c + m * (lastc - 1);
              for (jy = c; jy <= i1; jy += m) {
                ix = iaii;
                b_c = 0.0;
                ijA = (jy + lastv) - 1;
                for (j = jy; j <= ijA; j++) {
                  b_c += c_A->data[j - 1] * c_A->data[ix];
                  ix++;
                }

                work->data[i] += b_c;
                i++;
              }
            }

            if (!(-tau->data[itau] == 0.0)) {
              i = c - 1;
              jy = 0;
              for (j = 1; j <= lastc; j++) {
                if (work->data[jy] != 0.0) {
                  b_c = work->data[jy] * -tau->data[itau];
                  ix = iaii;
                  i1 = lastv + i;
                  for (ijA = i; ijA + 1 <= i1; ijA++) {
                    c_A->data[ijA] += c_A->data[ix] * b_c;
                    ix++;
                  }
                }

                jy++;
                i += m;
              }
            }
          }

          xscal(m - b_i, -tau->data[itau], c_A, iaii + 2);
        }

        c_A->data[iaii] = 1.0 - tau->data[itau];
        for (j = 1; j < b_i; j++) {
          c_A->data[iaii - j] = 0.0;
        }

        itau--;
      }
    }

    i = b_A->size[0];
    jy = b_A->size[0];
    i1 = Q->size[0] * Q->size[1];
    Q->size[0] = i;
    Q->size[1] = jy;
    emxEnsureCapacity((emxArray__common *)Q, i1, (int)sizeof(double));
    for (j = 0; j + 1 <= m; j++) {
      for (b_i = 0; b_i + 1 <= m; b_i++) {
        Q->data[b_i + Q->size[0] * j] = c_A->data[b_i + c_A->size[0] * j];
      }
    }
  }

  emxFree_real_T(&work);
  emxFree_real_T(&tau);
  emxFree_real_T(&b_A);
  emxFree_real_T(&c_A);
}

//
// File trailer for qr.cpp
//
// [EOF]
//

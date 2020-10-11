//
// File: xgeqrf.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 03-Aug-2020 22:26:41
//

// Include Files
#include "rt_nonfinite.h"
#include "polyfit.h"
#include "xgeqrf.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include "polyfit_emxutil.h"

// Function Definitions

//
// Arguments    : emxArray_real_T *A
//                emxArray_real_T *tau
// Return Type  : void
//
void xgeqrf(emxArray_real_T *A, emxArray_real_T *tau)
{
  int m;
  int n;
  int mn;
  int i;
  emxArray_real_T *work;
  int i_i;
  int mmi;
  double atmp;
  m = A->size[0];
  n = A->size[1];
  if (A->size[0] <= A->size[1]) {
    mn = A->size[0];
  } else {
    mn = A->size[1];
  }

  i = tau->size[0];
  tau->size[0] = mn;
  emxEnsureCapacity((emxArray__common *)tau, i, (int)sizeof(double));
  if (!((A->size[0] == 0) || (A->size[1] == 0))) {
    emxInit_real_T1(&work, 1);
    i_i = A->size[1];
    i = work->size[0];
    work->size[0] = i_i;
    emxEnsureCapacity((emxArray__common *)work, i, (int)sizeof(double));
    for (i = 0; i < i_i; i++) {
      work->data[i] = 0.0;
    }

    for (i = 0; i + 1 <= mn; i++) {
      i_i = i + i * m;
      mmi = m - i;
      if (i + 1 < m) {
        atmp = A->data[i_i];
        tau->data[i] = xzlarfg(mmi, &atmp, A, i_i + 2);
        A->data[i_i] = atmp;
      } else {
        tau->data[i] = 0.0;
      }

      if (i + 1 < n) {
        atmp = A->data[i_i];
        A->data[i_i] = 1.0;
        xzlarf(mmi, (n - i) - 1, i_i + 1, tau->data[i], A, (i + (i + 1) * m) + 1,
               m, work);
        A->data[i_i] = atmp;
      }
    }

    emxFree_real_T(&work);
  }
}

//
// File trailer for xgeqrf.cpp
//
// [EOF]
//

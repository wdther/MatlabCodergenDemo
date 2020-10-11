//
// File: polyfit.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 03-Aug-2020 22:26:41
//

// Include Files
#include "rt_nonfinite.h"
#include "polyfit.h"
#include "polyfit_emxutil.h"
#include "mldivide.h"
#include "qr.h"

// Function Definitions

//
// POLYFIT Fit polynomial to data.
//    P = POLYFIT(X,Y,N) finds the coefficients of a polynomial P(X) of
//    degree N that fits the data Y best in a least-squares sense. P is a
//    row vector of length N+1 containing the polynomial coefficients in
//    descending powers, P(1)*X^N + P(2)*X^(N-1) +...+ P(N)*X + P(N+1).
//
//    [P,S] = POLYFIT(X,Y,N) returns the polynomial coefficients P and a
//    structure S for use with POLYVAL to obtain error estimates for
//    predictions.  S contains fields for the triangular factor (R) from a QR
//    decomposition of the Vandermonde matrix of X, the degrees of freedom
//    (df), and the norm of the residuals (normr).  If the data Y are random,
//    an estimate of the covariance matrix of P is (Rinv*Rinv')*normr^2/df,
//    where Rinv is the inverse of R.
//
//    [P,S,MU] = POLYFIT(X,Y,N) finds the coefficients of a polynomial in
//    XHAT = (X-MU(1))/MU(2) where MU(1) = MEAN(X) and MU(2) = STD(X). This
//    centering and scaling transformation improves the numerical properties
//    of both the polynomial and the fitting algorithm.
//
//    Warning messages result if N is >= length(X), if X has repeated, or
//    nearly repeated, points, or if X might need centering and scaling.
// V
//    Class support for inputs X,Y:
//       float: double, single
//
//    See also POLY, POLYVAL, ROOTS, LSCOV.
// Arguments    : const emxArray_real_T *x
//                const emxArray_real_T *y
//                double n
//                emxArray_real_T *p
//                struct0_T *S
// Return Type  : void
//
void polyfit(const emxArray_real_T *x, const emxArray_real_T *y, double n,
             emxArray_real_T *p, struct0_T *S)
{
  emxArray_real_T *V;
  int ar;
  int i0;
  int loop_ub;
  int ia;
  emxArray_real_T *b_x;
  double varargin_2;
  emxArray_real_T *Q;
  emxArray_real_T *R;
  int ic;
  emxArray_real_T *a;
  emxArray_real_T *b_y;
  boolean_T guard1 = false;
  int k;
  unsigned int a_idx_0;
  emxArray_real_T *b_p;
  int m;
  emxArray_real_T *r;
  int br;
  double scale;
  double absxk;
  double t;
  emxInit_real_T(&V, 2);

  //    Copyright 1984-2011 The MathWorks, Inc.
  //  The regression problem is formulated in matrix format as:
  //
  //     y = V*p    or
  //
  //           3  2
  //     y = [x  x  x  1] [p3
  //                       p2
  //                       p1
  //                       p0]
  //
  //  where the vector p contains the coefficients to be found.  For a
  //  7th order polynomial, matrix V would be:
  //
  //  V = [x.^7 x.^6 x.^5 x.^4 x.^3 x.^2 x ones(size(x))];
  //  Construct Vandermonde matrix.
  ar = x->size[1];
  i0 = V->size[0] * V->size[1];
  V->size[0] = ar;
  V->size[1] = (int)(n + 1.0);
  emxEnsureCapacity((emxArray__common *)V, i0, (int)sizeof(double));
  ar = x->size[1];
  loop_ub = ar * (int)(n + 1.0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    V->data[i0] = 0.0;
  }

  ar = x->size[1];
  for (i0 = 0; i0 < ar; i0++) {
    V->data[i0 + V->size[0] * ((int)(n + 1.0) - 1)] = 1.0;
  }

  i0 = (int)((1.0 + (-1.0 - n)) / -1.0);
  ia = 0;
  emxInit_real_T1(&b_x, 1);
  while (ia <= i0 - 1) {
    varargin_2 = n + -(double)ia;
    ar = x->size[1];
    ic = b_x->size[0];
    b_x->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)b_x, ic, (int)sizeof(double));
    for (ic = 0; ic < ar; ic++) {
      b_x->data[ic] = x->data[ic] * V->data[ic + V->size[0] * ((int)(varargin_2
        + 1.0) - 1)];
    }

    loop_ub = b_x->size[0];
    for (ic = 0; ic < loop_ub; ic++) {
      V->data[ic + V->size[0] * ((int)varargin_2 - 1)] = b_x->data[ic];
    }

    ia++;
  }

  emxFree_real_T(&b_x);
  emxInit_real_T(&Q, 2);
  emxInit_real_T(&R, 2);
  emxInit_real_T(&a, 2);

  //  Solve least squares problem.
  qr(V, Q, R);
  i0 = a->size[0] * a->size[1];
  a->size[0] = Q->size[1];
  a->size[1] = Q->size[0];
  emxEnsureCapacity((emxArray__common *)a, i0, (int)sizeof(double));
  loop_ub = Q->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    ar = Q->size[1];
    for (ic = 0; ic < ar; ic++) {
      a->data[ic + a->size[0] * i0] = Q->data[i0 + Q->size[0] * ic];
    }
  }

  emxFree_real_T(&Q);
  emxInit_real_T1(&b_y, 1);
  guard1 = false;
  if (a->size[1] == 1) {
    guard1 = true;
  } else {
    ar = y->size[1];
    if (ar == 1) {
      guard1 = true;
    } else {
      k = a->size[1];
      a_idx_0 = (unsigned int)a->size[0];
      i0 = b_y->size[0];
      b_y->size[0] = (int)a_idx_0;
      emxEnsureCapacity((emxArray__common *)b_y, i0, (int)sizeof(double));
      m = a->size[0];
      ar = b_y->size[0];
      i0 = b_y->size[0];
      b_y->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)b_y, i0, (int)sizeof(double));
      for (i0 = 0; i0 < ar; i0++) {
        b_y->data[i0] = 0.0;
      }

      if (a->size[0] != 0) {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            b_y->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = -1;
          i0 = br + k;
          for (loop_ub = br; loop_ub + 1 <= i0; loop_ub++) {
            if (y->data[loop_ub] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                b_y->data[ic] += y->data[loop_ub] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }
  }

  if (guard1) {
    i0 = b_y->size[0];
    b_y->size[0] = a->size[0];
    emxEnsureCapacity((emxArray__common *)b_y, i0, (int)sizeof(double));
    loop_ub = a->size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      b_y->data[i0] = 0.0;
      ar = a->size[1];
      for (ic = 0; ic < ar; ic++) {
        b_y->data[i0] += a->data[i0 + a->size[0] * ic] * y->data[ic];
      }
    }
  }

  emxFree_real_T(&a);
  emxInit_real_T1(&b_p, 1);
  mldivide(R, b_y, b_p);

  //  Same as p = V\y;
  emxFree_real_T(&b_y);
  emxInit_real_T1(&r, 1);
  if ((V->size[1] == 1) || (b_p->size[0] == 1)) {
    i0 = r->size[0];
    r->size[0] = V->size[0];
    emxEnsureCapacity((emxArray__common *)r, i0, (int)sizeof(double));
    loop_ub = V->size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      r->data[i0] = 0.0;
      ar = V->size[1];
      for (ic = 0; ic < ar; ic++) {
        r->data[i0] += V->data[i0 + V->size[0] * ic] * b_p->data[ic];
      }
    }
  } else {
    k = V->size[1];
    a_idx_0 = (unsigned int)V->size[0];
    i0 = r->size[0];
    r->size[0] = (int)a_idx_0;
    emxEnsureCapacity((emxArray__common *)r, i0, (int)sizeof(double));
    m = V->size[0];
    ar = r->size[0];
    i0 = r->size[0];
    r->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)r, i0, (int)sizeof(double));
    for (i0 = 0; i0 < ar; i0++) {
      r->data[i0] = 0.0;
    }

    if (V->size[0] != 0) {
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        for (ic = 1; ic <= m; ic++) {
          r->data[ic - 1] = 0.0;
        }

        ar = m;
      }

      br = 0;
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        ar = -1;
        i0 = br + k;
        for (loop_ub = br; loop_ub + 1 <= i0; loop_ub++) {
          if (b_p->data[loop_ub] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= m; ic++) {
              ia++;
              r->data[ic] += b_p->data[loop_ub] * V->data[ia];
            }
          }

          ar += m;
        }

        br += k;
        ar = m;
      }
    }
  }

  emxFree_real_T(&V);
  i0 = r->size[0];
  r->size[0] = y->size[1];
  emxEnsureCapacity((emxArray__common *)r, i0, (int)sizeof(double));
  loop_ub = y->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r->data[i0] = y->data[i0] - r->data[i0];
  }

  //  S is a structure containing three elements: the triangular factor from a
  //  QR decomposition of the Vandermonde matrix, the degrees of freedom and
  //  the norm of the residuals.
  i0 = S->R->size[0] * S->R->size[1];
  S->R->size[0] = R->size[0];
  S->R->size[1] = R->size[1];
  emxEnsureCapacity((emxArray__common *)S->R, i0, (int)sizeof(double));
  loop_ub = R->size[0] * R->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    S->R->data[i0] = R->data[i0];
  }

  emxFree_real_T(&R);
  ar = y->size[1];
  varargin_2 = (double)ar - (n + 1.0);
  if ((0.0 >= varargin_2) || rtIsNaN(varargin_2)) {
    S->df = 0.0;
  } else {
    S->df = varargin_2;
  }

  if (r->size[0] == 0) {
    varargin_2 = 0.0;
  } else {
    varargin_2 = 0.0;
    if (r->size[0] == 1) {
      varargin_2 = std::abs(r->data[0]);
    } else {
      scale = 2.2250738585072014E-308;
      for (k = 1; k <= r->size[0]; k++) {
        absxk = std::abs(r->data[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          varargin_2 = 1.0 + varargin_2 * t * t;
          scale = absxk;
        } else {
          t = absxk / scale;
          varargin_2 += t * t;
        }
      }

      varargin_2 = scale * std::sqrt(varargin_2);
    }
  }

  emxFree_real_T(&r);
  S->normr = varargin_2;
  i0 = p->size[0] * p->size[1];
  p->size[0] = 1;
  p->size[1] = b_p->size[0];
  emxEnsureCapacity((emxArray__common *)p, i0, (int)sizeof(double));
  loop_ub = b_p->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    p->data[p->size[0] * i0] = b_p->data[i0];
  }

  emxFree_real_T(&b_p);

  //  Polynomial coefficients are row vectors by convention.
}

//
// File trailer for polyfit.cpp
//
// [EOF]
//

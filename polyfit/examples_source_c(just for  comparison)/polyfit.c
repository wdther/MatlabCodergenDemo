/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: polyfit.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 04-Aug-2020 12:54:05
 */

/* Include Files */
#include "polyfit.h"
#include "polyfit_data.h"
#include "polyfit_emxutil.h"
#include "polyfit_initialize.h"
#include "qr.h"
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */

/*
 * POLYFIT Fit polynomial to data.
 *    P = POLYFIT(X,Y,N) finds the coefficients of a polynomial P(X) of
 *    degree N that fits the data Y best in a least-squares sense. P is a
 *    row vector of length N+1 containing the polynomial coefficients in
 *    descending powers, P(1)*X^N + P(2)*X^(N-1) +...+ P(N)*X + P(N+1).
 *
 *    [P,S] = POLYFIT(X,Y,N) returns the polynomial coefficients P and a
 *    structure S for use with POLYVAL to obtain error estimates for
 *    predictions.  S contains fields for the triangular factor (R) from a QR
 *    decomposition of the Vandermonde matrix of X, the degrees of freedom
 *    (df), and the norm of the residuals (normr).  If the data Y are random,
 *    an estimate of the covariance matrix of P is (Rinv*Rinv')*normr^2/df,
 *    where Rinv is the inverse of R.
 *
 *    [P,S,MU] = POLYFIT(X,Y,N) finds the coefficients of a polynomial in
 *    XHAT = (X-MU(1))/MU(2) where MU(1) = MEAN(X) and MU(2) = STD(X). This
 *    centering and scaling transformation improves the numerical properties
 *    of both the polynomial and the fitting algorithm.
 *
 *    Warning messages result if N is >= length(X), if X has repeated, or
 *    nearly repeated, points, or if X might need centering and scaling.
 * V
 *    Class support for inputs X,Y:
 *       float: double, single
 *
 *    See also POLY, POLYVAL, ROOTS, LSCOV.
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *y
 *                double n
 *                emxArray_real_T *p
 *                struct0_T *S
 * Return Type  : void
 */
void polyfit(const emxArray_real_T *x, const emxArray_real_T *y, double n,
             emxArray_real_T *p, struct0_T *S)
{
  emxArray_real_T *V;
  int i;
  int k;
  int inner;
  int aoffset;
  emxArray_real_T *r;
  int j;
  int m;
  emxArray_real_T *Q;
  double smax;
  emxArray_real_T *R;
  emxArray_real_T *a;
  int b_i;
  emxArray_real_T *b_p;
  emxArray_int32_T *ipiv;
  int b_n;
  int ldap1;
  int u1;
  int mmj_tmp;
  int jj;
  int ix;
  double s;
  double absxk;
  double t;
  if (isInitialized_polyfit == false) {
    polyfit_initialize();
  }

  emxInit_real_T(&V, 2);

  /*    Copyright 1984-2011 The MathWorks, Inc. */
  /*  The regression problem is formulated in matrix format as: */
  /*  */
  /*     y = V*p    or */
  /*  */
  /*           3  2 */
  /*     y = [x  x  x  1] [p3 */
  /*                       p2 */
  /*                       p1 */
  /*                       p0] */
  /*  */
  /*  where the vector p contains the coefficients to be found.  For a */
  /*  7th order polynomial, matrix V would be: */
  /*  */
  /*  V = [x.^7 x.^6 x.^5 x.^4 x.^3 x.^2 x ones(size(x))]; */
  /*  Construct Vandermonde matrix. */
  i = V->size[0] * V->size[1];
  V->size[0] = x->size[1];
  k = (int)(n + 1.0);
  V->size[1] = k;
  emxEnsureCapacity_real_T(V, i);
  inner = x->size[1] * k;
  for (i = 0; i < inner; i++) {
    V->data[i] = 0.0;
  }

  aoffset = x->size[1];
  inner = x->size[1];
  for (i = 0; i < inner; i++) {
    V->data[i + V->size[0] * (k - 1)] = 1.0;
  }

  i = (int)(((-1.0 - n) + 1.0) / -1.0);
  emxInit_real_T(&r, 1);
  if (0 <= i - 1) {
    aoffset = x->size[1];
    m = x->size[1];
  }

  for (j = 0; j < i; j++) {
    smax = n + -(double)j;
    k = r->size[0];
    r->size[0] = aoffset;
    emxEnsureCapacity_real_T(r, k);
    for (k = 0; k < m; k++) {
      r->data[k] = x->data[k] * V->data[k + V->size[0] * (int)smax];
    }

    inner = r->size[0];
    for (k = 0; k < inner; k++) {
      V->data[k + V->size[0] * ((int)smax - 1)] = r->data[k];
    }
  }

  emxInit_real_T(&Q, 2);
  emxInit_real_T(&R, 2);
  emxInit_real_T(&a, 2);

  /*  Solve least squares problem. */
  qr(V, Q, R);
  i = a->size[0] * a->size[1];
  a->size[0] = Q->size[1];
  a->size[1] = Q->size[0];
  emxEnsureCapacity_real_T(a, i);
  inner = Q->size[0];
  for (i = 0; i < inner; i++) {
    m = Q->size[1];
    for (k = 0; k < m; k++) {
      a->data[k + a->size[0] * i] = Q->data[i + Q->size[0] * k];
    }
  }

  if ((a->size[1] == 1) || (y->size[1] == 1)) {
    i = r->size[0];
    r->size[0] = a->size[0];
    emxEnsureCapacity_real_T(r, i);
    inner = a->size[0];
    for (i = 0; i < inner; i++) {
      r->data[i] = 0.0;
      m = a->size[1];
      for (k = 0; k < m; k++) {
        r->data[i] += a->data[i + a->size[0] * k] * y->data[k];
      }
    }
  } else {
    m = a->size[0];
    inner = a->size[1];
    i = r->size[0];
    r->size[0] = a->size[0];
    emxEnsureCapacity_real_T(r, i);
    for (b_i = 0; b_i < m; b_i++) {
      r->data[b_i] = 0.0;
    }

    for (k = 0; k < inner; k++) {
      aoffset = k * m;
      for (b_i = 0; b_i < m; b_i++) {
        r->data[b_i] += y->data[k] * a->data[aoffset + b_i];
      }
    }
  }

  emxFree_real_T(&a);
  emxInit_real_T(&b_p, 1);
  emxInit_int32_T(&ipiv, 2);
  if ((R->size[0] == 0) || (R->size[1] == 0) || (r->size[0] == 0)) {
    i = b_p->size[0];
    b_p->size[0] = R->size[1];
    emxEnsureCapacity_real_T(b_p, i);
    inner = R->size[1];
    for (i = 0; i < inner; i++) {
      b_p->data[i] = 0.0;
    }
  } else if (R->size[0] == R->size[1]) {
    b_n = R->size[1];
    i = Q->size[0] * Q->size[1];
    Q->size[0] = R->size[0];
    Q->size[1] = R->size[1];
    emxEnsureCapacity_real_T(Q, i);
    inner = R->size[0] * R->size[1];
    for (i = 0; i < inner; i++) {
      Q->data[i] = R->data[i];
    }

    m = R->size[1];
    i = ipiv->size[0] * ipiv->size[1];
    ipiv->size[0] = 1;
    ipiv->size[1] = R->size[1];
    emxEnsureCapacity_int32_T(ipiv, i);
    ipiv->data[0] = 1;
    aoffset = 1;
    for (k = 2; k <= m; k++) {
      aoffset++;
      ipiv->data[k - 1] = aoffset;
    }

    ldap1 = R->size[1];
    aoffset = R->size[1] - 1;
    u1 = R->size[1];
    if (aoffset < u1) {
      u1 = aoffset;
    }

    for (j = 0; j < u1; j++) {
      mmj_tmp = b_n - j;
      m = j * (b_n + 1);
      jj = j * (ldap1 + 1);
      inner = m + 2;
      if (mmj_tmp < 1) {
        aoffset = -1;
      } else {
        aoffset = 0;
        if (mmj_tmp > 1) {
          ix = m;
          smax = fabs(Q->data[jj]);
          for (k = 2; k <= mmj_tmp; k++) {
            ix++;
            s = fabs(Q->data[ix]);
            if (s > smax) {
              aoffset = k - 1;
              smax = s;
            }
          }
        }
      }

      if (Q->data[jj + aoffset] != 0.0) {
        if (aoffset != 0) {
          aoffset += j;
          ipiv->data[j] = aoffset + 1;
          ix = j;
          for (k = 0; k < b_n; k++) {
            smax = Q->data[ix];
            Q->data[ix] = Q->data[aoffset];
            Q->data[aoffset] = smax;
            ix += b_n;
            aoffset += b_n;
          }
        }

        i = jj + mmj_tmp;
        for (b_i = inner; b_i <= i; b_i++) {
          Q->data[b_i - 1] /= Q->data[jj];
        }
      }

      aoffset = m + b_n;
      m = jj + ldap1;
      for (inner = 0; inner <= mmj_tmp - 2; inner++) {
        smax = Q->data[aoffset];
        if (Q->data[aoffset] != 0.0) {
          ix = jj + 1;
          i = m + 2;
          k = mmj_tmp + m;
          for (b_i = i; b_i <= k; b_i++) {
            Q->data[b_i - 1] += Q->data[ix] * -smax;
            ix++;
          }
        }

        aoffset += b_n;
        m += b_n;
      }
    }

    i = b_p->size[0];
    b_p->size[0] = r->size[0];
    emxEnsureCapacity_real_T(b_p, i);
    inner = r->size[0];
    for (i = 0; i < inner; i++) {
      b_p->data[i] = r->data[i];
    }

    i = R->size[1];
    for (aoffset = 0; aoffset <= i - 2; aoffset++) {
      k = ipiv->data[aoffset];
      if (k != aoffset + 1) {
        smax = b_p->data[aoffset];
        b_p->data[aoffset] = b_p->data[k - 1];
        b_p->data[k - 1] = smax;
      }
    }

    for (k = 0; k < b_n; k++) {
      aoffset = b_n * k;
      if (b_p->data[k] != 0.0) {
        i = k + 2;
        for (b_i = i; b_i <= b_n; b_i++) {
          b_p->data[b_i - 1] -= b_p->data[k] * Q->data[(b_i + aoffset) - 1];
        }
      }
    }

    for (k = b_n; k >= 1; k--) {
      aoffset = b_n * (k - 1);
      smax = b_p->data[k - 1];
      if (smax != 0.0) {
        b_p->data[k - 1] = smax / Q->data[(k + aoffset) - 1];
        for (b_i = 0; b_i <= k - 2; b_i++) {
          b_p->data[b_i] -= b_p->data[k - 1] * Q->data[b_i + aoffset];
        }
      }
    }
  } else {
    qrsolve(R, r, b_p);
  }

  emxFree_int32_T(&ipiv);
  emxFree_real_T(&Q);

  /*  Same as p = V\y; */
  if ((V->size[1] == 1) || (b_p->size[0] == 1)) {
    i = r->size[0];
    r->size[0] = V->size[0];
    emxEnsureCapacity_real_T(r, i);
    inner = V->size[0];
    for (i = 0; i < inner; i++) {
      r->data[i] = 0.0;
      m = V->size[1];
      for (k = 0; k < m; k++) {
        r->data[i] += V->data[i + V->size[0] * k] * b_p->data[k];
      }
    }
  } else {
    m = V->size[0];
    inner = V->size[1];
    i = r->size[0];
    r->size[0] = V->size[0];
    emxEnsureCapacity_real_T(r, i);
    for (b_i = 0; b_i < m; b_i++) {
      r->data[b_i] = 0.0;
    }

    for (k = 0; k < inner; k++) {
      aoffset = k * m;
      for (b_i = 0; b_i < m; b_i++) {
        r->data[b_i] += b_p->data[k] * V->data[aoffset + b_i];
      }
    }
  }

  emxFree_real_T(&V);
  inner = y->size[1];
  i = r->size[0];
  r->size[0] = y->size[1];
  emxEnsureCapacity_real_T(r, i);
  for (i = 0; i < inner; i++) {
    r->data[i] = y->data[i] - r->data[i];
  }

  /*  S is a structure containing three elements: the triangular factor from a */
  /*  QR decomposition of the Vandermonde matrix, the degrees of freedom and */
  /*  the norm of the residuals. */
  i = S->R->size[0] * S->R->size[1];
  S->R->size[0] = R->size[0];
  S->R->size[1] = R->size[1];
  emxEnsureCapacity_real_T(S->R, i);
  inner = R->size[0] * R->size[1];
  for (i = 0; i < inner; i++) {
    S->R->data[i] = R->data[i];
  }

  emxFree_real_T(&R);
  S->df = fmax(0.0, (double)y->size[1] - (n + 1.0));
  if (r->size[0] == 0) {
    S->normr = 0.0;
  } else {
    smax = 0.0;
    if (r->size[0] == 1) {
      S->normr = fabs(r->data[0]);
    } else {
      s = 3.3121686421112381E-170;
      aoffset = r->size[0];
      for (k = 0; k < aoffset; k++) {
        absxk = fabs(r->data[k]);
        if (absxk > s) {
          t = s / absxk;
          smax = smax * t * t + 1.0;
          s = absxk;
        } else {
          t = absxk / s;
          smax += t * t;
        }
      }

      S->normr = s * sqrt(smax);
    }
  }

  emxFree_real_T(&r);
  i = p->size[0] * p->size[1];
  p->size[0] = 1;
  p->size[1] = b_p->size[0];
  emxEnsureCapacity_real_T(p, i);
  inner = b_p->size[0];
  for (i = 0; i < inner; i++) {
    p->data[i] = b_p->data[i];
  }

  emxFree_real_T(&b_p);

  /*  Polynomial coefficients are row vectors by convention. */
}

/*
 * File trailer for polyfit.c
 *
 * [EOF]
 */

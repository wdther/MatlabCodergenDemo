//
// File: std.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 03-Aug-2020 20:49:19
//

// Include Files
#include "rt_nonfinite.h"
#include "polyfit.h"
#include "std.h"

// Function Definitions

//
// Arguments    : const double varargin_1[3]
// Return Type  : double
//
double b_std(const double varargin_1[3])
{
  double y;
  int ix;
  double xbar;
  int k;
  double r;
  ix = 0;
  xbar = varargin_1[0];
  for (k = 0; k < 2; k++) {
    ix++;
    xbar += varargin_1[ix];
  }

  xbar /= 3.0;
  ix = 0;
  r = varargin_1[0] - xbar;
  y = r * r;
  for (k = 0; k < 2; k++) {
    ix++;
    r = varargin_1[ix] - xbar;
    y += r * r;
  }

  y /= 2.0;
  return std::sqrt(y);
}

//
// File trailer for std.cpp
//
// [EOF]
//

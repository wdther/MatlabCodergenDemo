//
// File: colon.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 03-Aug-2020 22:26:41
//

// Include Files
#include "rt_nonfinite.h"
#include "polyfit.h"
#include "colon.h"
#include "polyfit_emxutil.h"

// Function Definitions

//
// Arguments    : int b
//                emxArray_int32_T *y
// Return Type  : void
//
void eml_signed_integer_colon(int b, emxArray_int32_T *y)
{
  int n;
  int yk;
  int k;
  if (b < 1) {
    n = 0;
  } else {
    n = b;
  }

  yk = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity((emxArray__common *)y, yk, (int)sizeof(int));
  if (n > 0) {
    y->data[0] = 1;
    yk = 1;
    for (k = 2; k <= n; k++) {
      yk++;
      y->data[k - 1] = yk;
    }
  }
}

//
// File trailer for colon.cpp
//
// [EOF]
//

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: polyfit_initialize.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 04-Aug-2020 12:54:05
 */

/* Include Files */
#include "polyfit_initialize.h"
#include "polyfit.h"
#include "polyfit_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void polyfit_initialize(void)
{
  rt_InitInfAndNaN();
  isInitialized_polyfit = true;
}

/*
 * File trailer for polyfit_initialize.c
 *
 * [EOF]
 */

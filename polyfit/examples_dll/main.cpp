//
// File: main.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 03-Aug-2020 22:26:41
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
//#include "main.h"
#include "polyfit.h"
#include "polyfit_emxAPI.h"
#include "polyfit_terminate.h"
#include "rt_nonfinite.h"
#include <iostream>
using namespace std;
// Function Declarations
static emxArray_real_T *argInit_1xUnbounded_real_T();
static double argInit_real_T();
static void main_polyfit();

// Function Definitions

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T *argInit_1xUnbounded_real_T()
{
  emxArray_real_T *result;
  static int iv0[2] = { 1, 2 };

  int idx1;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result = emxCreateND_real_T(2, *(int (*)[2])&iv0[0]);

  // Loop over the array to initialize each element.
  for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result->data[result->size[0] * idx1] = argInit_real_T();
  }

  return result;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_polyfit()
{
  emxArray_real_T *p;
  struct0_T S;
  emxArray_real_T *x;
  emxArray_real_T *y;
  emxInitArray_real_T(&p, 2);
  emxInit_struct0_T(&S);



  x = argInit_1xUnbounded_real_T();

  // Initialize function input argument 'y'.
  y = argInit_1xUnbounded_real_T();
//测试y=x+5
    double xx[]={1,2,3,4};
    double yy[]={6,7,8,9};
    x->data=xx;
    y->data=yy;


  // Call the entry-point 'polyfit'.
  polyfit(x, y, 1, p, &S);
  cout<<"p "<<p->data[0]<<" | "<<p->data[1]<<endl;

//  emxDestroy_struct0_T(S);
//  emxDestroyArray_real_T(p);
//  emxDestroyArray_real_T(y);
//  emxDestroyArray_real_T(x);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  main_polyfit();

  polyfit_terminate();

  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//

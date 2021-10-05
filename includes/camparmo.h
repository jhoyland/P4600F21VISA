
// JAMES: There is no need to include these header files
// here as none of their functions or definitions are needed
// in this file itself.

// Also remember the "header guards" to prevent multiple inclusion.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double smoothed(int n, double *x, int w, double *ave);
double mean(int n, double *x);
double RMS(int n, double *x);
double Amp(int n, double *x);
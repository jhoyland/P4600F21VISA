#ifndef __CALCULATIONS_H
#define __CALCULATIONS_H

void smoothing(double* x, int n, int w, double* xSmoothed);
double mean(double* xSmoothed, int n);
double rootMeanSquare(double* xSmoothed, int n);


#endif

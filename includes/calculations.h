#ifndef __CALCULATIONS_H
#define __CALCULATIONS_H

void smoothing(double* dataArray, int n, int w, double* dataArraySmoothed);
double mean(double* dataArraySmoothed, int n);
double rootMeanSquare(double* dataArraySmoothed, int n);
double amplitude(double* dataArraySmoothed, int n);


#endif

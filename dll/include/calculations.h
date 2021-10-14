#ifndef __CALCULATIONS_H
#define __CALCULATIONS_H

void convertCurveToVoltage(int n, char* rawDataArray, float scale, double* voltages);
void smoothing(double* voltages, int n, int w, double* voltagesSmoothed);
double mean(double* voltagesSmoothed, int n);
double rootMeanSquare(double* voltagesSmoothed, int n);
double amplitude(double* voltagesSmoothed, int n);

#endif

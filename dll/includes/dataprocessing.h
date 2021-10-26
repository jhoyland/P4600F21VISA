#ifndef __DATAPROCESSING_H
#define __DATAPROCESSING_H

float mean(float num[], int n);
double stdev(double num[], double mean, int n);
double rms(double num[], int n);
double Amp(double num[], int n);
double smooth(double *d, int n, int w, double* end);

#endif
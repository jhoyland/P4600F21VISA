#ifndef __DATAPROCESSING_H
#define __DATAPROCESSING_H

float mean(float num[], int n);
float stdev(float num[], float mean, int n);
float rms(float num[], int n);
float Amp(float num[], int n);
float smooth(double *d, int n, int w, double* end);

#endif
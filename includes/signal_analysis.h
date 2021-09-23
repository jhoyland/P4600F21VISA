#ifndef __SIGNALANALYSIS_H
#define __SIGNALANALYSIS_H

double SA_Mean(int n, double * data);
double SA_RMS(int n, double * data, double mean);
double SA_Amplitude(double rms);
void SA_smooth(int n, int m, double * data, double * result);

#endif
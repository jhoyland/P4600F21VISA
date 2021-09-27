#ifndef __SIGNALANALYSIS_H
#define __SIGNALANALYSIS_H

// JAMES: Just as a matter of style, since your header name is
// signal_analysis.h the header guard name would usually be
// __SIGNAL_ANALYSIS_H

double SA_Mean(int n, double * data);
double SA_RMS(int n, double * data, double mean);
double SA_Amplitude(double rms);
void SA_smooth(int n, int m, double * data, double * result);

#endif

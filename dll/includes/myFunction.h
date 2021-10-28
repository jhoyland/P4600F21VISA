#ifndef __MYFUNCTION_H
#define __MYFUNCTION_H

double mean(double* data, int ndata);
double rms(double *data, double avg, int ndata);
double amplitude(double Vrms, double Voffset);
void smooth(double* data, int ndata, int window, double* newData);
#endif

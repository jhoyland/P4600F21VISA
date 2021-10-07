#ifndef __CALCFUNCTIONS_DOT_H  //if not defined or ignore the below code
#define __CALCFUNCTIONS_DOT_H  //creates a compilation variable
#include "visa.h"

double mean(double* data, int length);
double rms(double* data, int length, double mean);
double amplitude(double rms);
void smooth(double* data, int length, int filterLength, double* smoothed);
int adcConvert(char* data, double* converted, double volts);
double grabVoltsDiv(ViSession scope_handle);

#endif
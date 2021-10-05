#ifndef __CALCFUNCTIONS_DOT_H  //if not defined or ignore the below code
#define __CALCFUNCTIONS_DOT_H  //creates a compilation variable

double mean(double* data, int length);
double rms(double* data, int length, double mean);
double amplitude(double* data, int length, double rms);
void smooth(double* data, int length, int filterLength, double* smoothed);
int adcConvert(char* data, double* converted);

#endif
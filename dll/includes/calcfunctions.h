#ifndef __CALCFUNCTIONS_DOT_H  //if not defined or ignore the below code
#define __CALCFUNCTIONS_DOT_H  //creates a compilation variable
#include "visa.h"

double mean(double* data, int length);
double rms(double* data, int length, double mean);
double amplitude(double rms);
void smooth(double* data, int length, int filterLength, double* smoothed);
int adcConvert(char* data, double* converted, double volts);
void writeToFile(char* name, double start_freq, double amplength, double* ampData, double incr);
double calculateAmplitude(double* smoothed_data, int length);

#endif
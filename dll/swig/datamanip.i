%module datamanip
%{

#include "calculations.h"
#include "instrumentfunctions.h"
#include "visa.h"
	
%}

void setSinWave(ViSession handle, int channel, double frequency, double amplitude);
void getInstrumentName(ViSession handle, char* returned_message);
double getScopeScale(ViSession handle);
void getNewCurve(ViSession handle, char* rawDataArray);
void autoSetScope(ViSession handle);

void convertCurveToVoltage(int n, char* rawDataArray, float scale, double* voltages);
void smoothing(double* voltages, int n, int w, double* voltagesSmoothed);
double mean(double* voltagesSmoothed, int n);
double rootMeanSquare(double* voltagesSmoothed, int n);
double amplitude(double* voltagesSmoothed, int n);


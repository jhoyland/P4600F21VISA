%module datalink
%{
	#include "scopecontrol.h"
	#include "fgcontrol.h"
	#include "dataprocessing.h"
	#include "visa.h"
%}

typedef unsigned int ViSession;


ViSession resourceCreate();
ViSession initScope(ViSession resource_manager);
void showinfo(ViSession handle);
double getData(double *ddata, int ddatalength,ViSession scope_handle, int channel, int scale);
void setScale(ViSession scope_handle, int channel, int scale);
void Scopeset(ViSession scope_handle);
double Ampget(ViSession scope_handle, int channel);



ViSession resourceCreateFG();
ViSession initFG(ViSession resource_manager);
void initCH(ViSession handle, int channel);
ViStatus setSinWave(ViSession handle, double channel, double amp, double freq, double offset, double phase);
ViStatus setFreq(ViSession handle, double channel, double freq);


float mean(float num[], int n);
double stdev(double num[], double mean, int n);
double rms(double num[], int n);
double Amp(double num[], int n);
double smooth(double *d, int n, int w, double* end);

#ifndef __OSCOPE_H
#define __OSCOPE_H

//Oscilloscop functions
void autosetScope(ViSession scope_handle);
ViStatus setScopewindow(ViSession scope_handle, int channel, double yscale, double ypos, double xscale, double xpos);
ViStatus scopeInfo(ViSession scope_handle);
void getScopedata(ViSession scope_handle, int channel, char *dataGot);
void scanScopedata(double *dataDouble, double *avg, double *rootmeansquare, double *amp);
double getScopevolts(ViSession scope_handle, int channel);
void convertScopedata(char *dataGot, double *dataDouble, double step);
double getAmplitude(ViSession scope_handle, int channel);

ViSession initRM();
ViSession initScope(ViSession RM);
#endif
#ifndef __OSCOPE_H
#define __OSCOPE_H

//Oscilloscop functions
ViStatus autosetScope(ViSession scope_handle);
ViStatus setScopewindow(ViSession scope_handle, int channel, double yscale, double ypos, double xscale, double xpos);
ViStatus scopeInfo(ViSession scope_handle);
ViStatus getScopedata(ViSession scope_handle, int channel, char *dataGot);
void scanScopedata(double *dataDouble, double *avg, double *rootmeansquare, double *amp);
double getScopevolts(ViSession scope_handle, int channel);
#endif
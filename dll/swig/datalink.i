%module datalink
%{
#include "visatype.h"
#include "fgenerator.h"
#include "oscope.h"
%}

typedef unsigned int ViSession;
typedef int ViStatus;

void autosetScope(ViSession scope_handle);
ViStatus setScopewindow(ViSession scope_handle, int channel, double yscale, double ypos, double xscale, double xpos);
ViStatus scopeInfo(ViSession scope_handle);
void getScopedata(ViSession scope_handle, int channel, char *dataGot);
void scanScopedata(double *dataDouble, double *avg, double *rootmeansquare, double *amp);
double getScopevolts(ViSession scope_handle, int channel);
double getAmplitude(ViSession scope_handle, int channel);
ViSession initRM();
ViSession initScope(ViSession RM);

ViStatus displayWave(ViSession handle, int channel);
ViStatus setSinwave(ViSession handle, int channel, double frequency, double amplitude, double offset, double phase);
ViStatus beep(ViSession handle);
ViStatus fgInfo(ViSession handle);
ViSession initRM();
ViSession initFG(ViSession RM);

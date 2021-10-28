%module datalink

%{
#include "scope.h"
#include "fgenerator.h"
#include "inbetween.h"
%}

typedef unsigned int ViSession;

ViSession findgen(ViSession rm, int channel);
ViStatus setSinWave(ViSession gen, int channel, double amplitude, double frequency, double offset, double phase); 

ViSession rm();
ViSession findscope(ViSession rm, int channel);
void getdata(ViSession scope_handle, int channel, char *data);
void getvoltage(char *data, int n, double v, double* data_voltage);
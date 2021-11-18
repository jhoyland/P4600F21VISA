%module datalink
%{


#include "instrumentfunctions.h"
#include "visa.h"
	
%}
%include <typemaps.i>

typedef unsigned int ViSession;
typedef unsigned int ViStatus;

ViStatus openInstruments(ViSession *OUTPUT, ViSession *OUTPUT);

double getAmplitude(double frequency, ViSession scope_handle, ViSession func_handle);


%module datalink
%{


#include "instrumentfunctions.h"
#include "visa.h"
	
%}
%include <typemaps.i>


ViStatus openInstruments(ViSession *OUTPUT, ViSession *OUTPUT);

double getAmplitude(double frequency, ViSession scope_handle, ViSession func_handle);


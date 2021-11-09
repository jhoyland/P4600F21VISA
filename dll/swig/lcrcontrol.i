%module lcrcontrol
%{
	#include "calcfunctions.h"
%}

double theController(double freq, double amp, double offset, double phase);

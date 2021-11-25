#ifndef __SCOPE_FUNC_COMMANDS_DOT_H  //if not defined or ignore the below code
#define __SCOPE_FUNC_COMMANDS_DOT_H  //creates a compilation variable
#include "visa.h"

ViSession resourceManager(ViStatus* status);
ViSession findOpenScope(ViSession resource_manager, ViStatus* status);
ViSession findOpenFuncgen(ViSession resource_manager, ViStatus* status);
ViStatus setOscilloscopeHorScale(ViSession scope_handle, double x);
ViStatus setOscilloscopeVertScale(ViSession scope_handle, double amp);
double grabVoltsDiv(ViSession scope_handle, ViStatus* status);
ViStatus setFuctionGenSin(ViSession func_handle, int channel, double freq, double amplitude, double offset, double phase);
ViStatus scopeAutoSet(ViSession scope_handle);
ViStatus scopeGrabData(ViSession scope_handle, int channel, char* datatype, char* data);


#endif
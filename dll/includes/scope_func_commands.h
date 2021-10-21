#ifndef __SCOPE_FUNC_COMMANDS_DOT_H  //if not defined or ignore the below code
#define __SCOPE_FUNC_COMMANDS_DOT_H  //creates a compilation variable
#include "visa.h"

ViSession resourceManager();
ViSession findOpenScope(ViSession resource_manager);
ViSession findOpenFuncgen(ViSession resource_manager);
double grabVoltsDiv(ViSession scope_handle);
ViStatus setFuctionGenSin(ViSession func_handle, int channel, double freq, double amplitude, double offset, double phase);
ViStatus scopeAutoSet(ViSession scope_handle);
ViStatus scopeGrabData(ViSession scope_handle, int channel, char* datatype, char* data);


#endif
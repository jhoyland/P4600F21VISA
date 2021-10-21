#ifndef __VISACOMS_H
#define __VISACOMS_H
#include "visa.h"

void FG_parameters (ViSession functiongen_handle, int current_channel, float F_now, float fg_volt, float V_offset, float phase_offset);
void OSC_setup1(ViSession scope_handle,int current_channel, int osc_resol);
float OSC_setup2(ViSession scope_handle,int current_channel);
void OSC_gather(ViSession scope_handle,unsigned char * OSC_data);
void OSC_setup (ViStatus status, ViSession * resource_manager, ViSession * scope_handle);
void FG_setup (ViStatus status, ViSession * resource_manager, ViSession * functiongen_handle);
ViSession resource_manager_setup();
void Intrument_turnoff (ViSession * functiongen_handle, ViSession * scope_handle);

#endif
%module LCR_Analysis_FgOsc
%{
	include "visatype.h"
	include "visa.h"
	include "visa_coms.h"
	include "vpptype.h"
	include "signal_analysis.h"
%}

typedef unsigned int ViSession;

void OSC_setup (ViStatus status, ViSession * resource_manager, ViSession * scope_handle);
void FG_setup (ViStatus status, ViSession * resource_manager, ViSession * functiongen_handle);
ViSession resource_manager_setup();
void Intrument_turnoff (ViSession * functiongen_handle, ViSession * scope_handle)
float data_loop (int FG_channel,int OSC_channel,float F_now, float phase_offset,float V_offset,float fg_volt,int osc_resol,int move_avg_window);
%module datalink

%{
	#include "visatype.h"
	#include "visa.h"
	#include "visa_coms.h"
	#include "signal_analysis.h"
%}

typedef unsigned int ViSession;
%include <typemaps.i>

ViSession OSC_setup (ViSession resource_manager);
ViSession FG_setup (ViSession resource_manager);
ViSession resource_manager_setup();
float data_loop (ViSession functiongen_handle, ViSession scope_handle, int FG_channel,int OSC_channel,float F_now,float V_offset,float fg_volt,int osc_resol,int move_avg_window);
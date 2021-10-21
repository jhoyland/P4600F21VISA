%module datalink
%{
#include "visatype.h"
#include "scopecontrol.h"
#include "FGControl.h"
%}

typedef unsigned int ViSession;

ViSession resourceCreate();
ViSession initScope(ViSession resource_manager);
void showinfo(ViSession handle);
void setScale(ViSession scope_handle, int channel, int scale);

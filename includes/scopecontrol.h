#ifndef __SCOPECONTROL_H
#define __SCOPECONTROL_H
#include "visa.h"

ViSession resourceCreate();
ViSession initScope(ViSession resource_manager);
void showinfo(ViSession handle);
double getData(double *ddata, int ddatalength,ViSession scope_handle, int channel, int scale);
void setScale(ViSession scope_handle, int channel, int scale);

#endif
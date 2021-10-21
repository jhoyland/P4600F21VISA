#include "visa.h"

ViStatus findscope(ViSession* rm, ViSession* handle, int channel);
void getdata(ViSession scope_handle, int channel, char *data);
#include "visa.h"

ViSession findscope(ViSession rm, int channel);
void getdata(ViSession scope_handle, int channel, char *data);
void getvoltage(ViSession scope_handle, char *data, int n, double* data_voltage);
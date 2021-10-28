#include "visa.h"

ViSession findscope(ViSession rm, int channel);
void getdata(ViSession scope_handle, int channel, char *data);
void getvoltage(char *data, int n, double v, double* data_voltage);
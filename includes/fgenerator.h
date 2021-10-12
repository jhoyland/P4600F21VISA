#include "visa.h"

ViStatus setSinWave(ViSession handle, int channel, double amplitude, double frequency, double offset, double phase);
void getdata(ViSession scope_handle, int channel, char *data);
double getvoltage(char *data, double v);
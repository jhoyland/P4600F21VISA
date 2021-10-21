#include "visa.h"

void findgen(ViSession handle, int channel);
ViStatus setSinWave(ViSession handle, int channel, double amplitude, double frequency, double offset, double phase);

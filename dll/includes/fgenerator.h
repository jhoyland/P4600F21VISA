#include "visa.h"

ViSession findgen(ViSession rm, int channel);
ViStatus setSinWave(ViSession gen, int channel, double amplitude, double frequency, double offset, double phase);

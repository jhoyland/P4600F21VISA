#ifndef __FGCONTROL_H
#define __FGCONTROL_H
#include "visa.h"

ViSession resourceCreateFG();
ViSession initFG();
void initCH(ViSession handle, int channel);
ViStatus setSinWave(ViSession handle, int channel, double amp, double freq, double offset, double phase);
ViStatus setFreq(ViSession handle, int channel, double freq);


#endif
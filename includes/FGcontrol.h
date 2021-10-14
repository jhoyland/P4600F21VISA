#ifndef __FGCONTROL_H
#define __FGCONTROL_H
#include "visa.h"

ViSession resourceCreate();
ViSession initFG();
void initCH(ViSession handle, int channel);
ViStatus setSinWave(ViSession handle, double channel, double amp, double freq, double offset, double phase);



#endif
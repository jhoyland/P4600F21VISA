#ifndef __FGENERATOR_H
#define __FGENERATOR_H

ViStatus displayWave(ViSession handle, int channel);
ViStatus setSinwave(ViSession handle, int channel, double frequency, double amplitude, double offset, double phase);
ViStatus beep(ViSession handle);
ViStatus fgInfo(ViSession handle);
ViSession initRM();
ViSession initFG(ViSession RM);
#endif
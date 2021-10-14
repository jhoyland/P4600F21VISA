#ifndef __INSTRUMENTFUNCTIONS_H
#define __INSTRUMENTFUNCTIONS_H

#include "visa.h"

void setSinWave(ViSession handle, int channel, double frequency, double amplitude);
void getInstrumentName(ViSession handle, char* returned_message);
double getScopeScale(ViSession handle);
void getNewCurve(ViSession handle, char* rawDataArray);
void autoSetScope(ViSession handle);

#endif
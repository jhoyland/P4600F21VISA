#ifndef __INSTRUMENTFUNCTIONS_H
#define __INSTRUMENTFUNCTIONS_H

#include "visa.h"


ViStatus createResourceManager(ViSession *resource_manager);
void openFunctionGenerator(ViSession resource_manager, ViSession *func_handle);
void openScope(ViSession resource_manager, ViSession *scope_handle);
ViStatus openInstruments(ViSession *scope_handle, ViSession *func_handle);

double getAmplitude(double frequency, ViSession scope_handle, ViSession func_handle);

void setSinWave(ViSession handle, int channel, double frequency);
void getInstrumentName(ViSession handle, char* returned_message);
double getScopeScale(ViSession handle);
void getNewCurve(ViSession handle, char* rawDataArray);
void autoSetScope(ViSession handle);

#endif
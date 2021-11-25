#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "camparmo.h"
#include "fgenerator.h"
#include "scope.h"
#include "inbetween.h"
#include <time.h>
#include <windows.h>

/*
  TASK:

  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated

*/

 
int main(int argc, char** argv) 
{
ViSession scope_handle;
ViSession fun_generator;
ViSession resource_manager;
ViStatus status = VI_SUCCESS;
char returned_message[64];
char data[2500];
double ave[2496];
int i;
double a;
double m;
double rms;
double data_voltage[2500];

//status = rm(&resource_manager);
//fun_generator = findgen(resource_manager, 1);

// Controlling Function Generator from PC 
 //setSinWave(fun_generator,1,10,100,0,0); //Set the waveform of CH1 to sine waveform with 100Hz frequency, 10Vpp amplitude, 0VDC offset and 0° start phase
 //viPrintf(fun_generator,":OUTP1 ON\n");  
// for oscilloscope
 scope_handle = findscope(resource_manager, 1);
 getdata(scope_handle,1, data);
 double data_double[2500];
 getvoltage(data,2500, 2, data_voltage);
 fflush(stdout);
//   smoothed(2500,data_voltage,5,ave);
//   m = mean(2500,data_voltage);
//   rms = RMS(2500,data_voltage);
//   a = Amp(2500, data_voltage);
//   printf("\nRMS Value =%0.5f",rms);
//   printf("\nMean Value =%0.5f",m);
//   printf("\nAmplitude =%f",a);
viClose(fun_generator);
viClose(scope_handle);
}

#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "camparmo.h"
#include "fgenerator.h"
#include "scope.h"
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
char data[2500];
double ave[2496];
int i;
double a;
double m;
double rms;
double data_voltage[2500];
status = viOpenDefaultRM(&resource_manager);

fun_generator = findgen(resource_manager, 1);
// Controlling Function Generator from PC
 setSinWave(fun_generator,1,10,100,0,0); //Set the waveform of CH1 to sine waveform with 100Hz frequency, 10Vpp amplitude, 0VDC offset and 0° start phase
 viPrintf(fun_generator,":OUTP1 ON\n");  
// for oscilloscope
 scope_handle = findscope(resource_manager, 1);
 getdata(scope_handle,1, data);
 for(i=0;i<10;i++)
 {
  printf("%c\n",data);
 }
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

void getvoltage(char *data, int n, double v, double* data_voltage)
{

  int i;
  double data_double[n];
  FILE* outputfile =   fopen("data.dat","w");
   for(i=0;i<n;i++)
   {
    data_double[i]=data[i];
    data_voltage[i] = data_double[i]*10.0*v/255.0;
    fprintf(outputfile,"%f\n",data_voltage[i]);
   }
  fclose(outputfile);
  
}
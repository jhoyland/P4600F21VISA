#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "camparmo.h"
#include "fgenerator.h"
#include <time.h>
#include <windows.h>

/*
  TASK:

  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated

*/


int main(int argc, char** argv)
{
ViStatus status = VI_SUCCESS;
ViSession resource_manager;
ViSession scope_handle;
ViSession fun_generator;
ViFindList resource_list;
unsigned int num_inst;
char description[VI_FIND_BUFLEN];
char data[2500];
double ave[2496];
double a;
double m;
double rms;
int i;
double data_double[2500];

status = viOpenDefaultRM(&resource_manager);

if(status != VI_SUCCESS)
{
  printf("Ooops");
}
else
{//function generator
  status = viFindRsrc(resource_manager,"USB[0-9]::0x1AB1?*INSTR",&resource_list,&num_inst,description);
  if(status != VI_SUCCESS)
    {
      printf("couldn't find any instrument");
      fflush(stdout);
      exit(1);
    }
  status = viOpen(resource_manager,description,VI_NULL,VI_NULL,&fun_generator);
  if(status != VI_SUCCESS)
    {
      printf("couldn't connect to function generator");
      fflush(stdout);
      exit(1);
    }
  char returned_message[128];
  printf("\nOpened function generator");
  viPrintf(fun_generator,"*IDN?\n");
  viScanf(fun_generator,"%t",returned_message);

  printf(returned_message);
  fflush(stdout);
// Controlling Function Generator from PC
  setSinWave(fun_generator,1,10,100,0,0); //Set the waveform of CH1 to sine waveform with 100Hz frequency, 10Vpp amplitude, 0VDC offset and 0° start phase
  viPrintf(fun_generator,":OUTP1 ON\n");
  

// for oscilloscope
  status = viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&num_inst,description);
  if(status != VI_SUCCESS)
    {
      printf("couldn't find any instrument");
      fflush(stdout);
      exit(1);
    }
  status = viOpen(resource_manager,description,VI_NULL,VI_NULL,&scope_handle);
  if(status != VI_SUCCESS)
    {
      printf("couldn't connect to scope");
      fflush(stdout);
      exit(1);
    }

  printf("\nOpened Scope");
  viPrintf(scope_handle,"*IDN?\n");
  viScanf(scope_handle,"%t",returned_message);

  printf(returned_message);
  fflush(stdout);

  getdata(scope_handle,1, data);
  getvoltage(data, 2);
  fflush(stdout);

      
  viClose(scope_handle);
  viClose(fun_generator);

  for(i=0;i<2500;i++)
  {
    data_double[i]=data[i];
  }
  smoothed(2500,data_double,5,ave);
  m = mean(2500,data_double);
  rms = RMS(2500,data_double);
  a = Amp(2500, data_double);
  printf("\nRMS Value =%0.5f",rms);
  printf("\nMean Value =%0.5f",m);
  printf("\nAmplitude =%f",a);
}

//For testing 
/*  int ndata = 1024;
  double x[ndata];
  double ave[ndata-4];


  random_data(ndata,x);
  smoothed(ndata,x,5,ave);
  mean(ndata,x);
  RMS(ndata,x);
  FILE* outputfile =   fopen("data.dat","w");

  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile,"\n%0.5f",x[i]);

  }
  fclose(outputfile);
  printf("\nRMS Value =%0.5f",RMS(ndata,x));
  printf("\nMean Value =%0.5f",mean(ndata,x));
  printf("\nAmplitude =%f",Amp(ndata,x));*/
}

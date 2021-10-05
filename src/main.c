#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "camparmo.h"
#include "visa.h"
#include <time.h>


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
ViFindList resource_list;
unsigned int num_inst;
int i;
char description[VI_FIND_BUFLEN];
char data[2500];
double data_double[2500];

status = viOpenDefaultRM(&resource_manager);

if(status != VI_SUCCESS)
{
  printf("Ooops");
}
else
{
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
  char returned_message[128];
  printf("\nOpened Scope");
  viPrintf(scope_handle,"*IDN?\n");
  viScanf(scope_handle,"%t",returned_message);

  printf(returned_message);
  fflush(stdout);

  viPrintf(scope_handle,"DATA:SOURCE CH1\n");
  viPrintf(scope_handle,"DATA:ENC RIBINARY\n");
  viPrintf(scope_handle,"DATA:WIDTH 1\n");
  viPrintf(scope_handle,"DATA:START 1\n");
  viPrintf(scope_handle,"DATA:STOP 2500\n");
  viPrintf(scope_handle,"CURVE?\n");
  viScanf(scope_handle,"%t",data);
  printf("data= %c\n",data[2]);

  for(i=0;i<2500;i++)
  {
    data_double[i]=data[i];
  }

  FILE* outputfile =   fopen("data.dat","w");
   for(i=0;i<2500;i++)
   {
    data_double[i] = data_double[i]*10/255;
    fprintf(outputfile,"%f\n",data_double[i]);
   }
  fclose(outputfile);
}

//For testing 
/*  int ndata = 1024;
  double x[ndata];
  double ave[ndata-4];
/*

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

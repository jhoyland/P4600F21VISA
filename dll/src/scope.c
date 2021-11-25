#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "scope.h"

ViSession findscope(ViSession rm, int channel)
{
ViStatus status = VI_SUCCESS;
ViSession scope_handle;
ViFindList resource_list;
char returned_message[128];
unsigned int num_inst; 
char description[VI_FIND_BUFLEN];

status = viFindRsrc(rm,"USB[0-9]::0x0699?*INSTR",&resource_list,&num_inst,description);
  if(status != VI_SUCCESS)
    {
      printf("couldn't find any instrument");
      fflush(stdout);
      exit(1);
    }
  status = viOpen(rm,description,VI_NULL,VI_NULL,&scope_handle);
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
  return scope_handle;

 }

void getdata(ViSession scope_handle, int channel, char *data)
{  
  viPrintf(scope_handle,"DATA:SOURCE CH%d\n",channel);
  viPrintf(scope_handle,"DATA:ENC RIBINARY\n");
  viPrintf(scope_handle,"DATA:WIDTH 1\n");
  viPrintf(scope_handle,"DATA:START 1\n");
  viPrintf(scope_handle,"DATA:STOP 2500\n");
  Sleep(2500);
  viPrintf(scope_handle,"CURVE?\n");
  viScanf(scope_handle,"%t",data);
}

void getvoltage(ViSession scope_handle, char *data, int n, double* data_voltage)
{
  double v;
  char returned_message[128];
  char *a;
  viPrintf(scope_handle,"CH1:VOLTS?\n");
  viScanf(scope_handle,"%t",returned_message);
  v = strtod(returned_message,&a);
  int i;
  double data_double[n];
  FILE* outputfile =   fopen("data.dat","w");
   for(i=6;i<n;i++)
   {
    data_voltage[i] = (double)data[i]*10.0*v/255.0;
    fprintf(outputfile,"%f\n",data_voltage[i]);
   }
  fclose(outputfile);
  
}

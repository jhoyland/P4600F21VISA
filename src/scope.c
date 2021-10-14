#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "scope.h"

ViStatus findscope(ViSession rm, ViSession* handle, int channel)
{
ViStatus status = VI_SUCCESS;
ViSession scope_handle;
ViFindList resource_list;
char returned_message[128];
unsigned int num_inst;
char description[VI_FIND_BUFLEN];

status = viFindRsrc(rm,"USB[0-9]::0x0699?*INSTR",resource_list,&num_inst,description);
  if(status != VI_SUCCESS)
    {
      printf("couldn't find any instrument");
      fflush(stdout);
      exit(1);
    }
  status = viOpen(rm,description,VI_NULL,VI_NULL,scope_handle);
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
  return status;

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


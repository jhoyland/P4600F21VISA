#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fgenerator.h"
#include <time.h>
#include <windows.h>


void findgen(ViSession handle, int channel)
{
ViStatus status = VI_SUCCESS;
ViSession resource_manager;
ViSession fun_generator;
ViFindList resource_list;
char returned_message[128];
unsigned int num_inst;
char description[VI_FIND_BUFLEN];

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
  printf("\nOpened function generator");
  viPrintf(fun_generator,"*IDN?\n");
  viScanf(fun_generator,"%t",returned_message);

  printf(returned_message);
  fflush(stdout);
}
}

ViStatus setSinWave(ViSession handle, int channel, double amplitude, double frequency, double offset, double phase)
{
	ViStatus status = VI_SUCCESS;
	status = viPrintf(handle,"SOURCE%d:APPLY:SIN %f, %f, %f, %f\n",channel,frequency, amplitude, offset, phase);
	return status;
}


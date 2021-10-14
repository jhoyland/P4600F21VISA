#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "visa.h"

/*GOAL: create readable library to control function generator through VI commands*/ 
/*AUTHOR: Erinn Psajd DATE: October 12th, 2021*/

//function to generate resource manager address space

ViSession resourceCreate()
{
	ViStatus status = VI_SUCCESS;
	ViSession resource_manager;
	status = viOpenDefaultRM(&resource_manager);

  	if(status != VI_SUCCESS)
  	{
    	//Do something about it 
    	printf("Resource manager status could not be set!\n");
    	exit(1);
  	}
  	return resource_manager;
}

ViSession initFG(ViSession resource_manager)
{
	ViStatus status = VI_SUCCESS;
  	ViSession fg_handle;
  	ViFindList resource_list;
  	unsigned int num_inst;
  	char description[VI_FIND_BUFLEN];

	status = viFindRsrc(resource_manager, "USB[0-9]::0x1AB1?*INSTR", &resource_list, &num_inst, &description);

    if(status != VI_SUCCESS)
    {
      printf("Could not locate any instruments\n");
      fflush(stdout);
      exit(1);
    }

  status = viOpen(resource_manager, description, VI_NULL, VI_NULL, &fg_handle);
  
  if(status != VI_SUCCESS)
    {
      printf("Could not connect to function generator\n");
      fflush(stdout);
      exit(1);
    } 
  
  fflush(stdout);
  return fg_handle;
}

//function to turn on channel
void initCH(ViSession handle, int channel)
{
	viPrintf(handle, ":OUTP%d:STAT ON\n", channel);
}

//function to set sin wave
ViStatus setSinWave(ViSession handle, double channel, double amp, double freq, double offset, double phase)
{
	viPrintf(handle,"SOURCE%d:APPLY:SIN%f,%f,%f,%f\n",channel, freq, amp, offset, phase);
	ViStatus status = VI_SUCCESS;
	return status;
}
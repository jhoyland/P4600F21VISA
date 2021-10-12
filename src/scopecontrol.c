#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "visa.h"

//#include<scopecontrol.h>

/*GOAL: create readable library to control scope through VI commands*/ 
/*AUTHOR: Erinn Psajd DATE: October 5th, 2021*/


// function to generate one resource manager address space

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

//function to initialize and return VISession scope handle if showinfo == true,True,t then print
//default is to not print device info
ViSession initScope(ViSession resource_manager)
{
	ViStatus status = VI_SUCCESS;
  	ViSession scope_handle;
  	ViFindList resource_list;
  	unsigned int num_inst;
  	char description[VI_FIND_BUFLEN];

	status = viFindRsrc(resource_manager, "USB[0-9]::0x0699?*INSTR", &resource_list, &num_inst, &description);

    if(status != VI_SUCCESS)
    {
      printf("Could not locate any instruments\n");
      fflush(stdout);
      exit(1);
    }

  status = viOpen(resource_manager, description, VI_NULL, VI_NULL, &scope_handle);
  
  if(status != VI_SUCCESS)
    {
      printf("Could not connect to scope\n");
      fflush(stdout);
      exit(1);
    } 
  
  fflush(stdout);
  return scope_handle;
}


// function to show info from a certain handle
void showinfo(handle)
{
    char returned_message[128];
  	printf("\n");

  	viPrintf(handle, "*IDN?\n");
  	viScanf(handle, "%t", returned_message);

  	printf(returned_message);
  	printf("\n");

}

//function to create a file of data with voltage values getData

void getData()

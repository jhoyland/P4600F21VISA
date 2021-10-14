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
void showinfo(ViSession handle)
{
    char returned_message[128];
  	printf("\n");

  	viPrintf(handle, "*IDN?\n");
  	viScanf(handle, "%t", returned_message);

  	printf(returned_message);
  	printf("\n");

}

//function to create a file of data with voltage values getData, returns data values as double

void getData(double *ddata, int ddatalength,ViSession scope_handle, int channel, int scale)
{
	viPrintf(scope_handle, "DATA:SOURCE CH%d\nDATA:ENC BINARY\nDATA:WIDTH 1\nDATA:START 0\nDATA:STOP 2500\n", channel);
	char data[ddatalength];
  	viPrintf(scope_handle, "CURVe?\n");
  	viScanf(scope_handle, "%t", data);
  	int i;
  	// this code works but is not in voltage values
  	//read through loop
  	//for(i=0; i<2500; i++)
  	//{
  	//  printf("%d \n",data[i]);
  	//}

  	//print data to a file 

  	FILE* datafile = fopen("curvedata.dat","w");
  	// turn data into double to convert to voltage values
  	//double ddata[2500];

  	for(i=0; i<ddatalength; i++)
  	{
    	ddata[i] = (scale/255.0) * data[i];
    	fprintf(datafile,"%f \n",ddata[i]);
  	}

  	fclose(datafile);
}

//function to set the time interval 

void setScale(ViSession scope_handle, int channel, int scale)
{
	//autoset and then set scale
	viPrintf(scope_handle, "CH%d:SCA %d \n",channel,scale);

}
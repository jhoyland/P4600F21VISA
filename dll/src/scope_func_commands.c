#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include "scope_func_commands.h"
#include "visa.h"

ViSession resourceManager()
{
	ViStatus status;
	ViSession resource_manager;
	status = viOpenDefaultRM(&resource_manager);//opens resource manager

	if(status != VI_SUCCESS)
	{
	exit(1);
	}

	else return resource_manager;
}

ViSession findOpenScope(ViSession resource_manager)
{
	ViStatus status = VI_SUCCESS;
	ViSession scope_handle;
	ViFindList resource_list;
	long unsigned int num_inst;
	char description[VI_FIND_BUFLEN];

	status = viFindRsrc(resource_manager, "USB[0-9]::0x0699?*INSTR", &resource_list, &num_inst, description);
    if(status != VI_SUCCESS)
    {
      printf("couldn't find the Oscilloscope");
      fflush(stdout);
      exit(1);
    }

    status = viOpen(resource_manager, description, VI_NULL, VI_NULL, &scope_handle);
    if(status != VI_SUCCESS)
    {
      printf("couldn't connect to oscilloscope");
      fflush(stdout);
      exit(1);
    }

    else return scope_handle;
    printf("Opened oscilloscope\n");

}

ViSession findOpenFuncgen(ViSession resource_manager)
{
	ViStatus status = VI_SUCCESS;
	ViSession func_handle;
	ViFindList resource_list;
	long unsigned int num_inst;
	char description[VI_FIND_BUFLEN];

	status = viFindRsrc(resource_manager, "USB[0-9]::0x1AB1?*INSTR", &resource_list, &num_inst, description);
    if(status != VI_SUCCESS)
    {
      printf("couldn't find the function generator");
      fflush(stdout);
      exit(1);
    }
    status = viOpen(resource_manager, description, VI_NULL, VI_NULL, &func_handle);
    if(status != VI_SUCCESS)
    {
      printf("couldn't connect to function generator");
      fflush(stdout);
      exit(1);
    }

    else return func_handle;

    printf("Opened function generator\n");
}

double grabVoltsDiv(ViSession scope_handle)
{
	char returned_message[128];
	ViStatus status = VI_SUCCESS;

	status = viPrintf(scope_handle, "CH1:VOLts?\n");
 	viScanf(scope_handle, "%t", returned_message);
 	fflush(stdout);
 	if(status == VI_SUCCESS)
 	{
 		char *eptr;
		double volts = strtod(returned_message, &eptr);
		return volts;
 	}
 	else
 	{
 		return 0.0;
 	}
}

ViStatus setFuctionGenSin(ViSession func_handle, int channel, double freq, double amplitude, double offset, double phase)
{
	if(channel != 1 && channel != 2)
	{
		printf("Your function channel value is not valid setting channel to 1\n");
		fflush(stdout);
		channel = 1;
	}
	ViStatus status = VI_SUCCESS;
	status = viPrintf(func_handle, ":SOURce%d:APPLy:SIN %f,%f,%f,%f\n", channel, freq, amplitude, offset, phase);
	status = viPrintf(func_handle, ":OUTPut1 ON\n");
	return status;
}

ViStatus scopeAutoSet(ViSession scope_handle)
{
	ViStatus status = VI_SUCCESS;
	status = viPrintf(scope_handle, "AUTOSet EXECute\n");
    Sleep(5000);
    return status;
}

ViStatus scopeGrabData(ViSession scope_handle, int channel, char* datatype, char* data)
{
	if(channel != 1 && channel != 2)
	{
		printf("Your scope channel value is not valid setting channel to 1\n");
		fflush(stdout);
		channel = 1;
	}
	ViStatus status = VI_SUCCESS;
	status = viPrintf(scope_handle, "DATa:Source CH%d\nDATa:ENC %s\nCurve?\n", channel, datatype);
    status = viScanf(scope_handle, "%t", data);
    return status;
}
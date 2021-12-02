#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include "scope_func_commands.h"
#include "visa.h"

ViSession resourceManager(ViStatus* status)
{
	ViSession resource_manager;
	*status = viOpenDefaultRM(&resource_manager);//opens resource manager

	if(*status != VI_SUCCESS)
	{
	exit(1);
	}

	else return resource_manager;
}

ViSession findOpenScope(ViSession resource_manager, ViStatus* status)
{
	ViSession scope_handle;
	ViFindList resource_list;
	long unsigned int num_inst;
	char description[VI_FIND_BUFLEN];

	*status = viFindRsrc(resource_manager, "USB[0-9]::0x0699?*INSTR", &resource_list, &num_inst, description);
    if(*status != VI_SUCCESS)
    {
      exit(1);
    }

    *status = viOpen(resource_manager, description, VI_NULL, VI_NULL, &scope_handle);
    if(*status != VI_SUCCESS)
    {
      exit(1);
    }

    else return scope_handle;
    printf("Opened oscilloscope\n");

}

ViSession findOpenFuncgen(ViSession resource_manager, ViStatus* status)
{
	ViSession func_handle;
	ViFindList resource_list;
	long unsigned int num_inst;
	char description[VI_FIND_BUFLEN];

	*status = viFindRsrc(resource_manager, "USB[0-9]::0x1AB1?*INSTR", &resource_list, &num_inst, description);
    if(*status != VI_SUCCESS)
    {
      exit(1);
    }
    *status = viOpen(resource_manager, description, VI_NULL, VI_NULL, &func_handle);
    if(*status != VI_SUCCESS)
    {
      exit(1);
    }

    else return func_handle;
    printf("Opened function generator\n");
}

ViStatus setOscilloscopeHorScale(ViSession scope_handle, double x)
{
	ViStatus status;
	// char returned_message[128];
	// status = viPrintf(scope_handle, "MEASUrement:IMMed:SOURCE CH1\n\n");
	// status = viPrintf(scope_handle, "MEASUrement:IMMed:TYPe FREQuency\n");
	// status = viPrintf(scope_handle, "MEASUrement:IMMed:VALue?\n");
 // 	viScanf(scope_handle, "%s", returned_message);
 // 	fflush(stdout);

 	// if(status == VI_SUCCESS)
 	// {
	// char *eptr;
	// double freq = strtod(returned_message, &eptr);
	// double timeScale = (1/freq);
	// char x[128];
	// sprintf(x, "%f", timeScale);
	// printf("%s\n", x);
	// fflush(stdout);
	double timeScale = 1/(2*x);
	status = viPrintf(scope_handle, "HORizontal:MAIn:SCAle %f\n", timeScale);

 	// }

 	return status;
}

ViStatus setOscilloscopeVertScale(ViSession scope_handle, double amp)
{
	ViStatus status;

	char returned_message[128];
	status = viPrintf(scope_handle, "MEASUrement:IMMed:SOURCE CH1\n\n");
	status = viPrintf(scope_handle, "MEASUrement:IMMed:TYPe  PK2pk\n");
	status = viPrintf(scope_handle, "MEASUrement:IMMed:VALue?\n");
 	viScanf(scope_handle, "%s", returned_message);
 	fflush(stdout);

 	if(status == VI_SUCCESS)
 	{
		char *eptr;
		double volt = strtod(returned_message, &eptr);
		double voltScale = volt/8.0;
		status = viPrintf(scope_handle, "CH1:VOLts %f\n", voltScale);
	}
	// char x[128];
	// sprintf(x, "%f", timeScale);
	// printf("%s\n", x);
	// fflush(stdout);

	// double voltScale = (amp + (amp*0.1))/10;
	

	return status;
}

double grabVoltsDiv(ViSession scope_handle, ViStatus* status)
{
	char returned_message[128];
	*status = viPrintf(scope_handle, "CH1:VOLts?\n");
 	viScanf(scope_handle, "%t", returned_message);
 	fflush(stdout);

 	if(*status == VI_SUCCESS)
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
	ViStatus status = VI_SUCCESS;
	if(channel != 1 && channel != 2)
	{
		printf("Your function channel value is not valid setting channel to 1\n");
		fflush(stdout);
		channel = 1;
	}
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
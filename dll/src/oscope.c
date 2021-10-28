#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "visa.h"
#include "myFunction.h"
#include "oscope.h"

//Oscilloscop functions
ViStatus autosetScope(ViSession scope_handle)
{
	ViStatus status = VI_SUCCESS;
	printf("\nAutosetting...\n");
    fflush(stdout);

    viPrintf(scope_handle,"AUTOSet EXECute\n");//autoset 
    Sleep(5000);

    printf("\nDone\n");
    fflush(stdout);
    return status;
}

ViStatus setScopewindow(ViSession scope_handle, int channel, double yscale, double ypos, double xscale, double xpos)
{
	ViStatus status = VI_SUCCESS;
	printf("\nSetting...\n");
	fflush(stdout);

	viPrintf(scope_handle, "CH%d:SCAle %f\n",channel,yscale); //preset CH1 viewing window
	viPrintf(scope_handle, "CH%d:POS %f\n",channel, ypos);
	viPrintf(scope_handle, "HOR:POS %f\n",xpos);
	viPrintf(scope_handle, "HOR:SCA %f\n",xscale);
	Sleep(5000);

	printf("\nDone\n");
    fflush(stdout);
    return status;
}

ViStatus scopeInfo(ViSession scope_handle)
{
	ViStatus status = VI_SUCCESS;
	printf("\nOpened scope\n");
    fflush(stdout);

	char info[128];
    viPrintf(scope_handle, "*IDN?\n");
    viScanf(scope_handle,"%t",info);

    printf(info);
    fflush(stdout);
    return status;
}

void getScopedata(ViSession scope_handle, int channel, char *dataGot)
{
	ViStatus status = VI_SUCCESS;
	status = viPrintf(scope_handle, "DATa:SOUrce CH%d\n DATa:ENCdg RIBinary\n DATa:STARt 1\n DATa:STOP 2500\n CURVe?\n",channel);
    status = viScanf(scope_handle,"%t", dataGot);
    if(status != VI_SUCCESS)
  	{
    	printf("could not get data");
    	fflush(stdout);
    	exit(1);
  	}
}

double getScopevolts(ViSession scope_handle, int channel) //grabbing volts/div
{
	ViStatus status = VI_SUCCESS;
	char volt[128];
	char *eptr;
	double volts;
	status = viPrintf(scope_handle, "CH%d:VOLts?\n", channel);
	status = viScanf(scope_handle,"%t", volt);
	volts = strtod(volt, &eptr);
	if(status != VI_SUCCESS)
  	{
    	printf("could not get volts");
    	fflush(stdout);
    	exit(1);
  	}

	return volts;
}

//Try and bring in data from the oscilloscope
void convertScopedata(char *dataGot, double *dataDouble, double dvolts)
{
 int i=0;
 for(i=6; i<2500; i++)
   {
    dataDouble[i-6] = dataGot[i] * dvolts * 10.0 / 256.0;
   }
      
}


void scanScopedata(double *dataDouble, double *avg, double *rootmeansquare, double *amp)
{

	*avg = mean(dataDouble, 2494);

	*rootmeansquare = rms(dataDouble, *avg, 2494);

	*amp = amplitude(*rootmeansquare, *avg);

	printf("Mean: %f\n",*avg);
	printf("RMS: %f\n",*rootmeansquare);
	printf("AMP: %f\n",*amp);
	fflush(stdout);
}


ViSession initRM()
{
	ViStatus status = VI_SUCCESS;
	ViSession resource_manager;
	status = viOpenDefaultRM(&resource_manager);

	if(status != VI_SUCCESS)
  	{
    	printf("could not create resource manager");
    	fflush(stdout);
    	exit(1);
  	}

	return resource_manager;
}

ViSession initScope(ViSession RM)
{
	ViStatus status = VI_SUCCESS;
	ViSession scope_handle;
	ViFindList resource_list;
	long unsigned int num_inst;
	char description[VI_FIND_BUFLEN];

	status = viFindRsrc(RM,"USB[0-9]::0x0699?*INSTR",&resource_list,&num_inst,description);
	if(status != VI_SUCCESS)
 	 {
    	printf("could not find any scopes");
    	fflush(stdout);
    	exit(1);
 	 }

	status = viOpen(RM,description,VI_NULL,VI_NULL,&scope_handle);
	if(status != VI_SUCCESS)
  	{
    	printf("could not connect to scope");
    	fflush(stdout);
    	exit(1);
 	}

	return scope_handle;
}
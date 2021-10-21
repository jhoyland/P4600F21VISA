#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "visa.h"
#include "myFunction.h"

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

ViStatus getScopedata(ViSession scope_handle, int channel, char *dataGot)
{
	ViStatus status = VI_SUCCESS;
	status = viPrintf(scope_handle, "DATa:SOUrce CH%d\n DATa:ENCdg RIBinary\n DATa:STARt 1\n DATa:STOP 2500\n CURVe?\n",channel);
    status = viScanf(scope_handle,"%t", dataGot);
    return status;
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

	return volts;
}


void scanScopedata(double *dataDouble, double *avg, double *rootmeansquare, double *amp)
{

	*avg = mean(dataDouble, 2500);

	*rootmeansquare = rms(dataDouble, 2500);

	*amp = amplitude(*rootmeansquare, *avg);

	printf("Mean: %f\n",*avg);
	printf("RMS: %f\n",*rootmeansquare);
	printf("AMP: %f\n",*avg);
	fflush(stdout);
}
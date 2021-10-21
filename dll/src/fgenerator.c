#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "visa.h"


ViStatus displayWave(ViSession handle, int channel)
{
	ViStatus status = VI_SUCCESS;
	viPrintf(handle,"OUTP%d:STAT ON\n",channel);
	return status;
}

ViStatus setSinwave(ViSession handle, int channel, double frequency, double amplitude, double offset, double phase)
{
	ViStatus status = VI_SUCCESS;
	viPrintf(handle,"SOURCE%d:APPLY:SIN %f,%f,%f,%f\n",channel,frequency,amplitude,offset,phase); //<freq Hz>,<amp Vpp/2>,<offset Vdc>,<phase deg>
	return status;
}

ViStatus beep(ViSession handle)
{
	ViStatus status = VI_SUCCESS;
	viPrintf(handle,"SYST:BEEP:IMM\n");
	return status;
}

ViStatus fgInfo(ViSession handle)
{
	ViStatus status = VI_SUCCESS;
    printf("\nOpened function generator\n");
    fflush(stdout);

	char info[128];
    viPrintf(handle, "*IDN?\n");
    viScanf(handle,"%t",info);

    printf(info);
    fflush(stdout);
    return status;
}


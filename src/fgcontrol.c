#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "visa.h"

/*GOAL: create readable library to control function generator through VI commands*/ 
/*AUTHOR: Erinn Psajd DATE: October 12th, 2021*/

ViSession initFG()
{
	return fg_handle;
}

//function to set sin wave
ViStatus setSinWave(ViSession handle, double channel, double amp, double freq, double offset, double phase)
{
	vPrintf(handle,"SOURCE%d:APPLY:SIN%f,%f,%f,%f\n",channel, freq, amp, offset, phase);
	ViStatus status = VI_SUCCESS;
	return status;
}
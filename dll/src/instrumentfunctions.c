#include <stdlib.h>
#include <stdio.h>
#include <instrumentfunctions.h>
#include <math.h>
#include "visa.h"

void setSinWave(ViSession handle, int channel, double frequency, double amplitude )
{
	viPrintf(handle, "SOURCE%d:APPLY:SIN %f, %f\n", channel, frequency, amplitude);
}

void getInstrumentName(ViSession handle, char* returned_message)
{

	viPrintf(handle, "*IDN?\n");              //gets the instrument that we are talking to
    viScanf(handle,"%t", returned_message);   //puts that instrument into returned_message
}

double getScopeScale(ViSession handle)
{
    char scaleChar[20];
    viPrintf(handle, "CH1:SCA?\n");           //gets the scale
    viScanf(handle,"%t", scaleChar);            //puts scale into returned_message
    double scale = (double)atof(scaleChar);	 //converts char string to a float
    return scale;
}

void getNewCurve(ViSession handle, char* rawDataArray)
{
    viPrintf(handle, "DATA:WIDTH 1\n");
    viPrintf(handle, "DATA:SOURCE CH1\n");
    viPrintf(handle, "DATA:ENCODE RIBINARY\n");
    viPrintf(handle, "DATA:START 1\n");
    viPrintf(handle, "DATA:STOP 2500\n");
    viPrintf(handle, "CURVE?\n");         //opens a quiery to the scope
    viScanf(handle, "%t", rawDataArray);  //writes data to an array
}

void autoSetScope(ViSession handle)
{
    viPrintf(handle, "AUTOSET EXECUTE\n");
}
#include <stdio.h>
#include <stdlib.h>
#include "camparmo.h"
#include "fgenerator.h"
#include "inbetween.h"
#include "scope.h"
#include <time.h>
#include <windows.h>

ViSession rm() 
{
	ViStatus status = VI_SUCCESS;
	ViSession resource_manager;
	status = viOpenDefaultRM(&resource_manager);
	return resource_manager;
}

double findamp(int channel, double amp, double frequency,ViSession fun_generator,ViSession scope_handle)
{
	char data[2500];
	setSinWave(fun_generator,channel,amp,frequency,0,0);
	double data_double[2500];
	double data_voltage[2500];
	double a;
	double m;
	double rms;
	double ave[2496];

	getdata(scope_handle,1, data);
	getvoltage(data,2500, 2, data_voltage);
	smoothed(2500,data_voltage,5,ave);
    m = mean(2500,data_voltage);
    rms = RMS(2500,data_voltage);
    a = Amp(2500, data_voltage);
      printf("\nRMS Value =%0.5f",rms);
  printf("\nMean Value =%0.5f",m);
  printf("\nAmplitude =%f",a);
    return a;
}
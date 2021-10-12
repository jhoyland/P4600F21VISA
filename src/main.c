#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include "calcfunctions.h"
#include "scope_func_commands.h"
#include "visa.h"

int main(int argc, char** argv)
{
  ViStatus status_scope = VI_SUCCESS, status_func = VI_SUCCESS, status = VI_SUCCESS;
  ViSession resource_manager, scope_handle, func_handle;
  ViFindList resource_list;
  long unsigned int num_inst;
  char description[VI_FIND_BUFLEN];
  status = viOpenDefaultRM(&resource_manager);//opens resource manager

  if(status != VI_SUCCESS)
  {
    printf("Ooops");
    exit(1);
  }

  else
  {
    status_scope = viFindRsrc(resource_manager, "USB[0-9]::0x0699?*INSTR", &resource_list, &num_inst, description);
    if(status_scope != VI_SUCCESS)
    {
      printf("couldn't find the Oscilloscope");
      fflush(stdout);
      exit(1);
    }
    status_scope = viOpen(resource_manager, description, VI_NULL, VI_NULL, &scope_handle);
    if(status_scope != VI_SUCCESS)
    {
      printf("couldn't connect to oscilloscope");
      fflush(stdout);
      exit(1);
    }
    printf("Opened oscilloscope\n");

    status_func = viFindRsrc(resource_manager, "USB[0-9]::0x1AB1?*INSTR", &resource_list, &num_inst, description);
    if(status_func != VI_SUCCESS)
    {
      printf("couldn't find the function generator");
      fflush(stdout);
      exit(1);
    }
    status_func = viOpen(resource_manager, description, VI_NULL, VI_NULL, &func_handle);
    if(status_func != VI_SUCCESS)
    {
      printf("couldn't connect to function generator");
      fflush(stdout);
      exit(1);
    }
    printf("Opened function generator\n");


    char returned_message[128];
    double start_freq = 100.0;
    double end_freq = 3000.0;
    double incr = 100;
    if(end_freq < start_freq)
    {
      double temp = start_freq;
      start_freq = end_freq;
      end_freq = start_freq;
    }

    int windowSize = 15;
    double meanValue = 0.0;
    double rmsValue = 0.0;
    double amplitudeValue = 0.0;
    int length = 2500;
    int amplength = ((int)end_freq - (int)start_freq)/incr + 2;
    double smoothed_data[length];
    double ampData[amplength];
    int j = 0;

    for(int i = start_freq; i <= end_freq; i += incr)
    {
      double freq = i;
      status = setFuctionGenSin(func_handle, 1, freq, 2, 0, 0);
      status = scopeAutoSet(scope_handle);

      char data[length];
      double data_double[length];

      status = scopeGrabData(scope_handle, 1, "RIBinary", data);
      double volts = grabVoltsDiv(scope_handle);
      int smoothLen = adcConvert(data, data_double, volts);

      smooth(data_double, length, windowSize, smoothed_data);

      meanValue = mean(smoothed_data, length);
      rmsValue = rms(smoothed_data, length, meanValue);
      amplitudeValue = amplitude(rmsValue);
      ampData[j] = amplitudeValue;
      j++;
    }

    writeToFile("ampdata.csv", start_freq, amplength, ampData, incr);

    viClose(scope_handle);
    viClose(func_handle);
  }
  return 0;
}

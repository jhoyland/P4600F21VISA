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
  ViStatus status = VI_SUCCESS;
  ViSession resource_manager, scope_handle, func_handle;

  resource_manager = resourceManager();
  scope_handle = findOpenScope(resource_manager);
  func_handle = findOpenFuncgen(resource_manager);


  char returned_message[128];
  double start_freq = 100.0;
  double end_freq = 300.0;
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

    ampData[j] = calculateAmplitude(smoothed_data, length);
    j++;

    writeToFile("ampdata.csv", start_freq, amplength, ampData, incr);

    viClose(scope_handle);
    viClose(func_handle);
  }
  return 0;
}

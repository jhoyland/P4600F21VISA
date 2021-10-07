#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include "calcfunctions.h"
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
    //do something about it
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
    printf("\nOpened oscilloscope\n");

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
    printf("\nOpened function generator\n");


    char returned_message[128];
    double start_freq = 15;
    int windowSize = 4;
    double meanValue = 0.0;
    double rmsValue = 0.0;
    double amplitudeValue = 0.0;
    int length = 2500;
    double smoothed_data[length];

    for(int i = start_freq; i < 17; i++)
    {

      double freq = i;
      viPrintf(func_handle, ":SOURce1:APPLy:SIN %f,3,0,1\n", freq);

      viPrintf(scope_handle, "AUTOSet EXECute\n");
      Sleep(5000);

      char data[length];
      double data_double[length];

      viPrintf(scope_handle, "DATa:Source CH1\nDATa:ENC RIBinary\nCurve?\n");
      viScanf(scope_handle, "%t", data);

      double volts = grabVoltsDiv(scope_handle);

      int smoothLen = adcConvert(data, data_double, volts);
      
      smooth(data_double, length, windowSize, smoothed_data);

      meanValue = mean(smoothed_data, length);
      rmsValue = rms(smoothed_data, length, meanValue);
      amplitudeValue = amplitude(rmsValue);
      printf("Mean = %g\nRMS = %g\nAmplitude = %g\n", meanValue, rmsValue, amplitudeValue);
      printf("------\n");



    }


    FILE* outputfile =   fopen("data.dat","w");

    for(int i = 0; i < 2500; i++)
    {
      fprintf(outputfile,"\n%0.5f",smoothed_data[i]);
    }


    fclose(outputfile);
    viClose(scope_handle);
    viClose(func_handle);
  }

  return 0;
  /*
  int ndata = 1024;
  int windowSize = 10;
  int smoothedLen = ndata - windowSize + 1;
  double x[ndata];
  double meanValue = 0.0;
  double rmsValue = 0.0;
  double amplitudeValue = 0.0;

  random_data(ndata,x);

  double smoothed[smoothedLen];
  smooth(x, ndata, windowSize, smoothed);

  meanValue = mean(smoothed, smoothedLen);
  rmsValue = rms(smoothed, smoothedLen, meanValue);
  amplitudeValue = amplitude(smoothed, smoothedLen, rmsValue);
  
  printf("Mean = %g\nRMS = %g\nAmplitude = %g\n", meanValue, rmsValue, amplitudeValue);


  FILE* outputfile =   fopen("data.dat","w");
  FILE* outputfilesmoothed =   fopen("smoothed_data.dat","w");

  for(int i = 0; i < ndata; i++)
  {
    fprintf(outputfile,"\n%0.5f",x[i]);
  }

  fclose(outputfile);

  for(int i = 0; i < smoothedLen; i++)
  {
    fprintf(outputfilesmoothed,"\n%0.5f",smoothed[i]);
  }

  fclose(outputfilesmoothed);

  return 0;*/
}

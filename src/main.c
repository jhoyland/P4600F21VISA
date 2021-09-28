#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "randdata.h"
#include "calcfunctions.h"
#include "visa.h"


int main(int argc, char** argv)
{

  ViStatus status = VI_SUCCESS;
  ViSession resource_manager;
  ViSession scope_handle;
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

    status = viFindRsrc(resource_manager, "USB[0-9]::0x0699?*INSTR", &resource_list, &num_inst, description);

    if(status != VI_SUCCESS)
    {
      printf("couldn't find any instruments");
      fflush(stdout);
      exit(1);
    }

    status = viOpen(resource_manager, description, VI_NULL, VI_NULL, &scope_handle);

    if(status != VI_SUCCESS)
    {
      printf("couldn't connect to oscilloscope");
      fflush(stdout);
      exit(1);
    }

    printf("\nOpened scope");

    char returned_message[128];
    char scale_message[128];
    char volt_message[128];

    viPrintf(scope_handle, "*IDN?\n");
    viScanf(scope_handle, "%t", returned_message);

    printf(returned_message);
    fflush(stdout);

    viPrintf(scope_handle, "CH1:SCAle 0.7446\nHORizontal:SCAle 0.10\nCH1:VOLts?\n");
    //viPrintf(scope_handle, "HORizontal:SCAle 1.0\n");

    viScanf(scope_handle, "%t", volt_message);
    printf("Voltage scale = %s\n", volt_message);
    //fflush(stdout);


    viPrintf(scope_handle, "CH1:SCAle?\n");
    viScanf(scope_handle, "%t", scale_message);
    printf("Vertical scale = %s\n", scale_message);
    fflush(stdout);




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

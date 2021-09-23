#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "randdata.h"
#include "calcfunctions.h"

/*
  TASK:

  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated

*/

int main(int argc, char** argv)
{

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

}

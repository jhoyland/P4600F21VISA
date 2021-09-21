#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
  double x[ndata];
  double meanValue = 0.0;
  double rms = 0.0;

  random_data(ndata,x);

  /*
    Code to test your functions goes here
  */
  meanValue = mean(x, ndata);
  rms = rms(x, ndata);
  


  FILE* outputfile =   fopen("data.dat","w");

  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile,"\n%0.5f",x[i]);

  }

  fclose(outputfile);


}

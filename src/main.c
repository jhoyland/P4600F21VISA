#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "signal_analysis.h"
#include <time.h>

/*
  TASK:

  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated

*/


int main(int argc, char** argv)
{

  int ndata = 1024;
  double x[ndata];
  double rms[ndata];

  random_data(ndata,x);


  double mean=SA_Mean(ndata,x);
  SA_RMS(ndata,x,rms);
  //SA_smooth(ndata,x);
  double ampl=SA_Amplitude(ndata,x);




  FILE* outputfile =   fopen("data.dat","w");

  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile,"\n\n%0.5f",x[i]);
    fprintf(outputfile,"\n%0.5f",rms[i]);
  }
  fprintf(outputfile,"\n\n\n\n%0.5f",mean)

  fclose(outputfile);


}

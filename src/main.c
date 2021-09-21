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
  int move_avg_size=10;
  int move_avg=ndata-move_avg_size+1;
  double x[ndata];
  double rms[ndata];
  double smooth[ndata-move_avg_size+1];
  random_data(ndata,x);


  double mean=SA_Mean(ndata,x);
  SA_RMS(ndata,x,rms);
  SA_smooth(move_avg,move_avg_size,x,smooth);
  double ampl=SA_Amplitude(move_avg,smooth);




  FILE* outputfile =   fopen("data.dat","w");

  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile,"\n\n%d) Value  : %0.5f",i,x[i]);
    fprintf(outputfile,"\n%d) RMS    : %0.5f",i,rms[i]);
    fprintf(outputfile,"\n%d) Smooth : %0.5f",i,smooth[i]);
  }
  fprintf(outputfile,"\n\n\n\n\nMean:%0.5f",mean);

  fclose(outputfile);


}

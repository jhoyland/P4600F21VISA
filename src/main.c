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
  // JAMES:Your variable names move_avg_size and move_avg are a little confusing
  int move_avg_window=10;
  int move_avg_arraysize=ndata-move_avg_window+1;

  double x[ndata];
  double smooth[move_avg_arraysize];

  random_data(ndata,x);
  SA_smooth(move_avg_arraysize,move_avg_window,x,smooth);
  double mean_smooth = SA_Mean(move_avg_arraysize,smooth);
  double rms_smooth = SA_RMS(move_avg_arraysize,smooth,mean_smooth);
  double amplitude_smooth = SA_Amplitude(rms_smooth);

  FILE* outputfile0 =   fopen("result.dat","w");
  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile0,"\n%d) Value  : %0.5f",i,x[i]);
  }
  fprintf(outputfile0,"\n\n\n");

  for(int i = 0; i< move_avg_arraysize; i++)
  {
    fprintf(outputfile0,"\n%d) Smooth : %0.5f",i,smooth[i]);
  }
  fprintf(outputfile0,"\n\n\n");
  fprintf(outputfile0,"\nMean of Smoothed Data:%0.5f",mean_smooth);
  fprintf(outputfile0,"\nRMS of Smoothed Data:%0.5f",rms_smooth);
  fprintf(outputfile0,"\nAmplitude of Smoothed Data:%0.5f",amplitude_smooth);
  fclose(outputfile0);

  FILE* outputfile1 =   fopen("og.dat","w");
  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile1,"\n%0.5f",x[i]);
  }
  fclose(outputfile1);

  FILE* outputfile2 =   fopen("smooth.dat","w");
  for(int i = 0; i< move_avg_arraysize; i++)
  {
    fprintf(outputfile2,"\n%0.5f",smooth[i]);
  }
  fclose(outputfile2);

}

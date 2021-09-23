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
  double smooth[move_avg];
  
  
  


  random_data(ndata,x);
  SA_smooth(move_avg,move_avg_size,x,smooth);
  double mean_smooth = SA_Mean(move_avg,smooth);
  double rms_smooth = SA_RMS(move_avg,smooth,mean_smooth);
  double amplitude_smooth = SA_Amplitude(rms_smooth);

  


  FILE* outputfile =   fopen("data.dat","w");

  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile,"\n%d) Value  : %0.5f",i,x[i]);
  }
  fprintf(outputfile,"\n\n\n");

  for(int i = 0; i< move_avg; i++)
  {
    fprintf(outputfile,"\n%d) Smooth : %0.5f",i,smooth[i]);
  }
  fprintf(outputfile,"\n\n\n");
  fprintf(outputfile,"\nMean of Smoothed Data:%0.5f",mean_smooth);
  fprintf(outputfile,"\nRMS of Smoothed Data:%0.5f",rms_smooth);
  fprintf(outputfile,"\nAmplitude of Smoothed Data:%0.5f",amplitude_smooth);
  
  fprintf(outputfile,"\n\n\n\n\n\n\n\n\n\n\n");

  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile,"\n%0.5f",x[i]);
  }
  fprintf(outputfile,"\n\n\n");
  for(int i = 0; i< move_avg; i++)
  {
    fprintf(outputfile,"\n%0.5f",smooth[i]);
  }




  

  fclose(outputfile);


}

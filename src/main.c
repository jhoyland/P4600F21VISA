#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "calculations.h"
#include <time.h>

/*
  TASK:

  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated

*/

/*void smoothing(double* x, int n, int w, double* xSmoothed)
{



}*/



int main(int argc, char** argv)
{
  double mean1, rms;
  int ndata = 1024;
  double x[ndata];
  int window = 5;
  double xSmoothed[ndata-(window-1)];

  random_data(ndata,x);


  mean1 = mean(x,ndata);
  printf ("%g \n", mean1);

  rms = rootMeanSquare(x,ndata);
  printf ("%g \n", rms);



  FILE* outputfile =   fopen("data.dat","w");

  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile,"\n%0.5f",x[i]);

  }

  fclose(outputfile);

  //return 0;



}

#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "camparmo.h"
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


  random_data(ndata,x);
  /*
    Code to test your functions goes here
  */
 // mean(ndata,x);
  //RMS(ndata,x);
  FILE* outputfile =   fopen("data.dat","w");

  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile,"\n%0.5f",x[i]);

  }
  fclose(outputfile);
  printf("\nRMS Value =%0.5f",RMS(ndata,x));
  printf("\nMean Value =%0.5f",mean(ndata,x));
}

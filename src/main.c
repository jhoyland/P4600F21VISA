#include <stdio.h>
#include <stdlib.h>
#include <randdata.h>
#include <time.h>

#include "myFunction.h"

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

  double avg;

  avg = mean(x,ndata);
  printf("The mean is %g\n",avg);



  FILE* outputfile =   fopen("data.dat","w");

  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile,"\n%0.5f",x[i]);

  }

  fclose(outputfile);


}

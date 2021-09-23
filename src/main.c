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
  int windowLen = 5;
  double x[ndata];
  double smoothSignal[ndata - windowLen + 1];
  random_data(ndata,x);
  

  double avg, rootmeansquare, amp;

  avg = mean(x,ndata);
  printf("The mean is %g\n",avg);

  rootmeansquare = rms(x, ndata);
  printf("The RMS is %g\n",rootmeansquare);

  amp = amplitude(rootmeansquare, avg);
  printf("The amplitude is %g\n",amp);

  smooth(x, ndata, windowLen, smoothSignal);



  FILE* outputfile =   fopen("data.dat","w");
  if(outputfile != NULL)
  {
    for(int i = 0; i< ndata; i++)
      {
        fprintf(outputfile,"\n%0.5f",x[i]);

      }
      fclose(outputfile);
  }


  FILE* smoothdatafile = fopen("smoothdata.dat","w");
  if(smoothdatafile != NULL)
  {
    for(int i=0; i< ndata-windowLen+1; i++)
    {
      fprintf(smoothdatafile,"\n%0.5f", smoothSignal[i]);
    }
    fclose(smoothdatafile);
  }
  
}

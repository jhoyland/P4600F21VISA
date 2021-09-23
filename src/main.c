#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "calculations.h"
#include <time.h>


int main(int argc, char** argv)
{
  double mean1, rms;
  int ndata = 1024;
  double x[ndata];
  int window = 5; 
  double xSmoothed[ndata-(window-1)];
  int ndataSmoothed = ndata - (window -1 )/2;
  random_data(ndata,x);

  smoothing(x,ndata, window, xSmoothed);
  mean1 = mean(xSmoothed,ndataSmoothed);
  printf ("%g \n", mean1);

  rms = rootMeanSquare(xSmoothed,ndataSmoothed);
  printf ("%g \n", rms);


  for (int i = (window-1)/2; i < window+(window-1)/2; i++)
  {
    printf("%g ",x[i]);
  }
  printf ("\n%g\n ",xSmoothed[0]);



  FILE* outputfile =   fopen("data.dat","w");

  if (outputfile != NULL)
  {

    for(int i = 0; i< ndata; i++)
    {
      fprintf(outputfile,"\n%0.5f",x[i]);

    }

    fclose(outputfile);
  }

  FILE* outputfile1 =   fopen("data1.dat","w");

  if (outputfile1 != NULL)
  {

    for(int i = 0; i< ndataSmoothed ; i++)
    {
      fprintf(outputfile1,"\n%0.5f",xSmoothed[i]);

    }

    fclose(outputfile);
  }


}

#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include <randdata.h>
#include "myFunction.h"

double mean(double* data, int ndata)  //data array, number of data points
{
  double sum;
  int i = 0;
  for(i=0; i<ndata; i++)
  {
    sum += data[i];
  }
  return sum/ndata;
}



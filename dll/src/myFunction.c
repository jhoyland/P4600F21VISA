#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include <randdata.h>
#include "myFunction.h"

// JAMES: Maybe a more descriptive name than "myFunction"

double mean(double* data, int ndata)  //data array, number of data points
{
  double sum;
  int i = 0;
  for(i=0; i<ndata; i++)
  {
    sum += data[i];
  }
  // JAMES: Note that "sum" may not be zero at the beginning so you
  // could end up with a wrong value. Initialize sum with sum = 0; before
  // the loop starts
  return sum/ndata;
}

double rms(double* data, int ndata)
{
	int i=0;
	double sumSqr = 0.0;
  	for(i=0; i < ndata; i++)
  	{
  		sumSqr += data[i]*data[i];
  	}
  	return sqrt(sumSqr/ndata);
    // JAMES: as with the mean function sumSqr is not necessarily zero at the beginning
}

double amplitude(double Vrms, double Voffset)
{
	double a,b;
	a=2*Vrms*Vrms;
	b=2*Voffset*Voffset;
	return sqrt(a-b);
}

void smooth(double* data, int ndata, int window, double* newData)
{
	int i=0, j=0;
	int len = ndata - window + 1;
	double sum;

	for(i=0; i<len; i++)
	{
		sum = 0.0;
		for(j=0; j<window ; j++)
		{
			sum += data[i+j];
		}
		newData[i] = sum/window;
	}

}

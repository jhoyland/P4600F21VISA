#include <stdlib.h>
#include <stdio.h>
#include <calculations.h>
#include <math.h>

void smoothing(double* x, int n, int w, double* xSmoothed)
{
  double sum;
  int j, i;
  
  for (i = (w-1)/2; i < n - (w-1)/2; i++)  
  {
    sum = 0;
    for (j = 0; j < w; j++)
    {
      sum = sum + x[i+j]; 
    }
    xSmoothed[i-(w-1)/2] = sum / w;
  }
}

double mean(double* xSmoothed, int n)
{
  double sum = 0;
  double mean;

  for (int i = 0; i < n ; i++)
  {
    sum = sum + xSmoothed[i];
  }

  mean = sum / n;

  return mean;

}

double rootMeanSquare(double* xSmoothed, int n)
{
  double sumSquares = 0;
  double rms;

  for (int i = 0; i < n ; i++)
  {
    sumSquares = sumSquares + (xSmoothed[i]*xSmoothed[i]);
  }

  rms = sqrt(sumSquares/n);

  return rms;
}

double amplitude(double* xSmoothed, int n)
{
  double rms = rootMeanSquare(xSmoothed,n);
  double mean1 = mean(xSmoothed,n);
  double amp = sqrt(2*(rms*rms - mean1*mean1));  
  return amp;

}
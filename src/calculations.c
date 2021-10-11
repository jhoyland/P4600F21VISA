#include <stdlib.h>
#include <stdio.h>
#include <calculations.h>
#include <math.h>

void smoothing(double* dataArray, int n, int w, double* dataArraySmoothed)
{
  double sum;
  int j, i;
  int smoothEnd = (w-1)/2;

  for (i = smoothEnd; i < n - smoothEnd; i++)
  {
    sum = 0;
    for (j = -smoothEnd; j < smoothEnd; j++)
    {
      sum = sum + dataArray[i+j];
    }
    dataArraySmoothed[i - smoothEnd] = sum / w;
  }

}

double mean(double* dataArraySmoothed, int n)
{
  double sum = 0;
  double mean;

  for (int i = 0; i < n ; i++)
  {
    sum = sum + dataArraySmoothed[i];
  }
  mean = sum / n;

  return mean;

}

double rootMeanSquare(double* dataArraySmoothed, int n)
{
  double sumSquares = 0;
  double rms;

  for (int i = 0; i < n ; i++)
  {
    sumSquares = sumSquares + (dataArraySmoothed[i]*dataArraySmoothed[i]);
  }

  rms = sqrt(sumSquares/n);

  return rms;
}

double amplitude(double* dataArraySmoothed, int n)
{
  double rms = rootMeanSquare(dataArraySmoothed,n);
  double mean1 = mean(dataArraySmoothed,n);
  double amp = sqrt(2*(rms*rms - mean1*mean1));
  return amp;

}

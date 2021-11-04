#include <stdlib.h>
#include <stdio.h>
#include "calculations.h"
#include <math.h>

void convertCurveToVoltage(int n, char* rawDataArray, float scale, double* voltages)
{

  for (int i=0;i<n;i++)
  {
    double tempArray[n];
    tempArray[i] = rawDataArray[i+6] ;        //rewrite the data to convert char to double and starts at element 6 
    voltages[i] = tempArray[i]*1/10*scale;    //use the scope sale to 
  }
}

void smoothing(double* voltages, int n, int w, double* voltagesSmoothed)
{
  double sum;
  int j, i;
  int smoothEnd = (w-1)/2;

  for (i = smoothEnd; i < n - smoothEnd; i++)
  {
    sum = 0;
    for (j = -smoothEnd; j < smoothEnd; j++)
    {
      sum = sum + voltages[i+j];
    }
    voltagesSmoothed[i - smoothEnd] = sum / w;
  }

}

double mean(double* voltagesSmoothed, int n)
{
  double sum = 0;
  double mean;

  for (int i = 0; i < n ; i++)
  {
    sum = sum + voltagesSmoothed[i];
  }
  mean = sum / n;

  return mean;

}

double rootMeanSquare(double* voltagesSmoothed, int n)
{
  double sumSquares = 0;
  double rms;

  for (int i = 0; i < n ; i++)
  {
    sumSquares = sumSquares + (voltagesSmoothed[i]*voltagesSmoothed[i]);
  }

  rms = sqrt(sumSquares/n);

  return rms;
}

double amplitude(double* voltagesSmoothed, int n)
{
  double rms = rootMeanSquare(voltagesSmoothed,n);
  double mean1 = mean(voltagesSmoothed,n);
  double amp = sqrt(2*(rms*rms - mean1*mean1));
  return amp;

}


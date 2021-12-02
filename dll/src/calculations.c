#include <stdlib.h>
#include <stdio.h>
#include "calculations.h"
#include <math.h>

//This  function takes the raw data from the oscilloscope and used the scale to convert to voltages
void convertCurveToVoltage(int n, char* rawDataArray, double scale, double* voltages)
{

  for (int i=0;i<n;i++)
  {
    voltages[i] = (double)rawDataArray[i+6]/10*scale;
  }
}

//This function takes a set of data and smooths it by taking small successive groups and averaging the 
//and reassigns it as a new set of data
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

//This fucntion calculates the mean
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

//This function Calculates and returns the rms
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


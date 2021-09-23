#include <stdlib.h>
#include <calculations.h>

double mean(double* x, int n)
{
  double sum = 0;
  double mean;


  for (int i = 0; i < n ; i++)
  {
    sum = sum + x[i];
  }

  mean = sum / n;

  return mean;

}

double rootMeanSquare(double* x, int n)
{
  double sumSquares = 0;
  double rms;

  for (int i = 0; i < n ; i++)
  {
    sumSquares = sumSquares + (x[i]*x[i]);
  }

  rms = sqrt(sumSquares/n);

  return rms;
}
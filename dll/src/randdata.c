#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "randdata.h"

double norm_rand()
{
  int norm_int = rand()%10000 - rand()%10000;  // Generate normally distributed random numnber -512 -> 512

  return (double)norm_int / 10000.0;
}

void random_data(int n, double * data)
{
  srand(time(NULL));

  double amplitude = (double)(rand()%1000) * 0.2 + 0.8;
  double omega = (2.0 * M_PI / 256.0) * (norm_rand() * 0.5 + 1.0);
  double phi = norm_rand() * M_PI;
  double offset = norm_rand() * 0.25;

  double noise = 0.05;
  double x;

  for(int i = 0; i< n; i++)
  {
    x = i;
    data[i] = amplitude * (sin(omega * x + phi) + noise * norm_rand()) + offset;
  }
}

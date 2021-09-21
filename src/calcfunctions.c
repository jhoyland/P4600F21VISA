#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calcfunctions.h"


double mean(double* data, int length)
{
	double sum = 0.0;
	for(int i = 0; i < length; i++)
	{
		sum += data[i];
	}
	return sum/length;
}

double rms(double* data, int length)
{



	return 0;
}
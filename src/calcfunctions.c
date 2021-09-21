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
	double sum = 0.0;
	for (int i = 0; i < length; i++)
	{
		sum += data[i] * data[i];
	}
	return sqrt(sum/length);
}

double amplitude(double* data, int length)
{
	double amplitude = 0.0;

	for (int i = 0; i < length; i++)
	{
		if(amplitude < data[i])
		{
			amplitude = data[i];
		}
	}
	return amplitude;
}

double smooth(double* data, int length, int filterLength)
{
	double smoothed[length];
	double summed = 0.0;

	for (int i = 0; i < (length - filterLength); i++)
	{
		for (int j = 0; i < filterLength; ++i)
		{
			if((i + j) < length)
			{
				summed += data[i + j];
			}
		}

		smoothed[i] = summed/filterLength;
	}
}
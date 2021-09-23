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

double rms(double* data, int length, double mean)
{
	double sum = 0.0;
	for (int i = 0; i < length; i++)
	{
		data[i] = data[i] - mean;
		sum += data[i] * data[i];
	}
	return sqrt(sum/length);
}

double amplitude(double* data, int length, double rms)
{
	double amplitude = 0.0;
	amplitude = rms * sqrt(2);
	return amplitude;
}

void smooth(double* data, int length, int filterLength, double* smoothed)
{
	double summed = 0.0;
	int adjustment = filterLength/2;
	int smoothedLength = length - filterLength + 1;

	// for (int i = adjustment; i < (length - adjustment + 1); i++)
	// {
	// 	for (int j = 0; i < filterLength; ++i)
	// 	{
	// 		summed += data[i + j];
	// 	}

	// 	smoothed[i] = summed/filterLength;
	// }


	double *cursor;
	cursor = data;
	for (int i = 0; i < smoothedLength; i++)
	{
		for (int j = 0; i < filterLength; i++)
		{
			summed += cursor[j];
		}

		smoothed[i] = summed/filterLength;
		cursor++;
	}

}
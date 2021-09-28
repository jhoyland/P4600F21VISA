#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "camparmo.h"

// Good. Try to get the smoothing and amplitude functions done also.
// Maybe also give your header file a more descriptive name so
// people know what it is for.

double mean(int n, double *x)
{
	int i;
	double y=0;
	double m =0;

	for(i=0; i<n; i++)
	{
		y = y + x[i];
	}

	m = y/i;

	return m;
}

double RMS(int n, double *x)
{
	int i;
	double r=0;
	double sum =0;

	for(i=0;i<n;i++)
	{
		sum = sum + x[i]*x[i];
	}
	r = sqrt(sum/n);
	printf("\nRMS in function =%f",r);

	return r;
}

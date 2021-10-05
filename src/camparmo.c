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

double smoothed(int n, double *x, int w, double *ave)
{
	int i;
	int j;
	double s;

	for(i=0; i<n-4; i++)
	{
		ave[i]=0;
		for(j=0;j<w;j++)
		{
			ave[i]= ave[i]+x[i+j];
		}
		 ave[i]=ave[i]/5;
		 //printf("Ave = %f\n",ave[i]);

	}
	return s;
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
	//printf("\nRMS in function =%f",r);

	return r;
}

double Amp(int n, double*x)
{
	double A;

	A = RMS(n,x)*sqrt(2);
	//printf("\nAmplitude =%f",A);
	return A;

}
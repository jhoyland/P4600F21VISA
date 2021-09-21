#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
  TASK:
  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated
*/

// Mean function: 
float mean(float num[], int n)
{
	float mean = 0, sum=0;
	int i = 0;

	for (i=0;i<n;i++)
	{
		sum += num[i];
	}

	mean = sum/10;

	return mean;
}

// Standard Deviation:
float stdev(float num[], float mean, int n)
{
	float dif[n], x, m;
	int i=0;
	while (i<n)
	{
		x = num[i] - mean;
		x = x*x;
		dif[i] = x;
		i++;
	}

	// mean of squared difs
	i = 0;
	float sum = 0;

	for (i=0;i<n;i++)
	{
		sum += num[i];
	}

	m = sum/n;
	// take the square root
	double std; 
	std = sqrt(m);

	return std; 
}


// RMS Value: 

float RMS(float num[])
{

}

//Amplitude:

float Amp(float num[])
{

}

//Moving Average Filter:

float MAF(float num[])
{

}
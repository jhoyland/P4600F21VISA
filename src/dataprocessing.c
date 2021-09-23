#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<dataprocessing.h>

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

float rms(float num[], int n)
{
	// n is the length of the array
	float sum = 0, rms = 0;
	for(int i=0; i<n; i++) //get the sum of squared values in array 
	{
		sum+= pow(num[n],2);
	}	
	rms = sqrt(sum/n);

	return rms;
}

//Amplitude:

float Amp(float num[], int n)
{
	// n is the length of the array 
	// the following peak method is not averaged and might produce
	//slight errors so it has been discarded 
	/*float peak[n], amp;
	for (i=0; i<n; i++)
	{
		if (i>0 && num[i] >= num[i-1] && num[i] >= num[i+1])
		{
			peak[i] = num[i];
		}
	}
	peak.sort();
	amp = peak[0];
	return amp; */
	float amp;
	amp = rms(num, n) * sqrt(2);
	return amp;
}

//Moving Average Filter:

float smooth(double *d, int n, int w, double* end)
{
	// where n is the length of the array, w is the window
	// double* is empty array 
	// moving average filter is the sum w # of elements/# of all elements
	double filter = 0;

	for(int i = 0; i < (n-w); i++) // cycle through without breaking upper limit
	{
		for(int j=0; j < w; j++) 
		{
			filter += (1/w) * d[i+j];
		}
		end[i] = d[i] * filter; 
		filter = 0;
	}
}

/*int main()
{
	// test
	printf("Test test");
	return 0;
} */
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
// where int n is the length of the array 
float mean(float num[], int n)
{
	double mean = 0, sum=0;
	int i = 0;

	for (i=0;i<n;i++)
	{
		sum += num[i];
	}

	mean = sum/n;

	return mean;
}

// Standard Deviation:
double stdev(double num[], double mean, int n)
{
	double dif[n], x, m;
	int i=0;
	while (i<n)
	{
		x = num[i] - mean;
		// JAMES: Probably quicker here just to say dif[i] = x*x;
		// ERINN: Changed. 
		dif[i] = x*x;
		i++;
	}

	// mean of squared difs
	i = 0;
	double sum = 0;

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

// JAMES: Take a look at your standard deviation and rms functions
// They essentially do the same thing with one minor difference
// Could they be combined into a single function?

// RMS Value:

double rms(double num[], int n)
{
	// n is the length of the array
	double sum = 0.0, rms = 0.0;
	FILE* datafile = fopen("rms.dat","w");
	fprintf(datafile, "\nrms");
	for(int i=0; i<n; i++) //get the sum of squared values in array
	{
		sum += pow(num[i],2.0);
		fprintf(datafile, "\n%f",sum);
	}
	rms = sqrt(sum/n);
	fprintf(datafile, "\n%f", rms);
	fclose(datafile);

	return rms;
}

//Amplitude:

double Amp(double num[], int n)
{
	// n is the length of the array
	// the following peak method is not averaged and might produce
	// slight errors so it has been discarded
	/*double peak[n], amp;
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
	double amp;
	// JAMES: math.h also has a constant M_SQRT2 which can be used instead
	// of calling sqrt(2)
	amp = rms(num, n) * sqrt(2);
	return amp;
}

//Moving Average Filter:

void smooth(double *d, int n, int w, double* end)
{
	// where n is the length of the array, w is the window
	// double* is empty array
	// moving average filter is the sum w # of elements/# of all elements
	double filter = 0;

	for(int i = 0; i < (n-w); i++) // cycle through without breaking upper limit
	{
		for(int j=0; j < w; j++)
		{
			// JAMES: This will cause problems, (1/w) will be calculated as
			// integer division producing zero if w>1. The simplest fix is
			// to write (1.0/w). But multiplying by 1/w is the same as dividing
			// by w so :
			filter += d[i+j];
			// JAMES: However, this is not the most efficient approach,
			// you are dividing each of the added terms by w, why not
			// just divide the final sum of the window by w? This would
			// save w-1 divisions per data point.
			// ERINN: Done, filter is now divided by w and saved in end
		}
		// JAMES: You do not need to multiply by d[i] the contents of filter
		// is the averaged value at that point.
		// ERINN: Done, filter is added to end without multiplying 
		// by the d[i] value
		end[i] = filter/w;
		filter = 0;
	}
}

/*int main()
{
	// test
	printf("Test test");
	return 0;
} */

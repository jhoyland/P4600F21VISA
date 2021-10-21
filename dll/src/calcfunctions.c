#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "calcfunctions.h"
#include "scope_func_commands.h"
#include "visa.h"


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

double amplitude(double rms)
{
	double amplitude = 0.0; 
	amplitude = rms * sqrt(2); // JAMES: math.h actually provides a constant M_SQRT2 for this so you don't have to calculate it each time
	// See "https://www.gnu.org/software/libc/manual/html_node/Mathematical-Constants.html"  for more math constants.
	amplitude = rms * M_SQRT2;
	return amplitude;
}

void smooth(double* data, int length, int filterLength, double* smoothed)
{
	double summed = 0.0;
	int adjustment = filterLength/2;
	int smoothedLength = length - filterLength + 1;

	// for (int i = adjustment; i < (length - adjustment + 1); i++)
	// {
	// 	for (int j = 0; j < filterLength; j++)
	// 	{
	// 		summed += data[i + j];
	// 		// printf("summed%g\nj = %d", summed, j);
	// 	}
	// 	// printf("---------\n");
	// 	smoothed[i] = summed/filterLength;
	// 	summed = 0.0;
	// }

	double *cursor;
	cursor = data;
	for (int i = 0; i < smoothedLength; i++)
	{
		for (int j = 0; j < filterLength; j++)
		{
			summed += cursor[j];
		}

		smoothed[i] = summed/filterLength;
		summed = 0.0;
		cursor++;
	}

}
int adcConvert(char* data, double* converted, double volts)
{
	int  start = 1;
	start = data[1] - '0';
    char str[5] = "";    

    for(int i = 2; i <= (start + 1); i++)
    {
    	char ch = data[i];
    	strncat(str, &ch, 1);
    }

    int numdatapoints = atoi(str) - (start + 2);

    for(int i = start ; i < 2500; i++)
    {
       converted[i - start] = data[i + 2] * volts*10.0/256.0;
    }

    return (2500 - (start + 2));
}

void writeToFile(char* name, double start_freq, double amplength, double* ampData, double incr)
{
	FILE* outputfile =   fopen(name,"w");
    double freq = start_freq;
    fprintf(outputfile,"x,y\n");
    for(int i = 0; i < amplength; i++)
    {
      fprintf(outputfile,"%f,%0.5f\n", freq, ampData[i]);
      freq += incr;
    }
    fclose(outputfile);
}

double calculateAmplitude(double* smoothed_data, int length)
{
	double meanValue = 0.0;
	double rmsValue = 0.0;
	double amplitudeValue = 0.0;

	meanValue = mean(smoothed_data, length);
  	rmsValue = rms(smoothed_data, length, meanValue);
  	amplitudeValue = amplitude(rmsValue);
  	return amplitudeValue;
}

double theController(double start_freq, double end_freq, double incr)
{
	
}

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "signal_analysis.h"

double SA_Mean(int n, double * data){
	double Mean = 0.0;
	for (int i = 0; i< n; i++) {
		Mean=Mean+data[i];
	}
	return (Mean/n);
}

double SA_RMS(int n, double * data, double mean) {
	double RMS = 0.0;
	double point = 0.0;
	for (int i = 0; i< n; i++) {
		point = data[i] - mean;
		RMS = RMS + point*point;
	}
	return sqrt(RMS/n);
}

void SA_smooth(int n, int m, double * data, double * result){
	for (int i = 0; i< n; i++) {
		/* JAMES: Potential problem here. You
		have result[i] = result[i]+data[i+j].Your result array may not be
		empty when the function starts. For example if SA_smooth is called
		twice on two different data sets with the same result array.
		so result[i] may not equal zero for j = 0. You should zero result before
		entering this second loop with result[i] = 0;

		MY: Fixed
		*/
		result[i] = 0;
		for (int j = 0; j< m; j++) {
			result[i]=result[i]+data[i+j];
		}
		result[i]=result[i]/m;
	}
}

double SA_Amplitude(double rms){
	return (rms*sqrt(2.0));
}

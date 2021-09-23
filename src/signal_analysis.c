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
		for (int j = 0; j< m; j++) {
			result[i]=result[i]+data[i+j];
		}
		result[i]=result[i]/m;
	}
}

double SA_Amplitude(double rms){
	return (rms*sqrt(2.0));
}



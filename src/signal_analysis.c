#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "signal_analysis.h"

double SA_Mean(int n, double * data){
	double Mean = 0;
	for (int i = 0; i< n; i++) {
		Mean=Mean+data[i];
	}
	return Mean;
}

void SA_RMS(int n, double * data, double * result) {
	double Sqrt = sqrt(2.0);
	for (int i = 0; i< n; i++) {
		result[i]=data[i]/Sqrt;
	}
}
//void SA_smooth();
double SA_Amplitude(int n, double * data){
	double mini=0;
	double maxi=0;
	for (int i = 0; i< n; i++) {
		if (maxi<data[i]){
			maxi=data[i];
		}
		if (mini>data[i]){
			mini=data[i];
		}
	}
	return ((maxi-mini)/2);
}



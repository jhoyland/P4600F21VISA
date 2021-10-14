#include <stdio.h>
#include <stdlib.h>
#include "signal_analysis.h"
#include <time.h>
#include <windows.h>
#include <math.h>

float SA_Mean(int n, float * data){
	float Mean = 0.0;
	for (int i = 0; i< n; i++) {
		Mean=Mean+data[i];
	}
	return (Mean/n);
}

float SA_RMS(int n, float * data, float mean) {
	float RMS = 0.0;
	float point = 0.0;
	for (int i = 0; i< n; i++) {
		point = data[i] - mean;
		RMS = RMS + point*point;
	}
	return sqrt(RMS/n);
}

float SA_smooth(int n, int m, float * data, float * result){
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

float SA_Amplitude(float rms){
	return (rms*sqrt(2.0));
}


void OSC_data_to_voltage (int length, float size_division, unsigned char * input, float * output) {
  double quant = 10.0*size_division/256.0; 
  int i=0;
  int value=0;
  while (i<(length-6)){
    output[i]=((double)input[i+6]-127.0)*quant;
    i=i+1;
  }
}

void V_vs_F_datasave (int F_array_size, float * F_array, float * Vamp_array,char * file_name) {
    const char * name = file_name;
    FILE* outputfile1 =   fopen(name,"w");
    fprintf(outputfile1,"Frequency f (Hz), Voltage Amplitude V_amp (V)\n");
    for(int i = 0; i< F_array_size; i++)
    {
      fprintf(outputfile1,"%f,%f\n",F_array[i],Vamp_array[i]);
    }
    fflush(stdout);
    fclose(outputfile1);
}
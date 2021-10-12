#ifndef __SIGNALANALYSIS_H
#define __SIGNALANALYSIS_H

// JAMES: Just as a matter of style, since your header name is
// signal_analysis.h the header guard name would usually be
// __SIGNAL_ANALYSIS_H

float SA_Mean(int n, float * data);
float SA_RMS(int n, float * data, float mean);
float SA_Amplitude(float rms);
float SA_smooth(int n, int m, float * data, float * result);
void OSC_data_to_voltage (int length, float size_division, unsigned char * input, float * output);
void V_vs_F_datasave (int F_array_size, float * F_array, float * Vamp_array,char * file_name);
#endif

#include <stdio.h>
#include <stdlib.h>
#include "signal_analysis.h"
#include "visa_coms.h"
#include "visa.h"
#include <time.h>
#include <windows.h>


int main(int argc, char** argv) {
  ViStatus status = VI_SUCCESS;
  ViSession resource_manager;
  ViSession scope_handle, functiongen_handle;

  if(status!=VI_SUCCESS){
    exit(1);
  }
  else{  

    OSC_setup (status,&resource_manager,&scope_handle);
    FG_setup (status, &resource_manager,&functiongen_handle);

    char returned_message[128];

    char * file_name = "FG_and_OSC_go_BRRRRRR.csv";
    int FG_channel=1; // either "1" or "2"
    int OSC_channel=1; // either "1" or "2"
    float F_bot= 1000.0; //in Hz
    float F_top= 10000.0; //in Hz
    float F_step= 1000; //in Hz
    float phase_offset=0.0; // degrees, from "0" to "<360"
    float V_offset=0.0;
    float fg_volt=1.35; // volts
    int osc_resol=2500; // 2 <--> 2500
    int move_avg_window=25;

    int F_array_size=((F_top-F_bot)/F_step)+1;
    float F_array[F_array_size];
    float Vamp_array[F_array_size];
    float F_now;
    float vertical_scale;
    int OSC_data_size = osc_resol;
    int true_OSC_data_size=OSC_data_size-6;
    unsigned char OSC_data[OSC_data_size];
    float voltage_data[true_OSC_data_size];
    
    int i=0;
    while (i<F_array_size){
      F_now=F_bot + (float)i*F_step;
      F_array[i]=F_now;

      FG_parameters(functiongen_handle,FG_channel,F_now,fg_volt,V_offset,phase_offset);
      
      OSC_setup1(scope_handle,OSC_channel,osc_resol);

      vertical_scale = OSC_setup2(scope_handle,OSC_channel);

      OSC_gather(scope_handle,OSC_data);

      OSC_data_to_voltage(OSC_data_size, vertical_scale, OSC_data, voltage_data);

      int smooth_data_size=true_OSC_data_size-move_avg_window+1;

      float smooth_voltage_data[smooth_data_size];

      SA_smooth(smooth_data_size,move_avg_window,voltage_data,smooth_voltage_data);

      float mean_smooth = SA_Mean(smooth_data_size,smooth_voltage_data);

      float rms_smooth = SA_RMS(smooth_data_size,smooth_voltage_data,mean_smooth);

      Vamp_array[i] = SA_Amplitude(rms_smooth);

      i=i+1;
    }

    V_vs_F_datasave (F_array_size, F_array, Vamp_array,file_name);

    viClose(scope_handle);
    viClose(functiongen_handle);

  }
}

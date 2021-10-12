#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "signal_analysis.h"
#include "visa_coms.h"
#include "visa.h"
#include <time.h>
#include <windows.h>
/*
  TASK:

  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated

*/



// ViSession VISA_OSC_setup(ViStatus status, ViSession resource_manager, ViSession scope_handle, ViFindList resource_list, long unsigned int resource_num, char description) { 
//   status = viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&resource_num,description);
//   if(status!=VI_SUCCESS){
//     // printf("Occilloscope is not found");
//     // fflush(stdout);
//     exit(1);
//   }
//   status=viOpen(resource_manager,description,VI_NULL,VI_NULL,&scope_handle);
//   if(status!=VI_SUCCESS){
//     // printf("Occilloscope connection is not established");
//     // fflush(stdout);
//     exit(1);
//   }
//   // printf("\n\n\nOccilloscope is connected\n\n\n");
//   // fflush(stdout);

//   return(scope_handle);
// }

// ViSession VISA_FG_setup(ViStatus status, ViSession resource_manager, ViSession functiongen_handle, ViFindList resource_list, long unsigned int resource_num, char description) {
//   status = viFindRsrc(resource_manager,"USB[0-9]::0x1AB1?*INSTR",&resource_list,&resource_num,description);
//   if(status!=VI_SUCCESS){
//     // printf("Function generator is not found");
//     // fflush(stdout);
//     exit(1);
//   }
//   status=viOpen(resource_manager,description,VI_NULL,VI_NULL,&functiongen_handle);
//   if(status!=VI_SUCCESS){
//     // printf("Function generator connection is not established");
//     // fflush(stdout);
//     exit(1);
//   }
//   //printf("\n\n\nFunction generator is connected\n\n\n");
//   // fflush(stdout);

//   return(functiongen_handle);
// }

int main(int argc, char** argv) {
  ViStatus status = VI_SUCCESS;
  ViSession resource_manager;
  ViSession scope_handle, functiongen_handle;
  status = viOpenDefaultRM(&resource_manager);
  ViFindList resource_list;
  long unsigned int resource_num;
  char description[VI_FIND_BUFLEN];

  if(status!=VI_SUCCESS){
    printf("Something is wrong");
    fflush(stdout);
    exit(1);
  }
  else{    
    status = viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&resource_num,description);
    if(status!=VI_SUCCESS){
      printf("Occilloscope is not found");
      fflush(stdout);
      exit(1);
    }
    status=viOpen(resource_manager,description,VI_NULL,VI_NULL,&scope_handle);
    if(status!=VI_SUCCESS){
      printf("Occilloscope connection is not established");
      fflush(stdout);
      exit(1);
    }
    printf("\n\n\nOccilloscope is connected\n\n\n");
    fflush(stdout);

    status = viFindRsrc(resource_manager,"USB[0-9]::0x1AB1?*INSTR",&resource_list,&resource_num,description);
    if(status!=VI_SUCCESS){
      printf("Function generator is not found");
      fflush(stdout);
      exit(1);
    }
    status=viOpen(resource_manager,description,VI_NULL,VI_NULL,&functiongen_handle);
    if(status!=VI_SUCCESS){
      printf("Function generator connection is not established");
      fflush(stdout);
      exit(1);
    }
    printf("\n\n\nFunction generator is connected\n\n\n");
    fflush(stdout);

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













    

    // viPrintf(functiongen_handle,"SOURCE1:APPLY:SIN %lf,0.5,0,0\n",F_now);
    // viPrintf(scope_handle,"DATA:WIDTH 1\n");
    // viPrintf(scope_handle,"DATA:SOURCE CH1\n");
    // viPrintf(scope_handle,"DATA:ENCDG RPBINARY\n");
    // viPrintf(scope_handle,"DATA:START 1\n");
    // viPrintf(scope_handle,"DATA:STOP 2500\n");
    // viPrintf(scope_handle,"DATA:STOP?\n");
    // viScanf(scope_handle,"%t",returned_message);
    // int OSC_data_size=atof(returned_message);
    // int true_OSC_data_size=OSC_data_size-6;
    // unsigned char OSC_data[OSC_data_size];
    // float voltage_data[true_OSC_data_size];



    // viPrintf(scope_handle,"AUTOSet EXECute\n");

    // viPrintf(scope_handle,"CH1:SCALE?\n");
    // viScanf(scope_handle,"%t",returned_message);
    // float vertical_scale = atof(returned_message);

    // viPrintf(scope_handle,"CH1:POSition 0.0\n");

    // viPrintf(scope_handle,"CURVE?\n");;
    // viScanf(scope_handle,"%t",OSC_data);
    // printf("\n");



    // // FILE* outputfile1 =   fopen("OSC_data.dat","w");
    // // for(int i = 6; i< OSC_data_size; i++)
    // // {
    // //   fprintf(outputfile1,"\n%d",OSC_data[i]);
    // // }
    // // fflush(stdout);
    // // fclose(outputfile1);

    // OSC_data_to_voltage(OSC_data_size, vertical_scale, OSC_data, voltage_data);



    // int move_avg_window=25;
    // int smooth_data_size=true_OSC_data_size-move_avg_window+1;
    // float smooth_voltage_data[smooth_data_size];

    // SA_smooth(smooth_data_size,move_avg_window,voltage_data,smooth_voltage_data);



    // FILE* outputfile2 =   fopen("OSC_vdata.dat","w");
    // for(int i = 0; i < true_OSC_data_size; i++)
    // {
    //   fprintf(outputfile1,"\n%f",voltage_data[i]);
    // }
    // fflush(stdout);
    // fclose(outputfile2);



    // FILE* outputfile3 =   fopen("OSC_vdata_smooth.dat","w");
    // for(int i = 0; i < smooth_data_size; i++)
    // {
    //   fprintf(outputfile1,"\n%f",smooth_voltage_data[i]);
    // }
    // fflush(stdout);
    // fclose(outputfile2);

  }
}

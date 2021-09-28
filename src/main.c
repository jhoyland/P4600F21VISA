#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "signal_analysis.h"
#include "visa.h"
#include <time.h>

/*
  TASK:

  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated

*/


int main(int argc, char** argv)
{

  // int ndata = 1024;
  // // JAMES:Your variable names move_avg_size and move_avg are a little confusing
  // int move_avg_window=10;
  // int move_avg_arraysize=ndata-move_avg_window+1;

  // double x[ndata];
  // double smooth[move_avg_arraysize];

  // random_data(ndata,x);
  // SA_smooth(move_avg_arraysize,move_avg_window,x,smooth);
  // double mean_smooth = SA_Mean(move_avg_arraysize,smooth);
  // double rms_smooth = SA_RMS(move_avg_arraysize,smooth,mean_smooth);
  // double amplitude_smooth = SA_Amplitude(rms_smooth);

  // FILE* outputfile0 =   fopen("result.dat","w");
  // for(int i = 0; i< ndata; i++)
  // {
  //   fprintf(outputfile0,"\n%d) Value  : %0.5f",i,x[i]);
  // }
  // fprintf(outputfile0,"\n\n\n");

  // for(int i = 0; i< move_avg_arraysize; i++)
  // {
  //   fprintf(outputfile0,"\n%d) Smooth : %0.5f",i,smooth[i]);
  // }
  // fprintf(outputfile0,"\n\n\n");
  // fprintf(outputfile0,"\nMean of Smoothed Data:%0.5f",mean_smooth);
  // fprintf(outputfile0,"\nRMS of Smoothed Data:%0.5f",rms_smooth);
  // fprintf(outputfile0,"\nAmplitude of Smoothed Data:%0.5f",amplitude_smooth);
  // fclose(outputfile0);

  // FILE* outputfile1 =   fopen("og.dat","w");
  // for(int i = 0; i< ndata; i++)
  // {
  //   fprintf(outputfile1,"\n%0.5f",x[i]);
  // }
  // fclose(outputfile1);

  // FILE* outputfile2 =   fopen("smooth.dat","w");
  // for(int i = 0; i< move_avg_arraysize; i++)
  // {
  //   fprintf(outputfile2,"\n%0.5f",smooth[i]);
  // }
  // fclose(outputfile2);

  

  ViStatus status = VI_SUCCESS;
  ViSession resource_manager;
  ViSession scope_handle;
  status = viOpenDefaultRM(&resource_manager);
  ViFindList resource_list;
  long unsigned int resource_num;
  char description[VI_FIND_BUFLEN];

  if(status!=VI_SUCCESS){
    printf("things go BRRRRRRRR");
    fflush(stdout);
    exit(1);
  }
  else{    
    status = viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&resource_num,description);
    if(status!=VI_SUCCESS){
      printf("instruments go BRRRRRRRR");
      fflush(stdout);
      exit(1);
    }
    status=viOpen(resource_manager,description,VI_NULL,VI_NULL,&scope_handle);
    if(status!=VI_SUCCESS){
      printf("connection go BRRRRRRRR");
      fflush(stdout);
      exit(1);
    }
    printf("\n\n\nhehe boi\n\n\n");
  fflush(stdout);

  	float desired_vert_scale;
  float desired_vert_offset;
  float desired_horz_scale;	

    char returned_message[128];
    viPrintf(scope_handle,"*IDN?\n");
    viScanf(scope_handle,"%t",returned_message);
    printf(returned_message);
    fflush(stdout);

    // MY:ques and adjust vertical scale;
    viPrintf(scope_handle,"CH1:SCALE?\n");
    viScanf(scope_handle,"%t",returned_message);
    fflush(stdout);
    printf("\nvertical scale RN: %s",returned_message);
    fflush(stdout);
    printf("\nDESIRED vertical scale? :");
    fflush(stdout);
    scanf("%f",desired_vert_scale);
    viPrintf(scope_handle,"CH1:SCALE %f\n",desired_vert_scale); //value is volt-based
    viPrintf(scope_handle,"CH1:SCALE?\n");
    viScanf(scope_handle,"%t",returned_message);
    printf(returned_message);
    fflush(stdout);

    printf("\n");

    // MY:ques and adjust vertical offset;
  viPrintf(scope_handle,"CH1:POSition?\n");
    viScanf(scope_handle,"%t",returned_message);
    printf("\nvertical offset RN: %s",returned_message);
    fflush(stdout);
    printf("\nDESIRED vertical offset? :");
    fflush(stdout);
    scanf("%f",desired_vert_offset);
    viPrintf(scope_handle,"CH1:POSition %f\n",desired_vert_offset); //value is fraction of current vertical division
    viPrintf(scope_handle,"CH1:POSition?\n");
    viScanf(scope_handle,"%t",returned_message);
    printf(returned_message);
    fflush(stdout);

    printf("\n");

    // MY:ques and adjust timescale;
    viPrintf(scope_handle,"HORizontal:MAIn:SCAle?\n"); 
    viScanf(scope_handle,"%t",returned_message);
    printf("\nhorizontal scale RN: %s",returned_message);
    fflush(stdout);
    printf("\nDESIRED horizontal scale? :");
    fflush(stdout);
    scanf("%f",desired_vert_scale);
    viPrintf(scope_handle,"HORizontal:MAIn:SCAle %f\n",desired_horz_scale); //value is second-based
    viPrintf(scope_handle,"HORizontal:MAIn:SCAle?\n");
    viScanf(scope_handle,"%t",returned_message);
    printf(returned_message);
    fflush(stdout);

  }

}

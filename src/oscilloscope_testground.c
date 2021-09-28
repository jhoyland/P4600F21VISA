#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "signal_analysis.h"
#include "visa.h"
#include <time.h>

int reeeeeee(int argc, char** argv)
{
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

    char returned_message[128];
    viPrintf(scope_handle,"*IDN?\n");
    viScanf(scope_handle,"%t",returned_message);
    printf(returned_message);
    fflush(stdout);

    // MY:ques and adjust vertical scale;
    viPrintf(scope_handle,"CH1:SCALE?\n");
    viScanf(scope_handle,"%t",returned_message);
    printf(returned_message);
    fflush(stdout);
    viPrintf(scope_handle,"CH1:SCALE 0.1\n"); //value is volt-based
    viPrintf(scope_handle,"CH1:SCALE?\n");
    viScanf(scope_handle,"%t",returned_message);
    printf(returned_message);
    fflush(stdout);

    printf("\n");

    // MY:ques and adjust vertical offset;
  viPrintf(scope_handle,"CH1:POSition?\n");
    viScanf(scope_handle,"%t",returned_message);
    printf(returned_message);
    fflush(stdout);
    viPrintf(scope_handle,"CH1:POSition 0.64\n"); //value is fraction of current vertical division
    viPrintf(scope_handle,"CH1:POSition?\n");
    viScanf(scope_handle,"%t",returned_message);
    printf(returned_message);
    fflush(stdout);

    printf("\n");

    // MY:ques and adjust timescale;
    viPrintf(scope_handle,"HORizontal:MAIn:SCAle?\n"); 
    viScanf(scope_handle,"%t",returned_message);
    printf(returned_message);
    fflush(stdout);
    viPrintf(scope_handle,"HORizontal:MAIn:SCAle 0.0025\n"); //value is second-based
    viPrintf(scope_handle,"HORizontal:MAIn:SCAle?\n");
    viScanf(scope_handle,"%t",returned_message);
    printf(returned_message);
    fflush(stdout);

  }
}

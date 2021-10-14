#include <stdio.h>
#include <stdlib.h>
#include "visa.h"
#include <time.h>
#include <windows.h>
#include "visa_coms.h"

void FG_parameters (ViSession functiongen_handle, int current_channel, float F_now, float fg_volt, float V_offset, float phase_offset){
  viPrintf(functiongen_handle,"SOURCE%d:APPLY:SIN %f,%f,%f,%f\n",current_channel,F_now,fg_volt,V_offset,phase_offset);
  Sleep(5000);
}

void OSC_setup1(ViSession scope_handle,int current_channel, int osc_resol) {
  viPrintf(scope_handle,"DATA:WIDTH 1\n");
  viPrintf(scope_handle,"DATA:SOURCE CH%d\n",current_channel);
  viPrintf(scope_handle,"DATA:ENCDG RPBINARY\n");
  viPrintf(scope_handle,"DATA:START 1\n");
  viPrintf(scope_handle,"DATA:STOP %d\n",osc_resol);
}

float OSC_setup2(ViSession scope_handle,int current_channel) {
  char returned_message[128];
  viPrintf(scope_handle,"AUTOSet EXECute\n");
  Sleep(5000);
  viPrintf(scope_handle,"CH%d:POSition 0.0\n",current_channel);
  Sleep(2500);
  viPrintf(scope_handle,"CH%d:SCALE?\n",current_channel);
  viScanf(scope_handle,"%t",returned_message);
  float vertical_scale = atof(returned_message);
  return(vertical_scale);
}

void OSC_gather(ViSession scope_handle,unsigned char * OSC_data) {
  viPrintf(scope_handle,"CURVE?\n");
  viScanf(scope_handle,"%t",OSC_data);
  Sleep(2500);
}


void OSC_setup (ViStatus status, ViSession * resource_manager, ViFindList resource_list, long unsigned int resource_num, char * description,ViSession * scope_handle) {
  status = viFindRsrc(*resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&resource_num,description);
  if(status!=VI_SUCCESS){
    exit(1);
  }
  status=viOpen(*resource_manager,description,VI_NULL,VI_NULL,scope_handle);
  if(status!=VI_SUCCESS){
    exit(1);
  }
}

void FG_setup (ViStatus status, ViSession * resource_manager, ViFindList resource_list, long unsigned int resource_num, char * description,ViSession * functiongen_handle) {
  status = viFindRsrc(*resource_manager,"USB[0-9]::0x1AB1?*INSTR",&resource_list,&resource_num,description);
  if(status!=VI_SUCCESS){
    exit(1);
  }
  status=viOpen(*resource_manager,description,VI_NULL,VI_NULL,functiongen_handle);
  if(status!=VI_SUCCESS){
    exit(1);
  }
}
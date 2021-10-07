#include <stdio.h>
#include <stdlib.h>
#include <randdata.h>
#include <time.h>
#include "visa.h"
#include "convertScopedata.h"
#include "myFunction.h"
#include "dataTofile.h"
#include <windows.h>

/*
  TASK:

  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated

*/

int main(int argc, char const *argv[])
{
  ViStatus status = VI_SUCCESS;
  ViSession resource_manager;
  ViSession scope_handle, fgHandle;
  ViFindList resource_list;
  long unsigned int num_inst;
  char description[VI_FIND_BUFLEN];

  unsigned int channel = 1;
  double volts = 1.0;

  status = viOpenDefaultRM(&resource_manager);
  if(status != VI_SUCCESS)
  {
    //Do something about it
    printf("Whoa");
    exit(1);
  }
  else
  {
    //continue finding the scope
    status = viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&num_inst,description);
    if(status != VI_SUCCESS)
    {
      printf("could not find any scopes");
      fflush(stdout);
      exit(1);
    }

    status = viOpen(resource_manager,description,VI_NULL,VI_NULL,&scope_handle);
    if(status != VI_SUCCESS)
    {
      printf("could not connect to scope");
      fflush(stdout);
      exit(1);
    }

    //continue finding the function generator
    status = viFindRsrc(resource_manager,"USB[0-9]::0x1AB1?*INSTR",&resource_list,&num_inst,description);
    if(status != VI_SUCCESS)
    {
      printf("could not find any function generator");
      fflush(stdout);
      exit(1);
    }

    status = viOpen(resource_manager,description,VI_NULL,VI_NULL,&fgHandle);
    if(status != VI_SUCCESS)
    {
      printf("could not connect to function generator");
      fflush(stdout);
      exit(1);
    }




// Function generator commands goes here:::::::::::::::::::::::::::::::
    printf("\nOpened function generator\n");
    fflush(stdout);

    char fgInfo[128];

    viPrintf(fgHandle, "*IDN?\n");
    viScanf(fgHandle,"%t",fgInfo);

    printf(fgInfo);
    fflush(stdout);


    viPrintf(fgHandle,"Source1:APPLY:SIN 10,5,0,0\n"); //<freq Hz>,<amp Vpp/2>,<offset Vdc>,<phase deg>
    viPrintf(fgHandle,"OUTP1:STAT ON\n");

    //viPrintf(fgHandle,"SYST:BEEP:IMM\n");
    //beep loop
    /*int x=0;
    for(x=0; x<10; x++)
    {
      viPrintf(fgHandle,"SYST:BEEP:IMM\n");
      Sleep(500);
    }*/
    
    
// Oscilloscope commands goes here:::::::::::::::::::::::::::::::::
    printf("\nOpened scope\n");
    fflush(stdout);

    char scopeInfo[128];

    viPrintf(scope_handle, "*IDN?\n");
    viScanf(scope_handle,"%t\n",scopeInfo);

    printf(scopeInfo);
    fflush(stdout);

    //char volt_message[128];
    //viPrintf(scope_handle, "CH1:SCAle 1.0\n CH1:POS 0\n HOR:POS 0\n HOR:SCA 500E-6\n"); //preset CH1 viewing window
    printf("\nAutosetting...\n");
    fflush(stdout);
    viPrintf(scope_handle,"AUTOSet EXECute\n");//autoset 
    Sleep(5000);
    //viScanf(scope_handle,"%t",volt_message);
    //printf(volt_message);
    


    //Try and bring in data from the oscilloscope
    char dataGot[2500];
    double dataDouble[2500];
    double delta_volts=5.0; //Vpp is 5.0v in function generator
    double step = delta_volts/256.0;
    int i=0;
    viPrintf(scope_handle, "DATa:SOUrce CH1\n DATa:ENCdg RIBinary\n DATa:STARt 1\n DATa:STOP 2500\n CURVe?\n");
    viScanf(scope_handle,"%t", dataGot);

    convertScopedata(dataGot, dataDouble, step);
    printf("\nData converted\n");
    fflush(stdout);
    dataTofile(dataDouble, "scopedata", 2500);
    printf("Data file created\n");
    fflush(stdout);

    viClose(scope_handle);
    viClose(fgHandle);
  }

  return 0;
}


/*int main(int argc, char** argv)
{

  int ndata = 1024;
  int windowLen = 5;
  double x[ndata];
  double smoothSignal[ndata - windowLen + 1];
  random_data(ndata,x);
  

  double avg, rootmeansquare, amp;

  avg = mean(x,ndata);
  printf("The mean is %g\n",avg);

  rootmeansquare = rms(x, ndata);
  printf("The RMS is %g\n",rootmeansquare);

  amp = amplitude(rootmeansquare, avg);
  printf("The amplitude is %g\n",amp);

  smooth(x, ndata, windowLen, smoothSignal);



  FILE* outputfile =   fopen("data.dat","w");
  if(outputfile != NULL)
  {
    for(int i = 0; i< ndata; i++)
      {
        fprintf(outputfile,"\n%0.5f",x[i]);

      }
      fclose(outputfile);
  }


  FILE* smoothdatafile = fopen("smoothdata.dat","w");
  if(smoothdatafile != NULL)
  {
    for(int i=0; i< ndata-windowLen+1; i++)
    {
      fprintf(smoothdatafile,"\n%0.5f", smoothSignal[i]);
    }
    fclose(smoothdatafile);
  }
  
}*/

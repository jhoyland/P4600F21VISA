#include <stdio.h>
#include <stdlib.h>
#include <randdata.h>
#include <time.h>
#include "visa.h"
#include "myFunction.h"

/*
  TASK:

  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated

*/

int main(int argc, char const *argv[])
{
  ViStatus status = VI_SUCCESS;
  ViSession resource_manager;
  ViSession scope_handle;
  ViFindList resource_list;
  unsigned int num_inst;
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
    //continue
    status = viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&num_inst,description);
    if(status != VI_SUCCESS)
    {
      printf("could not find any instruments");
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
// Oscilloscope commands goes here:::::::::::::::::::::::::::::::::
    printf("\nOpened scope\n");

    char returned_message[128];

    viPrintf(scope_handle, "*IDN?\n");
    viScanf(scope_handle,"%t",returned_message);

    printf(returned_message);


    //char volt_message[128];
    viPrintf(scope_handle, "CH1:SCAle 1.0\n CH1:POS 0\n HOR:POS 0\n HOR:SCA 500E-6\n");
    //viScanf(scope_handle,"%t",volt_message);
    //printf(volt_message);
    
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

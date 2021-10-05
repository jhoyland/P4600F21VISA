#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include <time.h>
#include <math.h>
#include "dataprocessing.h"
#include "visa.h"

/*
  TASK:

  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated

*/


/* int main(int argc, char** argv)
{

  int ndata = 1024;
  double x[ndata];

  random_data(ndata,x);


    //Code to test your functions goes here
  

  // find mean of randdata, RMS, AMP, and print to file

  double m, r, a; 
  m = mean(x, ndata);
  r = rms(x, ndata);
  a = Amp(x, ndata);

  FILE* datafile = fopen("sampleinfo.dat","w");

  fprintf(datafile,"\n MEAN = %f", m);
  fprintf(datafile,"\n RMS = %f", r);
  fprintf(datafile,"\n AMPLITUDE = %f", a);

  fclose(datafile);


  // END TESTING
  // file printing

  FILE* outputfile =   fopen("data.dat","w");

  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile,"\n%0.5f",x[i]);
  }

  fclose(outputfile);


} */

//CALLING THE OSCILLOSCOPE

int main(int argc, char** argv)
{
  ViStatus status = VI_SUCCESS;
  ViSession resource_manager;
  ViSession scope_handle;
  ViFindList resource_list;
  unsigned int num_inst;
  char description[VI_FIND_BUFLEN];


  status = viOpenDefaultRM(&resource_manager);

  if(status != VI_SUCCESS)
  {
    //Do something about it 
    printf("Your princess is in another castle!");
    exit(1);
  }
  else
  {
    //We do the next thing
    status = viFindRsrc(resource_manager, "USB[0-9]::0x0699?*INSTR", &resource_list, &num_inst, &description);

    if(status != VI_SUCCESS)
    {
      printf("Could not locate any instruments");
      fflush(stdout);
      exit(1);
    }

  status = viOpen(resource_manager, description, VI_NULL, VI_NULL, &scope_handle);
  
  if(status != VI_SUCCESS)
    {
      printf("Could not connect to scope");
      fflush(stdout);
      exit(1);
    } 
  printf("\nOpened Scope\n");

  char returned_message[128];

  viPrintf(scope_handle, "*IDN?\n");
  viScanf(scope_handle, "%t", returned_message);

  printf(returned_message);

  // now try other commands

  viPrintf(scope_handle, "CH1:SCA 1 \n");

  // try to use the curve command to read in a set of data
  //create an array to store values: 
  viPrintf(scope_handle, "DATA:SOURCE CH1\nDATA:ENC BINARY\nDATA:WIDTH 1\nDATA:START 0\nDATA:STOP 2500\n");

  char data[2500];

  viPrintf(scope_handle, "CURVe?\n");
  viScanf(scope_handle, "%t", data);
  int i;
  //read through loop
  /*for(i=0; i<2500; i++)
  {
    printf("%d \n",data[i]);
  }
  */
  //print data to a file 

  FILE* datafile = fopen("curve.dat","w");
  double ddata[2500];

  for(i=0; i<2500; i++)
  {
    ddata[i] = (10/255) * data[i];
    fprintf(datafile,"%d \n",ddata[i]);
  }

  fclose(datafile);

  return 0;
  }
}
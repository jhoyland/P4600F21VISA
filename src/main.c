#include <stdio.h>
#include <stdlib.h>
#include <randdata.h>
#include <time.h>
#include "visa.h"
#include <windows.h>

/*
  TASK:

  Create, in a separate file a set of functions to calculate:
  The mean, RMS value and amplitude and smoothed version of the random data generated

*/


int main(int argc, char** argv)
{

  int ndata = 1024;
  double x[ndata];

  ViStatus status = VI_SUCCESS;
  ViFindList resourceList;
  ViUInt32 num_inst;
  ViUInt32 resultCount;

  ViSession defaultRM, scopeHandle;
  ViChar description[VI_FIND_BUFLEN];
  setvbuf(stdout,NULL,_IONBF,16);

  //random_data(ndata,x);

  status = viOpenDefaultRM(&defaultRM); //open the resource manager
  if (status != VI_SUCCESS)
  {
    // Do something if RM cannot open
  }
  else
  {
    status = viFindRsrc(defaultRM,"USB[0-9]::0x0699?*INSTR",&resourceList,&num_inst,description); //find the scope
		if (status != VI_SUCCESS)
		{
			// Do something if cannot find scope
		}
		else
		{
      printf("\nFound Scope");

      status = viOpen(defaultRM,description,VI_NULL,VI_NULL,&scopeHandle); //open the scope and give it a handle
      if(status != VI_SUCCESS)
      {
        // Do something if cannot open scope
      }
      else
      {

        printf("\nOpened Scope");

        char ret[50];

        viWrite(scopeHandle,"*IDN?\n",5,&resultCount);
        //Sleep(1000);
        viRead(scopeHandle,ret,50,&resultCount);


        printf(ret);
        printf("\nGot here");

        //fflush(stdout);
      }

    }
  }



  /*
    Code to test your functions goes here
  */

  FILE* outputfile =   fopen("data.dat","w");

  for(int i = 0; i< ndata; i++)
  {
    fprintf(outputfile,"\n%0.5f",x[i]);

  }

  fclose(outputfile);


}

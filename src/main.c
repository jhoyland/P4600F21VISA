#include <stdio.h>
#include <stdlib.h>
#include <randdata.h>
#include <time.h>
#include "visa.h"
#include <windows.h>

#define MESSAGE_LENGTH 128

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

  ViSession defaultRM, fgHandle;
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
    status = viFindRsrc(defaultRM,"USB[0-9]::?*INSTR",&resourceList,&num_inst,description); //find the scope
		if (status != VI_SUCCESS)
		{
			// Do something if cannot find scope
		}
		else
		{
      printf("\nFound function gnerator\n");
      printf(description);

      status = viOpen(defaultRM,description,VI_NULL,VI_NULL,&fgHandle); //open the scope and give it a handle
      if(status != VI_SUCCESS)
      {
        // Do something if cannot open scope
      }
      else
      {

        printf("\nOpened function generator");

        char ret[MESSAGE_LENGTH];

        viPrintf(fgHandle,"*IDN?\n");
        //Sleep(1000);
        //viFlush(fgHandle,VI_READ_BUF_DISCARD);
        viScanf(fgHandle,"%t",ret);

        printf(ret);

        viPrintf(fgHandle,"SOURCE1:APPLY:SIN 175,0.003,-0.5,0\n");
        viPrintf(fgHandle,"OUTP1:STAT ON\n");
        viPrintf(fgHandle,"SYST:BEEP:IMM");

      /*    float v = 1.0;

        viPrintf(fgHandle,"CH1:SCALE %0.2f\n",v);
      viRead(fgHandle,ret,10,&resultCount);

        double scale;

        sscanf(ret,"%lf\n",&scale);

        printf(ret);
        printf("\nConverted value: %f",scale);*/

        viClose(fgHandle);
        viClose(defaultRM);
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

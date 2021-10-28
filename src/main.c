#include <stdio.h>
#include <stdlib.h>
#include <randdata.h>
#include <time.h>
#include <windows.h>
#include "visa.h"
#include "myFunction.h"
#include "dataTofile.h"
#include "fgenerator.h"
#include "oscope.h"


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

  unsigned int channel = 1;  //channel being used
  double volts = 1.0;

  resource_manager = initRM();    //initialize resource manager

  scope_handle = initScope(resource_manager);
  fgHandle = initFG(resource_manager);

// Function generator commands goes here:::::::::::::::::::::::::::::::
  fgInfo(fgHandle);

  setSinwave(fgHandle,1,100,5,0,0); //<CH:1>, <freq>, <amplitude>, <offset>, <phase>
  displayWave(fgHandle,1); //<CH:1>

    //beep(fgHandle);
    
    
// Oscilloscope commands goes here:::::::::::::::::::::::::::::::::
  scopeInfo(scope_handle);



    //char volt_message[128];
    //viScanf(scope_handle,"%t",volt_message);
    //printf(volt_message);

    
  setScopewindow(scope_handle,1,1.0,0,5E-3,0); //<handle>, <CH>, <y scale>, <y pos>, <x scale>, <x pos>

   
    //autosetScope(scope_handle);

    //Try and bring in data from the oscilloscope
  char dataGot[2500];
  double dataDouble[2500];
  double delta_volts = 0.0; //Vpp is 5.0v in function generator
  double step = delta_volts/256.0;
 
  getScopedata(scope_handle, 1, dataGot);

  delta_volts = getScopevolts(scope_handle, 1);

  convertScopedata(dataGot, dataDouble, delta_volts);

  printf("\nData converted\n");
  fflush(stdout);

  dataTofile(dataDouble, "scopedata", 2494);
  printf("Data file created\n");
  fflush(stdout);



  double avg=0.0, rms=0.0, amp=0.0;
  scanScopedata(dataDouble, &avg, &rms, &amp);


  viClose(scope_handle);
  viClose(fgHandle);


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

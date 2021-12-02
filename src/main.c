#include <stdio.h>
#include <stdlib.h>
#include "calculations.h"
#include "instrumentfunctions.h"
#include "visa.h"


int main(int argc, char** argv)
{
  ViStatus status = VI_SUCCESS;
  ViSession scope_handle, func_handle;      //handles for the instruments

  double frequency = 23000;
  double amplitude = 1;

  status = openInstruments(&scope_handle, &func_handle);   

  if(status != VI_SUCCESS)
    {
        printf("Ooops");
        exit(1);
    }
  else
    {
        amplitude = getAmplitude(frequency, scope_handle, func_handle); 
        double scale = getScopeScale(scope_handle); 
        printf("\nAmplitude: %g, Scale: %g", amplitude, scale);
        fflush(stdout);
        

                 
    }

}
 
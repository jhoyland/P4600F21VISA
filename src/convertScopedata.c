#include <stdio.h>
#include <stdlib.h>
#include "visa.h"

//Try and bring in data from the oscilloscope
    void convertScopedata(char *dataGot, double *dataDouble, double step)
    {
      int i=0;
      for(i=0; i<2500; i++)
      {
       dataDouble[i] = dataGot[i] * step;
      }

    }
    
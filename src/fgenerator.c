#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fgenerator.h"
#include <time.h>
#include <windows.h>




ViStatus setSinWave(ViSession handle, int channel, double amplitude, double frequency, double offset, double phase)
{
	ViStatus status = VI_SUCCESS;
	status = viPrintf(handle,"SOURCE%d:APPLY:SIN %f, %f, %f, %f\n",channel,frequency, amplitude, offset, phase);
	return status;
}

void getdata(ViSession scope_handle, int channel, char *data)
{
  viPrintf(scope_handle,"DATA:SOURCE CH%d\n",channel);
  viPrintf(scope_handle,"DATA:ENC RIBINARY\n");
  viPrintf(scope_handle,"DATA:WIDTH 1\n");
  viPrintf(scope_handle,"DATA:START 1\n");
  viPrintf(scope_handle,"DATA:STOP 2500\n");
  Sleep(2500);
  viPrintf(scope_handle,"CURVE?\n");
  viScanf(scope_handle,"%t",data);
}

double getvoltage(char *data, double v)
{
  double data_double[2500];
  int i;
  for(i=0;i<2500;i++)
  {
    data_double[i]=data[i];
  }

  FILE* outputfile =   fopen("data.dat","w");
   for(i=0;i<2500;i++)
   {
    data_double[i] = data_double[i]*10.0*v/255.0;
    fprintf(outputfile,"%f\n",data_double[i]);
   }
  fclose(outputfile);
  return 0;
}


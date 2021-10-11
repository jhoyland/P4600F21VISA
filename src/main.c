 #include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "calculations.h"
#include <time.h>
#include <math.h>
#include "visa.h"


int main(int argc, char** argv)
{

  int ndata = 2500;
  char rawDataArray[ndata+6];
  double dataArray[ndata];                    //was the array called x
  int window = 5; 
  int ndataSmoothed = ndata-(window-1);
  double dataArraySmoothed[ndataSmoothed];  //was the array called xSmoothed

  ViStatus status = VI_SUCCESS;
  ViSession resource_manager;
  ViSession scope_handle;
  ViFindList resource_list;
  long unsigned int num_inst;
  char description[VI_FIND_BUFLEN];


  status = viOpenDefaultRM(&resource_manager);

  if(status != VI_SUCCESS)
    {
        //do something about it
        printf("Ooops");
        exit(1);
    }
  else
    {
        status = viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&num_inst, description);

        if (status != VI_SUCCESS)
        {
            printf("Counldn't find any instruments.");
            fflush(stdout);
            exit(1);
        }

        status = viOpen(resource_manager,description,VI_NULL, VI_NULL, &scope_handle);

        if (status != VI_SUCCESS)
        {
            printf("Counldn't connect to scope.");
            fflush(stdout);
            exit(1);
        }

        char returned_message[128];                     //for the returned message from the instrument

        viPrintf(scope_handle, "*IDN?\n");              //gets the instrument that we are talking to
        viScanf(scope_handle,"%t", returned_message);   //puts that instrument into returned_message
        printf("Opened scope: ");
        printf(returned_message);                       //prints the instrument it found


        viPrintf(scope_handle, "DATA:WIDTH 1\n");
        viPrintf(scope_handle, "DATA:SOURCE CH1\n");
        viPrintf(scope_handle, "DATA:ENCODE RIBINARY\n");
        viPrintf(scope_handle, "DATA:START 1\n");
        viPrintf(scope_handle, "DATA:STOP 2500\n");


        printf("n is: %i", ndataSmoothed);
        viPrintf(scope_handle, "CURVE?\n");         //opens a quiery to the scope
        viScanf(scope_handle, "%t", rawDataArray);  //writes data to an array

        for (int i=0;i<ndata;i++)
        {
          dataArray[i] = rawDataArray[i+6];         //rewrite the data to convert char to double and starts at element 6 
        }

        double mean1, rms, amp;

        smoothing(dataArray,ndata, window, dataArraySmoothed);
  
        mean1 = mean(dataArraySmoothed,ndataSmoothed);
        printf ("Mean: %g \n", mean1);

        rms = rootMeanSquare(dataArraySmoothed,ndataSmoothed);
        printf ("RMS: %g \n", rms);

        amp = amplitude(dataArraySmoothed,ndataSmoothed);

        printf("Amplitude: %g \n", amp);

        printf("%g",dataArraySmoothed[1]);
        fflush(stdout);                             //flushes the prints out of the system













        /*viPrintf(scope_handle, "CH1:SCA?\n");           //gets the scale
        viScanf(scope_handle,"%t", returned_message);   //puts scale into returned_message
        printf("Scale:");                               
        printf(returned_message);                       //prints scale

        viPrintf(scope_handle, "CH1:SCA 1.0\n");      //changes CH1 scale
        viPrintf(scope_handle, "HOR:POS 6.0E-06\n");  //change horizontal position
        viPrintf(scope_handle, "CH1:POS -1.0\n");        //change position on channel 1, + up, - down 

        viPrintf(scope_handle, "HOR:SCA .01\n");      //change horizontal scale
        */

    }

  FILE* outputfile =   fopen("data.dat","w");

  if (outputfile != NULL)
  {

    for(int i = 0; i< ndata; i++)
    {
      fprintf(outputfile,"\n%0.5f",dataArray[i]);

    }

    fclose(outputfile);
  }

  FILE* outputfile1 =   fopen("data1.dat","w");

  if (outputfile1 != NULL)
  {

    for(int i = 0; i< ndataSmoothed ; i++)
    {
      fprintf(outputfile1,"\n%0.5f",dataArraySmoothed[i]);

    }

    fclose(outputfile);
  }

}

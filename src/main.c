#include <stdio.h>
#include <stdlib.h>
#include "calculations.h"
#include "instrumentfunctions.h"
//#include <time.h>
//#include <math.h>
#include "visa.h"
//#include <windows.h>


int main(int argc, char** argv)
{

  /*int ndata = 2500;                         //the number of retrieved data points 
  char rawDataArray[ndata+6];               //the curve data points
  double voltages[ndata];                   //array for converting curve to voltages          
  int window = 5;                           //the size for smoothing the noise
  int ndataSmoothed = ndata-(window-1);     //the reduced size of the smoothed array
  double voltagesSmoothed[ndataSmoothed];   //voltages after smoothing
*/
  ViStatus status = VI_SUCCESS;
  //ViSession resource_manager;
  ViSession scope_handle, func_handle;      //handles for the instruments

  double frequency = 2000;
  double amplitude = 1;

  //char returned_message[128];               //for the returned message from the instrument

  //variables for function generator
  /*int chan_func = 1;
  int nfreq = 10;
  float freq_func[] = {200,300,500,1000,1500,5000,10000,15000,20000,50000};
  float amp_func = 20;
  float amp_output[nfreq];
  double scale;    */                         //scope scale

  //status = createResourceManager(&resource_manager);
  status = openInstruments(&scope_handle, &func_handle);

  if(status != VI_SUCCESS)
    {
        //do something about it
        printf("Ooops");
        exit(1);
    }
  else
    {
        amplitude = getAmplitude(frequency, scope_handle, func_handle);
        printf("%g", amplitude);
      //Opening function generator

        //openFunctionGenerator(resource_manager, &func_handle);

        //getInstrumentName(func_handle, returned_message);
        //printf("Opened function generator: ");
        //printf(returned_message);                       //prints the instrument it found

      //Opening scope

        //openScope(resource_manager, &scope_handle);

        //getInstrumentName(scope_handle, returned_message);
        //printf("Opened scope: ");
        //printf(returned_message);                       //prints the instrument it found

        /*for (int i = 0; i < 1; i++)
        {
          setSinWave(func_handle,chan_func,freq_func[i],amp_func);        //sets the function generator with new parameters

          autoSetScope(scope_handle);                                     //autosets scope after new signal from func gen
          Sleep(4000);                                                    //need a pause after autoset

          getNewCurve(scope_handle, rawDataArray);                        //get the new curve data         

          scale = getScopeScale(scope_handle);                            //gets the scope scale after autoset

          convertCurveToVoltage(ndata, rawDataArray, scale, voltages);    //converts curve data to voltages

          smoothing(voltages, ndata, window, voltagesSmoothed);           //smooths the voltages
    
          amp_output[i] = amplitude(voltagesSmoothed,ndataSmoothed);      //saves new voltage into an array
          printf("%9g\t%7g\n", freq_func[i], amp_output[i]);

          fflush(stdout);                                                 //flushes the prints out of the system
        }*/
                            

    }

}

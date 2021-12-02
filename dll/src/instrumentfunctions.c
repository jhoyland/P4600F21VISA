#include <stdlib.h>
#include <stdio.h>
#include "instrumentfunctions.h"
#include <math.h>
#include "visa.h"
#include "calculations.h"
#include <windows.h>

//This function opens  the resource manager
//Returns if opening is successful
ViStatus createResourceManager(ViSession *resource_manager)
{
     ViStatus status = viOpenDefaultRM(resource_manager);
     return status;
}

//This function connects with the function generator (replaced with openInstruments)
void openFunctionGenerator(ViSession resource_manager, ViSession *func_handle)
{
    ViFindList resource_list;
    long unsigned int num_inst;
    char description[VI_FIND_BUFLEN];

    viFindRsrc(resource_manager,"USB[0-9]::0x1AB1?*INSTR",&resource_list,&num_inst, description);
    viOpen(resource_manager,description,VI_NULL, VI_NULL, func_handle);
}

//This function connects with the oscilloscope (replaced with openInstruments)
void openScope(ViSession resource_manager, ViSession *scope_handle)
{
    ViFindList resource_list;
    long unsigned int num_inst;
    char description[VI_FIND_BUFLEN];

    viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&num_inst, description);
    viOpen(resource_manager,description,VI_NULL, VI_NULL, scope_handle);
}

//This function connects with the oscilloscope and function generator.
//Returns the status of opening up the resource manager
ViStatus openInstruments(ViSession *scope_handle, ViSession *func_handle)
{
    ViFindList resource_list;
    long unsigned int num_inst;
    char description[VI_FIND_BUFLEN];

    ViSession resource_manager;
    ViStatus status = viOpenDefaultRM(&resource_manager);               //opens resource manager

    viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&num_inst, description);  //looks for oscilloscope in resource manager
    viOpen(resource_manager,description,VI_NULL, VI_NULL, scope_handle);                           //opens the oscilloscope and assigns it a handle

    viFindRsrc(resource_manager,"USB[0-9]::0x1AB1?*INSTR",&resource_list,&num_inst, description);  //looks for the function generator in resource manager      
    viOpen(resource_manager,description,VI_NULL, VI_NULL, func_handle);                            //opens function generator and assigns it a handle

    return status;

}

//This function takes in a frequecnty and scope and function generator handle 
//Returns the amplitude at that frequency
double getAmplitude(double frequency, ViSession scope_handle, ViSession func_handle)
{
    int ndata = 2500;                         //the number of retrieved data points 
    char rawDataArray[ndata+6];               //the curve data points
    double voltages[ndata];                   //array for converting curve to voltages          
    int window = 5;                           //the size for smoothing the noise
    int ndataSmoothed = ndata-(window-1);     //the reduced size of the smoothed array
    double voltagesSmoothed[ndataSmoothed];   //voltages after smoothing
    double scale;                             //scope scale

    setSinWave(func_handle,1,frequency);        //sets the function generator with a new frequency
    
    autoSetScope(scope_handle);                                     //autosets scope after new signal from func gen
    Sleep(5000);                                                    //need a pause after autoset

    getNewCurve(scope_handle, rawDataArray);                        //get the new curve data         

    scale = getScopeScale(scope_handle);                            //gets the scope scale after autoset

    convertCurveToVoltage(ndata, rawDataArray, scale, voltages);    //converts curve data to voltages

    smoothing(voltages, ndata, window, voltagesSmoothed);           //smooths the voltages
    
    return amplitude(voltagesSmoothed,ndataSmoothed);               //saves new voltage into an array
}

//This function sets the function gen. to a sin wave at a specific frequency
void setSinWave(ViSession handle, int channel, double frequency)
{
viPrintf(handle, "SOURCE%d:APPLY:SIN %f\n", channel, frequency);
}

//This function gets the name of the name of the connected instrument.
void getInstrumentName(ViSession handle, char* returned_message)
{

	viPrintf(handle, "*IDN?\n");              //gets the instrument that we are talking to
    viScanf(handle,"%t", returned_message);   //puts that instrument into returned_message
}

//This function gets the voltage scale of the oscilloscope
double getScopeScale(ViSession handle)
{
    char scaleChar[20];
    viPrintf(handle, "CH1:SCA?\n");           //gets the scale
    viScanf(handle,"%t", scaleChar);            //puts scale into returned_message
    double scale = (double)atof(scaleChar);	 //converts char string to a float
    return scale;
}

//This function retrieves the data presented on the oscilloscope screen
void getNewCurve(ViSession handle, char* rawDataArray)
{
    viPrintf(handle, "DATA:WIDTH 1\n");
    viPrintf(handle, "DATA:SOURCE CH1\n");
    viPrintf(handle, "DATA:ENCODE RIBINARY\n");
    viPrintf(handle, "DATA:START 1\n");
    viPrintf(handle, "DATA:STOP 2500\n");
    viPrintf(handle, "CURVE?\n");         //opens a quiery to the scope
    viScanf(handle, "%t", rawDataArray);  //writes data to an array



    FILE* outputfile = fopen("data.dat","w");               //saves the data to a file. used for inspection of the raw data
    {
        for(int i=0; i<2500; i++ )
        {
            fprintf(outputfile,"\n%d",rawDataArray[i]);

        }
    fclose(outputfile);
    }
}

//This funtion autosets the oscilloscope
void autoSetScope(ViSession handle)
{
    viPrintf(handle, "AUTOSET EXECUTE\n");
}

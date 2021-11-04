#include <stdlib.h>
#include <stdio.h>
#include "instrumentfunctions.h"
#include <math.h>
#include "visa.h"
#include "calculations.h"
//#include <time.h>
#include <windows.h>

ViStatus createResourceManager(ViSession *resource_manager)
{
     ViStatus status = viOpenDefaultRM(resource_manager);
     return status;
}

void openFunctionGenerator(ViSession resource_manager, ViSession *func_handle)
{
    ViFindList resource_list;
    long unsigned int num_inst;
    char description[VI_FIND_BUFLEN];

    viFindRsrc(resource_manager,"USB[0-9]::0x1AB1?*INSTR",&resource_list,&num_inst, description);
    viOpen(resource_manager,description,VI_NULL, VI_NULL, func_handle);
}

void openScope(ViSession resource_manager, ViSession *scope_handle)
{
    ViFindList resource_list;
    long unsigned int num_inst;
    char description[VI_FIND_BUFLEN];

    viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&num_inst, description);
    viOpen(resource_manager,description,VI_NULL, VI_NULL, scope_handle);
}

ViStatus openInstruments(ViSession *scope_handle, ViSession *func_handle)
{
    ViFindList resource_list;
    long unsigned int num_inst;
    char description[VI_FIND_BUFLEN];

    ViSession resource_manager;
    ViStatus status = viOpenDefaultRM(&resource_manager);

    viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&num_inst, description);
    viOpen(resource_manager,description,VI_NULL, VI_NULL, scope_handle);

    viFindRsrc(resource_manager,"USB[0-9]::0x1AB1?*INSTR",&resource_list,&num_inst, description);
    viOpen(resource_manager,description,VI_NULL, VI_NULL, func_handle);

    return status;

}

double getAmplitude(double frequency, ViSession scope_handle, ViSession func_handle)
{
    int ndata = 2500;                         //the number of retrieved data points 
    char rawDataArray[ndata+6];               //the curve data points
    double voltages[ndata];                   //array for converting curve to voltages          
    int window = 5;                           //the size for smoothing the noise
    int ndataSmoothed = ndata-(window-1);     //the reduced size of the smoothed array
    double voltagesSmoothed[ndataSmoothed];   //voltages after smoothing
    double scale;                             //scope scale

    setSinWave(func_handle,1,frequency,20);        //sets the function generator with new parameters

    autoSetScope(scope_handle);                                     //autosets scope after new signal from func gen
    Sleep(4000);                                                    //need a pause after autoset

    getNewCurve(scope_handle, rawDataArray);                        //get the new curve data         

    scale = getScopeScale(scope_handle);                            //gets the scope scale after autoset

    convertCurveToVoltage(ndata, rawDataArray, scale, voltages);    //converts curve data to voltages

    smoothing(voltages, ndata, window, voltagesSmoothed);           //smooths the voltages
    
    return amplitude(voltagesSmoothed,ndataSmoothed);      //saves new voltage into an array
}

void setSinWave(ViSession handle, int channel, double frequency, double amplitude )
{
	viPrintf(handle, "SOURCE%d:APPLY:SIN %f, %f\n", channel, frequency, amplitude);
}

void getInstrumentName(ViSession handle, char* returned_message)
{

	viPrintf(handle, "*IDN?\n");              //gets the instrument that we are talking to
    viScanf(handle,"%t", returned_message);   //puts that instrument into returned_message
}

double getScopeScale(ViSession handle)
{
    char scaleChar[20];
    viPrintf(handle, "CH1:SCA?\n");           //gets the scale
    viScanf(handle,"%t", scaleChar);            //puts scale into returned_message
    double scale = (double)atof(scaleChar);	 //converts char string to a float
    return scale;
}

void getNewCurve(ViSession handle, char* rawDataArray)
{
    viPrintf(handle, "DATA:WIDTH 1\n");
    viPrintf(handle, "DATA:SOURCE CH1\n");
    viPrintf(handle, "DATA:ENCODE RIBINARY\n");
    viPrintf(handle, "DATA:START 1\n");
    viPrintf(handle, "DATA:STOP 2500\n");
    viPrintf(handle, "CURVE?\n");         //opens a quiery to the scope
    viScanf(handle, "%t", rawDataArray);  //writes data to an array
}

void autoSetScope(ViSession handle)
{
    viPrintf(handle, "AUTOSET EXECUTE\n");
}


/*double setFreqGetAmp(frequency)
{
    int chan_func = 1;
    int nfreq = 10;
    //float freq_func[] = {200,300,500,1000,1500,5000,10000,15000,20000,50000};
    //float amp_func = 20;
    //float amp_output[nfreq];
    double scale;                             //scope scale

    setSinWave(func_handle,chan_func,freq_func[i],amp_func);        //sets the function generator with new parameters

    autoSetScope(scope_handle);                                     //autosets scope after new signal from func gen
    Sleep(4000);                                                    //need a pause after autoset

    getNewCurve(scope_handle, rawDataArray);                        //get the new curve data         

    scale = getScopeScale(scope_handle);                            //gets the scope scale after autoset

    convertCurveToVoltage(ndata, rawDataArray, scale, voltages);    //converts curve data to voltages

    smoothing(voltages, ndata, window, voltagesSmoothed);           //smooths the voltages
    
    return amplitude(voltagesSmoothed,ndataSmoothed);      //saves new voltage into an array
}*/
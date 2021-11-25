#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main(int argc, char** argv) 
{
ViStatus status = VI_SUCCESS;
ViSession fun_generator;
ViFindList resource_list;
char returned_message[128];
unsigned int num_inst;
char description[VI_FIND_BUFLEN];
ViSession resource_manager;


if(status != VI_SUCCESS)
{
  printf("Ooops");
}
else
{//function generator
  status = viFindRsrc(rm,"USB[0-9]::0x1AB1?*INSTR",&resource_list,&num_inst,description);
  if(status != VI_SUCCESS)
    {
      printf("couldn't find any instrument");
      fflush(stdout);
      exit(1);
    }
  status = viOpen(rm,description,VI_NULL,VI_NULL,&fun_generator);
  if(status != VI_SUCCESS)
    {
      printf("couldn't connect to function generator");
      fflush(stdout);
      exit(1);
    }
  printf("\nOpened function generator");
  viPrintf(fun_generator,"*IDN?\n");
  viScanf(fun_generator,"%t",returned_message);

  printf(returned_message);
  fflush(stdout);
}
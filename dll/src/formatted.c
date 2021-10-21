/*#include <stdlib.h>
#include <stdio.h>
#include "visa.h"

int main(int argc, char const *argv[])
{
	ViStatus status = VI_SUCCESS;
	ViSession resource_manager;
	ViSession scope_handle;
	ViFindList resource_list;
	unsigned int num_inst;
	char description[VI_FIND_BUFLEN];
	

	status = viOpenDefaultRM(&resource_manager);
	if(status != VI_SUCCESS)
	{
		//Do something about it
		printf("Whoa");
		exit(1);
	}
	else
	{
		//continue
		status = viFindRsrc(resource_manager,"USB[0-9]::0x0699?*INSTR",&resource_list,&num_inst,description);
		if(status != VI_SUCCESS)
		{
			printf("could not find any instruments");
			fflush(stdout);
			exit(1);
		}

		status = viOpen(resource_manager,description,VI_NULL,VI_NULL,scope_handle);
		if(status != VI_SUCCESS)
		{
			printf("could not connect to scope");
			fflush(stdout);
			exit(1);
		}

		printf("\nOpened scope");

		char returned_message[128];

		viPrintf(scope_handle, "*IDN?\n");
		viScanf(scope_handle,"%t",returned_message);

		printf(returned_message);

	}


	return 0;
}*/
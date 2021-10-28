#include <stdio.h>
#include <stdlib.h>
#include "randdata.h"
#include "camparmo.h"
#include "fgenerator.h"
#include "scope.h"
#include <time.h>
#include <windows.h>

ViSession rm() 
{
	ViSession resource_manager;
	ViStatus status = VI_SUCCESS;
	status = viOpenDefaultRM(&resource_manager);
	return status;
}
%module datalink
%{
#include "visatype.h"
#include "fgenerator.h"
#include "oscope.h"
%}

typedef unsigned int ViSession;

ViSession resourceCreate();
ViSession initScope(ViSession resource_manager);

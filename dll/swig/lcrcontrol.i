%module add
%{
	#include "name.h"
}

typedef unsigned int ViSession;

function prototype;


swig -python name.i
gcc -c name.c
gcc -c -I/(adress of Python.h) name_wrap.c

gcc -shared name.o name_wrap.o -L(adress of Python.dll) -lpython(version #) -o _name.pyd(this has to named the same as the import file)
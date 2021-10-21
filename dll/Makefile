# Compiler and linker options
CC        = gcc
CFLAGS    = -c -Wall -g
LDFLAGS   = -shared -v

MINGW_ENV = mingw64
PYVERSION = 37

HOMEDIR   = /c/msys64/home/$(USER)/P4600F21VISA
# User directories to search
BUILDDIR  = $(HOMEDIR)/dll/build
INCDIR    = $(HOMEDIR)/dll/includes
SRCDIR    = $(HOMEDIR)/dll/src
SWIGDIR		= $(HOMEDIR)/dll/swig
PYDIR			= $(HOMEDIR)/python

#ANACONDAPATH = /c/Users/$(USER)/Anaconda3
ANACONDAPATH = /c/ProgramData/Anaconda3


# 3rd Party library directories to search
LIBDIR    = /$(MINGW_ENV)/lib $(HOMEDIR)/dll/lib $(ANACONDAPATH)/libs
LIBINCDIR = $(HOMEDIR)/dll/includes $(ANACONDAPATH)/include

# List sources, object files and libraries to be used
SOURCES   = $(wildcard $(SRCDIR)/*.c )
OBJECTS   = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
LIBRARIES = visa64 python$(PYVERSION)

# Create command line arguments
LIBCMD    = $(addprefix -l,$(LIBRARIES))
LIBDIRCMD = $(addprefix -L,$(LIBDIR))
INCCMD    = $(addprefix -I,$(INCDIR) $(LIBINCDIR))

# The final executable name
TARGET    = datalink


# The rules

all: $(SOURCES) $(TARGET)

# Compile the DLL object files

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCCMD) $< -o $@

# Link the DLL

$(HOMEDIR)/$(TARGET).dll: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBDIRCMD) $(LIBCMD) -o $@

# Create the swig wrappers from the interface

$(SWIGDIR)/$(TARGET)_wrap.c: $(INCLUDES) $(SWIGDIR)/$(TARGET).i
	swig -python -py3 -outdir $(PYDIR) $(INCCMD) -o $@ $(SWIGDIR)/$(TARGET).i

# Compile the swig wrappers

$(SWIGDIR)/$(TARGET)_wrap.o: $(SWIGDIR)/$(TARGET)_wrap.c
	$(CC) $(CFLAGS) $(INCCMD) $(SWIGDIR)/$(TARGET)_wrap.c -o $@

# Link the wrapped python library

$(PYDIR)/_$(TARGET).pyd: $(OBJECTS) $(SWIGDIR)/$(TARGET)_wrap.o
	$(CC) $(LDFLAGS) $(OBJECTS) $(SWIGDIR)/$(TARGET)_wrap.o $(LIBDIRCMD) $(LIBCMD) -o $@

swig: $(PYDIR)/_$(TARGET).pyd

dll: $(HOMEDIR)/$(TARGET).dll

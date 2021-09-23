# Compiler and linker options
CC        = gcc
CFLAGS    = -c -Wall -g
LDFLAGS   =

# User directories to search
HOMEDIR   = /c/msys64/home/DCamparmo/P4600F21VISA
BUILDDIR  = $(HOMEDIR)/build
INCDIR    = $(HOMEDIR)/include
SRCDIR    = $(HOMEDIR)/src


# 3rd Party library directories to search
LIBDIR    = /mingw64/lib $(HOMEDIR)/libs
LIBINCDIR = $(HOMEDIR)/includes

# List sources, object files and libraries to be used
SOURCES   = $(wildcard $(SRCDIR)/*.c )
OBJECTS   = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
LIBRARIES =

# Create command line arguments
LIBCMD    = $(addprefix -l,$(LIBRARIES))
LIBDIRCMD = $(addprefix -L,$(LIBDIR))
INCCMD    = $(addprefix -I,$(INCDIR) $(LIBINCDIR))

# The final executable name
TARGET    = datamanip

# The rules

all: $(SOURCES) $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCCMD) $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBDIRCMD) $(LIBCMD) -o $@

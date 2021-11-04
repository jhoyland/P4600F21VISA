
CFLAGS    = -c -Wall -g
LDFLAGS   =

# User directories to search
BUILDDIR  = ./build
INCDIR    = ./includes $(HOMEDIR)/dll/include
SRCDIR    = ./src

HOMEDIR   = /c/msys64/home/texas/p4600F21visa

# 3rd Party library directories to search
LIBDIR    = /mingw64/lib $(HOMEDIR)/lib $(HOMEDIR)
LIBINCDIR = $(HOMEDIR)/includes $(HOMEDIR)/dll/indlude

# List sources, object files and libraries to be used
SOURCES   = $(wildcard $(SRCDIR)/*.c )# Compiler and linker options
CC        = gcc
OBJECTS   = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
LIBRARIES = visa64 datalink

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

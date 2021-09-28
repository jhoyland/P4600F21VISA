# Compiler and linker options
CC        = gcc
CFLAGS    = -c -g
LDFLAGS   =

# User directories to search
BUILDDIR  = ./build
INCDIR    = ./include
SRCDIR    = ./src

HOMEDIR   = /c/msys64/home/BMcClennon/week3/P4600F21VISA

# 3rd Party library directories to search
LIBDIR    = /mingw64/lib $(HOMEDIR)/lib
LIBINCDIR = $(HOMEDIR)/includes

# List sources, object files and libraries to be used
SOURCES   = $(wildcard $(SRCDIR)/*.c )
OBJECTS   = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
LIBRARIES = visa64

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

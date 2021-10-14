HOMEDIR   = /c/msys64/home/MYakovlev/LCR_Project/P4600F21VISA


# Compiler and linker options
CC        = gcc
CFLAGS    = -c -v -g
LDFLAGS   = -shared

# User directories to search
BUILDDIR  = $(HOMEDIR)/dll/build
INCDIR    = $(HOMEDIR)/dll/include
SRCDIR    = $(HOMEDIR)/dll/src


# 3rd Party library directories to search
LIBDIR    = /mingw64/lib $(HOMEDIR)/dll/lib
LIBINCDIR = $(HOMEDIR)/dll/includes

# List sources, object files and libraries to be used
SOURCES   = $(wildcard $(SRCDIR)/*.c )
OBJECTS   = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
LIBRARIES = visa64 

# Create command line arguments
LIBCMD    = $(addprefix -l,$(LIBRARIES))
LIBDIRCMD = $(addprefix -L,$(LIBDIR))
INCCMD    = $(addprefix -I,$(INCDIR) $(LIBINCDIR))

# The final executable name
TARGET    = FG_OSC_func

# The rules

all: $(SOURCES) $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCCMD) $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBDIRCMD) $(LIBCMD) -o $(HOMEDIR)/$@.dll

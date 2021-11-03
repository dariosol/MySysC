# Compiler and linker flags
SYSTEMC_HOME =/Users/dario/SystemC/systemc-2.3-2.3/
TARGET_ARCH = macosx64

ARCH_SUFFIX = -$(TARGET_ARCH)

## How to instruct the dynamic linker to locate the SystemC library
LDFLAG_RPATH = -Wl

# default compiler flags
FLAGS_COMMON = -g -Wall
FLAGS_STRICT = -pedantic -Wno-long-long
FLAGS_WERROR = -Werror

# combined flags
SYSTEMC_CXXFLAGS = $(FLAGS_COMMON) $(FLAGS_STRICT) $(FLAGS_WERROR)

# Explicit location of the SystemC headers
SYSTEMC_INC_DIR = $(SYSTEMC_HOME)/include

# Explicit location if the SystenC library
SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib$(ARCH_SUFFIX)

#########################

SYSTEMC_LDFLAGS  = -L $(SYSTEMC_LIB_DIR)
SYSTEMC_LIBS     = -lsystemc -lm

INCDIR   += -I$(SYSTEMC_INC_DIR)
INCDIR   += $(INCLUDE_FLAGS)

CXXFLAGS  += $(CFLAGS) $(SYSTEMC_CXXFLAGS) $(INCDIR) $(SYSTEMC_DEFINES)
LDFLAGS   += $(CFLAGS) $(SYSTEMC_CXXFLAGS) $(LIBDIR) $(SYSTEMC_LDFLAGS)
LIBS      += $(SYSTEMC_LIBS) $(EXTRA_LIBS)

CXX=/usr/local/Cellar/gcc/11.2.0/bin/g++-11
CC=$(CXX)


# List of all ecutables to be compiled
EXECUTABLES = main

# .PHONY targets don't generate files
.PHONY:	all clean

# Default targets
all:	$(EXECUTABLES)

# Compile rules
main:	main.cpp consumer.h producer.h stack.h stack_if.h
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o $@ main.cpp consumer.h producer.h stack.h stack_if.h $(LIBS) 2>&1

# Clean rule to delete temporary and generated files
clean:
	rm -f $(EXECUTABLES) *.o *~

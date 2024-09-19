# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra

# Include directories
INCLUDES = -lcryptopp -I./include/

# Source files
SRCS = ./src/main.cpp ./src/crypt_safe.cpp

# Header files
HDRS = ./include/crypt_safe.h

OBJS = /usr/lib/x86_64-linux-gnu/libcryptopp.a ./build/main.o ./build/crypt_safe.o

# Executable name
TARGET = cryptsafe

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): make_crypt_safe make_main
	$(CXX) $(CXXFLAGS) $(OBJS) -o app $(INCLUDES) 

# Compile source files into object files
make_crypt_safe:	
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o ./build/crypt_safe.o ./src/crypt_safe.cpp

make_main:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o ./build/main.o ./src/main.cpp

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
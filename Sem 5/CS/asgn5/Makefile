# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Include directories
INCLUDES = -lcryptopp -I./include -I/usr/include/nlohmann -I/usr/include/date

# Source files
SRCS = ./src/main.cpp ./src/certify_me.cpp ./src/certificate.cpp

# Header files
HDRS = ./include/certify_me.h ./include/certificate.h

# Object files
OBJS = /usr/lib/x86_64-linux-gnu/libcryptopp.a ./build/main.o ./build/certify_me.o ./build/certificate.o

# Executable name
TARGET = certify_me

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): make_certificate make_certify make_main
	$(CXX) $(CXXFLAGS) $(OBJS) -o app $(INCLUDES)

# Compile source files into object files
make_certify:	
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o ./build/certify_me.o ./src/certify_me.cpp

make_certificate:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o ./build/certificate.o ./src/certificate.cpp

make_main:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o ./build/main.o ./src/main.cpp

# Clean up build files
clean:
	rm -f ./build/*.o app

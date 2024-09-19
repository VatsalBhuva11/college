# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Include directories
INCLUDES = -lcryptopp -I./include -I/usr/include/nlohmann -I/usr/include/date

# Source files
SRCS = ./src/main.cpp ./src/crypt_safe.cpp

# Header files
HDRS = ./include/crypt_safe.h

# Object files
OBJS = /usr/lib/x86_64-linux-gnu/libcryptopp.a ./build/main.o ./build/crypt_safe.o ../asgn5/build/certify_me.o ../asgn5/build/certificate.o

# Executable name
TARGET = cryptsafe

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o app $(INCLUDES) 

# Compile source files into object files
./build/crypt_safe.o: ./src/crypt_safe.cpp ./include/crypt_safe.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o ./build/crypt_safe.o ./src/crypt_safe.cpp

./build/main.o: ./src/main.cpp ./include/crypt_safe.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o ./build/main.o ./src/main.cpp

# Clean up build files
clean:
	rm -f ./build/*.o app

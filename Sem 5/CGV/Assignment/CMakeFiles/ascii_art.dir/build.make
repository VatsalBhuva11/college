# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment"

# Include any dependencies generated for this target.
include CMakeFiles/ascii_art.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ascii_art.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ascii_art.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ascii_art.dir/flags.make

CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.o: CMakeFiles/ascii_art.dir/flags.make
CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.o: IIT2022004_ascii_art.cpp
CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.o: CMakeFiles/ascii_art.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.o -MF CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.o.d -o CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.o -c "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment/IIT2022004_ascii_art.cpp"

CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment/IIT2022004_ascii_art.cpp" > CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.i

CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment/IIT2022004_ascii_art.cpp" -o CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.s

# Object files for target ascii_art
ascii_art_OBJECTS = \
"CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.o"

# External object files for target ascii_art
ascii_art_EXTERNAL_OBJECTS =

ascii_art: CMakeFiles/ascii_art.dir/IIT2022004_ascii_art.cpp.o
ascii_art: CMakeFiles/ascii_art.dir/build.make
ascii_art: CMakeFiles/ascii_art.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ascii_art"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ascii_art.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ascii_art.dir/build: ascii_art
.PHONY : CMakeFiles/ascii_art.dir/build

CMakeFiles/ascii_art.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ascii_art.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ascii_art.dir/clean

CMakeFiles/ascii_art.dir/depend:
	cd "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment" "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment" "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment" "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment" "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CGV/Assignment/CMakeFiles/ascii_art.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ascii_art.dir/depend

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/169/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/169/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/agd3/Desktop/ED/practica3-colas_y_pilas

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/agd3/Desktop/ED/practica3-colas_y_pilas/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cola_max.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/cola_max.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cola_max.dir/flags.make

CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.o: CMakeFiles/cola_max.dir/flags.make
CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.o: ../estudiante/src/cola_max.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/agd3/Desktop/ED/practica3-colas_y_pilas/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.o -c /home/agd3/Desktop/ED/practica3-colas_y_pilas/estudiante/src/cola_max.cpp

CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/agd3/Desktop/ED/practica3-colas_y_pilas/estudiante/src/cola_max.cpp > CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.i

CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/agd3/Desktop/ED/practica3-colas_y_pilas/estudiante/src/cola_max.cpp -o CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.s

# Object files for target cola_max
cola_max_OBJECTS = \
"CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.o"

# External object files for target cola_max
cola_max_EXTERNAL_OBJECTS =

cola_max: CMakeFiles/cola_max.dir/estudiante/src/cola_max.cpp.o
cola_max: CMakeFiles/cola_max.dir/build.make
cola_max: libmaxqueue.a
cola_max: CMakeFiles/cola_max.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/agd3/Desktop/ED/practica3-colas_y_pilas/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cola_max"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cola_max.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cola_max.dir/build: cola_max
.PHONY : CMakeFiles/cola_max.dir/build

CMakeFiles/cola_max.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cola_max.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cola_max.dir/clean

CMakeFiles/cola_max.dir/depend:
	cd /home/agd3/Desktop/ED/practica3-colas_y_pilas/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/agd3/Desktop/ED/practica3-colas_y_pilas /home/agd3/Desktop/ED/practica3-colas_y_pilas /home/agd3/Desktop/ED/practica3-colas_y_pilas/cmake-build-debug /home/agd3/Desktop/ED/practica3-colas_y_pilas/cmake-build-debug /home/agd3/Desktop/ED/practica3-colas_y_pilas/cmake-build-debug/CMakeFiles/cola_max.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cola_max.dir/depend


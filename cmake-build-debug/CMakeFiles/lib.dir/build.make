# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /mnt/c/Users/Administrator/CLionProjects/project_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Administrator/CLionProjects/project_1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lib.dir/flags.make

CMakeFiles/lib.dir/lib/long_arithmetic.cxx.o: CMakeFiles/lib.dir/flags.make
CMakeFiles/lib.dir/lib/long_arithmetic.cxx.o: /mnt/c/Users/Administrator/CLionProjects/project_1/lib/long_arithmetic.cxx
CMakeFiles/lib.dir/lib/long_arithmetic.cxx.o: CMakeFiles/lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/Administrator/CLionProjects/project_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lib.dir/lib/long_arithmetic.cxx.o"
	/usr/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lib.dir/lib/long_arithmetic.cxx.o -MF CMakeFiles/lib.dir/lib/long_arithmetic.cxx.o.d -o CMakeFiles/lib.dir/lib/long_arithmetic.cxx.o -c /mnt/c/Users/Administrator/CLionProjects/project_1/lib/long_arithmetic.cxx

CMakeFiles/lib.dir/lib/long_arithmetic.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lib.dir/lib/long_arithmetic.cxx.i"
	/usr/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Administrator/CLionProjects/project_1/lib/long_arithmetic.cxx > CMakeFiles/lib.dir/lib/long_arithmetic.cxx.i

CMakeFiles/lib.dir/lib/long_arithmetic.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lib.dir/lib/long_arithmetic.cxx.s"
	/usr/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Administrator/CLionProjects/project_1/lib/long_arithmetic.cxx -o CMakeFiles/lib.dir/lib/long_arithmetic.cxx.s

# Object files for target lib
lib_OBJECTS = \
"CMakeFiles/lib.dir/lib/long_arithmetic.cxx.o"

# External object files for target lib
lib_EXTERNAL_OBJECTS =

liblib.a: CMakeFiles/lib.dir/lib/long_arithmetic.cxx.o
liblib.a: CMakeFiles/lib.dir/build.make
liblib.a: CMakeFiles/lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/c/Users/Administrator/CLionProjects/project_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lib.dir/build: liblib.a
.PHONY : CMakeFiles/lib.dir/build

CMakeFiles/lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lib.dir/clean

CMakeFiles/lib.dir/depend:
	cd /mnt/c/Users/Administrator/CLionProjects/project_1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Administrator/CLionProjects/project_1 /mnt/c/Users/Administrator/CLionProjects/project_1 /mnt/c/Users/Administrator/CLionProjects/project_1/cmake-build-debug /mnt/c/Users/Administrator/CLionProjects/project_1/cmake-build-debug /mnt/c/Users/Administrator/CLionProjects/project_1/cmake-build-debug/CMakeFiles/lib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/lib.dir/depend

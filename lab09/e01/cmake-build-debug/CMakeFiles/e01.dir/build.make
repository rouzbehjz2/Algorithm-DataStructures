# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.1.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.1.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/e01.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/e01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/e01.dir/flags.make

CMakeFiles/e01.dir/maze.c.obj: CMakeFiles/e01.dir/flags.make
CMakeFiles/e01.dir/maze.c.obj: ../maze.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/e01.dir/maze.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\e01.dir\maze.c.obj   -c "D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01\maze.c"

CMakeFiles/e01.dir/maze.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/e01.dir/maze.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01\maze.c" > CMakeFiles\e01.dir\maze.c.i

CMakeFiles/e01.dir/maze.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/e01.dir/maze.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01\maze.c" -o CMakeFiles\e01.dir\maze.c.s

# Object files for target e01
e01_OBJECTS = \
"CMakeFiles/e01.dir/maze.c.obj"

# External object files for target e01
e01_EXTERNAL_OBJECTS =

e01.exe: CMakeFiles/e01.dir/maze.c.obj
e01.exe: CMakeFiles/e01.dir/build.make
e01.exe: CMakeFiles/e01.dir/linklibs.rsp
e01.exe: CMakeFiles/e01.dir/objects1.rsp
e01.exe: CMakeFiles/e01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable e01.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\e01.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/e01.dir/build: e01.exe

.PHONY : CMakeFiles/e01.dir/build

CMakeFiles/e01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\e01.dir\cmake_clean.cmake
.PHONY : CMakeFiles/e01.dir/clean

CMakeFiles/e01.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01" "D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01" "D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01\cmake-build-debug" "D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01\cmake-build-debug" "D:\Lessons\Polito\Second Year\Algorithms and Programing\Labs and Solutions quer\laib\soluzioni\lab09\e01\cmake-build-debug\CMakeFiles\e01.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/e01.dir/depend


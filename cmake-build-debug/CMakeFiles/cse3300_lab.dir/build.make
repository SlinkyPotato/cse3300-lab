# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = "C:\Development\JetBrains\CLion 2016.3.5\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Development\JetBrains\CLion 2016.3.5\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = P:\Projects\cse3300-lab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = P:\Projects\cse3300-lab\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cse3300_lab.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cse3300_lab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cse3300_lab.dir/flags.make

CMakeFiles/cse3300_lab.dir/student.c.obj: CMakeFiles/cse3300_lab.dir/flags.make
CMakeFiles/cse3300_lab.dir/student.c.obj: ../student.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=P:\Projects\cse3300-lab\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cse3300_lab.dir/student.c.obj"
	C:\Development\mingw-w64\mingw32\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\cse3300_lab.dir\student.c.obj   -c P:\Projects\cse3300-lab\student.c

CMakeFiles/cse3300_lab.dir/student.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cse3300_lab.dir/student.c.i"
	C:\Development\mingw-w64\mingw32\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E P:\Projects\cse3300-lab\student.c > CMakeFiles\cse3300_lab.dir\student.c.i

CMakeFiles/cse3300_lab.dir/student.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cse3300_lab.dir/student.c.s"
	C:\Development\mingw-w64\mingw32\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S P:\Projects\cse3300-lab\student.c -o CMakeFiles\cse3300_lab.dir\student.c.s

CMakeFiles/cse3300_lab.dir/student.c.obj.requires:

.PHONY : CMakeFiles/cse3300_lab.dir/student.c.obj.requires

CMakeFiles/cse3300_lab.dir/student.c.obj.provides: CMakeFiles/cse3300_lab.dir/student.c.obj.requires
	$(MAKE) -f CMakeFiles\cse3300_lab.dir\build.make CMakeFiles/cse3300_lab.dir/student.c.obj.provides.build
.PHONY : CMakeFiles/cse3300_lab.dir/student.c.obj.provides

CMakeFiles/cse3300_lab.dir/student.c.obj.provides.build: CMakeFiles/cse3300_lab.dir/student.c.obj


# Object files for target cse3300_lab
cse3300_lab_OBJECTS = \
"CMakeFiles/cse3300_lab.dir/student.c.obj"

# External object files for target cse3300_lab
cse3300_lab_EXTERNAL_OBJECTS =

cse3300_lab.exe: CMakeFiles/cse3300_lab.dir/student.c.obj
cse3300_lab.exe: CMakeFiles/cse3300_lab.dir/build.make
cse3300_lab.exe: CMakeFiles/cse3300_lab.dir/linklibs.rsp
cse3300_lab.exe: CMakeFiles/cse3300_lab.dir/objects1.rsp
cse3300_lab.exe: CMakeFiles/cse3300_lab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=P:\Projects\cse3300-lab\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cse3300_lab.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cse3300_lab.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cse3300_lab.dir/build: cse3300_lab.exe

.PHONY : CMakeFiles/cse3300_lab.dir/build

CMakeFiles/cse3300_lab.dir/requires: CMakeFiles/cse3300_lab.dir/student.c.obj.requires

.PHONY : CMakeFiles/cse3300_lab.dir/requires

CMakeFiles/cse3300_lab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cse3300_lab.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cse3300_lab.dir/clean

CMakeFiles/cse3300_lab.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" P:\Projects\cse3300-lab P:\Projects\cse3300-lab P:\Projects\cse3300-lab\cmake-build-debug P:\Projects\cse3300-lab\cmake-build-debug P:\Projects\cse3300-lab\cmake-build-debug\CMakeFiles\cse3300_lab.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cse3300_lab.dir/depend

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/car/4WD-CAR-ROMA/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/car/4WD-CAR-ROMA/build

# Utility rule file for sbus_serial_genpy.

# Include the progress variables for this target.
include sbus_serial/CMakeFiles/sbus_serial_genpy.dir/progress.make

sbus_serial_genpy: sbus_serial/CMakeFiles/sbus_serial_genpy.dir/build.make

.PHONY : sbus_serial_genpy

# Rule to build all files generated by this target.
sbus_serial/CMakeFiles/sbus_serial_genpy.dir/build: sbus_serial_genpy

.PHONY : sbus_serial/CMakeFiles/sbus_serial_genpy.dir/build

sbus_serial/CMakeFiles/sbus_serial_genpy.dir/clean:
	cd /home/car/4WD-CAR-ROMA/build/sbus_serial && $(CMAKE_COMMAND) -P CMakeFiles/sbus_serial_genpy.dir/cmake_clean.cmake
.PHONY : sbus_serial/CMakeFiles/sbus_serial_genpy.dir/clean

sbus_serial/CMakeFiles/sbus_serial_genpy.dir/depend:
	cd /home/car/4WD-CAR-ROMA/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/car/4WD-CAR-ROMA/src /home/car/4WD-CAR-ROMA/src/sbus_serial /home/car/4WD-CAR-ROMA/build /home/car/4WD-CAR-ROMA/build/sbus_serial /home/car/4WD-CAR-ROMA/build/sbus_serial/CMakeFiles/sbus_serial_genpy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sbus_serial/CMakeFiles/sbus_serial_genpy.dir/depend

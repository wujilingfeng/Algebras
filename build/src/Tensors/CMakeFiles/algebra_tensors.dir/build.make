# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/libo/Documents/c++/tensor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/libo/Documents/c++/tensor/build

# Include any dependencies generated for this target.
include src/Tensors/CMakeFiles/algebra_tensors.dir/depend.make

# Include the progress variables for this target.
include src/Tensors/CMakeFiles/algebra_tensors.dir/progress.make

# Include the compile flags for this target's objects.
include src/Tensors/CMakeFiles/algebra_tensors.dir/flags.make

src/Tensors/CMakeFiles/algebra_tensors.dir/Al_Tensors.c.o: src/Tensors/CMakeFiles/algebra_tensors.dir/flags.make
src/Tensors/CMakeFiles/algebra_tensors.dir/Al_Tensors.c.o: ../src/Tensors/Al_Tensors.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/libo/Documents/c++/tensor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/Tensors/CMakeFiles/algebra_tensors.dir/Al_Tensors.c.o"
	cd /home/libo/Documents/c++/tensor/build/src/Tensors && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/algebra_tensors.dir/Al_Tensors.c.o   -c /home/libo/Documents/c++/tensor/src/Tensors/Al_Tensors.c

src/Tensors/CMakeFiles/algebra_tensors.dir/Al_Tensors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/algebra_tensors.dir/Al_Tensors.c.i"
	cd /home/libo/Documents/c++/tensor/build/src/Tensors && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/libo/Documents/c++/tensor/src/Tensors/Al_Tensors.c > CMakeFiles/algebra_tensors.dir/Al_Tensors.c.i

src/Tensors/CMakeFiles/algebra_tensors.dir/Al_Tensors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/algebra_tensors.dir/Al_Tensors.c.s"
	cd /home/libo/Documents/c++/tensor/build/src/Tensors && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/libo/Documents/c++/tensor/src/Tensors/Al_Tensors.c -o CMakeFiles/algebra_tensors.dir/Al_Tensors.c.s

# Object files for target algebra_tensors
algebra_tensors_OBJECTS = \
"CMakeFiles/algebra_tensors.dir/Al_Tensors.c.o"

# External object files for target algebra_tensors
algebra_tensors_EXTERNAL_OBJECTS =

../temp_libs/libalgebra_tensors.a: src/Tensors/CMakeFiles/algebra_tensors.dir/Al_Tensors.c.o
../temp_libs/libalgebra_tensors.a: src/Tensors/CMakeFiles/algebra_tensors.dir/build.make
../temp_libs/libalgebra_tensors.a: src/Tensors/CMakeFiles/algebra_tensors.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/libo/Documents/c++/tensor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library ../../../temp_libs/libalgebra_tensors.a"
	cd /home/libo/Documents/c++/tensor/build/src/Tensors && $(CMAKE_COMMAND) -P CMakeFiles/algebra_tensors.dir/cmake_clean_target.cmake
	cd /home/libo/Documents/c++/tensor/build/src/Tensors && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/algebra_tensors.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Tensors/CMakeFiles/algebra_tensors.dir/build: ../temp_libs/libalgebra_tensors.a

.PHONY : src/Tensors/CMakeFiles/algebra_tensors.dir/build

src/Tensors/CMakeFiles/algebra_tensors.dir/clean:
	cd /home/libo/Documents/c++/tensor/build/src/Tensors && $(CMAKE_COMMAND) -P CMakeFiles/algebra_tensors.dir/cmake_clean.cmake
.PHONY : src/Tensors/CMakeFiles/algebra_tensors.dir/clean

src/Tensors/CMakeFiles/algebra_tensors.dir/depend:
	cd /home/libo/Documents/c++/tensor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/libo/Documents/c++/tensor /home/libo/Documents/c++/tensor/src/Tensors /home/libo/Documents/c++/tensor/build /home/libo/Documents/c++/tensor/build/src/Tensors /home/libo/Documents/c++/tensor/build/src/Tensors/CMakeFiles/algebra_tensors.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Tensors/CMakeFiles/algebra_tensors.dir/depend


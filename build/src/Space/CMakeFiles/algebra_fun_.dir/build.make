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
include src/Space/CMakeFiles/algebra_fun_.dir/depend.make

# Include the progress variables for this target.
include src/Space/CMakeFiles/algebra_fun_.dir/progress.make

# Include the compile flags for this target's objects.
include src/Space/CMakeFiles/algebra_fun_.dir/flags.make

src/Space/CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.o: src/Space/CMakeFiles/algebra_fun_.dir/flags.make
src/Space/CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.o: ../src/Space/Algebra_Fun_.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/libo/Documents/c++/tensor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/Space/CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.o"
	cd /home/libo/Documents/c++/tensor/build/src/Space && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.o   -c /home/libo/Documents/c++/tensor/src/Space/Algebra_Fun_.c

src/Space/CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.i"
	cd /home/libo/Documents/c++/tensor/build/src/Space && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/libo/Documents/c++/tensor/src/Space/Algebra_Fun_.c > CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.i

src/Space/CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.s"
	cd /home/libo/Documents/c++/tensor/build/src/Space && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/libo/Documents/c++/tensor/src/Space/Algebra_Fun_.c -o CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.s

src/Space/CMakeFiles/algebra_fun_.dir/structures.c.o: src/Space/CMakeFiles/algebra_fun_.dir/flags.make
src/Space/CMakeFiles/algebra_fun_.dir/structures.c.o: ../src/Space/structures.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/libo/Documents/c++/tensor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/Space/CMakeFiles/algebra_fun_.dir/structures.c.o"
	cd /home/libo/Documents/c++/tensor/build/src/Space && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/algebra_fun_.dir/structures.c.o   -c /home/libo/Documents/c++/tensor/src/Space/structures.c

src/Space/CMakeFiles/algebra_fun_.dir/structures.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/algebra_fun_.dir/structures.c.i"
	cd /home/libo/Documents/c++/tensor/build/src/Space && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/libo/Documents/c++/tensor/src/Space/structures.c > CMakeFiles/algebra_fun_.dir/structures.c.i

src/Space/CMakeFiles/algebra_fun_.dir/structures.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/algebra_fun_.dir/structures.c.s"
	cd /home/libo/Documents/c++/tensor/build/src/Space && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/libo/Documents/c++/tensor/src/Space/structures.c -o CMakeFiles/algebra_fun_.dir/structures.c.s

# Object files for target algebra_fun_
algebra_fun__OBJECTS = \
"CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.o" \
"CMakeFiles/algebra_fun_.dir/structures.c.o"

# External object files for target algebra_fun_
algebra_fun__EXTERNAL_OBJECTS =

../temp_libs/libalgebra_fun_.a: src/Space/CMakeFiles/algebra_fun_.dir/Algebra_Fun_.c.o
../temp_libs/libalgebra_fun_.a: src/Space/CMakeFiles/algebra_fun_.dir/structures.c.o
../temp_libs/libalgebra_fun_.a: src/Space/CMakeFiles/algebra_fun_.dir/build.make
../temp_libs/libalgebra_fun_.a: src/Space/CMakeFiles/algebra_fun_.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/libo/Documents/c++/tensor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library ../../../temp_libs/libalgebra_fun_.a"
	cd /home/libo/Documents/c++/tensor/build/src/Space && $(CMAKE_COMMAND) -P CMakeFiles/algebra_fun_.dir/cmake_clean_target.cmake
	cd /home/libo/Documents/c++/tensor/build/src/Space && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/algebra_fun_.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Space/CMakeFiles/algebra_fun_.dir/build: ../temp_libs/libalgebra_fun_.a

.PHONY : src/Space/CMakeFiles/algebra_fun_.dir/build

src/Space/CMakeFiles/algebra_fun_.dir/clean:
	cd /home/libo/Documents/c++/tensor/build/src/Space && $(CMAKE_COMMAND) -P CMakeFiles/algebra_fun_.dir/cmake_clean.cmake
.PHONY : src/Space/CMakeFiles/algebra_fun_.dir/clean

src/Space/CMakeFiles/algebra_fun_.dir/depend:
	cd /home/libo/Documents/c++/tensor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/libo/Documents/c++/tensor /home/libo/Documents/c++/tensor/src/Space /home/libo/Documents/c++/tensor/build /home/libo/Documents/c++/tensor/build/src/Space /home/libo/Documents/c++/tensor/build/src/Space/CMakeFiles/algebra_fun_.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Space/CMakeFiles/algebra_fun_.dir/depend


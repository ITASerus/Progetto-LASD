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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Exercise0A.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Exercise0A.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Exercise0A.dir/flags.make

CMakeFiles/Exercise0A.dir/queue/queue.c.o: CMakeFiles/Exercise0A.dir/flags.make
CMakeFiles/Exercise0A.dir/queue/queue.c.o: ../queue/queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Exercise0A.dir/queue/queue.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise0A.dir/queue/queue.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/queue/queue.c

CMakeFiles/Exercise0A.dir/queue/queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise0A.dir/queue/queue.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/queue/queue.c > CMakeFiles/Exercise0A.dir/queue/queue.c.i

CMakeFiles/Exercise0A.dir/queue/queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise0A.dir/queue/queue.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/queue/queue.c -o CMakeFiles/Exercise0A.dir/queue/queue.c.s

CMakeFiles/Exercise0A.dir/stack/stack.c.o: CMakeFiles/Exercise0A.dir/flags.make
CMakeFiles/Exercise0A.dir/stack/stack.c.o: ../stack/stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Exercise0A.dir/stack/stack.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise0A.dir/stack/stack.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/stack/stack.c

CMakeFiles/Exercise0A.dir/stack/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise0A.dir/stack/stack.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/stack/stack.c > CMakeFiles/Exercise0A.dir/stack/stack.c.i

CMakeFiles/Exercise0A.dir/stack/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise0A.dir/stack/stack.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/stack/stack.c -o CMakeFiles/Exercise0A.dir/stack/stack.c.s

CMakeFiles/Exercise0A.dir/main.c.o: CMakeFiles/Exercise0A.dir/flags.make
CMakeFiles/Exercise0A.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Exercise0A.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise0A.dir/main.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/main.c

CMakeFiles/Exercise0A.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise0A.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/main.c > CMakeFiles/Exercise0A.dir/main.c.i

CMakeFiles/Exercise0A.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise0A.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/main.c -o CMakeFiles/Exercise0A.dir/main.c.s

CMakeFiles/Exercise0A.dir/utility.c.o: CMakeFiles/Exercise0A.dir/flags.make
CMakeFiles/Exercise0A.dir/utility.c.o: ../utility.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Exercise0A.dir/utility.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise0A.dir/utility.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/utility.c

CMakeFiles/Exercise0A.dir/utility.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise0A.dir/utility.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/utility.c > CMakeFiles/Exercise0A.dir/utility.c.i

CMakeFiles/Exercise0A.dir/utility.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise0A.dir/utility.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/utility.c -o CMakeFiles/Exercise0A.dir/utility.c.s

# Object files for target Exercise0A
Exercise0A_OBJECTS = \
"CMakeFiles/Exercise0A.dir/queue/queue.c.o" \
"CMakeFiles/Exercise0A.dir/stack/stack.c.o" \
"CMakeFiles/Exercise0A.dir/main.c.o" \
"CMakeFiles/Exercise0A.dir/utility.c.o"

# External object files for target Exercise0A
Exercise0A_EXTERNAL_OBJECTS =

Exercise0A: CMakeFiles/Exercise0A.dir/queue/queue.c.o
Exercise0A: CMakeFiles/Exercise0A.dir/stack/stack.c.o
Exercise0A: CMakeFiles/Exercise0A.dir/main.c.o
Exercise0A: CMakeFiles/Exercise0A.dir/utility.c.o
Exercise0A: CMakeFiles/Exercise0A.dir/build.make
Exercise0A: CMakeFiles/Exercise0A.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable Exercise0A"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Exercise0A.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Exercise0A.dir/build: Exercise0A

.PHONY : CMakeFiles/Exercise0A.dir/build

CMakeFiles/Exercise0A.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Exercise0A.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Exercise0A.dir/clean

CMakeFiles/Exercise0A.dir/depend:
	cd /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/cmake-build-debug /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/cmake-build-debug /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise0A/cmake-build-debug/CMakeFiles/Exercise0A.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Exercise0A.dir/depend


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
CMAKE_SOURCE_DIR = /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Exercise2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Exercise2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Exercise2.dir/flags.make

CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.o: ../adt/flt/adtflt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/flt/adtflt.c

CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/flt/adtflt.c > CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.i

CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/flt/adtflt.c -o CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.s

CMakeFiles/Exercise2.dir/adt/int/adtint.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/adt/int/adtint.c.o: ../adt/int/adtint.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Exercise2.dir/adt/int/adtint.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/adt/int/adtint.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/int/adtint.c

CMakeFiles/Exercise2.dir/adt/int/adtint.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/adt/int/adtint.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/int/adtint.c > CMakeFiles/Exercise2.dir/adt/int/adtint.c.i

CMakeFiles/Exercise2.dir/adt/int/adtint.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/adt/int/adtint.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/int/adtint.c -o CMakeFiles/Exercise2.dir/adt/int/adtint.c.s

CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.o: ../adt/rec/adtrec.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/rec/adtrec.c

CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/rec/adtrec.c > CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.i

CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/rec/adtrec.c -o CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.s

CMakeFiles/Exercise2.dir/adt/str/adtstr.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/adt/str/adtstr.c.o: ../adt/str/adtstr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Exercise2.dir/adt/str/adtstr.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/adt/str/adtstr.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/str/adtstr.c

CMakeFiles/Exercise2.dir/adt/str/adtstr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/adt/str/adtstr.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/str/adtstr.c > CMakeFiles/Exercise2.dir/adt/str/adtstr.c.i

CMakeFiles/Exercise2.dir/adt/str/adtstr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/adt/str/adtstr.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/str/adtstr.c -o CMakeFiles/Exercise2.dir/adt/str/adtstr.c.s

CMakeFiles/Exercise2.dir/adt/adt.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/adt/adt.c.o: ../adt/adt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Exercise2.dir/adt/adt.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/adt/adt.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/adt.c

CMakeFiles/Exercise2.dir/adt/adt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/adt/adt.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/adt.c > CMakeFiles/Exercise2.dir/adt/adt.c.i

CMakeFiles/Exercise2.dir/adt/adt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/adt/adt.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/adt/adt.c -o CMakeFiles/Exercise2.dir/adt/adt.c.s

CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.o: ../bst/itr/bstitr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/itr/bstitr.c

CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/itr/bstitr.c > CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.i

CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/itr/bstitr.c -o CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.s

CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.o: ../bst/rec/bstrec.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/rec/bstrec.c

CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/rec/bstrec.c > CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.i

CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/rec/bstrec.c -o CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.s

CMakeFiles/Exercise2.dir/bst/bst.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/bst/bst.c.o: ../bst/bst.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/Exercise2.dir/bst/bst.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/bst/bst.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bst.c

CMakeFiles/Exercise2.dir/bst/bst.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/bst/bst.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bst.c > CMakeFiles/Exercise2.dir/bst/bst.c.i

CMakeFiles/Exercise2.dir/bst/bst.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/bst/bst.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bst.c -o CMakeFiles/Exercise2.dir/bst/bst.c.s

CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.o: ../bst/bstitrbreadth.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrbreadth.c

CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrbreadth.c > CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.i

CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrbreadth.c -o CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.s

CMakeFiles/Exercise2.dir/bst/bstitrinord.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/bst/bstitrinord.c.o: ../bst/bstitrinord.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/Exercise2.dir/bst/bstitrinord.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/bst/bstitrinord.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrinord.c

CMakeFiles/Exercise2.dir/bst/bstitrinord.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/bst/bstitrinord.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrinord.c > CMakeFiles/Exercise2.dir/bst/bstitrinord.c.i

CMakeFiles/Exercise2.dir/bst/bstitrinord.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/bst/bstitrinord.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrinord.c -o CMakeFiles/Exercise2.dir/bst/bstitrinord.c.s

CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.o: ../bst/bstitrpostord.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrpostord.c

CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrpostord.c > CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.i

CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrpostord.c -o CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.s

CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.o: ../bst/bstitrpreord.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrpreord.c

CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrpreord.c > CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.i

CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/bst/bstitrpreord.c -o CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.s

CMakeFiles/Exercise2.dir/itr/itr.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/itr/itr.c.o: ../itr/itr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/Exercise2.dir/itr/itr.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/itr/itr.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/itr/itr.c

CMakeFiles/Exercise2.dir/itr/itr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/itr/itr.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/itr/itr.c > CMakeFiles/Exercise2.dir/itr/itr.c.i

CMakeFiles/Exercise2.dir/itr/itr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/itr/itr.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/itr/itr.c -o CMakeFiles/Exercise2.dir/itr/itr.c.s

CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.o: ../queue/lst/queuelst.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/queue/lst/queuelst.c

CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/queue/lst/queuelst.c > CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.i

CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/queue/lst/queuelst.c -o CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.s

CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.o: ../queue/vec/queuevec.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/queue/vec/queuevec.c

CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/queue/vec/queuevec.c > CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.i

CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/queue/vec/queuevec.c -o CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.s

CMakeFiles/Exercise2.dir/queue/queue.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/queue/queue.c.o: ../queue/queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building C object CMakeFiles/Exercise2.dir/queue/queue.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/queue/queue.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/queue/queue.c

CMakeFiles/Exercise2.dir/queue/queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/queue/queue.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/queue/queue.c > CMakeFiles/Exercise2.dir/queue/queue.c.i

CMakeFiles/Exercise2.dir/queue/queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/queue/queue.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/queue/queue.c -o CMakeFiles/Exercise2.dir/queue/queue.c.s

CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.o: ../stack/lst/stacklst.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building C object CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/stack/lst/stacklst.c

CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/stack/lst/stacklst.c > CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.i

CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/stack/lst/stacklst.c -o CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.s

CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.o: ../stack/vec/stackvec.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building C object CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/stack/vec/stackvec.c

CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/stack/vec/stackvec.c > CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.i

CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/stack/vec/stackvec.c -o CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.s

CMakeFiles/Exercise2.dir/stack/stack.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/stack/stack.c.o: ../stack/stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building C object CMakeFiles/Exercise2.dir/stack/stack.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/stack/stack.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/stack/stack.c

CMakeFiles/Exercise2.dir/stack/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/stack/stack.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/stack/stack.c > CMakeFiles/Exercise2.dir/stack/stack.c.i

CMakeFiles/Exercise2.dir/stack/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/stack/stack.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/stack/stack.c -o CMakeFiles/Exercise2.dir/stack/stack.c.s

CMakeFiles/Exercise2.dir/main.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Building C object CMakeFiles/Exercise2.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/main.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/main.c

CMakeFiles/Exercise2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/main.c > CMakeFiles/Exercise2.dir/main.c.i

CMakeFiles/Exercise2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/main.c -o CMakeFiles/Exercise2.dir/main.c.s

CMakeFiles/Exercise2.dir/utility.c.o: CMakeFiles/Exercise2.dir/flags.make
CMakeFiles/Exercise2.dir/utility.c.o: ../utility.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_21) "Building C object CMakeFiles/Exercise2.dir/utility.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercise2.dir/utility.c.o   -c /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/utility.c

CMakeFiles/Exercise2.dir/utility.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercise2.dir/utility.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/utility.c > CMakeFiles/Exercise2.dir/utility.c.i

CMakeFiles/Exercise2.dir/utility.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercise2.dir/utility.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/utility.c -o CMakeFiles/Exercise2.dir/utility.c.s

# Object files for target Exercise2
Exercise2_OBJECTS = \
"CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.o" \
"CMakeFiles/Exercise2.dir/adt/int/adtint.c.o" \
"CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.o" \
"CMakeFiles/Exercise2.dir/adt/str/adtstr.c.o" \
"CMakeFiles/Exercise2.dir/adt/adt.c.o" \
"CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.o" \
"CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.o" \
"CMakeFiles/Exercise2.dir/bst/bst.c.o" \
"CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.o" \
"CMakeFiles/Exercise2.dir/bst/bstitrinord.c.o" \
"CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.o" \
"CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.o" \
"CMakeFiles/Exercise2.dir/itr/itr.c.o" \
"CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.o" \
"CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.o" \
"CMakeFiles/Exercise2.dir/queue/queue.c.o" \
"CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.o" \
"CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.o" \
"CMakeFiles/Exercise2.dir/stack/stack.c.o" \
"CMakeFiles/Exercise2.dir/main.c.o" \
"CMakeFiles/Exercise2.dir/utility.c.o"

# External object files for target Exercise2
Exercise2_EXTERNAL_OBJECTS =

Exercise2: CMakeFiles/Exercise2.dir/adt/flt/adtflt.c.o
Exercise2: CMakeFiles/Exercise2.dir/adt/int/adtint.c.o
Exercise2: CMakeFiles/Exercise2.dir/adt/rec/adtrec.c.o
Exercise2: CMakeFiles/Exercise2.dir/adt/str/adtstr.c.o
Exercise2: CMakeFiles/Exercise2.dir/adt/adt.c.o
Exercise2: CMakeFiles/Exercise2.dir/bst/itr/bstitr.c.o
Exercise2: CMakeFiles/Exercise2.dir/bst/rec/bstrec.c.o
Exercise2: CMakeFiles/Exercise2.dir/bst/bst.c.o
Exercise2: CMakeFiles/Exercise2.dir/bst/bstitrbreadth.c.o
Exercise2: CMakeFiles/Exercise2.dir/bst/bstitrinord.c.o
Exercise2: CMakeFiles/Exercise2.dir/bst/bstitrpostord.c.o
Exercise2: CMakeFiles/Exercise2.dir/bst/bstitrpreord.c.o
Exercise2: CMakeFiles/Exercise2.dir/itr/itr.c.o
Exercise2: CMakeFiles/Exercise2.dir/queue/lst/queuelst.c.o
Exercise2: CMakeFiles/Exercise2.dir/queue/vec/queuevec.c.o
Exercise2: CMakeFiles/Exercise2.dir/queue/queue.c.o
Exercise2: CMakeFiles/Exercise2.dir/stack/lst/stacklst.c.o
Exercise2: CMakeFiles/Exercise2.dir/stack/vec/stackvec.c.o
Exercise2: CMakeFiles/Exercise2.dir/stack/stack.c.o
Exercise2: CMakeFiles/Exercise2.dir/main.c.o
Exercise2: CMakeFiles/Exercise2.dir/utility.c.o
Exercise2: CMakeFiles/Exercise2.dir/build.make
Exercise2: CMakeFiles/Exercise2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_22) "Linking C executable Exercise2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Exercise2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Exercise2.dir/build: Exercise2

.PHONY : CMakeFiles/Exercise2.dir/build

CMakeFiles/Exercise2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Exercise2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Exercise2.dir/clean

CMakeFiles/Exercise2.dir/depend:
	cd /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2 /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2 /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug /Users/ernestodecrecchio/Documents/GitHub/Progetto-LASD/Exercise2/cmake-build-debug/CMakeFiles/Exercise2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Exercise2.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\deofr\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\212.5457.51\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\deofr\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\212.5457.51\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\deofr\C++\ProgLab-2-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\deofr\C++\ProgLab-2-1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ProgLab_2_1.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/ProgLab_2_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProgLab_2_1.dir/flags.make

CMakeFiles/ProgLab_2_1.dir/main.cpp.obj: CMakeFiles/ProgLab_2_1.dir/flags.make
CMakeFiles/ProgLab_2_1.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\deofr\C++\ProgLab-2-1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ProgLab_2_1.dir/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ProgLab_2_1.dir\main.cpp.obj -c C:\Users\deofr\C++\ProgLab-2-1\main.cpp

CMakeFiles/ProgLab_2_1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProgLab_2_1.dir/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\deofr\C++\ProgLab-2-1\main.cpp > CMakeFiles\ProgLab_2_1.dir\main.cpp.i

CMakeFiles/ProgLab_2_1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProgLab_2_1.dir/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\deofr\C++\ProgLab-2-1\main.cpp -o CMakeFiles\ProgLab_2_1.dir\main.cpp.s

# Object files for target ProgLab_2_1
ProgLab_2_1_OBJECTS = \
"CMakeFiles/ProgLab_2_1.dir/main.cpp.obj"

# External object files for target ProgLab_2_1
ProgLab_2_1_EXTERNAL_OBJECTS =

ProgLab_2_1.exe: CMakeFiles/ProgLab_2_1.dir/main.cpp.obj
ProgLab_2_1.exe: CMakeFiles/ProgLab_2_1.dir/build.make
ProgLab_2_1.exe: CMakeFiles/ProgLab_2_1.dir/linklibs.rsp
ProgLab_2_1.exe: CMakeFiles/ProgLab_2_1.dir/objects1.rsp
ProgLab_2_1.exe: CMakeFiles/ProgLab_2_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\deofr\C++\ProgLab-2-1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ProgLab_2_1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ProgLab_2_1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProgLab_2_1.dir/build: ProgLab_2_1.exe
.PHONY : CMakeFiles/ProgLab_2_1.dir/build

CMakeFiles/ProgLab_2_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ProgLab_2_1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ProgLab_2_1.dir/clean

CMakeFiles/ProgLab_2_1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\deofr\C++\ProgLab-2-1 C:\Users\deofr\C++\ProgLab-2-1 C:\Users\deofr\C++\ProgLab-2-1\cmake-build-debug C:\Users\deofr\C++\ProgLab-2-1\cmake-build-debug C:\Users\deofr\C++\ProgLab-2-1\cmake-build-debug\CMakeFiles\ProgLab_2_1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProgLab_2_1.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/ynwad/workspace/sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ynwad/workspace/sylar

# Include any dependencies generated for this target.
include CMakeFiles/sylar.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sylar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sylar.dir/flags.make

CMakeFiles/sylar.dir/log.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/log.cc.o: log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ynwad/workspace/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sylar.dir/log.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/log.cc.o -c /home/ynwad/workspace/sylar/log.cc

CMakeFiles/sylar.dir/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ynwad/workspace/sylar/log.cc > CMakeFiles/sylar.dir/log.cc.i

CMakeFiles/sylar.dir/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ynwad/workspace/sylar/log.cc -o CMakeFiles/sylar.dir/log.cc.s

CMakeFiles/sylar.dir/utils.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/utils.cc.o: utils.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ynwad/workspace/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sylar.dir/utils.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/utils.cc.o -c /home/ynwad/workspace/sylar/utils.cc

CMakeFiles/sylar.dir/utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/utils.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ynwad/workspace/sylar/utils.cc > CMakeFiles/sylar.dir/utils.cc.i

CMakeFiles/sylar.dir/utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/utils.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ynwad/workspace/sylar/utils.cc -o CMakeFiles/sylar.dir/utils.cc.s

CMakeFiles/sylar.dir/thread.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/thread.cc.o: thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ynwad/workspace/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sylar.dir/thread.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/thread.cc.o -c /home/ynwad/workspace/sylar/thread.cc

CMakeFiles/sylar.dir/thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/thread.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ynwad/workspace/sylar/thread.cc > CMakeFiles/sylar.dir/thread.cc.i

CMakeFiles/sylar.dir/thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/thread.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ynwad/workspace/sylar/thread.cc -o CMakeFiles/sylar.dir/thread.cc.s

CMakeFiles/sylar.dir/mutex.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/mutex.cc.o: mutex.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ynwad/workspace/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sylar.dir/mutex.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/mutex.cc.o -c /home/ynwad/workspace/sylar/mutex.cc

CMakeFiles/sylar.dir/mutex.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/mutex.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ynwad/workspace/sylar/mutex.cc > CMakeFiles/sylar.dir/mutex.cc.i

CMakeFiles/sylar.dir/mutex.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/mutex.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ynwad/workspace/sylar/mutex.cc -o CMakeFiles/sylar.dir/mutex.cc.s

CMakeFiles/sylar.dir/config.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/config.cc.o: config.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ynwad/workspace/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/sylar.dir/config.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/config.cc.o -c /home/ynwad/workspace/sylar/config.cc

CMakeFiles/sylar.dir/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/config.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ynwad/workspace/sylar/config.cc > CMakeFiles/sylar.dir/config.cc.i

CMakeFiles/sylar.dir/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/config.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ynwad/workspace/sylar/config.cc -o CMakeFiles/sylar.dir/config.cc.s

# Object files for target sylar
sylar_OBJECTS = \
"CMakeFiles/sylar.dir/log.cc.o" \
"CMakeFiles/sylar.dir/utils.cc.o" \
"CMakeFiles/sylar.dir/thread.cc.o" \
"CMakeFiles/sylar.dir/mutex.cc.o" \
"CMakeFiles/sylar.dir/config.cc.o"

# External object files for target sylar
sylar_EXTERNAL_OBJECTS =

lib/libsylar.so: CMakeFiles/sylar.dir/log.cc.o
lib/libsylar.so: CMakeFiles/sylar.dir/utils.cc.o
lib/libsylar.so: CMakeFiles/sylar.dir/thread.cc.o
lib/libsylar.so: CMakeFiles/sylar.dir/mutex.cc.o
lib/libsylar.so: CMakeFiles/sylar.dir/config.cc.o
lib/libsylar.so: CMakeFiles/sylar.dir/build.make
lib/libsylar.so: CMakeFiles/sylar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ynwad/workspace/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX shared library lib/libsylar.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sylar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sylar.dir/build: lib/libsylar.so

.PHONY : CMakeFiles/sylar.dir/build

CMakeFiles/sylar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sylar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sylar.dir/clean

CMakeFiles/sylar.dir/depend:
	cd /home/ynwad/workspace/sylar && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ynwad/workspace/sylar /home/ynwad/workspace/sylar /home/ynwad/workspace/sylar /home/ynwad/workspace/sylar /home/ynwad/workspace/sylar/CMakeFiles/sylar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sylar.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /apps/sylar/bin/cmake

# The command to remove a file.
RM = /apps/sylar/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
<<<<<<< HEAD
CMAKE_SOURCE_DIR = /home/sylar/workspace/sylar/sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sylar/workspace/sylar/sylar

# Include any dependencies generated for this target.
include CMakeFiles/libsylar.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libsylar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libsylar.dir/flags.make

CMakeFiles/libsylar.dir/log.cc.o: CMakeFiles/libsylar.dir/flags.make
CMakeFiles/libsylar.dir/log.cc.o: log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sylar/workspace/sylar/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libsylar.dir/log.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libsylar.dir/log.cc.o -c /home/sylar/workspace/sylar/sylar/log.cc

CMakeFiles/libsylar.dir/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libsylar.dir/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sylar/workspace/sylar/sylar/log.cc > CMakeFiles/libsylar.dir/log.cc.i

CMakeFiles/libsylar.dir/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libsylar.dir/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sylar/workspace/sylar/sylar/log.cc -o CMakeFiles/libsylar.dir/log.cc.s

# Object files for target libsylar
libsylar_OBJECTS = \
"CMakeFiles/libsylar.dir/log.cc.o"

# External object files for target libsylar
libsylar_EXTERNAL_OBJECTS =

$(PROJECT_SOURCE_DIR)/lib/liblibsylar.so: CMakeFiles/libsylar.dir/log.cc.o
$(PROJECT_SOURCE_DIR)/lib/liblibsylar.so: CMakeFiles/libsylar.dir/build.make
$(PROJECT_SOURCE_DIR)/lib/liblibsylar.so: CMakeFiles/libsylar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sylar/workspace/sylar/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library \$$(PROJECT_SOURCE_DIR)/lib/liblibsylar.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libsylar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libsylar.dir/build: $(PROJECT_SOURCE_DIR)/lib/liblibsylar.so

.PHONY : CMakeFiles/libsylar.dir/build

CMakeFiles/libsylar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libsylar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libsylar.dir/clean

CMakeFiles/libsylar.dir/depend:
	cd /home/sylar/workspace/sylar/sylar && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sylar/workspace/sylar/sylar /home/sylar/workspace/sylar/sylar /home/sylar/workspace/sylar/sylar /home/sylar/workspace/sylar/sylar /home/sylar/workspace/sylar/sylar/CMakeFiles/libsylar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libsylar.dir/depend
=======
CMAKE_SOURCE_DIR = /home/ynwad/workspace/ynwad/ynwad

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ynwad/workspace/ynwad/ynwad

# Include any dependencies generated for this target.
include CMakeFiles/libynwad.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libynwad.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libynwad.dir/flags.make

CMakeFiles/libynwad.dir/log.cc.o: CMakeFiles/libynwad.dir/flags.make
CMakeFiles/libynwad.dir/log.cc.o: log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ynwad/workspace/ynwad/ynwad/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libynwad.dir/log.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libynwad.dir/log.cc.o -c /home/ynwad/workspace/ynwad/ynwad/log.cc

CMakeFiles/libynwad.dir/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libynwad.dir/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ynwad/workspace/ynwad/ynwad/log.cc > CMakeFiles/libynwad.dir/log.cc.i

CMakeFiles/libynwad.dir/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libynwad.dir/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ynwad/workspace/ynwad/ynwad/log.cc -o CMakeFiles/libynwad.dir/log.cc.s

# Object files for target libynwad
libynwad_OBJECTS = \
"CMakeFiles/libynwad.dir/log.cc.o"

# External object files for target libynwad
libynwad_EXTERNAL_OBJECTS =

$(PROJECT_SOURCE_DIR)/lib/liblibynwad.so: CMakeFiles/libynwad.dir/log.cc.o
$(PROJECT_SOURCE_DIR)/lib/liblibynwad.so: CMakeFiles/libynwad.dir/build.make
$(PROJECT_SOURCE_DIR)/lib/liblibynwad.so: CMakeFiles/libynwad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ynwad/workspace/ynwad/ynwad/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library \$$(PROJECT_SOURCE_DIR)/lib/liblibynwad.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libynwad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libynwad.dir/build: $(PROJECT_SOURCE_DIR)/lib/liblibynwad.so

.PHONY : CMakeFiles/libynwad.dir/build

CMakeFiles/libynwad.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libynwad.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libynwad.dir/clean

CMakeFiles/libynwad.dir/depend:
	cd /home/ynwad/workspace/ynwad/ynwad && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ynwad/workspace/ynwad/ynwad /home/ynwad/workspace/ynwad/ynwad /home/ynwad/workspace/ynwad/ynwad /home/ynwad/workspace/ynwad/ynwad /home/ynwad/workspace/ynwad/ynwad/CMakeFiles/libynwad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libynwad.dir/depend
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c


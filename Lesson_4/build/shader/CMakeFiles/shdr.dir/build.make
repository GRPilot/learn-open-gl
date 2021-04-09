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
CMAKE_SOURCE_DIR = /home/gollan/Programming/OpenGL/Ravesli/Lesson_4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build

# Include any dependencies generated for this target.
include shader/CMakeFiles/shdr.dir/depend.make

# Include the progress variables for this target.
include shader/CMakeFiles/shdr.dir/progress.make

# Include the compile flags for this target's objects.
include shader/CMakeFiles/shdr.dir/flags.make

shader/CMakeFiles/shdr.dir/shader.cpp.o: shader/CMakeFiles/shdr.dir/flags.make
shader/CMakeFiles/shdr.dir/shader.cpp.o: ../shader/shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object shader/CMakeFiles/shdr.dir/shader.cpp.o"
	cd /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build/shader && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shdr.dir/shader.cpp.o -c /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/shader/shader.cpp

shader/CMakeFiles/shdr.dir/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shdr.dir/shader.cpp.i"
	cd /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build/shader && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/shader/shader.cpp > CMakeFiles/shdr.dir/shader.cpp.i

shader/CMakeFiles/shdr.dir/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shdr.dir/shader.cpp.s"
	cd /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build/shader && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/shader/shader.cpp -o CMakeFiles/shdr.dir/shader.cpp.s

# Object files for target shdr
shdr_OBJECTS = \
"CMakeFiles/shdr.dir/shader.cpp.o"

# External object files for target shdr
shdr_EXTERNAL_OBJECTS =

shader/libshdr.a: shader/CMakeFiles/shdr.dir/shader.cpp.o
shader/libshdr.a: shader/CMakeFiles/shdr.dir/build.make
shader/libshdr.a: shader/CMakeFiles/shdr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libshdr.a"
	cd /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build/shader && $(CMAKE_COMMAND) -P CMakeFiles/shdr.dir/cmake_clean_target.cmake
	cd /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build/shader && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shdr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
shader/CMakeFiles/shdr.dir/build: shader/libshdr.a

.PHONY : shader/CMakeFiles/shdr.dir/build

shader/CMakeFiles/shdr.dir/clean:
	cd /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build/shader && $(CMAKE_COMMAND) -P CMakeFiles/shdr.dir/cmake_clean.cmake
.PHONY : shader/CMakeFiles/shdr.dir/clean

shader/CMakeFiles/shdr.dir/depend:
	cd /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gollan/Programming/OpenGL/Ravesli/Lesson_4 /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/shader /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build/shader /home/gollan/Programming/OpenGL/Ravesli/Lesson_4/build/shader/CMakeFiles/shdr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : shader/CMakeFiles/shdr.dir/depend


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
CMAKE_COMMAND = /snap/clion/82/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/82/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SyncPerformanceTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SyncPerformanceTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SyncPerformanceTest.dir/flags.make

CMakeFiles/SyncPerformanceTest.dir/main.cpp.o: CMakeFiles/SyncPerformanceTest.dir/flags.make
CMakeFiles/SyncPerformanceTest.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SyncPerformanceTest.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SyncPerformanceTest.dir/main.cpp.o -c /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/main.cpp

CMakeFiles/SyncPerformanceTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SyncPerformanceTest.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/main.cpp > CMakeFiles/SyncPerformanceTest.dir/main.cpp.i

CMakeFiles/SyncPerformanceTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SyncPerformanceTest.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/main.cpp -o CMakeFiles/SyncPerformanceTest.dir/main.cpp.s

CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.o: CMakeFiles/SyncPerformanceTest.dir/flags.make
CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.o: ../TestTime.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.o -c /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/TestTime.cpp

CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/TestTime.cpp > CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.i

CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/TestTime.cpp -o CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.s

CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.o: CMakeFiles/SyncPerformanceTest.dir/flags.make
CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.o: ../BenchmarkTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.o -c /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/BenchmarkTest.cpp

CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/BenchmarkTest.cpp > CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.i

CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/BenchmarkTest.cpp -o CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.s

CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.o: CMakeFiles/SyncPerformanceTest.dir/flags.make
CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.o: ../PerformanceMonitor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.o -c /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/PerformanceMonitor.cpp

CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/PerformanceMonitor.cpp > CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.i

CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/PerformanceMonitor.cpp -o CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.s

CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.o: CMakeFiles/SyncPerformanceTest.dir/flags.make
CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.o: ../Listener.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.o -c /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/Listener.cpp

CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/Listener.cpp > CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.i

CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/Listener.cpp -o CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.s

CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.o: CMakeFiles/SyncPerformanceTest.dir/flags.make
CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.o: ../ListenerImpl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.o -c /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/ListenerImpl.cpp

CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/ListenerImpl.cpp > CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.i

CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/ListenerImpl.cpp -o CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.s

# Object files for target SyncPerformanceTest
SyncPerformanceTest_OBJECTS = \
"CMakeFiles/SyncPerformanceTest.dir/main.cpp.o" \
"CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.o" \
"CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.o" \
"CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.o" \
"CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.o" \
"CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.o"

# External object files for target SyncPerformanceTest
SyncPerformanceTest_EXTERNAL_OBJECTS =

SyncPerformanceTest: CMakeFiles/SyncPerformanceTest.dir/main.cpp.o
SyncPerformanceTest: CMakeFiles/SyncPerformanceTest.dir/TestTime.cpp.o
SyncPerformanceTest: CMakeFiles/SyncPerformanceTest.dir/BenchmarkTest.cpp.o
SyncPerformanceTest: CMakeFiles/SyncPerformanceTest.dir/PerformanceMonitor.cpp.o
SyncPerformanceTest: CMakeFiles/SyncPerformanceTest.dir/Listener.cpp.o
SyncPerformanceTest: CMakeFiles/SyncPerformanceTest.dir/ListenerImpl.cpp.o
SyncPerformanceTest: CMakeFiles/SyncPerformanceTest.dir/build.make
SyncPerformanceTest: CMakeFiles/SyncPerformanceTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable SyncPerformanceTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SyncPerformanceTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SyncPerformanceTest.dir/build: SyncPerformanceTest

.PHONY : CMakeFiles/SyncPerformanceTest.dir/build

CMakeFiles/SyncPerformanceTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SyncPerformanceTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SyncPerformanceTest.dir/clean

CMakeFiles/SyncPerformanceTest.dir/depend:
	cd /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug /home/braveen79/Desktop/Benchmark/Sync/PassthroughBenchmark/cmake-build-debug/CMakeFiles/SyncPerformanceTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SyncPerformanceTest.dir/depend


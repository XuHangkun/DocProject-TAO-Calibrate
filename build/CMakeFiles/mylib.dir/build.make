# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/Cmake/3.17.0/bin/cmake

# The command to remove a file.
RM = /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/Cmake/3.17.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /dybfs/users/xuhangkun/SimTAO/analysis/calibrate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/build

# Include any dependencies generated for this target.
include CMakeFiles/mylib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mylib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mylib.dir/flags.make

CMakeFiles/mylib.dir/src/GeneralFunction.cpp.o: CMakeFiles/mylib.dir/flags.make
CMakeFiles/mylib.dir/src/GeneralFunction.cpp.o: ../src/GeneralFunction.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/dybfs/users/xuhangkun/SimTAO/analysis/calibrate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mylib.dir/src/GeneralFunction.cpp.o"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mylib.dir/src/GeneralFunction.cpp.o -c /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/GeneralFunction.cpp

CMakeFiles/mylib.dir/src/GeneralFunction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/src/GeneralFunction.cpp.i"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/GeneralFunction.cpp > CMakeFiles/mylib.dir/src/GeneralFunction.cpp.i

CMakeFiles/mylib.dir/src/GeneralFunction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/src/GeneralFunction.cpp.s"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/GeneralFunction.cpp -o CMakeFiles/mylib.dir/src/GeneralFunction.cpp.s

CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.o: CMakeFiles/mylib.dir/flags.make
CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.o: ../src/RadioActiveSource.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/dybfs/users/xuhangkun/SimTAO/analysis/calibrate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.o"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.o -c /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/RadioActiveSource.cpp

CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.i"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/RadioActiveSource.cpp > CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.i

CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.s"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/RadioActiveSource.cpp -o CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.s

CMakeFiles/mylib.dir/src/RunData.cpp.o: CMakeFiles/mylib.dir/flags.make
CMakeFiles/mylib.dir/src/RunData.cpp.o: ../src/RunData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/dybfs/users/xuhangkun/SimTAO/analysis/calibrate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mylib.dir/src/RunData.cpp.o"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mylib.dir/src/RunData.cpp.o -c /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/RunData.cpp

CMakeFiles/mylib.dir/src/RunData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/src/RunData.cpp.i"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/RunData.cpp > CMakeFiles/mylib.dir/src/RunData.cpp.i

CMakeFiles/mylib.dir/src/RunData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/src/RunData.cpp.s"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/RunData.cpp -o CMakeFiles/mylib.dir/src/RunData.cpp.s

CMakeFiles/mylib.dir/src/TAORunData.cpp.o: CMakeFiles/mylib.dir/flags.make
CMakeFiles/mylib.dir/src/TAORunData.cpp.o: ../src/TAORunData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/dybfs/users/xuhangkun/SimTAO/analysis/calibrate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mylib.dir/src/TAORunData.cpp.o"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mylib.dir/src/TAORunData.cpp.o -c /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/TAORunData.cpp

CMakeFiles/mylib.dir/src/TAORunData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/src/TAORunData.cpp.i"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/TAORunData.cpp > CMakeFiles/mylib.dir/src/TAORunData.cpp.i

CMakeFiles/mylib.dir/src/TAORunData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/src/TAORunData.cpp.s"
	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/src/TAORunData.cpp -o CMakeFiles/mylib.dir/src/TAORunData.cpp.s

# Object files for target mylib
mylib_OBJECTS = \
"CMakeFiles/mylib.dir/src/GeneralFunction.cpp.o" \
"CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.o" \
"CMakeFiles/mylib.dir/src/RunData.cpp.o" \
"CMakeFiles/mylib.dir/src/TAORunData.cpp.o"

# External object files for target mylib
mylib_EXTERNAL_OBJECTS =

libmylib.so: CMakeFiles/mylib.dir/src/GeneralFunction.cpp.o
libmylib.so: CMakeFiles/mylib.dir/src/RadioActiveSource.cpp.o
libmylib.so: CMakeFiles/mylib.dir/src/RunData.cpp.o
libmylib.so: CMakeFiles/mylib.dir/src/TAORunData.cpp.o
libmylib.so: CMakeFiles/mylib.dir/build.make
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libCore.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libImt.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libRIO.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libNet.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libHist.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libGraf.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libGraf3d.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libGpad.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libROOTDataFrame.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libTree.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libTreePlayer.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libRint.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libPostscript.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libMatrix.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libPhysics.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libMathCore.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libThread.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libMultiProc.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libRooStats.so
libmylib.so: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/ExternalLibs/ROOT/6.20.02/lib/libMinuit2.so
libmylib.so: CMakeFiles/mylib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/dybfs/users/xuhangkun/SimTAO/analysis/calibrate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libmylib.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mylib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mylib.dir/build: libmylib.so

.PHONY : CMakeFiles/mylib.dir/build

CMakeFiles/mylib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mylib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mylib.dir/clean

CMakeFiles/mylib.dir/depend:
	cd /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /dybfs/users/xuhangkun/SimTAO/analysis/calibrate /dybfs/users/xuhangkun/SimTAO/analysis/calibrate /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/build /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/build /dybfs/users/xuhangkun/SimTAO/analysis/calibrate/build/CMakeFiles/mylib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mylib.dir/depend


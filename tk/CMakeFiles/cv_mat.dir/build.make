# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/ubuntu/RBE4915/tk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/RBE4915/tk

# Include any dependencies generated for this target.
include CMakeFiles/cv_mat.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cv_mat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cv_mat.dir/flags.make

CMakeFiles/cv_mat.dir/cv_mat.cpp.o: CMakeFiles/cv_mat.dir/flags.make
CMakeFiles/cv_mat.dir/cv_mat.cpp.o: cv_mat.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/RBE4915/tk/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cv_mat.dir/cv_mat.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cv_mat.dir/cv_mat.cpp.o -c /home/ubuntu/RBE4915/tk/cv_mat.cpp

CMakeFiles/cv_mat.dir/cv_mat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cv_mat.dir/cv_mat.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/RBE4915/tk/cv_mat.cpp > CMakeFiles/cv_mat.dir/cv_mat.cpp.i

CMakeFiles/cv_mat.dir/cv_mat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cv_mat.dir/cv_mat.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/RBE4915/tk/cv_mat.cpp -o CMakeFiles/cv_mat.dir/cv_mat.cpp.s

CMakeFiles/cv_mat.dir/cv_mat.cpp.o.requires:
.PHONY : CMakeFiles/cv_mat.dir/cv_mat.cpp.o.requires

CMakeFiles/cv_mat.dir/cv_mat.cpp.o.provides: CMakeFiles/cv_mat.dir/cv_mat.cpp.o.requires
	$(MAKE) -f CMakeFiles/cv_mat.dir/build.make CMakeFiles/cv_mat.dir/cv_mat.cpp.o.provides.build
.PHONY : CMakeFiles/cv_mat.dir/cv_mat.cpp.o.provides

CMakeFiles/cv_mat.dir/cv_mat.cpp.o.provides.build: CMakeFiles/cv_mat.dir/cv_mat.cpp.o

# Object files for target cv_mat
cv_mat_OBJECTS = \
"CMakeFiles/cv_mat.dir/cv_mat.cpp.o"

# External object files for target cv_mat
cv_mat_EXTERNAL_OBJECTS =

cv_mat: CMakeFiles/cv_mat.dir/cv_mat.cpp.o
cv_mat: CMakeFiles/cv_mat.dir/build.make
cv_mat: /usr/lib/libopencv_vstab.so.2.4.13
cv_mat: /usr/lib/libopencv_tegra.so.2.4.13
cv_mat: /usr/lib/libopencv_imuvstab.so.2.4.13
cv_mat: /usr/lib/libopencv_facedetect.so.2.4.13
cv_mat: /usr/lib/libopencv_esm_panorama.so.2.4.13
cv_mat: /usr/lib/libopencv_detection_based_tracker.so.2.4.13
cv_mat: /usr/lib/libopencv_videostab.so.2.4.13
cv_mat: /usr/lib/libopencv_video.so.2.4.13
cv_mat: /usr/lib/libopencv_ts.a
cv_mat: /usr/lib/libopencv_superres.so.2.4.13
cv_mat: /usr/lib/libopencv_stitching.so.2.4.13
cv_mat: /usr/lib/libopencv_photo.so.2.4.13
cv_mat: /usr/lib/libopencv_objdetect.so.2.4.13
cv_mat: /usr/lib/libopencv_ml.so.2.4.13
cv_mat: /usr/lib/libopencv_legacy.so.2.4.13
cv_mat: /usr/lib/libopencv_imgproc.so.2.4.13
cv_mat: /usr/lib/libopencv_highgui.so.2.4.13
cv_mat: /usr/lib/libopencv_gpu.so.2.4.13
cv_mat: /usr/lib/libopencv_flann.so.2.4.13
cv_mat: /usr/lib/libopencv_features2d.so.2.4.13
cv_mat: /usr/lib/libopencv_core.so.2.4.13
cv_mat: /usr/lib/libopencv_contrib.so.2.4.13
cv_mat: /usr/lib/libopencv_calib3d.so.2.4.13
cv_mat: /usr/lib/libopencv_tegra.so.2.4.13
cv_mat: /usr/lib/libopencv_stitching.so.2.4.13
cv_mat: /usr/lib/libopencv_gpu.so.2.4.13
cv_mat: /usr/lib/libopencv_photo.so.2.4.13
cv_mat: /usr/lib/libopencv_legacy.so.2.4.13
cv_mat: /usr/local/cuda-6.5/lib/libcufft.so
cv_mat: /usr/lib/libopencv_video.so.2.4.13
cv_mat: /usr/lib/libopencv_objdetect.so.2.4.13
cv_mat: /usr/lib/libopencv_ml.so.2.4.13
cv_mat: /usr/lib/libopencv_calib3d.so.2.4.13
cv_mat: /usr/lib/libopencv_features2d.so.2.4.13
cv_mat: /usr/lib/libopencv_highgui.so.2.4.13
cv_mat: /usr/lib/libopencv_imgproc.so.2.4.13
cv_mat: /usr/lib/libopencv_flann.so.2.4.13
cv_mat: /usr/lib/libopencv_core.so.2.4.13
cv_mat: /usr/local/cuda-6.5/lib/libcudart.so
cv_mat: /usr/local/cuda-6.5/lib/libnppc.so
cv_mat: /usr/local/cuda-6.5/lib/libnppi.so
cv_mat: /usr/local/cuda-6.5/lib/libnpps.so
cv_mat: CMakeFiles/cv_mat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable cv_mat"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cv_mat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cv_mat.dir/build: cv_mat
.PHONY : CMakeFiles/cv_mat.dir/build

CMakeFiles/cv_mat.dir/requires: CMakeFiles/cv_mat.dir/cv_mat.cpp.o.requires
.PHONY : CMakeFiles/cv_mat.dir/requires

CMakeFiles/cv_mat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cv_mat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cv_mat.dir/clean

CMakeFiles/cv_mat.dir/depend:
	cd /home/ubuntu/RBE4915/tk && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/RBE4915/tk /home/ubuntu/RBE4915/tk /home/ubuntu/RBE4915/tk /home/ubuntu/RBE4915/tk /home/ubuntu/RBE4915/tk/CMakeFiles/cv_mat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cv_mat.dir/depend


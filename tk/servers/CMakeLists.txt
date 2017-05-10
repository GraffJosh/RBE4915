cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_FLAGS "-std=c++11 -pthread ${CMAKE_CXX_FLAGS}")

project(servers)


SET(CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/lib/cmake/ )

#find arm (hint, it's in the parent directory)
find_library(arm REQUIRED HINTS "..")
#get Open_CV, that should be installed to the computer.
find_package(OpenCV REQUIRED)
#we're going to also compile OpenTLD. The current
#implementation doesn't actually use this.
#add_subdirectory(OpenTLD)
#find_package(OpenTLD REQUIRED HINTS "OpenTLD/build")


#we're making a library called receiver. I don't really know why,
#but there you have it.
add_library(receiver SHARED video_server.cpp server.cpp aruco_camera.cpp)
target_link_libraries(receiver arm ${OpenCV_LIBS} )

#link_directories(OpenTLD/src/opentld/main)
include_directories(human ${OpenCV_INCLUDE_DIR})
#we're making a library for our human tracking code, should probaby have put this in
#the receiver lib.
add_library(human SHARED human_tracker.cpp)
target_link_libraries(human ${OpenCV_LIBS})

add_executable(video_server video_server.cpp)

include_directories(${OpenCV_INCLUDE_DIRS} ../arms)
add_dependencies(video_server arm receiver human)

target_link_libraries(video_server arm receiver human ${OpenCV_LIBS} )

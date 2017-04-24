cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_FLAGS "-std=c++11 -pthread ${CMAKE_CXX_FLAGS}")

project(servers)


SET(CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/lib/cmake/ )

find_library(arm HINTS "..")
find_package(OpenCV REQUIRED)

add_library(receiver SHARED video_server.cpp server.cpp aruco_camera.cpp)
target_link_libraries(receiver aruco arm ${OpenCV_LIBS} )

add_library(human SHARED human_tracker.cpp)
target_link_libraries(human ${OpenCV_LIBS})

add_executable(video_server video_server.cpp)

include_directories(${OpenCV_INCLUDE_DIRS} ../arms)
add_dependencies(video_server aruco arm receiver human)

target_link_libraries(video_server aruco arm receiver human ${OpenCV_LIBS} )

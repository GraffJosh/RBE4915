cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_FLAGS "-std=c++11 -pthread ${CMAKE_CXX_FLAGS}")

project(servers)

find_library(arms HINTS "..")

SET(CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/lib/cmake/ )

find_package(OpenCV REQUIRED)

add_executable(video_server video_server.cpp server.cpp)

include_directories(${OpenCV_INCLUDE_DIRS} ../arms)
add_dependencies(video_server aruco)

target_link_libraries(video_server aruco arm ${OpenCV_LIBS})

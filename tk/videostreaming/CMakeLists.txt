cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_FLAGS "-std=c++11 -pthread -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter ${CMAKE_CXX_FLAGS}")

project (server)

find_library(aruco HINTS "..")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ../markers)

add_executable(video_server video_server.cpp)
add_dependencies(video_server aruco)
target_link_libraries(video_server aruco arm ${OpenCV_LIBS})

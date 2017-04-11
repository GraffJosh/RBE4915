cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter ${CMAKE_CXX_FLAGS}")

project (hello)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(video_server video_server.cpp)


target_link_libraries(video_server ${OpenCV_LIBS})

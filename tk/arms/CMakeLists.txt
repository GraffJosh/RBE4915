cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_FLAGS "-std=c++11 -pthread ${CMAKE_CXX_FLAGS}")


project(arms)
include_directories("${CMAKE_SOURCE_DIR}/apriltags-cpp/src" )
add_subdirectory(apriltags-cpp)


SET(CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/lib/cmake/ )
find_package(aruco REQUIRED
              OpenCV REQUIRED)

add_library(arm SHARED arm_aruco.cpp arm_april.cpp arm_control.cpp tracker.cpp)
target_link_libraries(arm apriltags ${aruco_LIBS})

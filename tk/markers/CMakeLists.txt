cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")


project(markers)

SET(CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/lib/cmake/ )

find_package(aruco REQUIRED
              OpenCV REQUIRED)

find_library(jpg_math HINTS "../")
find_library(apriltags apriltags HINTS "apriltags-cpp/")

add_executable(read_markers read_markers.cpp)
target_link_libraries(read_markers ${aruco_LIBS})


add_library(arm SHARED arm_aruco.cpp arm_april.cpp)
include_directories(apriltags-cpp/src)
add_dependencies(arm apriltags jpg_math)
target_link_libraries(arm apriltags jpg_math ${OpenCV_LIBS} ${aruco_LIBS})


#target_link_libraries(arm_april apriltags-cpp ${OpenCV_LIBS})

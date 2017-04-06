cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
project(aruco_testproject)

SET(CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/lib/cmake/ )

find_package(aruco REQUIRED
              OpenCV REQUIRED)


#add_executable(detect_markers detect_markers.cpp)
#target_link_libraries(detect_markers  ${aruco_LIBS})

add_executable(read_markers read_markers.cpp)
target_link_libraries(read_markers  ${aruco_LIBS})

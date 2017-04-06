cmake_minimum_required(VERSION 2.8)

project (hello)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(server server.cpp)
add_executable(cv_mat cv_mat.cpp)

target_link_libraries(server ${OpenCV_LIBS})
target_link_libraries(imageread ${OpenCV_LIBS})

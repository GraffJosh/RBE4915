cmake_minimum_required(VERSION 2.8)

project (hello)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

#add_executable(cv_hello hello_world_cv.cpp)
#add_executable(cv_mat cv_mat.cpp)
add_executable(imageread imageread.cpp)

#target_link_libraries(cv_hello ${OpenCV_LIBS})
target_link_libraries(imageread ${OpenCV_LIBS})
#target_link_libraries(cv_mat ${OpenCV_LIBS})


cmake_minimum_required(VERSION 2.8)

project(images)

find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)

find_package(libexstl PATHS ../.. REQUIRED)

include_directories(${OpenCV_INCLUDE_DIR} ${libexstl_INCLUDE_DIR} include)

add_library(${PROJECT_NAME} src/images.cpp src/images_read.cpp src/images_process.cpp src/images_write.cpp)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${libexstl_LIBS} ${OpenCV_LIBS})

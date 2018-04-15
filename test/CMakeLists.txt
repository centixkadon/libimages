
cmake_minimum_required(VERSION 2.8)

project(images)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(libexstl PATHS ../.. REQUIRED)
find_package(libimages PATHS ../.. REQUIRED)

add_subdirectory(${libexstl_PATH} libexstl)
add_subdirectory(${libimages_PATH} libimages)

include_directories(${libexstl_INCLUDE_DIR} ${libimages_INCLUDE_DIR})

add_executable(${PROJECT_NAME}_test main.cpp precomp.cpp)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})

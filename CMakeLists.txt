cmake_minimum_required(VERSION 3.13)
project(oogl)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations -Wno-unused-value ${CMAKE_C_FLAGS}")

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED graphics window system)
find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)
find_package(glm REQUIRED)

include_directories(${SFML_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

include(CMakeExamples.cmake)
add_example_directory(examples)
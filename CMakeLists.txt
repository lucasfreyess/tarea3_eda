cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
# set the project name

project(calculadora
VERSION 1.0
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_subdirectory(src)
#add_subdirectory(tests)

add_executable(calculadora test/test.cpp src/abb.cpp src/abbNode.cpp src/calculator.cpp src/node.cpp src/stack.cpp src/utils.cpp)
target_include_directories(calculadora PUBLIC ${PROJECT_SOURCE_DIR}/include)


# add the executable
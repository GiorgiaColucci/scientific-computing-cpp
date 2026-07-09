cmake_minimum_required(VERSION 3.20)
project(esercitazione10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

add_executable(main main.cpp)
add_test(NAME test_gradiente COMMAND main)

target_include_directories(main PRIVATE /usr/include/eigen3)

enable_testing()
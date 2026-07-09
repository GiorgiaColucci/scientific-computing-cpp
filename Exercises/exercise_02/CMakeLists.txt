cmake_minimum_required(VERSION 3.20)
project(esercitazione2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE CXX FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

add_executable(es1_1 ese1_parte1.cpp)
add_executable(es1_2 ese1_parte2.cpp)
add_executable(es2 ese2.cpp)
add_executable(es3 ese3.cpp)

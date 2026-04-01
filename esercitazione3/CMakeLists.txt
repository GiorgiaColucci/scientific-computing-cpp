cmake_minimum_required(VERSION 3.20)
project(esercitazione2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE CXX FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

set(SOURCES main.cpp header.hpp)
add_executable(eseguibile3 ${SOURCES})

set(SOURCES prova.cpp header.hpp)
add_executable(eseguibile3_prova ${SOURCES})

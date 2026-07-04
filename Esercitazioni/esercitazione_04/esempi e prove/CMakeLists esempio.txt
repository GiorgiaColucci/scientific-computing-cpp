cmake_minimum_required(VERSION 3.20)
project(esercitazione2) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla -Wno-sign-compare")

set(SRC_rf esempio_randfiller.cpp)
add_executable(esempio_randfiller ${SRC_rf})

set(SRC_tc esempio_timecounter.cpp timecounter.cpp)
add_executable(esempio_timecounter ${SRC_tc})

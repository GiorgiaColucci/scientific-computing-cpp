cmake_minimum_required(VERSION 3.20)
project(pcs2026)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Werror=vla")

# Eigen: serve al solver (solve.hpp) per matrici e sistemi lineari.
find_package(Eigen3 3.3 REQUIRED NO_MODULE)


# Cartelle di inclusione: header sono in 'include'
include_directories(include)

# Sorgenti del nucleo (i .cpp del progetto, escluso main e test).
# Non si mettono gradiente e costruzione grafo perchè LIB_SOURCES viene usata 
# da tutti gli eseguibili, ma test_parser non linka eigen e invece gradiente lo 
# include, quindi fallirebbe. 
set(LIB_SOURCES
    src/netlist_parser.cpp
)


add_executable(main main.cpp ${LIB_SOURCES} src/conjugate_gradient.cpp src/graph_construction.cpp)
target_link_libraries(main PRIVATE Eigen3::Eigen)

enable_testing()


# Test del parser:Non ha bisogno di Eigen perche' testa solo il parsing della netlist.
add_executable(test_parser test/test_parser.cpp ${LIB_SOURCES})
add_test(NAME parser COMMAND test_parser)

add_executable(test_graph test/test_graph.cpp ${LIB_SOURCES} src/graph_construction.cpp)
add_test(NAME graph COMMAND test_graph
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

## Si fa il link a eigen per sicurezza, anche se usa solo template header
add_executable(test_de_pina test/test_de_pina.cpp)
target_link_libraries(test_de_pina PRIVATE Eigen3::Eigen)
add_test(NAME depina COMMAND test_de_pina)

add_executable(test_cycles_DFS test/test_cycles_DFS.cpp)
add_test(NAME cycles_dfs COMMAND test_cycles_DFS)

add_executable(test_solve test/test_solve.cpp ${LIB_SOURCES} src/graph_construction.cpp src/conjugate_gradient.cpp)
target_link_libraries(test_solve PRIVATE Eigen3::Eigen)
add_test(NAME solve COMMAND test_solve
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

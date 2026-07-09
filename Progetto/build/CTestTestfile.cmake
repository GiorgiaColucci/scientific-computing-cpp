# CMake generated Testfile for 
# Source directory: /home/pcsdocker/Data/PCS_2026/Progetto
# Build directory: /home/pcsdocker/Data/PCS_2026/Progetto/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[parser]=] "/home/pcsdocker/Data/PCS_2026/Progetto/build/test_parser")
set_tests_properties([=[parser]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/pcsdocker/Data/PCS_2026/Progetto/CMakeLists.txt;32;add_test;/home/pcsdocker/Data/PCS_2026/Progetto/CMakeLists.txt;0;")
add_test([=[graph]=] "/home/pcsdocker/Data/PCS_2026/Progetto/build/test_graph")
set_tests_properties([=[graph]=] PROPERTIES  WORKING_DIRECTORY "/home/pcsdocker/Data/PCS_2026/Progetto" _BACKTRACE_TRIPLES "/home/pcsdocker/Data/PCS_2026/Progetto/CMakeLists.txt;35;add_test;/home/pcsdocker/Data/PCS_2026/Progetto/CMakeLists.txt;0;")
add_test([=[depina]=] "/home/pcsdocker/Data/PCS_2026/Progetto/build/test_de_pina")
set_tests_properties([=[depina]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/pcsdocker/Data/PCS_2026/Progetto/CMakeLists.txt;41;add_test;/home/pcsdocker/Data/PCS_2026/Progetto/CMakeLists.txt;0;")
add_test([=[cycles_dfs]=] "/home/pcsdocker/Data/PCS_2026/Progetto/build/test_cycles_DFS")
set_tests_properties([=[cycles_dfs]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/pcsdocker/Data/PCS_2026/Progetto/CMakeLists.txt;44;add_test;/home/pcsdocker/Data/PCS_2026/Progetto/CMakeLists.txt;0;")
add_test([=[solve]=] "/home/pcsdocker/Data/PCS_2026/Progetto/build/test_solve")
set_tests_properties([=[solve]=] PROPERTIES  WORKING_DIRECTORY "/home/pcsdocker/Data/PCS_2026/Progetto" _BACKTRACE_TRIPLES "/home/pcsdocker/Data/PCS_2026/Progetto/CMakeLists.txt;48;add_test;/home/pcsdocker/Data/PCS_2026/Progetto/CMakeLists.txt;0;")

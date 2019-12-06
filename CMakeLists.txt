cmake_minimum_required(VERSION 3.10)
project(infosec)

set(CMAKE_CXX_STANDARD 17)

add_library(matrix Matrix.cpp Matrix.h)
add_library(intmodp IntModuloP.cpp IntModuloP.h)
add_library(coder Coder.cpp Coder.h)
add_library(decoder Decoder.cpp Decoder.h)

add_executable(myclient myclient.cpp)
add_executable(myserver myserver.cpp)

add_executable(dg_test tests/dg_test.cpp DegreeTable.cpp)
add_executable(block_matrix_test tests/block_matrix_test.cpp)
add_executable(intmodp_test tests/intmodp_test.cpp IntModuloP.cpp)

target_link_libraries(myserver matrix intmodp)
target_link_libraries(block_matrix_test matrix intmodp)
target_link_libraries(myclient matrix intmodp)

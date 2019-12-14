cmake_minimum_required(VERSION 3.10)
project(infosec)

set(CMAKE_CXX_STANDARD 17)

add_library(matrix Matrix.cpp Matrix.h)
add_library(intmodp IntModuloP.cpp IntModuloP.h)
add_library(codec Decoder.cpp Decoder.h Coder.cpp Coder.h)
add_library(dg DegreeTable.cpp DegreeTable.h)

add_executable(myclient myclient.cpp)
add_executable(myserver myserver.cpp)

add_executable(codec_example tests/codec_example.cpp)
add_executable(dg_test tests/dg_test.cpp DegreeTable.cpp)
add_executable(block_matrix_test tests/block_matrix_test.cpp)
add_executable(intmodp_test tests/intmodp_test.cpp IntModuloP.cpp)
add_executable(coder_test tests/coder_test.cpp Coder.cpp)     #
add_executable(horner_test tests/horner_test.cpp)

target_link_libraries(myserver matrix intmodp)
target_link_libraries(intmodp_test matrix intmodp)
target_link_libraries(block_matrix_test matrix intmodp)
target_link_libraries(coder_test coder matrix intmodp dg)
target_link_libraries(myclient matrix intmodp)
target_link_libraries(horner_test matrix intmodp)
target_link_libraries(codec_example matrix intmodp codec dg)

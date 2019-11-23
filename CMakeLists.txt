cmake_minimum_required(VERSION 3.10)
project(infosec)

set(CMAKE_CXX_STANDARD 17)

add_executable(myclient myclient.cpp Matrix.cpp IntModuloP.cpp)
add_executable(myserver myserver.cpp Matrix.cpp IntModuloP.cpp)
add_executable(dg_test tests/dg_test.cpp DegreeTable.cpp)
add_executable(intmodp_test tests/intmodp_test.cpp IntModuloP.cpp)


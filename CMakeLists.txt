cmake_minimum_required(VERSION 3.10)
project(infosec)

set(CMAKE_CXX_STANDARD 17)

add_executable(myclient myclient.cpp Matrix.cpp DegreeTable.cpp DegreeTable.h)
add_executable(myserver myserver.cpp Matrix.cpp DegreeTable.cpp DegreeTable.h)
add_executable(dg_test tests/dg_test.cpp DegreeTable.cpp)

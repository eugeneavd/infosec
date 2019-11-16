cmake_minimum_required(VERSION 3.10)
project(infosec)

set(CMAKE_CXX_STANDARD 17)

add_executable(myclient myclient.cpp Matrix.cpp)
add_executable(myserver myserver.cpp Matrix.cpp)

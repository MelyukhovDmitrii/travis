cmake_minimum_required(VERSION 3.9)
project(ot_task4_MelyukhovDmitrii)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

add_executable(ot_task4_MelyukhovDmitrii
        myServer.cpp myServer.h serverMain.cpp)

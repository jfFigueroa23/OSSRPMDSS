cmake_minimum_required(VERSION 3.0)
project(ELECTREIII)

set(CMAKE_CXX_STANDARD 20)

add_executable(ELECTREIII main.cpp
        ElectreIII.cpp
        ../../SUPERACION/Superacion.cpp)

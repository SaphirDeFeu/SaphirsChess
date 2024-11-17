cmake_minimum_required(VERSION 3.29)
project(saphirschess)

set(CMAKE_CXX_STANDARD 26)

add_executable(saphirschess src/main.cpp
        src/board.cpp
        src/board.hpp
        src/state.cpp
        src/state.hpp
        src/piece.cpp
        src/piece.hpp)

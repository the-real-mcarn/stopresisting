cmake_minimum_required(VERSION 3.30)
project(stopresisting)

set(CMAKE_CXX_STANDARD 20)

add_executable(stopresisting src/main.cpp
        src/stopresisting/StopResisting.cpp
        src/stopresisting/StopResisting.hpp)

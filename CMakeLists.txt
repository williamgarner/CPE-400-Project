cmake_minimum_required(VERSION 3.6)
project(networking)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Network.cpp src/Network.h)
add_executable(networking ${SOURCE_FILES})
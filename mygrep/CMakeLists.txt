cmake_minimum_required(VERSION 3.10)
project(mygrep)

set(CMAKE_CXX_STANDARD 11)

add_executable(mygrep main.cpp Helpers.cpp Helpers.h)
cmake_minimum_required(VERSION 3.5.2)
project(myrm)

find_package(Boost COMPONENTS program_options filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(myrm main.cpp)
target_link_libraries(myrm ${Boost_LIBRARIES})

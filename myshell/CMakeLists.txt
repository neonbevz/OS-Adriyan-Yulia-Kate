cmake_minimum_required(VERSION 3.5.1)
project(myshell)

set(CMAKE_CXX_STANDARD 14)

add_executable(myshell main.cpp)

find_package( Boost COMPONENTS filesystem system REQUIRED )

include_directories(${BOOST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

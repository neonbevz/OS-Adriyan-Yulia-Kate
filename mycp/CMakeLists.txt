cmake_minimum_required(VERSION 3.10)
project(mycp)

set(CMAKE_CXX_STANDARD 11)

add_executable(mycp main.cpp Helpers.cpp Helpers.h Files.cpp Files.h)

find_package( Boost COMPONENTS filesystem system REQUIRED )

include_directories(${BOOST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

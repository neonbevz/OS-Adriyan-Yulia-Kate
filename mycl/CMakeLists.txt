cmake_minimum_required(VERSION 3.10)
project(mycl)

set(CMAKE_CXX_STANDARD 11)


add_executable(myclServer serverMain.cpp Server.h Server.cpp)
add_executable(myclClient clientMain.cpp)


FIND_PACKAGE(Boost 1.63.0 REQUIRED COMPONENTS system thread regex)
SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

target_link_libraries(myclServer ${USED_LIBS})
target_link_libraries(myclClient ${USED_LIBS})


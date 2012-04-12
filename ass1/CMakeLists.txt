cmake_minimum_required(VERSION 2.6) 
project(ass1)

find_package(Boost COMPONENTS regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# C++0x support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")

add_executable(ass1 main.cpp ngram_requency.cpp)
target_link_libraries(ass1 ${Boost_LIBRARIES})

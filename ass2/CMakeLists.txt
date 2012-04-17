cmake_minimum_required(VERSION 2.6) 
project(ass2)

find_package(Boost COMPONENTS regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# C++0x support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x")

add_executable(ass2 main.cpp ngram_requency.cpp probabilities.cpp smoothing.cpp)
target_link_libraries(ass2 ${Boost_LIBRARIES})

cmake_minimum_required(VERSION 2.6) 
project(ass3)

find_package(Boost COMPONENTS regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# C++0x support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x")

add_executable(ass3 main.cpp ngram_requency.cpp probabilities.cpp smoothing.cpp)
target_link_libraries(ass3 ${Boost_LIBRARIES})

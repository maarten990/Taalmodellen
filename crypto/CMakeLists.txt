cmake_minimum_required(VERSION 2.6) 
project(Cryptografie)

# C++0x support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x")

add_executable(crypto main.cpp languagemodel.cpp relative_frequencies.cpp)

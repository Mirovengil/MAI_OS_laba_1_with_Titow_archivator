cmake_minimum_required(VERSION 3.5.0)
project(sobelFilter_laba2 VERSION 0.1.0 LANGUAGES C CXX)
include_directories(./headers/)
add_executable(sobelFilter_laba2 ./main.cpp ./sobolsFilter.cpp)
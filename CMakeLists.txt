cmake_minimum_required(VERSION 3.5.0)
project(sobelFilter_laba4 VERSION 0.1.0 LANGUAGES C CXX)
find_package(Qt5 COMPONENTS Gui Widgets Core)
include_directories(./headers/)
add_executable(sobelFilter_laba4 ./main.cpp ./sobelsFilter.cpp ./ImageMatrix.cpp ./RGBCell.cpp
./GUI.cpp)
target_link_libraries(sobelFilter_laba4 Qt5::Gui Qt5::Widgets Qt5::Core)
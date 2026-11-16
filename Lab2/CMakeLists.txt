cmake_minimum_required(VERSION 4.3.0)
project (lab2)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenMP REQUIRED)

add_executable(Multiplication Multiplication.cpp)
add_executable(Generator Generator.cpp)

target_link_libraries(Multiplication PRIVATE OpenMP::OpenMP_CXX)


cmake_minimum_required(VERSION 3.17)
project(GJKDistanceAlgorithm C)

set(CMAKE_C_STANDARD 11)

add_executable(GJKDistanceAlgorithm main.c)
target_link_libraries(GJKDistanceAlgorithm m)

cmake_minimum_required(VERSION 3.17)
project(GJKDistanceAlgorithm C)

set(CMAKE_C_STANDARD 11)

add_executable(GJKDistanceAlgorithm main.c circle.h multipoint.h generics.h vector_math.h vector_math.c)
target_link_libraries(GJKDistanceAlgorithm m)

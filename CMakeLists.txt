cmake_minimum_required(VERSION 3.17)
project(graph)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic)

add_subdirectory(tests)

add_library(graph adjacency_matrix.h)
set_target_properties(graph PROPERTIES LINKER_LANGUAGE CXX)
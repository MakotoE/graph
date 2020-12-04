project(tests)

add_compile_options(-Wall -Wextra -pedantic)

add_subdirectory(googletest)

add_executable(tests adjacency_matrix.cpp adjacency_list.cpp)
target_link_libraries(tests gtest gtest_main graph)
cmake_minimum_required(VERSION 3.2)

project(Queens)


add_executable(queens queens_v2.cpp)
add_executable(test test.cpp)


set_target_properties(queens test_ PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

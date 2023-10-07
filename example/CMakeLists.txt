# Author: zzz00yx, 2023

cmake_minimum_required(VERSION 3.12)

add_executable(example
    example1.cpp
    example2.cpp
    simple_fifo.cpp
)

target_link_libraries(example
    SCGTest
)

include(GoogleTest)
gtest_discover_tests(example)

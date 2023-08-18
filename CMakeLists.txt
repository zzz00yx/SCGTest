# Author: yanxin, 2023

cmake_minimum_required(VERSION 3.12)

project(SCGTest)

option(ENABLE_EXAMPLE "Enable building the example add add them to ctest" OFF)

find_package(GTest REQUIRED)
find_package(SystemCLanguage CONFIG REQUIRED)
set(CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

add_library(SCGTest OBJECT
    scgtest_main.cpp
)

target_include_directories(SCGTest PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(SCGTest
    GTest::gtest
    SystemC::systemc
)

if(ENABLE_EXAMPLE)
    enable_testing()
    add_subdirectory(example)
endif()

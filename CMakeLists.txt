cmake_minimum_required(VERSION 4.3)
project(tiny_parse)

set(CMAKE_CXX_STANDARD 26)

add_library(tiny_parse STATIC
        src/parser.cpp
        include/tiny-parse/parser.hpp
        src/option.hpp
)
target_include_directories(tiny_parse PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(tests)
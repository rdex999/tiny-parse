cmake_minimum_required(VERSION 4.3)
project(tiny_parse)

set(CMAKE_CXX_STANDARD 26)

add_library(tiny_parse STATIC
        src/parser.cpp
        include/tiny-parse/parser.hpp
)
target_include_directories(tiny_parse PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
cmake_minimum_required(VERSION 4.3)
project(tiny_parse)

set(CMAKE_CXX_STANDARD 26)

option(TINY_PARSE_TESTS "Build Tiny Parse tests." OFF)

add_library(tiny_parse STATIC
        src/parser.cpp
        include/tiny-parse/parser.hpp
        include/tiny-parse/result.hpp
        src/option.hpp
        src/option.cpp
        src/result.cpp
        src/utils.hpp
)

target_include_directories(tiny_parse
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(TINY_PARSE_TESTS)
    add_subdirectory(tests)
endif()
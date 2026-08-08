include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        main
)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)

add_executable(tiny_parse_tests
        parser_test.cpp
)

target_link_libraries(tiny_parse_tests
        PRIVATE
        tiny_parse
        GTest::gtest_main
)

target_include_directories(tiny_parse_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

gtest_discover_tests(tiny_parse_tests)

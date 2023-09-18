# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

# Include Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    nanobench
    GIT_REPOSITORY https://github.com/martinus/nanobench.git
    GIT_TAG v4.3.11
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nanobench)

add_executable(${PROJECT_NAME}_tests
    test_main.cpp
    test_benchmark.cpp
)

target_include_directories(${PROJECT_NAME}_tests PRIVATE .)

target_link_libraries(${PROJECT_NAME}_tests PRIVATE
    my_container
    gtest_main
    nanobench
)

target_compile_options(${PROJECT_NAME}_tests PRIVATE -Wall -Wextra -pedantic -fbounds-check)

# Enable testing with CTest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)

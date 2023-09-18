cmake_minimum_required(VERSION 3.15)
project(my_container)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    include/my_container.hpp
)

add_library(my_container INTERFACE ${HEADERS})
target_include_directories(my_container INTERFACE include)

enable_testing()
add_subdirectory(tests)

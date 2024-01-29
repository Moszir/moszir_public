cmake_minimum_required(VERSION 3.20)

project(
    moszir_public
    LANGUAGES CXX
    VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 23)

include(cmake/find_python.cmake)
include(cmake/find_googletest.cmake)
include(cmake/find_google_benchmark.cmake)

add_subdirectory(cpp)

cmake_minimum_required(VERSION 3.20)
project(MoszirCpp VERSION 1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Third-party libraries managed by Conan
include("conan.cmake")
conan_cmake_settings(conan_settings)

# GTest for testing
conan_cmake_install(
    CONANFILE gtest_conanfile.txt
    INSTALL_ARGS ${conan_settings}
    BUILD)
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
enable_testing()

conan_basic_setup()

add_subdirectory(leetcode)

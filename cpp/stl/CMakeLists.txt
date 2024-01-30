include(GoogleTest)

function(add_stl_test name)
    set(executable_name "stl_${name}_test")
    add_executable(${executable_name} "${name}.cpp")
    target_link_libraries(${executable_name} gtest gtest_main)
    gtest_discover_tests(${executable_name})
endfunction()

function(add_stl_benchmark name)
    set(executable_name "stl_${name}_benchmark")
    add_executable(${executable_name} "${name}_benchmarks.cpp")
    target_link_libraries(${executable_name} benchmark::benchmark)
endfunction()

add_subdirectory(algorithm)

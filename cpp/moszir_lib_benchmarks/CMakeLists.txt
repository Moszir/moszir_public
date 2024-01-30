function(moszir_add_benchmark name)
    add_executable(${name} "${name}.cpp")
    target_link_libraries(${name} benchmark::benchmark moszir_lib)
endfunction()

moszir_add_benchmark(string_vector_benchmark)
moszir_add_benchmark(string_view_vector_benchmark)

add_library(moszir_lib INTERFACE)
target_include_directories(moszir_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/moszir_lib)

add_subdirectory(moszir_lib_tests)

add_subdirectory(moszir_lib_benchmarks)

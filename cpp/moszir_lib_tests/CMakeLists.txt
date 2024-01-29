include(GoogleTest)

add_executable(
    string_vector_test
    "string_vector_test.cpp"
)

target_link_libraries(
    string_vector_test
    gtest
    gtest_main
    moszir_lib
)

gtest_discover_tests(
    string_vector_test
    PROPERTIES
    LABELS "moszir"
)

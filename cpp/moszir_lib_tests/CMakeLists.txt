include(GoogleTest)

function(moszir_add_test module_name)
    add_executable("${module_name}_test" "${module_name}_test.cpp")
    target_link_libraries("${module_name}_test" gtest gtest_main moszir_lib)
    gtest_discover_tests("${module_name}_test" PROPERTIES LABELS "moszir")
endfunction()

moszir_add_test(string_vector)
moszir_add_test(string_view_vector)

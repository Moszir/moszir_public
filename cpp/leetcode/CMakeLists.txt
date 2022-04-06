function(add_leetcode_problem name)
    add_executable(${name} "problem/${name}.cpp")
    target_include_directories(${name} PUBLIC "${CONAN_INCLUDE_DIRS}")
    target_link_libraries(${name} ${CONAN_LIBS})
    add_test(
        NAME ${name}
        COMMAND $<TARGET_FILE:${name}>
    )
endfunction()

add_leetcode_problem("402_remove_k_digits")
add_leetcode_problem("1675_minimize_deviation_in_array")

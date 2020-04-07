macro(package_add_test TESTNAME)
    # create an exectuable in which the tests will be stored
    add_executable(${TESTNAME} ${ARGN})
    # link the Google test infrastructure, mocking library, and a default main fuction to
    # the test executable.  Remove g_test_main if writing your own main function.
    target_link_libraries(${TESTNAME} gtest gmock gtest_main )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})

    # Test dependant build options
    target_compile_options(${TESTNAME} PRIVATE
        -I${CMAKE_CURRENT_SOURCE_DIR}/../sources
    )
    target_link_libraries(${TESTNAME} drivers)
endmacro()

package_add_test(valve valve_test.cc valve_mock.cc)

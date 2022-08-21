add_executable(tests TestScenarios.cpp)
target_link_libraries(tests gtest_main scp)
add_test(NAME TestScenarios COMMAND tests)

add_custom_command(
        TARGET tests PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/resources"
                "${CMAKE_CURRENT_BINARY_DIR}/resources")
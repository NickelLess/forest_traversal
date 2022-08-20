add_executable(tests TestScenarios.cpp)
target_link_libraries(tests gtest_main)
add_test(NAME TestScenarios COMMAND tests)
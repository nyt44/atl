file(GLOB TEST_FILES "*Test.cpp")

add_executable(client_test ${TEST_FILES})

target_link_libraries(client_test gtest
                                  gmock
                                  gtest_main
                                  client)

add_test(NAME client_test COMMAND client_test)

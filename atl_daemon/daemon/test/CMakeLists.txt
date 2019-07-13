file(GLOB TEST_FILES "*Test.cpp")

add_executable(daemon_test ${TEST_FILES})

target_link_libraries(daemon_test
                      gtest
                      gmock
                      gtest_main
                      pthread
                      daemon)

add_test(NAME daemon_test COMMAND daemon_test)

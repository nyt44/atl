file(GLOB SOURCE_FILES "*.hpp" "*.cpp")

add_subdirectory(daemon)

add_executable(atl_daemon ${SOURCE_FILES})
target_link_libraries(atl_daemon daemon
                                 rt)

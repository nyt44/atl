file(GLOB SOURCE_FILES "*.hpp" "*.cpp")

add_subdirectory(tests)

add_library(daemon ${SOURCE_FILES})
target_link_libraries(daemon common
                             rt
                             dbg_trace)

target_include_directories(daemon PUBLIC .)

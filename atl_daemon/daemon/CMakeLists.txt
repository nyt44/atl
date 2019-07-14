file(GLOB SOURCE_FILES "*.hpp" "*.cpp")

add_subdirectory(test)

add_library(daemon ${SOURCE_FILES})
target_link_libraries(daemon shared_memory_lib
                             rt)

target_include_directories(daemon PUBLIC .)

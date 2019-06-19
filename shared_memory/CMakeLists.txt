file(GLOB SOURCE_FILES "*.hpp" "*.cpp")

add_library(shared_memory_lib ${SOURCE_FILES})

target_include_directories(shared_memory_lib PUBLIC .)

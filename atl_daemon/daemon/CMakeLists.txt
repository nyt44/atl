file(GLOB SOURCE_FILES "*.hpp" "*.cpp")

add_subdirectory(test)

add_library(daemon ${SOURCE_FILES})

target_include_directories(daemon PUBLIC .)

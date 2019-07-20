file(GLOB SOURCE_FILES "*.hpp" "*.cpp")

add_library(common ${SOURCE_FILES})
target_link_libraries(common rt
                             pthread)

target_include_directories(common PUBLIC .)

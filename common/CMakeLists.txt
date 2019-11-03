file(GLOB SOURCE_FILES "*.hpp" "*.cpp")

add_library(common SHARED ${SOURCE_FILES})
target_link_libraries(common rt
                             pthread
                             dbg_trace)

target_include_directories(common PUBLIC .)
